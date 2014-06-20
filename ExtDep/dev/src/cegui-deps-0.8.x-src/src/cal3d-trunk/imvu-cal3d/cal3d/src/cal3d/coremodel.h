//****************************************************************************//
// coremodel.h                                                                //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_COREMODEL_H
#define CAL_COREMODEL_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/global.h"

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

class CalCoreSkeleton;
class CalCoreAnimation;
class CalCoreAnimatedMorph;
class CalCoreMorphAnimation;
class CalCoreMesh;
class CalCoreMaterial;

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

 /*****************************************************************************/
/** The core model class.
  *****************************************************************************/

class CAL3D_API CalCoreModel
{
// member variables
protected:
  std::string m_strName;
  CalCoreSkeleton *m_pCoreSkeleton;
  std::vector<CalCoreAnimation *> m_vectorCoreAnimation;
  std::vector<CalCoreMorphAnimation *> m_vectorCoreMorphAnimation;
  std::vector<CalCoreAnimatedMorph *> m_vectorCoreAnimatedMorph;
  std::vector<CalCoreMesh *> m_vectorCoreMesh;
  std::vector<CalCoreMaterial *> m_vectorCoreMaterial;
  std::map<int, std::map<int, int> > m_mapmapCoreMaterialThread;
  Cal::UserData m_userData;
  std::map<std::string, int> m_animationHelper;
  bool m_coreMeshManagement;
  bool m_coreAnimationManagement;
  unsigned int m_magic;

// constructors/destructor
public:
  CalCoreModel();
  virtual ~CalCoreModel();

// member functions
public:

  int getNumCoreAnimations();

  int getNumCoreAnimatedMorphs();
  int addCoreAnimation(CalCoreAnimation *pCoreAnimation);
  bool removeCoreAnimation( int id );

  bool removeCoreAnimatedMorph( int id );

  int addCoreMorphAnimation(CalCoreMorphAnimation *pCoreMorphAnimation);
  int addCoreAnimatedMorph(CalCoreAnimatedMorph *pCoreAnimatedMorph);
  int addCoreMaterial(CalCoreMaterial *pCoreMaterial);
  int addCoreMesh(CalCoreMesh *pCoreMesh);
  bool createInternal(const std::string& strName);
  bool createWithName( char const * strName);
  bool createCoreMaterialThread(int coreMaterialThreadId);
  void destroy();
  CalCoreAnimation *getCoreAnimation(int coreAnimationId);
  CalCoreMorphAnimation *getCoreMorphAnimation(int coreMorphAnimationId);
  CalCoreAnimatedMorph *getCoreAnimatedMorph(int coreAnimatedMorphId);
  int getCoreAnimationMaxId();
  int getCoreMorphAnimationCount();
  // int getCoreAnimatedMorphCount();
  CalCoreMaterial *getCoreMaterial(int coreMaterialId);
  int getCoreMaterialCount();
  int getCoreMaterialId(int coreMaterialThreadId, int coreMaterialSetId);
  CalCoreMesh *getCoreMesh(int coreMeshId);
  int getCoreMeshCount();
  CalCoreSkeleton *getCoreSkeleton();
  Cal::UserData getUserData();
  int loadCoreAnimation(const std::string& strFilename);
  int loadCoreAnimatedMorph(const std::string& strFilename);
  int loadCoreMaterial(const std::string& strFilename);
  int loadCoreMesh(const std::string& strFilename);
  bool loadCoreSkeleton(const std::string& strFilename);
  bool saveCoreAnimation(const std::string& strFilename, int coreAnimtionId);
  bool saveCoreMaterial(const std::string& strFilename, int coreMaterialId);
  bool saveCoreMesh(const std::string& strFilename, int coreMeshId);
  bool saveCoreSkeleton(const std::string& strFilename);
  bool setCoreMaterialId(int coreMaterialThreadId, int coreMaterialSetId, int coreMaterialId);
  void setCoreSkeleton(CalCoreSkeleton *pCoreSkeleton);
  void setUserData(Cal::UserData userData);
  void addBoneHelper(const std::string& strBoneName, int boneId);
  void addAnimHelper(const std::string& strAnimName, int animId);
  int getBoneId(const std::string& strBoneName);
  int getAnimId(const std::string& strAnimName);
  void scale(float factor);
  void setCoreMeshManagementOn( bool p ) { m_coreMeshManagement = p; }
  bool getCoreMeshManagementOn() { return m_coreMeshManagement; }
  void setCoreAnimationManagementOn( bool p ) { m_coreAnimationManagement = p; }
  bool getCoreAnimationManagementOn() { return m_coreAnimationManagement; }

};

#endif

//****************************************************************************//
