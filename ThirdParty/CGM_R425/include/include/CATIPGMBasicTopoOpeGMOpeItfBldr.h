#ifndef CATIPGMBasicTopoOpeGMOpeItfBldr_h
#define CATIPGMBasicTopoOpeGMOpeItfBldr_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CatTopPointLMode.h"
#include "CATDataType.h"
#include "CATCollec.h"
#include "CATDynDraftDef.h"
#include "CATMathConstant.h"
#include "CATMathDef.h"
#include "CATBodyFreezeMode.h"
#include "CATDistanceBodyBodyDef.h"
#include "CATSkillValue.h"
#include "CATIAV5Level.h"
#include "CATDynChamferRibbon.h"

class CATBody;
class CATTopData;
class CATMathVector;
class CATMathPoint;
class CATGeoFactory;
class CATICGMTopPointOperator;
class CATIPGMTopPointOperator;
class CATICGMTopSplineOperator;
class CATIPGMTopSplineOperator;
class CATICGMTopSurToNurbsSurOperator;
class CATIPGMTopSurToNurbsSurOperator;
class CATCell;
class CATIPGMDynAdvancedChamfer;
class CATIPGMDynAdvancedDraft;
class CATIPGMDynFillet;
class CATIPGMDynAdvancedFillet;
class CATIPGMCornerFace;
class CATIPGMTopConcatenateCrvOperator;
class CATIPGMTopConcatenateSurOperator;
class CATIPGMTopPlaneOperator;
class CATIPGMTopSpiralOperator;
class CATIPGMTopCircle;
class CATIPGMTopPConicOperator;
class CATIPGMTopCorner;
class CATIPGMThickPlus;
class CATICGMThickPlus;
class CATIPGMRegul;
class CATIPGMTopExtractEdge;
class CATEdge;
class CATListPtrCATEdge;
class CATVertex;
class CATIPGMTopExtractFace;
class CATFace;
class CATIPGMDistanceBodyBody;
class CATDomain;
class CATMathTransformation;
class CATIPGMDistanceBodyBody2;
class CATLISTP(CATCell);
class CATLISTP(CATFace);
#ifdef CATIAV5R20 // Not in R211
class CATIPGMTopAutoParallel;
class CATICGMDistanceTool;
#endif
class CATIPGMShellOperatorPlus;
class CATICGMShellOperatorPlus;
class CATIPGMThickSurfacePlus;
class CATICGMThickSurfacePlus;
class CATIPGMBtoSmoothingOper;
class CATSoftwareConfiguration;
class CATMathSetOfPointsND;
class CATCldScan;
class CATICGMDynAdvancedChamfer;
class CATICGMDynAdvancedDraft;
class CATICGMDynAdvancedFillet;
class CATICGMTopExtractFace;
class CATIPGMTopXHealingOp;
class CATIPGMMidSurfaceOperator;
class CATIPGMMidSurfaceAdvancedOperator;
class CATPGMBtoSmoothSVGModel;
class CATMathPoint;
class CATIPGMCornerChamferFace;
class CATIPGMCornerFaceOnShell;
class CATIPGMTopChamferDeltaShape;
class CATListPtrCATCell;
class CATIPGMTopUntrimOperator;
class CATIPGMBtoSmoothingOperAdv;
class CATIPGMBtoApproximateProfile;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMBasicTopoOpeGMOpeItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework BasicTopologicalOpe.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMBasicTopoOpeGMOpeItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATBody *CATCGMCreateTopPointOnSurface(
    CATGeoFactory *ioFactory,
    CATTopData *iTopData,
    CATBody *iSurface,
    const CATMathVector &iDirection,
    const double iGeodesicLength,
    CATBody *iReferencePointOnSurface) = 0;

  virtual CATBody *CATCGMCreateTopPointUV(
    CATGeoFactory *ioFactory,
    CATTopData *iTopData,
    const CATBody *iReferencePointOnSurface,
    CATBody *iSurface,
    const double iULength,
    const double iVLength) = 0;

  virtual CATBody *CATCGMCreateTopPointsTgtOnWire(
    CATGeoFactory *ioFactory,
    CATTopData *iTopData,
    CATBody *iWire,
    const CATMathVector &iTangent) = 0;

  virtual CATBody *CATCGMCreateTopPointOnWire(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWire,
    const double iLength,
    CATBody *iRefPoint,
    const CatTopPointLMode iLengthMode) = 0;

  virtual CATBody *CATCGMCreateTopPointXYZ(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    double iX,
    double iY,
    double iZ) = 0;

  virtual CATICGMTopPointOperator *CATCGMCreateTopPointOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData) = 0;

  virtual CATIPGMTopPointOperator *CATPGMCreateTopPointOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData) = 0;

  virtual CATBody *CATCGMCreateTopStableSpline(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLONG32 iNbpts,
    CATBody **iListOfPoints,
    const CATMathVector *iTangents,
    const CATMathVector *iCurvatures,
    const CATLONG32 *iImposition) = 0;

  virtual CATBody *CATCGMCreateTopSpline(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLONG32 iNbpts,
    CATBody **iListOfPoints,
    const CATMathVector *iTangents,
    const CATMathVector *iCurvatures,
    const CATLONG32 *iImposition) = 0;

  virtual CATICGMTopSplineOperator *CATCGMCreateTopStableSplineOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLONG32 iNbpts,
    CATBody **iListOfPoints,
    const CATMathVector *iTangents,
    const CATMathVector *iCurvatures,
    const CATLONG32 *iImposition) = 0;

  virtual CATICGMTopSplineOperator *CATCGMCreateTopSplineOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLONG32 iNbpts,
    CATBody **iListOfPoints,
    const CATMathVector *iTangents,
    const CATMathVector *iCurvatures,
    const CATLONG32 *iImposition) = 0;

  virtual CATIPGMTopSplineOperator *CATPGMCreateTopStableSplineOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLONG32 iNbpts,
    CATBody **iListOfPoints,
    const CATMathVector *iTangents,
    const CATMathVector *iCurvatures,
    const CATLONG32 *iImposition) = 0;

  virtual CATIPGMTopSplineOperator *CATPGMCreateTopSplineOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLONG32 iNbpts,
    CATBody **iListOfPoints,
    const CATMathVector *iTangents,
    const CATMathVector *iCurvatures,
    const CATLONG32 *iImposition) = 0;

  virtual CATICGMTopSurToNurbsSurOperator *CATCGMCreateTopSurToNurbsSurOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iShellBody,
    CATLISTP(CATFace) *iFaceList) = 0;

  virtual CATICGMTopSurToNurbsSurOperator *CATCGMCreateTopSurToNurbsSurOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iSkinBody,
    CATCell *iFaceCell) = 0;

  virtual CATIPGMTopSurToNurbsSurOperator *CATPGMCreateTopSurToNurbsSurOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iShellBody,
    CATLISTP(CATFace) *iFaceList) = 0;

  virtual CATIPGMTopSurToNurbsSurOperator *CATPGMCreateTopSurToNurbsSurOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iSkinBody,
    CATCell *iFaceCell) = 0;

  virtual CATIPGMDynAdvancedChamfer *CATPGMCreateDynAdvancedChamfer(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATIPGMDynAdvancedDraft *CATPGMCreateDynAdvancedDraft(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart,
    const CATDynDraftType iType) = 0;

  virtual CATIPGMDynFillet *CATPGMCreateAdvancedDynFillet(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart,
    CATBoolean iMultiRibbSafeMode) = 0;

  virtual CATIPGMDynAdvancedFillet *CATPGMCreateDynAdvancedFillet(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATIPGMCornerFace *CATPGMCreateCornerFace(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iVolumeBody,
    CATBody *iShellBody,
    CATVertex *iVertex,
    double iRadius,
    CATLISTP(CATEdge) *iListOfEdges) = 0;

  virtual CATIPGMCornerFace *CATPGMCreateCornerFace(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATVertex *iVertex,
    double iRadius,
    CATLISTP(CATEdge) *iListOfEdges) = 0;

  virtual CATIPGMCornerFace *CATPGMCreateCornerFace(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iVolumeBody,
    CATBody *iShellBody,
    CATLISTP(CATFace) *iListOfLeftFaces,
    CATLISTP(CATFace) *iListOfRightFaces,
    double iRadius,
    CATVertex *iVertex) = 0;

  virtual CATIPGMCornerFace *CATPGMCreateCornerFace(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iVolumeBody,
    CATBody *iShellBody,
    CATLISTP(CATFace) *iListOfLeftFaces,
    CATLISTP(CATFace) *iListOfRightFaces,
    CATLISTP(CATFace) *iListOfFacesToRemove) = 0;

  virtual const CATString *CATThickPlus_CATCGMGetDefaultOperatorId() = 0;

  virtual const CATString *CATRegul_CATCGMGetDefaultOperatorId() = 0;

  virtual CATIPGMTopConcatenateCrvOperator *CATPGMCreateTopConcatenateCrvOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWireBody) = 0;

  virtual CATIPGMTopConcatenateSurOperator *CATPGMCreateTopConcatenateSurOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToConcatenate,
    const int iNbFacesListToConcatenate,
    CATLISTP(CATFace) *iFacesListToConcatenate) = 0;

  virtual CATIPGMTopConcatenateSurOperator *CATPGMCreateTopConcatenateSurOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iShellBody,
    CATCell *iFaceCell1,
    CATCell *iFaceCell2) = 0;

  virtual const CATString *CATTopExtractEdge_CATCGMGetDefaultOperatorId() = 0;

  virtual const CATString *CATTopExtractFace_CATCGMGetDefaultOperatorId() = 0;

  virtual CATIPGMTopPlaneOperator *CATPGMCreateTopPlaneByLineAngularOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iPlane,
    CATBody *iLine,
    CATAngle iAngle) = 0;

  virtual CATIPGMTopSpiralOperator *CATPGMCreateTopSpiralOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iSupport,
    CATBody *iRadiusOrigin,
    const CATMathVector &iAngleAxis,
    CATLength iStartingRadius,
    CATBoolean iClockwiseRevolution) = 0;

  virtual CATIPGMTopCircle *CATPGMCreateTopCircleCenterRadius(
    CATGeoFactory *iFactory,
    CATTopData *iReport,
    CATBody *iCenter,
    CATBody *iSupport,
    double iRadius) = 0;

  virtual CATBody *CATPGMCreateTopPConic(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iShellBody,
    CATBody *iStartVertexBody,
    CATBody *iEndVertexBody,
    CATBody *iPassingVertexBody1,
    CATBody *iPassingVertexBody2,
    const CATMathVector &iTgt,
    CATLONG32 iIndexTgtVertexBody) = 0;

  virtual CATBody *CATPGMCreateTopPConic(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iShellBody,
    CATBody *iStartVertexBody,
    CATBody *iEndVertexBody,
    CATBody *iPassingVertexBody1,
    CATBody *iPassingVertexBody2,
    CATBody *iPassingVertexBody3) = 0;

  virtual CATBody *CATPGMCreateTopPConic(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iShellBody,
    CATBody *iStartVertexBody,
    CATBody *iEndVertexBody,
    CATBody *iTgtInterVertexBody,
    CATBody *iPassingVertexBody) = 0;

  virtual CATBody *CATPGMCreateTopPConic(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iShellBody,
    CATBody *iStartVertexBody,
    CATBody *iEndVertexBody,
    CATBody *iTgtInterVertexBody,
    double iParameter) = 0;

  virtual CATBody *CATPGMCreateTopPConic(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iShellBody,
    CATBody *iStartVertexBody,
    CATBody *iEndVertexBody,
    const CATMathVector &iStartTangent,
    const CATMathVector &iEndTangent,
    double iParameter) = 0;

  virtual CATBody *CATPGMCreateTopPConic(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iShellBody,
    CATBody *iStartVertexBody,
    CATBody *iEndVertexBody,
    const CATMathVector &iStartTangent,
    const CATMathVector &iEndTangent,
    CATBody *iPassingVertexBody) = 0;

  virtual CATIPGMTopPConicOperator *CATPGMCreateTopPConicOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iShellBody,
    CATBody *iStartVertexBody,
    CATBody *iEndVertexBody) = 0;

  virtual CATIPGMTopCorner *CATPGMCreateTop3DCorner(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iCurveOrPoint1,
    CATBody *iCurveOrPoint2,
    double iRadius) = 0;

  virtual CATIPGMThickPlus *CATPGMCreateThickPlus(CATTopData *iTopData, CATBody *iBody) = 0;

  virtual CATICGMThickPlus *CATCGMCreateThickPlus(CATTopData *iTopData, CATBody *iBody) = 0;

  virtual CATIPGMRegul *CATPGMCreateRegulOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData, 
    CATBody *iBody) = 0;

  virtual CATIPGMTopExtractEdge *CATPGMCreateTopExtractEdge(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATEdge *iEdge,
    CATBodyFreezeMode iMode) = 0;

  virtual CATIPGMTopExtractEdge *CATPGMCreateTopExtractEdge(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLISTP(CATCell) *iEdges,
    CATBodyFreezeMode iMode) = 0;

  virtual CATIPGMTopExtractFace *CATPGMCreateTopExtractFace(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATFace *iFace,
    CATBodyFreezeMode iMode) = 0;

  virtual CATIPGMTopExtractFace *CATPGMCreateTopExtractFace(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLISTP(CATCell) *iFaces,
    CATBodyFreezeMode iMode) = 0;

  virtual CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iMODE) = 0;

  virtual CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2) = 0;

  virtual CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATCell *iCell1,
    CATCell *iCell2,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iMODE) = 0;

  virtual CATIPGMDistanceBodyBody *CATPGMCreateDistanceBodyBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATDomain *iDomain1,
    CATDomain *iDomain2,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iMODE) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATBody *iBody1,
    const CATMathTransformation &iBody1Transformation,
    CATGeoFactory *iFactory2,
    CATBody *iBody2,
    const CATMathTransformation &iBody2Transformation,
    CATSkillValue iSkillValue) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATCell *iCell1,
    const CATMathTransformation &iCell1Transformation,
    CATGeoFactory *iFactory2,
    CATCell *iCell2,
    const CATMathTransformation &iCell2Transformation,
    CATSkillValue iSkillValue) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATDomain *iDomain1,
    const CATMathTransformation &iDomain1Transformation,
    CATGeoFactory *iFactory2,
    CATDomain *iDomain2,
    const CATMathTransformation &iDomain2Transformation,
    CATSkillValue iMODE) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATBody *iBody1,
    const CATMathTransformation &iBody1Transformation,
    CATGeoFactory *iFactory2,
    CATBody *iBody2,
    const CATMathTransformation &iBody2Transformation,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iSkillValue) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATCell *iCell1,
    const CATMathTransformation &iCell1Transformation,
    CATGeoFactory *iFactory2,
    CATCell *iCell2,
    const CATMathTransformation &iCell2Transformation,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iSkillValue) = 0;

  virtual CATIPGMDistanceBodyBody2 *CATPGMCreateDistanceBodyBody2(
    CATTopData *iTopData,
    CATGeoFactory *iFactory1,
    CATDomain *iDomain1,
    const CATMathTransformation &iDomain1Transformation,
    CATGeoFactory *iFactory2,
    CATDomain *iDomain2,
    const CATMathTransformation &iDomain2Transformation,
    CATDistanceBodyBodyType iType,
    CATDistanceBodyBodyMode iMode,
    CATSkillValue iMODE) = 0;

  virtual CATIPGMShellOperatorPlus *CATPGMCreateShellOperatorPlus(
    CATBody *iBody,
    CATTopData *iTopData,
    CATLength iInternalOffsetValue,
    CATLength iExternalOffsetValue) = 0;

  virtual CATICGMShellOperatorPlus *CATCGMCreateShellOperatorPlus(
    CATBody *iBody,
    CATTopData *iTopData,
    CATLength iInternalOffsetValue,
    CATLength iExternalOffsetValue) = 0;

  virtual CATIPGMThickSurfacePlus *CATPGMCreateThickSurfacePlus(
    CATTopData *iTopData,
    CATBody *iBodyToThick,
    double iOffset_1,
    double iOffset_2) = 0;

  virtual CATICGMThickSurfacePlus *CATCGMCreateThickSurfacePlus(
    CATTopData *iTopData,
    CATBody *iBodyToThick,
    double iOffset_1,
    double iOffset_2) = 0;

  virtual CATIPGMBtoSmoothingOper *CATPGMBtoCreateSmoothingOper(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATMathSetOfPointsND *iPoints) = 0;

  virtual CATIPGMBtoSmoothingOper *CATPGMBtoCreateSmoothingOper(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATCldScan *iScan) = 0;

  virtual CATIPGMBtoSmoothingOper *CATPGMBtoCreateSmoothingOper(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody) = 0;

  virtual CATICGMDynAdvancedChamfer *CATCGMCreateDynAdvancedChamfer(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATICGMDynAdvancedDraft *CATCGMCreateDynAdvancedDraft(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart,
    const CATDynDraftType iType) = 0;

  virtual CATICGMDynAdvancedFillet *CATCGMCreateDynAdvancedFillet(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATICGMTopExtractFace *CATCGMCreateTopExtractFace(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATFace *iFace,
    CATBodyFreezeMode iMode) = 0;

  virtual CATICGMTopExtractFace *CATCGMCreateTopExtractFace(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATLISTP(CATCell) *iFaces,
    CATBodyFreezeMode iMode) = 0;

  // KTU20120530 Xhealing
  virtual CATIPGMTopXHealingOp *CATPGMCreateTopXHealing(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATBody *ipBodyToHeal,
    const int iMode) = 0;

  virtual CATIPGMTopXHealingOp *CATPGMCreateTopXHealing(
    CATGeoFactory *ipFactory,
    CATTopData *ipTopData,
    CATBody *ipBodyToHeal) = 0;

  virtual CATIPGMMidSurfaceOperator *CATPGMCreateMidSurfaceOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iInputBody) = 0;

  virtual CATIPGMMidSurfaceAdvancedOperator *CATPGMCreateMidSurfaceAdvancedOperator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iInputBody) = 0;

  virtual CATPGMBtoSmoothSVGModel *CATPGMBtoCreateSmoothSVGModel(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    int iOrder,
    int iNbOfPoints,
    CATMathPoint *iTabOfCtrlPoints) = 0;

  virtual CATIPGMCornerChamferFace *CATPGMCreateCornerChamferFace(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iVolumeBody,
    CATBody *iShellBody,
    CATVertex *iVertex,
    CATDynTypeChamfer iChamferType,
    double iDistance1,
    double iDistance2,
    CATLISTP(CATEdge) *iListOfEdges,
    CATLISTP(CATFace) *iListOfFaces) = 0;

  virtual CATIPGMCornerFaceOnShell *CATPGMCreateCornerFaceOnShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    double iRadius,
    CATLISTP(CATEdge) *iListOfLeftEdges,
    CATLISTP(CATEdge) *iListOfRightEdges) = 0;

  virtual CATIPGMCornerFaceOnShell *CATPGMCreateCornerFaceOnShell(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATLISTP(CATEdge) *iListOfLeftEdges,
    CATLISTP(CATEdge) *iListOfRightEdges,
    CATLISTP(CATEdge) *iListOfEdgesToRemove) = 0;

  virtual CATIPGMTopChamferDeltaShape *CATPGMCreateTopChamferDeltaShape(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iFirstBody,
    CATLISTP(CATEdge) *iListOfEdgesToChamfer,
    CATLISTP(CATFace) *iListOfReferenceFaces,
    CATDynTypeChamfer iChamferType,
    double iLengthOfLeg1,
    double iLengthOfLeg2) = 0;

  virtual CATIPGMTopUntrimOperator *CATPGMCreateTopUntrimOperator(
    CATGeoFactory &iFactory,
    CATSoftwareConfiguration &iConfig,
    CATBody *iBodyToBeUntrimmed,
    CATListPtrCATCell * iListOfCells,
    CATCGMJournalList *iJournal) = 0;

  virtual const CATString *CATBtoSmoothingOperAdv_CATPGMGetDefaultOperatorId() = 0;

  virtual CATIPGMBtoSmoothingOperAdv *CATPGMBtoCreateSmoothingOperAdv(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATMathSetOfPointsND *iPoints,
    CATBoolean iSubdivMode) = 0;

  virtual CATIPGMBtoSmoothingOperAdv *CATPGMBtoCreateSmoothingOperAdv(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATCldScan *iScan,
    CATBoolean iSubdivMode) = 0;

  virtual CATIPGMBtoSmoothingOperAdv *CATPGMBtoCreateSmoothingOperAdv(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody) = 0;

  virtual CATIPGMBtoApproximateProfile *CATPGMBtoCreateApproximateProfile(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATMathSetOfPointsND *iPoints) = 0;

  virtual CATIPGMBtoApproximateProfile *CATPGMBtoCreateApproximateProfile(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATCldScan *iScan) = 0;

  virtual int CATBtoSmoothingServices_CATPGMReordering(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    int iIndex1,
    int iIndex2,
    CATCldScan *&ioScan) = 0;

  virtual void CATBtoSmoothingServices_CATPGMCleanOfTheInputScan(
    CATGeoFactory *iFactory,
    CATCldScan *InputScan,
    CATCldScan *&oCleanScan) = 0;

};

/**
 * Returns the factory of implementations of interfaces for the framework BasicTopologicalOpe.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMBasicTopoOpeGMOpeItfBldr *CATCGMGetBasicTopoOpeGMOpeItfBldr();

#endif /* CATIPGMBasicTopoOpeGMOpeItfBldr_h */
