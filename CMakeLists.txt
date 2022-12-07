cmake_minimum_required(VERSION 3.24)
project(APC)

set(CMAKE_CXX_STANDARD 14)

add_executable(APC main.cpp fixed_point.cpp fixed_point.h)
