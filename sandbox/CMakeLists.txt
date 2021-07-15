cmake_minimum_required(VERSION 3.16)
project(minishell LANGUAGES C)
set(CMAKE_C_STANDARD 99)

add_executable(
		sandbox
		pipe_redirs.c
)