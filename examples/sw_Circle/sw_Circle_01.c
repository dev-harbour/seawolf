/*
 *
 */

#include "seawolf.h"

int main( void )
{
   int x, y, w, h, i, radius = 100;

   sw_CreateWindow( 830, 450, "sw_Circle" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         w = sw_WinWidth() / 2;
         h = sw_WinHeight() / 2;

         sw_Background( 0x006994 );

         for( i = 0; i < 44; i++ )
         {
            x = sin( i ) * radius + w;
            y = cos( i ) * radius + h;
            sw_Circle( x, y, radius, 0x323232 );
         }

      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
