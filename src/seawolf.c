/*
 *
 */

#include "seawolf.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// static functions
static void cursor_position_callback( GLFWwindow *window, double x, double y )
{
   pSeaWolf s_w = glfwGetWindowUserPointer( window );

   s_w->cursorX = x;
   s_w->cursorY = y;
}

static void key_callback( GLFWwindow *window, int key, int scancode, int action, int mods )
{
   pSeaWolf s_w = glfwGetWindowUserPointer( window );

   s_w->keyKey      = key;
   s_w->keyScancode = scancode;
   s_w->keyAction   = action;
   s_w->keyMods     = mods;

   if( action != GLFW_PRESS )
      return;

   switch( key )
   {
      case KEY_PRINT_SCREEN:
         break;
   }
}

static void mouse_button_callback( GLFWwindow *window, int button, int action, int mods )
{
   pSeaWolf s_w = glfwGetWindowUserPointer( window );

   s_w->mouseButton = button;
   s_w->mouseAction = action;
   s_w->mouseMods   = mods;
}

static void window_maximize_callback( GLFWwindow *window, int maximized )
{
   pSeaWolf s_w = glfwGetWindowUserPointer( window );

   s_w->winMaximized = maximized;
}

static void window_size_callback( GLFWwindow *window, int width, int height )
{
   pSeaWolf s_w = glfwGetWindowUserPointer( window );

   s_w->width  = width;
   s_w->height = height;
}

static void hex_to_ClearColor( uint32_t hexColor )
{
   double r, g, b;
   r = ( ( hexColor >> 16 ) & 0xFF ) / 255.0;
   g = ( ( hexColor >> 8  ) & 0xFF ) / 255.0;
   b = (   hexColor         & 0xFF ) / 255.0;

   glClearColor( r, g, b, 1.0 );
}

static void hex_to_Color3f( uint32_t hexColor )
{
   float r, g, b;
   r = ( ( hexColor >> 16 ) & 0xFF ) / 255.0;
   g = ( ( hexColor >> 8  ) & 0xFF ) / 255.0;
   b = (   hexColor         & 0xFF ) / 255.0;

   glColor3f( r, g, b );
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// API functions
pSeaWolf sw_CreateWindow( int width, int height, const char *title )
{
   pSeaWolf w;

   if( ! glfwInit() )
   {
      exit( EXIT_FAILURE );
   }

   w = calloc( 1, sizeof( SeaWolf ) );

   w->width  = width;
   w->height = height;
   w->title  = title;

   w->window = glfwCreateWindow( w->width, w->height, w->title, NULL, NULL );
   if( ! w->window )
   {
      free( w );
      glfwTerminate();
      exit( EXIT_FAILURE );
   }
   glfwMakeContextCurrent( w->window );
   glfwSetWindowUserPointer( w->window, w );

   glfwSetCursorPosCallback( w->window, cursor_position_callback );
   glfwSetKeyCallback( w->window, key_callback );
   glfwSetMouseButtonCallback( w->window, mouse_button_callback );
   glfwSetWindowMaximizeCallback( w->window, window_maximize_callback );
   glfwSetWindowSizeCallback( w->window, window_size_callback );

   glfwSetWindowSizeLimits( w->window, w->width, w->height, GLFW_DONT_CARE , GLFW_DONT_CARE );

   return w;
}

bool sw_MainLoop( pSeaWolf w )
{
   w->closeFlag = glfwWindowShouldClose( w->window );
   glfwSetWindowShouldClose( w->window, GLFW_FALSE );

   return w->closeFlag;
}

bool sw_CloseWindow( pSeaWolf w )
{
   glfwDestroyWindow( w->window );
   free( w );
   glfwTerminate();

   exit( EXIT_SUCCESS );
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
void begin_drawing( pSeaWolf w )
{
   glfwGetFramebufferSize( w->window, &w->width, &w->height );

   glViewport( 0, 0, w->width, w->height );
   hex_to_ClearColor( w->background );
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glDisable( GL_CULL_FACE );
   glDisable( GL_DEPTH_TEST );
   glDisable( GL_BLEND );
   glDepthMask( GL_TRUE );

   // set up orthographic projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, w->width, 0, w->height, -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glEnable( GL_TEXTURE_2D );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void end_drawing( pSeaWolf w )
{
   glfwSwapBuffers( w->window );
}

int opengl_functions( pSeaWolf w, iShape type, int par1, int par2, int par3, int par4, int par5, int par6, int par7 )
{
   int ret = 1;

   switch( type )
   {
   case OPENGL_BACKGROUND:

      w->background = par1;
      break;

   case OPENGL_POINT:

      hex_to_Color3f( par3 );
      glBegin( GL_POINTS );
      glVertex2f( par1, par2 );
      glEnd();
      break;

   case OPENGL_POINTSIZE:

      hex_to_Color3f( par4 );
      glPointSize( par3 );
      glBegin( GL_POINTS );
      glVertex2f( par1, par2 );
      glEnd();
      break;

   case OPENGL_LINES:

      hex_to_Color3f( par5 );
      glBegin( GL_LINES );
      glVertex2f( par1, par2 );
      glVertex2f( par3, par4 );
      glEnd();
      break;

   case OPENGL_RECT:

      hex_to_Color3f( par5 );
      glBegin( GL_LINE_LOOP );
      glVertex2f( par1, par2 );
      glVertex2f( par3, par2 );
      glVertex2f( par3, par4 );
      glVertex2f( par1, par4 );
      glEnd();
      break;

   case OPENGL_FILLRECT:

      hex_to_Color3f( par5 );
      glBegin( GL_POLYGON );
      glVertex2f( par1, par2 );
      glVertex2f( par3, par2 );
      glVertex2f( par3, par4 );
      glVertex2f( par1, par4 );
      glEnd();
      break;

   case OPENGL_TRIANGLE:

      hex_to_Color3f( par7 );
      glBegin( GL_LINE_LOOP );
      glVertex2f( par1, par2 );
      glVertex2f( par3, par4 );
      glVertex2f( par5, par6 );
      glEnd();
      break;

   case OPENGL_FILLTRIANGLE:

      hex_to_Color3f( par7 );
      glBegin( GL_TRIANGLES );
      glVertex2f( par1, par2 );
      glVertex2f( par3, par4 );
      glVertex2f( par5, par6 );
      glEnd();
      break;

   case OPENGL_CIRCLE:

      hex_to_Color3f( par4 );
      glBegin( GL_LINE_LOOP );
         for( int i = 0; i < 360; i++ )
         {
            float angle = i * M_PI / 180.0;
            glVertex2f( par1 + cos( angle ) * par3, par2 + sin( angle ) * par3 );
         }
      glEnd();
      break;

   case OPENGL_FILLCIRCLE:

      hex_to_Color3f( par4 );
      glBegin( GL_POLYGON );
         for( int i = 0; i < 360; i++ )
          {
            float angle = i * M_PI / 180.0;
            glVertex2f( par1 + cos( angle ) * par3, par2 + sin( angle ) * par3 );
         }
      glEnd();
      break;

   case OPENGL_ELLIPSE:

      hex_to_Color3f( par5 );
      float x, y;
      for( float angle = 0; angle <= 360; angle += 0.1 )
      {
         x = par1 + par3 * cos( angle );
         y = par2 + par4 * sin( angle );
         glBegin( GL_POINTS );
            glVertex2f( x, y );
         glEnd();
      }
      break;

   case OPENGL_FILLELLIPSE:

      hex_to_Color3f( par5 );
      glBegin( GL_TRIANGLE_FAN );
      glVertex2f( par1, par2 ); // center point
      for( float angle = 0; angle <= 360; angle += 1 )
      {
         float x = par1 + par3 * cos( angle );
         float y = par2 + par4 * sin( angle );
         glVertex3f( x, y, 0.0f );
      }
      glEnd();
      break;

   default:

     return 0;
   }
   return ret;
}

int text_functions( pSeaWolf w, iText type, const char *par1, int par2, int par3, int par4 )
{
   int ret = 1;
   UNUSED( w );
   UNUSED( par1 );
   UNUSED( par2 );
   UNUSED( par3 );
   UNUSED( par4 );

   switch( type )
   {
   case TEXT_FONT:
      break;

   case TEXT_DISPOUTAT:
      break;

   default:
      return 0;
   }
   return ret;
}

int glfw_functions( pSeaWolf w, iGlfw type, int par1 )
{
   int ret = 1;

   switch( type )
   {
   case GLFW_GET_KEY:

      ret = ( w->keyKey == par1 ) == GLFW_PRESS ? T : F;
      break;

   case GLFW_GET_MOUSEBUTTON:

      ret = ( w->mouseButton == par1 ) == GLFW_PRESS ? T : F;
      break;

   case GLFW_WIN_WIDTH:

      ret = w->width;
      break;

   case GLFW_WIN_HEIGHT:

      ret = w->height;
      break;

   case GLFW_WIN_MAXCOL:

      ret = w->width / 9;
      break;

   case GLFW_WIN_MAXROW:

      ret = w->height / 18;
      break;

   case GLFW_WIN_MAXIMIZED:

      glfwMaximizeWindow( w->window );
      ret = w->winMaximized;
      break;

   case GLFW_POLLEVENTS:

      glfwPollEvents();
      break;

   case GLFW_WAITEVENTS:

      glfwWaitEvents();
      break;

   case GLFW_WAITEVENTSTIMEOUT:

      glfwWaitEventsTimeout( ( double ) par1 );
      break;

   default:

      return 0;
   }
   return ret;
}
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

double sw_GetTime( void )
{
   struct timeval tv;
   gettimeofday( &tv, NULL );
   return ( double ) tv.tv_sec + ( double ) tv.tv_usec / 1000000;
}
