// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
//	Class :		CATCGMObjectWithIndexHashTable
//	=====
//	Purpose :	Hash-Table of instances of class CATCGMObject
//	=======
//=============================================================================
// Jul. 98 Creation                                                       LR 
// Sep. 99 Gestion simplifiee sans Remove                                 TCX
// Avp. 02 Migration vers CATCGMHashTableWithAssoc                        HCN
// Jul. 02 Portage 64 bits                                                HCN
// Feb. 05 Renommage de CATCGMObjectHashTable
//           en CATCGMObjectWithIndexHashTable                            HCN
//=============================================================================
#ifndef	CATCGMObjectWithIndexHashTable_h
#define	CATCGMObjectWithIndexHashTable_h

#include "CATCGMHashTableWithAssoc.h"
#include "CATCGMNewArray.h"

// 64bits
#include "CATDataType.h"

// type of elements
class CATCGMObject ;
class CATICGMObject ;


class CATCGMObjectWithIndexHashTable : public CATCGMHashTableWithAssoc
{
public:
  CATCGMObjectWithIndexHashTable(int iEstimatedSize = 0);
  ~CATCGMObjectWithIndexHashTable();
  CATCGMNewClassArrayDeclare;
    
  inline int            Insert(CATCGMObject*cgm, CATULONG32  idx);
  inline int            Search(CATULONG32  iTag, CATCGMObject *&cgm , CATULONG32  &idx) const;
  CATICGMObject*        KeyInterfaceLocate(int iTag) const;
  inline void           RemoveAll();
  inline int Remove(CATCGMObject* iObjectToRemove);

private:

  static unsigned int HashKeyFunction(void* ipElem);
  static int CompareFunction(void* ipElem1, void* ipElem2);
};

//-----------------------------------------------------------------------------
// Insert
//-----------------------------------------------------------------------------
inline int CATCGMObjectWithIndexHashTable::Insert(CATCGMObject*cgm, CATULONG32  idx)
{
  return (this->CATCGMHashTableWithAssoc::Insert((void*)cgm, (void*)CATULONG32ToPtr(idx)));
}

//-----------------------------------------------------------------------------
// Search
//-----------------------------------------------------------------------------
inline int CATCGMObjectWithIndexHashTable::Search(CATULONG32  iTag, CATCGMObject *&cgm , CATULONG32  &idx) const
{
  // portage 64 bits
  CATULONGPTR idx_64_ou_32bits;

  if ((this->CATCGMHashTableWithAssoc::KeyLocateItem(iTag, (void**)&cgm, (void**)&idx_64_ou_32bits)) > -1)
  {
    idx = (CATULONG32 )CATPtrToULONG32(idx_64_ou_32bits);
    return 1;
  }

  idx = 0xFFFFFFFF;
  return 0;
}


//-----------------------------------------------------------------------------
// RemoveAll
//-----------------------------------------------------------------------------
inline void CATCGMObjectWithIndexHashTable::RemoveAll()
{
  this->CATCGMHashTableWithAssoc::RemoveAll();
}

//-----------------------------------------------------------------------------
// Remove
//-----------------------------------------------------------------------------
inline int CATCGMObjectWithIndexHashTable::Remove(CATCGMObject* iObjectToRemove)
{
  return this->CATCGMHashTableWithAssoc::Remove((void*)iObjectToRemove);
}

#endif
