cmake_minimum_required(VERSION 3.15)

project(mandelbrot C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Packages
find_package(PNG REQUIRED)

# Add test subdirectory
add_subdirectory(image_generator)
add_subdirectory(test)

# Main program
add_executable(mandel main.c)
target_include_directories(mandel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/image_generator)
target_link_libraries(mandel PRIVATE image_generator PNG::PNG)

# Enable warnings for MSVC
if(MSVC)
    target_compile_options(mandel PRIVATE /W4 /WX)
endif()

# Enable testing
enable_testing()
