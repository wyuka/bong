option(BUILD_DTD_TESTS "Build tests for Mozilla DTD backend" on)
option(BUILD_PROPERTIES_TESTS "Build tests for Mozilla Properties backend" on)
option(BUILD_QT_PROPERTIES_TESTS "Build tests for Qt wrapper for the Mozilla Properties backend" on)

include_directories(
    ${GOBJECT_INCLUDE_DIR}
    ${GLIB2_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    )

if(BUILD_PROPERTIES_TESTS)

    include_directories(${CMAKE_SOURCE_DIR}/src/plugins/properties)
    set(test_translatable_SRCS test_translatable.c)
    add_executable(test_translatable ${test_translatable_SRCS})
    target_link_libraries(test_translatable ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} bong bong-properties)

    set(test_properties_SRCS test_properties.c)
    add_executable(test_properties ${test_properties_SRCS})
    target_link_libraries(test_properties ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} bong bong-properties)

    set(test_properties_2_SRCS test_properties_2.c)
    add_executable(test_properties_2 ${test_properties_2_SRCS})
    target_link_libraries(test_properties_2 ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} bong bong-properties)

endif(BUILD_PROPERTIES_TESTS)

if(BUILD_DTD_TESTS)

    include_directories(${CMAKE_SOURCE_DIR}/src/plugins/dtd)
    set(test_dtd_SRCS test_dtd.c)
    add_executable(test_dtd ${test_dtd_SRCS})
    target_link_libraries(test_dtd ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} bong bong-dtd)

endif(BUILD_DTD_TESTS)

if(BUILD_QT_PROPERTIES_TESTS)

    find_package(Qt4 REQUIRED)

    include_directories(${CMAKE_SOURCE_DIR}/src/plugins/properties/qt ${CMAKE_SOURCE_DIR}/src/qt)
    set(test_qt_properties_SRCS test_qt_properties.cpp)
    add_executable(test_qt_properties ${test_qt_properties_SRCS})
    target_link_libraries(test_qt_properties ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} ${QT_QTCORE_LIBRARY} bong bongqt bong-properties bongqt-properties)

endif(BUILD_QT_PROPERTIES_TESTS)