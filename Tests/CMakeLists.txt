cmake_minimum_required(VERSION 3.5)

project(tests CXX)

enable_testing()
find_package(GTest REQUIRED)

file(GLOB_RECURSE SOURCES . source/*.cpp)

add_executable(tests ${SOURCES}) 

target_include_directories(tests PUBLIC "./include")

target_link_libraries(tests PUBLIC reglib GTest::GTest GTest::Main)


add_test(CommonTestsAll tests)