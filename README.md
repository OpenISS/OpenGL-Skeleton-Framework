# New in Programming Assignment 3
* OpenISS skeleton tracker integration
* Multi-light shadows

# Building & Running

## Building Dependencies

* cmake >= 3.17.0
* C++ >= 14

## Manual Build Steps (Windows/MacOS/Linux)
```bash
cd <project_root>
cmake -S . -B cmake-build
cmake --build cmake-build --target install
cd dist
./SunRay
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

# Controls (Programming Assignment 3)
A user interface is provided.

# Controls (new in Programming Assignment 2)
* **X** to toggle textures
* **B** to toggle shadows
* **Spacebar** to teleport model to a random position on the grid
* **N** to cycle through the shear direction, starts at `Y`
* **F/G/C/V** (uppercase) control small step model shear in the direction selected by **N**
* **F/G/C/V** (lowercase) control continuous model shear in the direction selected by **N**

# Controls (Programming Assignment 1 & 2)
* **W/A/S/D** to move camera, **mouse movement** to rotate camera
* **Left mouse button + mouse movement** to zoom camera in/out
* **Middle mouse button + mouse movement** to tilt camera
* **Right mouse button + mouse movement** to pan camera
* **Left/right arrows** to rotate world around its `X` axis, **up/down arrows** to rotate world around its `Y` axis
* **1/2/3/4/5** to select model
* **T/L/P** to set model to triangle/line/point rendering mode
* **Y/I** to scale model up/down
* **U/J** (uppercase) to move model up/down
* **H/K** (uppercase) to move model to its left/right
* **H/K** (lowercase) to rotate model about its `Y` axis

# Architecture
API docs also available.

## Application Lifecycle
* **main.cpp:** GLFW window & input handling + OpenGL setup.
* **World:** Contains global state such as the camera and scene graph. Runs update and render loops. Manages all modules.
* **Module:** Logical class that can receive inputs and update/render - every major feature is implemented as a self-contained module.

## Wrappers
* **Camera:** Abstracts camera transform and projection math.
* **LightData:** Contains light source properties (for Phong lighting).
* **Material:** Contains material properties (for Phong lighting).
* **Mesh:** Abstracts mesh GPU buffer construction, uploading, and rendering.
* **VertexBuffer:** Abstracts VBO OpenGL implementation away from mesh.
* **IndexBuffer:** Abstracts IBO (EBO) OpenGL implementation away from mesh.
* **Shader:** Abstracts shader compilation, linking, and uniform updates.
* **Texture:** Abstracts texture loading from file and uploading to GPU.

## Modules
* **Assignment1:** Implements programming assignment 1 specifications.
* **Assignment2:** Implements programming assignment 2 specifications.
* **Assignment3:** Implements programming assignment 3 specifications.
* **FPSCamera:** FPS game camera movement and orientation.
* **GroundGrid:** Constructs and renders the 128x128 grid.
* **ImGuiIntegration:** Integrates the ImGui UI library.
* **ModuleManagerUI:** ImGui UI window that lets the user toggle modules and tests on/off.
* **OriginAxis:** Constructs and renders the 3 axis lines.
* **RenderingMode:** Sets OpenGL to point/line/triangle polygon mode.
* **SceneGraph:** This is our hiearchical modelling system.
* **Shadows:** Implements the two-pass shadow algorithm.
* **WorldOrientation:** Rotates the hierarchy's root node in response to input.

## Adapters
* **OISkeletonTrackerAdapter:** Drives a NodeSkeleton using an OpenISS skeleton tracker.

## Misc
* **color.h:** Utility functions for dealing with colors.
* **LoaderOBJ:** Loads meshes from the .obj file format.
* **Node:** Invisible member of the scene graph.
* **NodeCharacter:** Member of the scene graph, renders cubes that compose a character (from ResourcesAlphabet).
* **NodeModel:** Member of the scene graph, rendered using its associated mesh, shader, and material.
* **Resources:** For common constants (ex `unitSize` and `colorWhite`) and resources (ex `unitCube` and `quad`).
* **ResourcesAlphabet:** For loading letter/digit cube transforms from an embedded text file.

## Shaders
* **color:** Displays vertex color.
* **lit:** Blinn-Phong lighting with texturing and shadow reception.
* **shadow_cast:** Outputs depth only.
* **shadowed:** Displays vertex color with shadow reception.
* **textured:** Displays textured surface.

## Tests
* **TestAlphabet:** The user can display any character model by pressing its key. Verifies that they load and render correctly.
* **TestHalfCylinder:** Displays the procedurally generated half-cylinder mesh that is used for the stage in Programming Assignment 2.
* **TestImGuiIntegration:** Displays ImGui's demo window.
* **TestLitShader:** A scene for testing Phong lighting.
* **TestLoaderOBJ:** Loads and displays a Utah teapot.
* **TestMultiLights:** A scene for testing multiple active lights at the same time.
* **TestSceneGraph:** Displays a nested hierarchy which generates complex movement. Verifies the hierarchical modelling system.
* **TestShapeMeshes:** Displays all procedurally generated meshes, textured.
* **TestTexture:** Tests the Texture wrapper class, as well as tiling textures.
* **TestUnitCube:** Displays a simple rotating unit cube. This is the "hello world" of this framework.
* **TestVertexDrawing:** Displays a simple rotating quad. Verifies the `glDrawArrays` code path (as opposed to the indexed `glDrawElements` code path).
