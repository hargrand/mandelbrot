# Define test executable
add_executable(
    mandel_tests
    support.c
    test_complex.c
    mandel_test.c "test_mandelbrot.h" "test_mandelbrot.c")

# Enable strict compilation for tests too
if(MSVC)
    target_compile_options(mandel_tests PRIVATE /W4 /WX)
endif()

# Link with any libraries if needed (optional)
target_link_libraries(mandel_tests image_generator)

# Add the test to CTest
add_test(NAME c_mandel_tests COMMAND mandel_tests)
