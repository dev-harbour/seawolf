/*
 *
 */

#include "seawolf.h"

int main( void )
{
   int width = 0, height = 0;
   int x = 0, y = 0, radius = 200;
   int x1, y1, x2, y2;
   double angle1, angle2;

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

         sw_FillCircle( x, y, radius, 0x152026 );

         for( int i = 0; i < 360; i++ )
         {
            angle1 = rand() % 360 * ( M_PI / 180.0 );
            angle2 = rand() % 360 * ( M_PI / 180.0 );

            x1 = x + radius * cos( angle1 );
            y1 = y + radius * sin( angle1 );
            x2 = x + radius * cos( angle2 );
            y2 = y + radius * sin( angle2 );

            sw_Line( x1, y1, x2, y2, 0xFFC107 );
         }

      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
