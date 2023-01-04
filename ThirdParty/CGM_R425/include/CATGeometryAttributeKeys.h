// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATGeometryAttributeKeys :
//
// Contains attribute keys for geometric operators. 
//
//=============================================================================
// Usage notes:
//
// If an operator gives a result, this result can be stored as an attribute on
// an object (the object is usually one of the operands of the operator). If 
// the same operation is asked again, it is only necessary to read the 
// attribute.
//   
//
//=============================================================================
// Jul. 98  Creation                                                 L. Alt
//=============================================================================

#ifndef CATGeometryAttributeKeys_H
#define CATGeometryAttributeKeys_H

#include "Y30C3XGG.h"
#include "CATExtrapolSurface.h"

class ExportedByY30C3XGG CATGeometryAttributeKeys 
{
  public : 
  static int _Extrapol_UMin;
  static int _Extrapol_UMax;
  static int _Extrapol_VMin;
  static int _Extrapol_VMax;
};

//----------------------------------------------------------------------------
// Returns the attribute key that corresponds to the extrapolation operator 
// in provided direction. There is one attribute key for each side value (since
// it is impossible to store several attributes with the same key on one single
// element).
//----------------------------------------------------------------------------
ExportedByY30C3XGG int CATGetExtrapolAttributeKey( 
                        CATExtrapolSurface::CATSurfaceSide iNumSurfaceSide );


#endif
























