cmake_minimum_required(VERSION 3.17)
project(JACE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-march=native")

file(GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "sources/*/*.cpp")

add_executable(JACE sources/main.cpp ${SOURCES})

target_include_directories(JACE PRIVATE ${PROJECT_SOURCE_DIR}/include/)

find_package(Threads REQUIRED)
target_link_libraries(JACE PRIVATE Threads::Threads)
