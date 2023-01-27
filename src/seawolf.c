/*
 * Copyright 2022 - 2023 Rafał Jopek ( rafaljopek at hotmail com )
 */

#include "seawolf.h"

static pSeaWolf w = NULL;
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
bool sw_CreateWindow( int width, int height, const char *title )
{
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

   return T;
}

bool sw_MainLoop()
{
   bool state;

   w->closeFlag = glfwWindowShouldClose( w->window );
   glfwSetWindowShouldClose( w->window, GLFW_FALSE );

   state = glfwGetWindowAttrib( w->window, GLFW_ICONIFIED ) ;
   if( state == T )        // if window is minimized
   {
      while( state == T )  // stop loop execution
      {
         state = glfwGetWindowAttrib( w->window, GLFW_ICONIFIED );
         glfwWaitEvents(); // wait for events
      }
   }
   return w->closeFlag;
}

bool sw_CloseWindow()
{
   glfwDestroyWindow( w->window );
   free( w );
   glfwTerminate();

   exit( EXIT_SUCCESS );
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
void begin_drawing()
{
   glfwGetFramebufferSize( w->window, &w->width, &w->height );

   glViewport( 0, 0, w->width, w->height );
   hex_to_ClearColor( w->background );
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glDisable( GL_CULL_FACE );
   glDisable( GL_DEPTH_TEST );
   glDisable( GL_BLEND );

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho( 0, w->width, w->height, 0, -1, 1 );
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   glEnable( GL_TEXTURE_2D );
   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void end_drawing()
{
   glfwSwapBuffers( w->window );
}

int opengl_functions( iShape type, void *args )
{
   int ret = 1;

   switch( type )
   {
   // sw_Background( hc )
   case OPENGL_BACKGROUND:
      {
      SW_Color *background = ( SW_Color *)args;

      w->background = background->color;
      }
      break;

   // sw_Point( x, y, hc )
   // sw_Point( x, y, size, hc )
   case OPENGL_POINT:
      {
      SW_Point *point = ( SW_Point *)args;

      hex_to_Color3f( point->hc );
      glPointSize( point->size );
      glBegin( GL_POINTS );
      glVertex2f( point->x, point->y + 1 );
      glEnd();
      }
      break;

   // sw_Lines( x1, y1, x2, y2, hc )
   case OPENGL_LINES:
      {
      SW_Lines *lines = ( SW_Lines *)args;

      hex_to_Color3f( lines->hc );
      glBegin( GL_LINES );
      glVertex2f( lines->x1, lines->y1 );
      glVertex2f( lines->x2, lines->y2 );
      glEnd();
      }
      break;

   // sw_Rect( x1, y1, x2, y2, hc )
   case OPENGL_RECT:
      {
      SW_Rect *rect = ( SW_Rect *)args;

      hex_to_Color3f( rect->hc );
      glBegin( GL_LINE_LOOP );
      glVertex2f( rect->x1, rect->y1 );
      glVertex2f( rect->x2, rect->y1 );
      glVertex2f( rect->x2, rect->y2 );
      glVertex2f( rect->x1, rect->y2 );
      glEnd();
      }
      break;

   // sw_FillRect( x1, y1, x2, y2, hc )
   case OPENGL_FILLRECT:
      {
      SW_FillRect *fillrect = ( SW_FillRect *)args;

      hex_to_Color3f( fillrect->hc );
      glBegin( GL_POLYGON );
      glVertex2f( fillrect->x1, fillrect->y1 );
      glVertex2f( fillrect->x2, fillrect->y1 );
      glVertex2f( fillrect->x2, fillrect->y2 );
      glVertex2f( fillrect->x1, fillrect->y2 );
      glEnd();
      }
      break;

   // sw_Triangle( x1, y1, x2, y2, x3, y3, hc )
   case OPENGL_TRIANGLE:
      {
      SW_Triangle *triangle = ( SW_Triangle *)args;

      hex_to_Color3f( triangle->hc );
      glBegin( GL_LINE_LOOP );
      glVertex2f( triangle->x1, triangle->y1 );
      glVertex2f( triangle->x2, triangle->y2 );
      glVertex2f( triangle->x3, triangle->y3 );
      glEnd();
      }
      break;

   // sw_FillTriangle( x1, y1, x2, y2, x3, y3, hc )
   case OPENGL_FILLTRIANGLE:
      {
      SW_FillTriangle * filltriangle = ( SW_FillTriangle *)args;

      hex_to_Color3f( filltriangle->hc );
      glBegin( GL_TRIANGLES );
      glVertex2f( filltriangle->x1, filltriangle->y1 );
      glVertex2f( filltriangle->x2, filltriangle->y2 );
      glVertex2f( filltriangle->x3, filltriangle->y3 );
      glEnd();
      }
      break;

   // sw_Circle( x, y, radius, hc )
   case OPENGL_CIRCLE:
      {
      SW_Circle *circle = ( SW_Circle *)args;

      hex_to_Color3f( circle->hc );
      glBegin( GL_LINE_LOOP );
         for( int i = 0; i < 360; i++ )
         {
            float angle = i * M_PI / 180.0;
            glVertex2f( circle->x + cos( angle ) * circle->radius, circle->y + sin( angle ) * circle->radius );
         }
      glEnd();
      }
      break;

   // sw_FillCircle( x, y, radius, hc )
   case OPENGL_FILLCIRCLE:
      {
      SW_FillCircle *fillcircle = ( SW_FillCircle *)args;

      hex_to_Color3f( fillcircle->hc );
      glBegin( GL_POLYGON );
         for( int i = 0; i < 360; i++ )
          {
            float angle = i * M_PI / 180.0;
            glVertex2f( fillcircle->x + cos( angle ) * fillcircle->radius, fillcircle->y + sin( angle ) * fillcircle->radius );
         }
      glEnd();
      }
      break;

   // sw_Ellipse( x, y, radius, rotation, hc )
   case OPENGL_ELLIPSE:
      {
      SW_Ellipse *ellipse = ( SW_Ellipse *)args;

      hex_to_Color3f( ellipse->hc );
         float x, y;
         for( float angle = 0; angle <= 360; angle += 0.1 )
         {
            x = ellipse->x + ellipse->radius * cos( angle );
            y = ellipse->y + ellipse->rotation * sin( angle );
            glBegin( GL_POINTS );
               glVertex2f( x, y );
            glEnd();
         }
      }
      break;

   // sw_FillEllipse( x, y, radius, rotation, hc )
   case OPENGL_FILLELLIPSE:
      {
      SW_FillEllipse *fillellipse = ( SW_FillEllipse *)args;

      hex_to_Color3f( fillellipse->hc );
      glBegin( GL_TRIANGLE_FAN );
      glVertex2f( fillellipse->x, fillellipse->y ); // center point
         for( float angle = 0; angle <= 360; angle += 1 )
         {
            float x = fillellipse->x + fillellipse->radius * cos( angle );
            float y = fillellipse->y + fillellipse->rotation * sin( angle );
            glVertex3f( x, y, 0.0f );
         }
      }
      glEnd();
      break;

   default:

     return 0;
   }
   return ret;
}

int text_functions( iText type, void *args )
{
   int ret = 1;
   UNUSED( args );

   switch( type )
   {
   case TEXT_FONT:
      break;

   default:
      return 0;
   }
   return ret;
}

int glfw_functions( iGlfw type, void *args )
{
   int ret = 1;

   switch( type )
   {
      // sw_GetKey( key )
      case GLFW_GET_KEY:
         {
         int *get_key = ( int *)args;

         ret = ( w->keyKey == *get_key ) == GLFW_PRESS ? T : F;
         }
         break;

      // sw_GetMouseButton( button )
      case GLFW_GET_MOUSEBUTTON:
         {
         int *get_mousebutton = ( int *)args;

         ret = ( w->mouseButton == *get_mousebutton ) == GLFW_PRESS ? T : F;
         }
         break;

      // sw_WinWidth()
      case GLFW_WIN_WIDTH:

         ret = w->width;
         break;

      // sw_WinHeight()
      case GLFW_WIN_HEIGHT:

         ret = w->height;
         break;

      // sw_WinMaximized()
      case GLFW_WIN_MAXIMIZED:

         glfwMaximizeWindow( w->window );
         ret = w->winMaximized;
         break;

      // sw_PollEvents()
      case GLFW_POLLEVENTS:

         glfwPollEvents();
         break;

      // sw_WaitEvents()
      case GLFW_WAITEVENTS:

         glfwWaitEvents();
         break;

      // sw_WaitEventsTimeout( timeout )
      case GLFW_WAITEVENTSTIMEOUT:
         {
         double *events_timeout = ( double *)args;

         glfwWaitEventsTimeout( *events_timeout );
         }
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
