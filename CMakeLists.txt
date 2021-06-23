cmake_minimum_required(VERSION 2.8)
project(mipt-flat-prac1)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage --coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

include_directories(${PROJECT_SOURCE_DIR})

find_package(GTest REQUIRED)

if(NOT GTest_FOUND)
  message(SEND_ERROR "Failed to find gtest library")
  return()
else()
  include_directories(${GTEST_INCLUDE_DIRS})
endif()

add_library(F16 SHARED F16.h F16.cpp)
add_executable(MainTest main_test.cpp)
add_executable(main main.cpp)
target_link_libraries(main F16)
target_link_libraries(MainTest F16)
target_link_libraries(MainTest ${GTEST_LIBRARIES} pthread)

enable_testing()
