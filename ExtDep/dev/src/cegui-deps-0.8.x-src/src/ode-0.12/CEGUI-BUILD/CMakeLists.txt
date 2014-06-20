set(DEPNAME ode)

file(GLOB GI_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../GIMPACT/src/*.c*")
file(GLOB OP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../OPCODE/*.c*")
file(GLOB OPICE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../OPCODE/Ice/*.c*")
file(GLOB CCD_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../libccd/src/*.c*")
file(GLOB OU_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../ou/src/*.c*")
file(GLOB ODE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../ode/src/*.c*")
file(GLOB ODE2_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "../ode/src/joints/*.c*")

set(SOURCES ${GI_SOURCES} ${OP_SOURCES} ${OPICE_SOURCES} ${ODE_SOURCES} ${ODE2_SOURCES} ${CCD_SOURCES} ${OU_SOURCES})

message (${SOURCES})

set(HEADERS 
collision.h
collision_space.h
collision_trimesh.h
common.h
compatibility.h
contact.h
error.h
export-dif.h
mass.h
matrix.h
memory.h
misc.h
objects.h
ode.h
odeconfig.h
odecpp.h
odecpp_collision.h
odeinit.h
odemath.h
odemath_legacy.h
rotation.h
timer.h)

include_directories(../include ../GIMPACT/include ../OPCODE ../ode/src ../libccd/src ../ou/include)

cegui_add_library(${DEPNAME} SOURCES NONE)

set_property(TARGET ${DEPNAME} APPEND PROPERTY
    COMPILE_DEFINITIONS "dSINGLE;HAVE_CONFIG_H;__ODE__;dTRIMESH_ENABLED;dTRIMESH_OPCODE")

set_target_properties(${DEPNAME}_static PROPERTIES
    COMPILE_DEFINITIONS "dSINGLE;HAVE_CONFIG_H;__ODE__;dTRIMESH_ENABLED;dTRIMESH_OPCODE")

MAKE_DIRECTORY("${CMAKE_BINARY_DIR}/dependencies/include/ode/")

foreach(_H_FILE ${HEADERS})
    message(${_H_FILE})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../include/ode/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/ode/${_H_FILE}")
endforeach()


add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE.TXT" "${CMAKE_BINARY_DIR}/dependencies/ode-license.txt")

