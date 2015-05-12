# Install script for directory: /Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/dependencies/include/OpenEXR/IlmBaseConfig.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/IlmBase.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Half/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Iex/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/IexMath/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/Imath/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/IlmThread/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/HalfTest/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/IexTest/cmake_install.cmake")
  include("/Users/david/development/ExtDepSrc/cegui-deps-0.8.x-src/src/ilmbase-2.2.0/ImathTest/cmake_install.cmake")

endif()

