cmake_minimum_required(VERSION 3.24)
project(APC)

set(CMAKE_CXX_STANDARD 14)

add_executable(APC main.cpp lookup_table.cpp lookup_table.h fixed_point.cpp fixed_point.h)
