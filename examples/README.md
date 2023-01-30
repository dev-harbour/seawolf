# seawolf

## Installing on Windows

- MSYS2

   ```
   pacman -S mingw-w64-x86_64-gc
   pacman -S mingw-w64-x86_64-glfw
   ```
   To test it, type:

   ```
      $ cd examples/main
      $ gcc main.c -o main -I ../../include -L ../../lib/win/mingw64 -lgc -lseawolf -lglfw3 -lopengl32 -lm
   ```

## Installing on Linux

- Debian

   ```
   sudo apt-get update
   sudo apt-get install libgc-dev
   sudo apt-get install libglfw3-dev
   ```
   To test it, type:

   ```
      $ cd examples/main
      $ gcc main.c -o main -I ../../include -L ../../lib/linux/gcc -lseawolf -lglfw -GL -lm
   ```
---
