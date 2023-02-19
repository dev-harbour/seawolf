/*
 *
 */

#include "seawolf.h"

int main( void )
{
   const char *name = "Marek Skalewski";
   const char *substr1 = sw_SubStr( name,  1, 5 );
   const char *substr2 = sw_SubStr( name,  7, 0 );
   const char *substr3 = sw_SubStr( name, -9, 0 );
   const char *substr4 = sw_SubStr( name, -9, 3 );
   int centerY;

   sw_CreateWindow( 830, 450, "sw_SubStr" );

   sw_LoadFont_9x18_BDF( "../../font/9x18.bdf" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x274534 );

         centerY = ( sw_WinHeight() - 4 * 18 ) / 2;

         sw_DrawTextCenterBDF( sw_WinWidth(), centerY += 18, substr1, 0x274534, 0xf6f6f6 );
         sw_DrawTextCenterBDF( sw_WinWidth(), centerY += 18, substr2, 0x274534, 0xf6f6f6 );
         sw_DrawTextCenterBDF( sw_WinWidth(), centerY += 18, substr3, 0x274534, 0xf6f6f6 );
         sw_DrawTextCenterBDF( sw_WinWidth(), centerY += 18, substr4, 0x274534, 0xf6f6f6 );

      sw_End();
      sw_WaitEvents();
   }

   printf(" substr1: %s\n", substr1 ); // output: Marek
   printf(" substr2: %s\n", substr2 ); // output: Skalewski
   printf(" substr3: %s\n", substr3 ); // output: Skalewski
   printf(" substr4: %s\n", substr4 ); // output: Ska

   sw_CloseWindow();
   return 0;
}
