/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/* -*-c++-*- */
//===========================================================================
//
// Implementation generique d'une hash table avec stockage
// d'une donnee associee (avec gestion des adresses > 2 Go)
//  
//
// Avr. 2002   Creation                            HCN
//
//===========================================================================

#ifndef  CATCGMHashTableWithAssoc_h
#define  CATCGMHashTableWithAssoc_h

#include "CATCGMHashTable.h"
#include "CATMathematics.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"

class ExportedByCATMathematics CATCGMHashTableWithAssoc : public CATCGMVirtual
{
public:

  CATCGMHashTableWithAssoc(int iEstimatedSize = 0,
                           PFHASHKEYFUNCTION ipHashKeyFunction = NULL,
                           PFCOMPAREFUNCTION	ipCompareFunction = NULL);

  virtual ~CATCGMHashTableWithAssoc();

  int          Insert(void* ipElem, void* ipAssoc);
  int          InsertReturnPos(void* ipElem, void* ipAssoc);
  int          LocateItem(void* ipElem, void** oppAssoc) const;
  int          KeyLocateItem(unsigned int iKey, void** ippElem, void** oppAssoc) const;
  void*        LocateAssoc(void* ipElem) const;
  void         SetItem(int iPos, void* ipElem);
  INLINE void  SetAssoc(int iPos, void* ipAssoc);
  int          SetAssoc(void* ipElem, void* ipAssoc);
  INLINE void* GetItem(int iPos) const;
  INLINE void* GetItemAndAssoc(int iPos, void** oppAssoc) const;
  INLINE void* GetAssoc(int iPos) const;

  int          Size() const;
  void         RemoveAll();

  //VUC: 2010-03-04
  int Remove(void* ipElem);

  
protected:

  PFHASHKEYFUNCTION	_pHashKeyFunction;
  PFCOMPAREFUNCTION	_pCompareFunction;

  int          _NbAllocatedBuckets; // Dimension of the hashtab (maximum number of buckets to be stored in the Hashtable)
  CATULONGPTR* _pAllocatedBuckets;  // Address of the allocated memory  
  CATULONGPTR* _pFirstFreeBucket;   // Address of the first free bucket

  // Par defaut, un bucket est un CATULONGPTR
  // CATULONGPTR  _StaticBuckets[3 * CATCGM_DEFAULT_HASH_TABLE_DIMENSION];  // Static array (93 = 3 * _NbAllocatedBuckets with _NbAllocatedBuckets = 31) 
  CATULONGPTR  _StaticBuckets[4 * CATCGM_DEFAULT_HASH_TABLE_DIMENSION];  // Static array (124 = 4 * _NbAllocatedBuckets with _NbAllocatedBuckets = 31) 

  int          _NbFreeBuckets;      // Number of free buckets 
  int          _NbStoredElems;      // Number of stored elements in the hashtable

  // Pour debug
  unsigned int        _Tag;
  static unsigned int _Tag_Counter;

  void ReAllocate();
};

//-----------------------------------------------------------------------------
// GetItem
//-----------------------------------------------------------------------------
INLINE void* CATCGMHashTableWithAssoc::GetItem(int iPos) const
{
  if (iPos < 0 || iPos >= _NbStoredElems)
    return NULL;
  return (void *) *(_pAllocatedBuckets + _NbAllocatedBuckets + 3 * iPos);
};

//-----------------------------------------------------------------------------
// GetItem
//-----------------------------------------------------------------------------
INLINE void* CATCGMHashTableWithAssoc::GetItemAndAssoc(int iPos, void** oppAssoc) const
{
  if (iPos < 0 || iPos >= _NbStoredElems)
    return NULL;
  else
  {
    if (oppAssoc)
      *oppAssoc = (void*) *(_pAllocatedBuckets + _NbAllocatedBuckets + 3 * iPos + 1);
    return (void *) *(_pAllocatedBuckets + _NbAllocatedBuckets + 3 * iPos);
  }
}

//-----------------------------------------------------------------------------
// GetAssoc
//-----------------------------------------------------------------------------
INLINE void* CATCGMHashTableWithAssoc::GetAssoc(int iPos) const
{
  if (iPos < 0 || iPos >= _NbStoredElems)
    return NULL;
  return (void *) *(_pAllocatedBuckets + _NbAllocatedBuckets + 3 * iPos + 1);
};
//-----------------------------------------------------------------------------
// SetAssoc
//-----------------------------------------------------------------------------
INLINE void CATCGMHashTableWithAssoc::SetAssoc(int iPos, void* ipAssoc)
{
  if (iPos >= 0 && iPos < _NbStoredElems)
  {
    CATULONGPTR* pBucket = _pAllocatedBuckets + _NbAllocatedBuckets + 3 * iPos + 1;
    *(pBucket) = (CATULONGPTR)ipAssoc;
  }
}

#endif

