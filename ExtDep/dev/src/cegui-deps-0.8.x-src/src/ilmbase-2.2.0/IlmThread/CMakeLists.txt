# yue.nicholas@gmail.com

SET( ILMTHREAD_LIBRARY_SOURCES
  IlmThread.cpp
  IlmThreadMutex.cpp
  IlmThreadMutexPosix.cpp
  IlmThreadPool.cpp
  IlmThreadPosix.cpp
  IlmThreadSemaphore.cpp
  IlmThreadSemaphorePosixCompat.cpp
  IlmThreadSemaphorePosix.cpp
)
IF (WIN32)
  SET( ILMTHREAD_LIBRARY_SOURCES ${ILMTHREAD_LIBRARY_SOURCES}
    IlmThreadMutexWin32.cpp
    IlmThreadSemaphoreWin32.cpp
    IlmThreadWin32.cpp
	)
ENDIF()

set(SOURCES ${ILMTHREAD_LIBRARY_SOURCES})

cegui_add_library(IlmThread SOURCES NONE)

if (WIN32)
    set_property(TARGET IlmThread APPEND PROPERTY
       COMPILE_DEFINITIONS "ILMTHREAD_EXPORTS")
endif ()


#IF(BUILD_SHARED_LIBS)
#  ADD_DEFINITIONS(-DILMTHREAD_EXPORTS)
#ENDIF()

#ADD_LIBRARY ( IlmThread ${LIB_TYPE}
#  ${ILMTHREAD_LIBRARY_SOURCES}
#  )

TARGET_LINK_LIBRARIES(IlmThread Iex)

INSTALL ( TARGETS
  IlmThread IlmThread_static
  DESTINATION
  lib
)

Set(HEADERS
  IlmThreadPool.h
  IlmThread.h
  IlmThreadSemaphore.h
  IlmThreadMutex.h
  IlmThreadNamespace.h
  IlmThreadExport.h
  IlmThreadForward.h
)

INSTALL ( FILES 
  ${HEADERS}
  DESTINATION
  include/OpenEXR
)

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET IlmThread POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_CURRENT_SOURCE_DIR}/${_H_FILE}"
       "${CMAKE_BINARY_DIR}/dependencies/include/OpenEXR")
endforeach()