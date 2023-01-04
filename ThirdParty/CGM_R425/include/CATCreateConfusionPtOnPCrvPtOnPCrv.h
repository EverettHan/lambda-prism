// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCreateConfusionPtOnPCrvPtOnPCrv :
// 2d confusion of two points on the same pcurve
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Aug. 97    Creation                         X. Gourdon
// Dec. 97    Documentation                    C. Keribin
//=============================================================================

#ifndef CATCreateConfusionPtOnPCrvPtOnPCrv_H
#define CATCreateConfusionPtOnPCrvPtOnPCrv_H

#include "Y300IINT.h"

#include "CATSkillValue.h"

class CATConfusionPtOnPCrvPtOnPCrv;
class CATGeoFactory;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATPCurve;
class CATSoftwareConfiguration;
class CATCrvParam;

/**
 * Creates an operator for testing the confusion of two CATPointOnEdgeCurves.
 * @param iTol
 * The maximum distance for deciding of the confusion.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise (not yet implemented)</dl>
 */
ExportedByY300IINT CATConfusionPtOnPCrvPtOnPCrv* 
CATCreateConfusionOnSurface(CATGeoFactory * iWhere,
                            CATSoftwareConfiguration *iConfig,
                            const CATPointOnCurve *iPoint1,
                            const CATPointOnCurve *iPoint2,
                            double iTol,
                            CATSkillValue iMode=BASIC );

/**
 * Creates an operator for testing the confusion of two CATPointOnEdgeCurves.
 * @param iTol
 * The maximum distance for deciding of the confusion.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise (not yet implemented)</dl>
 */
ExportedByY300IINT CATConfusionPtOnPCrvPtOnPCrv* 
CATCreateConfusionOnSurface(CATGeoFactory * iWhere,
                            CATSoftwareConfiguration *iConfig,
                            const CATPointOnEdgeCurve *iPoint1,
                            const CATPointOnEdgeCurve *iPoint2,
                            const CATPCurve * iPCrv,
                            double iTol,
                            CATSkillValue iMode=BASIC );

ExportedByY300IINT CATConfusionPtOnPCrvPtOnPCrv *
CATCreateConfusionOnSurface(CATGeoFactory * iWhere,
          CATSoftwareConfiguration * iConfig,
          const CATCrvParam & param1, 
				  const CATCrvParam & param2,
				  const CATPCurve * crv, 
				  double tol);

#endif



