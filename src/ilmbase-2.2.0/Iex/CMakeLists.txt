# yue.nicholas@gmail.com

#IF(BUILD_SHARED_LIBS)
#    ADD_DEFINITIONS(-DIEX_EXPORTS)
#ENDIF()

#ADD_LIBRARY ( Iex ${LIB_TYPE}
#  IexBaseExc.cpp
#  IexThrowErrnoExc.cpp
#  )


set(SOURCES IexBaseExc.cpp
  IexThrowErrnoExc.cpp)

cegui_add_library(Iex SOURCES NONE)

if (WIN32)
    set_property(TARGET Iex APPEND PROPERTY
       COMPILE_DEFINITIONS "IEX_EXPORTS")
endif ()

INSTALL ( TARGETS
  Iex Iex_static
  DESTINATION
  lib
)

Set(HEADERS
  IexBaseExc.h
  IexMathExc.h
  IexThrowErrnoExc.h
  IexErrnoExc.h
  IexMacros.h
  Iex.h
  IexNamespace.h
  IexExport.h
  IexForward.h
)

INSTALL ( FILES ${HEADERS}
  DESTINATION
  include/OpenEXR
)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET Iex POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_CURRENT_SOURCE_DIR}/${_H_FILE}"
       "${CMAKE_BINARY_DIR}/dependencies/include/OpenEXR")
endforeach()

