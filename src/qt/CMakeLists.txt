SET(    bongqt_SRC
        translatableqt.cpp
    )

SET(    bongqt_HEADERS
        translatableqt.hpp
        filetypeqt.hpp
        bonqt_export.hpp
   )

include_directories(
    ${GOBJECT_INCLUDE_DIR}
    ${GLIB2_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${QT_INCLUDES}
    )

link_directories (${CMAKE_BINARY_DIR}/src)

add_library(bongqt SHARED ${bongqt_SRC})
target_link_libraries(bongqt ${GLIB_LIBRARIES} ${GOBJECT_LIBRARIES} ${QT_QTCORE_LIBRARY} bong)

set_target_properties(bongqt PROPERTIES VERSION "0.0.0" SOVERSION "0" LINK_INTERFACE_LIBRARIES "" DEFINE_SYMBOL BUILDING_BONGQT)

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )

install( TARGETS bongqt DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} )

install( FILES
         ${bongqt_HEADERS}
         DESTINATION ${CMAKE_INSTALL_PREFIX}/include/bong COMPONENT devel
         )

set(INCLUDE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include/bong)
get_target_property(LIB_OUT_NAME bongqt LOCATION)
get_filename_component(LIB_OUT_NAME ${LIB_OUT_NAME} NAME)
set(LIBPATH ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})

configure_file(
   BongQtConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/BongQtConfig.cmake @ONLY
)

install( FILES
         ${CMAKE_CURRENT_BINARY_DIR}/BongQtConfig.cmake
     DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/cmake/BongQt
)