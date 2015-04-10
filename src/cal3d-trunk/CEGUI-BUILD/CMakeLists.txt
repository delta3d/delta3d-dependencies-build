set(DEPNAME cal3d)

set(SOURCES 
../cal3d/src/cal3d/animation.cpp
../cal3d/src/cal3d/animation_action.cpp
../cal3d/src/cal3d/animation_cycle.cpp
../cal3d/src/cal3d/animation_pose.cpp
../cal3d/src/cal3d/bone.cpp
../cal3d/src/cal3d/buffersource.cpp
../cal3d/src/cal3d/cal3d_wrapper.cpp
../cal3d/src/cal3d/calxmlbindings.cpp
../cal3d/src/cal3d/coreanimatedmorph.cpp
../cal3d/src/cal3d/coreanimation.cpp
../cal3d/src/cal3d/corebone.cpp
../cal3d/src/cal3d/corekeyframe.cpp
../cal3d/src/cal3d/corematerial.cpp
../cal3d/src/cal3d/coremesh.cpp
../cal3d/src/cal3d/coremodel.cpp
../cal3d/src/cal3d/coremorphkeyframe.cpp
../cal3d/src/cal3d/coremorphtrack.cpp
../cal3d/src/cal3d/coreskeleton.cpp
../cal3d/src/cal3d/coresubmesh.cpp
../cal3d/src/cal3d/coresubmorphtarget.cpp
../cal3d/src/cal3d/coretrack.cpp
../cal3d/src/cal3d/dualquaternion.cpp
../cal3d/src/cal3d/error.cpp
../cal3d/src/cal3d/global.cpp
../cal3d/src/cal3d/hardwaremodel.cpp
../cal3d/src/cal3d/loader.cpp
../cal3d/src/cal3d/matrix.cpp
../cal3d/src/cal3d/mesh.cpp
../cal3d/src/cal3d/mixer.cpp
../cal3d/src/cal3d/model.cpp
../cal3d/src/cal3d/morphtargetmixer.cpp
../cal3d/src/cal3d/physique.cpp
../cal3d/src/cal3d/physiquedualquaternion.cpp
../cal3d/src/cal3d/platform.cpp
../cal3d/src/cal3d/quaternion.cpp
../cal3d/src/cal3d/renderer.cpp
../cal3d/src/cal3d/saver.cpp
../cal3d/src/cal3d/skeleton.cpp
../cal3d/src/cal3d/springsystem.cpp
../cal3d/src/cal3d/streamsource.cpp
../cal3d/src/cal3d/submesh.cpp
../cal3d/src/cal3d/tinybind.cpp
../cal3d/src/cal3d/tinyxml.cpp
../cal3d/src/cal3d/tinyxmlerror.cpp
../cal3d/src/cal3d/tinyxmlparser.cpp
../cal3d/src/cal3d/vector.cpp
../cal3d/src/cal3d/xmlformat.cpp
)

set(HEADERS 
animation.h
animation_action.h
animation_cycle.h
animation_pose.h
animcallback.h
bone.h
buffersource.h
cal3d.h
cal3d_wrapper.h
calxmlbindings.h
coreanimatedmorph.h
coreanimation.h
corebone.h
corekeyframe.h
corematerial.h
coremesh.h
coremodel.h
coremorphkeyframe.h
coremorphtrack.h
coreskeleton.h
coresubmesh.h
coresubmorphtarget.h
coretrack.h
datasource.h
dualquaternion.h
error.h
global.h
hardwaremodel.h
loader.h
matrix.h
mesh.h
mixer.h
model.h
morphtargetmixer.h
physique.h
physiquedualquaternion.h
platform.h
quaternion.h
refcounted.h
refptr.h
renderer.h
resource.h
saver.h
skeleton.h
springsystem.h
streamsource.h
submesh.h
tinybind.h
tinyxml.h
transform.h
vector.h
xmlformat.h
)

include_directories(../cal3d/src)

cegui_add_library(${DEPNAME} SOURCES NONE)

if (MSVC)
    set_property(TARGET ${DEPNAME} APPEND PROPERTY
       COMPILE_DEFINITIONS "CAL3D_EXPORTS")
endif ()

#set_target_properties(${DEPNAME}_static PROPERTIES
#    COMPILE_DEFINITIONS "")

MAKE_DIRECTORY("${CMAKE_BINARY_DIR}/dependencies/include/${DEPNAME}/")

foreach(_H_FILE ${HEADERS})
    #message(${_H_FILE})
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${DEPNAME}/src/${DEPNAME}/${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${DEPNAME}/${_H_FILE}")
endforeach()


add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${DEPNAME}/COPYING" "${CMAKE_BINARY_DIR}/dependencies/${DEPNAME}-license.txt")


set(SOURCES_CAL3D_CONVERTER
    ../cal3d/src/cal3d_converter.cpp )
    
cegui_add_executable(cal3d_converter SOURCES_CAL3D_CONVERTER)
target_link_libraries(cal3d_converter cal3d_static)