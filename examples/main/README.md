<h1><p align="center">
Main.c
</p></h1>

<p align="justify">
This code creates a window using the <b>sw_CreateWindow()</b> function, sets the window title to "Hello Window", and enters a main loop. In the loop, it calls <b>sw_Begin</b>() to begin drawing on the window, sets the background color to a dark gray using the <b>sw_Background()</b> function, and draws a series of lines in a circular pattern with a yellow color using the sw_Lines function. The loop continues until the user closes the window or presses the escape key, at which point the program calls <b>sw_CloseWindow()</b> to close the window and end the program.
</p>

<p align="justify">
NOTE, it is important to note that all rendering actions should be done between the sw_Begin(w) and sw_End(w) functions. This is because these functions handle the setup and cleanup of the rendering context, and any drawing done outside of these functions may result in unexpected behavior or errors. Additionally, the sw_MainLoop(w) and sw_WaitEvents(w) functions are used to handle the main loop and event handling of the application, respectively. The sw_GetKey(w, KEY_ESCAPE) function is used to check if the escape key has been pressed, and if so, it will exit the main loop and close the window.
</p>

``` c
#include "seawolf.h"

int main( void )
{
   pSeaWolf w;
   const char *text = "Hello Window";
   int x1, y1, x2, y2;
   uint8_t i;
   int n = 46, radius = 100;

   w = sw_CreateWindow( 830, 450, text );

   while( ! sw_MainLoop( w ) && ! sw_GetKey( w, KEY_ESCAPE ) )
   {
      sw_Begin( w );

         x2 = sw_WinWidth( w ) / 2;
         y2 = sw_WinHeight( w ) / 2;

         sw_Background( w, 0x323232 );

         for( i = 0; i < 2 * n; i++ )
         {
            x1 = sin(        i * M_PI / n ) * radius * 2 + x2;
            y1 = cos( M_PI + i * M_PI / n ) * radius * 2 + y2;
            sw_Lines( w, x1, y1, x2, y2, 0xfecb0b );
         }

      sw_End( w );

      sw_WaitEvents( w );
   }

   sw_CloseWindow( w );

   return 0;
}
```

![Main](main.png)

<p align="justify">
Code below creates a loop that runs for 2 * n iterations. In each iteration, it calculates the x and y coordinates of the line's starting point using trigonometry. Then, it uses the modulus operator to check the value of i and change the color of the line accordingly. The line is then drawn at the calculated x and y coordinates using the sw_Lines function. However, it doesn't make the lines move, it only changes the color of the lines on each iteration.
</p>

``` c
for( i = 0; i < 2 * n; i++ )
{
   x1 = sin(        i * M_PI / n ) * radius * 2 + x2;
   y1 = cos( M_PI + i * M_PI / n ) * radius * 2 + y2;

   //Change color based on i value
   if( i  %4 == 1 )
      sw_Lines( w, x1, y1, x2, y2, 0xfecb0b );
   else if( i %4 == 2 )
      sw_Lines( w, x1, y1, x2, y2, 0x7a5aff );
   else if( i %4 == 3 )
      sw_Lines( w, x1, y1, x2, y2, 0x00ff00 );
   else
      sw_Lines( w, x1, y1, x2, y2, 0xff0000 );
}
```