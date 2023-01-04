//================================================================================
// Copyright Dassault Systemes Provence 2005, All Rights Reserved 
//================================================================================
//
// CATSobFaceCutInfo.h
//
//================================================================================
//
// Usage notes: Petite classe permettant de décrire les découpes
//              d'une face, elle est utilisée par CATSobCheckVertexMoveOperator.
//
//================================================================================
// March,     2005 : RAQ : Creation
//================================================================================
#ifndef CATSobFaceCutInfo_H
#define CATSobFaceCutInfo_H

#include "CATSobObjects.h"

#include "CATListOfDouble.h"
#include "CATBoolean.h"

class CATSobFace;


class ExportedByCATSobObjects CATSobFaceCutInfo
{
public:

  CATSobFaceCutInfo(CATSobFace* iFace);

  ~CATSobFaceCutInfo();

  CATSobFace* GetFace();

  void GetNbCuts(CATListOfDouble*& iCutsOnU, CATListOfDouble*& iCutsOnV, const CATBoolean iRemoveDuplicates=TRUE);

private:

  // Copy constructor and equal operator
  CATSobFaceCutInfo (CATSobFaceCutInfo &);
  CATSobFaceCutInfo& operator=(CATSobFaceCutInfo&);

  void RemoveDuplicateCuts();

  //Data:
  CATSobFace* _Face;
  CATListOfDouble _RatioOnU, _RatioOnV;
};


inline CATSobFace* CATSobFaceCutInfo::GetFace()
{
  return _Face;
}


inline void CATSobFaceCutInfo::GetNbCuts(CATListOfDouble*& iCutsOnU, CATListOfDouble*& iCutsOnV, const CATBoolean iRemoveDuplicates)
{
  if(iRemoveDuplicates) RemoveDuplicateCuts();

  iCutsOnU=&_RatioOnU;
  iCutsOnV=&_RatioOnV;
}


inline void CATSobFaceCutInfo::RemoveDuplicateCuts()
{
  _RatioOnU.RemoveDuplicates();
  _RatioOnV.RemoveDuplicates();
}



#endif



