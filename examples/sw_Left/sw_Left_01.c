/*
 *
 */

#include "seawolf.h"

int main( void )
{
   const char *name = "Marek Skalewski";
   const char *substr1 = sw_Left( name,  5 );
   const char *substr2 = sw_Left( name,  0 );
   const char *substr3 = sw_Left( name, -3 );
   const char *substr4 = sw_Left( name, 20 );

   sw_CreateWindow( 830, 450, "sw_Left" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x323232 );

      sw_End();
      sw_PollEvents();
   }

   printf(" substr1: %s\n", substr1 ); // output: Marek
   printf(" substr2: %s\n", substr2 ); // output:
   printf(" substr3: %s\n", substr3 ); // output:
   printf(" substr4: %s\n", substr4 ); // output: Marek Skalewski

   sw_CloseWindow();
   return 0;
}
