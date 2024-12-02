cmake_minimum_required(VERSION 3.30)

project(advent_of_code_2024 VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# project with default compiler warnings
include(cmake/CompilerWarnings.cmake)
add_library(advent_2024_warnings INTERFACE)
advent2024_setup_project_warnings(advent_2024_warnings)

add_subdirectory(day01)
