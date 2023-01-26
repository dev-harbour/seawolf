/*
 *
 */

#include "seawolf.h"

#define POINTS_COUNT 100

int main( void )
{
   float x, y, size;
   uint32_t hc;

   sw_CreateWindow( 830, 450, "sw_Point" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x323232 );

         // Draw randomly placed points
         for( int i = 0; i < POINTS_COUNT; i++ )
         {
            x = ( float )rand() / RAND_MAX * sw_WinWidth();
            y = ( float )rand() / RAND_MAX * sw_WinHeight();
            size = (float)rand() / RAND_MAX * 10 + 1;
            hc = rand() % 0xffffff;

            // Animate the movement of points towards the center of the screen
            x += ( sw_WinWidth() / 2 - x ) / 100;
            y += ( sw_WinHeight() / 2 - y ) / 100;
            size += ( 5 - size ) / 100;
            hc += ( 0xffffff / 2 - hc )  / 100;

            sw_PointSize( x, y, size, hc );
         }

      sw_End();
      glfwPollEvents();
   }
   sw_CloseWindow();
   return 0;
}
