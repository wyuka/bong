SET(    bong_SRC
        translatable.c
        filetype.c
        dtdfiletype.c
        propertiesfiletype.c
        hashvalue.c
        localestring.c
        utils.c
    )

SET(    bong_HEADERS
        translatable.h
        dtdfiletype.h
        propertiesfiletype.h
   )

add_library(bong SHARED ${bong_SRC})
target_link_libraries(bong ${GLIB_LIBRARIES} ${GOBJECT_LIBRARIES})

set_target_properties(bong PROPERTIES VERSION "0.0.0" SOVERSION "0" LINK_INTERFACE_LIBRARIES "" DEFINE_SYMBOL BUILDING_BONG)

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )

install( TARGETS bong DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} )

install( FILES
         ${bong_HEADERS}
         DESTINATION ${CMAKE_INSTALL_PREFIX}/include/bong COMPONENT devel
         )

set(INCLUDE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include/bong)
get_target_property(LIB_OUT_NAME bong LOCATION)
get_filename_component(LIB_OUT_NAME ${LIB_OUT_NAME} NAME)
set(LIBPATH ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})

configure_file(
   BongConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/BongConfig.cmake @ONLY
)

install( FILES
         ${CMAKE_CURRENT_BINARY_DIR}/BongConfig.cmake
	 DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/cmake/Bong
)



