/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

/* -*-C++-*-*/
#ifndef CATListDbgPoseSurHashTable_H
#define CATListDbgPoseSurHashTable_H

//=============================================================================
// Hash table utilisee pour trier des
// ListPOfCATCGMDbgPoseSur / ListPOfCATCGMDbgPoseSur suivant la cellule
//
// Inspire de CATArrayBoundingCellHashTable
//
//=============================================================================
// Nov. 03 Creation                                                       HCN
//=============================================================================

#include "CATCGMHashTableWithAssoc.h"
#include "CATCGMNewArray.h"

//On ne peut pas se contenter de "class ListPOfCATCGMDbgPoseSur" a cause du define dans le .h;
#include "CATListOfCATCGMDbgPoseSurs.h"
#include "CATMathInline.h"

class CATGeometry;


class CATListDbgPoseSurHashTable : public CATCGMHashTableWithAssoc
{
public:
  CATListDbgPoseSurHashTable(int iEstimatedSize);
  ~CATListDbgPoseSurHashTable();
  CATCGMNewClassArrayDeclare;

  INLINE int                      Insert(CATGeometry* ipSupport, ListPOfCATCGMDbgPoseSur* ipListOfPoseSurs);
  INLINE ListPOfCATCGMDbgPoseSur* Locate(CATGeometry* ipSupport);
  INLINE CATGeometry*             GetSupport(int iPos);
  INLINE ListPOfCATCGMDbgPoseSur* GetListOfPoseSurs(int iPos);
};

//-----------------------------------------------------------------------------
// GetItem
//-----------------------------------------------------------------------------
INLINE int CATListDbgPoseSurHashTable::Insert(CATGeometry* ipSupport, ListPOfCATCGMDbgPoseSur* ipListOfPoseSurs)
{
  return (this->CATCGMHashTableWithAssoc::Insert((void*)ipSupport, (void*)ipListOfPoseSurs));
}

//-----------------------------------------------------------------------------
// Locate
//-----------------------------------------------------------------------------
INLINE ListPOfCATCGMDbgPoseSur* CATListDbgPoseSurHashTable::Locate(CATGeometry* ipSupport)
{
  return ((ListPOfCATCGMDbgPoseSur*)this->CATCGMHashTableWithAssoc::LocateAssoc((void*)ipSupport));
}

//-----------------------------------------------------------------------------
// GetGeo
//-----------------------------------------------------------------------------
INLINE CATGeometry* CATListDbgPoseSurHashTable::GetSupport(int iPos)
{
  return ((CATGeometry*)this->CATCGMHashTableWithAssoc::GetItem(iPos));
}

//-----------------------------------------------------------------------------
// GetAssoc
//-----------------------------------------------------------------------------
INLINE ListPOfCATCGMDbgPoseSur* CATListDbgPoseSurHashTable::GetListOfPoseSurs(int iPos)
{
  return ((ListPOfCATCGMDbgPoseSur*)this->CATCGMHashTableWithAssoc::GetAssoc(iPos));
}

#endif 
