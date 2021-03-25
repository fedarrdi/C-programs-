cmake_minimum_required(VERSION 3.17)
project(hash C)

set(CMAKE_C_STANDARD 99)

add_library(hash library.h cmake-build-debug/hash.c)