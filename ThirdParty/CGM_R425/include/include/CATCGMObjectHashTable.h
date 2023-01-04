/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES  2005
//=============================================================================
// Feb. 05 Creatiom                                                       HCN
//=============================================================================
#ifndef CATCGMObjectHashTable_H
#define CATCGMObjectHashTable_H

#include "ExportedByCATCGMFusion.h"
#include "CATCGMHashTable.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"

class CATCGMObject;

typedef		int	         (*PFCGMObjectCompareFunction) ( CATCGMObject *, CATCGMObject * );	
typedef		unsigned int (*PFCGMObjectHashKeyFunction) ( CATCGMObject * ) ;

ExportedByCATCGMFusion unsigned int HashKeyCATCGMObject(CATCGMObject* ipCGMObject);
ExportedByCATCGMFusion int CompareCATCGMObject(CATCGMObject* ipCGMObject1, CATCGMObject* ipCGMObject2);

class   ExportedByCATCGMFusion  CATCGMObjectHashTable : public CATCGMHashTable
{
public:
  CATCGMObjectHashTable (PFCGMObjectHashKeyFunction ipHashKeyFunction, PFCGMObjectCompareFunction ipCompareFunction, int iEstimatedSize = 0);
  ~CATCGMObjectHashTable();
  CATCGMNewClassArrayDeclare;
  
  INLINE int           Insert(CATCGMObject* ipCGMObject);
  INLINE CATCGMObject* Get(int iPos) const;
  INLINE void*         Locate(CATCGMObject* ipCGMObject) const;
  INLINE CATCGMObject* KeyLocate(unsigned int iKey) const; 
  INLINE int           Remove(CATCGMObject* ipCGMObject);

  INLINE CATCGMObject* Next(CATCGMObject* ipCGMObject) const;
  INLINE CATCGMObject* Next(int& ioNumBucket, int& ioPos) const;
  INLINE int           Size() const;
};

//-----------------------------------------------------------------------------
// Insert
//-----------------------------------------------------------------------------
INLINE int CATCGMObjectHashTable::Insert(CATCGMObject* ipCGMObject)
{
  return (this->CATCGMHashTable::Insert((void*)ipCGMObject));
}

//-----------------------------------------------------------------------------
// Get
//-----------------------------------------------------------------------------
INLINE CATCGMObject* CATCGMObjectHashTable::Get(int iPos) const
{
  return ((CATCGMObject*)this->CATCGMHashTable::Get(iPos));
}

//-----------------------------------------------------------------------------
// Locate
//-----------------------------------------------------------------------------
INLINE void* CATCGMObjectHashTable::Locate(CATCGMObject* ipCGMObject) const
{
  return (this->CATCGMHashTable::Locate((void*)ipCGMObject));
}

//-----------------------------------------------------------------------------
// KeyLocate
//-----------------------------------------------------------------------------
INLINE CATCGMObject* CATCGMObjectHashTable::KeyLocate(unsigned int iKey) const
{
  return ((CATCGMObject*)this->CATCGMHashTable::KeyLocate(iKey));
}

//-----------------------------------------------------------------------------
// Remove
//-----------------------------------------------------------------------------
INLINE int CATCGMObjectHashTable::Remove(CATCGMObject* ipCGMObject)
{
  return (this->CATCGMHashTable::Remove((void*)ipCGMObject));
}

//-----------------------------------------------------------------------------
// Next
//-----------------------------------------------------------------------------
INLINE CATCGMObject* CATCGMObjectHashTable::Next(CATCGMObject* ipCGMObject) const
{
  return ((CATCGMObject*)this->CATCGMHashTable::Next((void*)ipCGMObject));
}

//-----------------------------------------------------------------------------
// Next
//-----------------------------------------------------------------------------
INLINE CATCGMObject* CATCGMObjectHashTable::Next(int& ioNumBucket, int& ioPos) const
{
  return ((CATCGMObject*)this->CATCGMHashTable::Next(ioNumBucket, ioPos));
}

//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------
INLINE int CATCGMObjectHashTable::Size() const
{
  return (this->CATCGMHashTable::Size());
}


#endif 
