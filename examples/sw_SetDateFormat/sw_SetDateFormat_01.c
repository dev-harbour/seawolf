/*
 *
 */

#include "seawolf.h"

int main( void )
{
   sw_CreateWindow( 830, 450, "sw_SetDateFormat" );

   sw_SetDateFormat( "%y.%m.%d" );

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x323232 );

      sw_End();
      sw_PollEvents();
   }

   sw_SetDateFormat( "%d.%m.%y" );
   printf( "Date format: %s\n", sw_CDate() );
   sw_SetDateFormat( "%d-%m-%y" );
   printf( "Date format: %s\n", sw_CDate() );
   sw_SetDateFormat( "%d/%m/%y" );
   printf( "Date format: %s\n", sw_CDate() );

   sw_CloseWindow();
   return 0;
}
