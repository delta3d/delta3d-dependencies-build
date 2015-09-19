set(DEPNAME openvdb)

set(SOURCES 
../Grid.cc
../Platform.cc
#../cmd/openvdb_print/main.cc
#../cmd/openvdb_render/main.cc
#../cmd/openvdb_view/main.cc
../io/Archive.cc
../io/Compression.cc
../io/File.cc
../io/GridDescriptor.cc
../io/Queue.cc
../io/Stream.cc
../io/TempFile.cc
../math/Hermite.cc
../math/Maps.cc
../math/Proximity.cc
../math/QuantizedUnitVec.cc
../math/Transform.cc
../metadata/MetaMap.cc
../metadata/Metadata.cc
../openvdb.cc
../util/Formats.cc
../util/Util.cc
)


set(HEADERS 
../Exceptions.h
../Grid.h
../Metadata.h
../Platform.h
../PlatformConfig.h
../Types.h
../io/Archive.h
../io/Compression.h
../io/File.h
../io/GridDescriptor.h
../io/Queue.h
../io/Stream.h
../io/TempFile.h
../io/io.h
../math/BBox.h
../math/ConjGradient.h
../math/Coord.h
../math/DDA.h
../math/FiniteDifference.h
../math/Hermite.h
../math/LegacyFrustum.h
../math/Maps.h
../math/Mat.h
../math/Mat3.h
../math/Mat4.h
../math/Math.h
../math/Operators.h
../math/Proximity.h
../math/QuantizedUnitVec.h
../math/Quat.h
../math/Ray.h
../math/Stats.h
../math/Stencils.h
../math/Transform.h
../math/Tuple.h
../math/Vec2.h
../math/Vec3.h
../math/Vec4.h
../metadata/MetaMap.h
../metadata/Metadata.h
../metadata/StringMetadata.h
../openvdb.h
../tools/ChangeBackground.h
../tools/Clip.h
../tools/Composite.h
../tools/Dense.h
../tools/DenseSparseTools.h
../tools/Diagnostics.h
../tools/Filter.h
../tools/GridOperators.h
../tools/GridTransformer.h
../tools/Interpolation.h
../tools/LevelSetAdvect.h
../tools/LevelSetFilter.h
../tools/LevelSetFracture.h
../tools/LevelSetMeasure.h
../tools/LevelSetMorph.h
../tools/LevelSetRebuild.h
../tools/LevelSetSphere.h
../tools/LevelSetTracker.h
../tools/LevelSetUtil.h
../tools/MeshToVolume.h
../tools/Morphology.h
../tools/ParticlesToLevelSet.h
../tools/PointAdvect.h
../tools/PointIndexGrid.h
../tools/PointPartitioner.h
../tools/PointScatter.h
../tools/PoissonSolver.h
../tools/Prune.h
../tools/RayIntersector.h
../tools/RayTracer.h
../tools/SignedFloodFill.h
../tools/Statistics.h
../tools/ValueTransformer.h
../tools/VectorTransformer.h
../tools/VolumeToMesh.h
../tools/VolumeToSpheres.h
../tree/InternalNode.h
../tree/Iterator.h
../tree/LeafManager.h
../tree/LeafNode.h
../tree/LeafNodeBool.h
../tree/NodeManager.h
../tree/NodeUnion.h
../tree/RootNode.h
../tree/Tree.h
../tree/TreeIterator.h
../tree/ValueAccessor.h
../util/CpuTimer.h
../util/Formats.h
../util/MapsUtil.h
../util/Name.h
../util/NodeMasks.h
../util/NullInterrupter.h
../util/Util.h
../util/logging.h
../version.h
)

FIND_PACKAGE(Boost REQUIRED iostreams system thread filesystem)
FIND_PACKAGE(TBB REQUIRED)

#the root IS the include
include_directories(../../ ../../../dependencies/include ${TBB_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

cegui_add_library(${DEPNAME} SOURCES NONE)
target_link_libraries(${DEPNAME} ${TBB_LIBRARIES} Half zlib 
	${Boost_IOSTREAMS_LIBRARIES} ${Boost_SYSTEM_LIBRARIES} ${Boost_THREAD_LIBRARIES})


SET_TARGET_PROPERTIES ( ${DEPNAME}
  PROPERTIES
  VERSION 3.1
  SOVERSION 0
  )

if (MSVC)
    set_property(TARGET ${DEPNAME} APPEND PROPERTY
       COMPILE_DEFINITIONS "OPENVDB_DLL")

endif ()

#set_target_properties(${DEPNAME}_static PROPERTIES
#    COMPILE_DEFINITIONS "")

MAKE_DIRECTORY("${CMAKE_BINARY_DIR}/dependencies/include/${DEPNAME}/")

foreach(_H_FILE_RAW ${HEADERS})
    #message(${_H_FILE_RAW})
    string(SUBSTRING ${_H_FILE_RAW} 3 -1 _H_FILE)
    add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../${_H_FILE}" "${CMAKE_BINARY_DIR}/dependencies/include/${DEPNAME}/${_H_FILE}")
endforeach()


add_custom_command(TARGET ${DEPNAME} POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE" "${CMAKE_BINARY_DIR}/dependencies/${DEPNAME}-license.txt")

