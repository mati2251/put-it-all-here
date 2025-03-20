cmake_minimum_required(VERSION 3.7)

project(opencl)

add_executable(vadd vadd/main.c)
target_compile_features(vadd PRIVATE cxx_auto_type)

add_executable(mat-mul mat-mul/main.c)
target_compile_features(mat-mul PRIVATE cxx_auto_type)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})

target_link_libraries(vadd ${OpenCL_LIBRARIES})
target_link_libraries(mat-mul ${OpenCL_LIBRARIES})

