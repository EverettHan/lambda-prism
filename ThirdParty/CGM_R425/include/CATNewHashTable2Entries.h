#ifndef CATNewHashTable2Entries_h
#define CATNewHashTable2Entries_h

//**************************************************************************************************************
// CATNewHashTable2Entries
//
// Class representing a hash table having 2 pointers as entries.
// The EstimatedSize DON'T NEED TO BE superior than the expected one, since a bigger number of
//  buckets is always allocated. Expressions of kind "Size * 3 / 2" ARE UNUSEFUL AND MEMORY-WASTING.
// If you're not able to estimate maximum size, it is not a big problem: reallocation is always done before
//  saturation point.
//**************************************************************************************************************
// 2011 WEEK 26 CREATION                                                                                    LD2
//**************************************************************************************************************

#define NHT2E_InheritFromKBM

#include "YP0LOGRP.h"
#include "CATBoolean.h"
#include "KeyBucketMap.h"

class ExportedByYP0LOGRP CATNewHashTable2Entries : public KeyBucketMap
{
public:

  /**
  * iSensitiveToOrder = TRUE   --> couples (A,B) and (B,A) are considered as 2 different elements
  * iSensitiveToOrder = FALSE  --> couples (A,B) and (B,A) are considered as the same element
  */
  CATNewHashTable2Entries(int iEstimatedSize = 0, CATBoolean iSensitiveToOrder = FALSE);
  virtual ~CATNewHashTable2Entries();

  CATBoolean Insert(void * ipElem1, void * ipElem2);
  CATBoolean Locate(void * ipElem1, void * ipElem2) const;
  CATBoolean Remove(void * ipElem1, void * ipElem2);

  void Get(int iPosition, void *& oElem1, void *& oElem2) const;

  CATBoolean operator == (const CATNewHashTable2Entries & iOther) const;

protected:

  virtual void Reallocate();
  virtual void CreateEmptyTables();
  virtual void ResetTables();
  virtual void ReplaceByLastElement(int iPos);

private:
  
  unsigned int HashElements(void * ipElem1, void * ipElem2) const;
  CATBoolean CompareWithExistingElements(int iPos, void * ipElem1, void * ipElem2) const;

  void ** _Elements1;
  void ** _Elements2;
  CATBoolean _SensitiveToOrder;
};

#define HashTable2EntriesBegin(TABLE, ELEM1, ELEM2, TYPE1, TYPE2)          \
{                                                                          \
  int __i##ELEM1;                                                          \
  int __n##ELEM1 = (TABLE).Size();                                         \
  for (__i##ELEM1 = 0; __i##ELEM1 < __n##ELEM1; __i##ELEM1++)              \
  {                                                                        \
    void * __Pointer1##ELEM1 = NULL;                                       \
    void * __Pointer2##ELEM1 = NULL;                                       \
    (TABLE).Get(__i##ELEM1, __Pointer1##ELEM1, __Pointer2##ELEM1);         \
    TYPE1 ELEM1 = (TYPE1)__Pointer1##ELEM1;                                \
    TYPE2 ELEM2 = (TYPE2)__Pointer2##ELEM1;                                \
    if (ELEM1 && ELEM2)                                                    \
    {

#define HashTable2EntriesEnd     \
    }                            \
  }                              \
}

#endif
