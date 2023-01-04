/**
 * @COPYRIGHT DASSAULT SYSTEMES 2011
 */
/* -*-c++-*- */
//===========================================================================
//
// Hash table qui associe une liste d'int a une clef.
//
// Nov. 2011   Creation                            JJ3
//
//===========================================================================


#ifndef  CATHashTableWithIntListAssoc_h
#define  CATHashTableWithIntListAssoc_h

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMHashTable.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATMathematics.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATListOfShort.h"

class ExportedByCATTopologicalObjects CATHashTableWithIntListAssoc
{
public:

  CATHashTableWithIntListAssoc(int iEstimatedSize = 0);

  virtual ~CATHashTableWithIntListAssoc();

  int          Insert(void* ipElem, CATListOfShort & iAssoc);
  int          Insert(void* ipElem, short iAssoc);
  int          LocateItem(void* ipElem) const;
  int          LocateItem(void* ipElem, CATListOfShort * ipAssoc) const;
  void *       GetItem(int iPos) const;
  CATListOfShort  GetAssoc(int iPos) const;
  CATListOfShort  GetAssoc(void* ipElem);

  int          Size() const;

protected:

  int Reallocate();
  int Hash(void * ipElem) const;
  int UpToNiceModulo(int iN);

  int   * _Buckets;
  void ** _Elements;
  CATListOfShort   * _AssocElements;
  int     _MaxSize;
  int     _Size;
  int     _DefaultSize;
  int     _NbBuckets;
  int     _NbMaxOfCollisionForLastBucket;
  PFHASHKEYFUNCTION	_pHashKeyFunction;

  
};

#endif

