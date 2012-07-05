project(bong)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(GLIB2 REQUIRED)
find_package(GObject REQUIRED)

include_directories(${GOBJECT_INCLUDE_DIR} ${GLIB2_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR} )

add_subdirectory(src)
add_subdirectory(tests)
