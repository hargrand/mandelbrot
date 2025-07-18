# Create a static library from complex.c
add_library(math STATIC complex.c)

# Specify the include directories for this target
target_include_directories(math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../)
