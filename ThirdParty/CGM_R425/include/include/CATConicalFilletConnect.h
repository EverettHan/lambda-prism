//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================
//
// CATConicalFilletConnect:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// Sept. 06     Creation                                       Melina Skouras
//=============================================================================

#ifndef CATConicalFilletConnect_h
#define CATConicalFilletConnect_h

#include "CATMathDef.h"
#include "CATFilletBordersCommand.h"
#include "ConnectInt.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATConnectTool;
class CATSurface;
class CATCurve;
class CATGeometry;
class CATCrvParam;
class CATConnectTool;

class CATMathPoint;
class CATMathVector;
class CATMathSetOfPointsND;

class ExportedByConnectInt CATConicalFilletConnect
{
public:
  CATConicalFilletConnect(CATSoftwareConfiguration * iSoftwareConfiguration,
                          CATGeoFactory            * iFactory,
                          const CATConnectTool     * iTool,
                          double                     iConicalParam,
                          CATLONG32                  iConnectConfiguration);

  // copy constructor
  CATConicalFilletConnect(const CATConicalFilletConnect & ConicalConnect);

  ~CATConicalFilletConnect();


  CATSurface * CreateConicalSurface(CATMathSetOfPointsND & iParams,
                                    CATMathSetOfPointsND & iPoints,
                                    CATMathSetOfPointsND & iTangents,
                                    CATMathSetOfPointsND & iSecondDerivatives,
                                    CATLONG32              iFirstTraceIndex,
                                    CATLONG32              iSecondTraceIndex,
                                    CATLONG32              iCenterCurveIndex,
                                    CATLONG32              iAngleIndex,
                                    CATLONG32            & oCentripetalOrientation) const;


  void CreateConicalFilletBorders(CATGeoFactory * Where,
                                  CATFilletBordersCommand iCommand,
                                  CATGeometry*& SplineBorder1,
                                  CATGeometry*& SplineBorder2,
                                  CATGeometry*& StartCircularBorder, 
                                  CATGeometry*& EndCircularBorder,
                                  const CATCrvParam* iSplineStartPosition,
                                  const CATCrvParam* iSplineEndPosition,
                                  const CATCrvParam* iStartBorderPosition,
                                  const CATCrvParam* iEndBorderPosition,
                                  const CATLONG32 iParamID, 
                                  CATSurface * FilletSurface) const;

  CATCurve * CreateTransversalCurve(CATMathPoint &iT1, CATMathPoint &iT2, CATMathPoint &iCenter) const;

private:
  CATMathPoint EvalMidP(CATMathPoint &iT0, CATMathPoint &iT1, CATMathPoint &iCenter, double iAngle) const;

  CATMathVector EvaldMidP(CATMathPoint &iT0, CATMathPoint &iT1, CATMathPoint &iCenter, double iAngle,
                          CATMathVector &idT0, CATMathVector &idT1, CATMathVector &idCenter, double idAngle) const;

  CATMathVector Evald2MidP(CATMathPoint &iT0, CATMathPoint &iT1, CATMathPoint &iCenter, double iAngle,
                           CATMathVector &idT0, CATMathVector &idT1, CATMathVector &idCenter, double idAngle,
                           CATMathVector &id2T0, CATMathVector &id2T1, CATMathVector &id2Center, double id2Angle) const;

  // Calcul les points de controle permettant de passer d'un arc conique de degre 2 a un arc de degre 5
  CATBoolean ComputeEquivalentPoles(CATMathPoint * iInitialPoles,
                                    CATMathPoint * oResultPoles,
                                    double       * oResultWeights) const;

private:
  CATSoftwareConfiguration * _SoftwareConfiguration;
  CATGeoFactory            * _Factory;
  const CATConnectTool     * _Profile;
  double                     _ConicalParam;
  CATLONG32                  _ConnectConfig;


};

#endif

