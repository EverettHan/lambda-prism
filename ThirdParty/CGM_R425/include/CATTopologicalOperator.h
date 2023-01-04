/* -*-c++-*- */
#ifndef CATTopologicalOperator_h
#define CATTopologicalOperator_h
/* -*-c++-*- */
//===========================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : Topological toolkit.
//               
// 
//---------------------------------------------------------------------------
// Oct. 97   Creation                                            H. Kabla
// ...
// Jun. 98   Ajout d'une methode pour calculer le positionnement d'un point
//           par rapport a un ensemble ferme de faces.           L. Alt
// Jul. 98   Ajout de la possibilite de poser des attributs sur les faces
//           pour ne calculer les intersections face/face que si necessaire
//           lors de l'appel du booleen par le shell.            L. Alt
// Oct. 98   Modification de l'interface du positionnement point/face, qui 
//           prend maintenant une tolerance 3D en entree.        L. Alt
// Jan. 04 Parametre CATICGMUnknown* au lieu de CATBody*
//         pour CleanNewerUnused(...)                                     HCN
// Sep. 07 TassTagsForCVM()                                               FDN
// Jan. 09 CleanMultipleIntersections	                                    WQO
// Oct. 09 Ajout du CATContextForFastRun                                  WQO
// Feb. 12 Added method ComputeShellWireIntersection to support the
//         surfacic mode with contextual limits.                          G5S
// Jul. 13 Protected GetDisconnectedShellPartition has new argument - a 
//         selected list of edges to use for the positioning.  Existing
//         public methods set this extra argument to NULL.  New
//         public method to pass in a list of edges.                      G5S
// Oct. 13 Argument added to CompatibleCuttings to contain edges that we
//         want to track changes to.                                      G5S
// Nov. 19 inputbody for help in errors                                   JHN 
// Jun. 21 New method FluidRegionExtract() for when we use the disconnect
//         engine for Fluid Region Extraction, to enable surfacic lids.
//         We can use code in
//         NewTopologicalObjects, but call it from TopologicalOperators.  G5S
// Jun. 21 Enable simplification of lids when we use the disconnect 
//         engine.                                                        G5S
// Apr. 22 For lattice, enable us to keep volumes from the container in the result. G5S
//=============================================================================
#include "BOOPER.h"
#include "CATDomain.h"
#include "CATCellHashTable.h"
#include "ListPOfCATTopology.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATDomain.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATVertex.h"
#include "ListPOfListPOfCATFace.h"
#include "CATListPOfListPOfCATCell.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATWire.h"
#include "ListPOfCATVertexInVolume.h"
#include "CATListOfDouble.h"
#include "CATBooleanOperation.h"
#include "CATTopOperator.h"
#include "CATSubdIntersectingFunction.h"
#include "CATMathInline.h"
#include "CATBody.h"
#include "ListPOfListPOfCATEdge.h"
#include "CATListOfInt.h"
#include "CATVoBContactCheck.h"

#define InputHelpError

 
class CATGeoFactory;

class CATWire;
class CATEdge;
class CATFace;
class CATVolume;
class CATVertex;
class CATDomain;
class CATShell;
class CATLoop;
class CATTopCompatible2;

class CATSurface;
class CATSurParam;
class CATCrvParam;
class CATMathPoint;
class CATPointOnEdgeCurve;
class CATPointOnSurface;
class CATCGMJournalList;
class CATPCurve;
class CATEdgeCurve;
class CATCXBody; // purement interne
class CATSubdContextForFastRunExt;
class CATSubdMultiVolume;
class CATSubdSession;
class CATMathDirection;
class CATSubdArrayCXEdgeP;
class CATCGMAttrId;
class CATListPtrDynBoolSharedFaceData;

class CATFaceOrder;
class CATIntersectFilteringTools;
class CATAdaptiveHashTable;
class CATSubdParameters;

class ExportedByBOOPER CATTopologicalOperator : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopologicalOperator);
 public:

   CATTopologicalOperator(CATGeoFactory* iFactory, CATTopData* iData, CATBody* iCreationBody,
                          CATSubdContextForFastRunExt * ipCtxExt = NULL);

   // Deprecated
   CATTopologicalOperator(CATGeoFactory* iFactory, CATCGMJournalList* Report=NULL, CATBody* CreationBody=NULL);
   
   ~CATTopologicalOperator();

   INLINE void SetJournal(CATCGMJournalList* iJournal);

   void DumpCutting(CATVertex* iVertex);

   INLINE CATCGMJournalList* GetIntermediateJournal();

   INLINE void          SetVertexReporting(unsigned char iReporting);
   INLINE unsigned char GetVertexReporting();
   INLINE void          SetEdgeReporting(unsigned char iReporting);
   INLINE unsigned char GetEdgeReporting();
   INLINE void          SetFaceReporting(unsigned char iReporting);
   INLINE unsigned char GetFaceReporting();
   INLINE void          SetVolumeReporting(unsigned char iReporting);
   INLINE unsigned char GetVolumeReporting();

   /* @nodoc @nocgmitf
   * specific method for shell (to allow specific simplification and avoid  intersection between faces belonging to two different shells
   */
   void                 SetAttributeKeyForFaceVsVolPosition(int iAttributeKey,const CATCGMAttrId * iShellNewAttributeId );
   /* @nodoc @nocgmitf
   * specific method for shell (to allow specific simplification and avoid  intersection between faces belonging to two different shells
   */
   int                  GetAttributeKeyForFaceVsVolPosition();
   /* @nodoc @nocgmitf
   * specific method for shell (to allow specific simplification and avoid  intersection between faces belonging to two different shells
   */
   const CATCGMAttrId * GetAttributeId();

   INLINE void          SetFreezeResultBody(short iFreezeResultBody);
   INLINE short         GetFreezeResultBody();

   INLINE void          SetCreationBody(CATBody*iBody);
   INLINE CATBody     * GetCreationBody();

   INLINE void          SetNoSimplif(unsigned char iValue);
   INLINE void          SetNoSimplif_MergedCurves(short  iValue);
   INLINE unsigned char GetNoSimplif();
   INLINE short         GetNoSimplif_MergedCurves();
   INLINE void          SetNonManifoldReportDelayed(unsigned char iValue);
   INLINE unsigned char GetNonManifoldReportDelayed();
   // Surfacic cases
   INLINE void          SetSimplifOnlyModifiable(CATBoolean iSimplifOnlyModifiable);
   INLINE CATBoolean    GetSimplifOnlyModifiable();

   void                 SetIntersectingFunction(IntersectingFunction iFunction);
   void                 SetIntersectFilteringTools(CATIntersectFilteringTools * ipFilteringTools);

#ifdef InputHelpError
   INLINE void             SetOperatorCaller(CATTopOperator * iCallerOperator);
   INLINE CATTopOperator * GetOperatorCaller();
#endif

   INLINE void          SetLiveMode(CATBoolean iLiveMode);
   INLINE CATBoolean    GetLiveMode();
  
   // Operations booleennes
   CATBody * Inter(CATBody*iBody1, CATBody*iBody2, CATListPtrDynBoolSharedFaceData* ipListSharedFacesData = NULL);
   CATBody * Union(CATBody*iBody1, CATBody*iBody2, CATListPtrDynBoolSharedFaceData* ipListSharedFacesData = NULL);
   CATBody * Diff (CATBody*iBody1, CATBody*iBody2, CATListPtrDynBoolSharedFaceData* ipListSharedFacesData = NULL);
   CATBody * Delta(CATBody*iBody1, CATBody*iBody2, CATListPtrDynBoolSharedFaceData* ipListSharedFacesData = NULL);

   /** @nodoc @nocgmitf */
   void ExecuteBooleanOperation(CATSubdMultiVolume *& iMulti1, CATSubdMultiVolume *& iMulti2, ListPOfCATBody * iInputBodies = NULL, CATListPtrDynBoolSharedFaceData* ipListSharedFacesData = NULL);

   /** @nodoc @nocgmitf */
   CATBody * BooleanInternal(CATLISTP(CATBody)& iBodies1,
     CATLISTP(CATBody)& iBodies2,
     CATListPtrDynBoolSharedFaceData* ipListSharedFacesData = NULL);

   // Split Volume par Skin
   CATBody* SplitBySkin(CATBody* iBody, CATBody* iSkin, int iSideToKeep,
                        CATBoolean* oRelimitation = NULL, CATLISTP(CATCell)* oUnknownPositionCells = NULL);

   // Relimitation Skin par Volume
   CATBody* RelimitSkin(CATBody* iBody, CATBody* iSkin, int iSideToKeep);
   CATBody* RelimitWires(CATBody* iSolidBody, CATBody* iWiresBody, int iSideToKeep);
   CATBody* RelimitVIV(CATBody* iSolidBody, CATBody* iVIVBody, int iSideToKeep);

   // Sewing d'une skin sur un Volume
   CATBody* SewSkin(CATBody* iBody, CATBody* iSkin, int iSideToKeep);

   // Trim
   CATBody * Trim  (CATBody* iBody1, CATBody* iBody2, 
                    CATCell** iCellsToRemove      , int iNbCellsToRemove,
                    CATCell** iCellsToKeep = NULL , int iNbCellsToKeep = 0 ,
                    CATCell** iCellsToRemoveByAdjacent = NULL, CATCell** iCellsAdjacentForRemove = NULL, int iNbCellsToRemoveByAdjacent = 0,
                    CATCell** iCellsToKeepByAdjacent= NULL, CATCell** iCellsAdjacentForKeep = NULL, int iNbCellsToKeepByAdjacent = 0);
   CATBody * Trim  (CATLISTP(CATBody)& iBodies1, CATLISTP(CATBody)& iBodies2, 
                    CATCell** iCellsToRemove      , int iNbCellsToRemove,
                    CATCell** iCellsToKeep = NULL , int iNbCellsToKeep = 0,
                    CATCell** iCellsToRemoveByAdjacent = NULL, CATCell** iCellsAdjacentForRemove = NULL, int iNbCellsToRemoveByAdjacent = 0,
                    CATCell** iCellsToKeepByAdjacent = NULL, CATCell** iCellsAdjacentForKeep = NULL, int iNbCellsToKeepByAdjacent = 0);

   CATBody * Trim  (CATLISTP(CATBody)& iBodies1, CATLISTP(CATBody)& iBodies2,
                    CATCell** iCellsToRemove   , int iNbCellsToRemove,
                    CATCell** iCellsToKeep     , int iNbCellsToKeep,
                    CATCell** iCellsToRemoveByAdjacent,
                    CATCell** iCellsAdjacentForRemove,
                    int     * iNbCellsForRemoveSelection,
                    int       iNbSelectionsByRemoveAdjacency,
                    int       iNbCellsToRemoveByAdjacent,
                    CATCell** iCellsToKeepByAdjacent,
                    CATCell** iCellsAdjacentForKeep,
                    int     * iNbCellsForKeepSelection,
                    int       iNbSelectionsByKeepAdjacency,
                    int       iNbCellsToKeepByAdjacent);

   // services atomiques du Trim.
   CATBody * CutBodies(CATBody* iBody1, CATBody* iBody2, 
                       CATLISTP(CATCell)& oListCells1,
                       CATLISTP(CATCell)& oListCells2, 
                       CATLISTP(CATCell)& oListCells12);
   CATBody * CutBodies(CATLISTP(CATBody)& iBodies1, CATLISTP(CATBody)& iBodies2, 
                       CATLISTP(CATCell)& oListCells1,
                       CATLISTP(CATCell)& oListCells2, 
                       CATLISTP(CATCell)& oListCells12);
   void      GetAdjacentTrimmedCells(CATCell* iCell, CATLISTP(CATCell)& oListAdjacentCells);
   void      ToggleSelection(CATCell* iCell);
   void      BuildTrimmedBody(CATBody* iBody,CATLONG32 iComplementary=0);
   void      BuildTrimmedAndIntermediateBodies(CATBody* iBody, CATLISTP(CATBody)& iBodies1, CATLISTP(CATBody)& iBodies2,
                                               CATLISTP(CATCell)& iListCells1,
                                               CATLISTP(CATCell)& iListCells2, 
                                               CATLISTP(CATCell)& iListCells12,
                                               CATBooleanOperation iOperation,
                                               CATBody* & oIntermediateBody);
  CATBody *  Duplicate(CATBody *Body, short iDuplicateIS,
                       CATLISTP(CATCell)& iListCells1, CATLISTP(CATCell)& iListCells2, CATLISTP(CATCell)& iListCells12,
                       CATLISTP(CATCell)& ioNewListCells1,CATLISTP(CATCell)& ioNewListCells2,CATLISTP(CATCell)& ioNewListCells12);

  /** @nodoc @nocgmitf */
  void       FinalizeOutput(CATBody * iBody);

  /** @nodoc @nocgmitf */
  INLINE CATFaceOrder * GetFaceOrdering();

  /** @nodoc @nocgmitf */
  CATFaceOrder * CreateFaceOrdering();

   // RemoveLump
   CATBody * RemoveLump(CATBody* iBody, 
                        CATCell** iCellsToRemove      , int iNbCellsToRemove,
                        CATCell** iCellsToKeep = NULL , int iNbCellsToKeep = 0);

   // y a-t-il une intersection entre deux Bodies ?
   int IsIntersecting(CATBody* iBody1, CATBody* iBody2);
   int IsClashing(CATBody* iBody1, CATBody* iBody2, int iTestVolumeInclusion = TRUE);
   int IsIntersecting(CATShell* iShell1, CATShell* iShell2, CATBody* iBody1, CATBody* iBody2);
   
   // Outils Divers
   CATBody   * CloneBody  (CATBody *iBody);
   CATBody   * CloneBodies(CATBody **ippBody, int iNb);
   CATDomain * CloneDomain(CATBody*iBody, CATDomain*iDomain);
  
   //............................................
   // Outils De Nettoyage Recursif du Body :
   //    des cellules non partagees
   //    avec gestion du journal topo
   void  RemoveBody  (CATBody *iBody);
   void  RemoveCell  (CATCell *iCell);
   void  RemoveCellFromBody  (CATCell *iCell,CATBody*iBody);
   // nettoyage des BoundingBoxes stockees
   void  ResetBoxes  (CATBody*iBody);
   //............................................
   void  FullDuplicateCell(CATCell *iCell,CATBody* inBody,CATCell *&iDuplicatedCell);
   void  TouchLoops(CATBody * iBody);
   //............................................

   
   // Operateur de positionnement
   CATLocation CalculatePosition(CATVolume*iVolume, const CATMathPoint&iMathPoint);
   // Nouvelle interface avec tolerance 3D (si NULL, c'est la resolution de modele qui est prise
   // par defaut).
   CATLocation CalculatePosition(CATFace*iFace, const CATSurParam&iSurParam, double * i3DToleranceOnBoundary=NULL);
   // autre interface renvoyant l'Edge sur laquelle est pose le SurParam s'il est sur le bord de la face.
   CATLocation CalculatePosition(CATFace*iFace, const CATSurParam&iSurParam, CATEdge ** oBorder, CATCrvParam & oParamOnBorder, 
                                 double * i3DToleranceOnBoundary=NULL);
   
   // Operateurs pose de coupantes
   void SetCutting(CATFace* iCutFace, CATEdge* iCutEdge, CATSide iCutEdgeSide, CATVertex* iCuttingVertex, 
                   CATPointOnEdgeCurve* iPOECOnCutEdge, CATEdge* iCuttingEdgeBoundedByCuttingVertex = NULL);
   void SetCutting(CATFace* iCutFace, CATVertex* iCutVertex, CATVertex* iCuttingVertex,
                   CATEdge* iCuttingEdgeBoundedByCuttingVertex = NULL);
   void SetCutting(CATShell* iCutShell, CATFace* iCutFace, CATEdge* iCutEdge, CATSide iCutEdgeSide,
                   CATEdge* iCuttingEdge, CATCell* iCuttingStartSupport, CATCell* iCuttingEndSupport,
                   CATPointOnEdgeCurve* iStartPOECOnCutEdge, CATPointOnEdgeCurve* iEndPOECOnCutEdge);
   void SetCutting(CATFace* iCutFace, CATEdge* iCuttingEdge, CATPCurve* iCuttingPCurve);

   void InvertCuttingPositionning(CATFace* iCutFace, CATEdge* iCuttingEdge);
   void UnsetCutting(CATFace* iCutFace, CATEdge* iCutEdge, CATSide iCutEdgeSide, CATVertex* iCuttingVertex);
   void UnsetCutting(CATFace* iCutFace, CATVertex* iCutVertex, CATVertex* iCuttingVertex);
   void UnsetCutting(CATEdge* iCutEdge, CATEdge* iCuttingEdge, CATShell* iCutShell = NULL);
   void UnsetCutting(CATFace* iCutFace, CATEdge* iCuttingEdge);

   void UnsetCutting(CATShell* iCutShell, CATFace* iCuttingFace);
   void UnsetCutting(CATShell* iCutShell, CATWire* iCuttingWire);
   void UnsetCutting(CATShell* iCutShell, CATEdge* iCuttingEdge);
   void UnsetCutting(CATShell* iCutShell, CATVertex* iCuttingVertex);

   void UnsetCutting(CATWire* iCutWire, CATVertex* iCuttingVertex);

   // on passe le body pour activation, il faudrait le faire dans tous les operateurs Set et Unset.
   int  IsCutting(CATBody* iShellBody, CATShell* iCutShell, CATWire* iCuttingWire, int iCompletely = 0);
   int  IsCutting(CATBody* iShellBody, CATShell* iCutShell, CATEdge* iCuttingEdge);

   // Dump des cutting
   void DumpCutting(CATFace *iFace, CATLISTP(CATCell) &oCuttingEdges);
   void DumpCutting(CATFace *iFace, CATEdge *iEdge, CATLISTP(CATCell) &oCuttingCells);
   void DumpCutting(CATFace *iFace, CATVertex *iVertex, CATLISTP(CATCell) &oCuttingCells);

   // intersecte des coupantes entre elles 
   void IntersectCuttingEdges(CATFace* iCutFace, CATEdge* iCuttingEdge1, CATEdge* iCuttingEdge2, 
                              int &oNbIntersections, CATVertex*** oIntersections, 
                              int withConfusion = 0, int iConditionalEdgeIntersection = 0,
                              int *oNbConfusionEdges=NULL, CATEdge*** oConfusionEdges=NULL);
   CATEdge** SplitCuttingEdge(CATFace* iCutFace, CATEdge *iCoupee, int &oNbEdges, CATLocation ** oLocations,
                              int iPreserveModifiableVertices = 0);

   // renvoie 1 si l'intersection est un zero franc, 0 sinon
   int  RetrieveCuttingStatus(CATFace* iCutFace, CATEdge* iCutEdge, CATSide iCutEdgeSide, CATVertex* iCuttingVertex);
   int  RetrieveCuttingStatus(CATFace* iCutFace, CATVertex* iCutVertex, CATVertex* iCuttingVertex);
   int  RetrieveCuttingStatus(CATFace* iCutFace, CATVertex* iCuttingVertex);

   // Operateurs de decoupe
   CATCell   * GetCellSupport (CATCell* iCell, CATCell* iSupportOwningCell = NULL, int* oNbContainers = NULL);
   static void GetAllCellSupports(CATCell* iCell, CATLISTP(CATCell)& oListOfCells, int iOnlyDirect = 0);
   void        SplitWire      (CATWire *iWire, CATFace *iSplittingFace,
                               int &oNbEdges, CATLocation ** oLocations, 
                               int iWithConfusion);
   CATEdge **  SplitEdge      (CATEdge *iCutEdge, CATFace *iSplittingFace, 
                               int &oNbEdges, CATLocation ** oLocations, 
                               int iWithConfusion = 0, int iConditionalEdgeIntersections = 0,
                               int iPreserveModifiableVertices = 0, CATLoop* iLoopNotToIntersect = NULL, 
                               int iStabilizeConfusion = 0, int iUpdateFaceTouch = 1);
   CATEdge **  SplitEdge      (CATEdge *iCutEdge, const CATCrvParam& iParam, int &oNbEdges);
   CATEdge **  SplitEdge      (CATEdge *iCutEdge, CATPointOnEdgeCurve* iPoec, int &oNbEdges);

   void        SplitVertex    (CATBody* iFaceBody, CATFace *iFace, CATVertex *iVertex,
                               CATPointOnSurface *iPos, CATLocation &oLocation);
   void        SplitVertex    (CATBody* iEdgeBody, CATEdge *iEdge, CATVertex *iVertex,
                               CATPointOnEdgeCurve *iPoec, CATLocation &oLocation);

   void        SplitSingleEdgeWire(CATWire *iWire);

   CATBody   * IntersectFaces (CATFace *iFace1, CATFace *iFace2);
   CATFace  ** DisconnectFace (CATFace* iFace, int& oNbFaces, CATBody* iBody, 
                               CATShell* iContainingShell = NULL, int iKeepInfo = 0,
                               CATLISTP(CATEdge)* oFlattenedEdges = NULL);
   void        CleanDisconnectInfo(CATEdge* iEdge, int iCleanVertices=0, int iCleanLoop=1);
   int         SimplifyECrvs(CATLISTP(CATEdge)& iSetOfEdgesToSimplify, CATBody* iEdgesBody, int iKeepCanonicity=0);
   int         SimplifyCompatibleECrvs(CATBody* iBodyToSimplify, int iKeepCanonicity=0);
   void        SetOldSubdivide(int iOldSubdivide);

   void        CleanScar(CATEdge* iEdge);
   void        CleanDisconnectInfo(CATVertex* iVertex);


   void        RecalculateTouched(CATBody* iBody);  
   void        RecalculateTouched(CATFace* iFace); 
   void        RecalculateTouched(CATShell* iShell);
   void        RecalculateTouched(CATWire* iWire);

   // HKL 01 12 98 splits two faces
   void        MutuallySplitFaces(CATFace * iFace1, CATFace * iFace2,
                                  ListPOfCATFace & oFacesFrom1, 
                                  ListPOfCATFace & oFacesFrom2, 
                                  ListPOfCATFace & oFacesFrom12);
  
   // calcule la peau a laquelle appartient la face sur le shell par propagation
   CATFace  ** PropagatePositionVsDisconnector(CATFace* iFace, int& oNbFaces, CATShell* iContainingShell,CATBody * DisconnectBody=NULL,
                                               CATLocation* oLocation = NULL, CATBody* iWires = NULL, 
                                               CATLONG32 * ConfusionRelativeOri = NULL, CATLONG32 * FlattenedIS=NULL, CATBoolean iSewingSelection = FALSE,
                                               ListPOfCATCell * iPositioningVolumes = NULL); 

   void        PropagatePositionVsDisconnector(CATWire *iWire, CATEdge *iEdge,
                                               CATBoolean iStopAtWireClosure,
                                               CATBoolean iThrowExceptionOnInconsistentPosition,
                                               CATLISTP(CATEdge)& oSetOfEdges, CATLocation& oLocation,
                                               CATBoolean & oIncompatiblePosition);

   /** @nodoc @nocgmitf */
   CATFace  ** GetPropagationResult(CATFace * iFace, int& oNbFaces, CATLocation * oLocation, CATLONG32* oNbScarEdges, CATEdge*** oScarEdges);
                  
   // Decompositions en IS avec positionnement Vs. 3D Disconnector, then, if it's unknown, 
   // CATSubdIntersectionSkin::RetrieveScarPosition().
   void        GetDisconnectedShellPartition(CATShell                 * iDisconnectedShell,
                                             CATBoolean                 iErrorOnIncompatiblePositions,
                                             CATLISTP(ListPOfCATFace) & ioConnectedSetsOfFaces,
                                             CATListOfInt             * ioPositions,
                                             CATListOfInt             * ioRelativeOrientations);

   // Decompositions en IS avec positionnement Vs. Wires
   void        GetDisconnectedShellPartition(CATShell                 * iDisconnectedShell,
                                             CATBody                  * iWiresBody,
                                             CATBoolean                 iErrorOnIncompatiblePositions,
                                             CATLISTP(ListPOfCATFace) & ioConnectedSetsOfFaces,
                                             CATListOfInt             * ioPositions);

   /** @nodoc @nocgmitf
       Function for splitting the shell into sets of connected faces with positioning using 3D Disconnector, then,
       if it's still unknown, CATSubdIntersectionSkin::RetrieveScarPositionWithSelectedIEs(). */
   void        GetDisconnectedShellPartition(CATShell                 * iDisconnectedShell,
                                             CATBoolean                 iErrorOnIncompatiblePositions,
                                             CATLISTP(ListPOfCATFace) & ioConnectedSetsOfFaces,
                                             CATListOfInt             * ioPositions,
                                             ListPOfCATEdge           * iSelectedIEsForPositioning, 
                                             CATListOfInt             * ioRelativeOrientations);

   void        RemoveConfusedFaceLink(CATShell * iDisconnectedShell);

   void DisconnectEdge (CATEdge*iEdge);
   void DestroyCell    (CATCell*iCell);
   void DestroyEdge    (CATEdge* iEdge, int iDestroyDependancies = 0, CATFace* iSurroundingFace = NULL,
                        CATBoolean iUnlinkUselessGeometry = FALSE, CATBoolean iDestroyLyingOn = TRUE);
   void  DestroyVertex  (CATVertex* iVertex);

   void          MergeVertices(	CATVertex                * iVertexReceiver,
                                CATVertex                * iVertexEmitter,
                                int                        iKeepAllPoecs = 0,
                                CATBody                  * iWorkingBody = NULL,
                                CATLISTP(CATTopology)    * iListFederator = NULL);


   void          MergeEdges(	CATEdge                 *  iEdgeReceiver,
                              CATEdge                 *  iEdgeEmitter,
                              int                        inversion = 0,
                              CATBody                  * iWorkingBody = NULL,
                              CATLISTP(CATTopology)    * iListFederator = NULL);



   CATEdgeCurve* ComputeMerge   (CATEdge* iEdge1, CATEdge* iEdge2, double iTolerance, int inversion = 0);

   void  ReportContents (CATEdge*iEdge);

   CATBody* IntersectShells(CATShell* iShell1, CATShell* iShell2, CATBody* iBody1, CATBody* iBody2, int iKeepSign = 0); 

   // Si iResultBody est non nul, le resultat de l'intersection (et donc de la methode) sera ce body
   CATBody* IntersectShells(CATShell* iShell1, CATShell* iShell2, CATBody* iBody1, CATBody* iBody2,
                            int iCreateWire  , int iKeepSign, 
                            int* oNbWire, CATEdge *** oEdgesWire, int ** oNbEdgesInWire, 
                            int ** oNbConnectedExtremities,
                            CATVertex *** oStartingFreeVertices = (CATVertex***)0,
                            CATVertex *** oEndingFreeVertices   = (CATVertex***)0,
                            CATLISTP(CATFace) * iShell1CoveredFaces = (ListPOfCATFace*)0,
                            CATLISTP(CATFace) * iShell2CoveredFaces = (ListPOfCATFace*)0,
                            CATBody* iResultBody = (CATBody*) 0 );
 
   CATBody* IntersectShells(CATBody* iBody1, CATBody* iBody2, CATShell* iShell1, CATShell* iShell2, int iKeepSign = 0,
                            ListPOfListPOfCATEdge * oConfusionBorders = NULL); 

   CATBody* IntersectShellWire(CATShell* iShell, CATWire* iWire, CATBody* iBody1, CATBody* iBody2,
                               int iCreateWire, int iKeepSign, int* oNbWire, CATEdge *** oEdgesWire, int ** oNbEdgesInWire, 
                               int ** oNbConnectedExtremities, CATVertex *** oStartingFreeVertices, CATVertex *** oEndingFreeVertices,
                               CATLISTP(CATFace) * iShellCoveredFaces, CATBody* iResultBody);

   void        CompatibleCuttings(CATShell* iShell, CATBody* iBody);

   void        CompatibleCuttings(CATShell* iShell, CATBody* iBody, 
                                  ListPOfListPOfCATEdge *ioNewIEListCorrOldIEList);
   
   void        DisconnectShell     (CATShell* iShell, int iKeepInfo = 0, CATBody* iShellBody = NULL, CATBody* iSplittingBody = NULL, int iFullTreatment=0);
   // info==1 car on va disconnecter les faces apres
   void        DisconnectShellEdges(CATShell* iShell, int iKeepInfo = 1); 
   void        CleanDisconnectInfo (CATShell* iShell, int iSimplifyECrv = 0, CATBoolean iCleanLimitedToShell = FALSE);
   // wqo jan 09 calcul du positionnement pour une IE liant plus de 2 shells (CATSubdDisconnect.cpp)
   void        CleanMultipleIntersections(CATEdge* ipEdge, CATShell* ipShellCont, CATShell* ipShellInter,
                                          CATBoolean ContDisconnected, CATBoolean CorrParasite);
   // iBody1D doit etre un body compose seulement de domaine 1D
   // Retourne TRUE si chaque domaine de iBody1D est pose et disconnecte
   // un shell de iBody2D
   CATBoolean  BodyDisconnectable  (CATBody* iBody2D, CATBody* iBody1D);

   int         ShellDisconnectable (CATShell* iShell, CATWire* iWire, 
                                    CATCell** oWireStartSupportCell, CATCell** oWireEndSupportCell);
   int         ShellDisconnectable (CATShell* iShell, CATWire* iWire);
   int         ShellDisconnectable (CATShell* iShell, CATWire* iWire, 
                                    CATBoolean &oStartWireDisconnecting,
                                    CATBoolean &oEndWireDisconnecting); 

 
   // Operations sur les Wires
   CATBody   * IntersectWires(CATWire * iWire1, CATWire * iWire2, CATBody* iBody1, CATBody* iBody2,
                              CATBoolean iConditionalEdgeIntersection = FALSE, 
                              CATBoolean iDetectTangentDesign = FALSE, 
                              CATBoolean iBooleanOperationFollow = FALSE,
                              CATBoolean iConfusionStabilization = TRUE);
   CATBody   * IntersectWiresOnShell(CATShell * iSupportShell, 
                                     CATWire * iWire1, CATWire * iWire2, CATBody* iBody1, CATBody* iBody2, 
                                     CATBoolean iBooleanOperationFollow = FALSE);
   CATBody   * IntersectWiresWithSignedMode(CATWire * iWire1, CATWire * iWire2, CATBody* iBody1, CATBody* iBody2, 
                                            CATBoolean iBooleanOperationFollow, CATBoolean iConfusionStabilization=TRUE);

   void        DisconnectWire(CATWire * iWire);
   void        DisconnectWireOnShell(CATWire * iWire);
   CATBoolean  CheckOverlapInEdgeCurve(CATGeoFactory *iFactory, CATBody * iShellBody, CATEdgeCurve * iEdgeCrv);

   /** @nodoc @nocgmitf */
   void DisplayWarningOnFacesWithImpasses(CATCXBody * iBody);

   /** @nodoc @nocgmitf */
   void DisplayWarningOnNonManifoldEdges(CATSubdArrayCXEdgeP & iNonManifoldEdges);

   /** @nodoc @nocgmitf */
   void OpenBooleanEnvironment();

   /** @nodoc @nocgmitf */
   void CloseBooleanEnvironment();

   //VoB contact check
   void SetVoBContactCheck(CATVoBContactCheck * iContactCheck);
   CATVoBContactCheck * GetVoBContactCheck() const;
   
   /** @nodoc @nocgmitf */
   void SetVolumicSimplification(short noVolumicSimplification);

   /** @nodoc @nocgmitf */
   short GetVolumicSimplification() const;

   // Fluid Region extract
   CATBody * FluidRegionExtract(CATBody* iContainersBody, CATBody* iLidsBody, CATBoolean iToKeepContainers = FALSE, CATBoolean iSimplifyLids = FALSE); 

protected:
   void        DisconnectWireWithSignedMode(CATWire * iWire);
   void CompatibleFace(CATTopData * iTopData,CATBody * ibody1,CATBody * ibody2,CATTopCompatible2 *& oDisconnectOperator, CATBody *& oResult);
   void BuildSimplification(CATTopData * iTopData,CATBody * ibody1,CATBody * ibody2,CATTopCompatible2 *DisconnectOperator, CATBody *& resultBody);

public:
   void        CleanDisconnectInfo(CATWire* iWire);


   CATFace   * IsConfused(CATFace * iFace);

   // Operations Shell/Wire
   CATBody   * IntersectWireShell(CATWire * iWire, CATShell * iShell, CATBody* iWireBody, CATBody* iShellBody, CATBoolean iActivateDone = FALSE);
   CATBody   * IntersectWiresShells(CATBody* iBodyWire, CATBody* iBodyShell, CATWire* iWire=NULL, CATShell* iShell=NULL);  

   // Creation de wires a partir de coupantes sur un domain (shell ou wire)
   void        CreateWiresFromCuttings(CATBody * iDomainBody, CATDomain  * iDomain,
                                       CATBody * oWiresBody,  CATBoolean   iKeepCuttings = TRUE);

   void        CreateWiresFromWiresProjection(CATBody  * iShellBody , CATShell * iShell, 
                                              CATBody  * iWiresBody , 
                                              CATLISTP(CATVertex)* iPointSolutions,
                                              CATBoolean iPosageMode, CATBoolean iSuppressFlattenedEdges, int iSmartMode,
                                              CATBoolean iCleanDataProjection,
                                              CATBody  * oResultBody);

   void        CreateWiresFromWiresProjection(CATBody  * iShellBody , CATShell * iShell, 
                                              CATBody  * iWiresBody , 
                                              CATLISTP(CATVertex)* iPointSolutions,
                                              CATBoolean iPosageMode, CATBoolean iSuppressFlattenedEdges, int iSmartMode,
                                              CATBoolean iCleanDataProjection,
                                              CATBody  * oResultBody,
                                              double & oProjectDistance);

   void        SetRemoveArtefacts( int iRemoveArtefacts );

   // Pose de coupantes sur un shell a partir des edges lying-on d'un wire
   CATTopLyingOnDiagnostic DuplicateLyingEdges(CATWire * iWire, CATShell * iShell, CATBoolean iCreateProjectionData, 
                                               CATLISTP(CATFace) * iCoveredFaces,
                                               CATLISTP(CATEdge) * oEdgesToProject,
                                               CATLISTP(CATCell) * oInitialEdges,
                                               CATLISTP(CATCell) * oDuplicateEdges,
                                               CATLISTP(CATCell) * oContainerEdges,
                                               CATListOfDouble   * oDuplicationDistance);

   // Simplification
   void Simplify    (CATBody*iBody);
   // @nocgmitf Not implemented!
   void SimplifyNew (CATBody*iBody);

   // Simplification de wire
/*   void Simplify(CATBody    * iTargetBody,
                 CATWire    * iWireToSimplify,
                 CATSurface * iWireSurface,
                 CATBoolean   iKeepClosurePosition,
                 CATBoolean & oHasSimplified);*/

   INLINE void SetTraceMode(int mode=1);

   //=================================
   void SetAllCellsExpected(int iAllCellsExpected=0 );
      // 1 = journal complet
      // 0 = fonctionnement normal
   //=================================
   INLINE void GetAllCellsExpected(int & iAllCellsExpected );
   // Acces aux tailles
   void GetSizes(CATBody * body,
                 int &nHighDomains, int &sHighDomains,
                 int &nVolumes  , int &sVolumes,
                 int &nFaces    , int &sFaces,
                 int &nEdges    , int &sEdges,
                 int &nVertices , int &sVertices,
                 int &nBEdges   , int &sBEdges,
                 int &nBVertices, int &sBVertices);
   // Acces au Contexte du Fast Update @nocgmitf
   INLINE void SetSubdContextForFastRunExt(CATSubdContextForFastRunExt * ipCtxExt);
   //  @nocgmitf
   INLINE CATSubdContextForFastRunExt * GetSubdContextForFastRunExt();

   // NE PAS UTILISER : cette methode va disparaitre !!!
   void ForceActivate(CATBody *iBody);

#ifdef InputHelpError
   void SetInputBodies(const ListPOfCATBody &ListOfCopyInputBodies,const ListPOfCATBody &ListOfNoCopyInputBodies);
   void ResetInputBodies();
   void ReadInputBodies(ListPOfCATBody &oListOfCopyInputBodies, ListPOfCATBody &oListOfNoCopyInputBodies);
#endif
  //-----------------------------------------------------------------------
  //- Gestion DEBUG
  //-----------------------------------------------------------------------  
  static CATString _OperatorId;
  /** @nodoc @nocgmitf */
  const CATString * GetOperatorId();


 protected:
   short               _traceMode;
   unsigned char       _mustReportVertices;
   unsigned char       _mustReportEdges;
   unsigned char       _mustReportFaces;
   unsigned char       _mustReportVolumes;
   CATCGMJournalList*  _IntermediateReport;

   void CreateWiresFromCuttings(CATBody * iWireBody,  CATWire    * iWire,
                                CATBody * oWiresBody, CATBoolean   iKeepCuttings);
   void CreateWiresFromCuttings(CATBody * iShellBody, CATShell   * iShell,
                                CATBody * oWiresBody, CATBoolean   iKeepCuttings);

 private:
   CATBody * _IntersectShells(
     CATBody * iBody1,
     CATBody * iBody2,
     int * oNbWire,
     CATEdge *** oEdgesWire,
     int ** oNbEdgesInWire,
     int ** oNbConnectedExtremities,
     int iKeepSign = 0,
     CATShell * iShell1 = NULL,
     CATShell * iShell2 = NULL,
     ListPOfListPOfCATEdge * oConfusionBorders = NULL,
     CATLISTP(CATFace) * iShell1CoveredFaces = NULL,
     CATLISTP(CATFace) * iShell2CoveredFaces = NULL,
     int iCreateWire = 1,
     CATVertex *** oStartingFreeVertices = NULL,
     CATVertex *** oEndingFreeVertices = NULL,
     CATBody * iResultBody = NULL);

   void FillSubdParameters(CATSubdParameters * iParameters);

   // internes du booleen
   int CompatibleDomainDomain(CATDomain* iDomain, CATLISTP(CATDomain)&iListDomains,
                               CATLISTP(CATDomain)&oListDomains, 
                               CATLISTP(CATCell) &oc1, CATLISTP(CATCell) &oc2, CATLISTP(CATCell) &oc12,
                               int iKeepInfo = 0);
   int CompatibleCellDomain(CATLISTP(CATCell)&, CATDomain*, 
                             CATLISTP(CATCell)&, CATLISTP(CATCell)&, CATLISTP(CATCell)&, int iKeepInfo = 0);
   CATEdgeCurve* _MergeEdges    (CATEdge* iEdge1, CATEdge* iEdge2, double iTolerance, int inversion = 0);
   
   // Internes des Outils Divers
   CATVolume   * CloneVolume  (CATBody*, CATVolume  *);

   // Internes Booleen
   CATBody * CompatibleInter(CATBody*, CATBody*);
   CATBody * CompatibleUnion(CATBody*, CATBody*);
   CATBody * CompatibleDiff (CATBody*, CATBody*);
   CATBody * CompatibleDelta(CATBody*, CATBody*);

   // Internes BuildTrimmedAndIntermediateBodies
   void      BuildTrimmedAndIntermediateBodies(CATBody *iBody, CATDomain* iManifold, 
                                               CATLISTP(CATCell)& iListCells1,
                                               CATLISTP(CATCell)& iListCells2, 
                                               CATLISTP(CATCell)& iListCells12,
                                               CATBooleanOperation iOperation,
                                               CATBody* & oIntermediateBody);
   int _AttributeKeyForFaceVsVolPosition;
   const CATCGMAttrId *  _AttributeID;
   
   short _FreezeResultBody;
   unsigned char _NoSimplif;
   unsigned char _NonManifoldReportDelayed;
   CATBoolean    _SimplifOnlyModifiable;
   short        _NoSimplif_MergedCurves;
   short      	_VolumicSimplif;
   CATIntersectFilteringTools * _pFilteringTools;

   CATBoolean _LiveMode;

   int   _AllCellsExpected;  //celltrack

 protected:
   CATCXBody * GetCreationBodyOfLastCentury(const char Id[]);

   void        GetDisconnectedShellPartition(CATShell                 * iDisconnectedShell,
                                             CATBody                  * iWiresBody,
                                             CATBoolean                 iErrorOnIncompatiblePositions,
                                             CATLISTP(ListPOfCATFace) & ioConnectedSetsOfFaces,
                                             CATListOfInt             * ioPositions,
											 ListPOfCATEdge           * iSelectedIEsForPositioning, 
                                             CATListOfInt             * ioRelativeOrientations);

   void        GenerateSubWiresVsVolumes(CATCXBody * iSolidBody,
                                         CATCXBody * iDisconnectedWiresBody,
                                         int         iSideToKeep,
                                         CATCXBody * ioResultBody);
   int                _OldSubdivide;

 private:

   CATBody* const      _CreationBody;

   CATCXBody*         _BodyIsNeededButNoCreationBodyHasBeenSpecified;

   // Context pour le Fast Update
   CATSubdContextForFastRunExt * _pCtxExt;

   CATFaceOrder * _FaceOrdering;

   CATSubdSession * _BooleanSession;

   // VoB boolean contact check
   CATVoBContactCheck       * _VoBContactCheck;

   int _RemoveArtefacts;

#ifdef InputHelpError
   CATTopOperator * _OperatorCaller;
   ListPOfCATBody * _ListOfCopyInputBodies;
   ListPOfCATBody * _ListOfNoCopyInputBodies; 
#endif

 
 

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATTopologicalOperator(const CATTopologicalOperator &iCopy);
  CATTopologicalOperator& operator=(const CATTopologicalOperator &iCopy);

};

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================

INLINE void CATTopologicalOperator::SetCreationBody(CATBody * iCreationBody)
{
  if ( _CreationBody != iCreationBody )
  {
    if ( _CreationBody ) _CreationBody->Release();
    *((CATBody **)&_CreationBody) = iCreationBody;
    if ( _CreationBody ) _CreationBody->AddRef();
  }
}

INLINE CATBody * CATTopologicalOperator::GetCreationBody ()
{
   return _CreationBody;
}

INLINE void CATTopologicalOperator::GetAllCellsExpected(int & iAllCellsExpected)
{
   iAllCellsExpected=_AllCellsExpected;
   return;
}

//-------------------------------------------------------
// Oct. 09  Acces au Contexte du Fast Update          WQO
//-------------------------------------------------------
INLINE void CATTopologicalOperator::SetSubdContextForFastRunExt(CATSubdContextForFastRunExt * ipCtxExt)
{
  _pCtxExt = ipCtxExt;
  return;
}
INLINE CATSubdContextForFastRunExt * CATTopologicalOperator::GetSubdContextForFastRunExt()
{
  return _pCtxExt;
}

// WQO June 10 Reordonnanceur de faces pour plus de stabilite
INLINE CATFaceOrder * CATTopologicalOperator::GetFaceOrdering()
{
  return _FaceOrdering;
}

INLINE CATCGMJournalList*  CATTopologicalOperator::GetIntermediateJournal()
{
  return _IntermediateReport;
}

INLINE void CATTopologicalOperator::SetJournal(CATCGMJournalList * iJournal)
{
   CATTopOperator::SetJournal(iJournal);
}

INLINE void CATTopologicalOperator::SetVertexReporting(unsigned char report)
{ 
   _mustReportVertices = report;
}

INLINE void CATTopologicalOperator::SetEdgeReporting(unsigned char  report)
{ 
   _mustReportEdges = report;
}

INLINE void CATTopologicalOperator::SetFaceReporting(unsigned char  report)
{ 
   _mustReportFaces = report;
}

INLINE void CATTopologicalOperator::SetVolumeReporting(unsigned char  report)
{
   _mustReportVolumes = report;
}


INLINE void CATTopologicalOperator::SetNonManifoldReportDelayed(unsigned char iDelayed)
{ 
   _NonManifoldReportDelayed = iDelayed;
}

INLINE unsigned char CATTopologicalOperator::GetNonManifoldReportDelayed()   
{
   return _NonManifoldReportDelayed;
}

INLINE unsigned char CATTopologicalOperator::GetVertexReporting()   
{
   return _mustReportVertices;
}

INLINE unsigned char CATTopologicalOperator::GetEdgeReporting()   
{
   return _mustReportEdges;
}

INLINE unsigned char CATTopologicalOperator::GetFaceReporting()   
{
   return _mustReportFaces;
}

INLINE unsigned char CATTopologicalOperator::GetVolumeReporting()
{
   return _mustReportVolumes;
}

INLINE short CATTopologicalOperator::GetFreezeResultBody()
{ 
   return _FreezeResultBody;
}

INLINE void CATTopologicalOperator::SetFreezeResultBody(short iFreezeResultBody)
{ 
   _FreezeResultBody = iFreezeResultBody;
}

INLINE void CATTopologicalOperator::SetNoSimplif(unsigned char iNoSimplif)
{ 
   _NoSimplif = iNoSimplif;
}

INLINE void CATTopologicalOperator::SetNoSimplif_MergedCurves(short iNoSimplif)
{ 
  _NoSimplif_MergedCurves = iNoSimplif;
}

INLINE unsigned char CATTopologicalOperator::GetNoSimplif()   
{
   return _NoSimplif;
}

INLINE short CATTopologicalOperator::GetNoSimplif_MergedCurves()   
{
   return _NoSimplif_MergedCurves;
}

INLINE void CATTopologicalOperator::SetSimplifOnlyModifiable(CATBoolean iSimplifOnlyModifiable)
{
   _SimplifOnlyModifiable = iSimplifOnlyModifiable;
}

INLINE CATBoolean CATTopologicalOperator::GetSimplifOnlyModifiable()
{
   return _SimplifOnlyModifiable;
}

INLINE void CATTopologicalOperator::SetLiveMode(CATBoolean iLiveMode)
{
  _LiveMode=iLiveMode;
}
INLINE CATBoolean CATTopologicalOperator::GetLiveMode()
{
  return _LiveMode;
}

#ifdef InputHelpError
INLINE void  CATTopologicalOperator::SetOperatorCaller(CATTopOperator * iCallerOperator)
{
  _OperatorCaller = iCallerOperator;
}

INLINE CATTopOperator * CATTopologicalOperator::GetOperatorCaller()
{
  return _OperatorCaller;
}
#endif

INLINE void CATTopologicalOperator::SetRemoveArtefacts( int iRemoveArtefacts )
{
  _RemoveArtefacts = iRemoveArtefacts;
}


INLINE void CATTopologicalOperator::SetTraceMode (int mode)
{
   _traceMode=mode;
}

//======================================================================
// Create
//======================================================================

ExportedByBOOPER CATTopologicalOperator* CATCreateTopologicalOperator(CATGeoFactory*                iFactory,
                                                                      CATTopData*                   iData,
                                                                      CATBody*                      iCreationBody,
                                                                      CATSubdContextForFastRunExt * ipCtxExt = NULL);

#endif
