/*
 *
 */

#include "seawolf.h"

int main( void )
{
   sw_CreateWindow( 830, 450, "sw_Date" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x323232 );

      sw_End();
      sw_PollEvents();
   }

   printf( "Result: %s\n", sw_CDate() );

   sw_CloseWindow();
   return 0;
}
