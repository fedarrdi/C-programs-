cmake_minimum_required(VERSION 3.22)
project(pool)

set(CMAKE_CXX_STANDARD 14)

add_executable(pool main.cpp Point.cpp Point.h Table.cpp Table.h Ball.cpp Ball.h)
