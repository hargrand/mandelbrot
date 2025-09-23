# Create a static library from complex.c
add_library(image_generator STATIC complex.c "mandelbrot.c")

# Specify the include directories for this target
target_include_directories(image_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../)
