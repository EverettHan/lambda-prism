#ifndef CATIPGMCurveToCanonic_h_
#define CATIPGMCurveToCanonic_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMCanonicalProjectionCrvSur.h"
#include "CATSkillValue.h"
#include "CATGeometryType.h"

class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATMathVector;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMCurveToCanonic;

class ExportedByCATGMModelInterfaces CATIPGMCurveToCanonic: public CATIPGMCanonicalProjectionCrvSur
{
public:
  /**
   * Constructor
   */
  CATIPGMCurveToCanonic();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  // Returns canonical equivalent curve (or return 0 if no canonical equivalent
  // curve has been found), together with the Curve limits.
  virtual CATCurve *GetResult(CATCrvLimits &oLimits) = 0;

  // Returns canonical equivalent pcurve (or return 0 if no canonical equivalent
  // curve has been found) on the support on one of the EdgeCurve representant, 
  // together with the Curve limits and the orientation (1 or -1) with respect 
  // to the initial curve.
  // Note : GetPResult should be used if and only if a support has been specified
  //        in the constructor of the operator
  virtual CATPCurve *GetPResult(CATLONG32 &oOrientation, CATCrvLimits &oLimits) = 0;

  // Setting methods
  virtual void SetLogicalMode(CATBoolean iLogicalMode = 1) = 0;

  virtual void SetTolerance(double iTolerance) = 0;

  virtual void SetSideContinuity(short iSideContinuity) = 0;

  // Activate the search of p-lines on a generic surface.
  // Deactivates all other 3D detections.
  virtual void Set2DDetection(CATBoolean i2DDetection = 1) = 0;

  // Specify type of canonical geometry requested
  // possible types are : CATLineType, CATCircleType, CATConicType, CATEllipseType,
  //                      CATPLineType, CATPCircleType, ...
  virtual void SetRequestedType(const CATGeometricType iRequestedType) = 0;

  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  virtual CATGeoOpTimer *GetTimer() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCurveToCanonic(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
  CATGeoFactory *iFactory,
  const CATLONG32 iNbCrv,
  CATCurve **iTabCrv,
  CATCrvParam *iStartParam,
  CATCrvParam *iEndParam,
  CATSurface *iSupport = 0);

// If iSupport is specified, iSupport should be a support of one of the representant
// of iEdgeCurve
// Note : iSupport should be a plane if specified
// Do not use (use CATPGMCreateCurveToCanonic(), with CATSoftwareConfiguration)
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
  CATGeoFactory *iFactory,
  CATEdgeCurve *iEdgeCurveToCanonic,
  CATPointOnEdgeCurve *iStartPOEC,
  CATPointOnEdgeCurve *iEndPOEC,
  CATSurface *iSupport = 0,
  CATSkillValue iMode = BASIC);

// If iSupport is specified, iCurveToCanonic should be a pcurve on iSupport
// Note : iSupport should be a plane if specified
// Do not use (use CATPGMCreateCurveToCanonic(), with CATSoftwareConfiguration)
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
  CATGeoFactory *iFactory,
  CATCurve *iCurveToCanonic,
  CATCrvLimits &iLimits,
  CATSurface *iSupport = 0,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMCurveToCanonic_h_ */
