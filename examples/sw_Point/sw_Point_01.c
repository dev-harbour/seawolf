/*
 *
 */

#include "seawolf.h"

int main( void )
{
   float x = 0, y = 0;
   uint32_t hc;

   sw_CreateWindow( 830, 450, "sw_Point" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x000000 );

         for( int i = 0; i < 1000; i++ )
         {
            x = ( float )rand() / RAND_MAX * sw_WinWidth();
            y = ( float )rand() / RAND_MAX * sw_WinHeight();
            hc = rand() | 0xff0000;
            sw_Point( x, y, hc );
         }

      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
