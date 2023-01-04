/* -*-c++-*- */
#ifndef CATCGMDynEdgeCurve_H
#define CATCGMDynEdgeCurve_H
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// CATCGMDynEdgeCurve : Gestion des attributs 
//=============================================================================
#include "ExportedByCATGeometricObjectsCGM.h"
#include "CATListOfCATCGMAttribute.h"
#include "CATCGMDynObject.h"
#include "CATParamData.h"

class CATSharpnessCGMData;


class ExportedByCATGeometricObjectsCGM CATCGMDynEdgeCurve : public CATCGMDynObject
{
public :
  
  //--------------------------------------------------------------------
  // Les premiers 8 octets (en adressage 32 bits) sont occupes par 
  //    pointeur fonction virtuel + pointeur liste attribut
  //-------------------------------------------------------------------- 
  CATCGMDynEdgeCurve(CATCGMFusion *iHolder);
  virtual ~CATCGMDynEdgeCurve();

  virtual void Clear();

  CATCGMNewClassArrayDeclare;
  
  void                 * _V2R0Data;
  CATSharpnessCGMData  * _Sharpness;
  
};

#endif

