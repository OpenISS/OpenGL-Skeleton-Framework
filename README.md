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
* `-G`: Specifies output format, for example: `-G "CodeBlocks - Unix Makefiles"` to build a clion compatible project or `-G Xcode`
  

* `-DCMAKE_BUILD_TYPE`: to specify a build type, for example: `-DCMAKE_BUILD_TYPE=Debug` or `-DCMAKE_BUILD_TYPE=Release`

## Importing Project into an IDE
### Visual Studio
In Visual Studio 2017 with the `Visual C++ tools for CMake` component installed:

1. Open project: File -> Open-> CMake... -> Select `CMakeLists.txt` in file browser
2. Startup item should be `SunRay.exe`

### VSCode
In VSCode with the `CMake` and `CMake Tools` extensions installed:

1. Open project folder, ask CMake extension to setup for an appropriate compiler (should support C++14)
2. Set `SunRay` as build target and run target

### Clion 

1. Open project folder in clion
2. Tweak any cmake / c++ configurations options you may need
3. Target & Executable should be `SunRay`

### XCode 

1. Run `cmake -G Xcode -S . -B cmake-xcode` to generate an xcode project file
2. Open `./cmake-xcode/SunRay.xcodeproj`
3. Set target to `SunRay` and build

# Controls
* Camera: **W/A/S/D** to move, move mouse to look, **left/right mouse buttons** to zoom in/out
* World orientation: **left/right arrows** to rotate vertically, **up/down arrows** to rotate horizontally
* **T/L/P** for triangle/line/point rendering modes
* **1/2/3/4/5** to select model
* **Y/I** to scale model up/down
* **H/K/U/J** (uppercase) to move model
* **H/K** (lowercase) to rotate model about Y axis

# Architecture
## Application Lifecycle
* **main.cpp:** GLFW window & input handling + OpenGL setup.
* **World:** Contains global state such as the camera and scene graph. Runs update and render loops. Manages all modules.
* **Module:** Logical class that can receive inputs and update/render - every major feature is implemented as a self-contained module.

## Wrappers
* **Camera:** Abstracts camera transform and projection math.
* **Mesh:** Abstracts mesh GPU buffer construction, uploading, and rendering.
* **Shader:** Abstracts shader compilation, linking, and uniform updates.

## Modules
* **Assignment1:** Implements programming assignment 1 specifications.
* **FPSCamera:** FPS game camera movement and orientation.
* **GroundGrid:** Constructs and renders the 128x128 grid.
* **OriginAxis:** Constructs and renders the 3 axis lines.
* **RenderingMode:** Sets OpenGL to point/line/triangle polygon mode.
* **SceneGraph:** This is our hiearchical modelling system.
* **WorldOrientation:** Rotates the hierarchy's root node in response to input.

## Misc
* **color.h:** Utility functions for dealing with colors.
* **Node:** Invisible member of the scene graph.
* **NodeCharacter:** Member of the scene graph, renders cubes that compose a character (from ResourcesAlphabet).
* **NodeModel:** Member of the scene graph, rendered using its associated mesh and shader.
* **Resources:** For common constants (ex `unitSize` and `colorWhite`) and resources (ex `unitCube` and `quad`).
* **ResourcesAlphabet:** For loading letter/digit cube transforms from an embedded text file.

## Tests
* **TestAlphabet:** The user can display any character model by pressing its key. Verifies that they load and render correctly.
* **TestSceneGraph:** Displays a nested hierarchy which generates complex movement. Verifies the hierarchical modelling system.
* **TestUnitCube:** Displays a simple rotating unit cube. This is the "hello world" of this framework.
* **TestVertexDrawing:** Displays a simple rotating quad. Verifies the `glDrawArrays` code path (as opposed to the indexed `glDrawElements` code path).
