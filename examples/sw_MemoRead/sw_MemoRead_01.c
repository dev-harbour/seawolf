/*
 *
 */

#include "seawolf.h"

int main( void )
{
   const char *filePath = "sw_MemoRead_01.c";
   char *fileContent = sw_MemoRead( filePath );

   sw_CreateWindow( 830, 450, "sw_MemoRead" );

   if( strcmp( fileContent, "" ) == 0 )
   {
      printf( "Could not read file %s \n", filePath );
      return 1;
   }

   while( ! sw_MainLoop() && ! sw_GetKey( KEY_ESCAPE ) )
   {
      sw_Begin();

         sw_Background( 0x003232 );

      sw_End();
      glfwPollEvents();
   }

   printf( "%s \n", fileContent );
   free( fileContent );

   sw_CloseWindow();
   return 0;
}
