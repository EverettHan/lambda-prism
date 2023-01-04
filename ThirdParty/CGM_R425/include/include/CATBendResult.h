//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================
//
// CATBendResult :
//   Class used to store a resulting sub-element of CATBendSolver.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// March 06 Creation												       CQI
//=============================================================================

#ifndef CATBendResult_H
#define CATBendResult_H

#include "Y30UIUTI.h"

#include "CATCGMVirtual.h"

#include "CATCurve.h"

#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathPlane.h"
#include "CATMathInline.h"
#include "CATCrvLimits.h"

class CATGeoFactory;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATBendResult : public CATCGMVirtual
{
public :
  //-------------------------------------------------------------------------
  //  Constructor and Destructor 
  //-------------------------------------------------------------------------
  CATBendResult(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig);
  
  virtual ~CATBendResult();
  
  //-------------------------------------------------------------------------
  //  Set methods 
  //-------------------------------------------------------------------------
  
  // To create a Line result.
  void SetLineData(CATMathPoint & iStartPt, CATMathPoint & iEndPt);

  // To create a Circle result.
  void SetCircleData(double iRadius, double iStartAngle, double iEndAngle, CATMathPlane & iCirclePlane);
  
  //-------------------------------------------------------------------------
  //  Get methods 
  //-------------------------------------------------------------------------

  // To retrieve current result curve type (Undefined, Line or Circle).
  INLINE CATLONG32 GetCurveType() const { return _CurveType; }

  // To create the current result curve in the geometrical factory.
  // Caller must manage its remove.
  CATCurve * GetCurve();

  INLINE void GetCurveLimits(CATCrvLimits & oCrvLimits) const { oCrvLimits = _CrvLimits; }

protected :
  
  // Curve type flag.
  CATLONG32 _CurveType;
  
  // Line data.
  CATMathPoint _StartPt, _EndPt;
  
  // Circle data.
  double _Radius, _StartAngle, _EndAngle; 
  CATMathPlane * _CirclePlane;

  // Curve limits.
  CATCrvLimits _CrvLimits;

  // Pointer on the resulting curve (not removed !).
  CATCurve * _Curve;
  
  CATGeoFactory * _Factory;
  CATSoftwareConfiguration * _Config;
};

#endif

