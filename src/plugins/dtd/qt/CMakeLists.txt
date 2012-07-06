SET(    bongqt_dtd_SRC
        dtdfiletypeqt.cpp
    )

SET(    bongqt_dtd_HEADERS
        dtdfiletypeqt.hpp
        bongqt_dtd_export.hpp
   )

include_directories(
    ${GOBJECT_INCLUDE_DIR}
    ${GLIB2_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/qt
    ${CMAKE_SOURCE_DIR}/src/plugins/dtd
    )

link_directories (${CMAKE_BINARY_DIR}/src)

add_library(bongqt-dtd SHARED ${bongqt_dtd_SRC})
target_link_libraries(bongqt-dtd ${GLIB_LIBRARIES} ${GOBJECT_LIBRARIES} ${QT_QTCORE_LIBRARY} bong bong-dtd)

set_target_properties(bongqt-dtd PROPERTIES VERSION "0.0.0" SOVERSION "0" LINK_INTERFACE_LIBRARIES "" DEFINE_SYMBOL BUILDING_BONGQT_DTD)

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )

install( TARGETS bongqt-dtd DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} )

install( FILES
         ${bongqt_dtd_HEADERS}
         DESTINATION ${CMAKE_INSTALL_PREFIX}/include/bong COMPONENT devel
         )

set(INCLUDE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include/bong)
get_target_property(LIB_OUT_NAME bongqt-dtd LOCATION)
get_filename_component(LIB_OUT_NAME ${LIB_OUT_NAME} NAME)
set(LIBPATH ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})

configure_file(
   BongQtDtdConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/BongQtDtdConfig.cmake @ONLY
)

install( FILES
         ${CMAKE_CURRENT_BINARY_DIR}/BongQtDtdConfig.cmake
     DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/cmake/BongQtDtd
)
