//****************************************************************************//
// bone.h                                                                     //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_BONE_H
#define CAL_BONE_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/global.h"
#include "cal3d/vector.h"
#include "cal3d/quaternion.h"
#include "cal3d/matrix.h"
#include "cal3d/corebone.h"

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

//class CalCoreBone;
class CalSkeleton;
class CalModel;
class CalCoreModel;
//class CalBoundingBox;

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

 /*****************************************************************************/
/** The bone class.
  *****************************************************************************/

class CAL3D_API CalBone
{
// member variables
protected:
  CalCoreBone *m_pCoreBone;
  CalSkeleton *m_pSkeleton;
  float m_accumulatedWeight;
  float m_accumulatedWeightAbsolute;
  float m_accumulatedReplacementAttenuation;
  float m_firstBlendScale;
  CalVector m_meshScaleAbsolute; // w.r.t. absolute coord system in 3dsMax (Z up), not local coord of bone.
  CalVector m_translation;
  CalQuaternion m_rotation;
  CalVector m_translationAbsolute;
  CalQuaternion m_rotationAbsolute;
  CalVector m_translationBoneSpace;
  CalQuaternion m_rotationBoneSpace;
  CalMatrix m_transformMatrix;  
  CalBoundingBox m_boundingBox;


// constructors/destructor
public:
  CalBone();
  virtual ~CalBone();

// member functions
public:
  void blendState(float unrampedWeight, const CalVector& translation, 
    const CalQuaternion & rotation, float scale = 1.0f,
    bool replace = false, float rampValue = 1.0f );
  void calculateState();
  void clearState();
  bool create(CalCoreBone *pCoreBone);
  void destroy();
  CalCoreBone *getCoreBone();
  void setCoreState();
  void setCoreStateRecursive();
  void setRotation(const CalQuaternion& rotation);
  const CalQuaternion& getRotation();
  const CalQuaternion& getRotationAbsolute();
  const CalQuaternion& getRotationBoneSpace();
  void setTranslation(const CalVector& translation);
  const CalVector& getTranslation();
  const CalVector& getTranslationAbsolute();
  inline void setMeshScaleAbsolute( CalVector const & sv ) {
    m_meshScaleAbsolute = sv; }
  inline const CalVector& getTranslationBoneSpace() {
    return m_translationBoneSpace;
  }
  inline const CalMatrix& getTransformMatrix() {
    return m_transformMatrix;
  }
  void lockState();
  void setSkeleton(CalSkeleton *pSkeleton);
  void calculateBoundingBox();
  CalBoundingBox & getBoundingBox();


};

#endif

//****************************************************************************//
