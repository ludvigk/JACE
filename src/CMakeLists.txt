cmake_minimum_required(VERSION 3.16)
project(JACE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-march=native")

file(GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "sources/*/*.cpp")

add_library(JACE_lib STATIC ${SOURCES})
add_executable(JACE sources/main.cpp)
add_executable(JACE_tests sources/test.cpp)

set_target_properties(JACE_lib PROPERTIES OUTPUT_NAME JACE)

target_include_directories(JACE_lib PRIVATE ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(JACE PRIVATE ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(JACE_tests PRIVATE ${PROJECT_SOURCE_DIR}/include/)

find_package(Threads REQUIRED)
find_package(Catch2 REQUIRED)

target_link_libraries(JACE_lib PRIVATE Threads::Threads)
target_link_libraries(JACE PRIVATE JACE_lib)
target_link_libraries(JACE_tests PRIVATE JACE_lib)
target_link_libraries(JACE_tests PRIVATE Catch2::Catch2)
