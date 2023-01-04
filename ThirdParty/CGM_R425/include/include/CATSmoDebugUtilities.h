//====================================================================
// Copyright Dassault Systemes Provence 2018, All Rights Reserved
//====================================================================
//
// CATSmoDebugUtilities.h
//
//====================================================================
//
// Usage notes: Debug utilities
//
//====================================================================
// 26.01.2018 : RAQ : Creation
//====================================================================
#ifndef CATSmoDebugUtilities_H
#define CATSmoDebugUtilities_H

//Pour l'export
#include "CATSmoOperators.h"

//Subdivision
#include "CATSobDiag.h"

//Divers
#include "CATBoolean.h"

class CATSobMesh;

namespace CATSmoDebugUtilities
{
  //Saves the subdivision points and optionnaly normals of a mesh
  ExportedByCATSmoOperators
  CATSobDiag SaveSubdividedMesh(const char* ipFileName, CATSobMesh* ipMesh, const int iLevel, const CATBoolean iSaveNormals);
}

#endif  //CATSmoDebugUtilities_H

