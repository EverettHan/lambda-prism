#ifndef CATIPGMFreeFormOpeItfBldr1_h
#define CATIPGMFreeFormOpeItfBldr1_h

//=============================================================================
// 31/10/18 NLD XScale: argument iTolObject à CATPGMCreateLawEquationDistCrv() et CATPGMCreateLawEquationDistLnCrvParamOnCrv()
//=============================================================================

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATDataType.h"
#include "CATSkillValue.h"
#include "CATCollec.h"
#include "CATTopDefine.h"
#include "CATMathDef.h"
#include "CATFrFExtrapolNurbsSur.h" // CATSurfaceSide
#include "CATFrFExtrapolNurbsCrv.h" // CATCurveSide
#include "CATTolerance.h"

class CATConvertSurToNurbsSur;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;
class CATICGMCrvFittingToNurbsCrv;
class CATIPGMCrvFittingToNurbsCrv;
class CATCurve;
class CATCrvLimits;
class CATCrvParam;
class CATICGMSurFittingToNurbsSur;
class CATIPGMSurFittingToNurbsSur;
class CATSurLimits;
class CATICGMInterproxCrv;
class CATIPGMInterproxCrv;
class CATMathSetOfPointsND;
class CATMathSetOfVectors;
class CATICGMInterproxSur;
class CATIPGMInterproxSur;
class CATMathDirection;
class CATICGMLiss;
class CATIPGMLiss;
class CATConvertCrvToNurbsCrv;
class CATICGMCrvDegreeModification;
class CATIPGMCrvDegreeModification;
class CATICGMSurDegreeModification;
class CATIPGMSurDegreeModification;
class CATNurbsSurface;
class CATFrFCompositeCurve;
class CATBody;
class CATEdge;
class CATEdgeCurve;
class CATPCurve;
class CATBreakSurface;
class CATPointOnSurface;
class CATIPGMConcatenationCurve;
class CATCurvesImprovement;
class CATEvalCrvSurf;
class CATMapParamCrvCrv;
class CATPGMFrFDistanceMaxCrvCrv;
class CATPGMFrFDistanceMinCcvCcv;
class CATPGMFrFDistanceMinPtCcv;
class CATMathPoint;
class CATGSDOptimizeSurf;
class CATMapFunctionXYZ; // Not interfaced for the moment
class CATGSDBase; // Not interfaced for the moment
class CATMathFunctionX;
class CATMathVector;
class CATPNurbs;
class CATNurbsCurve;
class CATFrFExtrapolNurbsCrv;
class CATFrFExtrapolNurbsSur;
class CATSurParam;
class CATFrFOffsetSur;
class CATAnalyticMatchSurface;
class CATPLine;
class CATPlane;
class CATLaw;
class CATBlendCurve;
class CATBreakCurve;
class CATPointOnCurve;
class CATCrvFittingToNupbsArc;
class CATCrvVertexG2Modification;
class CATLISTP(CATCrvLimits);
class CATLISTP(CATPCurve);
class CATLISTP(CATSurface);
class CATLISTP(CATCurve);
class CATIPGMFrFConversionServicesToSplines;
class CATTopData;
class CATIPGMFrFMultiSmoothOperator;
class CATSoftwareConfiguration;
class CATTolerance;
class CATMathSetOfPointsND; 

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFreeFormOpeItfBldr1;

/**
 * Factory of implementations of CGM interfaces for the framework FreeFormOperators.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMFreeFormOpeItfBldr1: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATConvertSurToNurbsSur *CATPGMCreateConvertSurToNurbsSur(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATSurface &iSurface) = 0;

  virtual CATICGMCrvFittingToNurbsCrv *CATCGMCreateCrvFittingToNurbsCrv(
    CATGeoFactory *iFactory,
    const CATCurve *iCurve,
    const CATCrvLimits &iLimits,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCrvFittingToNurbsCrv *CATPGMCreateCrvFittingToNurbsCrv(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATCurve *iCurve,
    const CATCrvLimits &iLimits,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCrvFittingToNurbsCrv *CATPGMCreateCrvFittingToNurbsCrv(
    CATGeoFactory *iFactory,
    const CATCurve *iCurve,
    const CATCrvLimits &iLimits,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual CATICGMSurFittingToNurbsSur *CATCGMCreateSurFittingToNurbsSur(
    CATGeoFactory *iFactory,
    const CATSurface *iSurface,
    const CATSurLimits &iLimits,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSurFittingToNurbsSur *CATPGMCreateSurFittingToNurbsSur(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATSurface *iSurface,
    const CATSurLimits &iLimits,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSurFittingToNurbsSur *CATPGMCreateSurFittingToNurbsSur(
    CATGeoFactory *iFactory,
    const CATSurface *iSurface,
    const CATSurLimits &iLimits,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual CATICGMInterproxCrv *CATCGMCreateInterproxCrv(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATLISTP(CATCurve) &iListe,
    const CATMathSetOfPointsND *iPoints,
    const CATMathSetOfVectors *iVectors,
    double &iTension,
    double &iSmoothness,
    double &iTolapp,
    const int iImposition[2],
    CATSkillValue iMode) = 0;

  virtual CATIPGMInterproxCrv *CATPGMCreateInterproxCrv(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATLISTP(CATCurve) &iListe,
    const CATMathSetOfPointsND *iPoints,
    const CATMathSetOfVectors *iVectors,
    double &iTension,
    double &iSmoothness,
    double &iTolapp,
    const int iImposition[2],
    CATSkillValue iMode) = 0;

  virtual CATICGMInterproxSur *CATCGMCreateInterproxSur(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATLISTP(CATSurface) &iListe,
    const CATMathSetOfPointsND *iPoints,
    const CATMathSetOfVectors *iVectors,
    double &iTension,
    double &iSmoothness,
    double &tolapp,
    const int *iImposition,
    const CATMathDirection *iVect,
    CATSkillValue iMode) = 0;

  virtual CATIPGMInterproxSur *CATPGMCreateInterproxSur(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATLISTP(CATSurface) &iListe,
    const CATMathSetOfPointsND *iPoints,
    const CATMathSetOfVectors *iVectors,
    double &iTension,
    double &iSmoothness,
    double &tolapp,
    const int *iImposition,
    const CATMathDirection *iVect,
    CATSkillValue iMode) = 0;

  virtual CATICGMLiss *CATCGMCreateLiss(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATMathSetOfPointsND *iPoints,
    double &iTol,
    CATSkillValue iMode) = 0;

  virtual CATIPGMLiss *CATPGMCreateLiss(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATMathSetOfPointsND *iPoints,
    double &iTol,
    CATSkillValue iMode) = 0;

  virtual CATConvertCrvToNurbsCrv *CATPGMCreateConvertCrvToNurbsCrv(
    CATGeoFactory *iFactory,
    const CATCurve &iCurve,
    CATSkillValue iMode) = 0;

  virtual CATConvertSurToNurbsSur *CATPGMCreateConvertSurToNurbsSur(
    CATGeoFactory *iFactory,
    const CATSurface &iSurface,
    CATSkillValue iMode) = 0;

  virtual CATICGMCrvDegreeModification *CATCGMCreateCrvDegreeModification(
    CATGeoFactory *iFactory,
    CATCurve *iNurbsCurve,
    const CATLONG32 iTargetDegree,
    const double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATICGMCrvDegreeModification *CATCGMCreateCrvDegreeModification(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration* iConfig,
    CATCurve *iNurbsCurve,
    const CATLONG32 iTargetDegree,
    const double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATICGMCrvDegreeModification *CATCGMCreateCrvDegreeModification(
    CATGeoFactory *iFactory,
    CATCurve *iNurbsCurve,
    const CATLONG32 &iNewDegree,
    CATSkillValue iMode) = 0;

  virtual CATICGMCrvDegreeModification *CATCGMCreateCrvDegreeModification(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration* iConfig,
    CATCurve *iNurbsCurve,
    const CATLONG32 &iNewDegree,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCrvDegreeModification *CATPGMCreateCrvDegreeModification(
    CATGeoFactory *iFactory,
    CATCurve *iNurbsCurve,
    const CATLONG32 iTargetDegree,
    const double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCrvDegreeModification *CATPGMCreateCrvDegreeModification(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration* iConfig,
    CATCurve *iNurbsCurve,
    const CATLONG32 iTargetDegree,
    const double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCrvDegreeModification *CATPGMCreateCrvDegreeModification(
    CATGeoFactory *iFactory,
    CATCurve *iNurbsCurve,
    const CATLONG32 &iNewDegree,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCrvDegreeModification *CATPGMCreateCrvDegreeModification(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration* iConfig,
    CATCurve *iNurbsCurve,
    const CATLONG32 &iNewDegree,
    CATSkillValue iMode) = 0;

  virtual CATICGMCrvFittingToNurbsCrv *CATCGMCreateCrvFittingToNurbsCrv(
    CATGeoFactory *iFactory,
    const CATCurve &iCurve,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual CATIPGMCrvFittingToNurbsCrv *CATPGMCreateCrvFittingToNurbsCrv(
    CATGeoFactory *iFactory,
    const CATCurve &iCurve,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual CATIPGMInterproxCrv *CATPGMCreateInterproxCrv(
    CATGeoFactory *iFactory,
    CATLISTP(CATCurve) &iListe,
    const CATMathSetOfPointsND *iPoints,
    const CATMathSetOfVectors *iVectors,
    double &iTension,
    double &iSmoothness,
    double &iTolapp,
    const int iImposition[2],
    CATSkillValue iMode) = 0;

  virtual CATIPGMInterproxSur *CATPGMCreateInterproxSur(
    CATGeoFactory *iFactory,
    CATLISTP(CATSurface) &iListe,
    const CATMathSetOfPointsND *iPoints,
    const CATMathSetOfVectors *iVectors,
    double &iTension,
    double &iSmoothness,
    double &tolapp,
    const int *iImposition,
    const CATMathDirection *iVect,
    CATSkillValue iMode) = 0;

  virtual CATIPGMLiss *CATPGMCreateLiss(
    CATGeoFactory *iFactory,
    CATMathSetOfPointsND *iPoints,
    double &iTol,
    CATSkillValue iMode) = 0;

  virtual CATICGMSurDegreeModification *CATCGMCreateSurDegreeModification(
    CATGeoFactory *ifactory,
    CATNurbsSurface *iNurbsSurface,
    const CATLONG32 &iTargetDegreeU,
    const CATLONG32 &iTargetDegreeV,
    const double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATICGMSurDegreeModification *CATCGMCreateSurDegreeModification(
    CATGeoFactory *ifactory,
    CATSoftwareConfiguration* iConfig,
    CATNurbsSurface *iNurbsSurface,
    const CATLONG32 &iTargetDegreeU,
    const CATLONG32 &iTargetDegreeV,
    const double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATICGMSurDegreeModification *CATCGMCreateSurDegreeModification(
    CATGeoFactory *iFactory,
    CATNurbsSurface *iNurbsSurface,
    const CATLONG32 &iNewDegreeU,
    const CATLONG32 &iNewDegreeV,
    CATSkillValue iMode) = 0;

  virtual CATICGMSurDegreeModification *CATCGMCreateSurDegreeModification(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration* iConfig,
    CATNurbsSurface *iNurbsSurface,
    const CATLONG32 &iNewDegreeU,
    const CATLONG32 &iNewDegreeV,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSurDegreeModification *CATPGMCreateSurDegreeModification(
    CATGeoFactory *ifactory,
    CATNurbsSurface *iNurbsSurface,
    const CATLONG32 &iTargetDegreeU,
    const CATLONG32 &iTargetDegreeV,
    const double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSurDegreeModification *CATPGMCreateSurDegreeModification(
    CATGeoFactory *ifactory,
    CATSoftwareConfiguration* iConfig,
    CATNurbsSurface *iNurbsSurface,
    const CATLONG32 &iTargetDegreeU,
    const CATLONG32 &iTargetDegreeV,
    const double iTolerance,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSurDegreeModification *CATPGMCreateSurDegreeModification(
    CATGeoFactory *iFactory,
    CATNurbsSurface *iNurbsSurface,
    const CATLONG32 &iNewDegreeU,
    const CATLONG32 &iNewDegreeV,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSurDegreeModification *CATPGMCreateSurDegreeModification(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration* iConfig,
    CATNurbsSurface *iNurbsSurface,
    const CATLONG32 &iNewDegreeU,
    const CATLONG32 &iNewDegreeV,
    CATSkillValue iMode) = 0;

  virtual CATICGMSurFittingToNurbsSur *CATCGMCreateSurFittingToNurbsSur(
    CATGeoFactory *iFactory,
    const CATSurface &iSurface,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual CATIPGMSurFittingToNurbsSur *CATPGMCreateSurFittingToNurbsSur(
    CATGeoFactory *iFactory,
    const CATSurface &iSurface,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual void CATCGMRemove(CATFrFCompositeCurve *&ioCompositeCurve) = 0;

  virtual void CATCGMCreateCompositeCurve_Streamable(
    CATFrFCompositeCurve *iCcv,
    CATFrFCompositeCurve *&oCcv,
    CATListOfInt *oListOfIndexNewCrv) = 0;

  virtual void CATCGMCreateCompositeCurve_InvertCcv(
    CATFrFCompositeCurve *iCcv,
    CATFrFCompositeCurve *&oCcv) = 0;

  virtual void CATCGMCreateCompositeCurve_PackCcv(
    CATFrFCompositeCurve *iCcv,
    CATFrFCompositeCurve *&oCcv,
    CATListOfInt *oListOfIndexPackcrv) = 0;

  virtual CATFrFCompositeCurve *CATCGMCreateCompositeCurve(const CATFrFCompositeCurve *iToCopy) = 0;

  virtual CATFrFCompositeCurve *CATCGMCreateConnexCompositeCurve(
    const CATBody *iWire,
    double iResolution,
    CATLONG32 iStartIndex,
    CATLONG32 iEndIndex) = 0;

  virtual CATFrFCompositeCurve *CATCGMCreateCompositeCurve(
    const CATEdge **iEdgeList,
    const CATOrientation *iListOfOrien,
    CATLONG32 iNbOfEdgeCur) = 0;

  virtual CATFrFCompositeCurve *CATCGMCreateCompositeCurve(
    const CATBody *iWire,
    CATEdge **&oEdgeList,
    CATLONG32 iStartIndex,
    CATLONG32 iEndIndex) = 0;

  virtual CATFrFCompositeCurve *CATCGMCreateCompositeCurve(
    const CATBody *iWire,
    CATLONG32 iStartIndex,
    CATLONG32 iEndIndex) = 0;

  virtual CATFrFCompositeCurve *CATCGMCreateCompositeCurve(CATCurve *iCurve) = 0;

  virtual CATFrFCompositeCurve *CATCGMCreateCompositeCurve(
    CATCurve *iCurve,
    const CATCrvLimits &iCrvLimits) = 0;

  virtual CATFrFCompositeCurve *CATCGMCreateCompositeCurve(
    CATLONG32 iNumberOfCurves,
    CATCrvLimits *iCrvLimits,
    CATLONG32 *iCrvOrientation,
    CATLONG32 *iSupportOrientation,
    CATEdgeCurve **iMergedCurves,
    CATCurve **iCurves,
    CATPCurve **iPCurves) = 0;

  virtual CATFrFCompositeCurve *CATCGMCreateCompositeCurve(
    CATLONG32 iNumberOfCurves,
    CATCurve **iCurves) = 0;

  virtual CATFrFCompositeCurve *CATCGMCreateCompositeCurve(
    CATLONG32 iNumberOfCurves,
    CATCurve **iCurves,
    CATCrvLimits *iCrvLimits,
    CATLONG32 *iCrvOrientation,
    CATLONG32 *iSupportOrientation) = 0;

  virtual CATBreakSurface *CATPGMCreateBreakSurface(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATLISTP(CATPCurve) &iListe,
    CATSkillValue iMode) = 0;

  virtual CATBreakSurface *CATPGMCreateBreakSurface(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATPointOnSurface *iPtBreak,
    CATSkillValue iMode) = 0;

  virtual CATBreakSurface *CATPGMCreateBreakSurface(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATPCurve *iCurve,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConcatenationCurve *CATPGMCreateConcatenationCurve(
    CATGeoFactory *iFactory,
    const CATLISTP(CATCurve) &iListOfCurve,
    const CATLISTP(CATCrvLimits) &iListOfLimits,
    const CATListOfInt & iListOfOrient) = 0;

  virtual CATCurvesImprovement *CATPGMCreateCurvesImprovement(
    CATGeoFactory *iFactory,
    const CATLISTP(CATCurve) *iCurvesToImprove,
    const CATLISTP(CATCrvLimits) *iListOfLimits,
    const CATListOfInt *iListOfOrientations) = 0;

  virtual CATCurvesImprovement *CATPGMCreateCurvesImprovement(
    CATSoftwareConfiguration *iSoftwareConfiguration,
    CATGeoFactory *iFactory,
    const CATLISTP(CATCurve) *iCurvesToImprove,
    const CATLISTP(CATCrvLimits) *iListOfLimits,
    const CATListOfInt *iListOfOrientations) = 0;

  virtual CATEvalCrvSurf *CATPGMCreateCATEvalCrvSurf(
    const CATCurve *iSpine,
    const CATCurve *iProfile,
    double iSpineParamWhereToAnalyzeProfile) = 0;

  virtual CATEvalCrvSurf *CATPGMCreateCATEvalCrvSurf(const CATCurve *iProfile) = 0;

  virtual CATMapParamCrvCrv *CATPGMCreateCATMapParamCrvCrv(
    const CATCurve *iCRVU,
    const CATCurve *iCRVV) = 0;

  virtual CATMapParamCrvCrv *CATPGMCreateCATMapParamCrvCrv(
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATCurve *iCRVU,
    const CATCurve *iCRVV) = 0;

  virtual CATPGMFrFDistanceMaxCrvCrv *CATPGMCreateFrFDistanceMaxCrvCrv(
    CATGeoFactory *iFactory,
    const CATCurve *CRef,
    const CATCurve *C2,
    const CATCrvLimits &CLRef,
    const CATCrvLimits &CL2,
    const CATSkillValue &iMode,
    CATSoftwareConfiguration *iSoftwareConfiguration) = 0;

  virtual CATPGMFrFDistanceMinCcvCcv *CATPGMCreateFrFDistanceMinCcvCcv(
    CATGeoFactory *factory,
    CATFrFCompositeCurve *CCV1,
    CATFrFCompositeCurve *CCV2,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATPGMFrFDistanceMinPtCcv *CATPGMCreateFrFDistanceMinPtCcv(
    CATGeoFactory *iFactory,
    CATFrFCompositeCurve *iCcv,
    const CATMathPoint &iPoint) = 0;

  virtual CATPGMFrFDistanceMinPtCcv *CATPGMCreateDistanceMin(
    CATGeoFactory *iWhere,
    const CATMathPoint &iPt,
    CATFrFCompositeCurve *iCcv,
    CATSkillValue iMode) = 0;

  virtual void CATPGMComputeDistanceMinPtCcv(
    CATGeoFactory *iFactory,
    CATFrFCompositeCurve *iCcv,
    const CATMathPoint &iPoint,
    CATLONG32 &oCrvIndex,
    CATCrvParam &oCrvParam) = 0;

  virtual CATGSDOptimizeSurf *CATPGMCreateCATGSDOptimizeSurf(
    CATSoftwareConfiguration *iSoftConf,
    CATMapFunctionXYZ *iMap,
    const double iTolPt,
    const double iTolNormal,
    const CATLONG32 iMaxDeg) = 0;

  virtual CATGSDOptimizeSurf *CATPGMCreateCATGSDOptimizeSurf(
    CATSoftwareConfiguration *iSoftConf,
    CATGSDBase *iAnaOpe,
    const CATLONG32 iNbSynOpe,
    CATGSDBase **iSynOpe,
    const CATLONG32 iIndSynOpe,
    const double iTolPt,
    const double iTolNormal,
    const CATLONG32 iMaxDeg) = 0;

  virtual CATGSDOptimizeSurf *CATPGMCreateCATGSDOptimizeSurf(
    CATSoftwareConfiguration *iSoftConf,
    const CATLONG32 iMaxDeg,
    const double iTolPt,
    const double iTolNormal) = 0;

  virtual CATGSDOptimizeSurf *CATPGMCreateCATGSDOptimizeSurf(
    CATMapFunctionXYZ *iMap,
    const double iTolPt,
    const double iTolNormal,
    const CATLONG32 iMaxDeg) = 0;

  virtual CATGSDOptimizeSurf *CATPGMCreateCATGSDOptimizeSurf(
    CATGSDBase *iAnaOpe,
    const CATLONG32 iNbSynOpe,
    CATGSDBase **iSynOpe,
    const CATLONG32 iIndSynOpe,
    const double iTolPt,
    const double iTolNormal,
    const CATLONG32 iMaxDeg) = 0;

  virtual CATGSDOptimizeSurf *CATPGMCreateCATGSDOptimizeSurf(
    const CATLONG32 iMaxDeg,
    const double iTolPt,
    const double iTolNormal) = 0;

  virtual CATMathFunctionX *CATPGMCreateLawEquationDistCrv(
    CATSoftwareConfiguration *iConfig,
    double StartParamLine,
    double EndParamLine,
    const CATMathPoint &StartPointLine,
    const CATMathVector &DirectionLine,
    CATPositiveLength LengthRef,
    const CATMathVector &NormalLine,
    CATCurve *Curve,
    const CATCrvParam &ParamStartCurve,
    const CATCrvParam &ParamEndCurve,
    const CATTolerance & iTolObject) = 0;

  virtual CATMathFunctionX *CATPGMCreateLawEquationDistCrv(
    CATSoftwareConfiguration *iConfig,
    double StartParamLine,
    double EndParamLine,
    const CATMathPoint &StartPointLine,
    const CATMathVector &DirectionLine,
    CATPositiveLength LengthRef,
    CATCurve *Curve,
    const CATCrvParam &ParamStartCurve,
    const CATCrvParam &ParamEndCurve,
    const CATTolerance & iTolObject) = 0;

  virtual CATMathFunctionX *CATPGMCreateLawEquationDistLnCrvParamOnCrv(
    CATSoftwareConfiguration *iConfig,
    double wStart,
    double wEnd,
    const CATMathPoint &StartPointLine,
    const CATMathVector &DirectionLine,
    CATPositiveLength LengthRef,
    const CATMathVector &NormalLine,
    CATCurve *Curve,
    const CATCrvParam &ParamStartCurve,
    const CATCrvParam &ParamEndCurve,
    const CATTolerance & iTolObject) = 0;

  virtual CATMathFunctionX *CATPGMCreateLawEquationDistLnCrvParamOnCrv(
    CATSoftwareConfiguration *iConfig,
    double wStart,
    double wEnd,
    const CATMathPoint &StartPointLine,
    const CATMathVector &DirectionLine,
    CATPositiveLength LengthRef,
    CATCurve *Curve,
    const CATCrvParam &ParamStartCurve,
    const CATCrvParam &ParamEndCurve,
    const CATTolerance & iTolObject) = 0;

  virtual CATCrvVertexG2Modification *CATPGMCreateCrvVertexG2Modification(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATPNurbs *ioPNurbs,
    CATLONG32 Start,
    CATLONG32 End,
    const CATMathSetOfVectors *iMovingField,
    CATSkillValue iMode) = 0;

  virtual CATCrvVertexG2Modification *CATPGMCreateCrvVertexG2Modification(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATNurbsCurve *ioNurbsCurve,
    CATLONG32 Start,
    CATLONG32 End,
    const CATMathSetOfVectors *iMovingField,
    CATSkillValue iMode) = 0;

  virtual CATFrFExtrapolNurbsCrv *CATPGMCreateFrFExtrapolNurbsCrv(
    CATGeoFactory *iFactory,
    CATNurbsCurve *ioCrv,
    CATCrvParam *iStartParam,
    const CATCurveSide iCurveSide,
    const double iEstimatedMaxLength) = 0;

  virtual CATFrFExtrapolNurbsCrv *CATPGMCreateFrFExtrapolNurbsCrv(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATNurbsCurve *ioCrv,
    CATCrvParam *iStartParam,
    const CATCurveSide iCurveSide,
    const double iEstimatedMaxLength) = 0;

  virtual CATFrFExtrapolNurbsSur *CATPGMCreateFrFExtrapolNurbsSur(
    CATGeoFactory *iFactory,
    CATNurbsSurface *ioSur,
    CATSurParam *iStartParam,
    const CATSurfaceSide iSurfaceSide,
    const double iEstimatedMaxLength) = 0;

  virtual CATFrFExtrapolNurbsSur *CATPGMCreateFrFExtrapolNurbsSur(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATNurbsSurface *ioSur,
    CATSurParam *iStartParam,
    const CATSurfaceSide iSurfaceSide,
    const double iEstimatedMaxLength) = 0;

  virtual CATFrFOffsetSur *CATPGMCreateFrFOffsetSur(
    CATGeoFactory *Factory,
    const CATSurface *iSurface,
    const double iOffsetLaw[],
    const double iTol,
    const CATLONG32 iKeepKnots,
    CATSkillValue iMode) = 0;

  virtual CATFrFOffsetSur *CATPGMCreateFrFOffsetSur(
    CATGeoFactory *Factory,
    const CATSurface *iSurface,
    const double iOffsetLength,
    const double iTol,
    const CATLONG32 iKeepKnots,
    CATSkillValue iMode) = 0;

  virtual CATFrFOffsetSur *CATPGMCreateFrFOffsetSur(
    CATGeoFactory *Factory,
    const CATSurface *iSurface,
    const double iOffsetLaw[],
    const double iTol,
    CATSkillValue iMode) = 0;

  virtual CATFrFOffsetSur *CATPGMCreateFrFOffsetSur(
    CATGeoFactory *Factory,
    const CATSurface *iSurface,
    const double iOffsetLength,
    const double iTol,
    CATSkillValue iMode) = 0;

  virtual CATAnalyticMatchSurface *CATPGMCreateAnalyticMirrorMatch(
    CATGeoFactory *iFactory,
    CATPLine *iBoundaryToMatch,
    CATPlane *iPlane,
    const CATLaw *iAngularLawMirror,
    CATSkillValue iMode) = 0;

  virtual CATAnalyticMatchSurface *CATPGMCreateAnalyticMatchSurface(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATPLine *iBoundaryToMatch,
    CATCurve *iCrvRef,
    const CATCrvLimits &iCrvLimRef,
    CATSkillValue iMode) = 0;

  virtual CATBlendCurve *CATPGMCreateBlendCurve(
    CATGeoFactory *iFactory,
    const CATCurve *iCurve1,
    const CATCrvParam &iCrvParam1,
    const CATCurve *iCurve2,
    const CATCrvParam &iCrvParam2,
    CATSkillValue iMode) = 0;

  virtual CATBreakCurve *CATPGMCreateBreakCurve(
    CATGeoFactory *iFactory,
    CATNurbsCurve *iCrvToBreak,
    CATLONG32 iKnotRank,
    CATSkillValue iMode) = 0;

  virtual CATBreakCurve *CATPGMCreateBreakCurve(
    CATGeoFactory *iFactory,
    CATPointOnCurve *iPtBreak,
    CATSkillValue iMode) = 0;

  //virtual CATBreakSurface *CATPGMCreateBreakSurface(
  //  CATGeoFactory *iFactory,
  //  CATLISTP(CATPCurve) &iListe,
  //  CATSkillValue iMode) = 0;

  //virtual CATBreakSurface *CATPGMCreateBreakSurface(
  //  CATGeoFactory *iFactory,
  //  CATPointOnSurface *iPtBreak,
  //  CATSkillValue iMode) = 0;

  //virtual CATBreakSurface *CATPGMCreateBreakSurface(
  //  CATGeoFactory *iFactory,
  //  CATPCurve *iCurve,
  //  CATSkillValue iMode) = 0;

  virtual CATAnalyticMatchSurface *CATPGMCreateAnalyticMirrorMatch(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATPLine *iBoundaryToMatch,
    CATPlane *iPlane,
    const CATLaw *iAngularLawMirror,
    CATSkillValue iMode) = 0;

  virtual CATICGMCrvFittingToNurbsCrv *CATCGMCreateCrvFittingToNurbsCrv(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATCurve *iCurve,
    const CATCrvLimits &iLimits,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual CATICGMSurFittingToNurbsSur *CATCGMCreateSurFittingToNurbsSur(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATSurface *iSurface,
    const CATSurLimits &iLimits,
    double iMaxDeviation,
    CATLONG32 iRationalAllowed,
    CATSkillValue iMode) = 0;

  virtual CATIPGMConcatenationCurve *CATPGMCreateConcatenationCurve(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iSoftwareConfiguration,
    const CATLISTP(CATCurve) &iListOfCurve,
    const CATLISTP(CATCrvLimits) &iListOfLimits,
    const CATListOfInt & iListOfOrient) = 0;

  virtual CATConvertCrvToNurbsCrv *CATPGMCreateConvertCrvToNurbsCrv(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATCurve &iCurve) = 0;

  virtual CATCrvFittingToNupbsArc *CATPGMCreateCrvFittingToNupbsArc(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATCurve *iCrvToConvert,
    const CATCrvLimits *iCrvLim,
    const CATLONG32 &iDimension,
    const double &iToler,
    const CATLONG32 &iMaxDegree,
    CATSkillValue iMode) = 0;

  virtual CATCrvFittingToNupbsArc *CATPGMCreateCrvFittingToNupbsArc(
    CATGeoFactory *iFactory,
    const CATCurve *iCrvToConvert,
    const CATCrvLimits *iCrvLim,
    const CATLONG32 &iDimension,
    const double &iToler,
    const CATLONG32 &iMaxDegree,
    CATSkillValue iMode) = 0;

  virtual CATIPGMFrFConversionServicesToSplines *CATPGMCreateConversionServicesToSplines(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATEdge *iEdge) = 0;

  virtual CATIPGMFrFConversionServicesToSplines *CATPGMCreateConversionServicesToSplines(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody) = 0;

  virtual CATIPGMFrFMultiSmoothOperator* CATPGMFrFCreateFMultiSmoothingOper(
    CATSoftwareConfiguration* iConfig,
    const CATTolerance* ipTolObject,
    int iNb_scans_to_smooth,
    CATMathSetOfPointsND** itab_of_scans) = 0;

};

/**
 * Returns the factory of implementations of interfaces for the framework FreeFormOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMFreeFormOpeItfBldr1 *CATCGMGetFreeFormOpeItfBldr1();

#endif /* CATIPGMFreeFormOpeItfBldr1_h */
