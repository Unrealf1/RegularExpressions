cmake_minimum_required(VERSION 3.5)

project(reglib CXX)

file(GLOB_RECURSE SOURCES . source/*.cpp)

add_library(reglib STATIC ${SOURCES})

target_include_directories(reglib PUBLIC "./include")
target_include_directories(reglib PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

