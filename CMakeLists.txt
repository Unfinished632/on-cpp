cmake_minimum_required(VERSION 3.28)
project(OnLang VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(OnLang 
    src/main.cpp
    src/interpreter.cpp
    src/parser.cpp)

configure_file(src/BuildConfig.h.in ../src/BuildConfig.h)