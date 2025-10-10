# Create a static library from complex.c
add_library(image_generator STATIC 
    complex_math.c 
    mandelbrot.c)

# Make the library's include path visible to anything that links against it
target_include_directories(image_generator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}       # for image_generator/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/..    # allow includes from parent if needed
    ${PNG_INCLUDE_DIRS}
)

# Find and link dependencies
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)

target_link_libraries(image_generator PRIVATE PNG::PNG ZLIB::ZLIB)