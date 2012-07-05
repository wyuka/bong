include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR})

set(test1_SRCS test1.c)
add_executable(bong-test1 ${test1_SRCS})
target_link_libraries(bong-test1 ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} bong)
