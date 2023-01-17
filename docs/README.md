# seawolf

#### sw_GetTime()

<p align="justify">
This function uses the <b>gettimeofday</b> function to get the current time in seconds, and returns it as a double. The <b>struct timeval<b> contains the current time in seconds and microseconds, and the <b>gettimeofday</b> function fills in this struct with the current time. The returned time can be used for various purposes, such as timing animation loops or measuring the performance of certain parts of the code.
</p>

<p align="justify">
You can then use this function in your main code to calculate the elapsed time between two points, and use it to control the animation speed.
</p>

``` c
double start_time = sw_GetTime();
double end_time;
double elapsed_time;

while( ! sw_MainLoop( w ) && ! sw_GetKey( w, KEY_ESCAPE ) )
{
   start_time = sw_GetTime();
   sw_Begin( w );

      // render code here

   sw_End( w );

   end_time = sw_GetTime();
   elapsed_time = end_time - start_time;
   // Code to handle the frame rate
   sw_PollEvents( w );
}
```

<p align="justify">
You can also use it to measure the performance of certain parts of your code and optimize them as needed.
</p>

<p align="justify">
It's worth noting that the gettimeofday function is available on POSIX systems and some other platforms, but it might not be available on all platforms, you should check the documentation of your platform to see what time functions are available, and use.
</p>

