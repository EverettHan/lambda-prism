#ifndef CATCGMVersionUnofficial_h
#define CATCGMVersionUnofficial_h
// COPYRIGHT DASSAULT SYSTEMES  2007
//-----------------------------------------------------------------------------
// Context : Restricted
//-----------------------------------------------------------------------------
/**
* @level Private
* @usage U1
*/
#include "ExportedByCATMathStream.h"
#include "CATMathStreamVersionDef.h"

class ExportedByCATMathStream CATCGMVersionUnofficial
{
public:
 static CATCGMStreamVersion Get();
 static CATCGMStreamVersion Set(const CATCGMStreamVersion iVersion);

private:
  static CATCGMStreamVersion _Unofficial;
};

#endif
