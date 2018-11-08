cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Practice1 CXX)

option(WITH_TESTS "Build with tests and run them" ON)

add_subdirectory("./reglib")
add_subdirectory("./Solution")

if(WITH_TESTS)
	add_subdirectory("./Tests")
endif(WITH_TESTS)
