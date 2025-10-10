cmake_minimum_required(VERSION 3.10)

project(PngTestPattern C)

# Set the C standard to C99. This is good practice and ensures that
# features like declaring variables inside for-loops are supported.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find the libpng library. The 'REQUIRED' keyword will cause CMake to
# fail with an error if the library is not found.
find_package(PNG REQUIRED)

# Find the Zlib library, which is a dependency of libpng.
find_package(ZLIB REQUIRED)

# Define test executable
add_executable(
    mandel_tests
    support.c
    test_complex.c
    mandel_test.c)

# Enable strict compilation for tests too
if(MSVC)
    target_compile_options(mandel_tests PRIVATE /W4 /WX)
endif()

# Link with any libraries if needed (optional)
target_link_libraries(mandel_tests PRIVATE image_generator)

# Add the test to CTest
add_test(NAME c_mandel_tests COMMAND mandel_tests)

