## TwistLoad

A simple, yet functional download manager for Windows, OS X, and Linux.

### Requirements

The following pieces of software are required in order to build TwistLoad:

- CMake 2.8.9+
- Qt 5.1+
- A C++ compiler:
    - Visual C++
    - GCC
    - Clang

### Build Instructions

1. Create an empty directory for building the application:

        mkdir build
        cd build

2. Run CMake:

        cmake ..

3. Build the application:

        make -j3

   (Replace "3" with the number of CPU cores in your system + 1.)

4. The application can be run with:

        ./twistload    # Mac / Linux
        twistload.exe  # Windows
