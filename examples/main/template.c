/*
 *
 */

#include "seawolf.h"

int main( void )
{
   sw_CreateWindow( 830, 450, "Template" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x323232 );

      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
