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

   sw_CreateWindow( 830, 450, text );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         x2 = sw_WinWidth() / 2;
         y2 = sw_WinHeight() / 2;

         sw_Background( 0x516C4B );

         for( i = 0; i < 2 * n; i++ )
         {
            x1 = sin(        i * M_PI / n ) * radius * 2 + x2;
            y1 = cos( M_PI + i * M_PI / n ) * radius * 2 + y2;

            if( x1 < x2 )
            {
               sw_Lines( x1, y1, x2, y2, 0xFF0000 );
            }
            else
            {
               sw_Lines( x1, y1, x2, y2, 0x00FF00 );
            }
         }

      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
