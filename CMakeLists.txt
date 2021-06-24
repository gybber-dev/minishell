cmake_minimum_required(VERSION 3.16)
project(minishell LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)


# Build googletest
add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
        "googletest"
)

# Main target
add_executable(
        minishell
        src/main.c
        src/includes/minishell.h
)

# Test target
add_executable(
        test_minishell
        tests/test.cpp
        src/includes/minishell.h
        src/main.c
)

# Вместо src/includes/minishell.h добавляем заголовочные файлы через
# https://youtu.be/jyQcCWWcIQU?t=2855
#target_link_directories(
#        test_minishell PRIVATE
#        "${CMAKE_CURRENT_SOURCE_DIR}/src"
#        "${CMAKE_CURRENT_SOURCE_DIR}/src/includes"
#)

target_link_libraries(
        test_minishell PRIVATE
        gtest gtest_main
)

target_compile_options(
        minishell PRIVATE
        -Wall -Wextra -Werror
)


