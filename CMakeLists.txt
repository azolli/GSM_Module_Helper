cmake_minimum_required(VERSION 3.7.2)  # CMake version check
project(GSMHelper)               # Create project "GSM Helper"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES src/main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(GSMHelper ${SOURCE_FILES})


#add_test(NAME TestName COMMAND ExecutableToRun arg1 arg2 ...)
