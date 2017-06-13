cmake_minimum_required(VERSION 3.7)
project(Mause)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MauseGestures.cpp MauseGestures.h)
add_executable(Mause ${SOURCE_FILES})