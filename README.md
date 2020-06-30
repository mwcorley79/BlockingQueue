# BlockingQueue build test on Windows 10
# Prereqs.. 
# Install CMake for Windows: https://cmake.org/download/   
# Visual Studio 2019 (installed, using as default generator)
# Steps for testing on Windows
# git clone https://github.com/mwcorley79/BlockingQueue.git
# cd BlockingQueue
# mkdir wbuild
# cd wbuild
# cmake .. -DCMAKE_INSTALL_PREFIX=../_install  
# start Visual Studio 2019, and open BlockingQueue.sln (solution) in the wbuild folder  
# build/run/debug BlockingQueueTest project as usual with VS 2019  
# Note: Cmake uses CMakeLists.txt to generate the Visual Studio solution on Windows
# *** The same CMakeLists.txt is used by CMake to generate Makefiles on Linux (see below) ***
# Steps for testing on Linux
# install cmake 3.10 or greater (debain based:  sudo apt-get install cmake)
# git clone https://github.com/mwcorley79/BlockingQueue.git
# cd BlockingQueue
# mkdir lbuild
# cd lbuild
# cmake .. -DCMAKE_INSTALL_PREFIX=../_install  

# CMake == "very nice cross platform code generation!"
# This is my first CMake project. Many more to come to soon! 
