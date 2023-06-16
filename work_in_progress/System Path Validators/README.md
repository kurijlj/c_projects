# GSL Framework
Framework for developing system path validation routines. The goal is to develop platform indenpendent code that wil for the given system path check if the path exists, is directory or a file, is empty directory or an empty file, is text file or an executable, ...

## Compiling Instructions
Build as a regular CMake project:
1. Create a build directory and `cd` into it. Then create a directory structure and
makefiles using:
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -S <source-path> -B .
$ cmake --build . --config Debug
```
or
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -S <source-path> -B .
$ make
```

for \*NIX platforms,

2. or using:
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -S <source-path> -B .
$ cmake --build . --config Debug
```
or
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -S <source-path> -B .
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