# Install script for directory: /Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/dependencies/lib/dynamic/libImath-2_2.12.0.0.dylib"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/dependencies/lib/dynamic/libImath-2_2.12.dylib"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/dependencies/lib/dynamic/libImath-2_2.dylib"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathBoxAlgo.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathBox.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathColorAlgo.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathColor.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathEuler.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathExc.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathExport.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathForward.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathFrame.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathFrustum.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathFrustumTest.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathFun.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathGL.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathGLU.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathHalfLimits.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathInt64.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathInterval.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathLimits.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathLineAlgo.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathLine.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathMath.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathMatrixAlgo.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathMatrix.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathNamespace.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathPlane.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathPlatform.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathQuat.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathRandom.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathRoots.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathShear.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathSphere.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathVecAlgo.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/ImathVec.h"
    )
endif()

