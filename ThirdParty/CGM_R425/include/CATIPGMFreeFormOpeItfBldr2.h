#ifndef CATIPGMFreeFormOpeItfBldr2_h
#define CATIPGMFreeFormOpeItfBldr2_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATDataType.h"
#include "CATSkillValue.h"
#include "CATCollec.h"
#include "CATTopDefine.h"
#include "CATMathDef.h"
#include "CATFrFExtrapolNurbsSur.h" // CATSurfaceSide
#include "CATFrFExtrapolNurbsCrv.h" // CATCurveSide

class CATCrvParametricExtend;
class CATCrvVertexSmoothing;
class CATMathMxNFullMatrix;
class CATFillSurface;
class CATFrFNurbsMultiForm;
class CATFrFCompositeCurveMapping;
class CATMovingFrameStruct;
class CATFrFCoupling;
class CATSurVertexSmoothing;
class CATFitting;
class CATMathSetOfPointsNDTwoTangents;
class CATFrFIntersectionCCvCCv;
class CATGeometricMatchSurface;
class CATGlobalDeformation;
class CATMathAxis;
class CATGeometry;
class CATInterpolPtToPNurbs;
class CATSegmentation;
class CATCrvVertexG2Modification;
class CATSurParametricExtend;
class CATFrFNurbsBipar;
class CATMathPolynomX;
class CATKnotVector;
class CATFrFCombMF;
class CATFrFCCvLimits;
class CATMathGridOfVectors;
class CATInterpolPtToNurbsCrv;
class CATMatchCurve;
class CATPoint;
class CATPNurbs;
class CATCurve;
class CATCrvLimits;
class CATFrFCompositeCurve;
class CATMathDirection;
class CATPLine;
class CATMathSetOfPointsND;
class CATSurface;
class CATPCurve;
class CATPointOnCurve;
class CATCGMStream;
class CATIPGMFrFMovingFrame;
class CATCurveGContinuity;
class CATMathFunctionX;
class CATPGMExtruder;
class CATIPGMFrFSimilarCurve;
class CATConnectSmooth;
class CATIPGMFrFObject;
class CATIPGMFrFCoupling;
class CATTolerance;
class CATIPGMFrFCheckGeometricContinuity;
class CATIPGMFrFSmoothingOper;
class CATICGMFrFSmoothingOper;
class CATCldScan;
class CATSurVertexG2Modification;
class CATLISTP(CATCrvLimits);
class CATLISTP(CATPCurve);
class CATLISTP(CATSurface);
class CATLISTP(CATCurve);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFreeFormOpeItfBldr2;

/**
 * Factory of implementations of CGM interfaces for the framework FreeFormOperators.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMFreeFormOpeItfBldr2: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATCrvParametricExtend *CATPGMCreateCrvParametricExtend(
    CATNurbsCurve *iNurbsCrv,
    const CATCrvParam &iCrvParam,
    const double &iExtendRatio,
    CATSkillValue iMode) = 0;

  virtual CATCrvParametricExtend *CATPGMCreateCrvParametricExtend(
    CATSoftwareConfiguration *iSoft,
    CATNurbsCurve *iNurbsCrv,
    const CATCrvParam &iCrvParam,
    const double &iExtendRatio,
    CATSkillValue iMode) = 0;

  virtual CATCrvVertexSmoothing *CATPGMCreateCrvVertexSmoothing(
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATPNurbs *iPNurbs,
    double smooth,
    CATMathMxNFullMatrix *iTargetPoints) = 0;

  virtual CATCrvVertexSmoothing *CATPGMCreateCrvVertexSmoothing(
    CATPNurbs *iPNurbs,
    double smooth,
    CATMathMxNFullMatrix *iTargetPoints,
    CATSkillValue iMode) = 0;

  virtual CATCrvVertexSmoothing *CATPGMCreateCrvVertexSmoothing(
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATNurbsCurve *iNurbsCurve,
    double smooth,
    CATMathMxNFullMatrix *iTargetPoints) = 0;

  virtual CATCrvVertexSmoothing *CATPGMCreateCrvVertexSmoothing(
    CATNurbsCurve *iNurbsCurve,
    double smooth,
    CATMathMxNFullMatrix *iTargetPoints,
    CATSkillValue iMode) = 0;

  virtual CATFillSurface *CATPGMCreateFillSurface(
    CATGeoFactory *ifactory,
    const CATLONG32 inumberofcurves,
    const CATCurve **itabofcurve,
    CATCrvLimits *itabofcrvlimits,
    CATLONG32 iNbOfMultiForms,
    const CATFrFNurbsMultiForm **iMultiForm,
    CATLONG32 *iTransitioncontMultiForm,
    CATSkillValue iMode) = 0;

  virtual CATFillSurface *CATPGMCreateFillSurface(
    CATGeoFactory *ifactory,
    const CATLONG32 inumberofcurves,
    const CATCurve **itabofcurve,
    CATCrvLimits *itabofcrvlimits,
    CATSkillValue iMode) = 0;

  virtual void CATCGMRemove(CATFrFCompositeCurveMapping *&ioCompositeCurveMapping) = 0; // Useful

  virtual CATFrFIntersectionCCvCCv *CATPGMCreateFrFIntersectionCCvCCv(
    CATGeoFactory *iFactory,
    CATFrFCompositeCurve *iCCv1,
    CATFrFCompositeCurve *iCCv2,
    CATSkillValue iMode,
    const CATSoftwareConfiguration *iConfig) = 0;

  virtual CATGeometricMatchSurface *CATPGMCreateGeometricMatchSurface(
    CATSoftwareConfiguration *iConfig,
    CATGeoFactory *iFactory,
    const CATPLine *iFrontiere,
    const CATFrFCompositeCurve *iCompCurve2,
    CATSkillValue iMode) = 0;

  virtual CATGeometricMatchSurface *CATPGMCreateGeometricMatchSurface(
    CATGeoFactory *iFactory,
    const CATPLine *iFrontiere,
    const CATFrFCompositeCurve *iCompCurve2,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *iFactory,
    CATNurbsCurve *iStartParametrisationSpine,
    CATNurbsCurve *iStartProjDirectionCrv,
    const CATLONG32 iNbOfReferenceCrv,
    CATNurbsCurve **iStartReferenceCrv,
    CATNurbsCurve *iTargetParametrisationSpine,
    CATNurbsCurve *iTargetProjDirectionCrv,
    CATNurbsCurve **iTargetReferenceCrv,
    const CATLONG32 iNbOfAdjustmentSurfaces,
    CATNurbsSurface **iAdjustmentSurfaces,
    const CATLONG32 iNbOfGeometricObjectsToDeform,
    CATNurbsSurface **iGeometricObjectsToDeform,
    const CATLONG32 iConstraintOnGuide,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *iFactory,
    CATNurbsCurve *iStartParametrisationSpine,
    CATNurbsCurve *iStartProjDirectionCrv,
    const CATLONG32 iNbOfReferenceCrv,
    CATNurbsCurve **iStartReferenceCrv,
    CATNurbsCurve *iTargetParametrisationSpine,
    CATNurbsCurve *iTargetProjDirectionCrv,
    CATNurbsCurve **iTargetReferenceCrv,
    const CATLONG32 iNbOfAdjustmentSurfaces,
    CATNurbsSurface **iAdjustmentSurfaces,
    const CATLONG32 iNbOfGeometricObjectsToDeform,
    CATNurbsSurface **iGeometricObjectsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *iFactory,
    CATNurbsCurve *iStartParametrisationSpine,
    CATNurbsCurve *iStartProjDirectionCrv,
    const CATLONG32 iNbOfReferenceCrv,
    CATNurbsCurve **iStartReferenceCrv,
    CATNurbsCurve *iTargetParametrisationSpine,
    CATNurbsCurve *iTargetProjDirectionCrv,
    CATNurbsCurve **iTargetReferenceCrv,
    const CATLONG32 iNbOfGeometricObjectsToDeform,
    CATNurbsSurface **iGeometricObjectsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsCurve *iStartParametrisationSpineCurve,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsCurve *iTargetParametrisationSpineCurve,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATNurbsSurface **iGeometricElementsToDeform,
    const CATLONG32 iConstraintOnGuide,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsCurve *iStartParametrisationSpineCurve,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsCurve *iTargetParametrisationSpineCurve,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATNurbsSurface **iGeometricElementsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsCurve *iStartParametrisationSpineCurve,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsCurve *iTargetParametrisationSpineCurve,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATNurbsSurface **iGeometricElementsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATNurbsSurface **iGeometricElementsToDeform,
    const CATLONG32 iConstraintOnGuide,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATNurbsSurface **iGeometricElementsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATNurbsSurface **iGeometricElementsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATMathAxis *iStartAxis,
    CATMathAxis *iTargetAxis,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToMove,
    CATNurbsSurface **iGeometricElementsToMove,
    const CATLONG32 iConstraintOnGuide,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATMathAxis *iStartAxis,
    CATMathAxis *iTargetAxis,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToMove,
    CATNurbsSurface **iGeometricElementsToMove,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATMathAxis *iStartAxis,
    CATMathAxis *iTargetAxis,
    const CATLONG32 iNbOfGeometricElementsToMove,
    CATNurbsSurface **iGeometricElementsToMove,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *iFactory,
    CATNurbsCurve *iStartParametrisationSpine,
    CATNurbsCurve *iStartProjDirectionCrv,
    const CATLONG32 iNbOfReferenceCrv,
    CATNurbsCurve **iStartReferenceCrv,
    CATNurbsCurve *iTargetParametrisationSpine,
    CATNurbsCurve *iTargetProjDirectionCrv,
    CATNurbsCurve **iTargetReferenceCrv,
    const CATLONG32 iNbOfAdjustmentSurfaces,
    CATNurbsSurface **iAdjustmentSurfaces,
    const CATLONG32 iNbOfGeometricObjectsToDeform,
    CATGeometry **iGeometricObjectsToDeform,
    const CATLONG32 iConstraintOnGuide,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *iFactory,
    CATNurbsCurve *iStartParametrisationSpine,
    CATNurbsCurve *iStartProjDirectionCrv,
    const CATLONG32 iNbOfReferenceCrv,
    CATNurbsCurve **iStartReferenceCrv,
    CATNurbsCurve *iTargetParametrisationSpine,
    CATNurbsCurve *iTargetProjDirectionCrv,
    CATNurbsCurve **iTargetReferenceCrv,
    const CATLONG32 iNbOfAdjustmentSurfaces,
    CATNurbsSurface **iAdjustmentSurfaces,
    const CATLONG32 iNbOfGeometricObjectsToDeform,
    CATGeometry **iGeometricObjectsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *iFactory,
    CATNurbsCurve *iStartParametrisationSpine,
    CATNurbsCurve *iStartProjDirectionCrv,
    const CATLONG32 iNbOfReferenceCrv,
    CATNurbsCurve **iStartReferenceCrv,
    CATNurbsCurve *iTargetParametrisationSpine,
    CATNurbsCurve *iTargetProjDirectionCrv,
    CATNurbsCurve **iTargetReferenceCrv,
    const CATLONG32 iNbOfGeometricObjectsToDeform,
    CATGeometry **iGeometricObjectsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsCurve *iStartParametrisationSpineCurve,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsCurve *iTargetParametrisationSpineCurve,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATGeometry **iGeometricElementsToDeform,
    const CATLONG32 iConstraintOnGuide,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsCurve *iStartParametrisationSpineCurve,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsCurve *iTargetParametrisationSpineCurve,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATGeometry **iGeometricElementsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsCurve *iStartParametrisationSpineCurve,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsCurve *iTargetParametrisationSpineCurve,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATGeometry **iGeometricElementsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATGeometry **iGeometricElementsToDeform,
    const CATLONG32 iConstraintOnGuide,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATGeometry **iGeometricElementsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATNurbsSurface *iStartParametrisationSurface,
    CATNurbsSurface *iTargetParametrisationSurface,
    const CATLONG32 iNbOfGeometricElementsToDeform,
    CATGeometry **iGeometricElementsToDeform,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATMathAxis *iStartAxis,
    CATMathAxis *iTargetAxis,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToMove,
    CATGeometry **iGeometricElementsToMove,
    const CATLONG32 iConstraintOnGuide,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATMathAxis *iStartAxis,
    CATMathAxis *iTargetAxis,
    const CATLONG32 iNbOfGuidingSurfaces,
    CATNurbsSurface **iGuidingSurfaces,
    const CATLONG32 iNbOfGeometricElementsToMove,
    CATGeometry **iGeometricElementsToMove,
    CATSkillValue iMode) = 0;

  virtual CATGlobalDeformation *CATPGMCreateGlobalDeformation(
    CATGeoFactory *ifactory,
    CATMathAxis *iStartAxis,
    CATMathAxis *iTargetAxis,
    const CATLONG32 iNbOfGeometricElementsToMove,
    CATGeometry **iGeometricElementsToMove,
    CATSkillValue iMode) = 0;

  virtual CATInterpolPtToPNurbs *CATPGMCreateInterpolPtToPNurbs(
    CATGeoFactory *iFactory,
    const CATMathSetOfPointsND *iPoints,
    const CATLONG32 &nvar0,
    const CATLONG32 &nvar1,
    const CATLONG32 &nvar2,
    CATSurface *iSupport,
    CATSkillValue iMode) = 0;

  virtual CATSegmentation *CATPGMCreateSegmentation(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATCurve *iCurve,
    double &Tolap,
    CATLONG32 &NbBreak,
    CATCrvParam *Wpar,
    CATSkillValue mode) = 0;

  virtual CATSegmentation *CATPGMCreateSegmentation(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATLISTP(CATCurve) &iListe,
    double &Tolap,
    CATSkillValue mode) = 0;

  virtual CATSegmentation *CATPGMCreateSegmentation(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATCurve *iCurve,
    double &Tolap,
    CATSkillValue mode) = 0;

  virtual CATSegmentation *CATPGMCreateSegmentation(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATCurve *iCurve,
    CATLONG32 NbSeg,
    CATLONG32 &NbBreak,
    CATCrvParam *Wpar,
    CATSkillValue mode) = 0;

  virtual CATSegmentation *CATPGMCreateSegmentation(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATLISTP(CATCurve) &iListe,
    CATLONG32 NbSeg,
    CATSkillValue mode) = 0;

  virtual CATSegmentation *CATPGMCreateSegmentation(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATCurve *iCurve,
    CATLONG32 NbSeg,
    CATSkillValue mode) = 0;

  virtual CATSurParametricExtend *CATPGMCreateSurParametricExtend(
    CATNurbsSurface *iNurbsSur,
    const CATSurParam &iSurParam,
    const double &iExtendRatio,
    CATSkillValue iMode) = 0;

  virtual CATSurParametricExtend *CATPGMCreateSurParametricExtend(
    CATSoftwareConfiguration *iSoft,
    CATNurbsSurface *iNurbsSur,
    const CATSurParam &iSurParam,
    const double &iExtendRatio,
    CATSkillValue iMode) = 0;

  virtual CATFrFNurbsBipar *CATPGMMakeNurbsSurfaceClamped(
    const CATLONG32 iOrderU,
    const CATLONG32 iKnotSizeU,
    double *iExtendedKnotVectorU,
    const CATLONG32 iOrderV,
    const CATLONG32 iKnotSizeV,
    double *iExtendedKnotVectorV,
    const CATLONG32 iIsRational,
    const CATLONG32 iIsPeriodic,
    CATLONG32 iNumberOfPoleU,
    CATLONG32 iNumberOfPoleV,
    double *iPole,
    double *iWeight,
    const double iTolEqualKnots) = 0;

// DEPRECATED
  virtual CATFrFNurbsBipar *CATPGMMakeNurbsSurfaceClamped(
    CATGeoFactory            *  iFactory             ,
    CATSoftwareConfiguration *  iConfig              ,
    const CATLONG32 iOrderU,
    const CATLONG32 iKnotSizeU,
    double *iExtendedKnotVectorU,
    const CATLONG32 iOrderV,
    const CATLONG32 iKnotSizeV,
    double *iExtendedKnotVectorV,
    const CATLONG32 iIsRational,
    const CATLONG32 iIsPeriodic,
    CATLONG32 iNumberOfPoleU,
    CATLONG32 iNumberOfPoleV,
    double *iPole,
    double *iWeight,
    const double iTolEqualKnots) = 0;


  virtual CATFrFNurbsMultiForm *CATPGMMakeNurbsCurveClamped(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATLONG32 iOrder,
    const CATLONG32 iKnotSize,
    double *iExtendedKnotVector,
    const CATLONG32 iDim,
    const CATLONG32 iIsRational,
    const CATLONG32 IsPeriodic,
    const CATLONG32 iNumberOfForm,
    const CATLONG32 iNumberOfPole,
    double *iPole,
    double *iWeight,
    const double iTolEqualKnots) = 0;

// DEPRECATED
  virtual CATFrFNurbsMultiForm *CATPGMMakeNurbsCurveClamped(
    const CATLONG32 iOrder,
    const CATLONG32 iKnotSize,
    double *iExtendedKnotVector,
    const CATLONG32 iDim,
    const CATLONG32 iIsRational,
    const CATLONG32 IsPeriodic,
    const CATLONG32 iNumberOfForm,
    const CATLONG32 iNumberOfPole,
    double *iPole,
    double *iWeight,
    const double iTolEqualKnots) = 0;


  virtual CATSurVertexG2Modification *CATCGMCreateSurVertexG2Modification(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration* iSoftwareConfiguration,
    CATNurbsSurface *ioNurbsSurface,
    CATLONG32 borderU1,
    CATLONG32 borderU2,
    CATLONG32 borderV1,
    CATLONG32 borderV2,
    const CATMathGridOfVectors *iMovingField,
    CATSkillValue iMode) = 0;

  virtual CATInterpolPtToNurbsCrv *CATPGMCreateInterpolPtToNurbsCrv(
    CATGeoFactory *iFactory,
    const CATMathSetOfPointsND *iPoints,
    const CATLONG32 &nvar0,
    const CATLONG32 &nvar1,
    const CATLONG32 &nvar2,
    CATSkillValue iMode) = 0;

  virtual CATMatchCurve *CATPGMCreateMatchCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration* iSoftwareConfiguration,
    const CATPointOnCurve *iLimitPoint,
    const CATCurve *iCrvMatched,
    CATPoint *iRefPoint,
    CATSkillValue iMode) = 0;

  virtual CATMatchCurve *CATPGMCreateMatchCurve(
    CATGeoFactory *iFactory,
    const CATPointOnCurve *iLimitPoint,
    const CATCurve *iCrvMatched,
    CATPoint *iRefPoint,
    CATSkillValue iMode) = 0;

  virtual CATMatchCurve *CATPGMCreateMatchCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration* iSoftwareConfiguration,
    const CATPointOnCurve *iLimitPoint,
    const CATCurve *iCrvMatched,
    const CATCurve *iCrvRef,
    const CATCrvParam &iParamPtRef,
    CATSkillValue iMode) = 0;

  virtual CATMatchCurve *CATPGMCreateMatchCurve(
    CATGeoFactory *iFactory,
    const CATPointOnCurve *iLimitPoint,
    const CATCurve *iCrvMatched,
    const CATCurve *iCrvRef,
    const CATCrvParam &iParamPtRef,
    CATSkillValue iMode) = 0;

  virtual CATIPGMFrFMovingFrame *CATPGMCreateMovingFrame(
    CATIPGMFrFMovingFrame *iToCopy,
    CATBoolean iCopyMapping) = 0;

  virtual void CATCGMGetFreeFormOperatorsSharedlib(char *&sharedlib) = 0;

  virtual CATCurveGContinuity *CATCGMCreateCurveGContinuity(
    CATGeoFactory *iFactory,
    const CATLISTP(CATCurve) &iCurvesToImprove,
    const CATListOfInt &iSens,
    const CATLISTP(CATCrvLimits) &iLimits,
    CATSoftwareConfiguration *iSoftConfig) = 0;

  virtual CATCurveGContinuity *CATCGMCreateCurveGContinuity(
    CATGeoFactory *iFactory,
    CATFrFCompositeCurve *iCCV,
    CATSoftwareConfiguration *iSoftConfig) = 0;

  virtual CATMathFunctionX *CATPGMCreateLawEquationDistPCrvPCrv(
    CATSoftwareConfiguration *iConfig,
    CATPCurve *iPCrv1,
    CATPCurve *iPCrv2,
    CATPCurve *iPCrvRef,
    const CATCrvParam &iPCrv1Start,
    const CATCrvParam &iPCrv1End,
    const CATCrvParam &iPCrv2Start,
    const CATCrvParam &iPCrv2End,
    const CATCrvParam &iPCrvRefStart,
    const CATCrvParam &iPCrvRefEnd,
    const double iLambdaStart,
    const double iLambdaEnd,
    const short iOrientationFlag,
    const CATTolerance & iTolObject) = 0;

  virtual CATMathFunctionX *CATPGMCreateLawEquationDistPCrvPCrv(
    CATSoftwareConfiguration *iConfig,
    CATPCurve *iPCrvBase,
    CATPCurve *iPCrvInf,
    CATPCurve *iPCrvSup,
    CATPCurve *iPCrvRef,
    const CATCrvParam &iPCrvBaseStart,
    const CATCrvParam &iPCrvBaseEnd,
    const CATCrvParam &iPCrvInfStart,
    const CATCrvParam &iPCrvInfEnd,
    const CATCrvParam &iPCrvSupStart,
    const CATCrvParam &iPCrvSupEnd,
    const CATCrvParam &iPCrvRefStart,
    const CATCrvParam &iPCrvRefEnd,
    const double iLambdaStart,
    const double iLambdaEnd,
    const short iOrientationFlag,
    const CATTolerance & iTolObject) = 0;

  virtual CATPGMExtruder *CATPGMCreateExtruderByCircle(
    CATGeoFactory *iWhere,
    const CATMathAxis &iRef,
    CATSoftwareConfiguration *iSoftwareConfiguration) = 0;

  virtual CATPGMExtruder *CATPGMCreateExtruderByLine(
    CATGeoFactory *iWhere,
    const CATMathPoint &iRef,
    CATSoftwareConfiguration *iSoftwareConfiguration) = 0;

  virtual CATIPGMFrFSimilarCurve *CATPGMCreateFrFSimilarCurve(
    CATGeoFactory *iFactory,
    CATLISTP(CATCurve) &iListOfBaseCurves,
    CATLISTP(CATCrvLimits) &iListLimitsOfBaseCurves,
    CATListOfInt &iListOrnOfBaseCurves,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    int iSimilar2D) = 0;

  virtual CATIPGMFrFSimilarCurve *CATPGMCreateFrFSimilarCurve(
    CATGeoFactory *iFactory,
    CATFrFNurbsMultiForm *iNurbsForSimilar,
    CATSoftwareConfiguration *iSoftwareConfiguration) = 0;

  virtual CATConnectSmooth *CreateSmoothPlaneDirCurve(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig) = 0;

  virtual CATIPGMFrFMovingFrame *CATPGMCreateParallelToPlaneMovingFrame(
    CATIPGMFrFObject &iFrFObject,
    const CATFrFCompositeCurve *iSpine,
    const CATMathDirection *iPlaneNormal,
    CATBoolean iComputeMapping) = 0;

  virtual CATIPGMFrFMovingFrame *CATPGMCreateOrthoMovingFrame(
    CATIPGMFrFObject &iFrFObject,
    const CATFrFCompositeCurve *iSpine,
    CATBoolean iComputeMapping) = 0;

  virtual CATIPGMFrFMovingFrame *CATPGMCreatePseudoOrthoMovingFrame(
    CATIPGMFrFObject &iFrFObject,
    const CATFrFCompositeCurve *iSpine,
    CATBoolean iComputeMapping) = 0;

  virtual CATIPGMFrFMovingFrame *CATPGMCreateOrthoCrvCrvMovingFrame(
    CATIPGMFrFObject &iFrFObject,
    const CATFrFCompositeCurve *iSpine,
    const CATIPGMFrFCoupling *iCoupling,
    CATBoolean iComputeMapping) = 0;

  virtual CATIPGMFrFMovingFrame *CATPGMCreatePseudoOrthoCrvCrvMovingFrame(
    CATIPGMFrFObject &iFrFObject,
    const CATFrFCompositeCurve *iSpine,
    const CATIPGMFrFCoupling *iCoupling,
    CATBoolean iComputeMapping) = 0;

  virtual CATIPGMFrFMovingFrame *CATPGMCreateMeanTangMovingFrame(
    CATIPGMFrFObject &iFrFObject,
    CATIPGMFrFCoupling *iCoupling) = 0;

  virtual CATIPGMFrFMovingFrame *CATPGMCreateMovingFrame(
    CATIPGMFrFObject &iFrFObject,
    const CATFrFCompositeCurve *iSpine,
    const CATMovingFrameStruct &iMFDef) = 0;

  virtual CATIPGMFrFMovingFrame *CATPGMCreateExtrapolShapeMovingFrame(
    CATIPGMFrFObject &iFrFObject,
    const CATFrFCompositeCurve *iSpine) = 0;

  virtual CATFrFCompositeCurveMapping *CATPGMCreatePreciseCompositeCurveMapping(
    const CATFrFCompositeCurve *iCompositeCurve) = 0;

  virtual CATFrFCompositeCurveMapping *CATPGMCreateDeprecatedUnpreciseCompositeCurveMapping(
    const CATFrFCompositeCurve *iCompositeCurve) = 0;

  virtual void CATCGMPrivRemove(CATFrFCompositeCurveMapping *&ioCompositeCurveMapping) = 0;

  virtual CATIPGMFrFCheckGeometricContinuity *CATPGMCreateFrFCheckGeometricContinuity(
    CATGeoFactory *iFactory,
    const CATCurve *C1,
    const CATCurve *C2,
    CATCrvLimits & CL1,
    CATCrvLimits & CL2,
    CATSoftwareConfiguration *iSoftwareConfiguration) = 0;

  virtual CATICGMFrFSmoothingOper *CATCGMFrFCreateSmoothingOper(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATMathSetOfPointsND *iPoints) = 0;

  virtual CATIPGMFrFSmoothingOper *CATPGMFrFCreateSmoothingOper(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATMathSetOfPointsND *iPoints) = 0;

  virtual CATIPGMFrFSmoothingOper *CATPGMFrFCreateSmoothingOper(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCldScan *iScan) = 0;

  virtual CATInterpolPtToNurbsCrv *CATPGMCreateInterpolPtToNurbsCrv(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathSetOfPointsND *iPoints,
    const CATLONG32 &nvar0,
    const CATLONG32 &nvar1,
    const CATLONG32 &nvar2,
    CATSkillValue iMode) = 0;

  virtual CATSurVertexSmoothing *CATPGMCreateSurVertexSmoothing(
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATNurbsSurface *iNurbsSurface,
    double iSmooth,
    CATLONG32 iBorderU1,
    CATLONG32 iBorderU2,
    CATLONG32 iBorderV1,
    CATLONG32 iBorderV2,
    CATMathMxNFullMatrix *iTargetPoints,
    CATSkillValue iMode) = 0;

  virtual CATIPGMFrFSimilarCurve *CATPGMCreateFrFSimilarCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATLISTP(CATCurve) &iListOfBaseCurves,
    CATLISTP(CATCrvLimits) &iListLimitsOfBaseCurves,
    CATListOfInt &iListOrnOfBaseCurves,
    int iSimilar2D) = 0;

  virtual CATIPGMFrFSimilarCurve *CATPGMCreateFrFSimilarCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATFrFNurbsMultiForm *iNurbsForSimilar) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework FreeFormOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFreeFormOpeItfBldr2 *CATCGMGetFreeFormOpeItfBldr2();

#endif /* CATIPGMFreeFormOpeItfBldr2_h */
