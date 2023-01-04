#ifndef CATIPGMAdvTopoOpeItfBldr_h
#define CATIPGMAdvTopoOpeItfBldr_h

//=============================================================================
// 10/01/18 NLD Suppression des vieux CATPGMCreateTopoFrFOffset sans configuration (1/2 par option de precompilation)
// 15/01/18 NLD Suppression des vieux CATPGMCreateTopoFrFOffset sans configuration (2/2 par suppression effective)
// 22/03/18 NLD Ajout CATPGMCreateFrFTopologicalRoadSweep
//              Mise au propre complète
//              Un brin de réordonnancement logique du foutoir des déclarations de classes
// 30/03/18 NLD Suppression CATPGMCreateTopologicalBlend à 2 wires et 2 supports (voir CATPGMCreateTopBlend)
// 30/10/20 NLD Ajout CATPGMCreateFrFTopologicalRoadSweep à deux guides
//=============================================================================

#include "CATGMOperatorsInterfaces.h"

#include "CATBaseUnknown.h"

#include "CATCollec.h"
#include "CATDataType.h"

#include "CATSkillValue.h"

#include "CATMathDef.h"
#include "CATTopDefine.h"
#include "CATFrFTopologicalSweepDef.h"
#include "CATBodyFreezeMode.h"
#include "CATShellUnfoldMethod.h"

class CATMathPoint;
class CATMathVector;
class CATMathPlane;
class CATMathDirection;
class CATMathLine;
class CATMathAxis;
class CATLISTV(CATMathPoint2D);

class CATGeoFactory;
class CATGeometry;
class CATDomain;
class CATEdge;
class CATFace;
class CATBody;
class CATLaw;
class CATShell;
class CATVertex;
class CATCurve;
class CATLISTP(CATCurve);
class CATLISTP(CATCell);
class CATLISTP(CATBody);
class CATLISTP(CATFace);
class CATLISTP(CATEdge);
class CATLISTP(CATGeometry);

class CATFrFNurbsMultiForm;

class CATSoftwareConfiguration;
class CATCGMJournalList;
class CATTopData;

class CATFrFCompositeCurve;

class CATDirWrapSurfaceDefine;
class CATWrapCurveDefine;
class CATWrapSurfaceDefine;

class CATSweepSolverEngineRoadInt;

class CATSpaceDeformationSplitTool;
class CATSpaceDeformationTopoMap;
class CATMapFunctionXYZ;

class CATLocalizer2DFrom3D;

class CATBodyMotion;

class CATICGMSkinExtrapolation;
class CATIPGMSkinExtrapolation;
class CATICGMThickenOp;
class CATIPGMThickenOp;
class CATICGMTopCleanCrvOperator;
class CATIPGMTopCleanCrvOperator;
class CATICGMTopMostContinuousGeoInWireOperator;
class CATIPGMTopMostContinuousGeoInWireOperator;
class CATICGMTopSimilarCurve;
class CATIPGMTopSimilarCurve;
class CATICGMTopSpine;
class CATIPGMTopSpine;
class CATICGMTopSweep;
class CATIPGMTopSweep;
class CATIPGMTopologicalBlend;
class CATICGMTopologicalBlendCurve;
class CATIPGMTopologicalBlendCurve;
class CATICGMTopologicalFill;
class CATIPGMTopologicalFill;
class CATICGMTopologicalFilletBlend;
class CATIPGMTopologicalFilletBlend;
class CATICGMTopologicalMatch;
class CATIPGMTopologicalMatch;
class CATICGMTopBlend;
class CATIPGMTopBlend;
class CATICGMTopShellOrientation;
class CATIPGMTopShellOrientation;
class CATICGMFrFTopologicalSweep;
class CATIPGMFrFTopologicalSweep;
class CATICGMTopCorner;
class CATIPGMTopCorner;
class CATICGMTopSweepWireSkinCircle;
class CATIPGMTopSweepWireSkinCircle;
class CATIPGMCreateLawOnWire;
class CATIPGMFrFConvertCCVToWire;
class CATIPGMTopCleanLoopOfFaceOperator;
class CATIPGMTopWireContinuity;
class CATIPGMTopoFrFOffset;
class CATIPGMTopProjection;
class CATIPGMTopShellUnfold;
class CATIPGMHybProject;
class CATIPGMTopParallel;
class CATICGMExtrapolParallelTool;
class CATIPGMWireContinuity;
class CATICGMGeometrySizeOptimization;
class CATIPGMGeometrySizeOptimization;
class CATIPGMTopFilletRadiusReductionOpe;
class CATIPGMSurTo2DGlobalDevProjMapping;
class CATIPGMSurTo2DGlobalDevDevMapping;
class CATPGMFrFTopologicalSweepR12Adapter;
class CATIPGMTopFRRRailsExtractorOpe;
class CATIPGMTopShellUnfoldTransfer;
class CATIPGMTopFRRRadiusComputationOpe;
class CATIPGMTopFRRFilletDetectionOpe;
class CATIPGMTopOperator;
class CATPGMTopologicalDeviation;
class CATIPGMTopShellFlattener;
class CATICGMTopSilhouette;
class CATICGMTopSweepVolume;
class CATIPGMTopSweepVolume;
class CATIPGMTopRevol;
class CATPGMShellUnfoldAttribute;
class CATICGMTopWireContinuity;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMAdvTopoOpeItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework AdvancedTopologicalOpe.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMAdvTopoOpeItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  //---------------------------------------------------------------------------
  virtual CATICGMSkinExtrapolation *CATCGMCreateSkinExtrapolation(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iSkin,
          CATBody                  * iWireOnSkin) = 0;

  virtual CATIPGMSkinExtrapolation *CATPGMCreateSkinExtrapolation(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iSkin,
          CATBody                  * iWireOnSkin) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMThickenOp *CATCGMCreateThickenOp(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iBody,
          double                     iOffset1,
          double                     iOffset2) = 0;

  virtual CATIPGMThickenOp *CATPGMCreateThickenOp(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iBody,
          double                     iOffset1,
          double                     iOffset2) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopCleanCrvOperator *CATCGMCreateTopCleanCrvOperator(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iWireBody) = 0;

  virtual CATIPGMTopCleanCrvOperator *CATPGMCreateTopCleanCrvOperator(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iWireBody) = 0;

  virtual CATICGMTopMostContinuousGeoInWireOperator *CATCGMCreateTopMostContinuousGeoInWireOperator(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iWireBody) = 0;

  virtual CATICGMTopMostContinuousGeoInWireOperator *CATCGMCreateTopMostContinuousGeoInWireOperator(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iWireBody,
          CATBody                  * iShellBody1,
          CATBody                  * iShellBody2) = 0;

  virtual CATICGMTopMostContinuousGeoInWireOperator *CATCGMCreateTopMostContinuousGeoInWireOperator(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iWireBody,
          CATBody                  * iShellBody) = 0;

  virtual CATIPGMTopMostContinuousGeoInWireOperator *CATPGMCreateTopMostContinuousGeoInWireOperator(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iWireBody) = 0;

  virtual CATIPGMTopMostContinuousGeoInWireOperator *CATPGMCreateTopMostContinuousGeoInWireOperator(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iWireBody,
          CATBody                  * iShellBody1,
          CATBody                  * iShellBody2) = 0;

  virtual CATIPGMTopMostContinuousGeoInWireOperator *CATPGMCreateTopMostContinuousGeoInWireOperator(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iWireBody,
          CATBody                  * iShellBody) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopSimilarCurve *CATCGMCreateTopSimilarCurve(
          CATGeoFactory            * iFacto,
          CATTopData               * iData,
          CATBody                  * iBaseCurve,
          CATBody                  * iInputCurve1,
          CATBody                  * iInputCurve2) = 0;

  virtual CATIPGMTopSimilarCurve *CATPGMCreateTopSimilarCurve(
          CATGeoFactory            * iFacto,
          CATTopData               * iData,
          CATBody                  * iBaseCurve,
          CATBody                  * iInputCurve1,
          CATBody                  * iInputCurve2) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopSpine *CATCGMCreateTopSpine(
          CATGeoFactory            * iGeoFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    & iProfiles) = 0;

  virtual CATIPGMTopSpine *CATPGMCreateTopSpine(
          CATGeoFactory            * iGeoFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    & iProfiles) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopSweep *CATCGMCreateTopSweep(
          CATGeoFactory            * iGeoFactory,
          CATTopData               * iData,
          CATBody                  * iCenterBody,
          CATGeometry              * iCenterSupport,
          CATBody                  * iSpineBody,
          CATBody                  * iProfile) = 0;

  virtual CATIPGMTopSweep *CATPGMTopCreateSweep(
          CATGeoFactory            * iGeoFactory,
          CATBody                  * iCenterBody,
          CATGeometry              * iCenterSupport,
          CATBody                  * iSpineBody,
          CATBody                  * iProfile,
          CATCGMJournalList        * iJournal) = 0;

  virtual CATIPGMTopSweep *CATPGMCreateTopSweep(
          CATGeoFactory            * iGeoFactory,
          CATTopData               * iData,
          CATBody                  * iCenterBody,
          CATGeometry              * iCenterSupport,
          CATBody                  * iSpineBody,
          CATBody                  * iProfile) = 0;

  // see forward CATPGMForceFillTwistMode
  // see forward CATPGMForceMultipleViewingDirMode
  //---------------------------------------------------------------------------
  virtual CATIPGMTopologicalBlend *CATPGMCreateTopologicalBlend(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
    const CATBody                  * iWire,
    const CATBody                  * iSupport) = 0;

/* suppression NLD300318 voir CATPGMCreateTopBlend
  virtual CATIPGMTopologicalBlend *CATPGMCreateTopologicalBlend(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
    const CATBody                  * iWire1,
    const CATBody                  * iWire2,
    const CATBody                  * iSupport1,
    const CATBody                  * iSupport2) = 0;
*/

  virtual CATICGMTopologicalBlendCurve *CATCGMCreateTopologicalBlendCurve(
          CATGeoFactory            * iFactory,
          CATTopData               * iData,
          CATBody                  * iWire1,
          CATBody                  * iWireParam1,
          CATBody                  * iWire2,
          CATBody                  * iWireParam2) = 0;

  virtual CATIPGMTopologicalBlendCurve *CATPGMCreateTopologicalBlendCurve(
          CATGeoFactory            * iFactory,
          CATTopData               * iData,
          CATBody                  * iWire1,
          CATBody                  * iWireParam1,
          CATBody                  * iWire2,
          CATBody                  * iWireParam2) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopologicalFill *CATCGMCreateTopologicalFill(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
    const CATLISTP(CATEdge)        * iListOfEdges,
    const CATLISTP(CATFace)        * iListOfFaces,
    const CATBody                  * iBody) = 0;

  virtual CATICGMTopologicalFill *CATCGMCreateTopologicalFill(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLONG32                  iNumberOfWires,
    const CATBody                 ** iArrayOfBodyWires,
    const CATBody                 ** iArrayOfBodySupports) = 0;

  virtual CATIPGMTopologicalFill *CATPGMCreateTopologicalFill(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLONG32                  iNumberOfWires,
    const CATBody                 ** iArrayOfWires) = 0;

  virtual CATIPGMTopologicalFill *CATPGMCreateTopologicalFill(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
    const CATLISTP(CATEdge)        * iListOfEdges,
    const CATLISTP(CATFace)        * iListOfFaces,
    const CATBody                  * iBody) = 0;

  virtual CATIPGMTopologicalFill *CATPGMCreateTopologicalFill(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLONG32                  iNumberOfWires,
    const CATBody                 ** iArrayOfBodyWires,
    const CATBody                 ** iArrayOfBodySupports) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopologicalMatch *CATCGMCreateTopologicalMatch(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                 ** iWire1,
          CATBody                 ** iWire2,
          CATLONG32                  iNbWires,
          CATBody                  * iSupport1,
          CATBody                 ** iSupport2,
          CATSkillValue              iMode    ) = 0;

  virtual CATIPGMTopologicalMatch *CATPGMCreateTopologicalMatch(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                 ** iWire1,
          CATBody                 ** iWire2,
          CATLONG32                  iNbWires,
          CATBody                  * iSupport1,
          CATBody                 ** iSupport2,
          CATSkillValue              iMode    ) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopBlend *CATCGMCreateTopBlend(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
    const CATBody                  * iWire1,
    const CATBody                  * iWire2,
    const CATBody                  * iSupport1,
    const CATBody                  * iSupport2) = 0;

  virtual CATIPGMTopBlend *CATPGMCreateTopBlend(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
    const CATBody                  * iWire1,
    const CATBody                  * iWire2,
    const CATBody                  * iSupport1,
    const CATBody                  * iSupport2) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopShellOrientation *CATCGMCreateTopShellOrientation(
          CATGeoFactory            * iFactory,
          CATTopData               * iData,
          CATBody                  * inputBody) = 0;

  virtual CATIPGMTopShellOrientation *CATPGMCreateTopShellOrientation(
          CATGeoFactory            * iFactory,
          CATTopData               * iData,
          CATBody                  * inputBody) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMFrFTopologicalSweep *CATCGMCreateFrFTopologicalConicSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    * iLimitGuides) = 0;

  virtual CATICGMFrFTopologicalSweep *CATCGMCreateFrFTopologicalCircleSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    * iLimitGuides) = 0;

  virtual CATICGMFrFTopologicalSweep *CATCGMCreateFrFTopologicalSegmentSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    * iLimitGuides) = 0;

  virtual CATICGMFrFTopologicalSweep *CATCGMCreateFrFTopologicalSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    * iGuides,
          CATLISTP(CATGeometry)    * iProfiles,
          CATFrFTopologicalSweepType iSweepType) = 0;

  virtual CATICGMFrFTopologicalSweep *CATCGMCreateFrFTopologicalSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iGuide,
          CATBody                  * iProfile) = 0;


  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalBlendSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    * iLimitGuides) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalRoadSweep(
          CATGeoFactory            * iFactory    ,
          CATTopData               * iTopData    ,
          CATGeometry              * iMasterGuide,
          CATGeometry              * iProfile    ,
          CATSweepSolverEngineRoadInt *& ioSweepSolver   // aussi rendu en sortie si créé en interne
                                              ) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalRoadSweep(
          CATGeoFactory            * iFactory    ,
          CATTopData               * iTopData    ,
          CATGeometry              * iMasterGuide,
          CATGeometry              * iGuide2,
          CATGeometry              * iProfile    ,
          CATSweepSolverEngineRoadInt *& ioSweepSolver   // aussi rendu en sortie si créé en interne
                                              ) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalInterpolationSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    * iLimitGuides) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalConicSweep(
          CATGeoFactory            * iFactory,
          CATLISTP(CATGeometry)    * iLimitGuides,
          CATSkillValue              iMode    ,
          CATCGMJournalList        * iReport) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalConicSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    * iLimitGuides) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalCircleSweep(
          CATGeoFactory            * iFactory,
          CATLISTP(CATGeometry)    * iLimitGuides,
          CATSkillValue              iMode    ,
          CATCGMJournalList        * iReport) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalCircleSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    * iLimitGuides) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalSegmentSweep(
          CATGeoFactory            * iFactory,
          CATLISTP(CATGeometry)    * iLimitGuides,
          CATSkillValue              iMode    ,
          CATCGMJournalList        * iReport) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalSegmentSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    * iLimitGuides) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalSweep(
          CATGeoFactory            * iFactory,
          CATLISTP(CATGeometry)    * iGuides,
          CATLISTP(CATGeometry)    * iProfiles,
          CATSkillValue              iMode    ,
          CATCGMJournalList        * iReport,
          CATFrFTopologicalSweepType iSweepType) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATGeometry)    * iGuides,
          CATLISTP(CATGeometry)    * iProfiles,
          CATFrFTopologicalSweepType iSweepType) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalSweep(
          CATGeoFactory            * iFactory,
          CATBody                  * iGuide,
          CATBody                  * iProfile,
          CATSkillValue              iMode    ,
          CATCGMJournalList        * iReport) = 0;

  virtual CATIPGMFrFTopologicalSweep *CATPGMCreateFrFTopologicalSweep(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iGuide,
          CATBody                  * iProfile) = 0;

  //---------------------------------------------------------------------------
  // see forward CATPGMGetTopologicalSweepR12Adapter
  //---------------------------------------------------------------------------

  virtual CATICGMTopCorner *CATCGMCreateTopCornerBiTgt(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iPassage1,
          CATBody                  * iPassage2,
          CATBody                  * iSupport,
          double                     Radius) = 0;

  virtual CATIPGMTopCorner *CATPGMCreateTopCornerTgtCenterOnCrvRad(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iCurveCenter,
          CATBody                  * iCurveTgt,
          double                     iRadius,
          CATBody                  * iSupport) = 0;

  virtual CATIPGMTopCorner *CATPGMCreateTopCornerTgtCenterOnPt(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iCrv,
          CATBody                  * iPt,
          CATBody                  * iSupport) = 0;

  virtual CATIPGMTopCorner *CATPGMCreateTopCornerTriTangent(
          CATGeoFactory            * iFactory,
          CATBody                  * iPassage1,
          CATBody                  * iPassage2,
          CATBody                  * iPassage3,
          CATBody                  * iSupport,
          CATTopData               * iTopData) = 0;

  virtual CATIPGMTopCorner *CATPGMCreateTopCornerTgtByPoint(
          CATGeoFactory            * iFactory,
          CATBody                  * iPassage,
          CATBody                  * iCrvPt,
          CATBody                  * iPt,
          CATBody                  * iSupport,
          CATTopData               * iTopData) = 0;

  virtual CATIPGMTopCorner *CATPGMCreateTopCornerBiTgt(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iPassage1,
          CATBody                  * iPassage2,
          CATBody                  * iSupport,
          double                     Radius) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopSweepWireSkinCircle *CATCGMCreateTopSweepWireSkinCircleVariable(
          CATGeoFactory            * iFactory,
          CATTopData               * iData,
          CATBody                  * iSupportShell,
          CATBody                  * iGuide,
          CATBody                  * iSpine,
          CATLaw                   * iRadiusLaw) = 0;

  virtual CATIPGMTopSweepWireSkinCircle *CATPGMCreateTopSweepWireSkinCircleVariable(
          CATGeoFactory            * iFactory,
          CATTopData               * iData,
          CATBody                  * iSupportShell,
          CATBody                  * iGuide,
          CATBody                  * iSpine,
          CATLaw                   * iRadiusLaw) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopologicalBlendCurve *CATPGMCreateTopologicalBlendCurve(
          CATGeoFactory            * iFactory,
          CATBody                  * iWire1,
          CATBody                  * iWireParam1,
          CATBody                  * iWire2,
          CATBody                  * iWireParam2,
          CATBody                  * iTargetBody,
          CATBodyFreezeMode          iBodyFreezeMode,
          CATCGMJournalList        * iJournal,
          CATSkillValue              iMode    ) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopologicalFill *CATPGMCreateTopologicalFill(
          CATGeoFactory            * iFactory,
    const CATLONG32                  iNumberOfWires,
    const CATBody                 ** iArrayOfBodyWires,
    const CATBody                 ** iArrayOfBodySupports,
          CATSkillValue              iMode    ,
          CATCGMJournalList        * iJournal) = 0;

  virtual CATIPGMTopologicalFill *CATPGMCreateTopologicalFill(
          CATGeoFactory            * iFactory,
    const CATLONG32                  iNumberOfWires,
    const CATBody                 ** iArrayOfWires,
          CATSkillValue              iMode    ,
          CATCGMJournalList        * iJournal) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopologicalMatch *CATPGMCreateTopologicalMatch(
          CATGeoFactory            * iFactory,
          CATBody                 ** iWire1,
          CATBody                 ** iWire2,
          CATLONG32                  iNbWires,
          CATBody                  * iSupport1,
          CATBody                 ** iSupport2,
          CATSkillValue              iMode    ,
          CATCGMJournalList        * iJournal) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMCreateLawOnWire *CATPGMCreateCreateLawOnWire(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iWire) = 0;

  //---------------------------------------------------------------------------
  virtual CATDirWrapSurfaceDefine *CATPGMCreateDirWrapSurfaceDefine(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iStartShell,
          CATBody                  * iTargetShell,
          CATMathDirection         * iProjDir) = 0;

  //---------------------------------------------------------------------------
  virtual CATPGMFrFTopologicalSweepR12Adapter *CATPGMGetTopologicalSweepR12Adapter(
          CATICGMFrFTopologicalSweep *iSweepOperator) = 0;

  //---------------------------------------------------------------------------
  virtual CATSpaceDeformationSplitTool *CATCGMCreateSpaceDeformationSplitTool(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData) = 0;

  virtual CATSpaceDeformationTopoMap *CATCGMCreateSpaceDeformationTopoMap(
          CATMapFunctionXYZ        * iMapFunctionXYZ,
          CATSpaceDeformationSplitTool *iFDFSplitTool,
          CATBoolean                 iCuttingIsNecessary) = 0;

  virtual CATSpaceDeformationTopoMap * CATCGMCreateSpaceDeformationTopoMap(
          CATMapFunctionXYZ**        iFDFXYZMap,
    const int                        iNumberOfMap,
          CATSpaceDeformationSplitTool* FDFSplitTool) = 0;

  virtual CATIPGMTopCleanLoopOfFaceOperator *CATPGMCreateTopCleanLoopOfFaceOperator(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iBodyShellMonoFace) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopShellUnfold *CATPGMCreateTopShellUnfold(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iBody,
          CATShell                 * iShellToUnfold,
          CATLISTP(CATEdge)        * iEdgesToTear,
          CATShellUnfoldMethod       iMethod) = 0;

  virtual CATIPGMTopShellUnfold *CATPGMCreateTopShellUnfold(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iBody,
          CATLISTP(CATFace)        * iFacesToUnfold,
          CATLISTP(CATEdge)        * iEdgesToTear,
          CATShellUnfoldMethod       iMethod) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopWireContinuity *CATPGMCreateTopWireContinuity(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iWireBody) = 0;

  virtual CATIPGMTopoFrFOffset *CATPGMCreateTopoFrFOffset(
          CATGeoFactory            * Factory,
          CATTopData               * iTopData,
    const CATBody                  * iSurface,
    const double                     iOffsetLaw[],
          double                     iTol,
          CATLONG32                  iKeepKnots,
          CATSkillValue              iMode    ) = 0;


  //---------------------------------------------------------------------------
  virtual CATWrapCurveDefine *CATCGMCreateWrapCurveDefine(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATBody)        * iListOfStartWires,
          CATLISTP(CATBody)        * iListOfTargetWires) = 0;

  virtual CATWrapCurveDefine *CATCGMCreateWrapCurveDefine(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iStartSpineWire,
          CATBody                  * iStartDirectionWire,
          CATLISTP(CATBody)        * iListOfStartWires,
          CATBody                  * iTargetSpineWire,
          CATBody                  * iTargetDirectionWire,
          CATLISTP(CATBody)        * iListOfTargetWires) = 0;

  virtual CATWrapSurfaceDefine *CATCGMCreateWrapSurfaceDefine(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iStartShell,
          CATBody                  * iTargetShell) = 0;

  //---------------------------------------------------------------------------
  virtual CATLocalizer2DFrom3D *CATPGMCreateLocalizer2DFrom3D(
          CATGeoFactory            * factory,
          CATSoftwareConfiguration * iSoftConfig,
          CATLISTP(CATCell)        * faces,
          CATLISTP(CATCurve)       * PCurveList = NULL) = 0;

  virtual CATLocalizer2DFrom3D *CATPGMCreateLocalizer2DFrom3D(
          CATGeoFactory            * factory,
          CATLISTP(CATCell)        * faces) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopProjection *CATPGMCreateTopProjection(
          CATGeoFactory            * iFactory,
          CATTopData               * iData,
          CATBody                  * iBodyToProject,
          CATBody                  * iBodySupport,
          CATBody                  * iBodyShell,
          CATMathDirection         * iDirection) = 0;

  //---------------------------------------------------------------------------
  virtual void CATPGMGetSurTo2DDevProjAxis(
          CATVertex                * iInvariantPoint,
    const CATMathLine              & iRevolAxis,
          CATMathAxis              & oAxisOnSupport,
          CATSoftwareConfiguration * iConfig) = 0;

  virtual CATIPGMSurTo2DGlobalDevProjMapping *CATPGMCreateDevProjMapping(
          CATGeoFactory            * iFactory,
    const CATBoolean                 iImplicitMapping,
          CATVertex                * iInvariantPoint,
    const CATMathLine              & iRevolAxis,
    const double                   & iRadius,
          CATSoftwareConfiguration * iConfig) = 0;

  virtual void CATPGMGetSurTo2DDevDevAxis(
          CATGeoFactory            * iFactory,
          CATBody                  * SupportShell,
    const CATBoolean                 iImplicitMapping,
          CATVertex                * iInvariantPoint,
    const CATMathLine              & iRevolAxis,
          CATMathAxis              & oAxisOnSupport,
          CATLONG32                & oAxisInversionSuggestion,
          double                   & oSkinAxisOrientation,
          CATSoftwareConfiguration * iConfig) = 0;

  virtual CATIPGMSurTo2DGlobalDevDevMapping *CATPGMCreateDevDevMapping(
          CATGeoFactory            * iFactory,
          CATBody                  * SupportShell,
    const CATBoolean                 iImplicitMapping,
          CATVertex                * iInvariantPoint,
    const CATMathLine              & iRevolAxis,
          CATSoftwareConfiguration * iConfig) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMFrFConvertCCVToWire *CATPGMCreateFrFConvertCCVToWire(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATFrFCompositeCurve     * iCCV,
          CATBoolean                 iFreezeMode,
          double                     iMaxGapInDomain,
          CATBody                  * iRefBody) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMHybProject *CATPGMCreateTopProjectSimplif(
          CATGeoFactory            * iFactory,
          CATTopData               * iData,
          CATBody                  * iBodyToProject,
          CATBody                  * iBodySupport,
          CATMathDirection         * iDirection) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopParallel *CATPGMCreateTopParallelMostContinuous(
          CATICGMExtrapolParallelTool *iOption,
          CATBody                  * iCurve) = 0;

  virtual CATIPGMWireContinuity *CATPGMCreateWireContinuity(
          CATGeoFactory            * iFactory,
          CATTopData               * TopData,
          CATBody                  * iBodyWire) = 0;

  virtual CATIPGMWireContinuity *CATPGMCreateWireContinuity(
          CATGeoFactory            * iFactory,
          CATBody                  * iBodyWire) = 0;

  //---------------------------------------------------------------------------
  virtual void CATPGMForceMultipleViewingDirMode(CATICGMTopSweep *iTopSweepOperator) = 0;
  //---------------------------------------------------------------------------

  virtual CATFrFNurbsMultiForm **CATPGMConvertWireToNurbsMultiForms(
          CATTopData               * iTopData,
    const CATBody                  * iWire,
          CATFrFNurbsMultiForm    ** iRefMults,
          CATLONG32                  iNbRefMults) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMGeometrySizeOptimization *CATCGMCreateGeometrySizeOptimization(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData) = 0;

  virtual CATIPGMGeometrySizeOptimization *CATPGMCreateGeometrySizeOptimization(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopFilletRadiusReductionOpe *CATPGMCreateTopFilletRadiusReductionOpe(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iShellBody,
          CATBody                  * iWireBody1,
          CATBody                  * iWireBody2,
          CATLength                  iOriginalRadius) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopFRRRailsExtractorOpe *CATPGMCreateTopFRRRailsExtractorOpe(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iShellBody,
          CATLength                  iOriginalRadius) = 0;

  //---------------------------------------------------------------------------
  virtual int CATTopFRRRailsExtractorOpe_CATPGMTwoDomainBodyToTwoBodiesMonoDomain(
          CATBody                  * iTwoDomainBody,
          CATBody                  *&oOneDomainBody1,
          CATBody                  *&oOneDomainBody2) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopShellUnfoldTransfer *CATPGMCreateTopShellUnfoldTransfer(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iBody,
          CATBody                  * iFlattenedBody,
    const CATLISTP(CATFace)        & iListOfInputFaces,
    const CATLISTP(CATFace)        & iListOfFlattenedFaces) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopFRRRadiusComputationOpe *CATPGMCreateTopFRRRadiusComputationOpe(
          CATGeoFactory            * iFactory,
          CATSoftwareConfiguration * iSoftConfig,
          CATBody                  * iShellBody) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopFRRFilletDetectionOpe *CATPGMCreateTopFilletDetectionOpe(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iShellBody) = 0;

  //---------------------------------------------------------------------------
  virtual CATFrFCompositeCurve *CATPGMCreateATOCompositeCurve(
          CATTopData               * iTopData,
    const CATBody                  * iWire,
          CATBoolean                 iNonConnexWireSupport,
          CATLONG32                  iStartIndex,
          CATLONG32                  iEndIndex,
          CATIPGMTopOperator       * iTopOperator) = 0;

  virtual CATFrFCompositeCurve *CATPGMCreateATOCompositeCurve(
          CATTopData               * iTopData,
    const CATBody                  * iWire,
          CATEdge                 **&oEdges,
          CATBoolean                 iNonConnexWireSupport,
          CATLONG32                  iStartIndex,
          CATLONG32                  iEndIndex,
          CATIPGMTopOperator       * iTopOperator) = 0;

  virtual CATFrFCompositeCurve *CATPGMCreateATOCompositeCurve(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
    const CATBody                  * iBodyWire,
    const CATBody                  * iBodySupport,
          CATBoolean                 iNonConnexWireSupport,
          CATBoolean                 iIgnoreOutsideEdgeParts,
          CATBoolean                 iHybrid3D2DMode,
          CATIPGMTopOperator       * iTopOperator,
          CATBoolean                 iWarningNotOnShellBoundary) = 0;

  virtual CATFrFCompositeCurve *CATPGMCreateATOCompositeCurve(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
    const CATBody                  * iBodyWire,
    const CATBody                  * iBodySupport,
          CATEdge                 **&oEdges,
          CATFace                 **&oDummy,
          CATBoolean                 iNonConnexWireSupport,
          CATBoolean                 iIgnoreOutsideEdgeParts,
          CATBoolean                 iHybrid3D2DMode,
          CATIPGMTopOperator       * iTopOperator,
          CATBoolean                 iWarningNotOnShellBoundary) = 0;

  //---------------------------------------------------------------------------
  virtual void CATPGMForceFillTwistMode(CATICGMTopSweep *iTopSweepOperator) = 0;
  //---------------------------------------------------------------------------

  virtual CATPGMTopologicalDeviation *CATPGMCreateTopologicalDeviation(
          CATGeoFactory            * iFactory,
    const CATBody                  * iBodySupport1,
    const CATBody                  * iBodySupport2,
    const CATDomain                * iDomainSupport1,
    const CATDomain                * iDomainSupport2,
          CATSkillValue              iMode    ) = 0;

  virtual void CATPGMRemove(CATPGMTopologicalDeviation *&iTopologicalDeviation) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopShellFlattener *CATPGMCreateTopShellFlattener(
          CATGeoFactory            * ipFactory,
          CATTopData               * ipTopData,
    const CATBody                  * ipOriginalBody,
    const CATShell                 * ipShellToFlatten = NULL,
    const CATEdge                  * ipConstrainedEdge = NULL,
    const CATFace                  * ipFirstFace = NULL) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopSilhouette *CATCGMCreateTopSilhouette(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iBody) = 0;

  virtual CATICGMTopSilhouette *CATCGMCreateTopSilhouette(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATLISTP(CATBody)        * iInputBodies) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopSweepVolume *CATCGMCreateTopSweepVolume(
          CATGeoFactory                  * ipFactory,
          CATTopData                     * ipTopData,
          CATLISTV(CATMathPoint2D) const & iBodyProfilePoints,
          CATListOfDouble          const & iBodyProfileRadii,
          CATMathPoint             const & iBodyAxisOrigin,
          CATMathVector            const & iBodyAxisDirection,
          CATBodyMotion            const & iBodyMotion) = 0;

  //---------------------------------------------------------------------------
  virtual CATICGMTopWireContinuity *CATCGMCreateTopWireContinuity(
          CATGeoFactory            * iFactory,
          CATTopData               * iTopData,
          CATBody                  * iWireBody) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopSweepVolume *CATPGMCreateTopSweepVolume(
          CATGeoFactory                  * ipFactory,
          CATTopData                     * ipTopData,
          CATLISTV(CATMathPoint2D) const & iBodyProfilePoints,
          CATListOfDouble          const & iBodyProfileRadii,
          CATMathPoint             const & iBodyAxisOrigin,
          CATMathVector            const & iBodyAxisDirection,
          CATBodyMotion            const & iBodyMotion) = 0;

virtual CATICGMTopSweepVolume *CATCGMCreateTopSweepVolume(
          CATGeoFactory                  * ipFactory,
          CATTopData                     * ipTopData,
          CATBody                        * ipProfileWire,
          CATMathPoint             const & iBodyAxisOrigin,
          CATMathVector            const & iBodyAxisDirection,
          CATBodyMotion            const & iBodyMotion) = 0;

  virtual CATIPGMTopSweepVolume *CATPGMCreateTopSweepVolume(
          CATGeoFactory                  * ipFactory,
          CATTopData                     * ipTopData,
          CATBody                        * ipProfileWire,
          CATMathPoint             const & iBodyAxisOrigin,
          CATMathVector            const & iBodyAxisDirection,
          CATBodyMotion            const & iBodyMotion) = 0;

  virtual CATICGMTopSweepVolume *CATCGMCreateTopSweepVolume(
          CATGeoFactory                  * ipFactory,
          CATTopData                     * ipTopData,
          CATLISTV(CATMathPoint2D) const & iBodyProfilePoints,
          CATListOfDouble          const & iBodyProfileRadii,
          CATMathPlane             const &  iBodyTargetPlane,
          CATBodyMotion            const & iBodyMotion) = 0;

  virtual CATIPGMTopSweepVolume *CATPGMCreateTopSweepVolume(
          CATGeoFactory                  * ipFactory,
          CATTopData                     * ipTopData,
          CATLISTV(CATMathPoint2D) const & iBodyProfilePoints,
          CATListOfDouble          const & iBodyProfileRadii,
          CATMathPlane             const & iBodyTargetPlane,
          CATBodyMotion            const & iBodyMotion) = 0;

  virtual CATICGMTopSweepVolume *CATCGMCreateTopSweepVolume(
          CATGeoFactory                  * ipFactory,
          CATTopData                     * ipTopData,
          CATBody                        * ipProfileWire,
          CATMathPlane             const & iBodyRefPlane,
          CATMathPlane             const & iBodyTargetPlane,
          CATBodyMotion            const & iBodyMotion) = 0;

  virtual CATIPGMTopSweepVolume *CATPGMCreateTopSweepVolume(
          CATGeoFactory                  * ipFactory,
          CATTopData                     * ipTopData,
          CATBody                        * ipProfileWire,
          CATMathPlane             const & iBodyRefPlane,
          CATMathPlane             const & iBodyTargetPlane,
          CATBodyMotion            const & iBodyMotion) = 0;

  //---------------------------------------------------------------------------
  virtual CATIPGMTopRevol *CATPGMCreateTopRevolForGetAngles(
          CATGeoFactory            * iGeoFactory,
          CATTopData               * iData,
          CATBody                  * iProfBody,
          CATMathAxis              * iAxis,
          CATAngle                   iStartAngle,
          CATAngle                   iEndAngle) = 0;

  virtual CATPGMShellUnfoldAttribute *CATPGMCreateShellUnfoldAttribute() = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework AdvancedTopologicalOpe.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMAdvTopoOpeItfBldr *CATCGMGetAdvTopoOpeItfBldr();

#endif /* CATIPGMAdvTopoOpeItfBldr_h */
