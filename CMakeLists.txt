cmake_minimum_required(VERSION 3.19)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(GoogleTest)


add_executable(minishell main.c)

enable_testing()
add_test(
        NAME unit_tests
        COMMAND minishell_tests
)