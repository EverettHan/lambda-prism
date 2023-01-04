// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//=============================================================================
// <ClassName> : CATAutoParallelFallback
//
// DESCRIPTION : For AutoParallel, determine Fallback use and precise its specifications.
//
//               - Fallback type: Euclidian or Geodesic
//               - Fallback smoothing: Tangency, Curvature or None 
//               - Fallback deviation: By default, CGM tolerance
//
// Default behavior: Euclidian Fallback with no Smoothing and CGM tolerance
//=============================================================================
// Creation       ST5       May 2011
//=============================================================================


#ifndef CATAutoParallelFallback_H
#define CATAutoParallelFallback_H

#include "CATMathInline.h"
#include "CATGMOperatorsInterfaces.h"

class ExportedByCATGMOperatorsInterfaces CATAutoParallelFallback
{
public:
  CATAutoParallelFallback();

  CATAutoParallelFallback(short iFallbackType, short iSmoothingType);

  virtual ~CATAutoParallelFallback();

  CATAutoParallelFallback * Clone() const;

  INLINE short  GetType() { return _FallbackType; };
  INLINE void   SetType(short iFallbackType) { _FallbackType = iFallbackType; };
  // 1 = geodesic
  // 0 = euclidian / default

  INLINE short  GetSmoothing() { return _SmoothingType; };
  INLINE void   SetSmoothing(short iSmoothingType) { _SmoothingType = iSmoothingType; };
  // 2 = curvature
  // 1 = tangency
  // 0 = none / default

  INLINE double  GetDeviation() { return _FallbackDeviation; };
  INLINE void   SetDeviation(double iFallbackDeviation) { _FallbackDeviation = iFallbackDeviation; };
  // if not defined, default CGM tolerance

	CATAutoParallelFallback(const CATAutoParallelFallback &);
	CATAutoParallelFallback & operator = (const CATAutoParallelFallback &);

protected:
  short   _FallbackType;
  short   _SmoothingType;
	double  _FallbackDeviation;  
};


#endif

