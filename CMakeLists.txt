
cmake_minimum_required(VERSION 3.16)
project(matmul-profiler LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native -fopenmp -Wall")

find_package(OpenMP)
if (OpenMP_C_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

add_library(matmul STATIC
    src/naive_c.c
    src/reorder_c.c
    src/omp_c.c
    src/tiled_c.c
    src/simd_c.c
)

add_executable(bench src/main_bench.c)
target_link_libraries(bench PRIVATE matmul m)

