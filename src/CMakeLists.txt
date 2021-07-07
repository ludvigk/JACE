cmake_minimum_required(VERSION 3.16)
project(JACE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-march=native")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

file(GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "sources/*/*.cpp")

add_executable(JACE sources/main.cpp ${SOURCES})
add_executable(JACE_tests sources/test.cpp ${SOURCES})

target_include_directories(JACE PRIVATE ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(JACE_tests PRIVATE ${PROJECT_SOURCE_DIR}/include/)


find_package(Threads REQUIRED)
find_package(Catch2 REQUIRED)

target_link_libraries(JACE PRIVATE Threads::Threads)
target_link_libraries(JACE_tests PRIVATE Threads::Threads)

target_link_libraries(JACE_tests PRIVATE Catch2::Catch2)
