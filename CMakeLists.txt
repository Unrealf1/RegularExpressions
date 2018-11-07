cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Practice1)

file(GLOB_RECURSE SOURCES . source/*.cpp)

add_executable(Practice1 ${SOURCES})

target_include_directories(Practice1 PUBLIC "./include")
