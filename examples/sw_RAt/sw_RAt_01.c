/*
 *
 */

#include "seawolf.h"

int main( void )
{
   uint32_t result = sw_RAt( "c", "abcdef" );

   sw_CreateWindow( 830, 450, "sw_RAt" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x323232 );

      sw_End();
      sw_PollEvents();
   }

   printf( "Result: %u \n", result ); // Result: 3

   sw_CloseWindow();
   return 0;
}
