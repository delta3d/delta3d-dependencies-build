//****************************************************************************//
// cal3d_wrapper.h                                                            //
// Copyright (C) 2002 Bruno 'Beosil' Heidelberger                             //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_CAL3D_WRAPPER_H
#define CAL_CAL3D_WRAPPER_H

#ifdef __cplusplus
#include "cal3d/global.h"
#endif

//****************************************************************************//
// Defines for Win32 and MingW32                                              //
//****************************************************************************//

#ifdef _WIN32

#ifdef __MINGW32__

#define CAL3D_WRAPPER_API

#else

#pragma warning(disable : 4251)
#pragma warning(disable : 4786)
#pragma warning(disable : 4099)

#ifdef CAL3D_WRAPPER_EXPORTS
#define CAL3D_WRAPPER_API __declspec(dllexport)
#else
#define CAL3D_WRAPPER_API __declspec(dllimport)
#endif

#endif

#else

//****************************************************************************//
// Defines for Linux, Cygwin, FreeBSD Sun and Mips...                         //
//****************************************************************************//

#define CAL3D_WRAPPER_API

#endif 

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

#ifndef CAL3D_WRAPPER_EXPORTS

struct CalAnimation;
struct CalAnimationAction;
struct CalAnimationCycle;
struct CalBone;
struct CalCoreAnimation;
struct CalCoreMorphAnimation;
struct CalCoreBone;
struct CalCoreKeyframe;
struct CalCoreMaterial;
struct CalCoreMesh;
struct CalCoreModel;
struct CalCoreSkeleton;
struct CalCoreSubmesh;
struct CalCoreTrack;
struct CalLoader;
struct CalMatrix;
struct CalMesh;
struct CalMixer;
struct CalMorphTargetMixer;
struct CalModel;
struct CalPhysique;
struct CalPlatform;
struct CalQuaternion;
struct CalRenderer;
struct CalSaver;
struct CalSkeleton;
struct CalSpringSystem;
struct CalSubmesh;
struct CalVector;
struct CalCoreSubMorphTargetDiffMap;

#ifndef __cplusplus
typedef int CalIndex; 
#endif

#endif



typedef void *CalUserData;

typedef unsigned long CalColorValue;	// r, g, b, a in hi to lo order

//****************************************************************************//
// Substitute for the C++ 'bool' type                                         //
//****************************************************************************//

#undef True
#undef False

enum CalBoolean
{
  False = 0,
  True = 1
};

//****************************************************************************//
// "C" wrapper functions declaration                                          //
//****************************************************************************//

#ifdef __cplusplus
extern "C"
{
#endif

//****************************************************************************//
// CalAnimation wrapper functions declaration                                 //
//****************************************************************************//

  enum CalAnimationType
  {
    ANIMATION_TYPE_NONE = 0,
    ANIMATION_TYPE_CYCLE,
    ANIMATION_TYPE_POSE,
    ANIMATION_TYPE_ACTION
  };

  enum CalAnimationState
  {
    ANIMATION_STATE_NONE = 0,
    ANIMATION_STATE_SYNC,
    ANIMATION_STATE_ASYNC,
    ANIMATION_STATE_IN,
    ANIMATION_STATE_STEADY,
    ANIMATION_STATE_OUT
  };

  CAL3D_WRAPPER_API void CalAnimation_Delete(struct CalAnimation *self);
  CAL3D_WRAPPER_API struct CalCoreAnimation *CalAnimation_GetCoreAnimation(struct CalAnimation *self);
  CAL3D_WRAPPER_API enum CalAnimationState CalAnimation_GetState(struct CalAnimation *self);
  CAL3D_WRAPPER_API float CalAnimation_GetTime(struct CalAnimation *self);
  CAL3D_WRAPPER_API enum CalAnimationType CalAnimation_GetType(struct CalAnimation *self);
  CAL3D_WRAPPER_API float CalAnimation_GetWeight(struct CalAnimation *self);

//****************************************************************************//
// CalAnimationAction wrapper functions declaration                           //
//****************************************************************************//

  CAL3D_WRAPPER_API void CalAnimationAction_Delete(struct CalAnimationAction *self);
  CAL3D_WRAPPER_API enum CalBoolean CalAnimationAction_Execute(struct CalAnimationAction *self, float delayIn, float delayOut);
  CAL3D_WRAPPER_API struct CalAnimationAction *CalAnimationAction_New(struct CalCoreAnimation *pCoreAnimation);
  CAL3D_WRAPPER_API enum CalBoolean CalAnimationAction_Update(struct CalAnimationAction *self, float deltaTime);
 
//****************************************************************************//
// CalAnimationCycle wrapper functions declaration                            //
//****************************************************************************//

  CAL3D_WRAPPER_API enum CalBoolean CalAnimationCycle_Blend(struct CalAnimationCycle *self, float weight, float delay);
  CAL3D_WRAPPER_API void CalAnimationCycle_Delete(struct CalAnimationCycle *self);
  CAL3D_WRAPPER_API struct CalAnimationCycle *CalAnimationCycle_New(struct CalCoreAnimation *pCoreAnimation);
  CAL3D_WRAPPER_API void CalAnimationCycle_SetAsync(struct CalAnimationCycle *self, float time, float duration);
  CAL3D_WRAPPER_API enum CalBoolean CalAnimationCycle_Update(struct CalAnimationCycle *self, float deltaTime);

//****************************************************************************//
// CalBone wrapper functions declaration                                      //
//****************************************************************************//

  CAL3D_WRAPPER_API void CalBone_BlendState(struct CalBone *self, float weight, struct CalVector *pTranslation, struct CalQuaternion *pRotation);
  CAL3D_WRAPPER_API void CalBone_CalculateState(struct CalBone *self);
  CAL3D_WRAPPER_API void CalBone_ClearState(struct CalBone *self);
  CAL3D_WRAPPER_API void CalBone_Delete(struct CalBone *self);
  CAL3D_WRAPPER_API struct CalCoreBone *CalBone_GetCoreBone(struct CalBone *self);
  CAL3D_WRAPPER_API struct CalQuaternion *CalBone_GetRotation(struct CalBone *self);
  CAL3D_WRAPPER_API struct CalQuaternion *CalBone_GetRotationAbsolute(struct CalBone *self);
  CAL3D_WRAPPER_API struct CalQuaternion *CalBone_GetRotationBoneSpace(struct CalBone *self);
  CAL3D_WRAPPER_API struct CalVector *CalBone_GetTranslation(struct CalBone *self);
  CAL3D_WRAPPER_API struct CalVector *CalBone_GetTranslationAbsolute(struct CalBone *self);
  CAL3D_WRAPPER_API struct CalVector *CalBone_GetTranslationBoneSpace(struct CalBone *self);
  CAL3D_WRAPPER_API void CalBone_LockState(struct CalBone *self);
  CAL3D_WRAPPER_API struct CalBone *CalBone_New(struct CalCoreBone* coreBone);
  CAL3D_WRAPPER_API void CalBone_SetSkeleton(struct CalBone *self, struct CalSkeleton *pSkeleton);
  CAL3D_WRAPPER_API void CalBone_SetTranslation(struct CalBone *self, struct CalVector *pTranslation);
  CAL3D_WRAPPER_API void CalBone_SetRotation(struct CalBone *self, struct CalQuaternion *pRotation);
  CAL3D_WRAPPER_API void CalBone_SetCoreState(struct CalBone *self);
  CAL3D_WRAPPER_API void CalBone_SetCoreStateRecursive(struct CalBone *self);
  CAL3D_WRAPPER_API enum CalBoolean CalBone_GetBoundingBox( struct CalBone *self, struct CalCoreModel* model,
  													float* outEightPoints );


//****************************************************************************//
// CalCoreAnimation wrapper functions declaration                             //
//****************************************************************************//

  CAL3D_WRAPPER_API struct CalCoreAnimation *CalCoreAnimation_New();
  CAL3D_WRAPPER_API void CalCoreAnimation_Delete(struct CalCoreAnimation* self);

  CAL3D_WRAPPER_API float CalCoreAnimation_GetDuration(struct CalCoreAnimation *self);
  CAL3D_WRAPPER_API void CalCoreAnimation_SetDuration(struct CalCoreAnimation *self, float duration);
  CAL3D_WRAPPER_API void CalCoreAnimation_Scale(struct CalCoreAnimation *self, float factor);

//****************************************************************************//
// CalCoreMorphAnimation wrapper functions declaration                             //
//****************************************************************************//

  CAL3D_WRAPPER_API struct CalCoreMorphAnimation *CalCoreMorphAnimation_New();
  CAL3D_WRAPPER_API void CalCoreMorphAnimation_Delete(struct CalCoreMorphAnimation* self);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreMorphAnimation_AddMorphTarget(struct CalCoreMorphAnimation* self, int meshID, int morphID);
  CAL3D_WRAPPER_API const char* CalCoreMorphAnimation_GetName( const struct CalCoreMorphAnimation *self );
  CAL3D_WRAPPER_API void CalCoreMorphAnimation_SetName(struct CalCoreMorphAnimation *self, const char* inName );

//****************************************************************************//
// CalCoreBone wrapper functions declaration                                  //
//****************************************************************************//

  CAL3D_WRAPPER_API enum CalBoolean CalCoreBone_AddChildId(struct CalCoreBone *self, int childId);
  CAL3D_WRAPPER_API void CalCoreBone_CalculateState(struct CalCoreBone *self);
  CAL3D_WRAPPER_API void CalCoreBone_Delete(struct CalCoreBone *self);
//  CAL3D_WRAPPER_API std::list<int>& CalCoreBone_GetListChildId(struct CalCoreBone *self);
  CAL3D_WRAPPER_API int CalCoreBone_GetChildCount( struct CalCoreBone *self );
  CAL3D_WRAPPER_API int CalCoreBone_GetChildId( struct CalCoreBone *self, int childIndex );
  CAL3D_WRAPPER_API const char *CalCoreBone_GetName(struct CalCoreBone *self);
  CAL3D_WRAPPER_API void CalCoreBone_SetName(struct CalCoreBone *self, const char* name );
  CAL3D_WRAPPER_API int CalCoreBone_GetParentId(struct CalCoreBone *self);
  CAL3D_WRAPPER_API struct CalQuaternion *CalCoreBone_GetRotation(struct CalCoreBone *self);
  CAL3D_WRAPPER_API struct CalQuaternion *CalCoreBone_GetRotationAbsolute(struct CalCoreBone *self);
  CAL3D_WRAPPER_API struct CalQuaternion *CalCoreBone_GetRotationBoneSpace(struct CalCoreBone *self);
  CAL3D_WRAPPER_API struct CalVector *CalCoreBone_GetTranslation(struct CalCoreBone *self);
  CAL3D_WRAPPER_API struct CalVector *CalCoreBone_GetTranslationAbsolute(struct CalCoreBone *self);
  CAL3D_WRAPPER_API struct CalVector *CalCoreBone_GetTranslationBoneSpace(struct CalCoreBone *self);
  CAL3D_WRAPPER_API CalUserData CalCoreBone_GetUserData(struct CalCoreBone *self);
  CAL3D_WRAPPER_API struct CalCoreBone *CalCoreBone_New(const char* name);
  CAL3D_WRAPPER_API void CalCoreBone_SetCoreSkeleton(struct CalCoreBone *self, struct CalCoreSkeleton *pCoreSkeleton);
  CAL3D_WRAPPER_API void CalCoreBone_SetParentId(struct CalCoreBone *self, int parentId);
  CAL3D_WRAPPER_API void CalCoreBone_SetRotation(struct CalCoreBone *self, struct CalQuaternion *pRotation);
  CAL3D_WRAPPER_API void CalCoreBone_SetRotationBoneSpace(struct CalCoreBone *self, struct CalQuaternion *pRotation);
  CAL3D_WRAPPER_API void CalCoreBone_SetTranslation(struct CalCoreBone *self, struct CalVector *pTranslation);
  CAL3D_WRAPPER_API void CalCoreBone_SetTranslationBoneSpace(struct CalCoreBone *self, struct CalVector *pTranslation);
  CAL3D_WRAPPER_API void CalCoreBone_SetUserData(struct CalCoreBone *self, CalUserData userData);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreBone_GetBoundingBox( struct CalCoreBone *self, struct CalCoreModel* model,
  													float* outEightPoints );
//****************************************************************************//
// CalCoreMaterial wrapper functions declaration                              //
//****************************************************************************//

  CAL3D_WRAPPER_API struct CalCoreMaterial *CalCoreMaterial_New();
  CAL3D_WRAPPER_API void CalCoreMaterial_Delete(struct CalCoreMaterial *self);

//  CAL3D_WRAPPER_API CalCoreMaterial::Color *CalCoreMaterial_GetAmbientColor(struct CalCoreMaterial *self);
//  CAL3D_WRAPPER_API CalCoreMaterial::Color *CalCoreMaterial_GetDiffuseColor(struct CalCoreMaterial *self);
  CAL3D_WRAPPER_API int CalCoreMaterial_GetMapCount(struct CalCoreMaterial *self);
  CAL3D_WRAPPER_API const char *CalCoreMaterial_GetMapFilename(struct CalCoreMaterial *self, int mapId);
  CAL3D_WRAPPER_API CalUserData CalCoreMaterial_GetMapUserData(struct CalCoreMaterial *self, int mapId);
  CAL3D_WRAPPER_API float CalCoreMaterial_GetShininess(struct CalCoreMaterial *self);
//  CAL3D_WRAPPER_API CalCoreMaterial::Color *CalCoreMaterial_GetSpecularColor(struct CalCoreMaterial *self);
  CAL3D_WRAPPER_API CalUserData CalCoreMaterial_GetUserData(struct CalCoreMaterial *self);
//  CAL3D_WRAPPER_API std::vector<Map>& CalCoreMaterial_GetVectorMap(struct CalCoreMaterial *self);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreMaterial_Reserve(struct CalCoreMaterial *self, int mapCount);
//  CAL3D_WRAPPER_API void CalCoreMaterial_SetAmbientColor(struct CalCoreMaterial *self, struct CalCoreMaterial::Color *pAmbientColor);
//  CAL3D_WRAPPER_API void CalCoreMaterial_SetDiffuseColor(struct CalCoreMaterial *self, struct CalCoreMaterial::Color *pDiffuseColor);
//  CAL3D_WRAPPER_API enum CalBoolean CalCoreMaterial_SetMap(struct CalCoreMaterial *self, int mapId, struct CalCoreMaterial::Map *pMap);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreMaterial_SetMapUserData(struct CalCoreMaterial *self, int mapId, CalUserData userData);
  CAL3D_WRAPPER_API void CalCoreMaterial_SetShininess(struct CalCoreMaterial *self, float shininess);
//  CAL3D_WRAPPER_API void CalCoreMaterial_SetSpecularColor(struct CalCoreMaterial *self, struct CalCoreMaterial::Color *pSpecularColor);
  CAL3D_WRAPPER_API void CalCoreMaterial_SetUserData(struct CalCoreMaterial *self, CalUserData userData);
  CAL3D_WRAPPER_API const char* CalCoreMaterial_GetName(struct CalCoreMaterial *self);
  CAL3D_WRAPPER_API void CalCoreMaterial_SetName(struct CalCoreMaterial *self, const char* inName);
  CAL3D_WRAPPER_API CalColorValue CalCoreMaterial_GetAmbientColor(struct CalCoreMaterial *self);
  CAL3D_WRAPPER_API CalColorValue CalCoreMaterial_GetDiffuseColor(struct CalCoreMaterial *self);
  CAL3D_WRAPPER_API CalColorValue CalCoreMaterial_GetSpecularColor(struct CalCoreMaterial *self);
  CAL3D_WRAPPER_API void CalCoreMaterial_SetAmbientColor(struct CalCoreMaterial *self, CalColorValue pAmbientColor);
  CAL3D_WRAPPER_API void CalCoreMaterial_SetDiffuseColor(struct CalCoreMaterial *self, CalColorValue pDiffuseColor);
  CAL3D_WRAPPER_API void CalCoreMaterial_SetSpecularColor(struct CalCoreMaterial *self, CalColorValue pSpecularColor);


//****************************************************************************//
// CalCoreMesh wrapper functions declaration                                  //
//****************************************************************************//

  CAL3D_WRAPPER_API struct CalCoreMesh *CalCoreMesh_New();
  CAL3D_WRAPPER_API void CalCoreMesh_Delete(struct CalCoreMesh *self);

  CAL3D_WRAPPER_API int CalCoreMesh_AddCoreSubmesh(struct CalCoreMesh *self, struct CalCoreSubmesh *pCoreSubmesh);
  CAL3D_WRAPPER_API void CalCoreMesh_RemoveCoreSubmesh( struct CalCoreMesh *self, int coreSubmeshID );
  CAL3D_WRAPPER_API struct CalCoreSubmesh *CalCoreMesh_GetCoreSubmesh(struct CalCoreMesh *self, int id);
  CAL3D_WRAPPER_API int CalCoreMesh_GetCoreSubmeshCount(struct CalCoreMesh *self);
//  CAL3D_WRAPPER_API std::vector<CalCoreSubmesh *>& CalCoreMesh_GetVectorCoreSubmesh(struct CalCoreMesh *self);
  CAL3D_WRAPPER_API const char* CalCoreMesh_GetName(struct CalCoreMesh *self);
  CAL3D_WRAPPER_API void CalCoreMesh_SetName(struct CalCoreMesh *self, const char* inName);
  CAL3D_WRAPPER_API void CalCoreMesh_Scale(struct CalCoreMesh *self,float factor);
  CAL3D_WRAPPER_API int CalCoreMesh_AddAsMorphTarget(struct CalCoreMesh *self, struct CalCoreMesh *target);
  
//****************************************************************************//
// CalCoreModel wrapper functions declaration                                 //
//****************************************************************************//

  CAL3D_WRAPPER_API int CalCoreModel_AddCoreAnimation(struct CalCoreModel *self, struct  CalCoreAnimation *pCoreAnimation);
  CAL3D_WRAPPER_API int CalCoreModel_AddCoreMorphAnimation(struct CalCoreModel *self, struct  CalCoreMorphAnimation *pCoreAnimation);
  CAL3D_WRAPPER_API int CalCoreModel_AddCoreMaterial(struct CalCoreModel *self, struct CalCoreMaterial *pCoreMaterial);
  CAL3D_WRAPPER_API int CalCoreModel_AddCoreMesh(struct CalCoreModel *self, struct CalCoreMesh *pCoreMesh);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreModel_CreateCoreMaterialThread(struct CalCoreModel *self, int coreMaterialThreadId);
  CAL3D_WRAPPER_API void CalCoreModel_Delete(struct CalCoreModel *self);
  CAL3D_WRAPPER_API const char *CalCoreModel_GetName(struct CalCoreModel *self);
  CAL3D_WRAPPER_API struct CalCoreAnimation *CalCoreModel_GetCoreAnimation(struct CalCoreModel *self, int coreAnimationId);
  CAL3D_WRAPPER_API int CalCoreModel_GetCoreAnimationCount(struct CalCoreModel *self);
  CAL3D_WRAPPER_API struct CalCoreMaterial *CalCoreModel_GetCoreMaterial(struct CalCoreModel *self, int coreMaterialId);
  CAL3D_WRAPPER_API int CalCoreModel_GetCoreMaterialCount(struct CalCoreModel *self);
  CAL3D_WRAPPER_API int CalCoreModel_GetCoreMaterialId(struct CalCoreModel *self, int coreMaterialThreadId, int coreMaterialSetId);
  CAL3D_WRAPPER_API struct CalCoreMesh *CalCoreModel_GetCoreMesh(struct CalCoreModel *self, int coreMeshId);
  CAL3D_WRAPPER_API int CalCoreModel_GetCoreMeshCount(struct CalCoreModel *self);
  CAL3D_WRAPPER_API int CalCoreModel_GetCoreMeshId(struct CalCoreModel *self, const char* coreMeshName );
  CAL3D_WRAPPER_API struct CalCoreSkeleton *CalCoreModel_GetCoreSkeleton(struct CalCoreModel *self);
  CAL3D_WRAPPER_API CalUserData CalCoreModel_GetUserData(struct CalCoreModel *self);
  CAL3D_WRAPPER_API int CalCoreModel_GetCoreMorphAnimationCount(struct CalCoreModel *self);
  CAL3D_WRAPPER_API int CalCoreModel_LoadCoreAnimation(struct CalCoreModel *self, const char *strFilename);
  CAL3D_WRAPPER_API int CalCoreModel_LoadCoreMaterial(struct CalCoreModel *self, const char *strFilename);
  CAL3D_WRAPPER_API int CalCoreModel_LoadCoreMesh(struct CalCoreModel *self, const char *strFilename);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreModel_LoadCoreSkeleton(struct CalCoreModel *self, const char *strFilename);
  CAL3D_WRAPPER_API int CalCoreModel_LoadCoreAnimationFromBuffer(struct CalCoreModel *self, const void* buffer);
  CAL3D_WRAPPER_API int CalCoreModel_LoadCoreMaterialFromBuffer(struct CalCoreModel *self, const void* buffer);
  CAL3D_WRAPPER_API int CalCoreModel_LoadCoreMeshFromBuffer(struct CalCoreModel *self, const void* buffer);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreModel_LoadCoreSkeletonFromBuffer(struct CalCoreModel *self, const void* buffer);
  CAL3D_WRAPPER_API struct CalCoreModel *CalCoreModel_New(const char* name);
  CAL3D_WRAPPER_API struct CalCoreModel *CalCoreModel_NewCopy( struct CalCoreModel* other );
  CAL3D_WRAPPER_API enum CalBoolean CalCoreModel_SaveCoreAnimation(struct CalCoreModel *self, const char *strFilename, int coreAnimtionId);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreModel_SaveCoreMaterial(struct CalCoreModel *self, const char *strFilename, int coreMaterialId);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreModel_SaveCoreMesh(struct CalCoreModel *self, const char *strFilename, int coreMeshId);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreModel_SaveCoreSkeleton(struct CalCoreModel *self, const char *strFilename);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreModel_SetCoreMaterialId(struct CalCoreModel *self, int coreMaterialThreadId, int coreMaterialSetId, int coreMaterialId);
  CAL3D_WRAPPER_API void CalCoreModel_SetCoreSkeleton(struct CalCoreModel *self, struct CalCoreSkeleton *pCoreSkeleton);
  CAL3D_WRAPPER_API void CalCoreModel_SetUserData(struct CalCoreModel *self, CalUserData userData);
  CAL3D_WRAPPER_API struct CalCoreMorphAnimation* CalCoreModel_GetCoreMorphAnimation( struct CalCoreModel *self, int morphAnimID );
  CAL3D_WRAPPER_API void CalCoreModel_SetName(struct CalCoreModel *self, const char* inName);
  CAL3D_WRAPPER_API void CalCoreModel_ReplaceCoreMesh(struct CalCoreModel *self, int coreMeshId, struct CalCoreMesh *pCoreMesh);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreModel_AddMeshName(struct CalCoreModel *self, const char* name, int coreMeshId );
  CAL3D_WRAPPER_API void CalCoreModel_CloneCoreMaterials(struct CalCoreModel *self );

//****************************************************************************//
// CalCoreSkeleton wrapper functions declaration                              //
//****************************************************************************//

  CAL3D_WRAPPER_API struct CalCoreSkeleton *CalCoreSkeleton_New();
  CAL3D_WRAPPER_API void CalCoreSkeleton_Delete(struct CalCoreSkeleton* self);

  CAL3D_WRAPPER_API int CalCoreSkeleton_AddCoreBone(struct CalCoreSkeleton *self, struct CalCoreBone *pCoreBone);
  CAL3D_WRAPPER_API void CalCoreSkeleton_CalculateState(struct CalCoreSkeleton *self);
  CAL3D_WRAPPER_API struct CalCoreBone *CalCoreSkeleton_GetCoreBone(struct CalCoreSkeleton *self, int coreBoneId);
  CAL3D_WRAPPER_API int CalCoreSkeleton_GetCoreBoneId(struct CalCoreSkeleton *self, const char *strName);
  CAL3D_WRAPPER_API enum CalBoolean CalCoreSkeleton_MapCoreBoneName( struct CalCoreSkeleton *self, int coreBoneID, const char* name );
  CAL3D_WRAPPER_API int CalCoreSkeleton_GetCoreBoneCount(struct CalCoreSkeleton *self);
  CAL3D_WRAPPER_API int CalCoreSkeleton_GetRootCoreBoneCount(struct CalCoreSkeleton *self);
  CAL3D_WRAPPER_API struct CalCoreBone *CalCoreSkeleton_GetRootCoreBone(struct CalCoreSkeleton *self, int rootBoneIndex);
//  CAL3D_WRAPPER_API std::list<int>& CalCoreSkeleton_GetListRootCoreBoneId(struct CalCoreSkeleton *self);
//  CAL3D_WRAPPER_API std::vector<CalCoreBone *>& CalCoreSkeleton_GetVectorCoreBone(struct CalCoreSkeleton *self);
  CAL3D_WRAPPER_API void CalCoreSkeleton_CalculateBoundingBoxes( struct CalCoreModel* coreModel );
  CAL3D_WRAPPER_API void CalCoreSkeleton_Scale(struct CalCoreSkeleton *self,float factor);

//****************************************************************************//
// CalCoreSubmesh wrapper functions declaration                               //
//****************************************************************************//

  CAL3D_WRAPPER_API void CalCoreSubmesh_Delete(struct CalCoreSubmesh *self);
  CAL3D_WRAPPER_API int CalCoreSubmesh_GetCoreMaterialThreadId(struct CalCoreSubmesh *self);
  CAL3D_WRAPPER_API int CalCoreSubmesh_GetFaceCount(struct CalCoreSubmesh *self);
  CAL3D_WRAPPER_API int CalCoreSubmesh_GetLodCount(struct CalCoreSubmesh *self);
  CAL3D_WRAPPER_API int CalCoreSubmesh_GetSpringCount(struct CalCoreSubmesh *self);
  CAL3D_WRAPPER_API const CalIndex* CalCoreSubmesh_GetFaces( struct CalCoreSubmesh *self );
//  CAL3D_WRAPPER_API std::vector<CalCoreSubmesh::Face>& CalCoreSubmesh_GetVectorFace(struct CalCoreSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<CalCoreSubmesh::PhysicalProperty>& CalCoreSubmesh_GetVectorPhysicalProperty(struct CalCoreSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<CalCoreSubmesh::Spring>& CalCoreSubmesh_GetVectorSpring(struct CalCoreSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<std::vector<CalCoreSubmesh::TextureCoordinate> >& CalCoreSubmesh_GetVectorVectorTextureCoordinate(struct CalCoreSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<CalCoreSubmesh::Vertex>& CalCoreSubmesh_GetVectorVertex(struct CalCoreSubmesh *self);
  CAL3D_WRAPPER_API int CalCoreSubmesh_GetVertexCount(struct CalCoreSubmesh *self);
  CAL3D_WRAPPER_API int CalCoreSubmesh_GetVertexInfluenceCount( struct CalCoreSubmesh *self, int vertID );
  CAL3D_WRAPPER_API int CalCoreSubmesh_GetVertexInfluence( struct CalCoreSubmesh *self, int vertID, int influenceID,
  															float* outWeight );
  CAL3D_WRAPPER_API struct CalCoreSubmesh *CalCoreSubmesh_New();
  CAL3D_WRAPPER_API void CalCoreSubmesh_GetVertex( struct CalCoreSubmesh* self, int vertID, float* outPosition, float* outNormal );
  CAL3D_WRAPPER_API enum CalBoolean CalCoreSubmesh_Reserve(struct CalCoreSubmesh *self, int vertexCount, int textureCoordinateCount, int faceCount, int springCount);
  CAL3D_WRAPPER_API void CalCoreSubmesh_SetCoreMaterialThreadId(struct CalCoreSubmesh *self, int coreMaterialThreadId);
//  CAL3D_WRAPPER_API enum CalBoolean CalCoreSubmesh_SetFace(struct CalCoreSubmesh *self, int faceId, struct CalCoreSubmesh::Face *pFace);
  CAL3D_WRAPPER_API void CalCoreSubmesh_SetLodCount(struct CalCoreSubmesh *self, int lodCount);
//  CAL3D_WRAPPER_API enum CalBoolean CalCoreSubmesh_SetPhysicalProperty(struct CalCoreSubmesh *self, int vertexId, struct CalCoreSubmesh::PhysicalProperty *pPhysicalProperty);
//  CAL3D_WRAPPER_API enum CalBoolean CalCoreSubmesh_SetSpring(struct CalCoreSubmesh *self, int springId, struct CalCoreSubmesh::Spring *pSpring);
//  CAL3D_WRAPPER_API enum CalBoolean CalCoreSubmesh_SetTextureCoordinate(struct CalCoreSubmesh *self, int vertexId, int textureCoordinateId, struct CalCoreSubmesh::TextureCoordinate *pTextureCoordinate);
//  CAL3D_WRAPPER_API enum CalBoolean CalCoreSubmesh_SetVertex(struct CalCoreSubmesh *self, int vertexId, struct CalCoreSubmesh::Vertex *pVertex);
CAL3D_WRAPPER_API enum CalBoolean  CalCoreSubmesh_IsTangentsEnabled(struct CalCoreSubmesh *self, int mapId);
CAL3D_WRAPPER_API enum CalBoolean  CalCoreSubmesh_EnableTangents(struct CalCoreSubmesh *self, int mapId, enum CalBoolean enabled);
CAL3D_WRAPPER_API int CalCoreSubmesh_AddSubMorphTarget( CalCoreSubmesh *self, CalCoreSubMorphTargetDiffMap* inTarget );
  
//****************************************************************************//
// CalCoreSubMorphTargetDiffMap wrapper functions declaration                 //
//****************************************************************************//
CAL3D_WRAPPER_API CalCoreSubMorphTargetDiffMap* CalCoreSubMorphTargetDiffMap_New();
CAL3D_WRAPPER_API CalCoreSubMorphTargetDiffMap* CalCoreSubMorphTargetDiffMap_Clone(
	const CalCoreSubMorphTargetDiffMap* inOther );
CAL3D_WRAPPER_API void CalCoreSubMorphTargetDiffMap_Delete( CalCoreSubMorphTargetDiffMap* inSelf );
CAL3D_WRAPPER_API bool CalCoreSubMorphTargetDiffMap_Reserve( CalCoreSubMorphTargetDiffMap* inSelf,
	int inNumDifferences );
CAL3D_WRAPPER_API bool CalCoreSubMorphTargetDiffMap_AppendVertex( CalCoreSubMorphTargetDiffMap* inSelf,
	int inVertexID, float* inPositionOffset, float* inNormalOffset );

//****************************************************************************//
// CalError wrapper functions declaration                                     //
//****************************************************************************//

  enum CalErrorCode
  {
    ERROR_CODE_OK = 0,
    ERROR_CODE_INTERNAL,
    ERROR_CODE_INVALID_HANDLE,
    ERROR_CODE_MEMORY_ALLOCATION_FAILED,
    ERROR_CODE_FILE_NOT_FOUND,
    ERROR_CODE_INVALID_FILE_FORMAT,
    ERROR_CODE_FILE_PARSER_FAILED,
    ERROR_CODE_INDEX_BUILD_FAILED,
    ERROR_CODE_NO_PARSER_DOCUMENT,
    ERROR_CODE_INVALID_ANIMATION_DURATION,
    ERROR_CODE_BONE_NOT_FOUND,
    ERROR_CODE_INVALID_ATTRIBUTE_VALUE,
    ERROR_CODE_INVALID_KEYFRAME_COUNT,
    ERROR_CODE_INVALID_ANIMATION_TYPE,
    ERROR_CODE_FILE_CREATION_FAILED,
    ERROR_CODE_FILE_WRITING_FAILED,
    ERROR_CODE_INCOMPATIBLE_FILE_VERSION,
    ERROR_CODE_NO_MESH_IN_MODEL,
    ERROR_CODE_MAX_ERROR_CODE
  };

  CAL3D_WRAPPER_API enum CalErrorCode CalError_GetLastErrorCode();
  CAL3D_WRAPPER_API const char *CalError_GetLastErrorDescription();
  CAL3D_WRAPPER_API const char *CalError_GetLastErrorFile();
  CAL3D_WRAPPER_API int CalError_GetLastErrorLine();
  CAL3D_WRAPPER_API const char *CalError_GetLastErrorText();
  CAL3D_WRAPPER_API void CalError_PrintLastError();
//  CAL3D_WRAPPER_API void CalError_SetLastError(enum CalErrorCode code, char *strFile, int line, char *strText);

//****************************************************************************//
// CalLoader wrapper functions declaration                                    //
//****************************************************************************//

  CAL3D_WRAPPER_API struct CalLoader *CalLoader_New();
  CAL3D_WRAPPER_API void CalLoader_Delete(struct CalLoader *self);
  CAL3D_WRAPPER_API struct CalCoreAnimation *CalLoader_LoadCoreAnimation(struct CalLoader *self, const char *strFilename);
  CAL3D_WRAPPER_API struct CalCoreMaterial *CalLoader_LoadCoreMaterial(struct CalLoader *self, const char *strFilename);
  CAL3D_WRAPPER_API struct CalCoreMesh *CalLoader_LoadCoreMesh(struct CalLoader *self, const char *strFilename);
  CAL3D_WRAPPER_API struct CalCoreSkeleton *CalLoader_LoadCoreSkeleton(struct CalLoader *self, const char *strFilename);
  CAL3D_WRAPPER_API struct CalCoreMesh *CalLoader_LoadCoreMeshFromBuffer(const void *data);
	enum CalLoaderFlags
	{
		CAL_LOADER_ROTATE_X_AXIS = 1,
		CAL_LOADER_INVERT_V_COORD = 2
	};
  CAL3D_WRAPPER_API void CalLoader_SetLoadingMode( int flags );

//****************************************************************************//
// CalMesh wrapper functions declaration                                      //
//****************************************************************************//

  CAL3D_WRAPPER_API void CalMesh_Delete(struct CalMesh *self);
  CAL3D_WRAPPER_API struct CalCoreMesh *CalMesh_GetCoreMesh(struct CalMesh *self);
  CAL3D_WRAPPER_API struct CalSubmesh *CalMesh_GetSubmesh(struct CalMesh *self, int id);
  CAL3D_WRAPPER_API int CalMesh_GetSubmeshCount(struct CalMesh *self);
//  CAL3D_WRAPPER_API std::vector<CalSubmesh *>& CalMesh_GetVectorSubmesh(struct CalMesh *self);
  CAL3D_WRAPPER_API struct CalMesh *CalMesh_New(struct CalCoreMesh *pCoreMesh);
  CAL3D_WRAPPER_API void CalMesh_SetLodLevel(struct CalMesh *self, float lodLevel);
  CAL3D_WRAPPER_API void CalMesh_SetMaterialSet(struct CalMesh *self, int setId);
  CAL3D_WRAPPER_API void CalMesh_SetModel(struct CalMesh *self, struct CalModel *pModel);

//****************************************************************************//
// CalMixer wrapper functions declaration                                     //
//****************************************************************************//

  CAL3D_WRAPPER_API enum CalBoolean CalMixer_BlendCycle(struct CalMixer *self, int id, float weight, float delay);
  CAL3D_WRAPPER_API enum CalBoolean CalMixer_ClearCycle(struct CalMixer *self, int id, float delay);
  CAL3D_WRAPPER_API void CalMixer_Delete(struct CalMixer *self);
  CAL3D_WRAPPER_API enum CalBoolean CalMixer_ExecuteAction(struct CalMixer *self, int id, float delayIn, float delayOut, enum CalBoolean autoLock);
  CAL3D_WRAPPER_API struct CalMixer *CalMixer_New(struct CalModel *pModel);
  CAL3D_WRAPPER_API void CalMixer_UpdateAnimation(struct CalMixer *self, float deltaTime);
  CAL3D_WRAPPER_API void CalMixer_UpdateSkeleton(struct CalMixer *self);
  CAL3D_WRAPPER_API void CalMixer_RemoveAction(struct CalMixer *self,int id);

//****************************************************************************//
// CalMorphTargetMixer wrapper functions declaration                          //
//****************************************************************************//
  CAL3D_WRAPPER_API enum CalBoolean CalMorphTargetMixer_Blend( struct CalMorphTargetMixer* self,
  							int morphAnimID, float weight, float delayIn, float delayOut, bool looping );
  CAL3D_WRAPPER_API enum CalBoolean CalMorphTargetMixer_Clear(struct CalMorphTargetMixer *self, int id, float delay);
  CAL3D_WRAPPER_API void CalMorphTargetMixer_Delete(struct CalMorphTargetMixer *self);
  CAL3D_WRAPPER_API struct CalMorphTargetMixer *CalMorphTargetMixer_New(struct CalModel *pModel);
  CAL3D_WRAPPER_API void CalMorphTargetMixer_Update( struct CalMorphTargetMixer* self, float deltaTime );
  CAL3D_WRAPPER_API int CalMorphTargetMixer_GetMorphTargetCount( struct CalMorphTargetMixer* self );
  CAL3D_WRAPPER_API enum CalBoolean CalMorphTargetMixer_Copy( struct CalMorphTargetMixer* self,
  															const struct CalMorphTargetMixer* toCopy );
  CAL3D_WRAPPER_API float CalMorphTargetMixer_GetCurrentWeight( struct CalMorphTargetMixer* self, int morphAnimID );

//****************************************************************************//
// CalModel wrapper functions declaration                                     //
//****************************************************************************//

  CAL3D_WRAPPER_API enum CalBoolean CalModel_AttachMesh(struct CalModel *self, int coreMeshId);
  CAL3D_WRAPPER_API void CalModel_Delete(struct CalModel *self);
  CAL3D_WRAPPER_API enum CalBoolean CalModel_DetachMesh(struct CalModel *self, int coreMeshId);
  CAL3D_WRAPPER_API struct CalCoreModel *CalModel_GetCoreModel(struct CalModel *self);
  CAL3D_WRAPPER_API struct CalMesh *CalModel_GetMesh(struct CalModel *self, int coreMeshId);
  CAL3D_WRAPPER_API const struct CalMesh *CalModel_GetMeshConst(const struct CalModel *self, int coreMeshId);
  CAL3D_WRAPPER_API struct CalMixer *CalModel_GetMixer(struct CalModel *self);
  CAL3D_WRAPPER_API struct CalMorphTargetMixer *CalModel_GetMorphTargetMixer(struct CalModel *self);
  CAL3D_WRAPPER_API const struct CalMorphTargetMixer *CalModel_GetMorphTargetMixerConst(const struct CalModel *self);
  CAL3D_WRAPPER_API struct CalPhysique *CalModel_GetPhysique(struct CalModel *self);
  CAL3D_WRAPPER_API const struct CalPhysique *CalModel_GetPhysiqueConst(const struct CalModel *self);
  CAL3D_WRAPPER_API void CalModel_SetPhysique(struct CalModel *self, struct CalPhysique *phys);
  CAL3D_WRAPPER_API struct CalRenderer *CalModel_GetRenderer(struct CalModel *self);
  CAL3D_WRAPPER_API struct CalSkeleton *CalModel_GetSkeleton(struct CalModel *self);
  CAL3D_WRAPPER_API struct CalSpringSystem *CalModel_GetSpringSystem(struct CalModel *self);
  CAL3D_WRAPPER_API const struct CalSpringSystem *CalModel_GetSpringSystemConst(const struct CalModel *self);
  CAL3D_WRAPPER_API CalUserData CalModel_GetUserData(struct CalModel *self);
  CAL3D_WRAPPER_API int CalModel_GetMeshCount(struct CalModel *self);
  CAL3D_WRAPPER_API struct CalMesh *CalModel_GetMeshByMeshID(struct CalModel *self, int meshId);
//  CAL3D_WRAPPER_API std::vector<CalMesh *>& CalModel_GetVectorMesh(struct CalModel *self);
  CAL3D_WRAPPER_API struct CalModel *CalModel_New(struct CalCoreModel* pCoreModel);
  CAL3D_WRAPPER_API void CalModel_SetLodLevel(struct CalModel *self, float lodLevel);
  CAL3D_WRAPPER_API void CalModel_SetMaterialSet(struct CalModel *self, int setId);
  CAL3D_WRAPPER_API void CalModel_SetUserData(struct CalModel *self, CalUserData userData);
  CAL3D_WRAPPER_API void CalModel_Update(struct CalModel *self, float deltaTime);

//****************************************************************************//
// CalPhysique wrapper functions declaration                                  //
//****************************************************************************//

  CAL3D_WRAPPER_API int CalPhysique_CalculateNormals(struct CalPhysique *self, struct CalSubmesh *pSubmesh, float *pNormalBuffer);
  CAL3D_WRAPPER_API int CalPhysique_CalculateVertices(struct CalPhysique *self, struct CalSubmesh *pSubmesh, float *pVertexBuffer);
  CAL3D_WRAPPER_API int CalPhysique_CalculateVerticesAndNormals(struct CalPhysique *self, struct CalSubmesh *pSubmesh, float *pVertexBuffer);
  CAL3D_WRAPPER_API int CalPhysique_CalculateVerticesNormalsAndTexCoords(struct CalPhysique *self, struct CalSubmesh *pSubmesh, float *pVertexBuffer, int NumTexCoords);
  CAL3D_WRAPPER_API int CalPhysique_CalculateTangentSpaces(struct CalPhysique *self, struct CalSubmesh *pSubmesh, int mapId, float *pTangentSpaceBuffer);
  CAL3D_WRAPPER_API void CalPhysique_Delete(struct CalPhysique *self);
  CAL3D_WRAPPER_API struct CalPhysique *CalPhysique_New(struct CalModel* pModel);
  CAL3D_WRAPPER_API void CalPhysique_Update(struct CalPhysique *self);
  CAL3D_WRAPPER_API struct CalPhysique *CalPhysiqueDualQuat_New(struct CalModel* pModel);

//****************************************************************************//
// CalPlatform wrapper functions declaration                                  //
//****************************************************************************//

//****************************************************************************//
// CalQuaternion wrapper functions declaration                                //
//****************************************************************************//

  CAL3D_WRAPPER_API void CalQuaternion_Blend(struct CalQuaternion *self, float d, const struct CalQuaternion *pQ);
  CAL3D_WRAPPER_API void CalQuaternion_Clear(struct CalQuaternion *self);
  CAL3D_WRAPPER_API void CalQuaternion_Conjugate(struct CalQuaternion *self);
  CAL3D_WRAPPER_API void CalQuaternion_Invert(struct CalQuaternion *self);
  CAL3D_WRAPPER_API void CalQuaternion_Delete(struct CalQuaternion *self);
  CAL3D_WRAPPER_API void CalQuaternion_Equal(struct CalQuaternion *self, const struct CalQuaternion *pQ);
  CAL3D_WRAPPER_API float *CalQuaternion_Get(struct CalQuaternion *self);
  CAL3D_WRAPPER_API void CalQuaternion_Multiply(struct CalQuaternion *self, const struct CalQuaternion *pQ);
  CAL3D_WRAPPER_API void CalQuaternion_MultiplyVector(struct CalQuaternion *self, const struct CalVector *pV);
  CAL3D_WRAPPER_API struct CalQuaternion *CalQuaternion_New();
  CAL3D_WRAPPER_API void CalQuaternion_Op_Multiply(struct CalQuaternion *pResult, const struct CalQuaternion *pQ, const struct CalQuaternion *pR);
  CAL3D_WRAPPER_API void CalQuaternion_Set(struct CalQuaternion *self, float qx, float qy, float qz, float qw);

//****************************************************************************//
// CalRenderer wrapper functions declaration                                  //
//****************************************************************************//

  CAL3D_WRAPPER_API enum CalBoolean CalRenderer_BeginRendering(struct CalRenderer *self);
  CAL3D_WRAPPER_API void CalRenderer_Delete(struct CalRenderer *self);
  CAL3D_WRAPPER_API void CalRenderer_EndRendering(struct CalRenderer *self);
  CAL3D_WRAPPER_API void CalRenderer_GetAmbientColor(struct CalRenderer *self, unsigned char *pColorBuffer);
  CAL3D_WRAPPER_API void CalRenderer_GetDiffuseColor(struct CalRenderer *self, unsigned char *pColorBuffer);
  CAL3D_WRAPPER_API int CalRenderer_GetFaceCount(struct CalRenderer *self);
  CAL3D_WRAPPER_API int CalRenderer_GetFaces(struct CalRenderer *self, CalIndex *pFaceBuffer);
  CAL3D_WRAPPER_API int CalRenderer_GetMapCount(struct CalRenderer *self);
  CAL3D_WRAPPER_API CalUserData CalRenderer_GetMapUserData(struct CalRenderer *self, int mapId);
  CAL3D_WRAPPER_API int CalRenderer_GetMeshCount(struct CalRenderer *self);
  CAL3D_WRAPPER_API int CalRenderer_GetNormals(struct CalRenderer *self, float *pNormalBuffer);
  CAL3D_WRAPPER_API float CalRenderer_GetShininess(struct CalRenderer *self);
  CAL3D_WRAPPER_API void CalRenderer_GetSpecularColor(struct CalRenderer *self, unsigned char *pColorBuffer);
  CAL3D_WRAPPER_API int CalRenderer_GetSubmeshCount(struct CalRenderer *self, int meshId);
  CAL3D_WRAPPER_API int CalRenderer_GetTextureCoordinates(struct CalRenderer *self, int mapId, float *pTextureCoordinateBuffer);
  CAL3D_WRAPPER_API int CalRenderer_GetVertexCount(struct CalRenderer *self);
  CAL3D_WRAPPER_API int CalRenderer_GetVertices(struct CalRenderer *self, float *pVertexBuffer);
  CAL3D_WRAPPER_API int CalRenderer_GetVerticesAndNormals(struct CalRenderer *self, float *pVertexBuffer);
  CAL3D_WRAPPER_API int CalRenderer_GetVerticesNormalsAndTexCoords(struct CalRenderer *self, float *pVertexBuffer, int NumTexCoords);
  CAL3D_WRAPPER_API int CalRenderer_GetTangentSpaces(struct CalRenderer *self, int mapId, float *pTangentSpaceBuffer);
  CAL3D_WRAPPER_API enum CalBoolean  CalRenderer_IsTangentsEnabled(struct CalRenderer *self, int mapId);
  CAL3D_WRAPPER_API struct CalRenderer *CalRenderer_New(struct CalModel* pModel);
  CAL3D_WRAPPER_API enum CalBoolean CalRenderer_SelectMeshSubmesh(struct CalRenderer *self, int meshId, int submeshId);

//****************************************************************************//
// CalSaver wrapper functions declaration                                     //
//****************************************************************************//

  CAL3D_WRAPPER_API void CalSaver_Delete(struct CalSaver *self);
  CAL3D_WRAPPER_API struct CalSaver *CalSaver_New();
  CAL3D_WRAPPER_API enum CalBoolean CalSaver_SaveCoreAnimation(struct CalSaver *self, const char *strFilename, struct  CalCoreAnimation *pCoreAnimation);
  CAL3D_WRAPPER_API enum CalBoolean CalSaver_SaveCoreMaterial(struct CalSaver *self, const char *strFilename, struct CalCoreMaterial *pCoreMaterial);
  CAL3D_WRAPPER_API enum CalBoolean CalSaver_SaveCoreMesh(struct CalSaver *self, const char *strFilename, struct CalCoreMesh *pCoreMesh);
  CAL3D_WRAPPER_API enum CalBoolean CalSaver_SaveCoreSkeleton(struct CalSaver *self, const char *strFilename, struct CalCoreSkeleton *pCoreSkeleton);

//****************************************************************************//
// CalSkeleton wrapper functions declaration                                  //
//****************************************************************************//

  CAL3D_WRAPPER_API void CalSkeleton_CalculateState(struct CalSkeleton *self);
  CAL3D_WRAPPER_API void CalSkeleton_ClearState(struct CalSkeleton *self);
  CAL3D_WRAPPER_API void CalSkeleton_Delete(struct CalSkeleton *self);
  CAL3D_WRAPPER_API struct CalBone *CalSkeleton_GetBone(struct CalSkeleton *self, int boneId);
  CAL3D_WRAPPER_API const struct CalBone *CalSkeleton_GetBoneConst(const struct CalSkeleton *self, int boneId);
  CAL3D_WRAPPER_API int CalSkeleton_GetBoneCount(const struct CalSkeleton *self);
  CAL3D_WRAPPER_API struct CalCoreSkeleton *CalSkeleton_GetCoreSkeleton(struct CalSkeleton *self);
  CAL3D_WRAPPER_API const struct CalCoreSkeleton *CalSkeleton_GetCoreSkeletonConst(const struct CalSkeleton *self);
//  CAL3D_WRAPPER_API std::vector<CalBone *>& CalSkeleton_GetVectorBone(struct CalSkeleton *self);
  CAL3D_WRAPPER_API void CalSkeleton_LockState(struct CalSkeleton *self);
  CAL3D_WRAPPER_API struct CalSkeleton *CalSkeleton_New(struct CalCoreSkeleton* pCoreSkeleton);
  CAL3D_WRAPPER_API void CalSkeleton_GetBoneBoundingBox(struct CalSkeleton *self, float *min, float *max);
  CAL3D_WRAPPER_API void CalSkeleton_CalculateBoundingBoxes(struct CalSkeleton *self);

  // DEBUG-CODE
  CAL3D_WRAPPER_API int CalSkeleton_GetBonePoints(struct CalSkeleton *self, float *pPoints);
  CAL3D_WRAPPER_API int CalSkeleton_GetBonePointsStatic(struct CalSkeleton *self, float *pPoints);
  CAL3D_WRAPPER_API int CalSkeleton_GetBoneLines(struct CalSkeleton *self, float *pLines);
  CAL3D_WRAPPER_API int CalSkeleton_GetBoneLinesStatic(struct CalSkeleton *self, float *pLines);

//****************************************************************************//
// CalSpringSystem wrapper functions declaration                              //
//****************************************************************************//

  CAL3D_WRAPPER_API void CalSpringSystem_CalculateForces(struct CalSpringSystem *self, struct CalSubmesh *pSubmesh, float deltaTime);
  CAL3D_WRAPPER_API void CalSpringSystem_CalculateVertices(struct CalSpringSystem *self, struct CalSubmesh *pSubmesh, float deltaTime);
  CAL3D_WRAPPER_API void CalSpringSystem_Delete(struct CalSpringSystem *self);
  CAL3D_WRAPPER_API struct CalSpringSystem *CalSpringSystem_New(struct CalModel *pModel);
  CAL3D_WRAPPER_API void CalSpringSystem_Update(struct CalSpringSystem *self, float deltaTime);
  CAL3D_WRAPPER_API const struct CalVector *CalSpringSystem_GetGravityVector(const struct CalSpringSystem *self);
  CAL3D_WRAPPER_API const struct CalVector *CalSpringSystem_GetForceVector(const struct CalSpringSystem *self);
  CAL3D_WRAPPER_API void CalSpringSystem_SetGravityVector(struct CalSpringSystem *self, struct CalVector* grav);
  CAL3D_WRAPPER_API void CalSpringSystem_SetForceVector(struct CalSpringSystem *self, struct CalVector* force);
  CAL3D_WRAPPER_API void CalSpringSystem_ResetPositions(struct CalSpringSystem *self);

//****************************************************************************//
// CalSubmesh wrapper functions declaration                                   //
//****************************************************************************//

  CAL3D_WRAPPER_API void CalSubmesh_Delete(struct CalSubmesh *self);
  CAL3D_WRAPPER_API struct CalCoreSubmesh *CalSubmesh_GetCoreSubmesh(struct CalSubmesh *self);
  CAL3D_WRAPPER_API int CalSubmesh_GetCoreMaterialId(struct CalSubmesh *self);
  CAL3D_WRAPPER_API int CalSubmesh_GetFaceCount(struct CalSubmesh *self);
  CAL3D_WRAPPER_API int CalSubmesh_GetFaces(struct CalSubmesh *self, CalIndex *pFaceBuffer);

//  CAL3D_WRAPPER_API std::vector<CalVector>& CalSubmesh_GetVectorNormal(struct CalSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<CalSubmesh::PhysicalProperty>& CalSubmesh_GetVectorPhysicalProperty(struct CalSubmesh *self);
//  CAL3D_WRAPPER_API std::vector<CalVector>& CalSubmesh_GetVectorVertex(struct CalSubmesh *self);
  CAL3D_WRAPPER_API int CalSubmesh_GetVertexCount(struct CalSubmesh *self);
  CAL3D_WRAPPER_API enum CalBoolean CalSubmesh_HasInternalData(struct CalSubmesh *self);
  CAL3D_WRAPPER_API struct CalSubmesh *CalSubmesh_New(struct CalCoreSubmesh* coreSubmesh);
  CAL3D_WRAPPER_API void CalSubmesh_SetCoreMaterialId(struct CalSubmesh *self, int coreMaterialId);
  CAL3D_WRAPPER_API void CalSubmesh_SetLodLevel(struct CalSubmesh *self, float lodLevel);

//****************************************************************************//
// CalVector wrapper functions declaration                                    //
//****************************************************************************//

  CAL3D_WRAPPER_API void CalVector_Add(struct CalVector *self, struct CalVector *pV);
  CAL3D_WRAPPER_API void CalVector_Blend(struct CalVector *self, float d, struct CalVector *pV);
  CAL3D_WRAPPER_API void CalVector_Clear(struct CalVector *self);
  CAL3D_WRAPPER_API void CalVector_Delete(struct CalVector *self);
  CAL3D_WRAPPER_API void CalVector_Equal(struct CalVector *self, struct CalVector *pV);
  CAL3D_WRAPPER_API void CalVector_InverseScale(struct CalVector *self, float d);
  CAL3D_WRAPPER_API float *CalVector_Get(struct CalVector *self);
  CAL3D_WRAPPER_API float CalVector_Length(struct CalVector *self);
  CAL3D_WRAPPER_API struct CalVector *CalVector_New();
  CAL3D_WRAPPER_API float CalVector_Normalize(struct CalVector *self);
  CAL3D_WRAPPER_API void CalVector_Op_Add(struct CalVector *pResult, struct CalVector *pV, struct CalVector *pU);
  CAL3D_WRAPPER_API void CalVector_Op_Subtract(struct CalVector *pResult, struct CalVector *pV, struct CalVector *pU);
  CAL3D_WRAPPER_API void CalVector_CalVector_Op_Scale(struct CalVector *pResult, struct CalVector *pV, float d);
  CAL3D_WRAPPER_API void CalVector_CalVector_Op_InverseScale(struct CalVector *pResult, struct CalVector *pV, float d);
  CAL3D_WRAPPER_API float CalVector_Op_Scalar(struct CalVector *pV, struct CalVector *pU);
  CAL3D_WRAPPER_API void CalVector_Op_Cross(struct CalVector *pResult, struct CalVector *pV, struct CalVector *pU);
  CAL3D_WRAPPER_API void CalVector_Scale(struct CalVector *self, float d);
  CAL3D_WRAPPER_API void CalVector_Set(struct CalVector *self, float vx, float vy, float vz);
  CAL3D_WRAPPER_API void CalVector_Subtract(struct CalVector *self, struct CalVector *pV);
  CAL3D_WRAPPER_API void CalVector_Transform(struct CalVector *self, struct CalQuaternion *pQ);

#ifdef __cplusplus
}
#endif

#endif

//****************************************************************************//
