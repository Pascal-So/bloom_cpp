cmake_minimum_required(VERSION 3.5)

add_executable(BloomFilterBenchmark BloomFilterBenchmark.cpp)

add_library(hayai INTERFACE)
target_include_directories(hayai
    INTERFACE ../third-party/hayai/src
)

target_link_libraries(BloomFilterBenchmark
    PRIVATE
        hayai
        BloomFilter
)
