#ifndef CATPGMEdgeCurveQuality_h_
#define CATPGMEdgeCurveQuality_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATCollec.h"


class CATCrvParam;
class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATMathInterval;
class CATLISTP(CATCurve);


class ExportedByCATGMModelInterfaces CATPGMEdgeCurveQuality: public CATCGMVirtual
{
public:
  /**
   * Constructor
   */
  CATPGMEdgeCurveQuality();

  /**
   * Destructor
   */
  virtual ~CATPGMEdgeCurveQuality();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------
  // return the maxgap (with respect to the input poecs)
  virtual double          ComputeMaxGap                     (CATCrvParam               * oWorstParam1 = 0,
                                                             CATCrvParam               * oWorstParam2 = 0,
                                                             double                      iTolerance   = 0.) = 0;

  // return the Global maxgap (with respect to the input poecs and listes of Pcurves)
  virtual double          ComputeGlobalMaxGap               (CATCrvParam               * oWorstParam1 = 0,
                                                             CATCrvParam               * oWorstParam2 = 0,
                                                             double                      iTolerance   = 0.) = 0;

  // return the min and max angle (in radian)
  // Note : The operator should be initialized with the first constructor and
  //        the two Curves (iCrv1 and iCrv2) must be some PCurves.
  // Note : Since no information is known on the orientation of the face/surface
  // and side on face, the angle returned are between -pi/2 and pi/2 and the sign
  // depends only on the orientation of the surfaces
  virtual CATMathInterval ComputeMinMaxAngle                () = 0;

  // return the min and max angle (in radian), taking into account the relative
  // orientation between the face and surface given by
  // OriFaceVsSurface1 and OriFaceVsSurface2 (=+1 or -1).
  // The angles returned are between -pi and pi.
  // The sign of the angles is decided from the side of the edgecurve 
  // on the first face (=1 by default, that is the first face is at the left 
  // of the EdgeCurve by default). Thus, if the SideEdgeCrvOnFace1 is not 
  // given (default behaviour), the sign of the angles is not determined.
  // Note : The operator should be initialized with the first constructor and
  //        the two Curves (iCrv1 and iCrv2) must be some PCurves.
  virtual CATMathInterval ComputeOrientedMinMaxAngle        (int                         OriFaceVsSurface1,
                                                             int                         OriFaceVsSurface2,
                                                             int                         SideEdgeCrvOnFace1 = 1) = 0;

  // return the max curvature difference
  virtual double          ComputeMaxCurvature               () = 0;

  // choice the Number of discretization point to compute the max Gap
  virtual void            SetNumberOfPoints                 (CATLONG32                   iNumberOfPoints) = 0;

  // choice the Number of discretization point per arc in case of Nurbs Curve, to compute the max Gap 
  // Default value 5
  virtual void            SetNumberOfPointsPerArcForNurbsCurve(CATLONG32 iNumberOfPoints) = 0;

  virtual void            SetReconvergeMaxGap               () = 0;

  /**
  * @nodoc
  */
  virtual void            SetSymmetrizedMapping             () = 0;

};

//do not use
ExportedByCATGMModelInterfaces CATPGMEdgeCurveQuality *CATPGMCreateEdgeCurveQuality(
        CATGeoFactory            *iFactory,
        CATEdgeCurve             *iEdgeCurve,
  const CATPointOnEdgeCurve      *iPOECStart = 0,
  const CATPointOnEdgeCurve      *iPOECEnd = 0,
  const CATLONG32                 iNbCrv = 0,
        CATCurve                **iTabCrv = 0);

//do not use
ExportedByCATGMModelInterfaces CATPGMEdgeCurveQuality *CATPGMCreateEdgeCurveQuality(
        CATGeoFactory            *iFactory,
        CATEdgeCurve             *iEdgeCurve,
  const CATPointOnEdgeCurve      *iPOECStart,
  const CATPointOnEdgeCurve      *iPOECEnd,
  const CATCurve                 *iCrv1,
  const CATCurve                 *iCrv2);

ExportedByCATGMModelInterfaces CATPGMEdgeCurveQuality *CATPGMCreateEdgeCurveQuality(
        CATGeoFactory            *iFactory,
        CATSoftwareConfiguration *iConfig,
        CATEdgeCurve             *iEdgeCurve,
  const CATPointOnEdgeCurve      *iPOECStart = 0,
  const CATPointOnEdgeCurve      *iPOECEnd = 0,
  const CATLONG32                 iNbCrv = 0,
        CATCurve                **iTabCrv = 0);

ExportedByCATGMModelInterfaces CATPGMEdgeCurveQuality *CATPGMCreateEdgeCurveQuality(
        CATGeoFactory            *iFactory,
        CATSoftwareConfiguration *iConfig,
        CATEdgeCurve             *iEdgeCurve,
  const CATPointOnEdgeCurve      *iPOECStart,
  const CATPointOnEdgeCurve      *iPOECEnd,
  const CATCurve                 *iCrv1,
  const CATCurve                 *iCrv2);

#endif /* CATPGMEdgeCurveQuality_h_ */
