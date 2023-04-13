enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_Declare(
    googlebenchmark
    URL https://github.com/google/benchmark/archive/d572f4777349d43653b21d6c2fc63020ab326db2.zip
)

FetchContent_MakeAvailable(
    googletest
    googlebenchmark
)

add_executable(db_benchmark db_benchmark.cpp)

target_link_libraries(db_benchmark benchmark::benchmark textdb_shared)