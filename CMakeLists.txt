cmake_minimum_required(VERSION 3.10)
project(Kits)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Kits main.cpp
    src/kitshandler.cpp
)

include_directories(${CMAKE_SOURCE_DIR})