cmake_minimum_required(VERSION 3.10)
project(MyProject)

enable_testing()

add_subdirectory(lib/googletest)

include_directories(lib/googletest/include)

add_subdirectory(tests)