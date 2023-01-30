/*
 * Copyright 2022 - 2023 Rafał Jopek ( rafaljopek at hotmail com )
 */

#ifndef SEAWOLF_H_
#define SEAWOLF_H_

#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <gc/gc.h>

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
   TEXT_OPEN_FONT,
   TEXT_TEXT,
   TEXT_WIDTH,
   TEXT_HEIGHT,
} iText;

typedef enum iGlfw
{
   GLFW_SET_WIN_OPACITY,
   GLFW_GET_KEY,
   GLFW_GET_MOUSEBUTTON,
   GLFW_WIN_WIDTH,
   GLFW_WIN_HEIGHT,
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

typedef struct _SW_Color
{
   uint32_t color;
} SW_Color;

typedef struct _SW_Point
{
   float x;
   float y;
   float size;
   uint32_t hc;
} SW_Point;

typedef struct _SW_Lines
{
   float x1;
   float y1;
   float x2;
   float y2;
   uint32_t hc;
} SW_Lines;

typedef struct _SW_Rect
{
   float x1;
   float y1;
   float x2;
   float y2;
   uint32_t hc;
} SW_Rect;

typedef struct _SW_FillRect
{
   float x1;
   float y1;
   float x2;
   float y2;
   uint32_t hc;
} SW_FillRect;

typedef struct _SW_Triangle
{
   float x1;
   float y1;
   float x2;
   float y2;
   float x3;
   float y3;
   uint32_t hc;
} SW_Triangle;

typedef struct _SW_FillTriangle
{
   float x1;
   float y1;
   float x2;
   float y2;
   float x3;
   float y3;
   uint32_t hc;
} SW_FillTriangle;

typedef struct _SW_Circle
{
   float x;
   float y;
   float radius;
   uint32_t hc;
} SW_Circle;

typedef struct _SW_FillCircle
{
   float x;
   float y;
   float radius;
   uint32_t hc;
} SW_FillCircle;

typedef struct _SW_Ellipse
{
   float x;
   float y;
   float radius;
   float rotation;
   uint32_t hc;
} SW_Ellipse;

typedef struct _SW_FillEllipse
{
   float x;
   float y;
   float radius;
   float rotation;
   uint32_t hc;
} SW_FillEllipse;

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

} SeaWolf;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// API functions
bool sw_CreateWindow( int width, int height, const char *title );
bool sw_MainLoop();
bool sw_CloseWindow();
void begin_drawing();
void end_drawing();
int opengl_functions( iShape type, void *args );
int text_functions( iText type, void *args );
int glfw_functions( iGlfw type, void *args );
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*                                  Strings                                  */
const char *sw_Left( const char *str, int count );
const char *sw_MemoRead( const char *filePath );
const char *sw_Right( const char *str, int count );
const char *sw_SubStr( const char *str, int start, int count );


bool sw_IsMouseInCircle( double circleX, double circleY, double radius, double cursorX, double cursorY );
bool sw_IsMouseInEllipse( double ellipseX, double ellipseY, double radiusX, double radiusY, double cursorX, double cursorY );
bool sw_IsMouseInHexagon( double hexagonX, double hexagonY, double radius, double cursorX, double cursorY );
bool sw_IsMouseInRect( double rectX1, double rectY1, double rectWidth, double rectHeight, double cursorX, double cursorY );
bool sw_IsMouseInRoundedRect( double rectX1, double rectY1, double rectWidth, double rectHeight, double radius, double cursorX, double cursorY );
bool sw_IsMouseInTriangle( double x1, double y1, double x2, double y2, double x3, double y3, double cursorX, double cursorY );

//---
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// macros
#define MAX( a, b ) ( ( a ) < ( b ) ? ( b ) : ( a ) )
#define MIN( a, b ) ( ( a ) < ( b ) ? ( a ) : ( b ) )
#define UNUSED( n ) ( ( void )( n ) )
#define LEN( n ) ( sizeof( n ) / sizeof( n )[ 0 ] )

#define sw_Begin() do { begin_drawing()
#define sw_End() end_drawing(); } while( 0 )
//---
#define sw_Background( hc ) \
do { \
   SW_Color background = { hc }; \
   opengl_functions( OPENGL_BACKGROUND, &background ); \
} while( 0 )

#define sw_Point( x, y, hc ) \
do { \
   SW_Point point = { x, y, 0, hc }; \
   opengl_functions( OPENGL_POINT, &point ); \
} while( 0 )

#define sw_PointSize( x, y, size, hc ) \
do { \
   SW_Point point = { x, y, size, hc }; \
   opengl_functions( OPENGL_POINT, &point ); \
} while( 0 )

#define sw_Lines( x1, y1, x2, y2, hc ) \
do { \
   SW_Lines lines = { x1, y1, x2, y2, hc }; \
   opengl_functions( OPENGL_LINES, &lines ); \
} while( 0 )

#define sw_Rect( x1, y1, x2, y2, hc ) \
do { \
   SW_Rect rect = { x1, y1, x2, y2, hc }; \
   opengl_functions( OPENGL_RECT, &rect ); \
} while( 0 )

#define sw_FillRect( x1, y1, x2, y2, hc ) \
do { \
   SW_FillRect fillrect = { x1, y1, x2, y2, hc }; \
   opengl_functions( OPENGL_FILLRECT, &fillrect ); \
} while( 0 )

#define sw_Triangle( x1, y1, x2, y2, x3, y3, hc ) \
do { \
   SW_Triangle triangle = { x1, y1, x2, y2, x3, y3, hc }; \
   opengl_functions( OPENGL_TRIANGLE, &triangle ); \
} while( 0 )

#define sw_FillTriangle( x1, y1, x2, y2, x3, y3, hc ) \
do { \
   SW_FillTriangle filltriangle = { x1, y1, x2, y2, x3, y3, hc }; \
   opengl_functions( OPENGL_FILLTRIANGLE, &filltriangle ); \
} while( 0 )

#define sw_Circle( x, y, radius, hc ) \
do { \
   SW_Circle circle = { x, y, radius, hc }; \
   opengl_functions( OPENGL_CIRCLE, &circle ); \
} while( 0 )

#define sw_FillCircle( x, y, radius, hc ) \
do { \
   SW_FillCircle fillcircle = { x, y, radius, hc }; \
   opengl_functions( OPENGL_FILLCIRCLE, &fillcircle ); \
} while( 0 )

#define sw_Ellipse( x, y, radius, rotation, hc ) \
do { \
   SW_Ellipse ellipse = { x, y, radius, rotation, hc }; \
   opengl_functions( OPENGL_ELLIPSE, &ellipse ); \
} while( 0 )

#define sw_FillEllipse( x, y, radius, rotation, hc ) \
do { \
   SW_FillEllipse fillellipse = { x, y, radius, rotation, hc }; \
   opengl_functions( OPENGL_FILLELLIPSE, &fillellipse ); \
} while( 0 )

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
//--- Text

//TODO:

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
//--- GLFW

#define sw_SetWinOpacity( opacity ) \
({ \
   float set_win_opacity = opacity; \
   glfw_functions( GLFW_SET_WIN_OPACITY, &set_win_opacity ); \
})

#define sw_GetKey( key ) \
({ \
   int get_key = key; \
   glfw_functions( GLFW_GET_KEY, &get_key ); \
})

#define sw_GetMouseButton( button ) \
({ \
   int get_mousebutton = button; \
   glfw_functions( GLFW_GET_MOUSEBUTTON, &get_mousebutton ); \
})

#define sw_WinWidth()     glfw_functions( GLFW_WIN_WIDTH, NULL )
#define sw_WinHeight()    glfw_functions( GLFW_WIN_HEIGHT, NULL )
#define sw_WinMaximized() glfw_functions( GLFW_WIN_MAXIMIZED, NULL )
#define sw_PollEvents()   glfw_functions( GLFW_POLLEVENTS, NULL )
#define sw_WaitEvents()   glfw_functions( GLFW_WAITEVENTS, NULL )

#define sw_WaitEventsTimeout( timeout ) \
({ \
   double events_timeout = timeout; \
   glfw_functions( GLFW_WAITEVENTSTIMEOUT, &events_timeout ); \
})

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
double sw_GetTime( void );
#endif /* End SEAWOLF_H_ */
