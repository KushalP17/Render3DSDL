cmake_minimum_required(VERSION 3.16)
project(hello)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in external/SDL
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(hello WIN32 src/hello.cpp src/Points3D.cpp)

# Find other custom header files for proj
target_include_directories(
    hello
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
)

# Link to the actual SDL3 library.
target_link_libraries(hello PRIVATE SDL3::SDL3)