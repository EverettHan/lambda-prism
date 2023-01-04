// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
//	Class :		CATCGMTagHashTableWithIndex
//	=====
//	Purpose :	Hash-Table of instances of class CATCGMObject
//	=======
//=============================================================================
// Avr. 10                                                                  VUC
//=============================================================================
#ifndef	CATCGMTagHashTableWithIndex_h
#define	CATCGMTagHashTableWithIndex_h

#include "CATCGMHashTableWithAssoc.h"
#include "CATCGMNewArray.h"

// 64bits
#include "CATDataType.h"
#include "CATCGMIncrementalTagAbsolutePosition.h"
#include "CATThrowForNullPointer.h"



// type of elements


class CATCGMTagHashTableWithIndex : public CATCGMHashTableWithAssoc
{
public:
  CATCGMTagHashTableWithIndex(int iEstimatedSize = 0);
  ~CATCGMTagHashTableWithIndex();
  CATCGMNewClassArrayDeclare;
    


  inline int            Insert(CATULONG32  iTag, CATCGMIncrementalTagAbsolutePosition*  Taginfo);
  inline int            Search(CATULONG32  iTag, CATCGMIncrementalTagAbsolutePosition*&  Taginfo) const; 
  inline void           RemoveAll();
  inline int            Remove(CATULONG32  iTag);

private:

  static unsigned int HashKeyFunction(void* ipElem);
  static int CompareFunction(void* ipElem1, void* ipElem2);
};

//-----------------------------------------------------------------------------
// Insert
//-----------------------------------------------------------------------------
inline int CATCGMTagHashTableWithIndex::Insert(CATULONG32 iTag, CATCGMIncrementalTagAbsolutePosition*  Taginfo)
{
  if(!Taginfo)CATThrowForNullPointerReturnValue(0);
  //printf("tag %d incrementindex %d \n",iTag,Taginfo->GetIncrementIndex());
  return (this->CATCGMHashTableWithAssoc::Insert((void*)CATULONG32ToPtr(iTag), (void*)(Taginfo)));
}

//-----------------------------------------------------------------------------
// Search
//-----------------------------------------------------------------------------
inline int CATCGMTagHashTableWithIndex::Search(CATULONG32  iTag,CATCGMIncrementalTagAbsolutePosition*&  Taginfo) const
{
  // portage 64 bits
  CATULONGPTR idx_64_ou_32bits;
  CATULONGPTR oTag = NULL;
  if ((this->CATCGMHashTableWithAssoc::KeyLocateItem(iTag, (void**)oTag, (void**)&idx_64_ou_32bits)) > -1)
  {
    Taginfo = (CATCGMIncrementalTagAbsolutePosition*)(idx_64_ou_32bits);
    return 1;
  }

  Taginfo = NULL;
  return 0;
}

//-----------------------------------------------------------------------------
// RemoveAll
//-----------------------------------------------------------------------------
inline void CATCGMTagHashTableWithIndex::RemoveAll()
{
  this->CATCGMHashTableWithAssoc::RemoveAll();
}

//-----------------------------------------------------------------------------
// Remove
//-----------------------------------------------------------------------------
inline int CATCGMTagHashTableWithIndex::Remove(CATULONG32  iTag)
{
  return this->CATCGMHashTableWithAssoc::Remove((void*)CATULONG32ToPtr(iTag));
}

#endif
