//****************************************************************************//
// animation_pose.cpp                                                        //
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

#include "cal3d/animation_pose.h"
#include "cal3d/error.h"
#include "cal3d/coreanimation.h"

 /*****************************************************************************/
/** Constructs the animation pose instance.
  *
  * This function is the default constructor of the animation pose instance.
  *****************************************************************************/

CalAnimationPose::CalAnimationPose(CalCoreAnimation *pCoreAnimation)
  : CalAnimation(pCoreAnimation)
{
  setType(TYPE_POSE);
  setState(STATE_SYNC);

  // set default weights and delay
  setWeight(1.0f);
  m_targetDelay = 0.0f;
  m_targetWeight = 1.0f;

  // the pose should be the end of the animation and such
  // an animation should really have only one frame.
  setTime(getCoreAnimation()->getDuration());
  setTimeFactor(1.0f);
}

 /*****************************************************************************/
/** Interpolates the weight of the animation pose instance.
  *
  * This function interpolates the weight of the animation pose instance to a
  * new value in a given amount of time.
  *
  * @param weight The weight to interpolate the animation pose instance to.
  * @param delay The time in seconds until the new weight should be reached.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happened
  *****************************************************************************/

bool CalAnimationPose::blend(float weight, float delay)
{
  m_targetWeight = weight;
  m_targetDelay = delay;

  return true;
}

 /*****************************************************************************/
/** Puts the animation pose instance into async state.
  *
  * This function puts the animation pose instance into async state, which
  * means that it will end after the current running pose.
  *
  * @param time The time in seconds at which the animation pose instance was
  *             unlinked from the global mixer animation pose.
  * @param duration The current duration of the global mixer animation pose in
  *                 seconds at the time of the unlinking.
  *****************************************************************************/

void CalAnimationPose::setAsync(float time, float duration)
{
  // check if thie animation pose is already async
  if(getState() != STATE_ASYNC)
  {
    setTimeFactor(1.0f);

    setState(STATE_ASYNC);
  }
}

 /*****************************************************************************/
/** Updates the animation pose instance.
  *
  * This function updates the animation pose instance for a given amount of
  * time.
  *
  * @param deltaTime The elapsed time in seconds since the last update.
  *
  * @return One of the following values:
  *         \li \b true if the animation pose instance is still active
  *         \li \b false if the execution of the animation pose instance has
  *             ended
  *****************************************************************************/

bool CalAnimationPose::update(float deltaTime)
{
  setTime(getCoreAnimation()->getDuration());

  if(m_targetDelay <= fabs(deltaTime))
  {
    // we reached target delay, set to full weight
    setWeight(m_targetWeight);
    m_targetDelay = 0.0f;

    // check if we reached the poses end
    if(getWeight() == 0.0f)
    {
      return false;
    }
  }
  else
  {
    // not reached target delay yet, interpolate between current and target weight
     float factor = m_targetDelay <= 0.0f ? 1.0f : deltaTime / m_targetDelay;
    if (factor > 1.0f)
    {
       factor = 1.0f;
    }
    if (factor < 0.0f)
    {
       factor = 0.0f;
    }
    setWeight((1.0f - factor) * getWeight() + factor * m_targetWeight);
    m_targetDelay -= deltaTime;
  }

  return true;
}

//****************************************************************************//
