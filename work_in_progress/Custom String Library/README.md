# Custom String Library
Investigate the implementation of a string data type as a variable-aggregate abstract data type.

## Compiling Instructions
Build as a regular CMake project:
1. Create a build directory and `cd` into it. Then create a directory structure and
makefiles using:
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ../.. -B .
$ cmake --build . --config Debug
```
or
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ../.. -B .
$ make
```

for \*NIX platforms,

2. or using:
```
$ cmake -DCMAKE_C_COMPILER=clang -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ../.. -B .
$ cmake --build . --config Debug
```
or
```
$ cmake -DCMAKE_C_COMPILER=clang -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ../.. -B .
$ msbuild.exe myproject.sln
```

for the Win64 platform.

Build parameters can take the following values:
```
-DCMAKE_CXX_COMPILER=(clang-c/cl/gcc/...)
-DCMAKE_BUILD_TYPE=(Debug/RelWithDebInfo/Release/MinSizeRel)
-DBUILD_SHARED_LIBS:BOOL=(TRUE/FALSE)
-DBUILD_TESTING:BOOL=(TRUE/FALSE)
-G ("NMake Makefiles"/"Unix Makefiles"/...)
```
