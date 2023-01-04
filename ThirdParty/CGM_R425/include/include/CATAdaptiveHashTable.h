#ifndef CATAdaptiveHashTable_h
#define CATAdaptiveHashTable_h

//**************************************************************************************************************
// CATAdaptiveHashTable
//
// Class representing a hash table having a pointer as entry.
// Main differences with CATCGMHashTableBase:
// - The number of buckets is equal to 1.5 * _MaxSize, reducing the probability of conflicts.
// - When _Size == _MaxSize, make reallocation multiplying _MaxSize by 10 instead of 2.
//**************************************************************************************************************
// 2011 WEEK 25 CREATION                                                                                    LD2
//**************************************************************************************************************

#include "YP0LOGRP.h"
#include "CATCGMHashTableBase.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATAssert.h"
#include "CATMath.h"
#include "KeyBucketMap.h"

#define LD2_AdaptiveHashTable_NoHashInternalElement

class ExportedByYP0LOGRP CATAdaptiveHashTable : public KeyBucketMap
{
public:

  /**
  * Constructor.
  *   Creates a table where elements can be inserted, located and removed.
  *
  * > iEstimatedSize (integer)
  *     The estimated number of elements that will be inserted in the table.
  *
  * > ipfHashKeyFunction (pointer to function of type: unsigned int(void*))
  *     ipfHashKeyFunction must guarantee that ipfHashKeyFunction(A) == ipfHashKeyFunction(B) if A and B are equivalent.
  *
  * > ipfCompareFunction (pointer to function of type: int(void*, void*))
  *     Two elements A and B are considered "equivalent" if ipfCompareFunction(A, B) == 0.
  */
  CATAdaptiveHashTable(int iEstimatedSize = 0,
                       PFHASHKEYFUNCTION ipfHashKeyFunction = CATCGMHashTableBase::HashKeyFunction,
                       PFCOMPAREFUNCTION ipfCompareFunction = CATCGMHashTableBase::CompareFunction);

  /* copy constructor */
  CATAdaptiveHashTable (const CATAdaptiveHashTable & iOther); 

  /**
  * Destructor.
  */
  virtual ~CATAdaptiveHashTable();

  /**
  * If the table already contains an element equivalent to ipElem,
  * then ipElem is NOT inserted, and 0 is returned.
  * Otherwise ipElem is inserted in the table, and 1 is returned.
  *
  * IMPORTANT INFORMATION:
  * If a table contains N elements, then the new element is inserted at position N,
  * and calling Get(N) would return it.
  * The position of elements in the table is stable UNLESS "Remove" method is called:
  * when Remove method is called, all the positions can be shuffled.
  */
  INLINE int Insert(void* ipElem);

  /**
  * If the table already contains an element E equivalent to ipElem,
  * then ipElem is NOT inserted, and the pointer to the internal pointer to E is returned (not a pointer to E!!!).
  * Otherwise ipElem is inserted in the table, and the pointer to the internal pointer to ipElem is returned (not a pointer to ipElem!!!).
  * In all cases, call (*ReturnedValue) to obtain ipElem or its equivalent.
  */
  INLINE void * LocateOrInsert(void * ipElem);

  /**
  * If the table contains an element E equivalent to ipElem,
  * then the pointer to the internal pointer to E is returned (not a pointer to E!!!).
  * In this case call (*ReturnedValue) to obtain ipElem or its equivalent.
  * If the table doesn't contain any element equivalent to ipElem, then NULL is returned.
  */
  INLINE void * Locate(void * ipElem) const;

  /**
  * If the table contains an element E equivalent to ipElem, return TRUE.
  * Otherwise return FALSE.
  */
  CATBoolean Contain(void* ipElem) const;

  /**
  * Same as "Contain".
  */
  CATBoolean Contains(void * iElem) const;

  /**
  * Same as "Contain".
  */
  CATBoolean IsInside(void * iElem) const;
  
  /**
  * If the table contains an element E equivalent to ipElem,
  * then E is removed from the table, and 1 is returned.
  * Otherwise 0 is returned.
  */
  int Remove(void * ipElem, void ** oInternalElement = NULL);

  /**
  * Returns the element inserted at position iPos,
  * with iPos going from 0 to (Size-1).
  */
  void * Get(int iPos) const;

  /**
  * Same as "Get".
  */
  void * GetItem(int iPos) const;

  /**
  * Returns the element inserted at position iPos,
  * with iPos going from 1 to Size.
  * This allows to navigate the HashTable like a CATListP.
  */
  INLINE void * operator[] (int iPos) const;

  /**
  * If the table contains an element E equivalent to ipElem,
  * returns the position of E.
  * Otherwise return -1.
  */
  int LocateReturnPos(void * ipElem) const;

  /**
  * Same as "LocateReturnPos".
  */
  int LocateItem(void * iElem) const;

  /**
  * If the table already contains an element E equivalent to ipElem,
  * then ipElem is NOT inserted, and the position of E is returned.
  * Otherwise ipElem is inserted in the table, and the position of insertion is returned.
  */
  int LocateOrInsertReturnPos(void * ipElem, CATBoolean * oInserionNeeded = NULL);

protected:

  virtual void Reallocate();
  virtual void CreateEmptyTables();
  virtual void ResetTables();
  virtual void ReplaceByLastElement(int iPos);
  INLINE CATBoolean AreInternalAndExternalElementEquivalent(void * iInternalElement, void * iExternalElement) const;

  
private:
  
  void ** _Elements;
  PFHASHKEYFUNCTION	_pHashKeyFunction;
  PFCOMPAREFUNCTION	_pCompareFunction;
};

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================

INLINE void * CATAdaptiveHashTable::Locate(void * ipElem) const
{
  int Position = this->LocateReturnPos(ipElem);
  if (Position > -1)
  {
    return _Elements + Position;
  }
  else
  {
    return NULL;
  }
}

INLINE void * CATAdaptiveHashTable::LocateOrInsert(void * ipElem)
{
  int Position = this->LocateOrInsertReturnPos(ipElem);
  if (Position > -1)
  {
    return _Elements + Position;
  }
  else
  {
    return NULL;
  }
}

INLINE int CATAdaptiveHashTable::Insert(void* ipElem)
{
  CATBoolean InserionNeeded = FALSE;
  this->LocateOrInsertReturnPos(ipElem, &InserionNeeded);
  return InserionNeeded;
}

INLINE void * CATAdaptiveHashTable::operator[] (int iPos) const
{
  return this->Get(iPos-1);
}

INLINE CATBoolean CATAdaptiveHashTable::AreInternalAndExternalElementEquivalent(void * iInternalElement, void * iExternalElement) const
{
  return (_pCompareFunction(iInternalElement, iExternalElement) == 0);
}

#endif
