#ifndef CATMATHATTRLIST_H
#define CATMATHATTRLIST_H

// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
//
//     Advanced mathematics operators attributes list for specific parameterizations
//
//=============================================================================
// XX/XX/XX XXX Creation
// 30/07/08 NLD Ajout _staticattr et _size pour perfos
// 27/07/09 NLD Ajout GetNbAttribute() et GetAttribute() par numero
// 21/06/12 NLD Ajout Reset()
//=============================================================================
#include "YN000FUN.h"

#include "CATMathAttribute.h"
#include "CATCGMNewArray.h"

class ExportedByYN000FUN CATMathAttrList
{

 private:

  CATLONG32 _nbAttr;
  #define CATMathAttrList_StaticSize 5
  const CATMathAttribute ** _attr;
  #ifdef CATMathAttrList_StaticSize
  const CATMathAttribute * _staticattr[CATMathAttrList_StaticSize] ;
  int _size ;
  #endif 

 public:

  CATMathAttrList();
  CATMathAttrList(const CATMathAttrList & list);
  CATMathAttrList(const CATMathAttribute * attr);
  ~CATMathAttrList();

  /** @nodoc */
  CATCGMNewClassArrayDeclare;

  void AddAttribute(const CATMathAttribute * attr);

  const CATMathAttribute * GetAttribute(const CATMathAttrId type,
                                        const CATLONG32 n = 1) const;

  // Get number of attributes
  int GetNbAttribute() const;

  // Get attribute by number (from 1 to GetNbAttr())
  const CATMathAttribute* GetAttribute(int iNumAttr) const;

  // Reset list content
  void Reset();


};

#endif
