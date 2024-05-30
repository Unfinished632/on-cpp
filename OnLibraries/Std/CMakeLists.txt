cmake_minimum_required(VERSION 2.8)

project (Std)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Std SHARED src/std.cpp)