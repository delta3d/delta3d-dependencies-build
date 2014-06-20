#if defined(_MSC_VER) && _MSC_VER <= 1200
#pragma warning(disable: 4786)
#endif

//****************************************************************************//
// coremodel.cpp                                                              //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
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
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/coremodel.h"
#include "cal3d/error.h"
#include "cal3d/coreskeleton.h"
#include "cal3d/coreanimation.h"
#include "cal3d/coremorphanimation.h"
#include "cal3d/coreanimatedmorph.h"
#include "cal3d/coremesh.h"
#include "cal3d/corematerial.h"
#include "cal3d/loader.h"
#include "cal3d/saver.h"

static unsigned int const CalCoreModelMagic = 0x77884455;

 /*****************************************************************************/
/** Constructs the core model instance.
  *
  * This function is the default constructor of the core model instance.
  *****************************************************************************/

CalCoreModel::CalCoreModel()
  : m_pCoreSkeleton(0), m_userData(0)
{
  m_magic = CalCoreModelMagic;
}

 /*****************************************************************************/
/** Destructs the core model instance.
  *
  * This function is the destructor of the core model instance.
  *****************************************************************************/

CalCoreModel::~CalCoreModel()
{
  assert(m_magic == CalCoreModelMagic );
  m_magic = 0;
  assert(m_vectorCoreAnimation.empty());
  assert(m_vectorCoreMorphAnimation.empty());
  assert(m_vectorCoreAnimatedMorph.empty());
  assert(m_vectorCoreMesh.empty());
  assert(m_vectorCoreMaterial.empty());
}



int 

CalCoreModel::getNumCoreAnimations()

{

  int num = m_vectorCoreAnimation.size();

  int r = 0;

  int i;

  for( i = 0; i < num; i++ ) {

    if( m_vectorCoreAnimation[ i ] ) r++;

  }

  return r;

}



int 

CalCoreModel::getNumCoreAnimatedMorphs()

{

  int num = m_vectorCoreAnimatedMorph.size();

  int r = 0;

  int i;

  for( i = 0; i < num; i++ ) {

    if( m_vectorCoreAnimatedMorph[ i ] ) r++;

  }

  return r;

}



 /*****************************************************************************/
/** Adds a core animation.
  *
  * This function adds a core animation to the core model instance.
  *
  * @param pCoreAnimation A pointer to the core animation that should be added.
  *
  * @return One of the following values:
  *         \li the assigned animation \b ID of the added core animation
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreModel::addCoreAnimation(CalCoreAnimation *pCoreAnimation)
{

  int num = m_vectorCoreAnimation.size();

  int i;

  for( i = 0; i < num; i++ ) {

    if( !m_vectorCoreAnimation[ i ] ) {

      m_vectorCoreAnimation[ i ] = pCoreAnimation;

      return i;

    }

  }

  m_vectorCoreAnimation.push_back(pCoreAnimation);

  return num;
}



/*

// Return true if removed.

bool CalCoreModel::removeCoreAnimation(CalCoreAnimation *pCoreAnimation)

{

  int num = m_vectorCoreAnimation.size();

  int i;

  for( i = 0; i < num; i++ ) {

    if( m_vectorCoreAnimation[ i ] == pCoreAnimation ) {

      m_vectorCoreAnimation[ i ] = NULL;

      return true;

    }

  }

  return false;

}

*/



bool CalCoreModel::removeCoreAnimation( int id )

{

  int num = m_vectorCoreAnimation.size();

  if( id >= num || id < 0) return false;

  if( !m_vectorCoreAnimation[ id ] ) return false;

  m_vectorCoreAnimation[ id ] = NULL;

  return true;

}



 /*****************************************************************************/
/** Adds a core animated morph (different from a morph animation).
  *
  * Loads a core animated morph (different from a morph animation), and adds
  * it to the model instance.  The model instance will free the loaded core
  * animated more when the model instance is freed.
  *
  * @param pCoreAnimation A pointer to the core animated morph that should be added.
  *
  * @return One of the following values:
  *         \li the assigned animation \b ID of the added core animated morph
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreModel::addCoreAnimatedMorph(CalCoreAnimatedMorph *pCoreAnimatedMorph)
{
  int num = m_vectorCoreAnimatedMorph.size();

  int i;

  for( i = 0; i < num; i++ ) {

    if( !m_vectorCoreAnimatedMorph[ i ] ) {

      m_vectorCoreAnimatedMorph[ i ] = pCoreAnimatedMorph;

      return i;

    }

  }

  m_vectorCoreAnimatedMorph.push_back(pCoreAnimatedMorph);

  return num;

}


bool CalCoreModel::removeCoreAnimatedMorph( int id )

{

  int num = m_vectorCoreAnimatedMorph.size();

  if( id >= num || id < 0) return false;

  if( !m_vectorCoreAnimatedMorph[ id ] ) return false;

  m_vectorCoreAnimatedMorph[ id ] = NULL;

  return true;

}




 /*****************************************************************************/
/** Adds a core morph animation.
  *
  * This function adds a core morph animation to the core model instance.
  *
  * @param pCoreMorphAnimation A pointer to the core morph animation that 
  *                            should be added.
  *
  * @return One of the following values:
  *         \li the assigned morph animation \b ID of the added core morph animation
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreModel::addCoreMorphAnimation(CalCoreMorphAnimation *pCoreMorphAnimation)
{
  // get the id of the core morph animation
  int morphAnimationId;
  morphAnimationId = m_vectorCoreMorphAnimation.size();

  m_vectorCoreMorphAnimation.push_back(pCoreMorphAnimation);

  return morphAnimationId;
}

 /*****************************************************************************/
/** Adds a core material.
  *
  * This function adds a core material to the core model instance.
  *
  * @param pCoreMaterial A pointer to the core material that should be added.
  *
  * @return One of the following values:
  *         \li the assigned material \b ID of the added core material
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreModel::addCoreMaterial(CalCoreMaterial *pCoreMaterial)
{
  // get the id of the core material
  int materialId;
  materialId = m_vectorCoreMaterial.size();

  m_vectorCoreMaterial.push_back(pCoreMaterial);

  return materialId;
}

 /*****************************************************************************/
/** Adds a core mesh.
  *
  * This function adds a core mesh to the core model instance.
  *
  * @param pCoreMesh A pointer to the core mesh that should be added.
  *
  * @return One of the following values:
  *         \li the assigned mesh \b ID of the added core material
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreModel::addCoreMesh(CalCoreMesh *pCoreMesh)
{
  // get the id of the core mesh
  int meshId;
  meshId = m_vectorCoreMesh.size();

  m_vectorCoreMesh.push_back(pCoreMesh);

  return meshId;
}

 /*****************************************************************************/
/** Creates the core model instance.
  *
  * This function creates the core model instance.
  *
  * @param strName A string that should be used as the name of the core model
  *                instance.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool CalCoreModel::createInternal(const std::string& strName)
{
  assert(m_magic == CalCoreModelMagic );
  m_strName = strName;
  m_coreMeshManagement = true;
  m_coreAnimationManagement = true;
  return true;
}

bool CalCoreModel::createWithName( char const * strName)
{
  std::string name = strName;
  return createInternal( name );
}


 /*****************************************************************************/
/** Creates a core material thread.
  *
  * This function creates a new core material thread with the given ID.
  *
  * @param coreMaterialThreadId The ID of the core material thread that should
  *                             be created.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool CalCoreModel::createCoreMaterialThread(int coreMaterialThreadId)
{
  // insert an empty core material thread with a given id
  std::map<int, int> mapCoreMaterialThreadId;
  m_mapmapCoreMaterialThread.insert(std::make_pair(coreMaterialThreadId, mapCoreMaterialThreadId));

  return true;
}

 /*****************************************************************************/
/** Destroys the core model instance.
  *
  * This function destroys all data stored in the core model instance and frees
  * all allocated memory.
  *****************************************************************************/

void CalCoreModel::destroy()
{
  assert( m_magic == CalCoreModelMagic );

  // destroy all core materials
  std::vector<CalCoreMaterial *>::iterator iteratorCoreMaterial;
  for(iteratorCoreMaterial = m_vectorCoreMaterial.begin(); iteratorCoreMaterial != m_vectorCoreMaterial.end(); ++iteratorCoreMaterial)
  {
    (*iteratorCoreMaterial)->destroy();
    delete (*iteratorCoreMaterial);
  }
  m_vectorCoreMaterial.clear();

  // destroy all core meshes
  std::vector<CalCoreMesh *>::iterator iteratorCoreMesh;
  for(iteratorCoreMesh = m_vectorCoreMesh.begin(); iteratorCoreMesh != m_vectorCoreMesh.end(); ++iteratorCoreMesh)
  {
    if( m_coreMeshManagement ) {
      (*iteratorCoreMesh)->destroy();
      delete (*iteratorCoreMesh);
    }
  }
  m_vectorCoreMesh.clear();

  // destroy all core animations
  std::vector<CalCoreAnimation *>::iterator iteratorCoreAnimation;
  for(iteratorCoreAnimation = m_vectorCoreAnimation.begin(); iteratorCoreAnimation != m_vectorCoreAnimation.end(); ++iteratorCoreAnimation)
  {
    if( m_coreAnimationManagement && ( * iteratorCoreAnimation ) ) {
      (*iteratorCoreAnimation)->destroy();
      delete (*iteratorCoreAnimation);
    }
  }
  m_vectorCoreAnimation.clear();

  // destroy all core animations
  std::vector<CalCoreMorphAnimation *>::iterator iteratorCoreMorphAnimation;
  for(iteratorCoreMorphAnimation = m_vectorCoreMorphAnimation.begin(); iteratorCoreMorphAnimation != 
      m_vectorCoreMorphAnimation.end(); ++iteratorCoreMorphAnimation)
  {
    (*iteratorCoreMorphAnimation)->destroy();
    delete (*iteratorCoreMorphAnimation);
  }
  m_vectorCoreMorphAnimation.clear();

  // destroy all core animated morphs
  std::vector<CalCoreAnimatedMorph *>::iterator iteratorCoreAnimatedMorph;
  for(iteratorCoreAnimatedMorph = m_vectorCoreAnimatedMorph.begin(); iteratorCoreAnimatedMorph != 
      m_vectorCoreAnimatedMorph.end(); ++iteratorCoreAnimatedMorph)
  {



    // I am always managing coreAnimatedMorphs.  However, since I allow the user to remove them,

    // I may still have gaps in my array.
    if( * iteratorCoreAnimatedMorph ) {

      (*iteratorCoreAnimatedMorph)->destroy();
      delete (*iteratorCoreAnimatedMorph);

    }
  }
  m_vectorCoreAnimatedMorph.clear();

  if(m_pCoreSkeleton != 0)
  {
    m_pCoreSkeleton->destroy();
    delete m_pCoreSkeleton;
    m_pCoreSkeleton = 0;
  }

  m_strName.erase();
}

 /*****************************************************************************/
/** Provides access to a core animation.
  *
  * This function returns the core animation with the given ID.
  *
  * @param coreAnimationId The ID of the core animation that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core animation
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreAnimation *CalCoreModel::getCoreAnimation(int coreAnimationId)
{
  if((coreAnimationId < 0) 

    || (coreAnimationId >= (int)m_vectorCoreAnimation.size())

    || !m_vectorCoreAnimation[ coreAnimationId ] )
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  return m_vectorCoreAnimation[coreAnimationId];
}

 /*****************************************************************************/
/** Provides access to a core morph animation.
  *
  * This function returns the core morph animation with the given ID.
  *
  * @param coreMorphAnimationId The ID of the core morph animation that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core morph animation
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreMorphAnimation *CalCoreModel::getCoreMorphAnimation(int coreMorphAnimationId)
{
  if((coreMorphAnimationId < 0) || (coreMorphAnimationId >= (int)m_vectorCoreMorphAnimation.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  return m_vectorCoreMorphAnimation[coreMorphAnimationId];
}

 /*****************************************************************************/
/** Provides access to a core morph animation.
  *
  * This function returns the core morph animation with the given ID.
  *
  * @param coreAnimatedMorphId The ID of the core morph animation that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core morph animation
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreAnimatedMorph *CalCoreModel::getCoreAnimatedMorph(int coreAnimatedMorphId)
{
  if((coreAnimatedMorphId < 0) 

    || (coreAnimatedMorphId >= (int)m_vectorCoreAnimatedMorph.size())

    || !m_vectorCoreAnimatedMorph[ coreAnimatedMorphId ] )

  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  return m_vectorCoreAnimatedMorph[coreAnimatedMorphId];
}


 /*****************************************************************************/
/** Returns the number of core animations.
  *
  * This function returns the number of core animations in the core model
  * instance.
  *
  * @return The number of core animations.
  *****************************************************************************/

int CalCoreModel::getCoreAnimationMaxId()
{
  return m_vectorCoreAnimation.size();
}



 /*****************************************************************************/
/** Returns the number of CoreAnimatedMorphs.
  *
  * This function returns the number of CoreAnimatedMorphs in the core model
  * instance.
  *
  * @return The number of CoreAnimatedMorphs.
  *****************************************************************************/

/*

int CalCoreModel::getCoreAnimatedMorphCount()
{
  return m_vectorCoreAnimatedMorph.size();
}
*/



 /*****************************************************************************/
/** Returns the number of core morph animations.
  *
  * This function returns the number of core morph animations in the core model
  * instance.
  *
  * @return The number of core morph animations.
  *****************************************************************************/

int CalCoreModel::getCoreMorphAnimationCount()
{
  return m_vectorCoreMorphAnimation.size();
}


 /*****************************************************************************/
/** Provides access to a core material.
  *
  * This function returns the core material with the given ID.
  *
  * @param coreMaterialId The ID of the core material that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core material
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreMaterial *CalCoreModel::getCoreMaterial(int coreMaterialId)
{
  if((coreMaterialId < 0) || (coreMaterialId >= (int)m_vectorCoreMaterial.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  return m_vectorCoreMaterial[coreMaterialId];
}

 /*****************************************************************************/
/** Returns the number of core materials.
  *
  * This function returns the number of core materials in the core model
  * instance.
  *
  * @return The number of core materials.
  *****************************************************************************/

int CalCoreModel::getCoreMaterialCount()
{
  return m_vectorCoreMaterial.size();
}

 /*****************************************************************************/
/** Returns a specified core material ID.
  *
  * This function returns the core material ID for a specified core material
  * thread / core material set pair.
  *
  * @param coreMaterialThreadId The ID of the core material thread.
  * @param coreMaterialSetId The ID of the core material set.
  *
  * @return One of the following values:
  *         \li the \b ID of the core material
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreModel::getCoreMaterialId(int coreMaterialThreadId, int coreMaterialSetId)
{
  // find the core material thread
  std::map<int, std::map<int, int> >::iterator iteratorCoreMaterialThread;
  iteratorCoreMaterialThread = m_mapmapCoreMaterialThread.find(coreMaterialThreadId);
  if(iteratorCoreMaterialThread == m_mapmapCoreMaterialThread.end())
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  // get the core material thread
  std::map<int, int>& coreMaterialThread = (*iteratorCoreMaterialThread).second;

  // find the material id for the given set
  std::map<int, int>::iterator iteratorSet;
  iteratorSet = coreMaterialThread.find(coreMaterialSetId);
  if(iteratorSet == coreMaterialThread.end())
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  return (*iteratorSet).second;
}

 /*****************************************************************************/
/** Provides access to a core mesh.
  *
  * This function returns the core mesh with the given ID.
  *
  * @param coreMeshId The ID of the core mesh that should be returned.
  *
  * @return One of the following values:
  *         \li a pointer to the core mesh
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreMesh *CalCoreModel::getCoreMesh(int coreMeshId)
{
  if((coreMeshId < 0) || (coreMeshId >= (int)m_vectorCoreMesh.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return 0;
  }

  return m_vectorCoreMesh[coreMeshId];
}

 /*****************************************************************************/
/** Returns the number of core meshes.
  *
  * This function returns the number of core meshes in the core model instance.
  *
  * @return The number of core meshes.
  *****************************************************************************/

int CalCoreModel::getCoreMeshCount()
{
  return m_vectorCoreMesh.size();
}

 /*****************************************************************************/
/** Provides access to the core skeleton.
  *
  * This function returns the core skeleton.
  *
  * @return One of the following values:
  *         \li a pointer to the core skeleton
  *         \li \b 0 if an error happend
  *****************************************************************************/

CalCoreSkeleton *CalCoreModel::getCoreSkeleton()
{
  return m_pCoreSkeleton;
}

 /*****************************************************************************/
/** Provides access to the user data.
  *
  * This function returns the user data stored in the core model instance.
  *
  * @return The user data stored in the core model instance.
  *****************************************************************************/

Cal::UserData CalCoreModel::getUserData()
{
  return m_userData;
}

 /*****************************************************************************/
/** Loads a core animation.
  *
  * This function loads a core animation from a file.
  *
  * @param strFilename The file from which the core animation should be loaded
  *                    from.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core animation
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreModel::loadCoreAnimation(const std::string& strFilename)
{
  // the core skeleton has to be loaded already
  if(m_pCoreSkeleton == 0)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  // load a new core animation
  CalCoreAnimation *pCoreAnimation = CalLoader::loadCoreAnimation(strFilename, m_pCoreSkeleton);
  if(pCoreAnimation == 0) return -1;

  // add core animation to this core model
  int animationId = addCoreAnimation(pCoreAnimation);
  if(animationId == -1)
  {
    delete pCoreAnimation;
    return -1;
  }

  return animationId;
}

 /*****************************************************************************/
/** Loads a core animatedMorph.
  *
  * This function loads a core animatedMorph from a file.
  *
  * @param strFilename The file from which the core animatedMorph should be loaded
  *                    from.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core animation
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreModel::loadCoreAnimatedMorph(const std::string& strFilename)
{

  // load a new core AnimatedMorph
  CalCoreAnimatedMorph *pCoreAnimatedMorph = CalLoader::loadCoreAnimatedMorph(strFilename);
  if(pCoreAnimatedMorph == 0) return -1;

  // add core AnimatedMorph to this core model
  int animatedMorphId = addCoreAnimatedMorph(pCoreAnimatedMorph);
  if(animatedMorphId == -1)
  {
    delete pCoreAnimatedMorph;
    return -1;
  }

  return animatedMorphId;
}


 /*****************************************************************************/
/** Loads a core material.
  *
  * This function loads a core material from a file.
  *
  * @param strFilename The file from which the core material should be loaded
  *                    from.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core material
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreModel::loadCoreMaterial(const std::string& strFilename)
{
  // the core skeleton has to be loaded already
  if(m_pCoreSkeleton == 0)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }

  // load a new core material
  CalCoreMaterial *pCoreMaterial = CalLoader::loadCoreMaterial(strFilename);
  if(pCoreMaterial == 0) return -1;

  // add core material to this core model
  int materialId = addCoreMaterial(pCoreMaterial);
  if(materialId == -1)
  {
    delete pCoreMaterial;
    return -1;
  }

  return materialId;
}

 /*****************************************************************************/
/** Loads a core mesh.
  *
  * This function loads a core mesh from a file.
  *
  * @param strFilename The file from which the core mesh should be loaded from.
  *
  * @return One of the following values:
  *         \li the assigned \b ID of the loaded core mesh
  *         \li \b -1 if an error happend
  *****************************************************************************/

int CalCoreModel::loadCoreMesh(const std::string& strFilename)
{


  /*
  // the core skeleton has to be loaded already
  if(m_pCoreSkeleton == 0)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return -1;
  }
*/

  // load a new core mesh
  CalCoreMesh *pCoreMesh = CalLoader::loadCoreMesh(strFilename);
  if(pCoreMesh == 0) return -1;

  // add core mesh to this core model
  int meshId;
  meshId = addCoreMesh(pCoreMesh);
  if(meshId == -1)
  {
    delete pCoreMesh;
    return -1;
  }

  return meshId;
}

 /*****************************************************************************/
/** Loads the core skeleton.
  *
  * This function loads the core skeleton from a file.
  *
  * @param strFilename The file from which the core skeleton should be loaded
  *                    from.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool CalCoreModel::loadCoreSkeleton(const std::string& strFilename)
{
  // destroy the current core skeleton
  if(m_pCoreSkeleton != 0)
  {
    m_pCoreSkeleton->destroy();
    delete m_pCoreSkeleton;
  }

  // load a new core skeleton
  m_pCoreSkeleton = CalLoader::loadCoreSkeleton(strFilename);
  if(m_pCoreSkeleton == 0) return false;

  return true;
}

 /*****************************************************************************/
/** Saves a core animation.
  *
  * This function saves a core animation to a file.
  *
  * @param strFilename The file to which the core animation should be saved to.
  * @param coreAnimationId The ID of the core animation that should be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool CalCoreModel::saveCoreAnimation(const std::string& strFilename, int coreAnimationId)
{
  // check if the core animation id is valid
  if((coreAnimationId < 0) 

    || (coreAnimationId >= (int)m_vectorCoreAnimation.size())

    || !m_vectorCoreAnimation[ coreAnimationId ] )
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // save the core animation
  if(!CalSaver::saveCoreAnimation(strFilename, m_vectorCoreAnimation[coreAnimationId]))
  {
    return false;
  }

  return true;
}



 /*****************************************************************************/
/** Saves a core material.
  *
  * This function saves a core material to a file.
  *
  * @param strFilename The file to which the core material should be saved to.
  * @param coreMaterialId The ID of the core material that should be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool CalCoreModel::saveCoreMaterial(const std::string& strFilename, int coreMaterialId)
{
  // check if the core material id is valid
  if((coreMaterialId < 0) || (coreMaterialId >= (int)m_vectorCoreMaterial.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // save the core animation
  if(!CalSaver::saveCoreMaterial(strFilename, m_vectorCoreMaterial[coreMaterialId]))
  {
    return false;
  }

  return true;
}

 /*****************************************************************************/
/** Saves a core mesh.
  *
  * This function saves a core mesh to a file.
  *
  * @param strFilename The file to which the core mesh should be saved to.
  * @param coreMeshId The ID of the core mesh that should be saved.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool CalCoreModel::saveCoreMesh(const std::string& strFilename, int coreMeshId)
{
  // check if the core mesh id is valid
  if((coreMeshId < 0) || (coreMeshId >= (int)m_vectorCoreMesh.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // save the core animation
  if(!CalSaver::saveCoreMesh(strFilename, m_vectorCoreMesh[coreMeshId]))
  {
    return false;
  }

  return true;
}

 /*****************************************************************************/
/** Saves the core skeleton.
  *
  * This function saves the core skeleton to a file.
  *
  * @param strFilename The file to which the core skeleton should be saved to.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool CalCoreModel::saveCoreSkeleton(const std::string& strFilename)
{
  // check if we have a core skeleton in this code model
  if(m_pCoreSkeleton == 0)
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // save the core skeleton
  if(!CalSaver::saveCoreSkeleton(strFilename, m_pCoreSkeleton))
  {
    return false;
  }

  return true;
}

 /*****************************************************************************/
/** Sets a core material ID.
  *
  * This function sets a core material ID for a core material thread / core
  * material set pair.
  *
  * @param coreMaterialThreadId The ID of the core material thread.
  * @param coreMaterialSetId The ID of the core maetrial set.
  * @param coreMaterialId The ID of the core maetrial.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool CalCoreModel::setCoreMaterialId(int coreMaterialThreadId, int coreMaterialSetId, int coreMaterialId)
{
  // find the core material thread
  std::map<int, std::map<int, int> >::iterator iteratorCoreMaterialThread;
  iteratorCoreMaterialThread = m_mapmapCoreMaterialThread.find(coreMaterialThreadId);
  if(iteratorCoreMaterialThread == m_mapmapCoreMaterialThread.end())
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // get the core material thread
  std::map<int, int>& coreMaterialThread = (*iteratorCoreMaterialThread).second;

  // remove a possible entry in the core material thread
  coreMaterialThread.erase(coreMaterialSetId);

  // set the given set id in the core material thread to the given core material id
  coreMaterialThread.insert(std::make_pair(coreMaterialSetId, coreMaterialId));

  return true;
}

 /*****************************************************************************/
/** Sets the core skeleton.
  *
  * This function sets the core skeleton of the core model instance..
  *
  * @param pCoreSkeleton The core skeleton that should be set.
  *****************************************************************************/

void CalCoreModel::setCoreSkeleton(CalCoreSkeleton *pCoreSkeleton)
{
  // destroy a possible existing core skeleton
  if(m_pCoreSkeleton != 0)
  {
    m_pCoreSkeleton->destroy();
    delete m_pCoreSkeleton;
  }

  m_pCoreSkeleton = pCoreSkeleton;
}

 /*****************************************************************************/
/** Stores user data.
  *
  * This function stores user data in the core model instance.
  *
  * @param userData The user data that should be stored.
  *****************************************************************************/

void CalCoreModel::setUserData(Cal::UserData userData)
{
  m_userData = userData;
}

 /*****************************************************************************/
/** Creates or overwrites a string-to-boneId mapping
  *
  * This function makes a bone ID reference-able by a string name.
  *
  * @param strBoneName The string that will be associated with the ID.
  * @param boneId The ID number of the bone that will be referenced by the string.
  *****************************************************************************/

void CalCoreModel::addBoneHelper(const std::string& strBoneName, int boneId)
{
  //Make sure the skeleton has been loaded first
  if (m_pCoreSkeleton != NULL)
  {
    //Map the bone ID to the name
    m_pCoreSkeleton->mapCoreBoneName(boneId, strBoneName);
  }
}
 /*****************************************************************************/
/** Creates or overwrites a string-to-animation ID mapping
  *
  * This function makes an animation ID reference-able by a string name.
  * Note that we don't verify that the ID is valid because the animation
  * may be added later.
  * Also, if there is already a helper with this name, it will be overwritten
  * without warning.
  *
  * @param strAnimName The string that will be associated with the ID.
  * @param animId The ID number of the animation to be referenced by the string.
  *****************************************************************************/

void CalCoreModel::addAnimHelper(const std::string& strAnimName, int animId)
{
  m_animationHelper[ strAnimName ] = animId;
}

 /*****************************************************************************/
/** Retrieves the ID of the bone referenced by a string
  *
  * This function returns a bone ID
  *
  * @param strBoneName A string that is associated with a bone ID number.
  * @return Returns:
  *         \li \b -1 if there is no bone ID associated with the input string
  *         \li \b the ID number of the bone asssociated with the input string
  *****************************************************************************/

int CalCoreModel::getBoneId(const std::string& strBoneName)
{
  if (m_pCoreSkeleton != NULL)
  {
    return m_pCoreSkeleton->getCoreBoneId(strBoneName);
  }
  return -1;
}

 /*****************************************************************************/
/** Retrieves the ID of the animation referenced by a string
  *
  * This function returns an animation ID
  *
  * @param strAnimName A string that is associated with an anim ID number.
  * @return Returns:
  *         \li \b -1 if there is no anim ID associated with the input string
  *         \li \b the ID number of the anim asssociated with the input string
  *****************************************************************************/

int CalCoreModel::getAnimId(const std::string& strAnimName)
{
  if (m_animationHelper.count( strAnimName ) < 1)
  {
    return -1;
  }
   
  return m_animationHelper[strAnimName];
}

 /*****************************************************************************/
/** Scale the core model.
  *
  * This function rescale all data that are in the core model instance
  *
  * @param factor A float with the scale factor
  *
  *****************************************************************************/


void CalCoreModel::scale(float factor)
{
	m_pCoreSkeleton->scale(factor);

	int animationId;
	for(animationId = 0; animationId < m_vectorCoreAnimation.size(); animationId++)
	{

    if( m_vectorCoreAnimation[animationId] ) {
  		m_vectorCoreAnimation[animationId]->scale(factor);

    }
	}

	int meshId;
	for(meshId = 0; meshId < m_vectorCoreMesh.size(); meshId++)
	{
		m_vectorCoreMesh[meshId]->scale(factor);
	}

}

//****************************************************************************//
