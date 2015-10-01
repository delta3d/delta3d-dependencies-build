FILE( GLOB GNE_CXX_SRCS *.cpp )
FILE( GLOB GNE_C_SRCS *.c )
FILE( GLOB GNE_HEADERS ${GNE_INCLUDE_DIR}/gnelib/*.h )

SET( GNELIB_SRCS ${GNE_CXX_SRCS} ${GNE_C_SRCS} )

ADD_LIBRARY( gnelib STATIC ${GNELIB_SRCS} )
TARGET_LINK_LIBRARIES( gnelib ${CURSES_LIBRARY} ${HAWKNL_LIBRARY} )

SET_SOURCE_FILES_PROPERTIES(
    ${GNELIB_SRCS} PROPERTIES COMPILE_FLAGS "${GNE_COMMON_FLAGS}" )

INSTALL( TARGETS gnelib
         ARCHIVE DESTINATION lib )
#Old 2.2.x and earlier command
#INSTALL_TARGETS( /lib gnelib )

IF ( UNIX )
    ADD_LIBRARY( gnelib_so SHARED ${GNELIB_SRCS} )
    TARGET_LINK_LIBRARIES( gnelib_so ${CURSES_LIBRARY} ${HAWKNL_LIBRARY} )
    SET_TARGET_PROPERTIES(
        gnelib_so PROPERTIES
        VERSION ${GNE_VERSION}
        SOVERSION ${GNE_SO_VERSION}
        OUTPUT_NAME gnelib
        LINK_FLAGS "${GNE_LINKER_FLAGS}" )

    INSTALL( TARGETS gnelib_so
             LIBRARY DESTINATION lib )
ENDIF( UNIX )

IF( GNE_BUILD_DOCS )
    IF( GNE_USE_DOT )
        SET( GNE_USE_DOT_YN YES )
    ELSE( GNE_USE_DOT )
        SET( GNE_USE_DOT_YN NO )
    ENDIF( GNE_USE_DOT )

    CONFIGURE_FILE(
        ${CMAKE_SOURCE_DIR}/Doxyfile.in
        ${CMAKE_BINARY_DIR}/Doxyfile
        @ONLY
        )

    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_BINARY_DIR}/docs/build-stamp
        COMMAND ${DOXYGEN} ${CMAKE_BINARY_DIR}/Doxyfile
        COMMAND ${CMAKE_COMMAND} -E echo "built!" > ${CMAKE_BINARY_DIR}/docs/build-stamp
        DEPENDS ${GNELIB_SRCS}
                ${GNE_HEADERS}
                ${CMAKE_CURRENT_SOURCE_DIR}/mainpage
                ${CMAKE_CURRENT_SOURCE_DIR}/groups
                ${CMAKE_BINARY_DIR}/Doxyfile
        COMMENT "Builds the GNE documentation"
        )

    ADD_CUSTOM_TARGET(
        gnedocs ALL
        DEPENDS ${CMAKE_BINARY_DIR}/docs/build-stamp
        )

    FILE( MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/docs )

    INSTALL(
        DIRECTORY ${CMAKE_BINARY_DIR}/docs
        DESTINATION share/${GNE_PACKAGE_NAME}
        PATTERN "build-stamp" EXCLUDE )

ENDIF( GNE_BUILD_DOCS )

