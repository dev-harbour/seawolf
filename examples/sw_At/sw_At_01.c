/*
 *
 */

#include "seawolf.h"

int main( void )
{
   uint32_t result1 = sw_At( "a",   "abcde" );
   uint32_t result2 = sw_At( "bcd", "abcde" );
   uint32_t result3 = sw_At( "a",   "bcde" );

   sw_CreateWindow( 830, 450, "sw_At" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x323232 );

      sw_End();
      sw_PollEvents();
   }

   printf( "at result1 - %d \n", result1 ); // Result: 1
   printf( "at result2 - %d \n", result2 ); // Result: 2
   printf( "at result3 - %d \n", result3 ); // Result: 0

   sw_CloseWindow();
   return 0;
}
