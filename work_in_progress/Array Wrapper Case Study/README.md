# Array Wrapper Case Study
Investigate implementation of structures and algorithms for maniupalting data array.

## Compiling Instructions
Build as regular CMake project:
1. Create build directory and `cd` into it. Than create directory structure and
makefiles using:
```
$ cmake -DCMAKE_C_COMPILER=clang-c -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ../.. -B .
$ make
```

for \*NIX platforms,

2. or using:
```
$ cmake -DOpenCV_PATH="path_to_opencv" -DCMAKE_C_COMPILER=clang-c -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ../.. -B .
$ msbuild.exe myproject.sln
```

for Win64 platform.

Build paramters can take following values:
```
-DCMAKE_CXX_COMPILER=(clang-c/cl/gcc/...)
-DCMAKE_BUILD_TYPE=(Debug/RelWithDebInfo/Release/MinSizeRel)
-DBUILD_SHARED_LIBS:BOOL=(TRUE/FALSE)
-DBUILD_TESTING:BOOL=(TRUE/FALSE)
-G ("NMake Makefiles"/"Unix Makefiles"/...)
```
