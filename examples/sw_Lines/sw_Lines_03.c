/*
 *
 */

#include "seawolf.h"

int main( void )
{
   const char *text = "sw_Lines";
   int x1, y1, x2, y2;
   uint8_t i;
   int n = 46, radius = 100;
   uint32_t ticks;
   uint8_t red, green, blue;
   uint32_t color;

   sw_CreateWindow( 830, 450, text );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         x2 = sw_WinWidth() / 2;
         y2 = sw_WinHeight() / 2;

         sw_Background( 0x516C4B );

         ticks = sw_GetTicks();
printf( "ticks = %i \n", ticks );
         for( i = 0; i < 2 * n; i++ )
         {
            x1 = sin(        i * M_PI / n ) * radius * 2 + x2;
            y1 = cos( M_PI + i * M_PI / n ) * radius * 2 + y2;

            red = 128 + 127 * sin( ( ticks + i * 1000 ) / 1000.0 );
            green = 128;
            blue = 128 - 127 * sin( ( ticks + i * 1000 ) / 1000.0 );

            color = sw_RGBToHex( red, green, blue );

            sw_Lines( x1, y1, x2, y2, color );
         }

      sw_End();
      sw_PollEvents();
   }
   sw_CloseWindow();
   return 0;
}
