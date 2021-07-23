cmake_minimum_required(VERSION 3.16)
project(minishell LANGUAGES C CXX)
set(CMAKE_C_STANDARD 99)


# SET VARIABLES:
# ====================================================
# Adds list of project files
FILE(GLOB MINISHELL_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/builtins/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/includes/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/libft/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/libft/*.c
)

FILE(GLOB LOCAL_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/builtins/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/includes/*.h
)
# Create copy of the variable for tests
set(TEST_SOURCES ${MINISHELL_SOURCES} tests/builtins/cmd_generator.c tests/builtins/builtins.h)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lreadline")
# We can't use another main function in tests, so exclude main.c file
list(FILTER TEST_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")
list(FILTER TEST_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/src/builtins/main.c")
list(FILTER MINISHELL_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/src/builtins/main.c")
# Print our variables
message(STATUS ${MINISHELL_SOURCES})
message(STATUS ${TEST_SOURCES})
# ====================================================


# Add GoogleTests directory
# ====================================================
# Build googletest
add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
        "googletest"
)
# ====================================================

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libft)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/readline)
link_directories(/Users/yeschall/.brew/Cellar/readline/8.1/lib/)
# Add Executables (binary files)
# ====================================================
# Main target
add_executable(
        minishell
        ${MINISHELL_SOURCES}
)
# Test target
add_executable(
        test_minishell
#        tests/test.cpp
        tests/builtins/builtins.cpp
        tests/builtins/cmd_generator.c
        ${TEST_SOURCES}
)
# ====================================================

# Local targets
add_executable(
        builtins
        ${LOCAL_SOURCES}
)
# ====================================================

target_link_libraries(
        test_minishell PRIVATE
        gtest gtest_main
		readline
        libft
		libreadline.a
		libhistory.a
)


target_link_libraries(
        builtins PRIVATE
        libft
)

target_link_libraries(
        minishell PRIVATE
        readline
        libft
		libreadline.a
		libhistory.a
)

target_compile_options(
        minishell PRIVATE
#        -Wall -Wextra -Werror
)


