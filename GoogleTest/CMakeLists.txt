cmake_minimum_required(VERSION 3.16)
project(minishell_tests)


set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(minishell_tests
        main.cpp
        Tests/test.cpp
		../includes/minishell.h
		../main.c
        )
