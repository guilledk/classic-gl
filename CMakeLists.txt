cmake_minimum_required(VERSION 3.10)

# Project name
project(classic_gl)

# C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories("src/include")

add_executable(classic_gl_app ${SOURCES})

add_subdirectory(libs)

file(COPY "${CMAKE_SOURCE_DIR}/res" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/src/shaders" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/manifest.json" DESTINATION "${CMAKE_BINARY_DIR}")
