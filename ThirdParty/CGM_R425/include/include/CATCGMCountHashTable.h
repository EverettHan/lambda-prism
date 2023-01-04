/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES	1999
//=============================================================================
//
// Class CATCGMCountHashTable :
//
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2000
//
// DESCRIPTION : CATCGMCountHashTable : Internal use only 
//               
//=============================================================================
// Mai. 2002   Migration vers CATCGMHashTableWithCounter            HCN
// Jui 02   Portage 64 bits                                         HCN
//=============================================================================

#ifndef CATCGMCountHashTable_H_
#define CATCGMCountHashTable_H_

#include "CATCGMHashTableWithCounter.h"
#include "CATCGMNewArray.h"
#include "YN000MAT.h"
#include "CATMathInline.h"

// 64bits
#include "CATDataType.h"



class ExportedByYN000MAT CATCGMCountHashTable : public CATCGMHashTableWithCounter
{
public:

  CATCGMCountHashTable(int iEstimatedSize = 0);
  ~CATCGMCountHashTable() ;
  CATCGMNewClassArrayDeclare;  

  INLINE int          Insert(void*iPtr);
  INLINE void*        Get(int iPos) const;
  INLINE unsigned int GetCount(void* iPtr) const; 
  INLINE unsigned int GetCount(int iPos) const ;  
};

//-----------------------------------------------------------------------------
// Insert
//-----------------------------------------------------------------------------
INLINE int CATCGMCountHashTable::Insert(void* iPtr)
{
  return (this->CATCGMHashTableWithCounter::InsertReturnPos(iPtr, (void*)1));
}

//-----------------------------------------------------------------------------
// Get
//-----------------------------------------------------------------------------
INLINE void* CATCGMCountHashTable::Get(int iPos) const
{
  return (this->CATCGMHashTableWithCounter::GetItem(iPos));
}

//-----------------------------------------------------------------------------
// GetCount
//-----------------------------------------------------------------------------
INLINE unsigned int CATCGMCountHashTable::GetCount(void* iPtr) const
{
  return (unsigned int)CATPtrToUINT32((this->CATCGMHashTableWithCounter::LocateAssoc(iPtr)));  
}

//-----------------------------------------------------------------------------
// GetCount
//-----------------------------------------------------------------------------
INLINE unsigned int CATCGMCountHashTable::GetCount(int iPos) const
{
  return (unsigned int)CATPtrToUINT32((this->CATCGMHashTableWithCounter::GetAssoc(iPos)));
}


#endif


