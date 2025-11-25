cmake_minimum_required(VERSION 3.10)

project(mandel C)

# Set the C standard to C99. This is good practice and ensures that
# features like declaring variables inside for-loops are supported.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find the libpng library. The 'REQUIRED' keyword will cause CMake to
# fail with an error if the library is not found.
find_package(PNG REQUIRED)

# Find the Zlib library, which is a dependency of libpng.
find_package(ZLIB REQUIRED)

# Define the executable target from the source file.
add_executable(mandel main.c mandel.c image.c)

# Link the executable against the libraries found by find_package.
# Using the modern target-based approach (PNG::PNG) is recommended.
target_link_libraries(mandel PRIVATE PNG::PNG ZLIB::ZLIB)

# Add compiler options for strict warnings and treat warnings as errors.
# This uses generator expressions to apply the correct flags based on the compiler.
target_compile_options(mandel PRIVATE
    # Flags for GCC and Clang
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
    # Flags for MSVC (Visual Studio)
    $<$<C_COMPILER_ID:MSVC>:/W4 /WX>
)
