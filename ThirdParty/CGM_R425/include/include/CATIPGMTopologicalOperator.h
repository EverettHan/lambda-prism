#ifndef CATIPGMTopologicalOperator_h_
#define CATIPGMTopologicalOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATBooleanOperation.h"
#include "CATTopDefine.h"
#include "ListPOfListPOfCATFace.h"
#include "ListPOfListPOfCATEdge.h"
#include "ListPOfListPOfCATCell.h"
#include "CATSubdIntersectingFunction.h"

class CATBody;
class CATCGMJournalList;
class CATCXBody;
class CATCrvParam;
class CATDomain;
class CATEdge;
class CATEdgeCurve;
class CATFace;
class CATGeoFactory;
class CATLoop;
class CATMathPoint;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATPointOnSurface;
class CATShell;
class CATSurParam;
class CATSurface;
class CATVertex;
class CATVolume;
class CATWire;
class CATCell;
class CATTopology;
class CATIntersectFilteringTools;
class CATLISTP(CATVertex);
class CATLISTP(CATTopology);
class CATLISTP(CATFace);
class CATLISTP(CATEdge);
class CATLISTP(CATCell);
class CATVoBContactCheck;
class CATPGMIntersectFilteringTools;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopologicalOperator;

class ExportedByCATGMModelInterfaces CATIPGMTopologicalOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopologicalOperator();

  virtual void SetJournal(CATCGMJournalList *iJournal) = 0;

  virtual void DumpCutting(CATVertex *iVertex) = 0;

  virtual CATCGMJournalList *GetIntermediateJournal() = 0;

  virtual void SetVertexReporting(unsigned char iReporting) = 0;

  virtual unsigned char GetVertexReporting() = 0;

  virtual void SetEdgeReporting(unsigned char iReporting) = 0;

  virtual unsigned char GetEdgeReporting() = 0;

  virtual void SetFaceReporting(unsigned char iReporting) = 0;

  virtual unsigned char GetFaceReporting() = 0;

  virtual void SetFreezeResultBody(short iFreezeResultBody) = 0;

  virtual short GetFreezeResultBody() = 0;

  virtual void SetCreationBody(CATBody *iBody) = 0;

  virtual CATBody *GetCreationBody() = 0;

  virtual void SetNoSimplif(unsigned char iValue) = 0;

  virtual void SetNoSimplif_MergedCurves(short iValue) = 0;

  virtual unsigned char GetNoSimplif() = 0;

  virtual short GetNoSimplif_MergedCurves() = 0;

  virtual void SetNonManifoldReportDelayed(unsigned char iValue) = 0;

  virtual unsigned char GetNonManifoldReportDelayed() = 0;

  virtual void SetIntersectingFunction(IntersectingFunction iFunction) = 0;

  // Surfacic cases
  virtual void SetSimplifOnlyModifiable(CATBoolean iSimplifOnlyModifiable) = 0;

  virtual CATBoolean GetSimplifOnlyModifiable() = 0;

  virtual void SetIntersectFilteringTools(CATPGMIntersectFilteringTools *ipFilteringTools) = 0;

  virtual void SetLiveMode(CATBoolean iLiveMode) = 0;

  virtual CATBoolean GetLiveMode() = 0;

  // Operations booleennes
  virtual CATBody *Inter(CATBody *iBody1, CATBody *iBody2) = 0;

  virtual CATBody *Union(CATBody *iBody1, CATBody *iBody2) = 0;

  virtual CATBody *Diff(CATBody *iBody1, CATBody *iBody2) = 0;

  virtual CATBody *Delta(CATBody *iBody1, CATBody *iBody2) = 0;

  // Split Volume par Skin
  virtual CATBody *SplitBySkin(
    CATBody *iBody,
    CATBody *iSkin,
    int iSideToKeep,
    CATBoolean *oRelimitation = NULL,
    CATLISTP(CATCell) *oUnknownPositionCells = NULL) = 0;

  // Relimitation Skin par Volume
  virtual CATBody *RelimitSkin(CATBody *iBody, CATBody *iSkin, int iSideToKeep) = 0;

  virtual CATBody *RelimitWires(CATBody *iSolidBody, CATBody *iWiresBody, int iSideToKeep) = 0;

  virtual CATBody *RelimitVIV(CATBody *iSolidBody, CATBody *iVIVBody, int iSideToKeep) = 0;

  // Sewing d'une skin sur un Volume
  virtual CATBody *SewSkin(CATBody *iBody, CATBody *iSkin, int iSideToKeep) = 0;

  // Trim
  virtual CATBody *Trim(
    CATBody *iBody1,
    CATBody *iBody2,
    CATCell **iCellsToRemove,
    int iNbCellsToRemove,
    CATCell **iCellsToKeep = NULL,
    int iNbCellsToKeep = 0,
    CATCell **iCellsToRemoveByAdjacent = NULL,
    CATCell **iCellsAdjacentForRemove = NULL,
    int iNbCellsToRemoveByAdjacent = 0,
    CATCell **iCellsToKeepByAdjacent = NULL,
    CATCell **iCellsAdjacentForKeep = NULL,
    int iNbCellsToKeepByAdjacent = 0) = 0;

  virtual CATBody *Trim(
    CATLISTP(CATBody) &iBodies1,
    CATLISTP(CATBody) &iBodies2,
    CATCell **iCellsToRemove,
    int iNbCellsToRemove,
    CATCell **iCellsToKeep = NULL,
    int iNbCellsToKeep = 0,
    CATCell **iCellsToRemoveByAdjacent = NULL,
    CATCell **iCellsAdjacentForRemove = NULL,
    int iNbCellsToRemoveByAdjacent = 0,
    CATCell **iCellsToKeepByAdjacent = NULL,
    CATCell **iCellsAdjacentForKeep = NULL,
    int iNbCellsToKeepByAdjacent = 0) = 0;

  virtual CATBody *Trim(
    CATLISTP(CATBody) &iBodies1,
    CATLISTP(CATBody) &iBodies2,
    CATCell **iCellsToRemove,
    int iNbCellsToRemove,
    CATCell **iCellsToKeep,
    int iNbCellsToKeep,
    CATCell **iCellsToRemoveByAdjacent,
    CATCell **iCellsAdjacentForRemove,
    int *iNbCellsForRemoveSelection,
    int iNbSelectionsByRemoveAdjacency,
    int iNbCellsToRemoveByAdjacent,
    CATCell **iCellsToKeepByAdjacent,
    CATCell **iCellsAdjacentForKeep,
    int *iNbCellsForKeepSelection,
    int iNbSelectionsByKeepAdjacency,
    int iNbCellsToKeepByAdjacent) = 0;

  // services atomiques du Trim.
  virtual CATBody *CutBodies(
    CATBody *iBody1,
    CATBody *iBody2,
    CATLISTP(CATCell) &oListCells1,
    CATLISTP(CATCell) &oListCells2,
    CATLISTP(CATCell) &oListCells12) = 0;

  virtual CATBody *CutBodies(
    CATLISTP(CATBody) &iBodies1,
    CATLISTP(CATBody) &iBodies2,
    CATLISTP(CATCell) &oListCells1,
    CATLISTP(CATCell) &oListCells2,
    CATLISTP(CATCell) &oListCells12) = 0;

  virtual void GetAdjacentTrimmedCells(
    CATCell *iCell,
    CATLISTP(CATCell) &oListAdjacentCells) = 0;

  virtual void ToggleSelection(CATCell *iCell) = 0;

  virtual void BuildTrimmedBody(CATBody *iBody, CATLONG32 iComplementary = 0) = 0;

  virtual void BuildTrimmedAndIntermediateBodies(
    CATBody *iBody,
    CATLISTP(CATBody) &iBodies1,
    CATLISTP(CATBody) &iBodies2,
    CATLISTP(CATCell) &iListCells1,
    CATLISTP(CATCell) &iListCells2,
    CATLISTP(CATCell) &iListCells12,
    CATBooleanOperation iOperation,
    CATBody *&oIntermediateBody) = 0;

  virtual CATBody *Duplicate(
    CATBody *Body,
    short iDuplicateIS,
    CATLISTP(CATCell) &iListCells1,
    CATLISTP(CATCell) &iListCells2,
    CATLISTP(CATCell) &iListCells12,
    CATLISTP(CATCell) &ioNewListCells1,
    CATLISTP(CATCell) &ioNewListCells2,
    CATLISTP(CATCell) &ioNewListCells12) = 0;

  // RemoveLump
  virtual CATBody *RemoveLump(
    CATBody *iBody,
    CATCell **iCellsToRemove,
    int iNbCellsToRemove,
    CATCell **iCellsToKeep = NULL,
    int iNbCellsToKeep = 0) = 0;

  // y a-t-il une intersection entre deux Bodies ?
  virtual int IsIntersecting(CATBody *iBody1, CATBody *iBody2) = 0;

  virtual int IsClashing(CATBody *iBody1, CATBody *iBody2, int iTestVolumeInclusion = TRUE) = 0;

  virtual int IsIntersecting(
    CATShell *iShell1,
    CATShell *iShell2,
    CATBody *iBody1,
    CATBody *iBody2) = 0;

  // Outils Divers
  virtual CATBody *CloneBody(CATBody *iBody) = 0;

  virtual CATBody *CloneBodies(CATBody **ippBody, int iNb) = 0;

  virtual CATDomain *CloneDomain(CATBody *iBody, CATDomain *iDomain) = 0;

  //............................................
  // Outils De Nettoyage Recursif du Body :
  //    des cellules non partagees
  //    avec gestion du journal topo
  virtual void RemoveBody(CATBody *iBody) = 0;

  virtual void RemoveCell(CATCell *iCell) = 0;

  virtual void RemoveCellFromBody(CATCell *iCell, CATBody *iBody) = 0;

  // nettoyage des BoundingBoxes stockees
  virtual void ResetBoxes(CATBody *iBody) = 0;

  //............................................
  virtual void FullDuplicateCell(CATCell *iCell, CATBody *inBody, CATCell *&iDuplicatedCell) = 0;

  //............................................
  // Operateur de positionnement
  virtual CATLocation CalculatePosition(CATVolume *iVolume, const CATMathPoint &iMathPoint) = 0;

  // Nouvelle interface avec tolerance 3D (si NULL, c'est la resolution de modele qui est prise
  // par defaut).
  virtual CATLocation CalculatePosition(
    CATFace *iFace,
    const CATSurParam &iSurParam,
    double *i3DToleranceOnBoundary = NULL) = 0;

  // autre interface renvoyant l'Edge sur laquelle est pose le SurParam s'il est sur le bord de la face.
  virtual CATLocation CalculatePosition(
    CATFace *iFace,
    const CATSurParam &iSurParam,
    CATEdge **oBorder,
    CATCrvParam &oParamOnBorder,
    double *i3DToleranceOnBoundary = NULL) = 0;

  // Operateurs pose de coupantes
  virtual void SetCutting(
    CATFace *iCutFace,
    CATEdge *iCutEdge,
    CATSide iCutEdgeSide,
    CATVertex *iCuttingVertex,
    CATPointOnEdgeCurve *iPOECOnCutEdge,
    CATEdge *iCuttingEdgeBoundedByCuttingVertex = NULL) = 0;

  virtual void SetCutting(
    CATFace *iCutFace,
    CATVertex *iCutVertex,
    CATVertex *iCuttingVertex,
    CATEdge *iCuttingEdgeBoundedByCuttingVertex = NULL) = 0;

  virtual void SetCutting(
    CATShell *iCutShell,
    CATFace *iCutFace,
    CATEdge *iCutEdge,
    CATSide iCutEdgeSide,
    CATEdge *iCuttingEdge,
    CATCell *iCuttingStartSupport,
    CATCell *iCuttingEndSupport,
    CATPointOnEdgeCurve *iStartPOECOnCutEdge,
    CATPointOnEdgeCurve *iEndPOECOnCutEdge) = 0;

  virtual void SetCutting(
    CATFace *iCutFace,
    CATEdge *iCuttingEdge,
    CATPCurve *iCuttingPCurve) = 0;

  virtual void InvertCuttingPositionning(CATFace *iCutFace, CATEdge *iCuttingEdge) = 0;

  virtual void UnsetCutting(
    CATFace *iCutFace,
    CATEdge *iCutEdge,
    CATSide iCutEdgeSide,
    CATVertex *iCuttingVertex) = 0;

  virtual void UnsetCutting(
    CATFace *iCutFace,
    CATVertex *iCutVertex,
    CATVertex *iCuttingVertex) = 0;

  virtual void UnsetCutting(
    CATEdge *iCutEdge,
    CATEdge *iCuttingEdge,
    CATShell *iCutShell = NULL) = 0;

  virtual void UnsetCutting(CATFace *iCutFace, CATEdge *iCuttingEdge) = 0;

  virtual void UnsetCutting(CATShell *iCutShell, CATFace *iCuttingFace) = 0;

  virtual void UnsetCutting(CATShell *iCutShell, CATWire *iCuttingWire) = 0;

  virtual void UnsetCutting(CATShell *iCutShell, CATEdge *iCuttingEdge) = 0;

  virtual void UnsetCutting(CATShell *iCutShell, CATVertex *iCuttingVertex) = 0;

  virtual void UnsetCutting(CATWire *iCutWire, CATVertex *iCuttingVertex) = 0;

  // on passe le body pour activation, il faudrait le faire dans tous les operateurs Set et Unset.
  virtual int IsCutting(
    CATBody *iShellBody,
    CATShell *iCutShell,
    CATWire *iCuttingWire,
    int iCompletely = 0) = 0;

  virtual int IsCutting(CATBody *iShellBody, CATShell *iCutShell, CATEdge *iCuttingEdge) = 0;

  // Dump des cutting
  virtual void DumpCutting(CATFace *iFace, CATLISTP(CATCell) &oCuttingEdges) = 0;

  virtual void DumpCutting(CATFace *iFace, CATEdge *iEdge, CATLISTP(CATCell) &oCuttingCells) = 0;

  virtual void DumpCutting(
    CATFace *iFace,
    CATVertex *iVertex,
    CATLISTP(CATCell) &oCuttingCells) = 0;

  // intersecte des coupantes entre elles 
  virtual void IntersectCuttingEdges(
    CATFace *iCutFace,
    CATEdge *iCuttingEdge1,
    CATEdge *iCuttingEdge2,
    int &oNbIntersections,
    CATVertex ***oIntersections,
    int withConfusion = 0,
    int iConditionalEdgeIntersection = 0,
    int *oNbConfusionEdges = NULL,
    CATEdge ***oConfusionEdges = NULL) = 0;

  virtual CATEdge **SplitCuttingEdge(
    CATFace *iCutFace,
    CATEdge *iCoupee,
    int &oNbEdges,
    CATLocation **oLocations,
    int iPreserveModifiableVertices = 0) = 0;

  // renvoie 1 si l'intersection est un zero franc, 0 sinon
  virtual int RetrieveCuttingStatus(
    CATFace *iCutFace,
    CATEdge *iCutEdge,
    CATSide iCutEdgeSide,
    CATVertex *iCuttingVertex) = 0;

  virtual int RetrieveCuttingStatus(
    CATFace *iCutFace,
    CATVertex *iCutVertex,
    CATVertex *iCuttingVertex) = 0;

  virtual int RetrieveCuttingStatus(CATFace *iCutFace, CATVertex *iCuttingVertex) = 0;

  // Operateurs de decoupe
  virtual CATCell *GetCellSupport(
    CATCell *iCell,
    CATCell *iSupportOwningCell = NULL,
    int *oNbContainers = NULL) = 0;

  static void GetAllCellSupports(
    CATCell *iCell,
    CATLISTP(CATCell) &oListOfCells,
    int iOnlyDirect = 0);

  virtual void SplitWire(
    CATWire *iWire,
    CATFace *iSplittingFace,
    int &oNbEdges,
    CATLocation **oLocations,
    int iWithConfusion) = 0;

  virtual CATEdge **SplitEdge(
    CATEdge *iCutEdge,
    CATFace *iSplittingFace,
    int &oNbEdges,
    CATLocation **oLocations,
    int iWithConfusion = 0,
    int iConditionalEdgeIntersections = 0,
    int iPreserveModifiableVertices = 0,
    CATLoop *iLoopNotToIntersect = NULL,
    int iStabilizeConfusion = 0,
    int iUpdateFaceTouch = 1) = 0;

  virtual CATEdge **SplitEdge(CATEdge *iCutEdge, const CATCrvParam &iParam, int &oNbEdges) = 0;

  virtual CATEdge **SplitEdge(CATEdge *iCutEdge, CATPointOnEdgeCurve *iPoec, int &oNbEdges) = 0;

  virtual void SplitVertex(
    CATBody *iFaceBody,
    CATFace *iFace,
    CATVertex *iVertex,
    CATPointOnSurface *iPos,
    CATLocation &oLocation) = 0;

  virtual void SplitVertex(
    CATBody *iEdgeBody,
    CATEdge *iEdge,
    CATVertex *iVertex,
    CATPointOnEdgeCurve *iPoec,
    CATLocation &oLocation) = 0;

  virtual void SplitSingleEdgeWire(CATWire *iWire) = 0;

  virtual CATBody *IntersectFaces(CATFace *iFace1, CATFace *iFace2) = 0;

  virtual CATFace **DisconnectFace(
    CATFace *iFace,
    int &oNbFaces,
    CATBody *iBody,
    CATShell *iContainingShell = NULL,
    int iKeepInfo = 0,
    CATLISTP(CATEdge) *oFlattenedEdges = NULL) = 0;

  virtual void CleanDisconnectInfo(CATEdge *iEdge, int iCleanVertices = 0, int iCleanLoop = 1) = 0;

  virtual int SimplifyECrvs(
    CATLISTP(CATEdge) &iSetOfEdgesToSimplify,
    CATBody *iEdgesBody,
    int iKeepCanonicity = 0) = 0;

  virtual int SimplifyCompatibleECrvs(CATBody *iBodyToSimplify, int iKeepCanonicity = 0) = 0;

  virtual void SetOldSubdivide(int iOldSubdivide) = 0;

  virtual void CleanScar(CATEdge *iEdge) = 0;

  virtual void CleanDisconnectInfo(CATVertex *iVertex) = 0;

  virtual void RecalculateTouched(CATBody *iBody) = 0;

  virtual void RecalculateTouched(CATFace *iFace) = 0;

  virtual void RecalculateTouched(CATShell *iShell) = 0;

  virtual void RecalculateTouched(CATWire *iWire) = 0;

  // HKL 01 12 98 splits two faces
  virtual void MutuallySplitFaces(
    CATFace *iFace1,
    CATFace *iFace2,
    CATLISTP(CATFace) & oFacesFrom1, 
    CATLISTP(CATFace) & oFacesFrom2, 
    CATLISTP(CATFace) & oFacesFrom12) = 0;

  // calcule la peau a laquelle appartient la face sur le shell par propagation
  virtual CATFace **PropagatePositionVsDisconnector(
    CATFace *iFace,
    int &oNbFaces,
    CATShell *iContainingShell,
    CATBody *DisconnectBody = NULL,
    CATLocation *oLocation = NULL,
    CATBody *iWires = NULL,
    CATLONG32 *ConfusionRelativeOri = NULL,
    CATLONG32 *FlattenedIS = NULL,
    CATBoolean iSewingSelection = FALSE,
    CATLISTP(CATCell) *iPositioningVolumes = NULL) = 0;

  virtual void PropagatePositionVsDisconnector(
    CATWire *iWire,
    CATEdge *iEdge,
    CATBoolean iStopAtWireClosure,
    CATBoolean iThrowExceptionOnInconsistentPosition,
    CATLISTP(CATEdge) &oSetOfEdges,
    CATLocation &oLocation,
    CATBoolean &oIncompatiblePosition) = 0;

  // Decompositions en IS avec positionnement Vs. 3D Disconnector, then, if it's unknown, 
  // CATSubdIntersectionSkin::RetrieveScarPosition().
  virtual void GetDisconnectedShellPartition(
    CATShell *iDisconnectedShell,
    CATBoolean iErrorOnIncompatiblePositions,
    ListPOfListPOfCATFace &ioConnectedSetsOfFaces,
    CATListOfInt *ioPositions,
    CATListOfInt *ioRelativeOrientations) = 0;

  // Decompositions en IS avec positionnement Vs. Wires
  virtual void GetDisconnectedShellPartition(
    CATShell *iDisconnectedShell,
    CATBody *iWiresBody,
    CATBoolean iErrorOnIncompatiblePositions,
    ListPOfListPOfCATFace &ioConnectedSetsOfFaces,
    CATListOfInt *ioPositions) = 0;

  virtual void RemoveConfusedFaceLink(CATShell *iDisconnectedShell) = 0;

  virtual void DisconnectEdge(CATEdge *iEdge) = 0;

  virtual void DestroyCell(CATCell *iCell) = 0;

  virtual void DestroyEdge(
    CATEdge *iEdge,
    int iDestroyDependancies = 0,
    CATFace *iSurroundingFace = NULL,
    CATBoolean iUnlinkUselessGeometry = FALSE,
    CATBoolean iDestroyLyingOn = TRUE) = 0;

  virtual void DestroyVertex(CATVertex *iVertex) = 0;

  virtual void MergeVertices(
    CATVertex *iVertexReceiver,
    CATVertex *iVertexEmitter,
    int iKeepAllPoecs = 0,
    CATBody *iWorkingBody = NULL,
    CATLISTP(CATTopology) *iListFederator = NULL) = 0;

  virtual void MergeEdges(
    CATEdge *iEdgeReceiver,
    CATEdge *iEdgeEmitter,
    int inversion = 0,
    CATBody *iWorkingBody = NULL,
    CATLISTP(CATTopology) *iListFederator = NULL) = 0;

  virtual CATEdgeCurve *ComputeMerge(
    CATEdge *iEdge1,
    CATEdge *iEdge2,
    double iTolerance,
    int inversion = 0) = 0;

  virtual void ReportContents(CATEdge *iEdge) = 0;

  virtual CATBody *IntersectShells(
    CATShell *iShell1,
    CATShell *iShell2,
    CATBody *iBody1,
    CATBody *iBody2,
    int iKeepSign = 0) = 0;

  // Si iResultBody est non nul, le resultat de l'intersection (et donc de la methode) sera ce body
  virtual CATBody *IntersectShells(
    CATShell *iShell1,
    CATShell *iShell2,
    CATBody *iBody1,
    CATBody *iBody2,
    int iCreateWire,
    int iKeepSign,
    int *oNbWire,
    CATEdge ***oEdgesWire,
    int **oNbEdgesInWire,
    int **oNbConnectedExtremities,
    CATVertex ***oStartingFreeVertices = (CATVertex***)0,
    CATVertex ***oEndingFreeVertices = (CATVertex***)0,
    CATLISTP(CATFace) *iShell1CoveredFaces = (CATLISTP(CATFace)*)0,
    CATLISTP(CATFace) *iShell2CoveredFaces = (CATLISTP(CATFace)*)0,
    CATBody *iResultBody = (CATBody*)0) = 0;

  virtual CATBody *IntersectShells(
    CATBody *iBody1,
    CATBody *iBody2,
    CATShell *iShell1,
    CATShell *iShell2,
    int iKeepSign = 0,
    ListPOfListPOfCATEdge * oConfusionBorders = NULL) = 0;

  virtual CATBody *IntersectShellWire(
    CATShell *iShell,
    CATWire *iWire,
    CATBody *iBody1,
    CATBody *iBody2,
    int iCreateWire,
    int iKeepSign,
    int *oNbWire,
    CATEdge ***oEdgesWire,
    int **oNbEdgesInWire,
    int **oNbConnectedExtremities,
    CATVertex ***oStartingFreeVertices,
    CATVertex ***oEndingFreeVertices,
    CATLISTP(CATFace) *iShellCoveredFaces,
    CATBody *iResultBody) = 0;

  virtual void CompatibleCuttings(CATShell *iShell, CATBody *iBody) = 0;

  virtual void CompatibleCuttings(
    CATShell *iShell,
    CATBody *iBody,
    ListPOfListPOfCATEdge *ioNewIEListCorrOldIEList) = 0;

  virtual void DisconnectShell(
    CATShell *iShell,
    int iKeepInfo = 0,
    CATBody *iShellBody = NULL,
    CATBody *iSplittingBody = NULL,
    int iFullTreatment = 0) = 0;

  // info==1 car on va disconnecter les faces apres
  virtual void DisconnectShellEdges(CATShell *iShell, int iKeepInfo = 1) = 0;

  virtual void CleanDisconnectInfo(
    CATShell *iShell,
    int iSimplifyECrv = 0,
    CATBoolean iCleanLimitedToShell = FALSE) = 0;

  // wqo jan 09 calcul du positionnement pour une IE liant plus de 2 shells (CATSubdDisconnect.cpp)
  virtual void CleanMultipleIntersections(
    CATEdge *ipEdge,
    CATShell *ipShellCont,
    CATShell *ipShellInter,
    CATBoolean ContDisconnected,
    CATBoolean CorrParasite) = 0;

  // iBody1D doit etre un body compose seulement de domaine 1D
  // Retourne TRUE si chaque domaine de iBody1D est pose et disconnecte
  // un shell de iBody2D
  virtual CATBoolean BodyDisconnectable(CATBody *iBody2D, CATBody *iBody1D) = 0;

  virtual int ShellDisconnectable(
    CATShell *iShell,
    CATWire *iWire,
    CATCell **oWireStartSupportCell,
    CATCell **oWireEndSupportCell) = 0;

  virtual int ShellDisconnectable(CATShell *iShell, CATWire *iWire) = 0;

  virtual int ShellDisconnectable(
    CATShell *iShell,
    CATWire *iWire,
    CATBoolean &oStartWireDisconnecting,
    CATBoolean &oEndWireDisconnecting) = 0;

  // Operations sur les Wires
  virtual CATBody *IntersectWires(
    CATWire *iWire1,
    CATWire *iWire2,
    CATBody *iBody1,
    CATBody *iBody2,
    CATBoolean iConditionalEdgeIntersection = FALSE,
    CATBoolean iDetectTangentDesign = FALSE,
    CATBoolean iBooleanOperationFollow = FALSE,
    CATBoolean iConfusionStabilization = TRUE) = 0;

  virtual CATBody *IntersectWiresOnShell(
    CATShell *iSupportShell,
    CATWire *iWire1,
    CATWire *iWire2,
    CATBody *iBody1,
    CATBody *iBody2,
    CATBoolean iBooleanOperationFollow = FALSE) = 0;

  virtual CATBody *IntersectWiresWithSignedMode(
    CATWire *iWire1,
    CATWire *iWire2,
    CATBody *iBody1,
    CATBody *iBody2,
    CATBoolean iBooleanOperationFollow,
    CATBoolean iConfusionStabilization = TRUE) = 0;

  virtual void DisconnectWire(CATWire *iWire) = 0;

  virtual void DisconnectWireOnShell(CATWire *iWire) = 0;

  virtual CATBoolean CheckOverlapInEdgeCurve(
    CATGeoFactory *iFactory,
    CATBody *iShellBody,
    CATEdgeCurve *iEdgeCrv) = 0;

  //VoB contact check
  virtual void SetVoBContactCheck(CATVoBContactCheck *iContactCheck) = 0;

  virtual CATVoBContactCheck *GetVoBContactCheck() const = 0;

  virtual void CleanDisconnectInfo(CATWire *iWire) = 0;

  virtual CATFace *IsConfused(CATFace *iFace) = 0;

  // Operations Shell/Wire
  virtual CATBody *IntersectWireShell(
    CATWire *iWire,
    CATShell *iShell,
    CATBody *iWireBody,
    CATBody *iShellBody,
    CATBoolean iActivateDone = FALSE) = 0;

  virtual CATBody *IntersectWiresShells(
    CATBody *iBodyWire,
    CATBody *iBodyShell,
    CATWire *iWire = NULL,
    CATShell *iShell = NULL) = 0;

  // Creation de wires a partir de coupantes sur un domain (shell ou wire)
  virtual void CreateWiresFromCuttings(
    CATBody *iDomainBody,
    CATDomain *iDomain,
    CATBody *oWiresBody,
    CATBoolean iKeepCuttings = TRUE) = 0;

  virtual void CreateWiresFromWiresProjection(
    CATBody *iShellBody,
    CATShell *iShell,
    CATBody *iWiresBody,
    CATLISTP(CATVertex) *iPointSolutions,
    CATBoolean iPosageMode,
    CATBoolean iSuppressFlattenedEdges,
    int iSmartMode,
    CATBoolean iCleanDataProjection,
    CATBody *oResultBody) = 0;

  virtual void CreateWiresFromWiresProjection(
    CATBody *iShellBody,
    CATShell *iShell,
    CATBody *iWiresBody,
    CATLISTP(CATVertex) *iPointSolutions,
    CATBoolean iPosageMode,
    CATBoolean iSuppressFlattenedEdges,
    int iSmartMode,
    CATBoolean iCleanDataProjection,
    CATBody *oResultBody,
    double &oProjectDistance) = 0;

  virtual void SetRemoveArtefacts(int iRemoveArtefacts) = 0;

  // Pose de coupantes sur un shell a partir des edges lying-on d'un wire
  virtual CATTopLyingOnDiagnostic DuplicateLyingEdges(
    CATWire *iWire,
    CATShell *iShell,
    CATBoolean iCreateProjectionData,
    CATLISTP(CATFace) *iCoveredFaces,
    CATLISTP(CATEdge) *oEdgesToProject,
    CATLISTP(CATCell) *oInitialEdges,
    CATLISTP(CATCell) *oDuplicateEdges,
    CATLISTP(CATCell) *oContainerEdges,
    CATListOfDouble *oDuplicationDistance) = 0;

  // Simplification
  virtual void Simplify(CATBody *iBody) = 0;

  // Simplification de wire

  virtual void SetTraceMode(int mode = 1) = 0;

  //=================================
  virtual void SetAllCellsExpected(int iAllCellsExpected = 0) = 0;

  // 1 = journal complet
  // 0 = fonctionnement normal
  //=================================
  virtual void GetAllCellsExpected(int &iAllCellsExpected) = 0;

  // Acces aux tailles
  virtual void GetSizes(
    CATBody *body,
    int &nHighDomains,
    int &sHighDomains,
    int &nVolumes,
    int &sVolumes,
    int &nFaces,
    int &sFaces,
    int &nEdges,
    int &sEdges,
    int &nVertices,
    int &sVertices,
    int &nBEdges,
    int &sBEdges,
    int &nBVertices,
    int &sBVertices) = 0;

  // NE PAS UTILISER : cette methode va disparaitre !!!
  virtual void ForceActivate(CATBody *iBody) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopologicalOperator(); // -> delete can't be called
};

// Create
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopologicalOperator *CATPGMCreateTopologicalOperator(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iCreationBody);

#endif /* CATIPGMTopologicalOperator_h_ */
