// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathSingleMemoryXDel:
// Class like CATMathSingleMemoryX but which deletes the composite 
// functions in the destructor 
//
//===================================================================
// Usage notes:
//
//===================================================================
// 21/07/09 NLD Ajout AddRef() et Release()
//              Ajout _UseCount
//              Ajout IsAKindOk()
//===================================================================

#ifndef CATMathSingleMemoryXDel_H
#define CATMathSingleMemoryXDel_H

#include "CATMathSingleMemoryX.h"
#include "YN000FUN.h"

class CATMathFunctionX;

class ExportedByYN000FUN CATMathSingleMemoryXDel : public CATMathSingleMemoryX
{
 public:
  CATMathSingleMemoryXDel(      CATMathFunctionX *f,
			  const double x = 0.);

 ~CATMathSingleMemoryXDel();
 CATCGMNewClassArrayDeclare;

 void AddRef(void* iReferencing) ;
 void Release(void* iReferencing) ;
 CATBoolean IsAKindOf(const CATMathClassId iClassId) const ;

 private: 
  int _UseCount;
};
#endif
