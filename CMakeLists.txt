cmake_minimum_required(VERSION 3.24)
project(ChessEngine C)

set(CMAKE_C_STANDARD 23)

add_executable(ChessEngine main.c defs.h init.c bitboards.c hashkeys.c board.c)
