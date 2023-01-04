// COPYRIGHT DASSAULT SYSTEMES 2003
/* -*-c++-*- */
//=============================================================================
// HashTable de CATCGMGeometryOfAnyone base sur _Obj et _OriginalContainer
//=============================================================================
// Nov. 03 Creation                                                       HCN
//=============================================================================
#ifndef CATCGMGeometryOfAnyoneHashTable_H
#define CATCGMGeometryOfAnyoneHashTable_H

#include "ExportedByGeometricObjects.h"
#include "CATCGMHashTable.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"

class CATGeometry;
class CATCGMGeometryOfAnyone;


class ExportedByGeometricObjects CATCGMGeometryOfAnyoneHashTable : public CATCGMHashTable
{
public:
  CATCGMGeometryOfAnyoneHashTable(int iEstimatedSize = 0);
  ~CATCGMGeometryOfAnyoneHashTable();
  CATCGMNewClassArrayDeclare;
  

  int                             Insert(CATCGMGeometryOfAnyone* iAnyOne);
  int                             Remove(CATCGMGeometryOfAnyone* iAnyOne);
  INLINE CATCGMGeometryOfAnyone*  Locate(CATCGMGeometryOfAnyone* iAnyOne) const;

    // perfo warning : 
  CATCGMGeometryOfAnyone * const _FirstAnyone;
  int                            _NumberOfAnyone;
 

  void InsertAnyone(CATCGMGeometryOfAnyone * iAnyOne);
  void RemoveAnyone(CATCGMGeometryOfAnyone * iAnyOne);


private:

  // Override de CATCGMHashTable
  static unsigned int HashKeyFunction(void* ipElem);
  static int CompareFunction(void* ipElem1, void* ipElem2);
};


//-----------------------------------------------------------------------------
// Locate
//-----------------------------------------------------------------------------
INLINE CATCGMGeometryOfAnyone* CATCGMGeometryOfAnyoneHashTable::Locate(CATCGMGeometryOfAnyone* ipFatAble) const
{
  // ATTENTION : CATCGMHashTableBase::Locate(void* ipElem) renvoie
  // le pointeur sur le bucket du tableau pointant sur l'element
  void* pBucket = this->CATCGMHashTable::Locate((void*)ipFatAble);

  return (pBucket ? *((CATCGMGeometryOfAnyone**)pBucket) : NULL);
}

#endif 
