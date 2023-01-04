/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
// Class CATConnectSmooth
//-----------------------------------------------------------------------------
// June 2005  Creation                                  CWM
// 
//=============================================================================
//
// Usage notes:
//
//=============================================================================
#ifndef CATConnectSmooth_h
#define CATConnectSmooth_h

#include "CATCGMVirtual.h"
#include "Connect.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATTolerance.h"
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATMathFunctionX;
class CATSurface;
class CATPCurve;
class CATMathSetOfPointsND;

class ExportedByConnect CATConnectSmooth : public CATCGMVirtual
{
public:
  //---------------------------------------------------------------------------
  // Object Management
  //---------------------------------------------------------------------------
  CATConnectSmooth( CATGeoFactory            * iFactory, 
                    CATSoftwareConfiguration * iConfig);

  virtual ~CATConnectSmooth();

  virtual int Run()=0;

  virtual void SetData(CATSurface                 * iSupport1,
                       const CATLONG32            & iOrientation1,
                       CATSurface                 * iSupport2,
                       const CATLONG32            & iOrientation2,
                       const CATMathFunctionX     * iRadiusFunction,
                       CATPCurve			            * iP1,
                       CATPCurve				          * iP2,
                       const CATMathFunctionX     * iW,
                       const CATMathSetOfPointsND * iExactParameters);

  virtual void SetTolerance(double iTolForApprox, double iTolForSmooth);

  virtual void GetPlaneDirEquations(const CATMathFunctionX * & oEqX, 
                                    const CATMathFunctionX * & oEqY, 
                                    const CATMathFunctionX * & oEqZ);

  virtual CATConnectSmooth * Clone(); 

protected:
  CATGeoFactory * _Factory;
  CATSoftwareConfiguration * _Config;
  double _TolForApprox, _TolForSmooth;
  CATBoolean _IsDataSet;
  CATSurface * _Support1, * _Support2;
	CATLONG32 _orient1, _orient2;
  CATPCurve * _P1,  * _P2;
  const CATMathFunctionX *_U1, *_V1, *_U2, *_V2, *_W;
  const CATMathFunctionX *_R;
  CATLONG32 _NumberOfCombs;
  CATMathSetOfPointsND *_ExactParameters;
  CATMathFunctionX *_dCsX, *_dCsY, *_dCsZ; 
  const CATTolerance & _TolObject;
};
#endif
