# Install script for directory: /Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "./stage")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./stage/lib" TYPE SHARED_LIBRARY FILES
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/libIlmImfUtil.22.0.0.dylib"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/libIlmImfUtil.22.dylib"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/libIlmImfUtil.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./stage/lib/libIlmImfUtil.22.0.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./stage/lib/libIlmImfUtil.22.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./stage/lib/libIlmImfUtil.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/../IlmImf"
        "${file}")
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./stage/include/OpenEXR" TYPE FILE FILES
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfImageChannel.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfFlatImageChannel.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfDeepImageChannel.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfSampleCountChannel.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfImageLevel.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfFlatImageLevel.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfDeepImageLevel.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfImage.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfFlatImage.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfDeepImage.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfImageIO.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfFlatImageIO.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfDeepImageIO.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfImageDataWindow.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/ImfImageChannelRenaming.h"
    )
endif()

