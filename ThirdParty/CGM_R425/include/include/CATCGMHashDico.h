/**
 * @COPYRIGHT DASSAULT SYSTEMES 2005
 */

/* -*-C++-*-*/
#ifndef CATCGMHashDico_H
#define CATCGMHashDico_H

//
//=============================================================================
// HashDico prenant en entree des const char*.
// C'est la version CGM de la CATHashDico de System qui elle manipule
//    des CATUnicodeStrings...
//=============================================================================
// Feb. 05 Creation                                                       HCN
//=============================================================================

#include "CATCGMHashTableWithAssoc.h"
#include "CATMathematics.h"
#include "CATMathInline.h"

class ExportedByCATMathematics CATCGMHashDico : public CATCGMHashTableWithAssoc
{
public:
  CATCGMHashDico(int iEstimatedSize);
  ~CATCGMHashDico();

  INLINE int          Insert(const char* ipName, void* ipAssoc);
  INLINE void*        Locate(const char* ipName);
  INLINE const char*  GetName(int iPos);
  //INLINE void*        GetAssoc(int iPos);
};

//-----------------------------------------------------------------------------
// GetItem
//-----------------------------------------------------------------------------
INLINE int CATCGMHashDico::Insert(const char* ipName, void* ipAssoc)
{
  return (this->CATCGMHashTableWithAssoc::Insert((void*)ipName, (void*)ipAssoc));
}

//-----------------------------------------------------------------------------
// Locate
//-----------------------------------------------------------------------------
INLINE void* CATCGMHashDico::Locate(const char* ipName)
{
  return ((void*)this->CATCGMHashTableWithAssoc::LocateAssoc((void*)ipName));
}

//-----------------------------------------------------------------------------
// GetName
//-----------------------------------------------------------------------------
INLINE const char* CATCGMHashDico::GetName(int iPos)
{
  return ((const char*)this->CATCGMHashTableWithAssoc::GetItem(iPos));
}


#endif 
