/*
 *
 */

#include "seawolf.h"

int main( void )
{
   const char *text = "sw_Rect";
   int x1, y1, x2, y2;
   uint8_t i;
   int n = 8, radius = 200;
   uint32_t colors[ 5 ] = { 0xFFA07A, 0x6B8E23, 0x4682B4, 0x9400D3, 0xFFFF00 };

   sw_CreateWindow( 830, 450, text );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         x2 = sw_WinWidth() / 2;
         y2 = sw_WinHeight() / 2;

         sw_Background( 0x2a442e );

         for( i = 0; i < n; i++ )
         {
            x1 = x2 - radius + i * ( radius / ( n - 1 ) );
            y1 = y2 - radius + i * ( radius / ( n - 1 ) );
            sw_Rect( x1, y1, x1 + radius * 2 / n, y1 + radius * 2 / n, colors[ i % 5 ] );
         }

      sw_End();
      sw_WaitEvents();
   }

   sw_CloseWindow();
   return 0;
}
