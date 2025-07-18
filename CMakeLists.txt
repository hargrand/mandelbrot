cmake_minimum_required(VERSION 3.15)

project(mandel C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Add test subdirectory
add_subdirectory(math)
add_subdirectory(test)

# Main program
add_executable(mandel main.c)

# Enable warnings for MSVC
if(MSVC)
    target_compile_options(mandel PRIVATE /W4 /WX)
endif()

# Enable testing
enable_testing()
