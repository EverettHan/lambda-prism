#ifndef CATIPGMBasicTopoOpeItfBldr_h
#define CATIPGMBasicTopoOpeItfBldr_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATSkillValue.h"
#include "CATCollec.h"
#include "CATBodyFreezeMode.h"
#include "CATDataType.h"
#include "CATMathConstant.h"
#include "CATMathDef.h"
#include "CatTopPolarExtremum.h"
#include "CATPGMStaticGlobalRatio.h"
#include "CATLengthType.h"
#include "CATIACGMLevel.h"
#include "CATBodyFromLengthOnWireMeasureType.h"

class CATICGMComputePointOnWire;
class CATIPGMComputePointOnWire;
class CATGeoFactory;
class CATTopData;
class CATBody;
class CATICGMTopGeodesicPtPt;
class CATIPGMTopGeodesicPtPt;
class CATICGMLengthFromBodyOnWire;
class CATIPGMLengthFromBodyOnWire;
class CATVertex;
class CATWire;
class CATICGMTopCrvToNurbsCrvOperator;
class CATCell;
class CATIPGMTopCrvToNurbsCrvOperator;
class CATIPGMTopCrvToNurbsCrvOperatorProtected;
class CATCGMJournalList;
class CATCGMStream;
class CATEdge;
class CATICGMTopGeodesicLineOperator;
class CATIPGMTopGeodesicLineOperator;
class CATMathVector;
class CATICGMTopHelixOperator;
class CATIPGMTopHelixOperator;
class CATICGMTopLineOperator;
class CATIPGMTopLineOperator;
class CATICGMTopLineTangentCrvCrvOperator;
class CATIPGMTopLineTangentCrvCrvOperator;
class CATICGMTopLineTangentPtCrvOperator;
class CATIPGMTopLineTangentPtCrvOperator;
class CATICGMTopPointOperator;
class CATIPGMTopPointOperator;
class CATICGMTopPolarExtremumOperator;
class CATIPGMTopPolarExtremumOperator;
class CATMathPoint;
class CATIPGMLengthFromBodyOnShell;
class CATIPGMBodyFromLengthOnWire;
class CATIPGMBodyFromLengthOnShell;
class CATMathDirection;
class CATLISTP(CATICGMObject);
class CATLISTP(CATEdge);
//class CATIPGMTopAutoParallel;
//class CATICGMDistanceTool;
class CATCGMPickOperator;
class CATPGMPickOperator;
class CATICGMBodyFromLengthOnWire;
class CATIPGMAdvancedRemoveFaceOpe;
class CATICGMAdvancedRemoveFaceOpe;
class CATWallAnalyzer;
class CATSoftwareConfiguration;
class CATIPGMThicknessExtraction;
class CATMathTransformation;
class CATLISTP(CATMathPoint);
class CATLISTP(CATMathVector);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMBasicTopoOpeItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework BasicTopologicalOpe.
 */
class ExportedByCATGMModelInterfaces CATIPGMBasicTopoOpeItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATICGMComputePointOnWire *CATCGMCreateComputePointOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWire,
    double iValue) = 0;

  virtual CATIPGMComputePointOnWire *CATPGMCreateComputePointOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWire,
    double iValue) = 0;

  virtual CATICGMTopGeodesicPtPt *CATCGMCreateGeodesicLinePtPt(
    CATGeoFactory *iFacto,
    CATTopData *iData,
    CATBody *iPtOrig,
    CATBody *iPtFin,
    CATBody *iShellSupport) = 0;

  virtual CATIPGMTopGeodesicPtPt *CATPGMCreateGeodesicLinePtPt(
    CATGeoFactory *iFacto,
    CATTopData *iData,
    CATBody *iPtOrig,
    CATBody *iPtFin,
    CATBody *iShellSupport) = 0;

  virtual CATICGMLengthFromBodyOnWire *CATCGMCreateLengthFromBodyOnWire(
    CATGeoFactory *iFactory,
    CATBody *iVertex1,
    CATBody *iVertex2,
    CATBody *iWire,
    CATSkillValue iMode) = 0;

  virtual CATICGMLengthFromBodyOnWire *CATCGMCreateLengthFromBodyOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iVertex1,
    CATBody *iVertex2,
    CATBody *iWire,
    CATSkillValue iMode) = 0;

  virtual CATICGMLengthFromBodyOnWire *CATCGMCreateLengthFromBodyOnWire(
    CATGeoFactory *iFactory,
    CATVertex *iVertex1,
    CATVertex *iVertex2,
    CATWire *iWire,
    CATSkillValue iMode) = 0;

  virtual CATICGMLengthFromBodyOnWire *CATCGMCreateLengthFromBodyOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATVertex *iVertex1,
    CATVertex *iVertex2,
    CATWire *iWire,
    CATSkillValue iMode) = 0;

  virtual CATIPGMLengthFromBodyOnWire *CATPGMCreateLengthFromBodyOnWire(
    CATGeoFactory *iFactory,
    CATBody *iVertex1,
    CATBody *iVertex2,
    CATBody *iWire,
    CATSkillValue iMode) = 0;

  virtual CATIPGMLengthFromBodyOnWire *CATPGMCreateLengthFromBodyOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iVertex1,
    CATBody *iVertex2,
    CATBody *iWire,
    CATSkillValue iMode) = 0;

  virtual CATIPGMLengthFromBodyOnWire *CATPGMCreateLengthFromBodyOnWire(
    CATGeoFactory *iFactory,
    CATVertex *iVertex1,
    CATVertex *iVertex2,
    CATWire *iWire,
    CATSkillValue iMode) = 0;

  virtual CATIPGMLengthFromBodyOnWire *CATPGMCreateLengthFromBodyOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATVertex *iVertex1,
    CATVertex *iVertex2,
    CATWire *iWire,
    CATSkillValue iMode) = 0;

  virtual CATICGMTopCrvToNurbsCrvOperator *CATCGMCreateTopCrvToNurbsCrvOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWireBody,
    CATLISTP(CATEdge) *iEdgeList) = 0;

  virtual CATICGMTopCrvToNurbsCrvOperator *CATCGMCreateTopCrvToNurbsCrvOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWireBody,
    CATCell *iEdgeCell) = 0;

  virtual CATIPGMTopCrvToNurbsCrvOperator *CATPGMCreateTopCrvToNurbsCrvOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWireBody,
    CATLISTP(CATEdge) *iEdgeList) = 0;

  virtual CATIPGMTopCrvToNurbsCrvOperator *CATPGMCreateTopCrvToNurbsCrvOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWireBody,
    CATCell *iEdgeCell) = 0;

  virtual CATIPGMTopCrvToNurbsCrvOperatorProtected* CATPGMCreateTopCrvToNurbsCrvOperatorProtected(
      CATGeoFactory* iFactory,
      CATTopData* iTopData,
      CATBody* iWireBody,
      CATLISTP(CATEdge)* iEdgeList) = 0;

  virtual CATIPGMTopCrvToNurbsCrvOperatorProtected* CATPGMCreateTopCrvToNurbsCrvOperatorProtected(
      CATGeoFactory* iFactory,
      CATTopData* iTopData,
      CATBody* iWireBody,
      CATCell* iEdgeCell) = 0;


  virtual void CATTopCurveOperator_CATCGMLoadInOutput(
    CATCGMStream &ioStream,
    CATGeoFactory *&iFactory,
    CATTopData &ioTopData,
    CATBodyFreezeMode &iFreezeMode,
    CATLONG32 &iClosed,
    CATLISTP(CATICGMObject) &ioInputCopy,
    CATLISTP(CATICGMObject) &ioInputNoCopy,
    CATBody *&ioOutputBody,
    CATBody *&ioSupport,
    CATLISTP(CATICGMObject) *ioInputNeutral) = 0;

  virtual CATICGMTopGeodesicLineOperator *CATCGMCreateTopGeodesicLineOperatorFromDirection(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iSupport,
    CATBody *iOriginPoint,
    const CATMathVector &iDirection,
    double iFirstLength,
    double iSecondLength) = 0;

  virtual CATIPGMTopGeodesicLineOperator *CATPGMCreateTopGeodesicLineOperatorFromDirection(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iSupport,
    CATBody *iOriginPoint,
    const CATMathVector &iDirection,
    double iFirstLength,
    double iSecondLength) = 0;

  virtual CATIPGMTopGeodesicLineOperator *CATPGMCreateTopGeodesicLineOperatorAngledTangentToWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iCurve,
    CATBody *iShellOfCurve,
    CATAngle iAngle,
    double iFirstLength,
    double iSecondLength) = 0;

  virtual CATBody *CATCGMCreateTopHelix(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iHelixAxis,
    CATLONG32 HelixAxisOrientation,
    CATBody *iHelixOrigin,
    CATAngle iStartAngle,
    CATAngle iEndAngle,
    CATLength iPitch,
    CATLONG32 iTrigoOrientation) = 0;

  virtual CATICGMTopHelixOperator *CATCGMCreateTopHelixOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iHelixAxis,
    CATLONG32 iHelixAxisOrientation,
    CATBody *iHelixOrigin,
    CATAngle iStartAngle,
    CATAngle iEndAngle,
    CATLength iPitch,
    CATLONG32 iTrigoOrientation) = 0;

  virtual CATIPGMTopHelixOperator *CATPGMCreateTopHelixOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iHelixAxis,
    CATLONG32 iHelixAxisOrientation,
    CATBody *iHelixOrigin,
    CATAngle iStartAngle,
    CATAngle iEndAngle,
    CATLength iPitch,
    CATLONG32 iTrigoOrientation) = 0;

  virtual CATBody *CATCGMCreateTopInfiniteLineFromDirection(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    const CATMathVector &iDirection,
    CATBoolean iIsSemiInfinite) = 0;

  virtual CATICGMTopLineOperator *CATCGMCreateTopLineInfiniteOperatorFromDirection(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    const CATMathVector &iDirection,
    CATBoolean iIsSemiInfinite) = 0;

  virtual CATBody *CATCGMCreateTopLineNormalToShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iFirstPoint,
    CATBody *iShellOfPoint,
    double iLength) = 0;

  virtual CATICGMTopLineOperator *CATCGMCreateTopLineOperatorNormalToShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iShellOfPoint,
    double iLength) = 0;

  virtual CATBody *CATCGMCreateTopLineAngledTangentToWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iWire,
    CATBody *iShellOfWire,
    double iLength,
    CATAngle iAngle) = 0;

  virtual CATICGMTopLineOperator *CATCGMCreateTopLineOperatorAngledTangentToWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iCurve,
    CATBody *iShellOfCurve,
    double iLength,
    CATAngle iAngle) = 0;

  virtual CATBody *CATCGMCreateTopLineTangentToWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iCurve,
    double iLength) = 0;

  virtual CATICGMTopLineOperator *CATCGMCreateTopLineOperatorTangentToWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iCurve,
    double iLength) = 0;

  virtual CATBody *CATCGMCreateTopLineFromDirection(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    const CATMathVector &iDirection,
    double iLength) = 0;

  virtual CATICGMTopLineOperator *CATCGMCreateTopLineOperatorFromDirection(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    const CATMathVector &iDirection,
    double iLength) = 0;

  virtual CATBody *CATCGMCreateTopLineFromPoints(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iSecondPoint) = 0;

  virtual CATICGMTopLineOperator *CATCGMCreateTopLineOperatorFromPoints(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iSecondPoint) = 0;

  virtual CATIPGMTopLineOperator *CATPGMCreateTopLineInfiniteOperatorFromDirection(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    const CATMathVector &iDirection,
    CATBoolean iIsSemiInfinite) = 0;

  virtual CATIPGMTopLineOperator *CATPGMCreateTopLineOperatorNormalToShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iShellOfPoint,
    double iLength) = 0;

  virtual CATIPGMTopLineOperator *CATPGMCreateTopLineOperatorAngledTangentToWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iCurve,
    CATBody *iShellOfCurve,
    double iLength,
    CATAngle iAngle) = 0;

  virtual CATIPGMTopLineOperator *CATPGMCreateTopLineOperatorTangentToWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iCurve,
    double iLength) = 0;

  virtual CATIPGMTopLineOperator *CATPGMCreateTopLineOperatorFromDirection(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    const CATMathVector &iDirection,
    double iLength) = 0;

  virtual CATIPGMTopLineOperator *CATPGMCreateTopLineOperatorFromPoints(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iSecondPoint) = 0;

  virtual CATICGMTopLineTangentCrvCrvOperator *CATCGMCreateTopLineTangentCrvCrvOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWire1,
    CATBody *iWire2,
    CATBody *iPlane) = 0;

  virtual CATIPGMTopLineTangentCrvCrvOperator *CATPGMCreateTopLineTangentCrvCrvOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWire1,
    CATBody *iWire2,
    CATBody *iPlane) = 0;

  virtual CATICGMTopLineTangentPtCrvOperator *CATCGMCreateTopLnTgtPtCrvOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iCurve,
    CATBody *iPlane) = 0;

  virtual CATIPGMTopLineTangentPtCrvOperator *CATPGMCreateTopLnTgtPtCrvOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iCurve,
    CATBody *iPlane) = 0;

  virtual CATICGMTopPolarExtremumOperator *CATCGMCreateTopPolarExtremumOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWireBody,
    CATBody *iPlanarShellBody,
    CATBody *iPolarOriginVertexBody,
    const CATMathVector &iPolarAxis,
    const CatTopPolarExtremum iPolarExtremumExpected) = 0;

  virtual CATIPGMTopPolarExtremumOperator *CATPGMCreateTopPolarExtremumOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWireBody,
    CATBody *iPlanarShellBody,
    CATBody *iPolarOriginVertexBody,
    const CATMathVector &iPolarAxis,
    const CatTopPolarExtremum iPolarExtremumExpected) = 0;

  virtual int StaticGlobalRatio_CATPGMGRFromMathPoint(
    CATBody *Wire,
    const CATMathPoint &MathPoint,
    CATGlobalRatio &GR) = 0;

  virtual int StaticGlobalRatio_CATPGMGRFromMathPoint(
    CATBody *Wire,
    CATTopData *iData,
    const CATMathPoint &MathPoint,
    CATGlobalRatio &GR) = 0;

  virtual int StaticGlobalRatio_CATPGMGRFromLocale(
    CATBody *Wire,
    CATEdge *LocalEdge,
    const CATLocalRatio &LR,
    CATGlobalRatio &GR,
    CATTopData *iData) = 0;

  virtual int StaticGlobalRatio_CATPGMLocaleFromGR(
    CATBody *Wire,
    const CATGlobalRatio &GR,
    CATEdge *&LocalEdge,
    CATLocalRatio &LR,
    CATTopData *iData) = 0;

  virtual int StaticGlobalRatio_CATPGMMathPointFromGR(
    CATBody *Wire,
    const CATGlobalRatio &GR,
    CATMathPoint &PointXYZ) = 0;

  virtual int StaticGlobalRatio_CATPGMMathPointFromGR(
    CATBody *Wire,
    CATTopData *iData,
    const CATGlobalRatio &GR,
    CATMathPoint &PointXYZ) = 0;

  virtual CATIPGMLengthFromBodyOnShell *CATPGMCreateLengthFromBodyOnShell(
    CATGeoFactory *iFactory,
    CATBody *VertexIni,
    CATBody *VertexTarget,
    CATBody *SupportShell,
    CATSkillValue modev) = 0;

  virtual CATIPGMBodyFromLengthOnWire *CATPGMCreateBodyFromLengthOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATWire *aWire,
    CATVertex *aVertex,
    CATLength aDistance,
    CATLengthType type,
    CATSkillValue modev) = 0;

  virtual CATIPGMBodyFromLengthOnWire *CATPGMCreateBodyFromLengthOnWire(
    CATGeoFactory *iFactory,
    CATWire *aWire,
    CATVertex *aVertex,
    CATLength aDistance,
    CATLengthType type,
    CATSkillValue modev,
    CATCGMJournalList *Journal) = 0;

  virtual CATIPGMBodyFromLengthOnShell *CATPGMCreateBodyFromLengthOnShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    const CATBody *iShell,
    const CATBody *iVertex,
    const CATMathDirection &iDirection,
    const CATLength iDistance,
    const CATLengthType itype,
    const CATSkillValue imodev) = 0;

  virtual CATIPGMBodyFromLengthOnShell *CATPGMCreateBodyFromLengthOnShell(
    CATGeoFactory *iFactory,
    const CATBody *iShell,
    const CATBody *iVertex,
    const CATMathDirection &iDirection,
    const CATLength iDistance,
    const CATLengthType itype,
    const CATSkillValue imodev,
    CATCGMJournalList *Journal) = 0;
/*
  virtual CATIPGMTopAutoParallel *CATPGMCreateTopAutoParallel(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iSupportBody,
    CATBody *iWireBody,
    CATICGMDistanceTool *iDistTool) = 0;
*/

  virtual CATCGMPickOperator *CATCGMCreatePickOperator(CATSoftwareConfiguration &iConfig) = 0;

  virtual CATPGMPickOperator *CATPGMCreatePickOperator(CATSoftwareConfiguration &iConfig) = 0;

  virtual CATICGMBodyFromLengthOnWire *CATCGMCreateBodyFromLengthOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATWire *aWire,
    CATVertex *aVertex,
    CATLength aDistance,
    CATLengthType type,
    CATSkillValue modev) = 0;

#ifdef CATIACGMR215CAA
  virtual CATICGMTopGeodesicLineOperator *CATCGMCreateTopGeodesicLineOperatorAngledTangentToWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iOriginPoint,
    CATBody *iCurve,
    CATBody *iShellOfCurve,
    CATAngle iAngle,
    double iFirstLength,
    double iSecondLength) = 0;
#endif

  virtual CATIPGMAdvancedRemoveFaceOpe *CATPGMCreateAdvancedRemoveFaceOpe(
    CATGeoFactory &iFactory,
    CATTopData &iTopData,
    CATBody &iReferenceBody) = 0;

  virtual CATIPGMAdvancedRemoveFaceOpe *CATPGMCreateAdvancedRemoveFaceOpe(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iReferenceBody) = 0;

  virtual CATICGMAdvancedRemoveFaceOpe *CATCGMCreateAdvancedRemoveFaceOpe(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iReferenceBody) = 0;


  virtual CATWallAnalyzer * CATPGMCreateWallAnalyzer(CATGeoFactory            * ipGeoFactory,
                                                     CATSoftwareConfiguration * ipConfig) = 0;

  virtual CATWallAnalyzer* CATPGMCreateWallAnalyzer(CATGeoFactory* ipGeoFactory,
                                                    CATSoftwareConfiguration* ipConfig,
                                                    CATBody *ipBody) = 0;


  virtual CATIPGMBodyFromLengthOnWire *CATPGMCreateBodyFromLengthOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    const CATListOfDouble &iSamplingArcLengths,
    CATWire *iWire,
    CATVertex *iReferenceVertex,
    CATBoolean iReverseSamplingDirection,
    double iRelativeTolerance) = 0;

  virtual CATIPGMBodyFromLengthOnWire *CATPGMCreateBodyFromLengthOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    double iSamplingArcLength,
    CATWire *iWire,
    CATVertex *iReferenceVertex,
    CATBoolean iReverseSamplingDirection,
    double iRelativeTolerance) = 0;

    virtual CATIPGMBodyFromLengthOnWire *CATPGMCreateBodyFromLengthOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    const CATListOfDouble &iSamplingMeasures,
    CATBodyFromLengthOnWireMeasureType iMeasureType,
    CATWire *iWire,
    CATVertex *iReferenceVertex,
    CATBoolean iReverseSamplingDirection,
    double iRelativeTolerance) = 0;

  virtual CATIPGMBodyFromLengthOnWire *CATPGMCreateBodyFromLengthOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    double iSamplingMeasure,
    CATBodyFromLengthOnWireMeasureType iMeasureType,
    CATWire *iWire,
    CATVertex *iReferenceVertex,
    CATBoolean iReverseSamplingDirection,
    double iRelativeTolerance) = 0;


  virtual CATICGMBodyFromLengthOnWire *CATCGMCreateBodyFromLengthOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    const CATListOfDouble &iSamplingArcLengths,
    CATWire *iWire,
    CATVertex *iReferenceVertex,
    CATBoolean iReverseSamplingDirection,
    double iRelativeTolerance) = 0;

  virtual CATICGMBodyFromLengthOnWire *CATCGMCreateBodyFromLengthOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    double iSamplingArcLength,
    CATWire *iWire,
    CATVertex *iReferenceVertex,
    CATBoolean iReverseSamplingDirection,
    double iRelativeTolerance) = 0;

  virtual CATICGMBodyFromLengthOnWire *CATCGMCreateBodyFromLengthOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    const CATListOfDouble &iSamplingMeasures,
    CATBodyFromLengthOnWireMeasureType iMeasureType,
    CATWire *iWire,
    CATVertex *iReferenceVertex,
    CATBoolean iReverseSamplingDirection,
    double iRelativeTolerance) = 0;

  virtual CATICGMBodyFromLengthOnWire *CATCGMCreateBodyFromLengthOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    double iSamplingMeasure,
    CATBodyFromLengthOnWireMeasureType iMeasureType,
    CATWire *iWire,
    CATVertex *iReferenceVertex,
    CATBoolean iReverseSamplingDirection,
    double iRelativeTolerance) = 0;

  virtual CATIPGMThicknessExtraction* CATPGMCreateThicknessExtraction(
    CATGeoFactory* iFactory,
    CATTopData* iData,
    CATBody* iVolumicBody,
    CATLISTP(CATMathPoint) iPoints,
    CATLISTP(CATMathVector)iNormals,
    double                 iMaxThickness,
    CATMathTransformation  iTransfo,
    CATListOfInt iListOfIndexesToIgnore) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework BasicTopologicalOpe.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMModelInterfaces CATIPGMBasicTopoOpeItfBldr *CATCGMGetBasicTopoOpeItfBldr();

#endif /* CATIPGMBasicTopoOpeItfBldr_h */
