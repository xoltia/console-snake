# Console Snake
This is a simple snake game played in the console that I created in C++ for Windows.
It is my first C++ project and probably isn't the too well optimized. Also, I'm aware embedding
Python just for a simple score keeping script probably isn't worth the extra dependencies but I
thought it'd be a cool experiment and maybe something that I can later use to improve the game.

## Building
This project was made in Visual Studio 17 and I have project build events that will put all the dependencies
and scripts in place for you. To get it working without Visual Studio you need to build it and place all the .py
files in a "Script" folder inside the build directory, all the Python "lib" files inside of a "libs" folder (or have
Python 3.7.3 installed), and the Python dlls inside the root of the build directory.
