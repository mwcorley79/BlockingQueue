# BlockingQueue build test on Windows 10
# Prereqs.. 
# Install CMake for Windows: https://cmake.org/download/   
# Visual Studio 2019 (installed, using as default generator)
# Steps for testing...
# git clone https://github.com/mwcorley79/BlockingQueue.git
# cd BlockingQueue
# mkdir build
# cd build
# cmake .. -DCMAKE_INSTALL_PREFIX=../_install  
# start Visual Studio 2019, and open BlockingQueue.sln (solution) in the build folder  
# build/run/debug BlockingQueueTest project as usual with VS 2019  
# Note: Cmake uses CMakeLists.txt to generate the Visual Studio solution on Windows
#      The same CMakeLists.txt is used by CMake to generate Makefiles on Linux etc.
# CMake == "very nice cross platform code generation!"
# This is my first CMake project. Many more to come to soon! 

