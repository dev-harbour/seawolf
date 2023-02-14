/*
 *
 */

#include "seawolf.h"

int main( void )
{
   sw_CreateWindow( 830, 450, "sw_Text" );

   sw_LoadFont_9x18_BDF( "../../font/9x18.bdf" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x323232 );

         sw_DrawText_9x18( 100, 100, "1234567890" );

      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
