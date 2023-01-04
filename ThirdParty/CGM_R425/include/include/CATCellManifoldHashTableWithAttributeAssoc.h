/**
 * @COPYRIGHT DASSAULT SYSTEMES 2011
 */
/* -*-c++-*- */
//===========================================================================
//
// Mar. 2011   Creation                            JJ3
//
//===========================================================================
#ifndef  CATCellManifoldHashTableWithAttributeAssoc_h
#define  CATCellManifoldHashTableWithAttributeAssoc_h

#include "PersistentCell.h"
#include "CATCGMHashTableWithAssoc.h"

class CATCellManifold;
class CATManifoldAttribute;

class ExportedByPersistentCell CATCellManifoldHashTableWithAttributeAssoc 
{
public:

  CATCellManifoldHashTableWithAttributeAssoc(int iEstimatedSize = 0);

  virtual ~CATCellManifoldHashTableWithAttributeAssoc();

  int          Insert(CATCellManifold * iCM, CATManifoldAttribute * iAssocAttr);
  //int          InsertReturnPos(void* ipElem, void* ipAssoc);
  
  int          LocateItem(CATCellManifold * iCM, CATManifoldAttribute ** oAssocAttr) const;
  //int          KeyLocateItem(unsigned int iKey, void** ippElem, void** oppAssoc) const;
  CATManifoldAttribute * LocateAssoc(CATCellManifold * iCM) const;
  //void         SetItem(int iPos, void* ipElem);
  //INLINE void  SetAssoc(int iPos, void* ipAssoc);
  //int          SetAssoc(void* ipElem, void* ipAssoc);
  CATCellManifold * GetItem(int iPos) const;
  //INLINE void* GetItemAndAssoc(int iPos, void** oppAssoc) const;
  //INLINE void* GetAssoc(int iPos) const;

  int          Size() const;
  //void         RemoveAll();

  //VUC: 2010-03-04
 // int Remove(void* ipElem);

private : 
  CATCGMHashTableWithAssoc * _HT;
};



#endif

