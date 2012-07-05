find_package(Bong REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR} ${BONG_INCLUDE_DIR})

set(test_translatable_SRCS test_translatable.c)
add_executable(test_translatable ${test_translatable_SRCS})
target_link_libraries(test_translatable ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} ${BONG_LIBRARIES})

set(test_properties_SRCS test_properties.c)
add_executable(test_properties ${test_properties_SRCS})
target_link_libraries(test_properties ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} ${BONG_LIBRARIES})

set(test_dtd_SRCS test_dtd.c)
add_executable(test_dtd ${test_dtd_SRCS})
target_link_libraries(test_dtd ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} ${BONG_LIBRARIES})