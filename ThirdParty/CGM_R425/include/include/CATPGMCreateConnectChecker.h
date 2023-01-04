#ifndef CATPGMCreateConnectChecker_h_
#define CATPGMCreateConnectChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"

class CATIPGMConnectCheckerInterfaceOfCurveSurface;
class CATIPGMConnectCheckerInterfaceOfCurves;
class CATIPGMConnectCheckerInterfaceOfSurfaces;
class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATMathBox;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;



/** 
 * Connect Checker of Curve Surface : check geometric continuity (gap,tangency,curvature)
 * @param iFactory
 * @param iConfig
 * @param iEdgeCurve
 * The EdgeCurve to analyse
 * @param iPOECStart
 * Start point on EdgeCurve
 * @param iPOECEnd
 * End point on EdgeCurve
 * @param iPOECOnCrv
 * The point to analyse on EdgeCurve
 * @param iSurface
 * The Surface to analyse
 * @param iLimitSurf
 * The limits on the Surface to analyse
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMConnectCheckerInterfaceOfCurveSurface *CATPGMCreateConnectChecker(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATEdgeCurve *iEdgeCurve,
  const CATPointOnEdgeCurve *iPOECStart,
  const CATPointOnEdgeCurve *iPOECEnd,
  const CATPointOnEdgeCurve *iPOECOnCrv,
  CATSurface *iSurface,
  const CATSurLimits &iLimitSurf);

/** 
 * Connect Checker of surfaces (light constructor) : Analyse of gap, tangent, curvature and overlaps
 * @param iFactory
 * @param iConfig
 * @param iSurface1
 * @param iSurface1
 * Surfaces to analysed
 * @param iPOECStart
 * @param iPOECEnd
 * Define the interval to analysed
 * @param iPCrv1
 * @param iPCrv2
 * The two PCrv Concerned by the analyse
 * @param iOriPCrv1Mat
 * @param iOriPCrv2Mat
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMConnectCheckerInterfaceOfSurfaces *CATPGMCreateConnectChecker(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATEdgeCurve *iEdgeCurve,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  const CATPointOnEdgeCurve *iPOECStart,
  const CATPointOnEdgeCurve *iPOECEnd,
  const CATPCurve *iPCrv1,
  const CATPCurve *iPCrv2,
  int iOriPCrv1VsSurf1,
  int iOriPCrv2VsSurf2);

/** 
 * Connect Checker of surfaces : Analyse of gap, tangent, curvature and overlaps
 * @param iFactory
 * @param iConfig
 * @param iSurface1
 * @param iSurface1
 * Surfaces to analysed
 * @param iBoxFace1
 * @param iBoxFace2
 * Boundary boxes of each surfaces
 * @param iPOECStart
 * @param iPOECEnd
 * Define the interval to analysed
 * @param iPCrv1
 * @param iPCrv2
 * The two PCrv Concerned by the analyse
 * @param iOriPCrv1Mat
 * @param iOriPCrv2Mat
 * Orientation of the matter compared to each PCurve
 * @param iIsSmooth
 * =1 if the edge curve is smooth, else if =0
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMConnectCheckerInterfaceOfSurfaces *CATPGMCreateConnectChecker(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATEdgeCurve *iEdgeCurve,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  const CATSurLimits &iLimitSurf1,
  const CATSurLimits &iLimitSurf2,
  const CATPointOnEdgeCurve *iPOECStart,
  const CATPointOnEdgeCurve *iPOECEnd,
  const CATPCurve *iPCrv1,
  const CATPCurve *iPCrv2,
  int iOriPCrv1Mat,
  int iOriPCrv2Mat,
  CATBoolean iIsSmooth);

/** 
 * Connect Checker of surfaces : Analyse of gap, tangent, curvature and overlaps
 * @param iFactory
 * @param iConfig
 * @param iSurface1
 * @param iSurface1
 * Surfaces to analysed
 * @param iBoxFace1
 * @param iBoxFace2
 * Boundary boxes of each surfaces
 * @param iPOECStart
 * @param iPOECEnd
 * Define the interval to analysed
 * @param iPCrv1
 * @param iPCrv2
 * The two PCrv Concerned by the analyse
 * @param iOriPCrv1Mat
 * @param iOriPCrv2Mat
 * Orientation of the matter compared to each PCurve
 * @param iOriPCrv1Face1
 * @param iOriPCrv1Face1
 * Orientation of each surface compared to face
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMConnectCheckerInterfaceOfSurfaces *CATPGMCreateConnectChecker(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATEdgeCurve *iEdgeCurve,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  const CATSurLimits &iLimSurf1,
  const CATSurLimits &iLimSurf2,
  const CATMathBox *iBoxFace1,
  const CATMathBox *iBoxFace2,
  const CATPointOnEdgeCurve *iPOECStart,
  const CATPointOnEdgeCurve *iPOECEnd,
  const CATPCurve *iPCrv1,
  const CATPCurve *iPCrv2,
  int iOriPCrv1Mat,
  int iOriPCrv2Mat,
  int iOriPCrv1Face1,
  int iOriPCrv2Face2);

/**
 *** V5R16 new specifications ***
 * @param iFactory
 * @param iConfig
 * @param iCurve1
 * the first curve to analysed
 * @param iLimits1
 * usefull limits on iCurve1
 * @param iOriCrv1
 * Orientation of the first Curve used to reorient tangents
 * @param iCurve2
 * the second curve to analysed
 * @param iLimits2
 * usefull limits on iCurve2
 * @param iOriCrv2
 * Orientation of the second Curve used to reorient tangents
 * @param iPOECOnCrv1
 * @param iPOECOnCrv2
 * Points to analysed
 *
 * IMPORTANT: see CATConnectCheckerInterfaceOfCurves.h for details on this constructor.
 *
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMConnectCheckerInterfaceOfCurves *CATPGMCreateConnectChecker(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCurve1,
  CATCrvLimits &iLimits1,
  int iOriCrv1,
  CATCurve *iCurve2,
  CATCrvLimits &iLimits2,
  int iOriCrv2,
  CATCrvParam &iPointToAnalyze1,
  CATCrvParam &iPointToAnalyze2);

/** 
 * Connect Checker of curves : Analyse of gap, tangent, curvature and overlaps
 * @param iFactory
 * @param iConfig
 * @param iEdgeCurve1
 * the first curve to analysed
 * @param iPOECStart1
 * Start of the Edge curve
 * @param iPOECEnd1
 * End of the Edge curve
 * @param iOriEdgeCrv1
 * Orientation of the first EdgeCurve
 * Same informations about the second edge curve
 * @param iPOECOnCrv1
 * @param iPOECOnCrv2
 * Points to analysed
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMConnectCheckerInterfaceOfCurves *CATPGMCreateConnectChecker(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATEdgeCurve *iEdgeCurve1,
  const CATPointOnEdgeCurve *iPOECStart1,
  const CATPointOnEdgeCurve *iPOECEnd1,
  int iOriEdgeCrv1,
  CATEdgeCurve *iEdgeCurve2,
  const CATPointOnEdgeCurve *iPOECStart2,
  const CATPointOnEdgeCurve *iPOECEnd2,
  int iOriEdgeCrv2,
  const CATPointOnEdgeCurve *iPOECOnCrv1,
  const CATPointOnEdgeCurve *iPOECOnCrv2);

#endif /* CATPGMCreateConnectChecker_h_ */
