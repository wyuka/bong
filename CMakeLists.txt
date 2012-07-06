option(BUILD_TESTS "Build tests" on)

project(bong)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(GLIB2 REQUIRED)
find_package(GObject REQUIRED)

link_directories (${CMAKE_BINARY_DIR}/src)

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)
