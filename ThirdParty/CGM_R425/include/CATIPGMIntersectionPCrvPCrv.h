#ifndef CATIPGMIntersectionPCrvPCrv_h_
#define CATIPGMIntersectionPCrvPCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATIntersectionPCrvPCrvSign.h"
#include "CATConst2D.h"
#include "CATSkillValue.h"

class CATEdgeCurve;
class CATMathAttrList;
class CATMathFunctionX;
class CATMathInterval2D;
class CATMathSetOfPointsND;
class CATMathVector2D;
class CATPCrvPCrvResultConfusion;
class CATPCrvPCrvResultPoint;
class CATPCurve;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATSurParam;
class CATCrvParam;
class CATCrvLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMIntersectionPCrvPCrv;

class ExportedByCATGMModelInterfaces CATIPGMIntersectionPCrvPCrv: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMIntersectionPCrvPCrv();

  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const = 0;

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  //NLD051208 Run() inconditionnel au lieu de CATCGMOperatorDebugDeclareRun(CATIPGMIntersectionPCrvPCrv,CATIPGMGeoOperator);
  virtual int Run() = 0;

  virtual void SetExtremityTol(const double tol) = 0;

  virtual void SetConfusionTol(const double tol) = 0;

  virtual void SetNoTangentialExtremitySolution(
    const CATPointOnEdgeCurve *iPOEC1,
    const double iTol1,
    const CATPointOnEdgeCurve *iPOEC2,
    const double iTol2) = 0;

  // 3D tangential tolerance; defaut is 0.01*resolution
  virtual void SetTangentialTolerance(double iTangentialTol) = 0;

  //Activation de la stabilisation
  //Stabilization des zones de confusion - methode en cours de conv voir avec EAB pour utilisation
  virtual void SetStabilizeConfusions(CATBoolean iIsStabilize = TRUE) = 0;

  //Remplace une des pcurves intersectees (la premiere). 
  virtual void SetPCurve(
    const CATPCurve *PCurve,
    const CATPointOnEdgeCurve *iStart2,
    const CATPointOnEdgeCurve *iEnd2) = 0;

  virtual void SetPCurve(const CATPCurve *PCurve, const CATCrvLimits &Limit) = 0;

  virtual void SetPCurves(
    const CATPCurve *PCurve0,
    const CATCrvLimits &Limit0,
    const CATPCurve *PCurve1,
    const CATCrvLimits &Limit1,
    const CATBoolean iCheckSurfaces = TRUE) = 0;

  // Reading point results
  virtual CATLONG32 GetNumberOfPoints() const = 0;

  virtual void BeginningPoint() = 0;

  virtual CATLONG32 NextPoint() = 0;

  //
  // Si les deux Pcurves sont les memes (iIndex =1 pour la premiere et iIndex = 2 pour la deuxieme)
  //
  virtual void GetCurveParam(
    const CATPCurve *Pcurve,
    CATCrvParam &oParam,
    const CATLONG32 Index = -1) const = 0;

  virtual void GetStartConfusionParam(
    const CATPCurve *Pcurve,
    CATCrvParam &oParam,
    const CATLONG32 Index = 0) const = 0;

  virtual void GetEndConfusionParam(
    const CATPCurve *Pcurve,
    CATCrvParam &oParam,
    const CATLONG32 Index = 0) const = 0;

  //
  //
  virtual CATPointOnCurve *GetPointOnCurve(const CATPCurve *Pcurve) const = 0;

  virtual CATPointPositionOnCurve GetPointPositionOnCurve(const CATPCurve *Pcurve) const = 0;

  virtual CATIntersectionPCrvPCrvSign GetPointSignature(const CATPCurve *Pcurve) const = 0;

  virtual CATIntersectionPCrvPCrvSign GetPointSignature(const CATEdgeCurve *iECrv) const = 0;

  virtual CATIntersectionPCrvPCrvCrossing GetPointCrossing(const CATPCurve *Pcurve) const = 0;

  virtual CATIntersectionPCrvPCrvCrossing GetPointCrossing(const CATEdgeCurve *iECrv) const = 0;

  //
  //Reading Signature and Crossing Point results on EdgeCurve
  //
  virtual CATIntersectionPCrvPCrvSign GetPointSignatureOnEdgeCurve(
    const CATEdgeCurve *iECrv) const = 0;

  virtual CATIntersectionPCrvPCrvCrossing GetPointCrossingOnEdgeCurve(
    const CATEdgeCurve *iECrv) const = 0;

  //
  // Reading mixed solutions
  //
  virtual CATLONG32 GetNumberOfMixedPoints() const = 0;

  virtual void BeginningMixedPoint() = 0;

  virtual CATLONG32 NextMixedPoint() = 0;

  virtual CATPointOnEdgeCurve *GetStartMixedSolution(
    const CATEdgeCurve *iECrv,
    const CATPCurve *Pcurve,
    const CATLONG32 Index = 0) = 0;

  virtual CATPointOnEdgeCurve *GetEndMixedSolution(
    const CATEdgeCurve *iECrv,
    const CATPCurve *Pcurve,
    const CATLONG32 Index = 0) = 0;

  virtual void GetMixedLimits(const CATPCurve *Pcurve, CATCrvLimits &oLimit) const = 0;

  //
  // Reading confusion results
  //
  virtual CATLONG32 GetNumberOfConfusions() const = 0;

  virtual void BeginningConfusion() = 0;

  virtual CATLONG32 NextConfusion() = 0;

  virtual CATEdgeCurve *GetEdgeCurve() = 0;

  // Confusion result relative to PCurve only
  virtual void GetConfusionLimits(const CATPCurve *Pcurve, CATCrvLimits &oLimit) const = 0;

  // Get extremity parameter of current confusion
  // iExtremity=0: start, =1: end
  virtual void GetCurrentConfusionExtremityParam(
    const CATPCurve *Pcurve,
    int iExtremity,
    CATCrvParam &oParam) const = 0;

  virtual CATPointOnCurve *GetConfusionStartPoint(const CATPCurve *Pcurve) const = 0;

  virtual CATPointOnCurve *GetConfusionEndPoint(const CATPCurve *Pcurve) const = 0;

  virtual CATPointPositionOnCurve GetConfusionStartPositionOnCurve(
    const CATPCurve *Pcurve) const = 0;

  virtual CATPointPositionOnCurve GetConfusionEndPositionOnCurve(
    const CATPCurve *Pcurve) const = 0;

  // Confusion results relative to EdgeCurve containing PCurve
  virtual CATPointOnEdgeCurve *GetPointOnEdgeCurve(
    const CATEdgeCurve *iECrv,
    const CATPCurve *Pcurve,
    const CATLONG32 iIndex = 0) const = 0;

  virtual CATPointOnEdgeCurve *GetConfusionStartPoint(
    const CATEdgeCurve *iECrv,
    const CATPCurve *Pcurve = 0,
    const CATLONG32 iIndex = 0) const = 0;

  virtual CATPointOnEdgeCurve *GetConfusionEndPoint(
    const CATEdgeCurve *iECrv,
    const CATPCurve *Pcurve = 0,
    const CATLONG32 iIndex = 0) const = 0;

  // A confusion is degenerated on Edge of index iIndex if it is shorter than the resolution 
  // on this Edge and larger than the resolution on the other edge.
  virtual CATBoolean IsConfusionDegenerated(const CATLONG32 iIndex) const = 0;

  //=======================================================================
  // Methodes obsoletes (ne plus utiliser)
  //=======================================================================
  virtual CATPointPositionOnCurve GetPointPositionOnCurve(const CATEdgeCurve *iECrv) const = 0;

  virtual CATPointPositionOnCurve GetConfusionStartPositionOnCurve(
    const CATEdgeCurve *iECrv) const = 0;

  virtual CATPointPositionOnCurve GetConfusionEndPositionOnCurve(
    const CATEdgeCurve *iECrv) const = 0;

  // XGN 28-04-98
  // if returned pointer is not 0, ParamMapping can be used to construct the merged-curve 
  // resulting from the confusion.
  // The returned pointer must be deleted by the caller
  virtual CATMathSetOfPointsND *GetParamMapping() = 0;

  // Specialized method for Boolean : return 0 for classical solution,
  // return 1 when the point solution was obtained as a confusion
  // degenerated on one side as a point.
  virtual CATBoolean GetPointSolutionType() const = 0;

  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  virtual CATGeoOpTimer *GetTimer() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMIntersectionPCrvPCrv(); // -> delete can't be called
};

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------  
ExportedByCATGMModelInterfaces CATIntersectionPCrvPCrvSign CATPGMIntersectionPCrvPCrvSignature(
  const CATPCurve *Pcurve1,
  const CATCrvParam &p1,
  const CATPCurve *Pcurve2,
  const CATCrvParam &p2);

ExportedByCATGMModelInterfaces CATIntersectionPCrvPCrvSign CATPGMIntersectionPCrvPCrvSignature(
  const CATPointOnCurve *p1,
  const CATPointOnCurve *p2);

ExportedByCATGMModelInterfaces CATIntersectionPCrvPCrvSign CATPGMIntersectionPCrvPCrvSignature(
  const CATPointOnEdgeCurve *iPOEC1,
  const CATPCurve *iPCrv1,
  const CATPointOnEdgeCurve *iPOEC2,
  const CATPCurve *iPCrv2);

//V1 & V2 should be non scaled vectors, ie with Factory Scale = 1
ExportedByCATGMModelInterfaces CATIntersectionPCrvPCrvSign CATPGMIntersectionPCrvPCrvSignature(
  const CATMathVector2D &V1,
  const CATMathVector2D &V2);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersection(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *_Config,
  const CATPCurve *Pcurve1,
  const CATPCurve *Pcurve2,
  const CATSkillValue skill = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersection(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *_Config,
  const CATPCurve *Pcurve1,
  const CATCrvLimits &Limit1,
  const CATPCurve *Pcurve2,
  const CATCrvLimits &Limit2,
  const CATSkillValue skill = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersection(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *_Config,
  const CATPointOnEdgeCurve *iPoec1On1,
  const CATPointOnEdgeCurve *iPoec2On1,
  const CATPCurve *iPCrv1,
  const CATPointOnEdgeCurve *iPoec1On2,
  const CATPointOnEdgeCurve *iPoec2On2,
  const CATPCurve *iPCrv2,
  const CATSkillValue skill = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersectionNoCheck(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *_Config,
  const CATPointOnEdgeCurve *iPoec1On1,
  const CATPointOnEdgeCurve *iPoec2On1,
  const CATPCurve *iPCrv1,
  const CATPointOnEdgeCurve *iPoec1On2,
  const CATPointOnEdgeCurve *iPoec2On2,
  const CATPCurve *iPCrv2,
  const CATSkillValue skill = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersectionPCrvPCrv(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *iConfig,
  const CATPCurve *Pcurve1,
  const CATPCurve *Pcurve2);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersectionPCrvPCrv(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *iConfig,
  const CATPCurve *Pcurve1,
  const CATCrvLimits &Limit1,
  const CATPCurve *Pcurve2,
  const CATCrvLimits &Limit2);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionPCrvPCrv *CATPGMCreateIntersectionPCrvPCrv(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *iConfig,
  const CATEdgeCurve *iECrv1,
  const CATPCurve *Pcurve1,
  const CATCrvLimits &Limit1,
  const CATEdgeCurve *iECrv2,
  const CATPCurve *Pcurve2,
  const CATCrvLimits &Limit2,
  const CATPointOnEdgeCurve *iStart1,
  const CATPointOnEdgeCurve *iEnd1,
  const CATPointOnEdgeCurve *iStart2,
  const CATPointOnEdgeCurve *iEnd2);

#endif /* CATIPGMIntersectionPCrvPCrv_h_ */
