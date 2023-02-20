/*
 *
 */

#include "seawolf.h"

int main( void )
{
   int x, y, radius = 200;
   int j, i, x1, y1, x2, y2, x3, y3;

   sw_CreateWindow( 830, 450, "sw_Triangle" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         x = sw_WinWidth() / 2;
         y = sw_WinHeight() / 2;

         sw_Background( 0x162D52 );

         for( j = 0; j < 20; j++ )
         {
            for( i = 0; i < 3; i++ )
            {
               x1 = x + cos( i * 2 * M_PI / 3 ) * ( radius - j * 10 );
               y1 = y + sin( i * 2 * M_PI / 3 ) * ( radius - j * 10 );
               x2 = x + cos( ( i + 1 ) * 2 * M_PI / 3 ) * ( radius - j * 10 );
               y2 = y + sin( ( i + 1 ) * 2 * M_PI / 3 ) * ( radius - j * 10 );
               x3 = x;
               y3 = y;
               sw_Triangle( x1, y1, x2, y2, x3, y3, 0x523b16 );
            }
         }

      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
