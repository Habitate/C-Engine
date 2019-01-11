# C-Engine
A simple concept C++/SDL graphics engine that I occassionally work on. 

# HOW-TO Build
1. Make sure you have a **C/C++ Compiler** that **supports posix threads** (any new version should suffice).
2. Make sure you have **SDL2**, **SDL2_Image** and **SDL2_TTF** installed under the compiler path directory.
3. Make sure you have **CMake** and **MAKE**.
4. Go inside the */build/* folder and run ```cmake -G "MinGW Makefiles" .```. Note that, if you have a compiler other than **MinGW** on windows, you'll need to find out what to put inside the quotes on your own. Oooorrrr, just compile everything by hand ¯\\_(ツ)_/¯.
5. Simply run ```make``` while still inside the */build/* folder. The compiled executable will be placed inside the */bin/* folder.

P.S. The **compiler**, **CMake** and **MAKE** all should be accessible from the command line (A.K.A Added to the **%PATH%**).

P.S.P.S If you can't run the **.exe**, please copy all of the **.dlls** from the */lib/* folder to the */bin/* folder.
