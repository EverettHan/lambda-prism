//=================================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved 
//=================================================================================
//
// Data of CGM to 
//
//=============================================================================
// Usage notes:
//
// Strictement réservé aux implémentations CGM.
//=============================================================================
//=============================================================================
// HISTORIQUE :
//
// 22/04/2010 : RNO : Creation !! 
//============================================================================= 
#ifndef CATSapExtrapolData_H
#define CATSapExtrapolData_H

#include "CATSapApprox.h"
class CATMathGridOfPoints;
class CATSapKnotVector;

class ExportedByCATSapApprox CATSapExtrapolData
{
public:
  CATSapExtrapolData();
  CATSapExtrapolData(CATMathGridOfPoints * CP,CATSapKnotVector ** KVU, CATSapKnotVector ** KVV);
  virtual ~CATSapExtrapolData();
  void SetSize(short NbPatchU,short NbPatchV);
  int AllocateArrayofSapKVs();
  void KillSapVectors();
  short _ZoneNU,_ZoneNV;
  CATMathGridOfPoints * _CPs;
  CATSapKnotVector **   _KVU;
  CATSapKnotVector ** _KVV;
};


#endif
