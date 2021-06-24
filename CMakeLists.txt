cmake_minimum_required(VERSION 3.19)
project(minishell LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)

#add_subdirectory(GoogleTest)
find_package(GTest)

#target_link_libraries(minishell_tests gtest gtest_main)

add_executable(minishell src/main.c)
