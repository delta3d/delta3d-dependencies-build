# Install script for directory: /Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./stage/include/OpenEXR" TYPE FILE FILES "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/config/OpenEXRConfig.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./stage/share/doc/OpenEXR-2.2.0" TYPE FILE FILES
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/TechnicalIntroduction.pdf"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/ReadingAndWritingImageFiles.pdf"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/OpenEXRFileLayout.pdf"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/MultiViewOpenEXR.pdf"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/InterpretingDeepPixels.pdf"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/TheoryDeepPixels.pdf"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./stage/share/doc/OpenEXR-2.2.0/examples" TYPE FILE FILES
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/main.cpp"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/drawImage.cpp"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/rgbaInterfaceExamples.cpp"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/rgbaInterfaceTiledExamples.cpp"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/generalInterfaceExamples.cpp"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/lowLevelIoExamples.cpp"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/previewImageExamples.cpp"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/generalInterfaceTiledExamples.cpp"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/generalInterfaceTiledExamples.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/drawImage.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/rgbaInterfaceExamples.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/generalInterfaceExamples.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/rgbaInterfaceTiledExamples.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/lowLevelIoExamples.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/previewImageExamples.h"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/namespaceAlias.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImf/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtil/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfExamples/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfTest/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfUtilTest/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/IlmImfFuzzTest/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/exrheader/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/exrmaketiled/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/exrstdattr/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/exrmakepreview/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/exrenvmap/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/exrmultiview/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/exrmultipart/cmake_install.cmake")

endif()

