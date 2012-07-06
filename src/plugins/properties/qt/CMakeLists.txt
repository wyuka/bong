SET(    bongqt_properties_SRC
        propertiesfiletypeqt.cpp
    )

SET(    bongqt_properties_HEADERS
        propertiesfiletypeqt.hpp
        bongqt_properties_export.hpp
   )

include_directories(
    ${GOBJECT_INCLUDE_DIR}
    ${GLIB2_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/qt
    ${CMAKE_SOURCE_DIR}/src/plugins/properties
    )

link_directories (${CMAKE_BINARY_DIR}/src)

add_library(bongqt-properties SHARED ${bongqt_properties_SRC})
target_link_libraries(bongqt-properties ${GLIB_LIBRARIES} ${GOBJECT_LIBRARIES} ${QT_QTCORE_LIBRARY} bong bong-properties)

set_target_properties(bongqt-properties PROPERTIES VERSION "0.0.0" SOVERSION "0" LINK_INTERFACE_LIBRARIES "" DEFINE_SYMBOL BUILDING_BONGQT_PROPERTIES)

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )

install( TARGETS bongqt-properties DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} )

install( FILES
         ${bongqt_properties_HEADERS}
         DESTINATION ${CMAKE_INSTALL_PREFIX}/include/bong COMPONENT devel
         )

set(INCLUDE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include/bong)
get_target_property(LIB_OUT_NAME bongqt-properties LOCATION)
get_filename_component(LIB_OUT_NAME ${LIB_OUT_NAME} NAME)
set(LIBPATH ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})

configure_file(
   BongQtPropertiesConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/BongQtPropertiesConfig.cmake @ONLY
)

install( FILES
         ${CMAKE_CURRENT_BINARY_DIR}/BongQtPropertiesConfig.cmake
     DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/cmake/BongQtProperties
)
