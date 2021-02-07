# Building & Running

## Building Dependencies

* cmake >= 3.17.0
* C++ >= 14

## Build Steps

### Windows
```bash
cd <project_root>
cmake -S . -B cmake-build
cmake --build cmake-build --target install
./dist/SunRay
```

### Linux/MacOS

```bash
cd <project_root>
cmake -S . -B cmake-build
cmake --build cmake-build --target install
./cmake-build/SunRay
```

Additional Flags:
* `-G`: Specifies output format
  
  Examples: `-G "CodeBlocks - Unix Makefiles"` to build a clion compatible project or `-G Xcode`
  

* `-DCMAKE_BUILD_TYPE`: to specify a build type, for example `-DCMAKE_BUILD_TYPE=Debug` or `-DCMAKE_BUILD_TYPE=Release`

## Importing Project into an IDE
### Visual Studio
In Visual Studio 2017 with the `Visual C++ tools for CMake` component installed:

File -> Open-> CMake... -> Select `CMakeLists.txt` in file browser

### VSCode
🤷‍🤷‍🤷‍

### Clion 

1. Clone repo
1. Open project folder in clion
1. Tweak any cmake / c++ configurations options you may need
1. Target & Executable should be SunRay

### XCode 

1. Clone repo
1. Run `cmake -G Xcode -S . -B cmake-xcode` to generate an xcode project file
1. Open `./cmake-xcode/SunRay.xcodeproj`
1. Set target to SunRay and build

# Controls
* Camera: **W/A/S/D** to move, move mouse to look, **left/right mouse buttons** to zoom in/out
* World orientation: **left/right arrows** to rotate vertically, **up/down arrows** to rotate horizontally
* **T/L/P** for triangle/line/point rendering modes
* **1/2/3/4/5** to select model
* **U/O** to scale model up/down
* **I/J/K/L** (uppercase) to move model
* **J/L** (lowercase) to rotate model about Y axis and **I/K** (lowercase) for the X axis

# Architecture
TODO
