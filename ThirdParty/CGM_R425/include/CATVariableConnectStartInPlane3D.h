#ifndef CATVariableConnectStartInPlane3D_H
#define CATVariableConnectStartInPlane3D_H

#include "Connect.h"
#include "CATConnectStartInPlane3D.h"
#include "CATGeoStreamFactory.h"

class CATMathSystem;
class CATMathAttrList;
class CATGeoFactory;
class CATCurve;
class CATConnectTool;
class CATSurLimits;
class CATSurface;
class CATMathPlane;
class CATSoftwareConfiguration;
class CATVariableFilletTool;

class ExportedByConnect  CATVariableConnectStartInPlane3D : public CATConnectStartInPlane3D
{   

public:

  //Do not use constructor directly. Use instead the appropriate method in CATCreateConnectStartInPlane.h
  CATVariableConnectStartInPlane3D(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
                           CATSurface * iSupport1,
                           const CATLONG32 iSupportOrientation1,
                           CATSurface * iSupport2,
                           const CATLONG32 iSupportOrientation2,
                           const CATMathPoint & iFixedPoint,
                           const CATVariableFilletTool * iConnectTool,
                           CATCurve * iSpine = NULL);

  CATCurve* GetSpine();

  const CATString * GetOperatorId(); 

 
protected:
  static CATString _OperatorId;

  CATCurve * _Spine;
  int GetDim();
  CATMathIntervalND FindDomain(double *& ioDomainArray);
  CATBoolean CreatePlaneSystem();
  double ComputeRadius();
  void WriteInput(CATCGMStream  & Str);
  void MyDebug();

};


#endif
