cmake_minimum_required(VERSION 3.17)
project(BlockingQueue)
 
# include all the headers from the include folder
include_directories(include)
 
# adds -D define flags to the compilation of source files (needed building the test stub target)
add_definitions(-DTEST_BLOCKING_QUEUE)

# generate the Utility test stub target (executable test) from the source
add_executable(BlockingQueueTest src/Cpp11-BlockingQueue.cpp)

# install the binary into the bin directory of the install directory
install(TARGETS BlockingQueueTest DESTINATION bin)