cmake_minimum_required(VERSION 3.10)
project(HelloTest)

enable_testing()

add_executable(test_main
    test_main.cpp
    ../src/dijkstra.cpp
    ../src/bellmanFord.cpp
    ../src/dfs.cpp
)
set_target_properties(test_main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
target_link_libraries(test_main gtest gtest_main)
add_test(NAME AlgoTest COMMAND ${CMAKE_BINARY_DIR}/tests/test_main.exe)