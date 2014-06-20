//****************************************************************************//
// error.cpp                                                                  //
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

#include "cal3d/error.h"

//****************************************************************************//
// Static member variables initialization                                     //
//****************************************************************************//

CalError::Code CalError::m_lastErrorCode = CalError::OK;
std::string CalError::m_strLastErrorFile;
int CalError::m_lastErrorLine = -1;
std::string CalError::m_strLastErrorText;

 /*****************************************************************************/
/** Returns the code of the last error.
  *
  * This function returns the code of the last error that occured inside the
  * library.
  *
  * @return The code of the last error.
  *****************************************************************************/

CalError::Code CalError::getLastErrorCode()
{
  return m_lastErrorCode;
}

 /*****************************************************************************/
/** Returns a description of the last error.
  *
  * This function returns a short description of the last error that occured
  * inside the library.
  *
  * @return The description of the last error.
  *****************************************************************************/

const char* CalError::getLastErrorDescriptionInternal()
{
  switch(m_lastErrorCode)
  {
    case OK:
      return "No error found";
      break;
    case INTERNAL:
      return "Internal error";
      break;
    case INVALID_HANDLE:
      return "Invalid handle as argument";
      break;
    case MEMORY_ALLOCATION_FAILED:
      return "Memory allocation failed";
      break;
    case FILE_NOT_FOUND:
      return "File not found";
      break;
    case INVALID_FILE_FORMAT:
      return "Invalid file format";
      break;
    case FILE_PARSER_FAILED:
      return "Parser failed to process file";
      break;
    case INDEX_BUILD_FAILED:
      return "Building of the index failed";
      break;
    case NO_PARSER_DOCUMENT:
      return "There is no document to parse";
      break;
    case INVALID_ANIMATION_DURATION:
      return "The duration of the animation is invalid";
      break;
    case BONE_NOT_FOUND:
      return "Bone not found";
      break;
    case INVALID_ATTRIBUTE_VALUE:
      return "Invalid attribute value";
      break;
    case INVALID_KEYFRAME_COUNT:
      return "Invalid number of keyframes";
      break;
    case INVALID_ANIMATION_TYPE:
      return "Invalid animation type";
      break;
    case FILE_CREATION_FAILED:
      return "Failed to create file";
      break;
    case FILE_WRITING_FAILED:
      return "Failed to write to file";
      break;
    case INCOMPATIBLE_FILE_VERSION:
      return "Incompatible file version";
      break;
    case NO_MESH_IN_MODEL:
      return "No mesh attached to the model";
      break;
    case BAD_DATA_SOURCE:
      return "Cannot read from data source";
      break;
    case NULL_BUFFER:
      return "Memory buffer is null";
      break;
    case INVALID_MIXER_TYPE:
      return "The CalModel mixer is not a CalMixer instance";
      break;
    default:
      break;
  }

  return "Unknown error";
}

 /*****************************************************************************/
/** Returns the name of the file where the last error occured.
  *
  * This function returns the name of the file where the last error occured.
  *
  * @return The name of the file where the last error occured.
  *****************************************************************************/

const std::string& CalError::getLastErrorFileInternal()
{
  return m_strLastErrorFile;
}

 /*****************************************************************************/
/** Returns the line number where the last error occured.
  *
  * This function returns the line number where the last error occured.
  *
  * @return The line number where the last error occured.
  *****************************************************************************/

int CalError::getLastErrorLine()
{
  return m_lastErrorLine;
}

 /*****************************************************************************/
/** Returns the supplementary text of the last error.
  *
  * This function returns the suppementary text of the last error occured
  * inside the library.
  *
  * @return The supplementary text of the last error.
  *****************************************************************************/

const std::string& CalError::getLastErrorTextInternal()
{
  return m_strLastErrorText;
}

char const * CalError::getLastErrorDescription()
{
  return getLastErrorDescriptionInternal();
}

char const * CalError::getLastErrorFile()
{
  return getLastErrorFileInternal().c_str();
}

char const * CalError::getLastErrorText()
{
  return getLastErrorTextInternal().c_str();
}


 /*****************************************************************************/
/** Dumps all information about the last error to the standard output.
  *
  * This function dumps all the information about the last error that occured
  * inside the library to the standard output.
  *****************************************************************************/

void CalError::printLastError()
{
  std::cout << "cal3d : " << getLastErrorDescription();

  // only print supplementary information if there is some
  if(m_strLastErrorText.size() > 0)
  {
    std::cout << " '" << m_strLastErrorText << "'";
  }

  std::cout << " in " << m_strLastErrorFile << "(" << m_lastErrorLine << ")" << std::endl;
}

 /*****************************************************************************/
/** Sets all the information about the last error.
  *
  * This function sets all the information about the last error that occured
  * inside the library.
  *
  * @param code The code of the last error.
  * @param strFile The file where the last error occured.
  * @param line The line number where the last error occured.
  * @param strText The supplementary text of the last error.
  *****************************************************************************/

void CalError::setLastError(Code code, const std::string& strFile, int line, const std::string& strText)
{
  if(code >= MAX_ERROR_CODE) code = INTERNAL;

  m_lastErrorCode = code;
  m_strLastErrorFile = strFile.c_str();
  m_lastErrorLine = line;
  m_strLastErrorText = strText.c_str();
}

//****************************************************************************//
