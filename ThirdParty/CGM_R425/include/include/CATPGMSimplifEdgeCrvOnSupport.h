#ifndef CATPGMSimplifEdgeCrvOnSupport_h_
#define CATPGMSimplifEdgeCrvOnSupport_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"
#include "CATDataType.h"

class CATCrvParam;
class CATEdgeCurve;
class CATGeoFactory;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATSurface;
struct SimplifEdgeCrvData;

class ExportedByCATGMModelInterfaces CATPGMSimplifEdgeCrvOnSupport: public CATCGMVirtual
{
public:
  /**
   * Constructor
   */
  CATPGMSimplifEdgeCrvOnSupport();

  /**
   * Destructor
   */
  virtual ~CATPGMSimplifEdgeCrvOnSupport();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------
  //
  // Set methods
  //
  // Canonical mode try to detect an eventual canonicity on the EdgeCurves
  // before doing the simplification.
  // The canonical mode is not set until this method is called with iCanonical=1
  virtual void SetCanonicalMode(const CATBoolean iCanonical = 1) = 0;

  //
  // Enable to pass the closure to simplify the wire
  //
  virtual void SetClosureSimplification(CATBoolean iClosure = 1) = 0;

  //
  // Running the operator
  //
  virtual void Run() = 0;

  //
  // Getting the results
  //
  virtual CATLONG32 GetNumberOfCurves() = 0;

  virtual void BeginningCurve() = 0;

  virtual CATBoolean NextCurve() = 0;

  // The GetEdgeCurve method can be used only if the constructor object was the one
  // with the CATEdgeCurves
  virtual void GetEdgeCurve(
    CATEdgeCurve *&oECrv,
    CATPCurve *&oPCrv,
    CATPointOnEdgeCurve *&oStartPOEC,
    CATPointOnEdgeCurve *&oEndPOEC) = 0;

  virtual void GetPCurve(
    CATPCurve *&oPCrv,
    CATCrvParam &oStartParam,
    CATCrvParam &oEndParam) = 0;

  //
  // Getting associated simplified curves
  //
  virtual void BeginningInputCurve() = 0;

  virtual CATBoolean NextInputCurve() = 0;

  virtual CATLONG32 GetSimplifiedCurveIndex() = 0;
};

ExportedByCATGMModelInterfaces CATPGMSimplifEdgeCrvOnSupport *CATPGMCreateSimplifEdgeCrvOnSupport(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATLONG32 iNbCrv,
  CATPCurve **iTabPCrv,
  CATCrvParam *iStartParam,
  CATCrvParam *iEndParam,
  CATSurface *iSurface);

ExportedByCATGMModelInterfaces CATPGMSimplifEdgeCrvOnSupport *CATPGMCreateSimplifEdgeCrvOnSupport(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATLONG32 iNbCrv,
  CATEdgeCurve **iTabECrv,
  CATPCurve **iTabPCrv,
  CATPointOnEdgeCurve **iStartPOEC,
  CATPointOnEdgeCurve **iEndPOEC,
  CATSurface *iSurface);

ExportedByCATGMModelInterfaces CATPGMSimplifEdgeCrvOnSupport *CATPGMCreateSimplifEdgeCrvOnSupport(
  CATGeoFactory *iFactory,
  const CATLONG32 iNbCrv,
  CATPCurve **iTabPCrv,
  CATCrvParam *iStartParam,
  CATCrvParam *iEndParam,
  CATSurface *iSurface);

//Do not use - Use the constructor with CATSoftwareConfiguration
ExportedByCATGMModelInterfaces CATPGMSimplifEdgeCrvOnSupport *CATPGMCreateSimplifEdgeCrvOnSupport(
  CATGeoFactory *iFactory,
  const CATLONG32 iNbCrv,
  CATEdgeCurve **iTabECrv,
  CATPCurve **iTabPCrv,
  CATPointOnEdgeCurve **iStartPOEC,
  CATPointOnEdgeCurve **iEndPOEC,
  CATSurface *iSurface);

#endif /* CATPGMSimplifEdgeCrvOnSupport_h_ */
