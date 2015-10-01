# yue.nicholas@gmail.com

#IF(BUILD_SHARED_LIBS)
#    ADD_DEFINITIONS(-DIMATH_EXPORTS)
#ENDIF()

#ADD_LIBRARY ( Imath ${LIB_TYPE}
set (SOURCES
  ImathBox.cpp
  ImathRandom.cpp
  ImathColorAlgo.cpp
  ImathShear.cpp
  ImathFun.cpp
  ImathVec.cpp
  ImathMatrixAlgo.cpp
)

set(HEADERS
  ImathBoxAlgo.h
  ImathBox.h
  ImathColorAlgo.h
  ImathColor.h
  ImathEuler.h
  ImathExc.h
  ImathExport.h
  ImathForward.h
  ImathFrame.h
  ImathFrustum.h
  ImathFrustumTest.h
  ImathFun.h
  ImathGL.h
  ImathGLU.h
  ImathHalfLimits.h
  ImathInt64.h
  ImathInterval.h
  ImathLimits.h
  ImathLineAlgo.h
  ImathLine.h
  ImathMath.h
  ImathMatrixAlgo.h
  ImathMatrix.h
  ImathNamespace.h
  ImathPlane.h
  ImathPlatform.h
  ImathQuat.h
  ImathRandom.h
  ImathRoots.h
  ImathShear.h
  ImathSphere.h
  ImathVecAlgo.h
  ImathVec.h
)

SET(SOURCES ${SOURCES} ${HEADERS})

cegui_add_library(Imath SOURCES NONE)

if (WIN32)
    set_property(TARGET Imath APPEND PROPERTY
       COMPILE_DEFINITIONS "IMATH_EXPORTS" "OPENEXR_DLL")
endif ()

TARGET_LINK_LIBRARIES(Imath Iex)


INSTALL ( TARGETS
  Imath
  DESTINATION
  lib
)

INSTALL ( FILES 
  ${HEADERS}
  DESTINATION
  include/OpenEXR
)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET Imath POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_CURRENT_SOURCE_DIR}/${_H_FILE}"
       "${CMAKE_BINARY_DIR}/dependencies/include/OpenEXR")
endforeach()
