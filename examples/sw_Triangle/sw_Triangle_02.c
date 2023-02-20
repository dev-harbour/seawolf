/*
 *
 */

/*
 *
 */

#include "seawolf.h"

int main( void )
{
   int x, y, i, radius = 150;
   double angle, rad, x1, y1, x2, y2, x3, y3;

   sw_CreateWindow( 830, 450, "sw_Triangle" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

     x = sw_WinWidth() / 2;
     y = sw_WinHeight() / 2;

     sw_Background( 0x162D52 );

      for( i = 0; i < 44; i++ )
      {
         angle = i * 8;
         rad = M_PI / 180 * angle;
         x1 = x + ( radius * cos( rad ) );
         y1 = y + ( radius * sin( rad ) );
         x2 = x + ( radius * cos( rad + ( 2 * M_PI / 3 ) ) );
         y2 = y + ( radius * sin( rad + ( 2 * M_PI / 3 ) ) );
         x3 = x + ( radius * cos( rad + ( 4 * M_PI / 3 ) ) );
         y3 = y + ( radius * sin( rad + ( 4 * M_PI / 3 ) ) );
         if (i % 2 == 0)
         {
            sw_Triangle( x1, y1, x2, y2, x3, y3, 0x52162d );
         }
         else
         {
            sw_Triangle( x1, y1, x2, y2, x3, y3, 0x2d5216 );
         }
      }
      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
