#ifdef _Coverage_GOO
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 
//==========================================================================
//
// CATConnectReconverge
//
//==========================================================================
//

//
//========================================================================== 
// MAR. 04                                                   P. Catel
//========================================================================== 
#ifndef CATConnectReconverge_H
#define CATConnectReconverge_H


#include "Connect.h"
#include "CATCGMVirtual.h"

#include "CATSurLimits.h"
#include "CATSurParam.h"
#include "CATMathPlane.h"
#include "CATMathPoint.h"

class CATGeoFactory;
class CATConnectTool;
class CATSurface;
class CATSoftwareConfiguration;
class CATMathPlane;

class ExportedByConnect CATConnectReconverge : public CATCGMVirtual
{  
public:
  CATConnectReconverge (CATGeoFactory * iFactory,
                        CATSoftwareConfiguration* iConfig,
                        CATSurface* iSupport1,
                        const CATLONG32 iOrientation1,
                        const CATSurLimits & iLimit1,
                        const CATSurParam & iParam1,
                        CATSurface* iSupport2,
                        const CATLONG32 iOrientation2,
                        const CATSurLimits & iLimit2,
                        const CATSurParam & iParam2,
                        const CATConnectTool * iConnectTool);

  ~CATConnectReconverge ();

  void SetFixedPoint(CATMathPoint &iPoint);

  void Run();
  
  CATLONG32 GetDiagnostic();
  
  void GetPoints(CATSurParam & ioParam1, CATSurParam & ioParam2);
  
  void GetMathPlane(CATMathPlane &ioMathPlane);

private:
  CATSurface *_Surf1, *_Surf2;
  CATGeoFactory * _Factory;
  CATSoftwareConfiguration * _SoftwareConfiguration;
  CATSurLimits _Lim1, _Lim2;
  CATSurParam _Param1, _Param2, _ResParam1, _ResParam2;
  CATMathPlane _MathPlane;
  CATMathPoint _Pt3D;
  CATLONG32 _Orient1, _Orient2, _Diag;
  const CATConnectTool *_Tool;
  const CATTolerance & _TolObject;

};

ExportedByConnect  
CATConnectReconverge * CreateCATConnectReconverge (CATGeoFactory * iFactory,
                                                   CATSoftwareConfiguration* iConfig,
                                                   CATSurface* iSupport1,
                                                   const CATLONG32 iOrientation1,
                                                   const CATSurLimits & iLimit1,
                                                   const CATSurParam & iParam1,
                                                   CATSurface* iSupport2,
                                                   const CATLONG32 iOrientation2,
                                                   const CATSurLimits & iLimit2,
                                                   const CATSurParam & iParam2,
                                                   const CATConnectTool * iConnectTool);

ExportedByConnect  void Remove (CATConnectReconverge *iOperator);

#endif

#endif
