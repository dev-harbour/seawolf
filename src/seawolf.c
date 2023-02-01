/*
 * Copyright 2022 - 2023 Rafał Jopek ( rafaljopek at hotmail com )
 */

#define STB_TRUETYPE_IMPLEMENTATION
#include "seawolf.h"

static SeaWolf *w = NULL;
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// static functions
static void cursor_position_callback( GLFWwindow *window, double x, double y )
{
   SeaWolf *s_w = glfwGetWindowUserPointer( window );

   s_w->cursorX = x;
   s_w->cursorY = y;
}

static void key_callback( GLFWwindow *window, int key, int scancode, int action, int mods )
{
   SeaWolf *s_w = glfwGetWindowUserPointer( window );

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
   SeaWolf *s_w = glfwGetWindowUserPointer( window );

   s_w->mouseButton = button;
   s_w->mouseAction = action;
   s_w->mouseMods   = mods;
}

static void window_maximize_callback( GLFWwindow *window, int maximized )
{
   SeaWolf *s_w = glfwGetWindowUserPointer( window );

   s_w->winMaximized = maximized;
}

static void window_size_callback( GLFWwindow *window, int width, int height )
{
   SeaWolf *s_w = glfwGetWindowUserPointer( window );

   s_w->width  = width;
   s_w->height = height;
}

static void hex_to_ClearColor( uint32_t hexColor )
{
   if( ( hexColor <= 0xffffff) )
   {
      double r, g, b;
      r = ( ( hexColor >> 16 ) & 0xFF ) / 255.0;
      g = ( ( hexColor >> 8 )  & 0xFF ) / 255.0;
      b = (   hexColor         & 0xFF ) / 255.0;
      glClearColor( r, g, b, 1.0 );
   }
   else if( ( hexColor <= 0xffffffff ) )
   {
      double r, g, b, a;
      r = ( ( hexColor >> 24 ) & 0xFF ) / 255.0;
      g = ( ( hexColor >> 16 ) & 0xFF ) / 255.0;
      b = ( ( hexColor >> 8 )  & 0xFF ) / 255.0;
      a = ( hexColor & 0xFF )           / 255.0;
      glClearColor( r, g, b, a );
   }
   else
   {
      printf( "Invalid hex value passed \n" );
   }
}

static void hex_to_Colorf( uint32_t hexColor )
{
   if( ( hexColor <= 0xffffff) )
   {
      double r, g, b;
      r = ( ( hexColor >> 16 ) & 0xFF ) / 255.0;
      g = ( ( hexColor >> 8 )  & 0xFF ) / 255.0;
      b = (   hexColor         & 0xFF ) / 255.0;
      glColor3f( r, g, b );
   }
   else if( ( hexColor <= 0xffffffff ) )
   {
      double r, g, b, a;
      r = ( ( hexColor >> 24 ) & 0xFF ) / 255.0;
      g = ( ( hexColor >> 16 ) & 0xFF ) / 255.0;
      b = ( ( hexColor >> 8 )  & 0xFF ) / 255.0;
      a = ( hexColor & 0xFF )           / 255.0;
      glColor4f( r, g, b, a );
   }
   else
   {
      printf( "Invalid hex value passed \n" );
   }
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
   w->setDateFormat = "%d.%m.%y";

   glfwWindowHint( GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE );
   glfwWindowHint( GLFW_ALPHA_BITS, 8 );

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

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
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

      hex_to_Colorf( point->hc );
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

      hex_to_Colorf( lines->hc );
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

      hex_to_Colorf( rect->hc );
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

      hex_to_Colorf( fillrect->hc );
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

      hex_to_Colorf( triangle->hc );
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

      hex_to_Colorf( filltriangle->hc );
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

      hex_to_Colorf( circle->hc );
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

      hex_to_Colorf( fillcircle->hc );
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

      hex_to_Colorf( ellipse->hc );
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

      hex_to_Colorf( fillellipse->hc );
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

uint32_t text_functions( iText type, void *args )
{
   int ret = 1;
   UNUSED( args );

   switch( type )
   {
      // sw_OpenFont( filepath )
      case TEXT_OPEN_FONT:
         {
         const char *filepath = ( const char *)args;

         uint8_t ttf_buffer[ 1 << 20 ];
         uint8_t temp_bitmap[ w->width * w->height ];
         stbtt_bakedchar cdata[ 256 ];

         FILE *file = fopen( filepath, "rb" );
         if( file == NULL )
         {
            printf( "Error opening file \n" );
            break;
         }

         size_t bytesRead = fread( ttf_buffer, 1, 1 << 20, file );
         if( bytesRead != 1 << 20 )
         {
            printf( "Error reading file \n" );
            break;
         }
         fclose( file );

         stbtt_BakeFontBitmap( ttf_buffer, 0, 0.0, temp_bitmap, w->width, w->height, 0, 255, cdata );

         glGenTextures( 1, &w->texture );
         glBindTexture( GL_TEXTURE_2D, w->texture );
         glTexImage2D( GL_TEXTURE_2D, 0, GL_ALPHA, w->width, w->height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap );
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

         return w->texture;
         }
         break;

      // sw_Text( x, y, text, size, hc )
      case TEXT_TEXT:
         break;

      // sw_TextWidth()
      case TEXT_WIDTH:
         break;

      // sw_TextHeight()
      case TEXT_HEIGHT:
         break;

      default:
         return 0;
   }
   return ret;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
int glfw_functions( iGlfw type, void *args )
{
   int ret = 1;

   switch( type )
   {
      // sw_SetWinOpacity( opacity )
      case GLFW_SET_WIN_OPACITY:
         {
         float *opacity = ( float *)args;

            if( *opacity >= 0.0f && *opacity <= 1.0f )
            {
               glfwSetWindowOpacity( w->window, *opacity );
            }
            else
            {
               printf("Invalid value of opacity : %f \n", *opacity );
            }
         }
         break;

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
/*                                Date & Time                                */
const char *sw_CDate()
{
   time_t currentTime = time( NULL );
   struct tm *localTime = localtime( &currentTime );
   static char result[ 256 ];

   size_t len = strftime( result, sizeof( result ), w->setDateFormat, localTime );
   if( len == 0 )
   {
      return "Invalid format";
   }

   return result;
}

bool sw_SetDateFormat( const char *format )
{

   if( format )
   {
      w->setDateFormat = format;
      return T;
   }

   return F;
}
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*                                  Strings                                  */
uint32_t sw_At( const char *search, const char *target )
{
   char *occurrence = strstr( target, search );
   if( occurrence == NULL )
   {
      return 0;
   }

   return (uint32_t)( occurrence - target + 1 );
}

const char *sw_Left( const char *str, int count )
{
   int len = strlen( str );

   if( count <= 0 )
   {
      return GC_STRDUP("");
   }

   if( count >= len )
   {
      return GC_STRDUP( str );
   }

   char *subString = GC_MALLOC( count + 1 );
   strncpy( subString, str, count );
   subString[ count ] = '\0';

   return subString;
}

const char *sw_MemoRead( const char *filePath )
{
   FILE *file = fopen( filePath, "rb" );
   if( file == NULL )
   {
      return GC_STRDUP("");
   }

   fseek( file, 0, SEEK_END );
   long fileSize = ftell( file );
   fseek( file, 0, SEEK_SET );

   char *buffer = GC_MALLOC( fileSize + 1 );
   if( buffer == NULL )
   {
      fclose( file );
      return GC_STRDUP("");
   }

   long int itemsRead = fread( buffer, 1, fileSize, file );
   if( itemsRead != fileSize )
   {
      fprintf( stderr, "Error: Only %ld bytes read, expected %ld\n", itemsRead, fileSize );
      return GC_STRDUP("");
   }

   fclose( file );
   buffer[ fileSize ] = '\0';

   return buffer;
}

uint32_t sw_RAt( const char *search, const char *target )
{
   int targetLen = strlen( target );
   int searchLen = strlen( search );

   for( int i = targetLen - searchLen; i >= 0; i-- )
   {
      if( strncmp( &target[ i ], search, searchLen ) == 0 )
      {
         return (uint32_t)( i + 1 );
      }
   }

   return 0;
}

const char *sw_Right( const char *str, int count )
{
   int len = strlen( str );

   if( count <= 0 )
   {
      return GC_STRDUP("");
   }

   if( count >= len )
   {
      return GC_STRDUP( str );
   }

   char *subString = GC_MALLOC( count + 1 );
   strncpy( subString, str + len - count, count );
   subString[ count ] = '\0';

   return subString;
}

const char *sw_SubStr( const char *str, int start, int count )
{
   int nSize = strlen( str );

   if( start > 0 )
   {
      if( --start > nSize )
         count = 0;
      }

      if( count > 0 )
      {
         if( start < 0 )
         {
            start = nSize + start;
         }
         if( start < 0 )
         {
            start = 0;
         }
         if( start + count > nSize )
         {
            count = nSize - start;
         }
      }
   else
   {
      if( start < 0 )
      {
         start = nSize + start;
      }
      if( start < 0 )
      {
         start = 0;
      }
      count = nSize - start;
   }

   char *subString = GC_MALLOC( count + 1 );
   strncpy( subString, str + start, count );
   subString[ count ] = '\0';

   return subString;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

bool sw_IsMouseInCircle( double circleX, double circleY, double radius, double cursorX, double cursorY )
{
   double distance = sqrt( ( cursorX - circleX ) * ( cursorX - circleX ) + ( cursorY - circleY ) * ( cursorY - circleY ) );
   if( distance <= radius )
      return T;
   else
   return F;
}

bool sw_IsMouseInEllipse( double ellipseX, double ellipseY, double radiusX, double radiusY, double cursorX, double cursorY )
{
   if( ( pow( ( cursorX - ellipseX ), 2 ) / pow( radiusX, 2 ) ) + ( pow( ( cursorY - ellipseY ), 2 ) / pow( radiusY, 2 ) ) <= 1 )
      return T;
   else
   return F;
}

bool sw_IsMouseInHexagon( double hexagonX, double hexagonY, double radius, double cursorX, double cursorY )
{
   double distance = sqrt( pow( cursorX - hexagonX, 2 ) + pow( cursorY - hexagonY, 2 ) );
   if( distance <= radius )
      return T;
   else
   return F;
}

bool sw_IsMouseInRect( double rectX1, double rectY1, double rectWidth, double rectHeight, double cursorX, double cursorY )
{
   return cursorX >= rectX1 && cursorY >= rectY1 && cursorX <= rectX1 + rectWidth && cursorY <= rectY1 + rectHeight;
}

static int Corner( double dx, double dy, double r )
{
   return( dx < 0 && dy < 0 && dx * dx + dy * dy > r * r );
}

bool sw_IsMouseInRoundedRect( double rectX1, double rectY1, double rectWidth, double rectHeight, double radius, double cursorX, double cursorY )
{
   int is_outside = ( cursorX < rectX1 ) ||
                    ( cursorX > rectX1 + rectWidth ) ||
                    ( cursorY < rectY1 ) ||
                    ( cursorY > rectY1 + rectHeight ) ||
                    ( Corner( cursorX - rectX1 - radius, cursorY - rectY1 - radius, radius ) ) ||
                    ( Corner( cursorX - rectX1 - radius, rectY1 + rectHeight - radius - cursorY, radius ) ) ||
                    ( Corner( rectX1 + rectWidth - radius - cursorX, rectY1 + rectHeight - radius - cursorY, radius ) ) ||
                    ( Corner( rectX1 + rectWidth - radius - cursorX, cursorY - rectY1 - radius, radius ) );

   if( is_outside )
      return 0;
   else
      return 1;
}

bool sw_IsMouseInTriangle( double x1, double y1, double x2, double y2, double x3, double y3, double cursorX, double cursorY )
{
   double s = y1 * x3 - x1 * y3 + ( y3 - y1 ) * cursorX + ( x1 - x3 ) * cursorY;
   double t = x1 * y2 - y1 * x2 + ( y1 - y2 ) * cursorX + ( x2 - x1 ) * cursorY;

   if( ( s < 0 ) != ( t < 0 ) )
      return 0;
   double a = -y2 * x3 + y1 * ( x3 - x2 ) + x1 * ( y2 - y3 ) + x2 * y3;
   if( a < 0.0 )
   {
      s = -s;
      t = -t;
      a = -a;
   }
   return s > 0 && t > 0 && ( s + t ) < a;
}

/*
 * The sw_GetTime function is a function that returns time in seconds with microsecond accuracy.
 * This is done using the timeval structure and the gettimeofday function, which retrieves the current time in seconds
 * and microseconds since the beginning of epoch (1970-01-01 00:00:00 UTC). The function returns a double value consisting
 * of the sum of seconds and microseconds divided by 1,000,000.
 */
double sw_GetTime( void )
{
   struct timeval tv;
   gettimeofday( &tv, NULL );
   return ( double ) tv.tv_sec + ( double ) tv.tv_usec / 1000000;
}

/*
 * The `sw_Sleep` function is a function that allows you to stop the program for a period of time specified in milliseconds.
 * This is a Linux and Windows implementation of the "sleep" function that uses the nanosleep() system call to implement the delay.
 * The argument of the function is the number of milliseconds for which we want to stop the program.
 */
void sw_Sleep( unsigned int milliseconds )
{
   struct timespec req;
   req.tv_sec = milliseconds / 1000;
   req.tv_nsec = ( milliseconds % 1000 ) * 1000000;
   nanosleep( &req, NULL );
}

