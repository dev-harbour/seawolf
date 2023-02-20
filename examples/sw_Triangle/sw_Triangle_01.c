/*
 *
 */

#include "seawolf.h"

int main( void )
{
   double size = 100, rad, angle = 30;
   int x, y, x1, y1, x2, y2, x3, y3;

   sw_CreateWindow( 830, 450, "sw_Triangle" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x162D52 );

         x = sw_WinWidth() / 2;
         y = sw_WinHeight() / 2;

         rad = M_PI / 180 * angle;
         x1 = x + size * cos( rad );
         y1 = y + size * sin( rad );
         x2 = x + size * cos( rad + ( 2 * M_PI / 3 ) );
         y2 = y + size * sin( rad + ( 2 * M_PI / 3 ) );
         x3 = x + size * cos( rad + ( 4 * M_PI / 3 ) );
         y3 = y + size * sin( rad + ( 4 * M_PI / 3 ) );

         sw_Triangle( x1, y1, x2, y2, x3, y3, 0x52162d );

      sw_End();

      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
