/*
 *
 */

#ifndef SEAWOLF_H_
#define SEAWOLF_H_

#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// tokens
#define KEY_UNKNOWN            -1

/* Printable keys */
#define KEY_SPACE              32
#define KEY_APOSTROPHE         39  /* ' */
#define KEY_COMMA              44  /* , */
#define KEY_MINUS              45  /* - */
#define KEY_PERIOD             46  /* . */
#define KEY_SLASH              47  /* / */
#define KEY_0                  48
#define KEY_1                  49
#define KEY_2                  50
#define KEY_3                  51
#define KEY_4                  52
#define KEY_5                  53
#define KEY_6                  54
#define KEY_7                  55
#define KEY_8                  56
#define KEY_9                  57
#define KEY_SEMICOLON          59  /* ; */
#define KEY_EQUAL              61  /* = */
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90
#define KEY_LEFT_BRACKET       91  /* [ */
#define KEY_BACKSLASH          92  /* \ */
#define KEY_RIGHT_BRACKET      93  /* ] */
#define KEY_GRAVE_ACCENT       96  /* ` */
#define KEY_WORLD_1            161 /* non-US #1 */
#define KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE             256
#define KEY_ENTER              257
#define KEY_TAB                258
#define KEY_BACKSPACE          259
#define KEY_INSERT             260
#define KEY_DELETE             261
#define KEY_RIGHT              262
#define KEY_LEFT               263
#define KEY_DOWN               264
#define KEY_UP                 265
#define KEY_PAGE_UP            266
#define KEY_PAGE_DOWN          267
#define KEY_HOME               268
#define KEY_END                269
#define KEY_CAPS_LOCK          280
#define KEY_SCROLL_LOCK        281
#define KEY_NUM_LOCK           282
#define KEY_PRINT_SCREEN       283
#define KEY_PAUSE              284
#define KEY_F1                 290
#define KEY_F2                 291
#define KEY_F3                 292
#define KEY_F4                 293
#define KEY_F5                 294
#define KEY_F6                 295
#define KEY_F7                 296
#define KEY_F8                 297
#define KEY_F9                 298
#define KEY_F10                299
#define KEY_F11                300
#define KEY_F12                301
#define KEY_F13                302
#define KEY_F14                303
#define KEY_F15                304
#define KEY_F16                305
#define KEY_F17                306
#define KEY_F18                307
#define KEY_F19                308
#define KEY_F20                309
#define KEY_F21                310
#define KEY_F22                311
#define KEY_F23                312
#define KEY_F24                313
#define KEY_F25                314
#define KEY_KP_0               320
#define KEY_KP_1               321
#define KEY_KP_2               322
#define KEY_KP_3               323
#define KEY_KP_4               324
#define KEY_KP_5               325
#define KEY_KP_6               326
#define KEY_KP_7               327
#define KEY_KP_8               328
#define KEY_KP_9               329
#define KEY_KP_DECIMAL         330
#define KEY_KP_DIVIDE          331
#define KEY_KP_MULTIPLY        332
#define KEY_KP_SUBTRACT        333
#define KEY_KP_ADD             334
#define KEY_KP_ENTER           335
#define KEY_KP_EQUAL           336
#define KEY_LEFT_SHIFT         340
#define KEY_LEFT_CONTROL       341
#define KEY_LEFT_ALT           342
#define KEY_LEFT_SUPER         343
#define KEY_RIGHT_SHIFT        344
#define KEY_RIGHT_CONTROL      345
#define KEY_RIGHT_ALT          346
#define KEY_RIGHT_SUPER        347
#define KEY_MENU               348

#define KEY_LAST               KEY_MENU

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// types
typedef enum iShape
{
   OPENGL_BACKGROUND,
   OPENGL_POINT,
   OPENGL_POINTSIZE,
   OPENGL_LINES,
   OPENGL_RECT,
   OPENGL_FILLRECT,
   OPENGL_TRIANGLE,
   OPENGL_FILLTRIANGLE,
   OPENGL_CIRCLE,
   OPENGL_FILLCIRCLE,
   OPENGL_ELLIPSE,
   OPENGL_FILLELLIPSE,
} iShape;

typedef enum iText
{
   TEXT_FONT,
   TEXT_DISPOUTAT,
} iText;

typedef enum iGlfw
{
   GLFW_GET_KEY,
   GLFW_GET_MOUSEBUTTON,
   GLFW_WIN_WIDTH,
   GLFW_WIN_HEIGHT,
   GLFW_WIN_MAXCOL,
   GLFW_WIN_MAXROW,
   GLFW_WIN_MAXIMIZED,
   GLFW_POLLEVENTS,
   GLFW_WAITEVENTS,
   GLFW_WAITEVENTSTIMEOUT,
} iGlfw;

typedef enum bool
{
   F = 0,
   T = ( ! 0 )
} bool;

typedef struct _SeaWolf
{
   GLFWwindow      *window;      // handle of the created window
   int              width;       // desired width, in screen coordinates, of the window
   int              height;      // desired height, in screen coordinates
   int              tmp_width;
   int              tmp_height;
   const char      *title;       // initial, UTF-8 encoded window title
   bool             closeFlag;   // returns the value of the close flag of the specified window
   // cursor
   double           cursorX;     // new cursor x-coordinate, relative to the left edge of the content area
   double           cursorY;     // new cursor y-coordinate, relative to the top edge of the content area
   // key
   int              keyKey;      // the keyboard key that was pressed or released
   int              keyScancode; // the system-specific scancode of the key
   int              keyAction;   // GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT. Future releases may add more actions
   int              keyMods;     // bit field describing which modifier keys were held down
   // mouse button
   int              mouseButton; // mouse button that was pressed or released
   int              mouseAction; // one of GLFW_PRESS or GLFW_RELEASE, future releases may add more actions
   int              mouseMods;   // bit field describing which modifier keys were held down
   // window maximized
   int              winMaximized;// GLFW_TRUE if the window was maximized, or GLFW_FALSE if it was restored
   // color
   int              background;

} SeaWolf, *pSeaWolf;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// API functions
pSeaWolf sw_CreateWindow( int width, int height, const char *title );
bool sw_MainLoop( pSeaWolf w );
bool sw_CloseWindow( pSeaWolf w );
//---
void sw_Create( pSeaWolf w, int width, int height, int flags );
//---
void begin_drawing( pSeaWolf w );
void end_drawing( pSeaWolf w );
int opengl_functions();
int text_functions();
int glfw_functions();

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// macros
#define MAX( a, b ) ( ( a ) < ( b ) ? ( b ) : ( a ) )
#define MIN( a, b ) ( ( a ) < ( b ) ? ( a ) : ( b ) )
#define UNUSED( n ) ( ( void )( n ) )
#define LEN( n ) ( sizeof( n ) / sizeof( n )[ 0 ] )

#define sw_Begin( w ) do { begin_drawing( w )
#define sw_End( w ) end_drawing( w ); } while( 0 )
//---
#define sw_Background( w, hexColor )                            opengl_functions( w, OPENGL_BACKGROUND, hexColor )
#define sw_Point( w, x, y, hexColor )                           opengl_functions( w, OPENGL_POINT, x, y, hexColor )
#define sw_PointSize( w, x, y, size, hexColor )                 opengl_functions( w, OPENGL_POINTSIZE, x, y, size, hexColor )
#define sw_Lines( w, x1, y1, x2, y2, hexColor )                 opengl_functions( w, OPENGL_LINES, x1, y1, x2, y2, hexColor )
#define sw_Rect( w, x1, y1, x2, y2, hexColor )                  opengl_functions( w, OPENGL_RECT, x1, y1, x2, y2, hexColor )
#define sw_FillRect( w, x1, y1, x2, y2, hexColor )              opengl_functions( w, OPENGL_FILLRECT, x1, y1, x2, y2, hexColor )
#define sw_Triangle( w, x1, y1, x2, y2, x3, y3, hexColor )      opengl_functions( w, OPENGL_TRIANGLE, x1, y1, x2, y2, x3, y3, hexColor )
#define sw_FillTriangle( w, x1, y1, x2, y2, x3, y3, hexColor )  opengl_functions( w, OPENGL_FILLTRIANGLE, x1, y1, x2, y2, x3, y3, hexColor )
#define sw_Circle( w, x, y, radius, hexColor )                  opengl_functions( w, OPENGL_CIRCLE, x, y, radius, hexColor )
#define sw_FillCircle( w, x, y, radius, hexColor )              opengl_functions( w, OPENGL_FILLCIRCLE, x, y, radius, hexColor )
#define sw_Ellipse( w, x, y, radius, rotation, hexColor )       opengl_functions( w, OPENGL_ELLIPSE, x, y, radius, rotation, hexColor )
#define sw_FillEllipse( w, x, y, radius, rotation, hexColor )   opengl_functions( w, OPENGL_FILLELLIPSE, x, y, radius, rotation, hexColor )
//---
#define sw_OpenFont( w, fileName )                  text_functions( w, TEXT_FONT, fileName )
#define sw_DispOutAt( w, text, col, row, hexColor ) text_functions( w, TEXT_DISPOUTAT, text, col, row, hexColor )
//---
#define sw_GetKey( w, key )                glfw_functions( w, GLFW_GET_KEY, key )
#define sw_GetMouseButton( w, button )     glfw_functions( w, GLFW_GET_MOUSEBUTTON, button )
#define sw_WinWidth( w )                   glfw_functions( w, GLFW_WIN_WIDTH )
#define sw_WinHeight( w )                  glfw_functions( w, GLFW_WIN_HEIGHT )
#define sw_WinMaxCol( w )                  glfw_functions( w, GLFW_WIN_MAXCOL )
#define sw_WinMaxRow( w )                  glfw_functions( w, GLFW_WIN_MAXROW )
#define sw_WinMaximized( w )               glfw_functions( w, GLFW_WIN_MAXIMIZED )
#define sw_PollEvents( w )                 glfw_functions( w, GLFW_POLLEVENTS )
#define sw_WaitEvents( w )                 glfw_functions( w, GLFW_WAITEVENTS )
#define sw_WaitEventsTimeout( w, timeout ) glfw_functions( w, GLFW_WAITEVENTSTIMEOUT, timeout )

#endif /* End SEAWOLF_H_ */
