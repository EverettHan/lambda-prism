// COPYRIGHT DASSAULT SYSTEMES 2018
//=============================================================================
//
// CATOLKCollector: 
//  
//
//=============================================================================
//
//  !!!!!!!!!!!!!!!!!!!!!!!!!  WARNING  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  !PLEASE DO NOT USE FOR THE MOMENT UNDER DEVELOPPEMENT !!!!!!!!!!!!
//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//
//=============================================================================
//  Dec 2018  Creation                                                 U29
//=============================================================================

#ifndef CATOLKCollector_H
#define CATOLKCollector_H

#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATFace;
class CATBody;

class ExportedByCATTopologicalObjects CATOLKCollector
{
public: 

  CATOLKCollector(CATGeoFactory * ipFactory);
  ~CATOLKCollector();

  void Add(CATFace * ipFace);

private:
  CATBody * _pWorker;
  CATGeoFactory * _pFactory;

};

#endif //CATOLKCollector_H
