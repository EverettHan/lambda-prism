#ifndef CATSubdContextForFastRunExt_h
#define CATSubdContextForFastRunExt_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
//==========================================================================
// Oct. 09  Rearchitecture du FastRun Booleen                            WQO
//==========================================================================
#include "CATCGMNewArray.h"
#include "CATContextForFastRunExt.h"
#include "CATDiagOfPersistence.h"
#include "CATDataType.h"
#include "CATTopDefine.h"
#include "CATSubdBoolean.h"
#include "CATSubdPosition.h"
#include "CATMathDef.h"
#include "CATMathInline.h"
#include "ListPOfCATShell.h"
#include "CATCGMJournalList.h"
#include "CATUnicodeString.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"

class CATGeoFactoryProtected;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATPCurve;
class CATCrvParam;
class CATSurface;

class CATTopology;
class CATCell;
class CATVertex;
class CATShell;
class CATFace;

class CATCXTopology;
class CATCXBody;
class CATCXShell;
class CATCXFace;
class CATCXLoop;
class CATCXEdge;
class CATCXVertex;
class CATCXCell;
class CATCXVolume;
class CATCXSmartBodyDuplicator;

class CATSubdMultiVolume;
class CATSubdOccurence;
class CATSubdVertex;
class CATSubdIntersectionEdge;
class CATSubdBoundingEdge;
class CATSubdVolume;
class CATSubdBoundingFace;
class CATSubdIntersectionSkin;
class CATSubdEdgeCurve;

class CATSubdPath;
class CATSubdBar;

class CATSubdArrayOccurenceP;
class CATSubdArrayVolumeP;
class CATSubdArrayCXShellP;
class CATSubdArrayBoolean;
class CATSubdArrayMemEdgeP;
class CATSubdArrayEdgeP;
class CATSubdArrayCXEdgeP;
class CATSubdArrayCXVertexP;
class CATSubdArrayCXCellP;
class CATSubdArrayPCurveP;
class CATSubdArrayArrayOccurencePP;
class CATSubdArrayMultiVolumeP;
class CATSubdArrayArrayCXEdgePP;
class CATSubdArrayIntersectionSkinP;

class CATSubdFaceNavigator;

class CATListPtrCATCXVolume;
class CATListPtrCATCXFace;
class CATListPtrCATCell;
class CATListPtrCATCXCell;
class CATListPtrCATCXTopology;
class CATListPtrCATCXShell;
class CATListPtrCATListPtrCATCXCell;

class CATCGMHashTable;
class CATCGMHashTableWithAssoc;
class CATHashTableWithIntAssoc;
class CATAdaptiveHashTable;
class HashTableAssocList;
class CellHashTableAssocList;
class CATAdaptiveHashTableOfRecoverableConfusionForFastRun;
struct RecoverableConfusionForFastRun;
class HashTable_FillingEdgesForFastRun;
class CATCGMOutput;
class CATCX_NCGM;
class CATSubdSmartManager;
class CATListPtrCATGeometry;
class CATJournalWithNoDuplicata;
class CATFillingEdgesManager;
class CATSubdFace;
class CATNewHashTable2Entries;
struct FrozenDivisionOfPropagationTree;

// Mar. 10  Type d adjacence pour la propagation WQO
typedef enum
{ // les deux faces adjacentes viennent (au sens du journal) :
  AdjMonoBodyPersitent          = 0, // - du meme old input et l adjacence aussi
  AdjMonoBodyNotPersitent       = 1, // - du meme old input mais pas l adjacence qui pourra etre recuperee
  AdjTransBodyNotToRegenerate   = 2, // - des deux old inputs et on peut recuperer l intersection (bord donc pas regeneree)
  AdjTransBodyFrankToRegenerate = 3, // - des deux old inputs et on peut recuperer l intersection (pas bord donc regeneree)
  AdjTransBodyToRecompute       = 4, // - des deux old inputs et on doit recalculer l intersection
  AdjTransBodyToForget          = 5, // - des deux old inputs mais une a un anterieur disparu des new inputs
  AdjPropagationDone            = 6, // - des old inputs et l adjacence a deja ete traitee par propagation
  AdjNotPersitentToForget       = 7, // - du meme old input mais une a un anterieur disparu des new inputs
  AdjNotPersitentToRecompute    = 8, // - du meme old input mais pas l adjacence qui doit etre recalculee
  AdjNotPersitentToWatch        = 9  // - du meme old input mais on doit surveiller la possibilite de substitution (remplace 8)
} 
BooleanFastRunAdjType;

class ExportedByCATTopologicalObjects CATSubdContextForFastRunExt: public CATContextForFastRunExt
{
public:
  CATSubdContextForFastRunExt();
  virtual ~CATSubdContextForFastRunExt();

  CATCGMNewClassArrayDeclare;

  CATBoolean                        FastJournalContainsSomething();
  // Acces au flag propre au Context de Booleen
  INLINE CATBoolean                 GetBackUpMode();
  // Acces elements dupliques associes a leur resultat de duplication
  const  CATCGMHashTableWithAssoc * GetDuplicatedInputObjectsWithAssoc(short inWhichBody=1);
  // Et reciproquement
  const  CATCGMHashTableWithAssoc * GetDuplicateOuputObjectsWithAssoc(short inWhichBody=1);
  // Acces aux elements Operands/Results associes a leur liste d'Result(s)/Operand(s)
  INLINE CATCGMHashTableWithAssoc * GetResultOldRunObjectsWithAssoc();
  INLINE CATCGMHashTableWithAssoc * GetOperandOldRunObjectsWithAssoc();
  // Acces a _OperationMultiVolumes
  void AddOperationMultiVolume(CATSubdMultiVolume * iMultiVolume);  
  // ComputeOrientationForNonOrientedPath
  int ComputeOrientationForNonOrientedPath(CATSubdPath * iPath);
  // Gestion du SmartManager
  INLINE void SetSmartManager(CATSubdSmartManager* iSmartManager);

  void EventuallyReorderThe2Inputs(CATBody * iFirstBody, CATBody * iSecondBody);

  /**
  * @See CATContextForFastRunExt::ComputeMultiPAD for more informations
  */
  virtual CATFastRunStatus ComputeMultiPAD(int iInfDimension = 2,
                                           CATBoolean StopToFirstNonPersistent = FALSE);
  
                  
  INLINE CATDiagOfPersistence DiagOfPersistenceForFastRun( CATCXTopology    * ipTopoObj,
                                                           CATBoolean         iRecursiveSearch = FALSE );
  INLINE CATDiagOfPersistence DiagOfPersistenceForFastRun( CATSubdOccurence * ipSubdTopoObj,
                                                           CATBoolean         iRecursiveSearch = FALSE );

  // On casse un tableau entre persistant et non-persistant
  #define _PersistenceDismantling(SHORTTYPE)                                                                    \
  CATDiagOfPersistence PersistenceDismantling( CATSubdArray##SHORTTYPE##P & ipArrayOfAll                      , \
                                               CATSubdArray##SHORTTYPE##P & opArrayOfPersistent               , \
                                               CATSubdArray##SHORTTYPE##P & opArrayOfNonPersistent            , \
                                               CATBoolean                   iRecursiveSearch = FALSE          , \
                                               CATDiagOfPersistence         iUpIsPersistent  = CATDiagIsUnset )
  //Fin du #define _PersistenceDismantling(SHORTTYPE)
  _PersistenceDismantling(Volume);
  _PersistenceDismantling(CXShell);
  
  // Verifie si ces faces sont en confusion ou adjacente a une confusion que l on peut economiser
  CATBoolean IsAFilterableConfusion(CATSubdBoundingFace & iCurrent, CATSubdBoundingFace & iOperand);

  CATBoolean IsOldResultCell(CATCell * iCell);
  CATBoolean IsOldInputCell(CATCell * iCell);
  CATBoolean IsGeneratedByOldRun(CATCell * iCell);

  CATSubdBoolean SkinsComeFromSameOperand(CATSubdIntersectionSkin* ipIS_1, CATSubdIntersectionSkin* ipIS_2);

  //------------------------------------------------------------------------------------------------------------
  // Fonctionnalites ODT et CGMReplay
  //------------------------------------------------------------------------------------------------------------

  virtual void       WriteInput(CATCGMStream & ioStream, CATGeoFactory* ipFactory);
  virtual void       ReadInput(CATCGMStream & ioStream, CATGeoFactory* ipFactory);
  virtual CATBoolean CheckStatusForReplay(CATCGMOutput& os, CATString & Report);

  void SetNbPtVolumesStoredForReplay(int iNbPtVolumesStoredForReplay);

  //------------------------------------------------------------------------------------------------------------
  // Services utilises une seule fois pour chaque Run
  //------------------------------------------------------------------------------------------------------------

  // Service integrant les eventuelles duplications de l'ActivateBodies dans le contexte
  virtual void IntegrateOneDuplication(short iInWhichBody, CATCXTopology* pCXOriginalObject, CATCXTopology* pCXDuplicateObject, int iEstimatedNbDuplications);

  virtual void IntegrateDuplication(CATCXSmartBodyDuplicator * ipDuplicator);

  // Service pour l'InterTopo (post-traitement de l'intersection fast)
  virtual CATBoolean PostInterTopoProcessingForFastRun(CATSubdArrayOccurenceP * iopInterTopoResult);

  virtual void SetTouchedForFalsePersistentCutByRegenerated();

  //Services a utiliser juste avant et apres le SmartDuplicate des touched apres intersection
  virtual void ToDoBeforeSmartDuplication(CATSubdArrayOccurenceP * iOccurencesToDuplicate, CATListPtrCATCXTopology * iCXTopologiesToDuplicate);
  virtual void ToDoAfterSmartDuplication(CATCXSmartBodyDuplicator * iDuplicator);

  //Services a utiliser juste avant et apres la disconnection des shells, mais avant des eventuels point-volumes
  virtual void ToDoBeforeShellDisconnection(CATCGMJournalList * ioJournal);
  virtual void ToDoAfterShellDisconnection();

  //------------------------------------------------------------------------------------------------------------
  // Services appeles plusieurs fois en interne, pendant duplication, disconnection, positionnement,...
  //------------------------------------------------------------------------------------------------------------

  // TRUE si il y a au moins une face a substituer dans iShell
  CATBoolean IsImpactedBySubstitution(CATCXShell * iShell);
  CATBoolean IsImpactedBySubstitution(CATShell * iShell);
  // Si la skin de iFace apparait boundary apres un point-volume, on regarde si on peut s'arreter
  virtual CATSubdPosition TakeADecisionAfterBoundaryPtVolume(CATSubdBoundingFace * iFace, CATSubdBoundingFace * CurrentBoundaryResult);
  // Translate les informations du contexte suivant la duplication d'apres InterTopo
  virtual void IntegrateFaceDuplication(CATSubdBoundingFace * ipFace, CATSubdBoundingFace * ipDuplicateFace);
  // Translate les informations du contexte suivant la disconnection des shells
  virtual void IntegrateShellDisconnection(CATSubdBoundingFace * iOldFace, CATSubdArrayOccurenceP * iNewFaces);
  // Service pour le positionnement des coupantes regenerees
  virtual void IntegratePositionningOfRegeneration();
  // Service for additonal confusion links between volumes
  void GetConfusedVolumesAssociations(CATCXVolume * iVolume, CATListPtrCATCXVolume & oAssociatedVolumes);
  // Service to explicitly declare couples of persistent faces to be intersected.
  void AddPersistentFacesToIntersect(CATCell * iFace1, CATCell * iFace2);

  //------------------------------------------------------------------------------------------------------------
  //Services pour ajouter/enlever this des SubdParameters
  //------------------------------------------------------------------------------------------------------------

  void AddMeToBooleanEnvironment();

  //------------------------------------------------------------------------------------------------------------
  //Services pour le DUMP
  //------------------------------------------------------------------------------------------------------------

  void EventuallySaveForODT(CATBoolean iBeforeRun); //FALSE -> AfterRun

  virtual void SpecificDump(CATCGMOutput& os);

  //------------------------------------------------------------------------------------------------------------
  // STATICS
  //------------------------------------------------------------------------------------------------------------

  //If we're inside a subdsession, it retrieves the context of the parameters
  static CATSubdContextForFastRunExt * SafeGetContextFromParameters(CATBoolean iOnlyIfFastRunNotImpossible = TRUE,
                                                                    CATBoolean iOnlyIfSmartificationNotImpossible = FALSE);  

  static CATShell * CreateAlternatedFaces(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATSurface * iSurface,
    ListPOfCATEdge & iEdgeList,
    CATBody * iCreationBody,
    ListPOfCATCell & oAlternatedFaces);

  static CATBoolean IsAttributeOnForBoolean();

  //------------------------------------------------------------------------------------------------------------
  // SMARTIFICATION
  //------------------------------------------------------------------------------------------------------------

  void DoSmartificationIfFastRunWasIncomplete(
    CATSoftwareConfiguration * iConfig,
    CATBody *&                 ioNewResult,
    CATCGMJournalList *        ioNewJournal);

  INLINE void SetBuildingMode(CATBoolean iMode = FALSE);
  INLINE CATBoolean GetBuildingMode();
protected:

  //------------------------------------------------------------------------------------------------------------
  //Services overloaded from mother class
  //------------------------------------------------------------------------------------------------------------

  // ------- for attributemanagement -------
  virtual CATBoolean IsAttributeManagementActive();

  //------------------------------------------------------------------------------------------------------------
  //Services overloaded in children classes
  //------------------------------------------------------------------------------------------------------------
  
  // ------- for post-intertopo -------
  virtual int AdaptOriToOperationType(int iInputOrientation, int InWhichBody);
  virtual CATBoolean ComputeOneIntersection(CATSubdBoundingFace      & SubdFP,
                                            CATSubdBoundingFace      & SubdFPoperand,
                                            CATSubdArrayOccurenceP & InterTopoResult);

  // ------- for face substitution -------
  virtual void RetrieveOperandShells(short iInWhichBody, ListPOfCATShell & oShells);
  virtual CATShell * DecideShellForLinking(ListPOfCATShell & PotentialShellsForLinking);
  virtual CATOrientation DecideOrientationForLinking(CATShell * iShellForLinking, CATFace * iFaceToLink, CATOrientation iOriInOldResult);

  // ------- for skin positioning -------
  virtual void MarkSkinToKeepOrNot(CATSubdIntersectionSkin * iSkin, CATBoolean iToKeep);
  virtual CATSubdPosition RetrievePositionNeededToCorrectlyMarkSkin(CATShell * iShell, CATBoolean iToKeep);

  // ------- for debug -------
  virtual void GetAdditionalObjectsForNCGMSave(CATListPtrCATICGMObject & ioList);
  virtual void SaveForODT(CATUnicodeString & iArguments);

  //------------------------------------------------------------------------------------------------------------
  //Services called by children classes
  //------------------------------------------------------------------------------------------------------------

  // ------- generic -------
  CATBoolean BodyCheckDomainDimension(CATBody * iBody,
                                      CATBoolean iAcceptLumps,
                                      CATBoolean iAcceptShells,
                                      CATBoolean iAcceptWires,
                                      CATBoolean iAcceptVIV);
  INLINE void SetEdgeJournaling(CATBoolean iEdgeJournaling);

  // ------- for post-intertopo -------
  int AdaptOriToOperationType_Boolean(int iInputOrientation, int InWhichBody);
  CATBoolean ComputeAnIntersection(CATSubdBoundingFace      & SubdFP,
                                   CATSubdBoundingFace      & SubdFPoperand,
                                   CATSubdArrayOccurenceP & InterTopoResult,
                                   CATBoolean iFirstVsSecondOrSecondVsFirst);
  
  // ------- for face substitution -------
  void RetrieveOperandShells_FromMultiVolumes(short iInWhichBody, ListPOfCATShell & oShells);
  void MakeFaceSubstitutionsAccordingToContext(CATCGMJournalList * ioJournal);
  CATBoolean SetToTouchedOfOldOperandShells();
  // Lie les bords libres d'apres substitution avec les coupantes regenerees
  void LinkSubstitutedFreeBordersToRegeneratedCuttings();
  CATShell * DecideShellForLinking_BetterIfInFirstBody(ListPOfCATShell & PotentialShellsForLinking);
  CATShell * DecideShellForLinking_FirstOneIsOK(ListPOfCATShell & PotentialShellsForLinking);
  CATOrientation Boolean_DecideOrientationForLinking(CATShell * iShellForLinking, CATFace * iFaceToLink, CATOrientation iOriInOldResult);
  // Gestion de _HTFirstBodyShells
  void CreateHTOperandShells();
  CATBoolean IsInHTFirstBodyShells(CATShell * iShell);
  CATBoolean IsInHTSecondBodyShells(CATShell * iShell);
  void CleanHTOperandShells();

  // ------- for skin positioning -------
  void PositionSkinsAccordingToContext();
  void MarkSkinToKeepOrNot_Simple(CATSubdIntersectionSkin * iSkin, CATBoolean iToKeep);
  void MarkSkinToKeepOrNot_ShellWillDecide(CATSubdIntersectionSkin * iSkin, CATBoolean iToKeep);
  void SetToRemoveForUnpositionedSkinsClashingOutsideScar();
  void TakeDecisionsBeforePtVolumes_Boolean();

  // ------- for debug -------
  int GetNbPtVolumes();
  CATBoolean SaveNCGMAndGetStringsForDump(CATUnicodeString & iArguments,
                                          const char * iOperatorName,
                                          CATUnicodeString & Path,
                                          CATUnicodeString & CaseName,
                                          CATUnicodeString & NCGMFileName,
                                          int & TagOldInput1,
                                          int & TagOldInput2,
                                          int & TagNewInput1,
                                          int & TagNewInput2,
                                          CATUnicodeString & StringStatus,
                                          int & FastLevel,
                                          int & SmartLevel);

private:

  // ------- generic -------
  INLINE CATBoolean GetEdgeJournaling();

  // Est-ce Faux-Persistant au sens Fast Run ?                     
  CATBoolean IsFalsePersistentForFastRun( CATSubdOccurence * ipSubdTopoObj,
                                          int              * oInWhichBody = NULL );
  CATBoolean IsFalsePersistentForFastRun( CATCXTopology    * ipTopoObj,
                                          int              * oInWhichBody = NULL );
  CATBoolean IsFalsePersistentForFastRun( CATTopology      * ipTopoObj,
                                          int              * oInWhichBody = NULL );
  CATBoolean IsShellImpactedBySubstitution(CATSubdBoundingFace & iFace);

  // ------- for post-intertopo -------
  void       CreateWorkingTables();
  CATBoolean FindIncompatibilities();
  CATBoolean AreTherePersistentOperands();
  void       CreateNavigatorInOldResult();
  void       FilteredConfusionTreatment();
  void       RegenerateFilteredConfusions();
  void       GetEdgesToRegenerateAConfusion(CATFace & iOldResultFace, CATFace & iAppearedFace, ListPOfCATEdge & oResult);
  void       RegenerateAConfusion(CATFace & iOldResultFace, CATFace & iAppearedFace, CATFace & iPersistentFace, ListPOfCATFace & oNewResultFaces);
  void       ConfusionRegeneration(RecoverableConfusionForFastRun & iRecoverableConfusion);
  void       PropagateAppearedResultWithDeleted();
  void       PropagateFalsePersistenceResult();
  void       UpdateTableOfOldOperands();
  void       ListDisappearedAdjacencesFP(
               CATCGMHashTableWithAssoc * & opTableOfDisappearedWithAdjFP,
               CATCGMHashTableWithAssoc * & opTableOfDisappearedOperandWithAdjFP);
  void       ListFPAdjacencesFP(
               CATCGMHashTableWithAssoc * & opTableOfFPWithAssoc,
               CATCGMHashTableWithAssoc * & opTableOfFPOperandWithAssoc);
  void       AddFPtoAdjacentIntersectionAppeared( 
               CATCell                  * pFPToHandle,
               CATCGMHashTableWithAssoc & CurrTableOfFalsePersistent);
  void       AllImageOfFPisFPR(CATLISTP(CATCell) & FPList0,
                               CATLISTP(CATCell) & ListOfFPRtoHandle);
  void       AllPreviousOfFPRisFP(CATCell           * pFPR0,
                                  CATLISTP(CATCell) & FPList0);
  void       AllTouchedOperandIsFP(CATLISTP(CATCell) * pListOfFPRtoHandle = NULL);
  void       ExtractSubCellsWithFollowedContainer();
  void       DiagAdjDelOrFP(CATCell           * pFP,
                            CATFace           * pCurrFace,
                            int                 InWhichBody,
                            CATCGMHashTable * & pTableOfAdj,
                            int                 EstOfNbAdj);
  void       AddAllAdjDelOrFP(CATLISTP(CATCell)        & FPList0,
                              CATCGMHashTableWithAssoc & TableOfAdjToADisappearedWithAssoc);
  void DefineAdjacencyTypeForPropagation(CATCXCell                  & CXFPR0            , 
                                         CATLISTP(CATCell)          & FPList0           ,
                                         CATBoolean                   FPR0_FromWhichBody,
                                         CATBoolean                   FPR0_IsDisappeared,
                                         CATCGMHashTable          * & pHTofECofFPList0  ,
                                         CATCGMHashTableWithAssoc * & pHTofPCofFPList0  ,
                                         CATLISTP(CATCXCell)        & FPR0AdjFaceList   ,
                                         CATLISTP(CATCXCell)        & FPR0AdjLinkList   ,
                                         CATListOfInt               & ListOfAdjType     );
  void RegroupAdjacenciesByTypeForPropagation(CATLISTP(CATCXCell)           & FPR0AdjFaceList       ,
                                              CATLISTP(CATCXCell)           & FPR0AdjLinkList       ,
                                              CATListOfInt                  & ListOfAdjType         ,
                                              CATListPtrCATListPtrCATCXCell & FPR0AdjFaceListListNew,
                                              CATListPtrCATListPtrCATCXCell & FPR0AdjLinkListListNew,
                                              CATListPV                     & ListOfListOfAdjTypeNew);
  void VerifyRegenerationExtremities(CATCXCell                     & CXFPR0                , 
                                     CATLISTP(CATCell)             & FPList0               ,
                                     CATListPtrCATListPtrCATCXCell & FPR0AdjLinkListListNew,
                                     CATListPV                     & ListOfListOfAdjTypeNew,
                                     CATCGMHashTable             * & pHTofECofFPList0      ,
                                     CATCGMHashTableWithAssoc    * & pHTofPCofFPList0      );
  CATBoolean IsCandidateToBreakPropagation(CATCXCell             & iCXAdjLink             , 
                                           CATCXCell             & iCXFPR0                , 
                                           CATLISTP(CATCell)     & iFPList0               , 
                                           int                     iFPR0_FromWhichBody    , 
                                           CATCXCell             & iCXFPR1                , 
                                           CATLISTP(CATCell)     & iFPList1               , 
                                           int                     iFPR1_FromWhichBody    ,
                                           BooleanFastRunAdjType & oAdjTypeForRegeneration);
  CATBoolean FinishFalsePersistentIntersections();
  void       CleanFastJournal();
  void       ComputeIntersections(CATCGMHashTable & iTableOfEntry, CATCGMHashTable & iTableOfOperand);
  void       DismantleIntersections(CATLISTP(CATCell) & iFPList        ,
                                    CATCGMHashTable   & iTableOfEntry  , 
                                    CATCGMHashTable   & iTableOfOperand);
  void       MakeIntersectionOrder(CATLISTP(CATCell) & iFP1List, CATLISTP(CATCell) & iFP2List);
  void       MakeIntersectionOrder(CATLISTP(CATCell) & iFPList, CATCell * ipFPoperand = NULL);
  void       MakeIntersectionsAccordingToPropagation(CATLISTP(CATCell)        & ListOfFPRtoHandle,
                                                     CATHashTableWithIntAssoc & TableOfTreatedFalsePersistent,
                                                     CATHashTableWithIntAssoc & TableOfTreatedFalsePersistentResult);
  void       MarkOperandTouchedByRegeneration(int       InWhichBody,
                                              CATCell * ipCurrFP0);
  CATBoolean RegenerateIntersectionResult(CATCXCell         * ipCXAdjLink, 
                                          int                 InWhichBody,
                                          CATCXCell         * ipCXFPR0, 
                                          CATLISTP(CATCell) * ipFPList0);
  int ListInWhichBody(CATCell * iOldResultCell, CATLISTP(CATCell) * iOperandCells);
  void CleanTablesOfIntersectedComposites();
  void ComputeAnIntersectionWithInterFaceFace(CATSubdBoundingFace&    SubdFP,
                                              CATSubdBoundingFace&    SubdFPoperand,
                                              CATSubdArrayOccurenceP& InterTopoResult);
  CATCXShell* RetrieveShellFromBoundingFace(CATSubdBoundingFace& Face) const;
  RecoverableConfusionForFastRun * IsAFilterableConfusion(CATFace & iAppeared, CATFace & iPersistent, int iAinWhichBody);
  CATBoolean MustBeReactivated(CATCXFace                       & CXFPR0, 
                               FrozenDivisionOfPropagationTree & AssocInfos,
                               CATCGMHashTableWithAssoc        & TableOfFalsePersistentResultWithAssoc,
                               CATCGMHashTableWithAssoc        & TableOfFalsePersistentIntersections,
                               CATCGMHashTable                 & TableOfOldDeleted);
  void TreatPersistentFacesToIntersect();
  
  // ------- for face substitution -------
  // Gestion de _AssocNewFaceWithOriginBody
  void SetOriginBodyForOldResultFace(CATCell * iFace, int iWhichBody);
  int GetOriginBodyForOldResultFace(CATCell * iFace);
  // Gestion de _ConfusedVolumes
  void CreateConfusedVolumesAssociations(int iEstimatedSize);
  void AddConfusedVolumesAssociations(ListPOfCATShell & iConfusedShells);
  CATOrientation GetOrientationInOldResult(CATCXFace * iFace);

  // ------- for skin positioning -------
  CATSubdPosition TakeADecisionForSkinWithoutPosition(CATSubdIntersectionSkin * iSkin,
                                                      CATCGMHashTableWithAssoc & iNotConfusedSurfaces);
  //Gestion des _PersistentUpToDate
  void CreatePersistentUpToDateTable();
  void UpdatePersistentUpToDate(CATSubdBoundingFace * iOldFace, CATSubdBoundingFace * iNewFace);
  void UpdatePersistentUpToDate(CATSubdBoundingFace * iOldFace, CATSubdArrayOccurenceP * iNewFaces);
  CATBoolean IsPersistentUpToDate(CATSubdBoundingFace * iFace);
  CATSubdBoundingFace * GetOriginalPersistentFace(CATSubdBoundingFace * iFace);
  CATBoolean IsSkinPersistentUpToDate(CATSubdIntersectionSkin * iSkin);
  //Gestion des _ReplacedEdges (utilises pour marquer remove certaines skins et eviter ainsi des point-volumes)
  CATSubdArrayCXEdgeP * GetReplacedEdges();
  CATSubdArrayCXEdgeP * GetOrCreateReplacedEdges(int iSize = 4);
  void DestroyReplacedEdges();
  void SetPositionOfUnpositionedSkins(CATCXEdge * iEdge, CATBoolean iToKeep);
  void SetToRemoveForSkinsClashingOutsideScar(CATSubdArrayIntersectionSkinP & iUnpositionedSkins, ListPOfCATShell & iOtherBodyShells);

  // ------- for face border substitution -------
  void MakeFaceBorderSubstitutions();
  void MakeBorderSubstitution(CATFace * iInputFace, CATListPtrCATCell * iOldResultFaces);
  void OrderEdgesAndFillGaps(CATGeoFactoryProtected * iImpFactory,
                             CATCXBody * iActiveBody,
                             CATSubdArrayEdgeP * iOldSubdEdges,
                             CATSubdArrayCXEdgeP * iCells,
                             CATSubdArrayCXEdgeP * oEdges,
                             CATPCurve * iPCurve,
                             CATCrvParam & iParamMin,
                             CATCrvParam & iParamMax,
                             CATCXVertex * iOldVertexMin,
                             CATCXVertex * iOldVertexMax,
                             CATPointOnEdgeCurve * iOldPOECMin,
                             CATPointOnEdgeCurve * iOldPOECMax,
                             CATBoolean iFillGapAtBeginning,
                             CATBoolean iFillGapAtEnd,
                             CATCXVertex * iNewVertexMin,
                             CATCXVertex * iNewVertexMax);
  void FindOrCreateFillingEdges(CATCXVertex * iPreviousVertex,
                              CATCXVertex * iNextVertex,
                              CATPCurve * iPCurve,
                              CATPointOnEdgeCurve * iPreviousPOEC,
                              CATPointOnEdgeCurve * iNextPOEC,
                              CATPositiveLength iResolution,
                              CATSubdArrayCXEdgeP & oFillingEdges,
                              CATSubdArrayEdgeP * iOldSubdEdges,
                              CATCXBody * iActiveBody,
                              CATGeoFactoryProtected * iImpFactory);
  void ClassifyVertices(CATCGMHashTable * oVerticesToConsider);
  // Gestion de _ValidVertices
  CATBoolean IsAVertexToConsiderForSubstitution(CATCXVertex   * ipCXVertex  );
  CATBoolean AllBoundedFacesAreUsefulOldResults(CATCXEdge * iCXEdge);
  CATCGMHashTable * GetValidVertices();
  void SetValidVertices(CATCGMHashTable * iValidVertices);
  //Gestion de _FillingElementsInBorderSubstitution
  CATFillingEdgesManager * GetOrCreateFillingEdgesManager();
  CATBoolean FindFillingEdgeCreationInformation(CATCXVertex * iVertex1, CATCXVertex * iVertex2, CATPCurve * iPCurve, CATSubdArrayCXEdgeP & oFillingEdges);
  void DeleteFillingEdgesManager();
  //Gestion des ordres de journal relatifs aux "ResultsWithFollowedContainer"
  void CreateOrdersForResultsWithFollowedContainer(CATCGMJournalList * ioJournal);
  short BarNature(CATSubdBar * iBar);

  // ------- for debug -------
  void StartPtVolumesCounting();
  int GetNbPtVolumesStoredForReplay();

  //------------------------------------------------------------------------------------------------------------
  // SET/GET pour acceder aux donnees. Mettre ici ceux qu'on ne veut pas appeler par l'exterieur.
  //------------------------------------------------------------------------------------------------------------

  // Acces au flag propre au Context de Booleen
  INLINE void                       SetBackUpMode(CATBoolean iBackUpMode);
  // Acces au navigateur d'adjacences dans le Old Result
  INLINE void                       SetNavigatorInOldResult(CATSubdFaceNavigator * ipNavigatorInOldResult);
  INLINE CATSubdFaceNavigator * GetNavigatorInOldResult();
  // Navigateur d'adjacences dans les Old Operands
  CATSubdFaceNavigator            * CreateNavigatorInOldOperands();
  INLINE CATSubdFaceNavigator     * GetNavigatorInOldOperands();
  // Acces aux elements Operands/Results associes a leur liste d'Result(s)/Operand(s)
  INLINE void                       SetOperandOldRunObjectsWithAssoc(CATCGMHashTableWithAssoc * ipOperandOldRunObjectsWithAssoc);
  INLINE void                       SetResultOldRunObjectsWithAssoc(CATCGMHashTableWithAssoc * ipResultOldRunObjectsWithAssoc);
  INLINE void                       SetSubOperandsWithFollowedContainer(CellHashTableAssocList * ipSubOperandsWithFollowedContainer);
  INLINE void                       SetSubResultsWithFollowedContainer(CellHashTableAssocList * ipSubResultsWithFollowedContainer);
  INLINE void                       SetSimplifiedOperandSupports(CATCGMHashTableWithAssoc * ipSimplifiedOperandSupports);
  INLINE CellHashTableAssocList   * GetSubOperandsWithFollowedContainer();
  INLINE CellHashTableAssocList   * GetSubResultsWithFollowedContainer();
  INLINE CATCGMHashTableWithAssoc * GetSimplifiedOperandSupports();
  // Acces aux elements Operands Old Deleted
  INLINE void                       SetOperandOldDeleted(CATCGMHashTable * ipOperandOldDeleted);
  INLINE CATCGMHashTable          * GetOperandOldDeleted();
  // Acces aux Faux Persistents et Faux Persistent Results, associes entre eux
  INLINE void                       SetFalsePersistentInputObjects(CATCGMHashTableWithAssoc * ipFalsePersistentInputObjects);
  INLINE void                       SetFalsePersistentOperandInputObjects(CATCGMHashTableWithAssoc * ipFalsePersistentInputObjects);
  INLINE void                       SetFalsePersistentOldResult(CATCGMHashTableWithAssoc * ipFalsePersistentOldResult);
  INLINE void                       SetOldResultFalsePersistentAdjacences(CATCGMHashTableWithAssoc * ipOldResultFalsePersistentAdjacences);
  INLINE void                       SetFalsePersistentIntersections(CATCGMHashTableWithAssoc * ipFalsePersistentIntersections);
  INLINE CATCGMHashTableWithAssoc * GetFalsePersistentInputObjects();
  INLINE CATCGMHashTableWithAssoc * GetFalsePersistentOperandInputObjects();
  INLINE CATCGMHashTableWithAssoc * GetFalsePersistentOldResult();
  INLINE CATCGMHashTableWithAssoc * GetOldResultFalsePersistentAdjacences();
  INLINE CATCGMHashTableWithAssoc * GetFalsePersistentIntersections();
  // Acces aux donnees des intersections recalculees
  INLINE void                       SetIOpInterTopoResult(CATSubdArrayOccurenceP * ipIOpInterTopoResult);
  INLINE void                       SetTableOfLockedFaces(CATCGMHashTable * ipTableOfLockedFaces);
  INLINE CATSubdArrayOccurenceP   * GetIOpInterTopoResult();
  INLINE CATCGMHashTable          * GetTableOfLockedFaces();
  // Acces aux donnees de regenerations
  INLINE void                       SetRegeneratedIntersections(CATSubdArrayOccurenceP * ipRegeneratedIntersections);
  INLINE void                       SetRegeneratedIntersectionsOriVsKeptFace(CATSubdArrayBoolean * ipRegeneratedIntersectionsOriVsKeptFace);
  INLINE void                       SetRegeneratedIntersectionsHTable(CATHashTableWithIntAssoc * ipRegeneratedIntersectionsHTable);
  INLINE void                       SetFalsePersistentTouchedByRegenerated(CATCGMHashTableWithAssoc * ipFalsePersistentTouchedByRegenerated);
  INLINE void                       SetFalsePersistentOperandTouchedByRegenerated(CATCGMHashTableWithAssoc * ipFalsePersistentTouchedByRegenerated);
  INLINE void                       SetFalsePersistentResultToRegenerate(CATCGMHashTableWithAssoc * ipFalsePersistentResultToRegenerate);
  INLINE CATSubdArrayOccurenceP   * GetRegeneratedIntersections();
  INLINE CATSubdArrayBoolean      * GetRegeneratedIntersectionsOriVsKeptFace();
  INLINE CATHashTableWithIntAssoc * GetRegeneratedIntersectionsHTable();
  INLINE CATCGMHashTableWithAssoc * GetFalsePersistentTouchedByRegenerated();
  INLINE CATCGMHashTableWithAssoc * GetFalsePersistentOperandTouchedByRegenerated();
  INLINE CATCGMHashTableWithAssoc * GetFalsePersistentResultToRegenerate();
  // Acces aux confusions que l on essaye d economiser
  INLINE void SetFilteredConfusionsTable(CATAdaptiveHashTableOfRecoverableConfusionForFastRun * ipFilteredConfusionsTable);
  INLINE CATAdaptiveHashTableOfRecoverableConfusionForFastRun * GetFilteredConfusionsTable();
  // Acces aux shells qui ont ete modifiees par la substitution
  void                       AddShellImpactedBySubstitution(CATCXShell * iShell);
  void                       AddShellsImpactedBySubstitution(CATSubdBoundingFace & iFace);
  // Acces a OperationMultiVolumes
  CATSubdArrayMultiVolumeP * GetOperationMultiVolumes();
  //EdgeJournal
  CATJournalWithNoDuplicata * CreateEdgeJournal();
  CATJournalWithNoDuplicata * GetEdgeJournal();
  void InsertEdgeJournalInJournal(CATCGMJournalList * ioJournal);
  //_IncompatibilitiesFound
  INLINE void SetIncompatibilitiesFound(CATBoolean iIncompatibilitiesFound) {_IncompatibilitiesFound = iIncompatibilitiesFound;}
  INLINE CATBoolean GetIncompatibilitiesFound() {return _IncompatibilitiesFound;}
  void AddObjectToRemoveAtTheEnd(CATICGMObject * iObject);
  void CleanGarbageCollector();
  // Gestion du LinkReconstructedFaceToOldResultFace
  void CreateLinkReconstructedFaceToOldResultFace(int iEstimatedSize);
  void AddLinkReconstructedFaceToOldResultFace(CATFace * iReconstructedFace, CATFace * iOldResultFace);
  CATFace * GetLinkReconstructedFaceToOldResultFace(CATFace * iReconstructedFace);
  CATFace * GetLinkOldResultFaceToReconstructedFace(CATFace * iOldResultFace);
  void AddLinkEdgeToReconstructedFace(CATCXEdge * iEdge, CATCXFace * iFace);
  void GetLinkEdgeToReconstructedFace(CATCXEdge * iEdge, CATListPtrCATCXCell & oList);

  CATBoolean IsCompatibleForBorderSubstitution(CATCXCell                  & CXAdjLink        , 
                                               CATLISTP(CATCell)          & ListOfO          ,
                                               CATCXCell                  & CXFPR0           ,
                                               CATCGMHashTable          * & iopHTofEC        ,
                                               CATCGMHashTableWithAssoc * & iopHTofPC        ,
                                               CATBoolean               *   iopToWatch = NULL);

  CATPCurve * GetPCurveOnFace(CATCXEdge * iCxEdge, CATFace * iFace, short iWhere); //iWhere = 1 for old inputs, 2 for old result

  void RetrieveUpToDateObjects(CATGeometry * iGeometry, CATListPtrCATGeometry & oResults);
  CATBoolean WereDuplicationsMadeInCATPAD();

  //------------------------------------------------------------------------------------------------------------
  // DONNEES
  //------------------------------------------------------------------------------------------------------------

  // Ensemble des liens d'adjacence permettant de naviguer dans le Old Result
  CATSubdFaceNavigator * _NavigatorInOldResult                       ;
  // Ensemble des liens d'adjacence permettant de naviguer dans les operandes
  CATSubdFaceNavigator * _NavigatorInOldOperands                            ;
  // Ensemble des elements Operands associes a leur liste de Result(s)
  CATCGMHashTableWithAssoc * _OperandOldRunObjectsWithAssoc              ;
  // Ensemble des elements Results associes a leur liste d'Operand(s)
  CATCGMHashTableWithAssoc * _ResultOldRunObjectsWithAssoc               ;
  // Ensemble des sous cellules dont la face est deja suivie
  CellHashTableAssocList   * _SubOperandsWithFollowedContainer           ;
  CellHashTableAssocList   * _SubResultsWithFollowedContainer            ;
  // Ensemble des supports geometrique d O non present dans les R associes
  CATCGMHashTableWithAssoc * _SimplifiedOperandSupports                  ;
  // Ensemble des elements Operands etant en ordre delete dans le Old Journal
  CATCGMHashTable          * _OperandOldDeleted                          ;
  // Ensemble des Faux Persistents (elements de O et P ayant une incompatibilite entre coupantes Old et New)
  CATCGMHashTableWithAssoc * _FalsePersistentInputObjects                ;
  CATCGMHashTableWithAssoc * _FalsePersistentOperandInputObjects         ;
  // Ensemble des Faux Resultats Persistents (elements de R ayant un Faux Persistent comme anterieur)
  CATCGMHashTableWithAssoc * _FalsePersistentOldResult                   ;
  // Ensemble des adjacences du Old Result diagnostiquees Faux Persistentes
  CATCGMHashTableWithAssoc * _OldResultFalsePersistentAdjacences         ;
  // Ensemble des intersections Faux-Persistentes a regenerer
  CATCGMHashTableWithAssoc * _FalsePersistentIntersections               ;
  // Donnees des et pour les intersections
  CATSubdArrayOccurenceP   * _IOpInterTopoResult                         ;
  int                        _NbInterFaceFace                            ;
  int                        _NbInterFaceFaceWithResult                  ;
  CATCGMHashTable          * _TableOfLockedFaces                         ;
  // Donnees de la regeneration (intersections, orientations, FPs touchees et Vertices disparues)
  CATSubdArrayOccurenceP   * _RegeneratedIntersections                   ;
  CATSubdArrayBoolean      * _RegeneratedIntersectionsOriVsKeptFace      ;
  CATHashTableWithIntAssoc * _RegeneratedIntersectionsHTable             ;
  CATCGMHashTableWithAssoc * _FalsePersistentTouchedByRegenerated        ;
  CATCGMHashTableWithAssoc * _FalsePersistentOperandTouchedByRegenerated ;
  CATCGMHashTableWithAssoc * _FalsePersistentResultToRegenerate          ;
  // Donnees specifiques pour le traitement des confusions que l on essaye de recuperer
  CATAdaptiveHashTableOfRecoverableConfusionForFastRun * _FilteredConfusionsTable;
  // Flag permettant de recuperer un Fast Update devenu impossible
  CATBoolean                 _BackUpMode                                 ;
  // Shells qui ont ete modifiees par la substitution
  CATAdaptiveHashTable     * _ShellsModifiedBySubstitution               ;
  // Toutes les faces persistantes lors de l'IntersectTopology (la persistance recursive se me suffit pas!)
  CATCGMHashTableWithAssoc * _PersistentUpToDate                         ;
  // All vertices that, if found in "O" faces or assoc of "TouchedByRegenerated", must/can be
  // in face after border substitution
  CATCGMHashTable          * _ValidVertices                              ;
  // Edges that are definitely unlinked from faces during border substitution
  CATSubdArrayCXEdgeP      * _ReplacedEdges                              ;
  // CATSubdMultiVolumes involved in operation
  CATSubdArrayMultiVolumeP * _OperationMultiVolumes                      ;
  // Hashtables of CATShells (NO CATCXShells) contained in first multivolume after duplication
  CATAdaptiveHashTable     * _HTFirstBodyShells                          ;
  CATAdaptiveHashTable     * _HTSecondBodyShells                         ;
  // For ODTs and CGMReplay
  int                      * _NbPtVolumesAtBeginning                     ;
  int                        _NbPtVolumesStoredForReplay                 ;
  // Les cellules qui bouchent les trous pendant la substitutions des bords (CATVertex avec en assoc 1 CATVertex et N CATEdges)
  CATFillingEdgesManager   * _FillingEdgesManager                        ;
  // Association between a face in OldResult and an integer representing the origin input body generating it
  // ( 1 = first body, 2 = second body, 3 = both(face confusion) )
  CATHashTableWithIntAssoc * _AssocNewFaceWithOriginBody                 ; 
  //TRUE if edge journalling is required
  CATBoolean                 _EdgeJournaling                             ;
  //Association table for volumes: if 2 volumes are associated, it means that in old operation they had faces in confusion
  CellHashTableAssocList   * _ConfusedVolumes                            ;
  //Journal for Edges, if edge journaling is asked
  CATJournalWithNoDuplicata * _EdgeJournal                              ;
  //Result of FindIncompatibilities
  CATBoolean                 _IncompatibilitiesFound                     ;
  //Garbage collector
  CATListPtrCATICGMObject    _ObjectsToRemoveFromFactory                  ;
  //ReconstructedFaces->OldResultFace
  CATCGMHashTableWithAssoc * _LinkReconstructedFaceToOldResultFace       ;
  CATCGMHashTableWithAssoc * _LinkOldResultFaceToReconstructedFace       ;
  //Link from the appeared CATCXEdge used for confusion treatment to the reconstructed CATCXFace
  HashTableAssocList       * _LinkEdgeToReconstructedFace        ; //CXEdge to list of CXFaces
  //SmartManager to create smart intersection
  CATSubdSmartManager      * _SmartManager                                ;
  //Couple of persistent faces that weren't intersected during IntersectTopology step,
  //and that need to be intersected in PostInterTopoProcessingForFastRun.
  CATNewHashTable2Entries  * _PersistentFacesToIntersect                  ;
  int                        _IndexPersistentFacesToIntersect             ;
  // 2019-11-18 if it is in the body building step                   QCN5
  CATBoolean                 _BuildingMode                              ;
};
INLINE CATDiagOfPersistence 
CATSubdContextForFastRunExt::DiagOfPersistenceForFastRun( CATSubdOccurence * ipSubdTopoObj,
                                                          CATBoolean         iRecursiveSearch )
{
  return (this->IsPersistentForFastRun(ipSubdTopoObj, iRecursiveSearch) == TRUE ? CATDiagIsPersistent : CATDiagIsNonPersistent);
}
INLINE CATDiagOfPersistence 
CATSubdContextForFastRunExt::DiagOfPersistenceForFastRun( CATCXTopology    * ipTopoObj,
                                                          CATBoolean         iRecursiveSearch )
{
  return (this->IsPersistentForFastRun(ipTopoObj, iRecursiveSearch) == TRUE ? CATDiagIsPersistent : CATDiagIsNonPersistent);
}
//----------------------------------------------------------------------
// Nov. 09  Acces au navigateur permettant de simuler l'activation
//          du Old Result (les liens d'adjacences)                   WQO
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetNavigatorInOldResult(CATSubdFaceNavigator * ipNavigatorInOldResult)
{
  _NavigatorInOldResult = ipNavigatorInOldResult;
  return;
}
INLINE CATSubdFaceNavigator * CATSubdContextForFastRunExt::GetNavigatorInOldResult()
{
  return _NavigatorInOldResult;
}
//----------------------------------------------------------------------
// Nov. 14  Acces au navigateur permettant de simuler l'activation
//          des Old operands (les liens d'adjacences)             LD2
//----------------------------------------------------------------------
INLINE CATSubdFaceNavigator * CATSubdContextForFastRunExt::GetNavigatorInOldOperands()
{
  return _NavigatorInOldOperands;
}
//----------------------------------------------------------------------
// Nov. 09  Acces au tableau des Old Operands et Results avec la
//          CATLISTP(CATCell) de Result(s) ou Operand(s) associee    WQO
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetOperandOldRunObjectsWithAssoc(CATCGMHashTableWithAssoc * ipOperandOldRunObjectsWithAssoc)
{
  _OperandOldRunObjectsWithAssoc = ipOperandOldRunObjectsWithAssoc;
  return;
}
INLINE void CATSubdContextForFastRunExt::SetResultOldRunObjectsWithAssoc(CATCGMHashTableWithAssoc * ipResultOldRunObjectsWithAssoc)
{
  _ResultOldRunObjectsWithAssoc = ipResultOldRunObjectsWithAssoc;
  return;
}
INLINE CATCGMHashTableWithAssoc * CATSubdContextForFastRunExt::GetOperandOldRunObjectsWithAssoc()
{
  return _OperandOldRunObjectsWithAssoc;
}
INLINE CATCGMHashTableWithAssoc * CATSubdContextForFastRunExt::GetResultOldRunObjectsWithAssoc()
{
  return _ResultOldRunObjectsWithAssoc;
}
//----------------------------------------------------------------------
// Sep. 10  Acces aux Edges ou Vertices dont la face est deja dans 
//          les objets suivis (i.e. le journal)
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetSubOperandsWithFollowedContainer(CellHashTableAssocList * ipSubOperandsWithFollowedContainer)
{
  _SubOperandsWithFollowedContainer = ipSubOperandsWithFollowedContainer;
  return;
}
INLINE void CATSubdContextForFastRunExt::SetSubResultsWithFollowedContainer(CellHashTableAssocList * ipSubResultsWithFollowedContainer)
{
  _SubResultsWithFollowedContainer = ipSubResultsWithFollowedContainer;
  return;
}
INLINE CellHashTableAssocList * CATSubdContextForFastRunExt::GetSubOperandsWithFollowedContainer()
{
  return _SubOperandsWithFollowedContainer;
}
INLINE CellHashTableAssocList * CATSubdContextForFastRunExt::GetSubResultsWithFollowedContainer()
{
  return _SubResultsWithFollowedContainer;
}
//----------------------------------------------------------------------
// Feb. 11  Acces au tableau des supports de O non presents dans 
//          les R associes car probablement issus de Simplify
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetSimplifiedOperandSupports(CATCGMHashTableWithAssoc * ipSimplifiedOperandSupports)
{
  _SimplifiedOperandSupports = ipSimplifiedOperandSupports;
  return;
}
INLINE CATCGMHashTableWithAssoc * CATSubdContextForFastRunExt::GetSimplifiedOperandSupports()
{
  return _SimplifiedOperandSupports;
}
//----------------------------------------------------------------------
// Dec. 09  Acces au tableau des elements Operands Old Deleted
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetOperandOldDeleted(CATCGMHashTable * ipOperandOldDeleted)
{
  _OperandOldDeleted = ipOperandOldDeleted;
  return;
}
INLINE CATCGMHashTable * CATSubdContextForFastRunExt::GetOperandOldDeleted()
{
  return _OperandOldDeleted;
}
//----------------------------------------------------------------------
// Nov. 09  Acces aux tableaux des Faux Persistents des Inputs       WQO
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetFalsePersistentInputObjects(CATCGMHashTableWithAssoc * ipFalsePersistentInputObjects)
{
  _FalsePersistentInputObjects = ipFalsePersistentInputObjects;
  return;
}
INLINE CATCGMHashTableWithAssoc * CATSubdContextForFastRunExt::GetFalsePersistentInputObjects()
{
  return _FalsePersistentInputObjects;
}
INLINE void CATSubdContextForFastRunExt::SetFalsePersistentOperandInputObjects(CATCGMHashTableWithAssoc * ipFalsePersistentInputObjects)
{
  _FalsePersistentOperandInputObjects = ipFalsePersistentInputObjects;
  return;
}
INLINE CATCGMHashTableWithAssoc * CATSubdContextForFastRunExt::GetFalsePersistentOperandInputObjects()
{
  return _FalsePersistentOperandInputObjects;
}
//----------------------------------------------------------------------
// Nov. 09  Acces aux donnees de Fausse Persistence du Old Result    WQO
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetFalsePersistentOldResult(CATCGMHashTableWithAssoc * ipFalsePersistentOldResult)
{
  _FalsePersistentOldResult = ipFalsePersistentOldResult;
  return;
}
INLINE CATCGMHashTableWithAssoc * CATSubdContextForFastRunExt::GetFalsePersistentOldResult()
{
  return _FalsePersistentOldResult;
}
INLINE void CATSubdContextForFastRunExt::SetOldResultFalsePersistentAdjacences(CATCGMHashTableWithAssoc * ipOldResultFalsePersistentAdjacences)
{
  _OldResultFalsePersistentAdjacences = ipOldResultFalsePersistentAdjacences;
  return;
}
INLINE CATCGMHashTableWithAssoc * CATSubdContextForFastRunExt::GetOldResultFalsePersistentAdjacences()
{
  return _OldResultFalsePersistentAdjacences;
}
//----------------------------------------------------------------------
// Jan. 10  Acces au tableau des Faux Persistent Insterscetions
//          i.e. les elements de l input 1 associes a 
//          leurs operandes de l input 2                             WQO
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetFalsePersistentIntersections(CATCGMHashTableWithAssoc * ipFalsePersistentIntersections)
{
  _FalsePersistentIntersections = ipFalsePersistentIntersections;
  return;
}
INLINE CATCGMHashTableWithAssoc * CATSubdContextForFastRunExt::GetFalsePersistentIntersections()
{
  return _FalsePersistentIntersections;
}
//----------------------------------------------------------------------
// Sep. 10  Acces aux donnees des intersections recalculees          WQO
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetIOpInterTopoResult(CATSubdArrayOccurenceP * ipIOpInterTopoResult)
{
  _IOpInterTopoResult = ipIOpInterTopoResult;
  return;
}
INLINE void CATSubdContextForFastRunExt::SetTableOfLockedFaces(CATCGMHashTable * ipTableOfLockedFaces)
{
  _TableOfLockedFaces = ipTableOfLockedFaces;
  return;
}
INLINE CATSubdArrayOccurenceP * CATSubdContextForFastRunExt::GetIOpInterTopoResult()
{
  return _IOpInterTopoResult;
}
INLINE CATCGMHashTable * CATSubdContextForFastRunExt::GetTableOfLockedFaces()
{
  return _TableOfLockedFaces;
}
//----------------------------------------------------------------------
// Mar. 10  Acces aux donnees de regeneration (intersections,  
//          orientations, FPs touchees et Vertices disparues)        WQO
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetRegeneratedIntersections(CATSubdArrayOccurenceP * ipRegeneratedIntersections)
{
  _RegeneratedIntersections = ipRegeneratedIntersections;
  return;
}
INLINE CATSubdArrayOccurenceP * CATSubdContextForFastRunExt::GetRegeneratedIntersections()
{
  return _RegeneratedIntersections;
}
INLINE void CATSubdContextForFastRunExt::SetRegeneratedIntersectionsOriVsKeptFace(CATSubdArrayBoolean * ipRegeneratedIntersectionsOriVsKeptFace)
{
  _RegeneratedIntersectionsOriVsKeptFace = ipRegeneratedIntersectionsOriVsKeptFace;
  return;
}
INLINE CATSubdArrayBoolean * CATSubdContextForFastRunExt::GetRegeneratedIntersectionsOriVsKeptFace()
{
  return _RegeneratedIntersectionsOriVsKeptFace;
}
INLINE void CATSubdContextForFastRunExt::SetRegeneratedIntersectionsHTable(CATHashTableWithIntAssoc * ipRegeneratedIntersectionsHTable)
{
  _RegeneratedIntersectionsHTable = ipRegeneratedIntersectionsHTable;
  return;
}
INLINE CATHashTableWithIntAssoc * CATSubdContextForFastRunExt::GetRegeneratedIntersectionsHTable()
{
  return _RegeneratedIntersectionsHTable;
}
INLINE void CATSubdContextForFastRunExt::SetFalsePersistentTouchedByRegenerated(CATCGMHashTableWithAssoc * ipFalsePersistentTouchedByRegenerated)
{
  _FalsePersistentTouchedByRegenerated = ipFalsePersistentTouchedByRegenerated;
  return;
}
INLINE CATCGMHashTableWithAssoc * CATSubdContextForFastRunExt::GetFalsePersistentTouchedByRegenerated()
{
  return _FalsePersistentTouchedByRegenerated;
}
INLINE void CATSubdContextForFastRunExt::SetFalsePersistentOperandTouchedByRegenerated(CATCGMHashTableWithAssoc * ipFalsePersistentOperandTouchedByRegenerated)
{
  _FalsePersistentOperandTouchedByRegenerated = ipFalsePersistentOperandTouchedByRegenerated;
  return;
}
INLINE CATCGMHashTableWithAssoc * CATSubdContextForFastRunExt::GetFalsePersistentOperandTouchedByRegenerated()
{
  return _FalsePersistentOperandTouchedByRegenerated;
}
INLINE void CATSubdContextForFastRunExt::SetFalsePersistentResultToRegenerate(CATCGMHashTableWithAssoc * ipFalsePersistentResultToRegenerate)
{
  _FalsePersistentResultToRegenerate = ipFalsePersistentResultToRegenerate;
  return;
}
INLINE CATCGMHashTableWithAssoc * CATSubdContextForFastRunExt::GetFalsePersistentResultToRegenerate()
{
  return _FalsePersistentResultToRegenerate;
}
INLINE void CATSubdContextForFastRunExt::SetFilteredConfusionsTable(CATAdaptiveHashTableOfRecoverableConfusionForFastRun * ipFilteredConfusionsTable)
{
  _FilteredConfusionsTable = ipFilteredConfusionsTable;
  return;
}
INLINE CATAdaptiveHashTableOfRecoverableConfusionForFastRun * CATSubdContextForFastRunExt::GetFilteredConfusionsTable()
{
  return _FilteredConfusionsTable;
}
//----------------------------------------------------------------------
// Oct. 09  Acces au Flag permettant de recuperer un Fast Update 
//          devenu impossible                                        WQO
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetBackUpMode(CATBoolean iBackUpMode)
{
  _BackUpMode = iBackUpMode;
  return;
}
INLINE CATBoolean CATSubdContextForFastRunExt::GetBackUpMode()
{
  return _BackUpMode;
}
INLINE void CATSubdContextForFastRunExt::SetEdgeJournaling(CATBoolean iEdgeJournaling)
{
  _EdgeJournaling = iEdgeJournaling;
}
INLINE CATBoolean CATSubdContextForFastRunExt::GetEdgeJournaling()
{
  return _EdgeJournaling;
}
//----------------------------------------------------------------------
// Nov. 13  Modification du Smart Manager                            D4U
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetSmartManager(CATSubdSmartManager* iSmartManager)
{
  this->_SmartManager = iSmartManager;
}

//----------------------------------------------------------------------
// 2019-11-18 Set and Get if we are in body building step           QCN5  
//----------------------------------------------------------------------
INLINE void CATSubdContextForFastRunExt::SetBuildingMode(CATBoolean iMode)
{
  this->_BuildingMode = iMode;
}
INLINE CATBoolean CATSubdContextForFastRunExt::GetBuildingMode()
{
  return _BuildingMode;
}
void CleanListOfList(CATListPtrCATListPtrCATCXCell * ipCurrentListOfList);
#endif
