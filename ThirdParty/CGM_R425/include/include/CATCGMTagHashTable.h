/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES  2005
//=============================================================================
// Feb. 05 Creatiom                                                       HCN
//=============================================================================
#ifndef CATCGMTagHashTable_H
#define CATCGMTagHashTable_H

#include "CATMathematics.h"
#include "CATCGMHashTable.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"
//#include "CATDataType.h"

typedef		int	         (*PFTagCompareFunction) ( CATULONG32 , CATULONG32 );	
typedef		unsigned int (*PFTagHashKeyFunction) ( CATULONG32 ) ;

ExportedByCATMathematics unsigned int HashKeyTag(CATULONG32 iTag);
ExportedByCATMathematics int CompareTag(CATULONG32 iTag1, CATULONG32 iTag2);

class   ExportedByCATMathematics  CATCGMTagHashTable : public CATCGMHashTable
{
public:
  CATCGMTagHashTable (PFTagHashKeyFunction ipHashKeyFunction, PFTagCompareFunction ipCompareFunction, int iEstimatedSize = 0);
  ~CATCGMTagHashTable();
  CATCGMNewClassArrayDeclare;
  
  INLINE int           Insert(CATULONG32 iTag);
  INLINE CATULONG32 Get(int iPos) const;
  INLINE void*         Locate(CATULONG32 iTag) const;
  INLINE CATULONG32 KeyLocate(unsigned int iKey) const; 
  INLINE int           Remove(CATULONG32 iTag);

  INLINE int           Size() const;
};

//-----------------------------------------------------------------------------
// Insert
//-----------------------------------------------------------------------------
INLINE int CATCGMTagHashTable::Insert(CATULONG32 iTag)
{
  return (this->CATCGMHashTable::Insert((void*)iTag));
}

//-----------------------------------------------------------------------------
// Get
//-----------------------------------------------------------------------------
INLINE CATULONG32 CATCGMTagHashTable::Get(int iPos) const
{
  void * tag = this->CATCGMHashTable::Get(iPos);
  return (CATPtrToULONG32(tag));
}

//-----------------------------------------------------------------------------
// Locate
//-----------------------------------------------------------------------------
INLINE void* CATCGMTagHashTable::Locate(CATULONG32 iTag) const
{
  return (this->CATCGMHashTable::Locate((void*)iTag));
}

//-----------------------------------------------------------------------------
// KeyLocate
//-----------------------------------------------------------------------------
INLINE CATULONG32 CATCGMTagHashTable::KeyLocate(unsigned int iKey) const
{
  void * tag = this->CATCGMHashTable::KeyLocate(iKey);
  return (CATPtrToULONG32(tag));
}

//-----------------------------------------------------------------------------
// Remove
//-----------------------------------------------------------------------------
INLINE int CATCGMTagHashTable::Remove(CATULONG32 iTag)
{
  return (this->CATCGMHashTable::Remove((void*)iTag));
}

//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------
INLINE int CATCGMTagHashTable::Size() const
{
  return (this->CATCGMHashTable::Size());
}


#endif 
