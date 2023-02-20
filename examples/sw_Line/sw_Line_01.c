/*
 *
 */

#include "seawolf.h"

int main( void )
{
   const char *text = "sw_Line";
   int x1, y1, x2, y2;
   uint8_t i;
   int n = 46, radius = 100;
   uint32_t colors[] = { 0x003F5C, 0x58508D, 0xBC5090, 0xFF6361, 0xFFA600 };

   sw_CreateWindow( 830, 450, text );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         x2 = sw_WinWidth() / 2;
         y2 = sw_WinHeight() / 2;

         sw_Background( 0x516c4b );

         for( i = 0; i < 2 * n; i++ )
         {
            x1 = sin(        i * M_PI / n ) * radius * 2 + x2;
            y1 = cos( M_PI + i * M_PI / n ) * radius * 2 + y2;
            sw_Line( x1, y1, x2, y2, colors[ i % 5 ] );
         }

      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
