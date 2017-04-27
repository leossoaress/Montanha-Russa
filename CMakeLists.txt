cmake_minimum_required(VERSION 3.7)
project(MR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES main.cpp passanger.cpp car.cpp park.cpp passanger.h park.h car.h)
add_executable(MR ${SOURCE_FILES})