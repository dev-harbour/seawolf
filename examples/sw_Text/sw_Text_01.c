/*
 *
 */

#include "seawolf.h"

int main( void )
{
   sw_CreateWindow( 830, 450, "sw_Text" );

   SW_Text txt;
   txt.x = 10.0f;
   txt.y = 10.0f;
   txt.text = "This is a simple test!";
   txt.size = 1.0f;
   txt.filePath = "../../font/freemono/FreeMono.ttf";
   txt.hc = 0xff0000;

   text_functions( TEXT_OPEN_FONT, &txt );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x323232 );

         text_functions( TEXT_TEXT, &txt );

      sw_End();
      sw_PollEvents();
   }

   sw_CloseWindow();
   return 0;
}
