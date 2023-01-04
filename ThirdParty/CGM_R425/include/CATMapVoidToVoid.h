/* -*-c++-*- */
#ifndef CATMapVoidToVoid_h_
#define CATMapVoidToVoid_h_

// COPYRIGHT DASSAULT SYSTEMES  2001

//=============================================================================
//
// CATMapVoidToVoid :
//
// Table double a accès rapide
//
//=============================================================================
// Usage Notes:
//=============================================================================
// Jan 01                                                      LR + ILY
// Avr. 2002  Migration vers CATCGMHashTableWithAssoc          HCN
//=============================================================================

#include "CATCGMHashTableWithAssoc.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"

//Windows compatibility
#include "CATMathematics.h"

class ExportedByCATMathematics CATMapVoidToVoid : public CATCGMHashTableWithAssoc
{
public:
  CATMapVoidToVoid(int iEstimatedSize);
  ~CATMapVoidToVoid();
  CATCGMNewClassArrayDeclare;
    
  INLINE void* LocatePtr1(void* iPtr1);
  INLINE CATLONG32  Locate(void* iPtr1, void ** oPtr2 = 0); 
  INLINE void* GetPtr1(CATLONG32 iToRead);
#ifdef EB_LUCA_20150709_CATCGMHashTableWithAssoc_SetItem_Makes_HashTableLocateItem_GoWrong
  // INLINE void  SetPtr1(CATLONG32 iToChange, void* iNewPtr1); //EB --20150709 
#else
  INLINE void  SetPtr1(CATLONG32 iToChange, void* iNewPtr1);
#endif
  INLINE void* GetPtr2(CATLONG32 iToRead);
};

//-----------------------------------------------------------------------------
// LocatePtr1
//-----------------------------------------------------------------------------
INLINE void* CATMapVoidToVoid::LocatePtr1(void* iPtr1)
{
  return (this->CATCGMHashTableWithAssoc::LocateAssoc(iPtr1));
}

//-----------------------------------------------------------------------------
// Locate
//-----------------------------------------------------------------------------
INLINE CATLONG32  CATMapVoidToVoid::Locate(void* iPtr1, void ** oPtr2)
{
  return (CATLONG32)(this->CATCGMHashTableWithAssoc::LocateItem(iPtr1, oPtr2));
}

//-----------------------------------------------------------------------------
// GetPtr1
//-----------------------------------------------------------------------------
INLINE void* CATMapVoidToVoid::GetPtr1(CATLONG32 iPos)
{
  return this->CATCGMHashTableWithAssoc::GetItem(iPos);
}

#ifdef EB_LUCA_20150709_CATCGMHashTableWithAssoc_SetItem_Makes_HashTableLocateItem_GoWrong
/*
//-----------------------------------------------------------------------------
// SetPtr1
//-----------------------------------------------------------------------------
INLINE void CATMapVoidToVoid::SetPtr1(CATLONG32 iPos, void* iNewPtr1)
{
  this->CATCGMHashTableWithAssoc::SetItem(iPos, iNewPtr1);
}
*/
#else
//-----------------------------------------------------------------------------
// SetPtr1
//-----------------------------------------------------------------------------
INLINE void CATMapVoidToVoid::SetPtr1(CATLONG32 iPos, void* iNewPtr1)
{
  this->CATCGMHashTableWithAssoc::SetItem(iPos, iNewPtr1);
}
#endif
//-----------------------------------------------------------------------------
// GetPtr2
//-----------------------------------------------------------------------------
INLINE void* CATMapVoidToVoid::GetPtr2(CATLONG32 iPos)
{
  return this->CATCGMHashTableWithAssoc::GetAssoc(iPos);
}


#endif 
