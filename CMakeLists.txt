cmake_minimum_required(VERSION 3.25)

project(screenshot)
add_executable(screenshot main.cpp)
message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

find_package(X11 REQUIRED)
message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})
