//****************************************************************************//
// renderer.h                                                                 //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_RENDERER_H
#define CAL_RENDERER_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/global.h"

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

class CalModel;
class CalSubmesh;

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

 /*****************************************************************************/
/** The renderer class.
  *****************************************************************************/

class CAL3D_API CalRenderer
{
// member variables
public:
  CalModel *m_pModel;
  CalSubmesh *m_pSelectedSubmesh;

// constructors/destructor
public:
  CalRenderer();
  CalRenderer(CalRenderer* pRenderer); 
  virtual ~CalRenderer();

// member functions	
public:
  bool beginRendering();
  bool create(CalModel *pModel);
  void destroy();
  void endRendering();
  void getAmbientColor(unsigned char *pColorBuffer);
  void getDiffuseColor(unsigned char *pColorBuffer);
  int getFaceCount();
  int getFaces(CalIndex *pFaceBuffer);
  CalModel * getModel() { return m_pModel; }
  int getMapCount();
  Cal::UserData getMapUserData(int mapId);
  int getMeshCount();
  int getNormals(float *pNormalBuffer);
  float getShininess();
  void getSpecularColor(unsigned char *pColorBuffer);
  int getSubmeshCount(int meshId);
  int getTextureCoordinates(int mapId, float *pTextureCoordinateBuffer);
  int getVertexCount();
  int getVertices(float *pVertexBuffer);
  int getVertColors(float *pVertexBuffer);
  int getVertColorsAsStandardPixels( unsigned int *pVertexBuffer);
  int getTangentSpaces(int mapId, float *pTangentSpaceBuffer);
  int getVerticesAndNormals(float *pVertexBuffer);
  int getVerticesNormalsAndTexCoords(float *pVertexBuffer,int NumTexCoords=1);
  bool isTangentsEnabled(int mapId);
  bool selectMeshSubmesh(int meshId, int submeshId);
  void setNormalization(bool normalize);
  bool textureCoordinatesForMapValid( int mapId );
  bool hasNonWhiteVertexColors();

};

#endif

//****************************************************************************//
