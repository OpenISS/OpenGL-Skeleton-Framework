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

1. Clone repo
2. Open project: File -> Open-> CMake... -> Select `CMakeLists.txt` in file browser
3. Startup item should be `SunRay.exe`

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
* **Y/I** to scale model up/down
* **U/H/J/K** (uppercase) to move model
* **H/K** (lowercase) to rotate model about Y axis

# Architecture
## Application Lifecycle
* **main.cpp:** GLFW window & input handling + OpenGL setup.
* **World:**: Contains global state such as the camera and scene graph. Runs update and render loops. Manages all modules.
* **Module:** Logical class that can receive inputs and update/render - every major feature is implemented as a self-contained module.

## Wrappers
* **Camera:** Abstracts camera transform and projection math.
* **Mesh:** Abstracts mesh GPU buffer construction, uploading, and rendering.
* **Shader:** Abstracts shader compilation, linking, and uniform updates.

## Modules
* **ModuleAxis:** Constructs and renders the 3 axis lines.
* **ModuleFPSCamera:** FPS game camera movement and orientation.
* **ModuleGrid:** Constructs and renders the 128x128 grid.
* **ModuleRenderingMode:** Sets OpenGL to point/line/triangle polygon mode.
* **ModuleSceneGraph:** This is our hiearchical modelling system.
* **ModuleWorldOrientation:** Rotates the hierarchy's root node in response to input.

## Misc
* **color.h:** Utility functions for dealing with colors.
* **Node:** Invisible member of the scene graph.
* **NodeModel:** Member of the scene graph, rendered using its associated mesh and shader.
* **Resources:** For common constants (ex `unitSize` and `colorWhite`) and resources (ex `unitCube` and `quad`).
* **ResourcesAlphabet:** For loading letter/digit cube transforms from an embedded text file.

## Tests
* **TestAlphabet:** The user can display any character model by pressing its key. Verifies that they load and render correctly.
* **TestSceneGraph:** Displays a nested hierarchy which generates complex movement. Verifies the hierarchical modelling system.
* **TestUnitCube:** Displays a simple rotating unit cube. This is the "hello world" of this framework.
* **TestVertexDrawing:** Displays a simple rotating quad. Verifies the `glDrawArrays` code path (as opposed to the indexed `glDrawElements` code path).
