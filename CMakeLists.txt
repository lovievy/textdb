cmake_minimum_required(VERSION 3.11...3.21)
project(
        TextDB
        VERSION 1.0
        DESCRIPTION "An text database library"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(db)
add_subdirectory(test EXCLUDE_FROM_ALL)
add_subdirectory(benchmark EXCLUDE_FROM_ALL)