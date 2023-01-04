// COPYRIGHT DASSAULT SYSTEMES 2003
/* -*-c++-*- */
//=============================================================================
// HashTable de CATCGMGeometryOfFatAble base sur _Obj et _OriginalContainer
//=============================================================================
// Nov. 03 Creation                                                       HCN
//=============================================================================

#ifndef CATCGMGeometryOfFatAbleHashTable_H
#define CATCGMGeometryOfFatAbleHashTable_H

#include "ExportedByGeometricObjects.h"
#include "CATCGMHashTable.h"
#include "CATCGMNewArray.h"

#include "CATListOfCATCGMGeometryOfFatAble.h"
#include "CATMathInline.h"

class CATGeometry;

class ExportedByGeometricObjects CATCGMGeometryOfFatAbleHashTable : public CATCGMHashTable
{
public:
  CATCGMGeometryOfFatAbleHashTable(int iEstimatedSize = 0);
  ~CATCGMGeometryOfFatAbleHashTable();
  CATCGMNewClassArrayDeclare;
  
  int                             Insert(CATCGMGeometryOfFatAble* ipFatAble);
  int                             Remove(CATCGMGeometryOfFatAble* ipFatAble);
  INLINE CATCGMGeometryOfFatAble* Locate(CATCGMGeometryOfFatAble* ipFatAble) const;

  // * * * NOT MULTITHREAD SAFE * * *
  int             LocateAllFatAbleWithContainer(CATGeometry*                       ipContainer,
                                                CATLISTP(CATCGMGeometryOfFatAble)& ioFatAbles) const;

private:

  // Override de CATCGMHashTable
  static unsigned int HashKeyFunction(void* ipElem);
  static int CompareFunction(void* ipElem1, void* ipElem2);
};


//-----------------------------------------------------------------------------
// Locate
//-----------------------------------------------------------------------------
INLINE CATCGMGeometryOfFatAble* CATCGMGeometryOfFatAbleHashTable::Locate(CATCGMGeometryOfFatAble* ipFatAble) const
{
  // ATTENTION : CATCGMHashTableBase::Locate(void* ipElem) renvoie
  // le pointeur sur le bucket du tableau pointant sur l'element
  void* pBucket = this->CATCGMHashTable::Locate((void*)ipFatAble);

  return (pBucket ? *((CATCGMGeometryOfFatAble**)pBucket) : NULL);
}

#endif 
