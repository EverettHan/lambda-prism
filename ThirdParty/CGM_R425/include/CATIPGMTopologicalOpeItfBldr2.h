#ifndef CATIPGMTopologicalOpeItfBldr2_h
#define CATIPGMTopologicalOpeItfBldr2_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATCollec.h"
#include "CATDynOperatorDef.h"
#include "CATDynDraftDef.h"
#include "CATMathConstant.h"
#include "CATMathDef.h"
#include "CATTopDefine.h"
#include "CATMinMax.h"
#include "CATBodyFreezeMode.h"
#include "CATSkillValue.h"

#include "CATHybDef.h"
#include "CATDir.h"
#include "CATExtremumCoordCrvDef.h"
#include "CATDynFilletBlendVertex.h"
#include "CATDynFilletVertexRibbonOrder.h"
#include "CATTopToolsGapCheckMode.h"
#include "CATDynValidShell.h"
#include "CATIsoParameter.h"
#include "CATTopDef.h"

class CATDomain;

class CATICGMTopReflectLine;
class CATIPGMTopReflectLine;
class CATIPGMBodyExtremumCoord;
class CATIPGMCornerFace;
class CATIPGMDynBooleanTrim;
class CATIPGMDynIntersectionCrvBody;
class CATIPGMDynIntersectionSurBody;
class CATIPGMDynPrism;
class CATPlane;
class CATIPGMDynShellBody;
class CATIPGMDynTrimSew;


class CATIPGMExtrapolOpWireOnShell;

class CATPGMIsolateAnalysis;
class CATPGMLocalOrientationInvert;
class CATIPGMRemoveFace;
class CATIPGMRemoveFacesInShell;
class CATPGMRibbonHomotopy;
class CATIPGMConnectTool;
class CATIPGMShellFromClosedWire;

class CATIPGMSortBlendVertexSpecs;
class CATPGMExtruder;
class CATIPGMThick;
class CATIPGMThickSurface;

class CATIPGMTopMakeManifold;

class CATIPGMTopPattern;
class CATCompositeLaw;
class CATMathVector;
class CATLaw;
class CATICGMExtrapolParallelTool;
class CATICGMRemoveFace;
class CATICGMTopPattern;

class CATLISTP(CATCGMJournalInfo);
class CATLISTP(CATMathTransformation);
class CATIPGMSweep2;
class CATLISTP(CATICGMTopPropagationEdge);
class CATLISTP(CATSurface);
class CATIPGMDynMassProperties2D;
class CATDynMassProperties1DOnEdge;
class CATLISTP(CATEdge);
class CATLISTP(CATDomain);
class CATLISTP(CATICGMObject);
class CATICGMSurTo2DGlobalMapping;
class CATICGMDynMassProperties3D;
class CATLISTP(CATFace);
class CATLISTP(CATBody);
class CATLISTP(CATCurve);
class CATLISTP(CATCell);
class CATLISTP(ListPOfCATEdge);

#define CATICGMTopSweepWireSkinSegment CATICGMTopSweepWireSkin
#define CATIPGMTopSweepWireSkinSegment CATIPGMTopSweepWireSkin

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopologicalOpeItfBldr2;

/**
 * Factory of implementations of CGM interfaces for the framework TopologicalOperators.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalOpeItfBldr2: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATICGMTopReflectLine *CATCGMCreateTopReflectLine(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iInputSkin,
    CATBody *iOriginPoint,
    CATAngle iAngle) = 0;

  virtual CATICGMTopReflectLine *CATCGMCreateTopReflectLine(
    CATGeoFactory *iFactory,
    CATBody *iInputSkin,
    CATMathVector &iDirection,
    CATAngle iAngle,
    CATTopData *iData) = 0;

  virtual CATIPGMTopReflectLine *CATPGMCreateTopReflectLine(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iInputSkin,
    CATBody *iOriginPoint,
    CATAngle iAngle) = 0;

  virtual CATIPGMTopReflectLine *CATPGMCreateTopReflectLine(
    CATGeoFactory *iFactory,
    CATBody *iInputSkin,
    CATMathVector &iDirection,
    CATAngle iAngle,
    CATTopData *iData) = 0;

  virtual CATIPGMBodyExtremumCoord *CATPGMCreateDirBodyExtremumCoord(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATMinMax iTypeOfExtremum,
    const CATMathVector &iDirection,
    const CATMathPoint &iPtOrig) = 0;

  virtual CATIPGMBodyExtremumCoord *CATPGMCreateDirBodyExtremumCoord(
    CATGeoFactory *iFactory,
    CATBody *iBody,
    CATMinMax iTypeOfExtremum,
    const CATMathVector &iDirection,
    const CATMathPoint &iPtOrig,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMBodyExtremumCoord *CATPGMCreateBodyExtremumCoord(
    CATBody *iBody,
    CATTopData *iData,
    MinMax iTypeOfExtremum,
    Direction iDirection) = 0;

  virtual CATIPGMBodyExtremumCoord *CATPGMCreateBodyExtremumCoord(
    CATBody *iBody,
    MinMax iTypeOfExtremum,
    Direction iDirection,
    CATCGMJournalList *iJournal) = 0;

  /*virtual CATIPGMCornerFace *CATPGMCreateCornerFace(
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
    CATLISTP(CATEdge) *iListOfEdges) = 0;*/

  virtual CATIPGMDynBooleanTrim *CATPGMCreateDynBooleanTrim(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iBody1,
    CATBody *iBody2) = 0;

  virtual CATDynFilletBlendVertex *CATPGMCreateBlendVertex(
    CATDynFilletBlendVertex::SpecMode iSpecMode,
    CATLISTP(CATDynFilletBlendVertexSpec) &iSpecs) = 0;

  virtual CATDynFilletBlendVertexSpec *CATPGMCreateDynFilletBlendVertexSpec(
    CATCell *iEdge,
    double iRatio,
    int iDirection,
    double iSetback) = 0;

  virtual CATDynFilletVertexRibbonOrder *CATPGMCreateDynFilletVertexRibbonOrder(
    CATCell *iVertex,
    CATCell *iLastEdge ) = 0;		

  virtual CATDynFilletVertexRibbonOrder *CATPGMCreateDynFilletVertexRibbonOrder(
    CATCell *iVertex,
    const CATLISTP(ListPOfCATEdge) & iListsOfEdges ) = 0;			

  virtual CATDynFilletVertexRibbonOrder *CATPGMCreateDynFilletVertexRibbonOrder(
    CATCell *iEdge,
    CATLISTP(CATCell) *iStopFaces ) = 0;																 

  virtual CATIPGMDynIntersectionCrvBody *CATPGMDynCreateIntersectionCrvBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATCurve *iCurve,
    CATBody *iPart) = 0;

  virtual CATIPGMDynIntersectionCrvBody *CATPGMDynCreateIntersectionCrvBody(
    CATGeoFactory *iFactory,
    CATCurve *iCurve,
    CATBody *iPart,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMDynIntersectionCrvBody *CATPGMCreateDynIntersectionCrvBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATCurve *iCurve,
    CATBody *iPart) = 0;

  virtual CATIPGMDynIntersectionSurBody *CATPGMDynCreateIntersectionSurBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATSurface *iSurface,
    CATBody *iPart) = 0;

  virtual CATIPGMDynIntersectionSurBody *CATPGMDynCreateIntersectionSurBody(
    CATGeoFactory *iFactory,
    CATSurface *iSurface,
    CATBody *iPart,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMDynIntersectionSurBody *CATPGMCreateDynIntersectionSurBody(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATSurface *iSurface,
    CATBody *iPart) = 0;

  virtual CATDynMassProperties1DOnEdge *CATPGMDynCreateMassProperties1DOnEdge(
    CATTopData *iTopData,
    const CATEdge *ipEdge) = 0;

  virtual CATDynMassProperties1DOnEdge *CATPGMDynCreateMassProperties1DOnEdge(const CATEdge *ipEdge) = 0;

  virtual CATIPGMDynMassProperties2D *CATPGMDynCreateMassProperties2D(
    CATTopData *iTopData,
    const CATLISTP(CATFace) &iFaces) = 0;

  virtual CATIPGMDynMassProperties2D *CATPGMDynCreateMassProperties2D(const CATLISTP(CATFace) &) = 0;

  virtual CATIPGMDynMassProperties2D *CATPGMDynCreateMassProperties2D(const CATFace *) = 0;

  virtual CATIPGMDynPrism *CATPGMCreateDynPrism(
    CATGeoFactory *Container,
    CATTopData *iData,
    CATMathDirection *iDirection,
    const CATLISTP(CATCurve) &iProfile,
    CATPlane *iSupport) = 0;

  virtual CATIPGMDynPrism *CATPGMDynCreatePrism(
    CATGeoFactory *Container,
    CATMathDirection *iDirection,
    const CATLISTP(CATCurve) &iProfile,
    CATPlane *iSupport,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMDynShellBody *CATPGMDynCreateShellBody(
    CATGeoFactory *iForResultingBody,
    const CATLISTP(CATFace) &iFaces,
    CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMDynTrimSew *CATPGMCreateDynTrimSew(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATBody *iPart) = 0;

  virtual CATPGMIsolateAnalysis *CATPGMCreateIsolateAnalysis(CATBody * iBody) = 0;

  virtual CATPGMLocalOrientationInvert *CATPGMCreateLocalOrientationInvert(
    CATBody *iBody,
    CATCGMJournalList *iJournal) = 0;

  virtual CATPGMLocalOrientationInvert *CATPGMCreateLocalOrientationInvert(
    CATTopData *iTopData,
    CATBody *iBody) = 0;

  virtual CATIPGMRemoveFace *CATPGMCreateRemoveFace(
    CATTopData *iTopData,
    CATBody *iBody,
    CATLISTP(CATFace) &iFacesToRemove) = 0;

  virtual CATPGMRibbonHomotopy *CATPGMCreateRibbonHomotopy(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATEdge *iEdge,
    const CATMathPoint &iPoint,
    CATIPGMConnectTool *iProfilePtr,
    CATFace *iRefFace) = 0;

  virtual const CATString *CATShellFromClosedWire_CATCGMGetDefaultOperatorId() = 0;

  virtual CATIPGMShellFromClosedWire *CATShellFromClosedWire_CATPGMLoad(
    CATCGMStream &Str,
    const short LevelOfRuntime,
    const short VersionOfStream) = 0;

  virtual CATIPGMShellFromClosedWire *CATPGMCreateShellFromClosedWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATLISTP(CATBody) *iBodies,
    CATLISTP(CATSurface) *iSupports) = 0;

  virtual CATIPGMShellFromClosedWire *CATPGMCreateShellFromClosedWire(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    const CATBody *iBody,
    const CATSurface *iSupport) = 0;

  virtual CATIPGMSortBlendVertexSpecs *CATPGMCreateSortBlendVertexSpecs(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATLISTP(CATDynFilletBlendVertexSpec) &iSpecToOrder,
    CATLISTP(CATICGMTopPropagationEdge) &iPropagationEdgeList) = 0;

  virtual CATIPGMSweep2 *CATPGMCreateSweep2(
    CATGeoFactory *iGeoFactory,
    CATTopData *iTopData,
    CATBody *iProfBody,
    CATBody *iCntBody,
    CATPGMExtruder *iExtruder) = 0;

  virtual const CATString *CATThick_CATCGMGetDefaultOperatorId() = 0;

  virtual CATIPGMThick *CATPGMCreateThick(CATBody *iBody, CATCGMJournalList *iJournal) = 0;

  virtual CATIPGMThick *CATPGMCreateThick(
    CATTopData *iTopData,
    CATBody *iBody,
    short iExtrapolMode) = 0;

  virtual const CATString *CATThickSurface_CATCGMGetDefaultOperatorId() = 0;

  virtual CATIPGMThickSurface *CATPGMCreateThickSurface(
    CATTopData *iTopData,
    CATBody *iBodyToThick,
    double iOffset_1,
    double iOffset_2,
    short iDefaultSideForAllShells) = 0;

  virtual CATIPGMTopMakeManifold *CATPGMCreateTopMakeManifold(
    CATGeoFactory *iGeoFactory,
    CATTopData *iData,
    CATBody *iBodyToMakeManifold) = 0;


  virtual CATIPGMTopPattern *CATPGMCreateTopPattern(
    CATGeoFactory *iContainer,
    CATTopData *iData,
    CATDynBooleanType iOperation,
    CATBody *iPart,
    CATPlane *iPlane,
    CATBody *iTool,
    CATLISTP(CATMathTransformation) *iListTransfo,
    CATLISTP(CATCGMJournalInfo) *iListJournalInfo) = 0;


  virtual CATPGMRibbonHomotopy *CATPGMCreateRibbonHomotopy(
    CATBody *iBody,
    CATEdge *iEdge,
    const CATMathPoint &iPoint,
    CATGeoFactory *iFactory,
    CATIPGMConnectTool *iProfilePtr,
    CATFace *iRefFace) = 0;

  virtual CATIPGMTopPattern *CATPGMCreateTopPattern(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iPart,
    CATPlane *iPlane,
    CATLISTP(CATFace) &iPatternFacesList,
    CATLISTP(CATMathTransformation) *iListTransfo,
    CATLISTP(CATCGMJournalInfo) *iListJournalInfo) = 0;

  virtual CATBoolean CATThick_CATPGMGetErrorLocation(CATDomain *iDomain, CATMathPoint &oLocation) = 0;

  virtual CATICGMRemoveFace *CATCGMCreateRemoveFace(
    CATTopData *iTopData,
    CATBody *iBody,
    CATLISTP(CATFace) &iFacesToRemove) = 0;

    virtual CATICGMTopPattern *CATCGMCreateTopPattern(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATDynBooleanType iOperation,
    CATBody *iPart,
    CATPlane *iPlane,
    CATBody *iTool,
    CATLISTP(CATMathTransformation) *iListTransfo,
    CATLISTP(CATCGMJournalInfo) *iListJournalInfo) = 0;

  virtual CATICGMTopPattern *CATCGMCreateTopPattern(
    CATGeoFactory *iFactory,
    CATTopData *iData,
    CATBody *iPart,
    CATPlane *iPlane,
    CATLISTP(CATFace) &iPatternFacesList,
    CATLISTP(CATMathTransformation) *iListTransfo,
    CATLISTP(CATCGMJournalInfo) *iListJournalInfo) = 0;

  virtual CATIPGMBodyExtremumCoord *CATPGMCreateDirNewBodyExtremumCoord(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody,
    CATMinMax iTypeOfExtremum,
    const CATMathVector &iDirection,
    const CATMathPoint &iPtOrig) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework TopologicalOpe2rators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopologicalOpeItfBldr2 *CATCGMGetTopologicalOpeItfBldr2();

#endif /* CATIPGMTopologicalOpeItfBldr2_h */
