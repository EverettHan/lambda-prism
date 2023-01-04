//====================================================================
// Copyright Dassault Systemes Provence 2016, All Rights Reserved
//====================================================================
//
// CATSobDebugUtilities.h
//
//====================================================================
//
// Usage notes: Debug utilities
//
//====================================================================
// 20.10.2016 : RAQ : Creation
//====================================================================
#ifndef CATSobDebugUtilities_H
#define CATSobDebugUtilities_H

//Pour l'export
#include "ExportedByCATSobUtilities.h"

//Mononcodage OS
#include "CATLib.h"

//STL
#ifndef _AIX_SOURCE
  #include <string>
#endif  //!_AIX_SOURCE



namespace CATSobDebugUtilities
{
  //Returns a string build from the current time : yyyymmdd_hhmmss.mmm
#ifndef _AIX_SOURCE
  ExportedByCATSobUtilities
    std::string GetTimeStampString();
#endif  //!_AIX_SOURCE
}

#endif  //CATSobDebugUtilities_H

