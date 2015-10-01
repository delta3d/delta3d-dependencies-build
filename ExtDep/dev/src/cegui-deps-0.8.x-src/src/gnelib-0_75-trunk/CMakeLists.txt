CMAKE_MINIMUM_REQUIRED( VERSION 2.4 )
PROJECT( GNE CXX C )

#Set up GNE version information
SET( GNE_MAJOR_VERSION 0 )
SET( GNE_MINOR_VERSION 75 )
SET( GNE_MICRO_VERSION 0 )

SET( GNE_SO_VERSION 0 )

SET( GNE_VERSION "${GNE_MAJOR_VERSION}.${GNE_MINOR_VERSION}.${GNE_MICRO_VERSION}" )

SET( GNE_VERSION_STR "GNE ${GNE_VERSION}-Development" )

MESSAGE( STATUS "GNE Version ${GNE_VERSION_STR}" )

SET( GNE_PACKAGE_NAME "libgnelib-dev" )

#Set up build type and build options, including build flags
IF( NOT MSVC AND NOT CMAKE_BUILD_TYPE )
    SET( CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE )
ENDIF( NOT MSVC AND NOT CMAKE_BUILD_TYPE )

OPTION( GNE_EXTRA_DEBUG_MODE
    "If on, sets on GNE's debugging mode, which adds extra checks and asserts"
    OFF )

#Right now we support this only for GCC
IF ( CMAKE_COMPILER_IS_GNUCXX )
  OPTION( GNE_STRIP_RESULTS
    "If on, strips debugging symbols from generated binaries when linking"
    OFF )
ENDIF( CMAKE_COMPILER_IS_GNUCXX )

OPTION( GNE_BUILD_EXAMPLES
    "If on, builds the example programs, to be installed to /share/${GNE_PACKAGE_NAME}/examples"
    OFF )

OPTION( GNE_TESTS
    "If on, builds the test program, which is not installed but can be run via `make test`"
    OFF )

SET( GNE_COMMON_FLAGS "" ) #make sure this is defined

#Set compile flags to be used in common across all of our code.
IF( CMAKE_COMPILER_IS_GNUCXX )
    SET( GNE_COMMON_FLAGS "-Wall" )
ENDIF( CMAKE_COMPILER_IS_GNUCXX )
IF( MSVC )
    SET( GNE_COMMON_FLAGS "/W3 /D_CRT_SECURE_NO_DEPRECATE" )
ENDIF( MSVC )

IF( GNE_EXTRA_DEBUG_MODE )
    ADD_DEFINITIONS( -D_DEBUG )
ENDIF( GNE_EXTRA_DEBUG_MODE )

#This is probably only required on GCC or UNIX or anything using POSIX
#threads, but to be safe I always define it, since it shouldn't hurt on
#compilers that don't listen to this.
IF( NOT MSVC )
  ADD_DEFINITIONS( -D_REENTRANT )
ENDIF( NOT MSVC )

SET( GNE_LINKER_FLAGS "" ) #make sure this is defined

IF( GNE_STRIP_RESULTS )
    IF( CMAKE_COMPILER_IS_GNUCXX )
        SET( GNE_LINKER_FLAGS "-s" )
    ENDIF( CMAKE_COMPILER_IS_GNUCXX )
ENDIF( GNE_STRIP_RESULTS )

# Documentation Section -- Find and use Doxygen and Dot
# More documentation config can be found in src/CMakeLists.txt
FIND_PACKAGE( Doxygen )

IF( NOT DEFINED GNE_BUILD_DOCS )
    IF ( DOXYGEN_FOUND )
        MESSAGE( STATUS "Doxygen found at ${DOXYGEN}, so GNE_BUILD_DOCS set to ON" )
        SET( GNE_BUILD_DOCS_DEFAULT ON )
    ELSE( DOXYGEN_FOUND )
        MESSAGE( STATUS "Doxygen was not found, so GNE_BUILD_DOCS set to OFF" )
        SET( GNE_BUILD_DOCS_DEFAULT OFF )
    ENDIF( DOXYGEN_FOUND )

    OPTION( GNE_BUILD_DOCS
        "If on, builds the GNE documentation.  Requires Doxygen to do this."
        ${GNE_BUILD_DOCS_DEFAULT} )

ENDIF( NOT DEFINED GNE_BUILD_DOCS )

IF( NOT DEFINED GNE_USE_DOT )
    IF( DOXYGEN_DOT_FOUND )
        MESSAGE( STATUS "DOT tool was detected, so it will be used if GNE_BUILD_DOCS is set" )
        SET( GNE_USE_DOT_DEFAULT ON )
    ELSE( DOXYGEN_DOT_FOUND )
        MESSAGE( STATUS "DOT tool was not detected, so it will not be used if GNE_BUILD_DOCS is set" )
        SET( GNE_USE_DOT_DEFAULT OFF )
    ENDIF( DOXYGEN_DOT_FOUND )

    OPTION( GNE_USE_DOT
        "If set, uses dot when the documentation is built. Only matters if GNE_BUILD_DOCS is ON"
        ${GNE_USE_DOT_DEFAULT} )
ENDIF( NOT DEFINED GNE_USE_DOT )

#Library detection section: HawkNL, curses, and Boost

FIND_LIBRARY( HAWKNL_LIBRARY
    NAMES hawknl NL
    DOC "Path to the HawkNL shared object/DLL library" )

FIND_PATH( HAWKNL_INCLUDE_PATH
    nl.h
    DOC "Path that contains the HawkNL include file, nl.h" )

IF( IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/hawknl )
  #We've found an embedded version, so try to compile this.
  MESSAGE( STATUS "Detected embedded HawkNL installation; attempting to use" )
  ADD_SUBDIRECTORY( hawknl )
  SET( HAWKNL_INCLUDE_PATH hawknl/include
       CACHE STRING "Using embedded version" FORCE )
  SET( HAWKNL_LIBRARY hawknl
       CACHE STRING "Using embedded version" FORCE )
ENDIF( IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/hawknl )

IF( NOT HAWKNL_LIBRARY OR NOT HAWKNL_INCLUDE_PATH )
    MESSAGE( SEND_ERROR "The library HawkNL version 1.68 or higher was not found. You will need to set HAWKNL_LIBRARY and HAWKNL_INCLUDE_PATH manually. Or, you can place a copy of the CMake-buildable branch of HawkNL 1.68 or later in directory ${CMAKE_CURRENT_SOURCE_DIR}/hawknl" )
ENDIF( NOT HAWKNL_LIBRARY OR NOT HAWKNL_INCLUDE_PATH )

MESSAGE( STATUS "HawkNL: ${HAWKNL_LIBRARY} ${HAWKNL_INCLUDE_PATH}/nl.h" )

#Boost detection -- FindBoost is 2.4 or later only
FIND_PACKAGE( Boost REQUIRED )

#Curses detection
IF( UNIX )
    SET( CURSES_USE_NCURSES TRUE )
    FIND_PACKAGE( Curses REQUIRED )
ENDIF( UNIX )

#Set up global include paths
SET( GNE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include )
#Somewhere between CMake 2.4 and 2.8, The BOOST* variables became Boost*, and
#that breaks backwards-compatibility. So, we include both on the line below,
#expecting that one of them won't be defined.
INCLUDE_DIRECTORIES( ${GNE_INCLUDE_DIR} ${BOOST_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${HAWKNL_INCLUDE_PATH} ${CURSES_INCLUDE_PATH} )


ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( include )

IF( GNE_BUILD_EXAMPLES )
  ADD_SUBDIRECTORY( examples )
ENDIF( GNE_BUILD_EXAMPLES )

IF( GNE_TESTS )
  ADD_SUBDIRECTORY( tests )
ENDIF( GNE_TESTS )
