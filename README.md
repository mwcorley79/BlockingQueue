# BlockingQueue build test on Windows 10
  Prereqs (Windows)
  <ol>
    <li> Install CMake for Windows: https://cmake.org/download/ </li>
    <li> Visual Studio 2019 (installed, using as default generator)</li>
  </ol>
  Steps for testing on Windows
  <ol>
    <li> git clone https://github.com/mwcorley79/BlockingQueue.git </li>
    <li>cd BlockingQueue</li>
    <li>mkdir wbuild</li>
    <li>cd wbuild</li>
    <li>cmake .. -DCMAKE_INSTALL_PREFIX=../_install</li> 
    <li>start Visual Studio 2019, and open BlockingQueue.sln (solution) in the wbuild folder</li>  
    <li>build/run/debug BlockingQueueTest project as usual with VS 2019 </li> 
   </ol>
 <b> Note: Cmake uses CMakeLists.txt to generate the Visual Studio solution on Windows <br>
  *** The same CMakeLists.txt is used by CMake to generate Makefiles on Linux (see below) *** </b>
 Prereqs (Linux)
  <ol>
      <li> install cmake 3.10 or greater (debian based:  sudo apt-get install cmake) </li>
      <li> toolchain: gcc/g++ etc.</li>
  </ol>
Steps for testing on Linux
<ol> 
  <li> git clone https://github.com/mwcorley79/BlockingQueue.git </li>
  <li> cd BlockingQueue </li>
  <li> mkdir lbuild </li>
  <li> cd lbuild </li>
  <li> cmake .. -DCMAKE_INSTALL_PREFIX=../_install </li>
 </ol>

<b> CMake == "very nice cross platform code generation!" <br>
 This is my first CMake project. Many more to come to soon! 
  </b>
