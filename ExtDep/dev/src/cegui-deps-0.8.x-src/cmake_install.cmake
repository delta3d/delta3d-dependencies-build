# Install script for directory: /Users/david/development/ext/src/cegui-deps-0.8.x-src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/zlib-1.2.5/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/libpng-1.4.7/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/jpeg-8c/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/libmng-1.0.10/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/tiff-3.9.5/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/freetype-2.4.4/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/lua-5.1.4/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/expat-2.0.1/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/xerces-c-3.1.1/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/SILLY/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/glew-1.7.0/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/glfw-2.7.2/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/glm-0.9.3.1/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/tolua++-1.0.93/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/ode-0.12/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/cppunit-1.13.1/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/HawkNL1.68/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/gnelib-0_70/CEGUI-BUILD/cmake_install.cmake")
  INCLUDE("/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/cal3d-trunk/CEGUI-BUILD/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/Users/david/development/ext/src/cegui-deps-0.8.x-src/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/Users/david/development/ext/src/cegui-deps-0.8.x-src/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
