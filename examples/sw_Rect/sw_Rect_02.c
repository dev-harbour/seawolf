/*
 *
 */

#include "seawolf.h"

int main( void )
{
   double size = 100, angle, rad;
   int x, y, x1, y1, x2, y2, x3, y3, x4, y4;
   uint32_t color;

   sw_CreateWindow( 830, 450, "sw_Rect" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

      sw_Background( 0x2a442e );

      x = sw_WinWidth() / 2;
      y = sw_WinHeight() / 2;

      for( int i = 0; i < 20; i++ )
      {
         angle = i * 18;
         rad = M_PI / 180 * angle;
         x1 = x + ( size * cos( rad ) );
         y1 = y + ( size * sin( rad ) );
         x2 = x + ( size * cos( rad + ( M_PI / 2 ) ) );
         y2 = y + ( size * sin( rad + ( M_PI / 2 ) ) );
         x3 = x + ( size * cos( rad + M_PI ) );
         y3 = y + ( size * sin( rad + M_PI ) );
         x4 = x + ( size * cos( rad + ( 3 * M_PI / 2 ) ) );
         y4 = y + ( size * sin( rad + ( 3 * M_PI / 2 ) ) );
         color = i * 0x111111;
         sw_Rect( x1, y1, x2, y2, color );
         sw_Rect( x2, y2, x3, y3, color );
         sw_Rect( x3, y3, x4, y4, color );
         sw_Rect( x4, y4, x1, y1, color );
      }

      sw_End();
      sw_WaitEvents();
   }

   sw_CloseWindow();
   return 0;
}
