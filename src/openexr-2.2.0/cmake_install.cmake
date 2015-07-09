# Install script for directory: /Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0

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
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/OpenEXR/OpenEXRConfig.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/OpenEXR" TYPE FILE FILES "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/config/OpenEXRConfig.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/doc/OpenEXR-2.2.0/TechnicalIntroduction.pdf;/usr/local/share/doc/OpenEXR-2.2.0/ReadingAndWritingImageFiles.pdf;/usr/local/share/doc/OpenEXR-2.2.0/OpenEXRFileLayout.pdf;/usr/local/share/doc/OpenEXR-2.2.0/MultiViewOpenEXR.pdf;/usr/local/share/doc/OpenEXR-2.2.0/InterpretingDeepPixels.pdf;/usr/local/share/doc/OpenEXR-2.2.0/TheoryDeepPixels.pdf")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/doc/OpenEXR-2.2.0" TYPE FILE FILES
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/TechnicalIntroduction.pdf"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/ReadingAndWritingImageFiles.pdf"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/OpenEXRFileLayout.pdf"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/MultiViewOpenEXR.pdf"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/InterpretingDeepPixels.pdf"
    "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/openexr-2.2.0/doc/TheoryDeepPixels.pdf"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/doc/OpenEXR-2.2.0/examples/main.cpp;/usr/local/share/doc/OpenEXR-2.2.0/examples/drawImage.cpp;/usr/local/share/doc/OpenEXR-2.2.0/examples/rgbaInterfaceExamples.cpp;/usr/local/share/doc/OpenEXR-2.2.0/examples/rgbaInterfaceTiledExamples.cpp;/usr/local/share/doc/OpenEXR-2.2.0/examples/generalInterfaceExamples.cpp;/usr/local/share/doc/OpenEXR-2.2.0/examples/lowLevelIoExamples.cpp;/usr/local/share/doc/OpenEXR-2.2.0/examples/previewImageExamples.cpp;/usr/local/share/doc/OpenEXR-2.2.0/examples/generalInterfaceTiledExamples.cpp;/usr/local/share/doc/OpenEXR-2.2.0/examples/generalInterfaceTiledExamples.h;/usr/local/share/doc/OpenEXR-2.2.0/examples/drawImage.h;/usr/local/share/doc/OpenEXR-2.2.0/examples/rgbaInterfaceExamples.h;/usr/local/share/doc/OpenEXR-2.2.0/examples/generalInterfaceExamples.h;/usr/local/share/doc/OpenEXR-2.2.0/examples/rgbaInterfaceTiledExamples.h;/usr/local/share/doc/OpenEXR-2.2.0/examples/lowLevelIoExamples.h;/usr/local/share/doc/OpenEXR-2.2.0/examples/previewImageExamples.h;/usr/local/share/doc/OpenEXR-2.2.0/examples/namespaceAlias.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/share/doc/OpenEXR-2.2.0/examples" TYPE FILE FILES
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
