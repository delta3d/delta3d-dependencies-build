//****************************************************************************//
// cal3d_wrapper.cpp                                                          //
// Copyright (C) 2002 Bruno 'Beosil' Heidelberger                             //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//****************************************************************************//
// Defines                                                                    //
//****************************************************************************//

#define CAL3D_WRAPPER_EXPORTS

//****************************************************************************//
// Includes                                                                   // 
//****************************************************************************//

#include "cal3d/cal3d.h"
#include "cal3d/cal3d_wrapper.h"

//****************************************************************************//
// CalAnimation wrapper functions definition                                  //
//****************************************************************************//

Boolean CalAnimation_Create(CalAnimation *self, CalCoreAnimation *pCoreAnimation)
{
  return self->create(pCoreAnimation) ? True : False;
}

void CalAnimation_Delete(CalAnimation *self)
{
  delete self;
}

void CalAnimation_Destroy(CalAnimation *self)
{
  self->destroy();
}

CalCoreAnimation *CalAnimation_GetCoreAnimation(CalAnimation *self)
{
  return self->getCoreAnimation();
}

CalAnimationState CalAnimation_GetState(CalAnimation *self)
{
  return (CalAnimationState)(self->getState());
}

float CalAnimation_GetTime(CalAnimation *self)
{
  return self->getTime();
}

CalAnimationType CalAnimation_GetType(CalAnimation *self)
{
  return (CalAnimationType)(self->getType());
}

float CalAnimation_GetWeight(CalAnimation *self)
{
  return self->getWeight();
}

//****************************************************************************//
// CalAnimationAction wrapper functions definition                            //
//****************************************************************************//

Boolean CalAnimationAction_Create(CalAnimationAction *self, CalCoreAnimation *pCoreAnimation)
{
  return self->create(pCoreAnimation) ? True : False;
}

void CalAnimationAction_Delete(CalAnimationAction *self)
{
  delete self;
}

void CalAnimationAction_Destroy(CalAnimationAction *self)
{
  self->destroy();
}

Boolean CalAnimationAction_Execute(CalAnimationAction *self, float delayIn, float delayOut)
{
  return self->execute(delayIn, delayOut) ? True : False;
}

CalAnimationAction *CalAnimationAction_New()
{
  return new CalAnimationAction();
}

Boolean CalAnimationAction_Update(CalAnimationAction *self, float deltaTime)
{
  return self->update(deltaTime) ? True : False;
}

//****************************************************************************//
// CalAnimationCycle wrapper functions definition                             //
//****************************************************************************//

Boolean CalAnimationCycle_Blend(CalAnimationCycle *self, float weight, float delay)
{
  return self->blend(weight, delay) ? True : False;
}

Boolean CalAnimationCycle_Create(CalAnimationCycle *self, CalCoreAnimation *pCoreAnimation)
{
  return self->create(pCoreAnimation) ? True : False;
}

void CalAnimationCycle_Delete(CalAnimationCycle *self)
{
  delete self;
}

void CalAnimationCycle_Destroy(CalAnimationCycle *self)
{
  self->destroy();
}

CalAnimationCycle *CalAnimationCycle_New()
{
  return new CalAnimationCycle();
}

void CalAnimationCycle_SetAsync(CalAnimationCycle *self, float time, float duration)
{
  self->setAsync(time, duration);
}

Boolean CalAnimationCycle_Update(CalAnimationCycle *self, float deltaTime)
{
  return self->update(deltaTime) ? True : False;
}

//****************************************************************************//
// CalBone wrapper functions definition                                           //
//****************************************************************************//

void CalBone_BlendState(CalBone *self, float weight, CalVector *pTranslation, CalQuaternion *pRotation)
{
  self->blendState(weight, *pTranslation, *pRotation);
}

void CalBone_CalculateState(CalBone *self)
{
  self->calculateState();
}

void CalBone_ClearState(CalBone *self)
{
  self->clearState();
}

Boolean CalBone_Create(CalBone *self, CalCoreBone *pCoreBone)
{
  return self->create(pCoreBone) ? True : False;
}

void CalBone_Delete(CalBone *self)
{
  delete self;
}

void CalBone_Destroy(CalBone *self)
{
  self->destroy();
}

CalCoreBone *CalBone_GetCoreBone(CalBone *self)
{
  return self->getCoreBone();
}

CalQuaternion *CalBone_GetRotation(CalBone *self)
{
  return &(const_cast<CalQuaternion&>(self->getRotation()));
}

CalQuaternion *CalBone_GetRotationAbsolute(CalBone *self)
{
  return &(const_cast<CalQuaternion&>(self->getRotationAbsolute()));
}

CalQuaternion *CalBone_GetRotationBoneSpace(CalBone *self)
{
  return &(const_cast<CalQuaternion&>(self->getRotationBoneSpace()));
}

CalVector *CalBone_GetTranslation(CalBone *self)
{
  return &(const_cast<CalVector&>(self->getTranslation()));
}

CalVector *CalBone_GetTranslationAbsolute(CalBone *self)
{
  return &(const_cast<CalVector&>(self->getTranslationAbsolute()));
}

CalVector *CalBone_GetTranslationBoneSpace(CalBone *self)
{
  return &(const_cast<CalVector&>(self->getTranslationBoneSpace()));
}

void CalBone_LockState(CalBone *self)
{
  self->lockState();
}

CalBone *CalBone_New()
{
  return new CalBone();
}

void CalBone_SetSkeleton(CalBone *self, CalSkeleton *pSkeleton)
{
  self->setSkeleton(pSkeleton);
}

void CalBone_SetRotation(CalBone *self, CalQuaternion *pRotation)
{
  self->setRotation(*pRotation);
}

void CalBone_SetTranslation(CalBone *self, CalVector *pTranslation)
{
  self->setTranslation(*pTranslation);
}

void CalBone_SetCoreState(CalBone *self)
{
  self->setCoreState();
}

void CalBone_SetCoreStateRecursive(CalBone *self)
{
  self->setCoreStateRecursive();
}


//****************************************************************************//
// CalCoreAnimation wrapper functions definition                              //
//****************************************************************************//

Boolean CalCoreAnimation_AddCoreTrack(CalCoreAnimation *self, CalCoreTrack *pCoreTrack)
{
  return self->addCoreTrack(pCoreTrack) ? True : False;
}

Boolean CalCoreAnimation_Create(CalCoreAnimation *self)
{
  return self->create() ? True : False;
}

void CalCoreAnimation_Delete(CalCoreAnimation *self)
{
  delete self;
}

void CalCoreAnimation_Destroy(CalCoreAnimation *self)
{
  self->destroy();
}

CalCoreTrack *CalCoreAnimation_GetCoreTrack(CalCoreAnimation *self, int coreBoneId)
{
  return self->getCoreTrack(coreBoneId);
}

float CalCoreAnimation_GetDuration(CalCoreAnimation *self)
{
  return self->getDuration();
}

/*
std::list<CalCoreTrack *>& CalCoreAnimation_GetListCoreTrack(CalCoreAnimation *self)
{
  return self->getListCoreTrack();
}
*/

CalCoreAnimation *CalCoreAnimation_New(CalCoreAnimation *self)
{
  return new CalCoreAnimation();
}

void CalCoreAnimation_SetDuration(CalCoreAnimation *self, float duration)
{
  self->setDuration(duration);
}

//****************************************************************************//
// CalCoreAnimation wrapper functions definition                              //
//****************************************************************************//

Boolean CalCoreBone_AddChildId(CalCoreBone *self, int childId)
{
  return self->addChildId(childId) ? True : False;
}

void CalCoreBone_CalculateState(CalCoreBone *self)
{
  self->calculateState();
}

Boolean CalCoreBone_Create(CalCoreBone *self, char *strName)
{
  return self->createWithName(strName) ? True : False;
}

void CalCoreBone_Delete(CalCoreBone *self)
{
  delete self;
}

void CalCoreBone_Destroy(CalCoreBone *self)
{
  self->destroy();
}

/*
std::list<int>& CalCoreBone_GetListChildId(CalCoreBone *self)
{
  return self->getListChildId();
}
*/

char *CalCoreBone_GetName(CalCoreBone *self)
{
  return const_cast<char *>(self->getName());
}

int CalCoreBone_GetParentId(CalCoreBone *self)
{
  return self->getParentId();
}

CalQuaternion *CalCoreBone_GetRotation(CalCoreBone *self)
{
  return &(const_cast<CalQuaternion&>(self->getRotation()));
}

CalQuaternion *CalCoreBone_GetRotationAbsolute(CalCoreBone *self)
{
  return &(const_cast<CalQuaternion&>(self->getRotationAbsolute()));
}

CalQuaternion *CalCoreBone_GetRotationBoneSpace(CalCoreBone *self)
{
  return &(const_cast<CalQuaternion&>(self->getRotationBoneSpace()));
}

CalVector *CalCoreBone_GetTranslation(CalCoreBone *self)
{
  return &(const_cast<CalVector&>(self->getTranslation()));
}

CalVector *CalCoreBone_GetTranslationAbsolute(CalCoreBone *self)
{
  return &(const_cast<CalVector&>(self->getTranslationAbsolute()));
}

CalVector *CalCoreBone_GetTranslationBoneSpace(CalCoreBone *self)
{
  return &(const_cast<CalVector&>(self->getTranslationBoneSpace()));
}

CalUserData CalCoreBone_GetUserData(CalCoreBone *self)
{
  return self->getUserData();
}

CalCoreBone *CalCoreBone_New()
{
  return new CalCoreBone();
}

void CalCoreBone_SetCoreSkeleton(CalCoreBone *self, CalCoreSkeleton *pCoreSkeleton)
{
  self->setCoreSkeleton(pCoreSkeleton);
}

void CalCoreBone_SetParentId(CalCoreBone *self, int parentId)
{
  self->setParentId(parentId);
}

void CalCoreBone_SetRotation(CalCoreBone *self, CalQuaternion *pRotation)
{
  self->setRotation(*pRotation);
}

void CalCoreBone_SetRotationBoneSpace(CalCoreBone *self, CalQuaternion *pRotation)
{
  self->setRotationBoneSpace(*pRotation);
}

void CalCoreBone_SetTranslation(CalCoreBone *self, CalVector *pTranslation)
{
  self->setTranslation(*pTranslation);
}

void CalCoreBone_SetTranslationBoneSpace(CalCoreBone *self, CalVector *pTranslation)
{
  self->setTranslationBoneSpace(*pTranslation);
}

void CalCoreBone_SetUserData(CalCoreBone *self, CalUserData userData)
{
  self->setUserData(userData);
}

//****************************************************************************//
// CalCoreKeyframe wrapper functions definition                               //
//****************************************************************************//

Boolean CalCoreKeyframe_Create(CalCoreKeyframe *self)
{
  return self->create() ? True : False;
}

void CalCoreKeyframe_Delete(CalCoreKeyframe *self)
{
  delete self;
}

void CalCoreKeyframe_Destroy(CalCoreKeyframe *self)
{
  self->destroy();
}

CalQuaternion *CalCoreKeyframe_GetRotation(CalCoreKeyframe *self)
{
  return &(const_cast<CalQuaternion&>(self->getRotation()));
}

float CalCoreKeyframe_GetTime(CalCoreKeyframe *self)
{
  return self->getTime();
}

CalVector *CalCoreKeyframe_GetTranslation(CalCoreKeyframe *self)
{
  return &(const_cast<CalVector&>(self->getTranslation()));
}

CalCoreKeyframe *CalCoreKeyframe_New()
{
  return new CalCoreKeyframe();
}

void CalCoreKeyframe_SetRotation(CalCoreKeyframe *self, CalQuaternion *pRotation)
{
  self->setRotation(*pRotation);
}

void CalCoreKeyframe_SetTime(CalCoreKeyframe *self, float time)
{
  self->setTime(time);
}

void CalCoreKeyframe_SetTranslation(CalCoreKeyframe *self, CalVector *pTranslation)
{
  self->setTranslation(*pTranslation);
}

//****************************************************************************//
// CalCoreMaterial wrapper functions definition                               //
//****************************************************************************//

Boolean CalCoreMaterial_Create(CalCoreMaterial *self)
{
  return self->create() ? True : False;
}

void CalCoreMaterial_Delete(CalCoreMaterial *self)
{
  delete self;
}

void CalCoreMaterial_Destroy(CalCoreMaterial *self)
{
  self->destroy();
}

/*
CalCoreMaterial::Color *CalCoreMaterial_GetAmbientColor(CalCoreMaterial *self)
{
  return &(self->getAmbientColor());
}
*/

/*
CalCoreMaterial::Color *CalCoreMaterial_GetDiffuseColor(CalCoreMaterial *self)
{
  return &(self->getDiffuseColor());
}
*/

int CalCoreMaterial_GetMapCount(CalCoreMaterial *self)
{
  return self->getMapCount();
}

char *CalCoreMaterial_GetMapFilename(CalCoreMaterial *self, int mapId)
{
  return const_cast<char *>(self->getMapFilename(mapId).c_str());
}

CalUserData CalCoreMaterial_GetMapUserData(CalCoreMaterial *self, int mapId)
{
  return self->getMapUserData(mapId);
}

float CalCoreMaterial_GetShininess(CalCoreMaterial *self)
{
  return self->getShininess();
}

/*
CalCoreMaterial::Color *CalCoreMaterial_GetSpecularColor(CalCoreMaterial *self)
{
  return &(self->getSpecularColor());
}
*/

CalUserData CalCoreMaterial_GetUserData(CalCoreMaterial *self)
{
  return self->getUserData();
}

/*
std::vector<Map>& CalCoreMaterial_GetVectorMap(CalCoreMaterial *self)
{
  return self->getVectorMap();
}
*/

CalCoreMaterial *CalCoreMaterial_New()
{
  return new CalCoreMaterial();
}

Boolean CalCoreMaterial_Reserve(CalCoreMaterial *self, int mapCount)
{
  return self->reserve(mapCount) ? True : False;
}

/*
void CalCoreMaterial_SetAmbientColor(CalCoreMaterial *self, CalCoreMaterial::Color *pAmbientColor)
{
  return self->setAmbientColor(*pAmbientColor);
}
*/

/*
void CalCoreMaterial_SetDiffuseColor(CalCoreMaterial *self, CalCoreMaterial::Color *pDiffuseColor)
{
  self->setDiffuseColor(*pDiffuseColor);
}
*/

/*
Boolean CalCoreMaterial_SetMap(CalCoreMaterial *self, int mapId, CalCoreMaterial::Map *pMap)
{
  return self->setMap(mapId, *pMap) ? True : False;
}
*/

Boolean CalCoreMaterial_SetMapUserData(CalCoreMaterial *self, int mapId, CalUserData userData)
{
  return self->setMapUserData(mapId, userData) ? True : False;
}

void CalCoreMaterial_SetShininess(CalCoreMaterial *self, float shininess)
{
  self->setShininess(shininess);
}

/*
void CalCoreMaterial_SetSpecularColor(CalCoreMaterial *self, CalCoreMaterial::Color *pSpecularColor)
{
  self->setSpecularColor(*pSpecularColor);
}
*/

void CalCoreMaterial_SetUserData(CalCoreMaterial *self, CalUserData userData)
{
  self->setUserData(userData);
}

//****************************************************************************//
// CalCoreMesh wrapper functions definition                                   //
//****************************************************************************//

int CalCoreMesh_AddCoreSubmesh(CalCoreMesh *self, CalCoreSubmesh *pCoreSubmesh)
{
  return self->addCoreSubmesh(pCoreSubmesh);
}

Boolean CalCoreMesh_Create(CalCoreMesh *self)
{
  return self->create() ? True : False;
}

void CalCoreMesh_Delete(CalCoreMesh *self)
{
  delete self;
}

void CalCoreMesh_Destroy(CalCoreMesh *self)
{
  self->destroy();
}

CalCoreSubmesh *CalCoreMesh_GetCoreSubmesh(CalCoreMesh *self, int id)
{
  return self->getCoreSubmesh(id);
}

int CalCoreMesh_GetCoreSubmeshCount(CalCoreMesh *self)
{
  return self->getCoreSubmeshCount();
}

/*
std::vector<CalCoreSubmesh *>& CalCoreMesh_GetVectorCoreSubmesh(CalCoreMesh *self)
{
  return self->getVectorCoreSubmesh();
}
*/

CalCoreMesh *CalCoreMesh_New()
{
  return new CalCoreMesh();
}

//****************************************************************************//
// CalCoreModel wrapper functions definition                                  //
//****************************************************************************//

int CalCoreModel_AddCoreAnimation(CalCoreModel *self, CalCoreAnimation *pCoreAnimation)
{
  return self->addCoreAnimation(pCoreAnimation);
}

int CalCoreModel_AddCoreMaterial(CalCoreModel *self, CalCoreMaterial *pCoreMaterial)
{
  return self->addCoreMaterial(pCoreMaterial);
}

int CalCoreModel_AddCoreMesh(CalCoreModel *self, CalCoreMesh *pCoreMesh)
{
  return self->addCoreMesh(pCoreMesh);
}

Boolean CalCoreModel_Create(CalCoreModel *self, char *strName)
{
  return self->createWithName(strName) ? True : False;
}

Boolean CalCoreModel_CreateCoreMaterialThread(CalCoreModel *self, int coreMaterialThreadId)
{
  return self->createCoreMaterialThread(coreMaterialThreadId) ? True : False;
}

void CalCoreModel_Delete(CalCoreModel *self)
{
  delete self;
}

void CalCoreModel_Destroy(CalCoreModel *self)
{
  self->destroy();
}

CalCoreAnimation *CalCoreModel_GetCoreAnimation(CalCoreModel *self, int coreAnimationId)
{
  return self->getCoreAnimation(coreAnimationId);
}

int CalCoreModel_GetCoreAnimationMaxId(CalCoreModel *self)
{
  return self->getCoreAnimationMaxId();
}

CalCoreMaterial *CalCoreModel_GetCoreMaterial(CalCoreModel *self, int coreMaterialId)
{
  return self->getCoreMaterial(coreMaterialId);
}

int CalCoreModel_GetCoreMaterialCount(CalCoreModel *self)
{
  return self->getCoreMaterialCount();
}

int CalCoreModel_GetCoreMaterialId(CalCoreModel *self, int coreMaterialThreadId, int coreMaterialSetId)
{
  return self->getCoreMaterialId(coreMaterialThreadId, coreMaterialSetId);
}

CalCoreMesh *CalCoreModel_GetCoreMesh(CalCoreModel *self, int coreMeshId)
{
  return self->getCoreMesh(coreMeshId);
}

int CalCoreModel_GetCoreMeshCount(CalCoreModel *self)
{
  return self->getCoreMeshCount();
}

CalCoreSkeleton *CalCoreModel_GetCoreSkeleton(CalCoreModel *self)
{
  return self->getCoreSkeleton();
}

CalUserData CalCoreModel_GetUserData(CalCoreModel *self)
{
  return self->getUserData();
}

int CalCoreModel_LoadCoreAnimation(CalCoreModel *self, char *strFilename)
{
  return self->loadCoreAnimation(strFilename);
}

int CalCoreModel_LoadCoreMaterial(CalCoreModel *self, char *strFilename)
{
  return self->loadCoreMaterial(strFilename);
}

int CalCoreModel_LoadCoreMesh(CalCoreModel *self, char *strFilename)
{
  return self->loadCoreMesh(strFilename);
}

Boolean CalCoreModel_LoadCoreSkeleton(CalCoreModel *self, char *strFilename)
{
  return self->loadCoreSkeleton(strFilename) ? True : False;
}

CalCoreModel *CalCoreModel_New()
{
  return new CalCoreModel();
}

Boolean CalCoreModel_SaveCoreAnimation(CalCoreModel *self, char *strFilename, int coreAnimationId)
{
  return self->saveCoreAnimation(strFilename, coreAnimationId) ? True : False;
}

Boolean CalCoreModel_SaveCoreMaterial(CalCoreModel *self, char *strFilename, int coreMaterialId)
{
  return self->saveCoreMaterial(strFilename, coreMaterialId) ? True : False;
}

Boolean CalCoreModel_SaveCoreMesh(CalCoreModel *self, char *strFilename, int coreMeshId)
{
  return self->saveCoreMesh(strFilename, coreMeshId) ? True : False;
}

Boolean CalCoreModel_SaveCoreSkeleton(CalCoreModel *self, char *strFilename)
{
  return self->saveCoreSkeleton(strFilename) ? True : False;
}

Boolean CalCoreModel_SetCoreMaterialId(CalCoreModel *self, int coreMaterialThreadId, int coreMaterialSetId, int coreMaterialId)
{
  return self->setCoreMaterialId(coreMaterialThreadId, coreMaterialSetId, coreMaterialId) ? True : False;
}

void CalCoreModel_SetCoreSkeleton(CalCoreModel *self, CalCoreSkeleton *pCoreSkeleton)
{
  self->setCoreSkeleton(pCoreSkeleton);
}

void CalCoreModel_SetUserData(CalCoreModel *self, CalUserData userData)
{
  self->setUserData(userData);
}

//****************************************************************************//
// CalCoreSkeleton wrapper functions definition                               //
//****************************************************************************//

int CalCoreSkeleton_AddCoreBone(CalCoreSkeleton *self, CalCoreBone *pCoreBone)
{
  return self->addCoreBone(pCoreBone);
}

void CalCoreSkeleton_CalculateState(CalCoreSkeleton *self)
{
  self->calculateState();
}


Boolean CalCoreSkeleton_Create(CalCoreSkeleton *self)
{
  return self->create() ? True : False;
}

void CalCoreSkeleton_Delete(CalCoreSkeleton *self)
{
  delete self;
}

void CalCoreSkeleton_Destroy(CalCoreSkeleton *self)
{
  self->destroy();
}

CalCoreBone *CalCoreSkeleton_GetCoreBone(CalCoreSkeleton *self, int coreBoneId)
{
  return self->getCoreBone(coreBoneId);
}

int CalCoreSkeleton_GetCoreBoneId(CalCoreSkeleton *self, char *strName)
{
  return self->getCoreBoneId(strName);
}

/*
std::list<int>& CalCoreSkeleton_GetListRootCoreBoneId(CalCoreSkeleton *self)
{
  return self->getlistRootCoreBoneId();
}
*/


/*
std::vector<CalCoreBone *>& CalCoreSkeleton_GetVectorCoreBone(CalCoreSkeleton *self)
{
  return self->getVectorCoreBone();
}
*/

CalCoreSkeleton *CalCoreSkeleton_New()
{
  return new CalCoreSkeleton();
}

//****************************************************************************//
// CalCoreSubmesh wrapper functions definition                                //
//****************************************************************************//

Boolean CalCoreSubmesh_Create(CalCoreSubmesh *self)
{
  return self->create() ? True : False;
}

void CalCoreSubmesh_Delete(CalCoreSubmesh *self)
{
  delete self;
}

void CalCoreSubmesh_Destroy(CalCoreSubmesh *self)
{
  self->destroy();
}

int CalCoreSubmesh_GetCoreMaterialThreadId(CalCoreSubmesh *self)
{
  return self->getCoreMaterialThreadId();
}

int CalCoreSubmesh_GetFaceCount(CalCoreSubmesh *self)
{
  return self->getFaceCount();
}

int CalCoreSubmesh_GetLodCount(CalCoreSubmesh *self)
{
  return self->getLodCount();
}

int CalCoreSubmesh_GetSpringCount(CalCoreSubmesh *self)
{
  return self->getSpringCount();
}

/*
std::vector<CalCoreSubmesh::Face>& CalCoreSubmesh_GetVectorFace(CalCoreSubmesh *self)
{
  return self->getVectorFace();
}
*/

/*
std::vector<CalCoreSubmesh::PhysicalProperty>& CalCoreSubmesh_GetVectorPhysicalProperty(CalCoreSubmesh *self)
{
  return self->getVectorPhysicalProperty();
}
*/

/*
std::vector<CalCoreSubmesh::Spring>& CalCoreSubmesh_GetVectorSpring(CalCoreSubmesh *self)
{
  return self->getVectorSpring();
}
*/

/*
std::vector<std::vector<CalCoreSubmesh::TextureCoordinate> >& CalCoreSubmesh_GetVectorVectorTextureCoordinate(CalCoreSubmesh *self)
{
  return self->getVectorVectorTextureCoordinate();
}
*/

/*
std::vector<CalCoreSubmesh::Vertex>& CalCoreSubmesh_GetVectorVertex(CalCoreSubmesh *self)
{
  return self->getVectorVertex();
}
*/

int CalCoreSubmesh_GetVertexCount(CalCoreSubmesh *self)
{
  return self->getVertexCount();
}

CalCoreSubmesh *CalCoreSubmesh_New()
{
  return new CalCoreSubmesh();
}

Boolean CalCoreSubmesh_Reserve(CalCoreSubmesh *self, int vertexCount, int textureCoordinateCount, int faceCount, int springCount)
{
  return self->reserve(vertexCount, textureCoordinateCount, faceCount, springCount) ? True : False;
}

void CalCoreSubmesh_SetCoreMaterialThreadId(CalCoreSubmesh *self, int coreMaterialThreadId)
{
  self->setCoreMaterialThreadId(coreMaterialThreadId);
}

/*
Boolean CalCoreSubmesh_SetFace(CalCoreSubmesh *self, int faceId, CalCoreSubmesh::Face *pFace)
{
  return self->setFace(faceId, *pFace) ? True : False;
}
*/

void CalCoreSubmesh_SetLodCount(CalCoreSubmesh *self, int lodCount)
{
  self->setLodCount(lodCount);
}

/*
Boolean CalCoreSubmesh_SetPhysicalProperty(CalCoreSubmesh *self, int vertexId, CalCoreSubmesh::PhysicalProperty *pPhysicalProperty)
{
  return self->setPhysicalProperty(vertexId, *pPhysicalProperty) ? True : False;
}
*/

/*
Boolean CalCoreSubmesh_SetSpring(CalCoreSubmesh *self, int springId, CalCoreSubmesh::Spring *pSpring)
{
  return self->setSpring(springId, *pSpring) ? True : False;
}
*/

/*
Boolean CalCoreSubmesh_SetTextureCoordinate(CalCoreSubmesh *self, int vertexId, int textureCoordinateId, CalCoreSubmesh::TextureCoordinate *pTextureCoordinate)
{
  return self->setTextureCoordinate(vertexId, textureCoordinateId, *pTextureCoordinate) ? True : False;
}
*/

/*
Boolean CalCoreSubmesh_SetVertex(CalCoreSubmesh *self, int vertexId, CalCoreSubmesh::Vertex *pVertex)
{
  return self->setVertex(vertexId, *pVertex) ? True : False;
}
*/

Boolean CalCoreSubmesh_IsTangentsEnabled(CalCoreSubmesh *self, int mapId)
{
  return self->isTangentsEnabled(mapId) ? True : False;
}

Boolean CalCoreSubmesh_EnableTangents(struct CalCoreSubmesh *self, int mapId, bool enabled)
{
  return self->enableTangents(mapId, enabled) ? True : False;
}

//****************************************************************************//
// CalCoreTrack wrapper functions definition                                  //
//****************************************************************************//

Boolean CalCoreTrack_AddCoreKeyframe(CalCoreTrack *self, CalCoreKeyframe *pCoreKeyframe)
{
  return self->addCoreKeyframe(pCoreKeyframe) ? True : False;
}

Boolean CalCoreTrack_Create(CalCoreTrack *self)
{
  self->create();
  return True;
}

void CalCoreTrack_Delete(CalCoreTrack *self)
{
  delete self;
}

void CalCoreTrack_Destroy(CalCoreTrack *self)
{
  self->destroy();
}

int CalCoreTrack_GetCoreBoneId(CalCoreTrack *self)
{
  return self->getCoreBoneId();
}

/*
std::map<float, CalCoreKeyframe *>& CalCoreTrack_GetMapCoreKeyframe(CalCoreTrack *self)
{
  return self->getMapCoreKeyframe();
}
*/

Boolean CalCoreTrack_GetState(CalCoreTrack *self, float time, CalVector *pTranslation, CalQuaternion *pRotation)
{
  return self->getState(time, *pTranslation, *pRotation) ? True : False;
}

CalCoreTrack *CalCoreTrack_New()
{
  return new CalCoreTrack();
}

Boolean CalCoreTrack_SetCoreBoneId(CalCoreTrack *self, int coreBoneId)
{
  return self->setCoreBoneId(coreBoneId) ? True : False;
}

//****************************************************************************//
// CalError wrapper functions definition                                      //
//****************************************************************************//

CalErrorCode CalError_GetLastErrorCode()
{
  return (CalErrorCode)CalError::getLastErrorCode();
}

char *CalError_GetLastErrorDescription()
{
  static std::string strDescription;
  strDescription = CalError::getLastErrorDescription();

  return const_cast<char *>(strDescription.c_str());
}

char *CalError_GetLastErrorFile()
{
  return const_cast<char *>(CalError::getLastErrorFile());
}

int CalError_GetLastErrorLine()
{
  return CalError::getLastErrorLine();
}

char *CalError_GetLastErrorText()
{
  return const_cast<char *>(CalError::getLastErrorText());
}

void CalError_PrintLastError()
{
  CalError::printLastError();
}

void CalError_SetLastError(CalErrorCode code, char *strFile, int line, char *strText)
{
  CalError::setLastError((CalError::Code)code, strFile, line, strText);
}

//****************************************************************************//
// CalLoader wrapper functions definition                                     //
//****************************************************************************//

void CalLoader_Delete(CalLoader *self)
{
  delete self;
}

CalCoreAnimation *CalLoader_LoadCoreAnimationFromBuffer(CalLoader *self, char *buf, unsigned int len)
{
  return self->loadCoreAnimationFromBuffer(buf, len, NULL);
}

CalCoreAnimatedMorph *CalLoader_LoadCoreAnimatedMorphFromBuffer(CalLoader *self, char *buf, unsigned int len)
{
  return self->loadCoreAnimatedMorphFromBuffer(buf, len);
}

CalCoreMaterial *CalLoader_LoadCoreMaterialFromBuffer(CalLoader *self, char *buf, unsigned int len)
{
  return self->loadCoreMaterialFromBuffer(buf, len);
}

CalCoreMesh *CalLoader_LoadCoreMeshFromBuffer(CalLoader *self, char *buf, unsigned int len)
{
  return self->loadCoreMeshFromBuffer(buf, len);
}

CalCoreSkeleton *CalLoader_LoadCoreSkeletonFromBuffer(CalLoader *self, char *buf, unsigned int len)
{
  return self->loadCoreSkeletonFromBuffer(buf, len);
}

void CalLoader_CompressCoreAnimation( CalLoader *self, CalCoreAnimation * anim, CalCoreSkeleton * skelOrNull )
{
  self->compressCoreAnimation( anim, skelOrNull );
}


CalLoader *CalLoader_New()
{
  return new CalLoader();
}

//****************************************************************************//
// CalMesh wrapper functions definition                                       //
//****************************************************************************//

Boolean CalMesh_Create(CalMesh *self, CalCoreMesh *pCoreMesh)
{
  return self->create(pCoreMesh) ? True : False;
}

void CalMesh_Delete(CalMesh *self)
{
  delete self;
}

void CalMesh_Destroy(CalMesh *self)
{
  self->destroy();
}

CalCoreMesh *CalMesh_GetCoreMesh(CalMesh *self)
{
  return self->getCoreMesh();
}

CalSubmesh *CalMesh_GetSubmesh(CalMesh *self, int id)
{
  return self->getSubmesh(id);
}

int CalMesh_GetSubmeshCount(CalMesh *self)
{
  return self->getSubmeshCount();
}

/*
std::vector<CalSubmesh *>& CalMesh_GetVectorSubmesh(CalMesh *self)
{
  return self->getVectorSubmesh();
}
*/

CalMesh *CalMesh_New()
{
  return new CalMesh();
}

void CalMesh_SetLodLevel(CalMesh *self, float lodLevel)
{
  self->setLodLevel(lodLevel);
}

void CalMesh_SetMaterialSet(CalMesh *self, int setId)
{
  self->setMaterialSet(setId);
}

void CalMesh_SetModel(CalMesh *self, CalModel *pModel)
{
  self->setModel(pModel);
}

//****************************************************************************//
// CalMixer wrapper functions definition                                      //
//****************************************************************************//

Boolean CalMixer_Create(CalMixer *self, CalModel *pModel)
{
  return self->create(pModel) ? True : False;
}

void CalMixer_Delete(CalMixer *self)
{
  delete self;
}

void CalMixer_Destroy(CalMixer *self)
{
  self->destroy();
}

Boolean CalMixer_ExecuteAction(CalMixer *self, int id, float delayIn, float delayOut)
{
  return self->executeAction(id, delayIn, delayOut, 1.0f) ? True : False;
}

CalMixer *CalMixer_New()
{
  return new CalMixer();
}

void CalMixer_UpdateAnimation(CalMixer *self, float deltaTime)
{
  self->updateAnimation(deltaTime);
}

void CalMixer_UpdateSkeleton(CalMixer *self)
{
  self->updateSkeleton();
}

//****************************************************************************//
// CalModel wrapper functions definition                                      //
//****************************************************************************//

Boolean CalModel_AttachMesh(CalModel *self, int coreMeshId)
{
  return self->attachMesh(coreMeshId) ? True : False;
}

Boolean CalModel_Create(CalModel *self, CalCoreModel *pCoreModel)
{
  return self->create(pCoreModel) ? True : False;
}

void CalModel_Delete(CalModel *self)
{
  delete self;
}

void CalModel_Destroy(CalModel *self)
{
  self->destroy();
}

Boolean CalModel_DetachMesh(CalModel *self, int coreMeshId)
{
  return self->detachMesh(coreMeshId) ? True : False;
}

CalCoreModel *CalModel_GetCoreModel(CalModel *self)
{
  return self->getCoreModel();
}

CalMesh *CalModel_GetMesh(CalModel *self, int coreMeshId)
{
  return self->getMesh(coreMeshId);
}

CalMixer *CalModel_GetMixer(CalModel *self)
{
  return self->getMixer();
}

CalPhysique *CalModel_GetPhysique(CalModel *self)
{
  return self->getPhysique();
}

CalRenderer *CalModel_GetRenderer(CalModel *self)
{
  return self->getRenderer();
}

CalSkeleton *CalModel_GetSkeleton(CalModel *self)
{
  return self->getSkeleton();
}

CalSpringSystem *CalModel_GetSpringSystem(CalModel *self)
{
  return self->getSpringSystem();
}

CalUserData CalModel_GetUserData(CalModel *self)
{
  return self->getUserData();
}

/*
std::vector<CalMesh *>& CalModel_GetVectorMesh(CalModel *self)
{
  return self->getVectorMesh();
}
*/

CalModel *CalModel_New()
{
  return new CalModel();
}

void CalModel_SetLodLevel(CalModel *self, float lodLevel)
{
  self->setLodLevel(lodLevel);
}

void CalModel_SetMaterialSet(CalModel *self, int setId)
{
  self->setMaterialSet(setId);
}

void CalModel_SetUserData(CalModel *self, CalUserData userData)
{
  self->setUserData(userData);
}

void CalModel_Update(CalModel *self, float deltaTime)
{
  self->update(deltaTime);
}

//****************************************************************************//
// CalPhysique wrapper functions definition                                   //
//****************************************************************************//

int CalPhysique_CalculateNormals(CalPhysique *self, CalSubmesh *pSubmesh, float *pNormalBuffer)
{
  return self->calculateNormals(pSubmesh, pNormalBuffer);
}

int CalPhysique_CalculateVertices(CalPhysique *self, CalSubmesh *pSubmesh, float *pVertexBuffer)
{
  return self->calculateVertices(pSubmesh, pVertexBuffer);
}

int CalPhysique_CalculateVerticesAndNormals(CalPhysique *self, CalSubmesh *pSubmesh, float *pVertexBuffer)
{
  return self->calculateVerticesAndNormals(pSubmesh, pVertexBuffer);
}

int CalPhysique_CalculateVerticesNormalsAndTexCoords(CalPhysique *self, CalSubmesh *pSubmesh, float *pVertexBuffer, int NumTexCoords)
{
  return self->calculateVerticesNormalsAndTexCoords(pSubmesh, pVertexBuffer, NumTexCoords);
}

int CalPhysique_CalculateTangentSpaces(CalPhysique *self, CalSubmesh *pSubmesh, int mapId, float *pTangentSpaceBuffer)
{
  return self->calculateTangentSpaces(pSubmesh, mapId, pTangentSpaceBuffer);
}

Boolean CalPhysique_Create(CalPhysique *self, CalModel *pModel)
{
  return self->create(pModel) ? True : False;
}

void CalPhysique_Delete(CalPhysique *self)
{
  delete self;
}

void CalPhysique_Destroy(CalPhysique *self)
{
  self->destroy();
}

CalPhysique *CalPhysique_New()
{
  return new CalPhysique();
}

void CalPhysique_Update(CalPhysique *self)
{
  self->update();
}

//****************************************************************************//
// CalPlatform wrapper functions definition                                   //
//****************************************************************************//

//****************************************************************************//
// CalQuaternion wrapper functions definition                                 //
//****************************************************************************//

void CalQuaternion_Blend(CalQuaternion *self, float d, CalQuaternion *pQ)
{
  self->blend(d, *pQ);
}

void CalQuaternion_Clear(CalQuaternion *self)
{
  self->clear();
}

void CalQuaternion_Conjugate(CalQuaternion *self)
{
  self->conjugate();
}

void CalQuaternion_Delete(CalQuaternion *self)
{
  delete self;
}

void CalQuaternion_Equal(CalQuaternion *self, CalQuaternion *pQ)
{
  *self = *pQ;
}

float *CalQuaternion_Get(CalQuaternion *self)
{
  return &(self->x);
}

void CalQuaternion_Multiply(CalQuaternion *self, CalQuaternion *pQ)
{
  *self *= *pQ;
}

void CalQuaternion_MultiplyVector(CalQuaternion *self, CalVector *pV)
{
  *self *= *pV;
}

CalQuaternion *CalQuaternion_New()
{
  return new CalQuaternion();
}

void CalQuaternion_Op_Multiply(CalQuaternion *pResult, CalQuaternion *pQ, CalQuaternion *pR)
{
  *pResult = *pQ * *pR;
}

void CalQuaternion_Set(CalQuaternion *self, float qx, float qy, float qz, float qw)
{
  self->set(qx, qy, qz, qw);
}

//****************************************************************************//
// CalRender wrapper functions definition                                         //
//****************************************************************************//

Boolean CalRenderer_BeginRendering(CalRenderer *self)
{
  return self->beginRendering() ? True : False;
}

Boolean CalRenderer_Create(CalRenderer *self, CalModel *pModel)
{
  return self->create(pModel) ? True : False;
}

void CalRenderer_Delete(CalRenderer *self)
{
  delete self;
}

void CalRenderer_Destroy(CalRenderer *self)
{
  self->destroy();
}

void CalRenderer_EndRendering(CalRenderer *self)
{
  self->endRendering();
}

void CalRenderer_GetAmbientColor(CalRenderer *self, unsigned char *pColorBuffer)
{
  self->getAmbientColor(pColorBuffer);
}

void CalRenderer_GetDiffuseColor(CalRenderer *self, unsigned char *pColorBuffer)
{
  self->getDiffuseColor(pColorBuffer);
}

int CalRenderer_GetFaceCount(CalRenderer *self)
{
  return self->getFaceCount();
}

int CalRenderer_GetFaces(CalRenderer *self, CalIndex *pFaceBuffer)
{
  return self->getFaces(pFaceBuffer);
}

int CalRenderer_GetMapCount(CalRenderer *self)
{
  return self->getMapCount();
}

CalUserData CalRenderer_GetMapUserData(CalRenderer *self, int mapId)
{
  return (CalUserData)self->getMapUserData(mapId);
}

int CalRenderer_GetMeshCount(CalRenderer *self)
{
  return self->getMeshCount();
}

int CalRenderer_GetNormals(CalRenderer *self, float *pNormalBuffer)
{
  return self->getNormals(pNormalBuffer);
}

float CalRenderer_GetShininess(CalRenderer *self)
{
  return self->getShininess();
}

void CalRenderer_GetSpecularColor(CalRenderer *self, unsigned char *pColorBuffer)
{
  self->getSpecularColor(pColorBuffer);
}

int CalRenderer_GetSubmeshCount(CalRenderer *self, int meshId)
{
  return self->getSubmeshCount(meshId);
}

int CalRenderer_GetTextureCoordinates(CalRenderer *self, int mapId, float *pTextureCoordinateBuffer)
{
  return self->getTextureCoordinates(mapId, pTextureCoordinateBuffer);
}

int CalRenderer_GetVertexCount(CalRenderer *self)
{
  return self->getVertexCount();
}

int CalRenderer_GetVertices(CalRenderer *self, float *pVertexBuffer)
{
  return self->getVertices(pVertexBuffer);
}

int CalRenderer_GetVerticesAndNormals(CalRenderer *self, float *pVertexBuffer)
{
  return self->getVerticesAndNormals(pVertexBuffer);
}

int CalRenderer_GetVerticesNormalsAndTexCoords(CalRenderer *self, float *pVertexBuffer, int NumTexCoords)
{
  return self->getVerticesNormalsAndTexCoords(pVertexBuffer,NumTexCoords);
}

int CalRenderer_GetTangentSpaces(CalRenderer *self, int mapId, float *pTangentSpaceBuffer)
{
  return self->getTangentSpaces(mapId, pTangentSpaceBuffer);
}

Boolean CalRenderer_IsTangentsEnabled(CalRenderer *self, int mapId)
{
  return self->isTangentsEnabled(mapId) ? True : False;
}

CalRenderer *CalRenderer_New()
{
  return new CalRenderer();
}

Boolean CalRenderer_SelectMeshSubmesh(CalRenderer *self, int meshId, int submeshId)
{
  return self->selectMeshSubmesh(meshId, submeshId) ? True : False;
}

//****************************************************************************//
// CalPlatform wrapper functions definition                                   //
//****************************************************************************//

void CalSaver_Delete(CalSaver *self)
{
  delete self;
}

CalSaver *CalSaver_New()
{
  return new CalSaver();
}

Boolean CalSaver_SaveCoreAnimation(CalSaver *self, char *strFilename, CalCoreAnimation *pCoreAnimation)
{
  return self->saveCoreAnimation(strFilename, pCoreAnimation) ? True : False;
}

Boolean CalSaver_SaveCoreAnimatedMorph(CalSaver *self, char *strFilename, CalCoreAnimatedMorph *pCoreAnimatedMorph)
{
  return self->saveCoreAnimatedMorph(strFilename, pCoreAnimatedMorph) ? True : False;
}

Boolean CalSaver_SaveCoreMaterial(CalSaver *self, char *strFilename, CalCoreMaterial *pCoreMaterial)
{
  return self->saveCoreMaterial(strFilename, pCoreMaterial) ? True : False;
}

Boolean CalSaver_SaveCoreMesh(CalSaver *self, char *strFilename, CalCoreMesh *pCoreMesh)
{
  return self->saveCoreMesh(strFilename, pCoreMesh) ? True : False;
}

Boolean CalSaver_SaveCoreSkeleton(CalSaver *self, char *strFilename, CalCoreSkeleton *pCoreSkeleton)
{
  return self->saveCoreSkeleton(strFilename, pCoreSkeleton) ? True : False;
}

//****************************************************************************//
// CalSkeleton wrapper functions definition                                   //
//****************************************************************************//

void CalSkeleton_CalculateState(CalSkeleton *self)
{
  self->calculateState();
}

void CalSkeleton_ClearState(CalSkeleton *self)
{
  self->clearState();
}

Boolean CalSkeleton_Create(CalSkeleton *self, CalCoreSkeleton *pCoreSkeleton)
{
  return self->create(pCoreSkeleton) ? True : False;
}

void CalSkeleton_Delete(CalSkeleton *self)
{
  delete self;
}

void CalSkeleton_Destroy(CalSkeleton *self)
{
  self->destroy();
}

CalBone *CalSkeleton_GetBone(CalSkeleton *self, int boneId)
{
  return self->getBone(boneId);
}

CalCoreSkeleton *CalSkeleton_GetCoreSkeleton(CalSkeleton *self)
{
  return self->getCoreSkeleton();
}

/*
std::vector<CalBone *>& CalSkeleton_GetVectorBone(CalSkeleton *self)
{
  return self->getVectorBone();
}
*/

void CalSkeleton_LockState(CalSkeleton *self)
{
  self->lockState();
}

CalSkeleton *CalSkeleton_New()
{
  return new CalSkeleton();
}

// DEBUG-CODE
int CalSkeleton_GetBonePoints(CalSkeleton *self, float *pPoints)
{
  return self->getBonePoints(pPoints);
}

// DEBUG-CODE
int CalSkeleton_GetBonePointsStatic(CalSkeleton *self, float *pPoints)
{
  return self->getBonePointsStatic(pPoints);
}

// DEBUG-CODE
int CalSkeleton_GetBoneLines(CalSkeleton *self, float *pLines)
{
  return self->getBoneLines(pLines);
}

// DEBUG-CODE
int CalSkeleton_GetBoneLinesStatic(CalSkeleton *self, float *pLines)
{
  return self->getBoneLinesStatic(pLines);
}

//****************************************************************************//
// CalSpringSystem wrapper functions definition                               //
//****************************************************************************//

void CalSpringSystem_CalculateForces(CalSpringSystem *self, CalSubmesh *pSubmesh, float deltaTime)
{
  self->calculateForces(pSubmesh, deltaTime);
}

void CalSpringSystem_CalculateVertices(CalSpringSystem *self, CalSubmesh *pSubmesh, float deltaTime)
{
  self->calculateVertices(pSubmesh, deltaTime);
}

Boolean CalSpringSystem_Create(CalSpringSystem *self, CalModel *pModel)
{
  return self->create(pModel) ? True : False;
}

void CalSpringSystem_Delete(CalSpringSystem *self)
{
  delete self;
}

void CalSpringSystem_Destroy(CalSpringSystem *self)
{
  self->destroy();
}

CalSpringSystem *CalSpringSystem_New()
{
  return new CalSpringSystem();
}

void CalSpringSystem_Update(CalSpringSystem *self, float deltaTime)
{
  self->update(deltaTime);
}

//****************************************************************************//
// CalSubmesh wrapper functions definition                                    //
//****************************************************************************//

Boolean CalSubmesh_Create(CalSubmesh *self, CalCoreSubmesh *pCoreSubmesh)
{
  return self->create(pCoreSubmesh) ? True : False;
}

void CalSubmesh_Delete(CalSubmesh *self)
{
  delete self;
}

void CalSubmesh_Destroy(CalSubmesh *self)
{
  self->destroy();
}

CalCoreSubmesh *CalSubmesh_GetCoreSubmesh(CalSubmesh *self)
{
  return self->getCoreSubmesh();
}

int CalSubmesh_GetCoreMaterialId(CalSubmesh *self)
{
  return self->getCoreMaterialId();
}

int CalSubmesh_GetFaceCount(CalSubmesh *self)
{
  return self->getFaceCount();
}

int CalSubmesh_GetFaces(CalSubmesh *self, CalIndex *pFaceBuffer)
{
  return self->getFaces(pFaceBuffer);
}

/*
std::vector<CalVector>& CalSubmesh_GetVectorNormal(CalSubmesh *self)
{
  return self->getVectorNormal();
}
*/
/*
std::vector<CalSubmesh::PhysicalProperty>& CalSubmesh_GetVectorPhysicalProperty(CalSubmesh *self)
{
  return self->getVectorPhysicalProperty();
}
*/

/*
std::vector<CalVector>& CalSubmesh_GetVectorVertex(CalSubmesh *self)
{
  return self->getVectorVertex();
}
*/

int CalSubmesh_GetVertexCount(CalSubmesh *self)
{
  return self->getVertexCount();
}

Boolean CalSubmesh_HasInternalData(CalSubmesh *self)
{
  return self->hasInternalData() ? True : False;
}

CalSubmesh *CalSubmesh_New()
{
  return new CalSubmesh();
}

void CalSubmesh_SetCoreMaterialId(CalSubmesh *self, int coreMaterialId)
{
  self->setCoreMaterialId(coreMaterialId);
}

void CalSubmesh_SetLodLevel(CalSubmesh *self, float lodLevel)
{
  self->setLodLevel(lodLevel);
}

//****************************************************************************//
// CalVector wrapper functions definition                                     //
//****************************************************************************//

void CalVector_Add(CalVector *self, CalVector *pV)
{
  *self += *pV;
}

void CalVector_Blend(CalVector *self, float d, CalVector *pV)
{
  self->blend(d, *pV);
}

void CalVector_Clear(CalVector *self)
{
  self->clear();
}

void CalVector_Delete(CalVector *self)
{
  delete self;
}

void CalVector_Equal(CalVector *self, CalVector *pV)
{
  *self = *pV;
}

void CalVector_InverseScale(CalVector *self, float d)
{
  *self /= d;
}

float *CalVector_Get(CalVector *self)
{
  return &(self->x);
}

float CalVector_Length(CalVector *self)
{
  return self->length();
}

CalVector *CalVector_New()
{
  return new CalVector();
}

float CalVector_Normalize(CalVector *self)
{
  return self->normalize();
}

void CalVector_Op_Add(CalVector *pResult, CalVector *pV, CalVector *pU)
{
  *pResult = *pV + *pU;
}

void CalVector_Op_Subtract(CalVector *pResult, CalVector *pV, CalVector *pU)
{
  *pResult = *pV - *pU;
}

void CalVector_CalVector_Op_Scale(CalVector *pResult, CalVector *pV, float d)
{
  *pResult = *pV * d;
}

void CalVector_CalVector_Op_InverseScale(CalVector *pResult, CalVector *pV, float d)
{
  *pResult = *pV / d;
}

float CalVector_Op_Scalar(CalVector *pV, CalVector *pU)
{
  return *pV * *pU;
}

void CalVector_Op_Cross(CalVector *pResult, CalVector *pV, CalVector *pU)
{
  *pResult = *pV % *pU;
}

void CalVector_Scale(CalVector *self, float d)
{
  *self *= d;
}

void CalVector_Set(CalVector *self, float vx, float vy, float vz)
{
  self->set(vx, vy, vz);
}

void CalVector_Subtract(CalVector *self, CalVector *pV)
{
  *self = *pV;
}

void CalVector_Transform(CalVector *self, CalQuaternion *pQ)
{
  *self *= *pQ;
}

//****************************************************************************//
