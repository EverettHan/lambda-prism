// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATReflectCurveInit :
//   Class to find init of a ReflectCurve along a curve
//
//=============================================================================
// Usage notes:
//
//
//=============================================================================
// Jan. 00  Creation                          X. Gourdon
//=============================================================================

#ifndef CATReflectCurveInit_H
#define CATReflectCurveInit_H 

#include "Y30C3XGG.h"

#include "CATCGMOperator.h"

#include "CATSkillValue.h"

#include "CATMathSetOfPointsND.h"
#include "CATMathVector.h"

#include "CATCrvParam.h"

class CATGeoFactory;
class CATCurve;
class CATPCurve;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATSoftwareConfiguration;


class ExportedByY30C3XGG CATReflectCurveInit : public CATCGMOperator
{
  public :  
  //-----------------------------------------------------------------------
  //- Object management 
  //-----------------------------------------------------------------------

  CATReflectCurveInit(CATGeoFactory * iFactory,
                      CATSoftwareConfiguration * iConfig,
                      CATEdgeCurve * iEdgeCurve,
                      CATPointOnEdgeCurve * iStartPOEC,
                      CATPointOnEdgeCurve * iEndPOEC,
                      CATSurface * iSupport,
                      const CATMathVector & iDirection,
                      double iAngle);

  ~CATReflectCurveInit();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

  // Launches the operator
  int Run();

  // Getting result
  void BeginningPoint();
  CATLONG32 GetNumberOfPoints();
  CATBoolean NextPoint();
  CATPointOnEdgeCurve * GetPointOnEdgeCurve();

  //-----------------------------------------------------------------------
  //- Private methods
  //-----------------------------------------------------------------------
private:  

  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
private :

// Input data
  CATEdgeCurve * _ECrv;
  CATPointOnEdgeCurve * _StartPOEC, * _EndPOEC;
  CATSurface * _Support;
  CATMathVector _Dir;
  double _Angle;

  // Internal data
  CATPCurve * _PCrv;
  CATCrvParam _StartParam, _EndParam;
  CATMathSetOfPointsND _Sol;

  // Data for output
  CATLONG32 _NbPoints, _IndexPoint;
  CATPointOnEdgeCurve ** _POEC;

  CATSoftwareConfiguration * _Config;
};


#endif







