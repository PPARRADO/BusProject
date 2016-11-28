cmake_minimum_required(VERSION 3.6)
project(BusProject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Trajet.cpp Trajet.h algo.h algo.cpp Base.cpp Base.h file_reader.cpp file_reader.h)
add_executable(BusProject ${SOURCE_FILES})