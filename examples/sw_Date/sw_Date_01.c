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

   printf( "Result: %s\n", sw_Date( "" ) );              // Result: 31.01.2023
   printf( "Result: %s\n", sw_Date( "%d.%m.%y" ) );      // Result: 31.01.23
   printf( "Result: %s\n", sw_Date("%invalid_format%")); // Result: Invalid format

   sw_CloseWindow();
   return 0;
}
