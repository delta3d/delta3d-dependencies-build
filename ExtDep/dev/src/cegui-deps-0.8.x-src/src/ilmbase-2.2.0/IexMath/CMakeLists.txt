# pstanczyk@ilm.com

#IF(BUILD_SHARED_LIBS)
#    ADD_DEFINITIONS(-DIEXMATH_EXPORTS)
#ENDIF()
#ADD_LIBRARY ( IexMath ${LIB_TYPE}
#  IexMathFloatExc.cpp  
#  IexMathFpu.cpp
#  )


set(SOURCES 
  IexMathFloatExc.cpp
  IexMathFpu.cpp)

cegui_add_library(IexMath SOURCES NONE)

if (WIN32)
    set_property(TARGET IexMath APPEND PROPERTY
       COMPILE_DEFINITIONS "IEXMATH_EXPORTS" "OPENEXR_DLL")
endif ()


TARGET_LINK_LIBRARIES(IexMath Iex)


INSTALL ( TARGETS
  IexMath IexMath_static
  DESTINATION
  lib
)

Set(HEADERS
  IexMathFloatExc.h  
  IexMathFpu.h  
  IexMathIeeeExc.h
)

INSTALL ( FILES ${HEADERS}
  DESTINATION
  include/OpenEXR
)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET IexMath POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_CURRENT_SOURCE_DIR}/${_H_FILE}"
       "${CMAKE_BINARY_DIR}/dependencies/include/OpenEXR")
endforeach()

