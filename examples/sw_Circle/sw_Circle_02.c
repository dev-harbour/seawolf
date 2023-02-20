/*
 *
 */

#include "seawolf.h"

int main( void )
{
   int width = 0, height = 0;
   int x, y, radius = 200;
   int x1, y1, x2, y2;

   srand( time( NULL ) );

   sw_CreateWindow( 830, 450, "sw_FillCircle" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         if( width != sw_WinWidth() || height != sw_WinHeight() )
         {
            width = sw_WinWidth();
            height = sw_WinHeight();
            x = width / 2;
            y = height / 2;
         }

         sw_Background( 0x0c1215 );

         x = sw_WinWidth() / 2;
         y = sw_WinHeight() / 2;

         sw_FillCircle( x, y, radius, 0x152026 );

         for( int i = 0; i < 360; i++ )
         {
            x1 = x + cos( i * M_PI / 180 ) * radius;
            y1 = y + sin( i * M_PI / 180 ) * radius;
            x2 = x + cos( ( i + rand() % 20 - 10 ) * M_PI / 180 ) * radius;
            y2 = y + sin( ( i + rand() % 20 - 10 ) * M_PI / 180 ) * radius;
            sw_Line( x1, y1, x2, y2, 0xf1f1f1 );
         }

      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
