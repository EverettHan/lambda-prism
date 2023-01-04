//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016
//==========================================================================
//
// 
//
//========================================================================== 
// June 2016                                                   SMT1
//========================================================================== 

#ifndef CATTritangentConnectStartInPlane3D_H
#define CATTritangentConnectStartInPlane3D_H

#include "Connect.h"
#include "CATConnectStartInPlane3D.h"

class CATMathSystem;
class CATMathAttrList;
class CATGeoFactory;
class CATCurve;
class CATConnectTool;
class CATSurLimits;
class CATSurface;
class CATMathPlane;
class CATSoftwareConfiguration;
class CATTritangentFilletTool;

class ExportedByConnect  CATTritangentConnectStartInPlane3D : public CATConnectStartInPlane3D
{   

public:
  //Do not use constructor directly. Use instead the appropriate method in CATCreateConnectStartInPlane.h

  CATTritangentConnectStartInPlane3D(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
                           CATSurface * iSupport1,
                           const CATLONG32 iSupportOrientation1,
                           CATSurface * iSupport2,
                           const CATLONG32 iSupportOrientation2,
                           CATSurface * iSupport3,
                           const CATLONG32 iSupportOrientation3,
                           CATMathPoint & iFixedPoint,
                           const CATTritangentFilletTool * iConnectTool);

  //Do not use constructor directly. Use instead the appropriate method in CATCreateConnectStartInPlane.h
  CATTritangentConnectStartInPlane3D(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
                           CATSurface * iSupport1,
                           const CATLONG32 iSupportOrientation1,
                           CATSurLimits &iLimit1,
                           CATSurface * iSupport2,
                           const CATLONG32 iSupportOrientation2,
                           CATSurLimits &iLimit2,
                           CATSurface * iSupport3,
                           const CATLONG32 iSupportOrientation3,
                           CATSurLimits &iLimit3,
                           CATMathPoint & iFixedPoint,
                           const CATTritangentFilletTool * iConnectTool);

  //~CATTritangentConnectStartInPlane3D();

  CATBoolean GetPoints(CATMathPoint & oPtSupp1, CATMathPoint & oPtSupp2, CATMathPoint & oPtSupp3);
  CATBoolean GetPoints(CATSurParam  & oPtSupp1, CATSurParam  & oPtSupp2, CATSurParam  & oPtSupp3);
  void SetLimits(CATSurLimits * iLimitsOnSupport1, CATSurLimits * iLimitsOnSupport2, CATSurLimits * iLimitsOnSupport3);
  const CATString * GetOperatorId();  

protected:
  static CATString _OperatorId;

  int GetDim();
  CATBoolean TrySafeNewton(CATMathSetOfPointsND &InitPoints, CATMathIntervalND &Domain);
  CATMathIntervalND FindDomain(double *& ioDomainArray);
  CATBoolean CreatePlaneSystem();
  double ComputeRadius();
  int RunOperator();
  void MyDebug();
  void ComputeCenterCoords(double * iX, double iRadius, double * oCenterCoords, double * oAngle = NULL);
  void WriteInput(CATCGMStream  & Str);
  
};


#endif
