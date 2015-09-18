set(DEPNAME NL)


set(SOURCES
../src/crc.c 
../src/errorstr.c 
../src/nl.c 
../src/sock.c 
../src/group.c
../src/loopback.c 
../src/err.c 
../src/thread.c
../src/mutex.c
../src/condition.c
../src/nltime.c
)

if(MSVC)
   set(SOURCESWIN "../src/ipx.c")
   list(APPEND SOURCES ${SOURCESWIN})
endif()

set(HEADERS 
nl.h
)

include_directories(../include)

cegui_add_library(${DEPNAME} SOURCES NONE)

if (APPLE)
    set_property(TARGET ${DEPNAME} APPEND PROPERTY
       COMPILE_DEFINITIONS "_REENTRANT;MACOSX")
    set_target_properties(${DEPNAME}_static PROPERTIES
       COMPILE_DEFINITIONS "_REENTRANT;MACOSX")
elseif (WIN32 OR WIN64)
    target_link_libraries(${DEPNAME} wsock32)
endif ()

foreach(_H_FILE ${HEADERS})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../include/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${_H_FILE}")
endforeach()

#No license file
#add_custom_command(TARGET ${DEPNAME} POST_BUILD 
#                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../COPYING" "${CMAKE_BINARY_DIR}/dependencies/${DEPNAME}-license.txt")
