# Focus Precision Anlayze

**Project Outline:** Focus Precision Measurement Log Viewer

## I Introduction

A. Background
B. Purpose of the Application
C. Objectives

## II Technologies and Libraries

A. GNU Scientific Library (GSL)
B. GTK (Graphical User Interface Toolkit)
C. PLplot (Plotting Library)

## III Features of the Application

### A. File Validation

1. Check file format and structure
2. Ensure data integrity and completeness

### B. Data Reading

1. Parse measurement logs
2. Extract necessary data fields

### C. Data Plotting

1. Plot measurement data on the screen

## IV Compiling Instructions

Build as a regular CMake project:

1. Create a build directory and `cd` into it. Then create a directory structure and
makefiles using:

```
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -DNO_AMPL_BINDINGS=True -S <source-path> -B .
cmake --build . --config Debug
```

or

```
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -DNO_AMPL_BINDINGS=True -S <source-path> -B .
make
```

for \*NIX platforms,

2. or using:

```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -DNO_AMPL_BINDINGS=True -S <source-path> -B .
cmake --build . --config Debug
```

or

```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -DNO_AMPL_BINDINGS=True -S <source-path> -B .
msbuild.exe myproject.sln
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