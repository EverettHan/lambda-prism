/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
// CATGenericRuledSurface Interface
//-----------------------------------------------------------------------------
// April  98   Creation                                     NDN
// Sept.  14   Added the function Unextrapol().             R1Y
//=============================================================================
//
// Usage notes:
//
//=============================================================================
#ifndef CATGenericRuledSurface_h
#define CATGenericRuledSurface_h

#include "CATBaseUnknown.h"
#include "CATSurface.h"
class CATMathSetOfPointsND;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGenericRuledSurface ;
#else
extern "C" const IID IID_CATGenericRuledSurface ;
#endif

class ExportedByCATGMGeometricInterfaces CATGenericRuledSurface : public CATSurface
{
  CATDeclareInterface;

 public:
  
//This method return the datas used to create the CATGenericRuledSurface
//oParams is of dimension 1, while the others are of dimension 6
  virtual void GetCreationData(CATMathSetOfPointsND &oParams,
			       CATMathSetOfPointsND &oPoints,
			       CATMathSetOfPointsND &oTangents,
			       CATMathSetOfPointsND &oSecondDeriv) const = 0;

//This method allow you to change the parametric space in the ruled direction
  virtual void SetParametricSpace(const double NewStartV,const double NewEndV) = 0;

  virtual void GetParametricSpace(double & oStartV,double & oEndV) const = 0;

//Extrapolation.
  virtual void Extrapolation(const CATMathSetOfPointsND * iParams,
			const CATMathSetOfPointsND * iPoints,
			const CATMathSetOfPointsND * iTangents,
			const CATMathSetOfPointsND * iSecondDerivatives,
			CATLONG32 iFirstTraceIndex,
			CATLONG32 iSecondTraceIndex) =0;

//Un-extrapolation.
  virtual CATBoolean Unextrapol(const CATSurLimits & iNewLimits,
                                      CATLONG32      iSplitMode) = 0;
};
  CATDeclareHandler(CATGenericRuledSurface, CATSurface);

#endif
