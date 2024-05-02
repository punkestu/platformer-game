cmake_minimum_required(VERSION 3.12)
project(platformer)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Add the include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES src/**/*.c src/**/*.h game/**/*.c game/**/*.h)

# Add the source files for your project
add_executable(platformer main.c ${SOURCES})

add_compile_definitions(DEBUG)

# Link against the SDL2 library
target_link_libraries(platformer ${SDL2_LIBRARIES})