# Comp-371

## Building Dependencies

* cmake >= 3.17.0
* C++ STD >= 14

## Build Steps

### Windows
🤷‍🤷‍🤷‍

### Linux/MacOS

```bash
cd <project_root>
cmake -S . -B cmake-build
cmake --build cmake-build --target install
./cmake-build/SunRay
```

Additional Flags:
* `-G`: Specifies output format
  
  examples: `-G "CodeBlocks - Unix Makefiles"` to build a clion compatible project or `-G Xcode`
  

* `-DCMAKE_BUILD_TYPE`: to specify a build type, for example `-DCMAKE_BUILD_TYPE=Debug` or `-DCMAKE_BUILD_TYPE=Release`

## Importing Project into an IDE
### Visual Studio
🤷‍🤷‍🤷‍

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