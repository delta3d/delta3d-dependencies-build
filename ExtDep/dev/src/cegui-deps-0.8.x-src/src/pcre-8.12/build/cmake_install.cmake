# Install script for directory: /Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/libpcre.a")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpcre.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpcre.a")
    EXECUTE_PROCESS(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpcre.a")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/libpcreposix.a")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpcreposix.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpcreposix.a")
    EXECUTE_PROCESS(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpcreposix.a")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/libpcrecpp.a")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpcrecpp.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpcrecpp.a")
    EXECUTE_PROCESS(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpcrecpp.a")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/pcregrep")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcregrep" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcregrep")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcregrep")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/pcretest")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcretest" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcretest")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcretest")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/pcrecpp_unittest")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcrecpp_unittest" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcrecpp_unittest")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcrecpp_unittest")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/pcre_scanner_unittest")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcre_scanner_unittest" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcre_scanner_unittest")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcre_scanner_unittest")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/pcre_stringpiece_unittest")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcre_stringpiece_unittest" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcre_stringpiece_unittest")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/pcre_stringpiece_unittest")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/pcre.h"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/pcreposix.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/pcrecpp.h"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/pcre_scanner.h"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/pcrecpparg.h"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/pcre_stringpiece.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/man/man1" TYPE FILE FILES
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre-config.1"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcregrep.1"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcretest.1"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/man/man3" TYPE FILE FILES
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_compile.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_compile2.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_config.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_copy_named_substring.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_copy_substring.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_dfa_exec.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_exec.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_free_substring.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_free_substring_list.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_fullinfo.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_get_named_substring.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_get_stringnumber.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_get_stringtable_entries.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_get_substring.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_get_substring_list.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_info.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_maketables.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_refcount.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_study.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcre_version.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcreapi.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcrebuild.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcrecallout.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcrecompat.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcrecpp.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcrematching.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcrepartial.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcrepattern.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcreperform.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcreposix.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcreprecompile.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcresample.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcrestack.3"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/pcresyntax.3"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/pcre/html" TYPE FILE FILES
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/index.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre-config.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_compile.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_compile2.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_config.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_copy_named_substring.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_copy_substring.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_dfa_exec.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_exec.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_free_substring.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_free_substring_list.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_fullinfo.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_get_named_substring.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_get_stringnumber.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_get_stringtable_entries.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_get_substring.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_get_substring_list.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_info.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_maketables.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_refcount.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_study.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcre_version.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcreapi.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcrebuild.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcrecallout.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcrecompat.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcrecpp.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcredemo.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcregrep.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcrematching.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcrepartial.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcrepattern.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcreperform.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcreposix.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcreprecompile.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcresample.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcrestack.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcresyntax.html"
    "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/doc/html/pcretest.html"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/Users/david/development/ext/src/cegui-deps-0.8.x-src/src/pcre-8.12/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
