/*
 *
 */


#include "seawolf.h"

typedef struct {
  unsigned char r, g, b;
} Color;

Color ColorGradient(Color start, Color end, float progress) {
  Color result;
  result.r = start.r + (end.r - start.r) * progress;
  result.g = start.g + (end.g - start.g) * progress;
  result.b = start.b + (end.b - start.b) * progress;
  return result;
}

int main( void )
{
   int x, y, radius = 200;
   int j, i, x1, y1, x2, y2, x3, y3;
   Color start = {0x52, 0x3b, 0x16};
   Color end = {0xff, 0xff, 0xff};

   sw_CreateWindow( 830, 450, "sw_Triangle" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         x = sw_WinWidth() / 2;
         y = sw_WinHeight() / 2;

         sw_Background( 0x162D52 );

     for( j = 0; j < 20; j++ )
     {
        float progress = j / 20.0;
        Color color = ColorGradient(start, end, progress);
        for( i = 0; i < 3; i++ )
        {
           x1 = x + cos( i * 2 * M_PI / 3 ) * ( radius - j * 10 );
           y1 = y + sin( i * 2 * M_PI / 3 ) * ( radius - j * 10 );
           x2 = x + cos( ( i + 1 ) * 2 * M_PI / 3 ) * ( radius - j * 10 );
           y2 = y + sin( ( i + 1 ) * 2 * M_PI / 3 ) * ( radius - j * 10 );
           x3 = x;
           y3 = y;
           sw_Triangle( x1, y1, x2, y2, x3, y3, (color.r << 16) | (color.g << 8) | color.b );
        }
     }
      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
