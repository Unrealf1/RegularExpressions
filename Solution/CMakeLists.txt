cmake_minimum_required(VERSION 3.5)

project(solution CXX)

file(GLOB_RECURSE SOURCES . source/*.cpp)

add_executable(solution ${SOURCES}) 

target_include_directories(solution PUBLIC "./include")

target_link_libraries(solution PUBLIC reglib)