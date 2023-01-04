// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATSimplifEdgeCrvOnSupport
// Class for operator of Simplif of a loop
//
//===================================================================
// Aug. 99    Creation                                      X.Gourdon
//===================================================================

#ifndef CATSimplifEdgeCrvOnSupport_H
#define CATSimplifEdgeCrvOnSupport_H

#include "Y30C1XMM.h"

#include "CATMathDef.h"

#include "CATMathPoint2D.h"
#include "CATMathVector2D.h"
#include "CATPGMSimplifEdgeCrvOnSupport.h"

class CATGeoFactory;
class CATEdgeCurve;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATCrvParam;
class CATSoftwareConfiguration;

struct SimplifEdgeCrvData;

class ExportedByY30C1XMM CATSimplifEdgeCrvOnSupport : public CATPGMSimplifEdgeCrvOnSupport
{
public:
  
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
   //Do not use - Use the constructor with CATSoftwareConfiguration
   CATSimplifEdgeCrvOnSupport(CATGeoFactory * iFactory,
                             const CATLONG32 iNbCrv,
                             CATEdgeCurve ** iTabECrv,
                             CATPCurve ** iTabPCrv,
                             CATPointOnEdgeCurve ** iStartPOEC,
                             CATPointOnEdgeCurve ** iEndPOEC,
                             CATSurface * iSurface);
  CATSimplifEdgeCrvOnSupport(CATGeoFactory * iFactory,
                             const CATLONG32 iNbCrv,
                             CATPCurve ** iTabPCrv,
                             CATCrvParam * iStartParam,
                             CATCrvParam * iEndParam,
                             CATSurface * iSurface);

  CATSimplifEdgeCrvOnSupport(CATGeoFactory * iFactory,
                             CATSoftwareConfiguration * iConfig,
                             const CATLONG32 iNbCrv,
                             CATEdgeCurve ** iTabECrv,
                             CATPCurve ** iTabPCrv,
                             CATPointOnEdgeCurve ** iStartPOEC,
                             CATPointOnEdgeCurve ** iEndPOEC,
                             CATSurface * iSurface);

  CATSimplifEdgeCrvOnSupport(CATGeoFactory * iFactory,
                             CATSoftwareConfiguration * iConfig,
                             const CATLONG32 iNbCrv,
                             CATPCurve ** iTabPCrv,
                             CATCrvParam * iStartParam,
                             CATCrvParam * iEndParam,
                             CATSurface * iSurface);

  ~CATSimplifEdgeCrvOnSupport();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  //
  // Set methods
  //

  // Canonical mode try to detect an eventual canonicity on the EdgeCurves
  // before doing the simplification.
  // The canonical mode is not set until this method is called with iCanonical=1
  void SetCanonicalMode(const CATBoolean iCanonical=1);
  //
  // Enable to pass the closure to simplify the wire
  //
  void SetClosureSimplification(CATBoolean iClosure=1);

  //
  // Running the operator
  //
  void Run();

  //
  // Getting the results
  //
  CATLONG32 GetNumberOfCurves();
  void BeginningCurve();
  CATBoolean NextCurve();
  // The GetEdgeCurve method can be used only if the constructor object was the one
  // with the CATEdgeCurves
  void GetEdgeCurve(CATEdgeCurve *& oECrv, CATPCurve *& oPCrv,
                    CATPointOnEdgeCurve *& oStartPOEC,
                    CATPointOnEdgeCurve *& oEndPOEC);
  void GetPCurve(CATPCurve *& oPCrv,
                 CATCrvParam & oStartParam,
                 CATCrvParam & oEndParam);
  //
  // Getting associated simplified curves
  //
  void BeginningInputCurve();
  CATBoolean NextInputCurve();
  CATLONG32 GetSimplifiedCurveIndex();
                    
  //-----------------------------------------------------------------------
  //- Protected methods
  //-----------------------------------------------------------------------
  
 protected:

  void ComputeCanonicalData(const CATLONG32 Index);
  CATBoolean SimplifyByPairs();
  CATBoolean MergePCrvPCrv(SimplifEdgeCrvData & Data0,
                           SimplifEdgeCrvData & Data1);

private:
  // Input values
  CATGeoFactory * _Factory;
  CATSoftwareConfiguration * _Config;

  CATLONG32 _NbInputCrv;
  SimplifEdgeCrvData * _InputData;
  CATSurface * _Surface;

  CATBoolean _CanonicalMode;
  CATBoolean _ClosureSimplification;
  
  // Data for output
  CATLONG32 _NbOutputCrv;
  SimplifEdgeCrvData * _OutputData;
  CATLONG32 * _SimplifiedCurveIndex;
  CATLONG32 _IndexInputCrv, _IndexSimplifiedCrv;

  // Internal data
  CATLONG32 _IndexCrv;
  double _Tolerance;
};


#endif
