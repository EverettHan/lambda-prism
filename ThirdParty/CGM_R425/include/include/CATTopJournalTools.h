#ifndef CATTopJournalTools_H_
#define CATTopJournalTools_H_

/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES  2002
//=============================================================================
// Class for various journal operations
//=============================================================================
// Oct. 02  ForgetOrdersWithCellsNotInInputBodies()                       HCN
// Aug. 04  _pNotBorderOutputVerticesAndEdges et _pListTabInputBodiesInsideCells
//            pour optimisation perfo de SortBorderCells(...) pour le Join,
//          Suppression de l'argument *Body de SortBorderCells(...) :
//            valeur _pOutputBody par defaut                              HCN
// Jan. 17  Perfos : mettre "_CopyNoCopyInfo" de type CATListOfInt        FDS
//          Eviter les listes de valeurs + enum est de type "int" par default
//=============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "ListPOfCATBody.h"
#include "CATListOfCATGeometries.h"
#include "CATCGMListOfCATULONGPTR.h"
#include "CATListOfInt.h"
#include "CATListOfCATCGMJournals.h"
#include "ListPOfCATBody.h"

#include "CATPGMTopJournalTools.h"
#include "CATCGMJournal.h"
#include "CATIACGMLevel.h"


class CATCGMJournal;
class CATCGMJournalList;
class CATBody;
class CATGeometry;
class CATCell;
class CATCellHashTable;
class CATCGMHashTable;
class CATCGMOutput;
class CellHashTableAssocList;
class CATListPtrCATCell;
class CATMapGeoToAssoc;
class CATAdaptiveHashTable;
class CATSoftwareConfiguration;
class CATCloneManager;
class HashTableAssocList;
class CATCGMHashTableWithAssoc;
struct JWC_LinksInOut;

class ExportedByCATTopologicalObjects CATTopJournalTools: public CATPGMTopJournalTools
{
public:
  CATTopJournalTools(CATCGMJournalList* ipReport, CATBody* ipOutBody = NULL, CATSoftwareConfiguration * iConfig = NULL);
  ~CATTopJournalTools();

  /** @nodoc */
  CATTopJournalTools(CATSoftwareConfiguration * iConfig = NULL);

  /** @nodoc */
  void SetOutputBodyAndJournal(CATBody* ipOutBody, CATCGMJournalList* ipReport);

  /** @nodoc */
  void AddInputBodies(ListPOfCATBody & iCopyInputBodies, ListPOfCATBody & iNoCopyInputBodies);

  // pour donner la sortie de l'operateur
  void SetOutputBody(CATBody* ipOutBody);

  // adds an input body without specifying Copy or NoCopy mode
  void AddInputBody(CATBody* ipInBody);

  // adds a list of input bodies without specifying Copy or NoCopy mode
  void AddInputBodies(const CATLISTP(CATBody)& iListInBodies);

  // adds an input body in Copy mode
  void AddInputCopyBody(CATBody* ipInBody);

  // adds an input body in NoCopy mode
  void AddInputNoCopyBody(CATBody* ipInBody);

  /** @nodoc @nocgmitf */
  void InitUpwardLinksForInputBodies();

  /** @nodoc */
  void SetCreateUpwardLinksOnlyForFollowedDimensions(CATBoolean iValue);

  /** @nodoc @nocgmitf */
  void SetTreatItemsWithInfo(CATBoolean iValue);

  /** @nodoc
   * Generical method to correct a journal.
   * After correction, all journal items will respect CGM journal speecifications.
   * @param iFullJournal
   *  Specifies if the journal is full or not.
   * @param iAddOrphanCreations
   *  Adds item [] -Creation-> Elem, if Elem is a cell to follow of result body,
   *  it's not in copy body, and no journal item describes its origin.
   * @param iEliminateRedondancy
   *  If TRUE, removes generating elements if they contain other generating elements.
   *  Example:
   *    F_1, E_2 -Creation-> E_3
   *    E_2 is an edge of face F_1
   *   The item will become:
   *    E_2 -Creation-> E_3
   * @param iForceCreationForIncreasingDimension
   *  Transform modification orders in creation orders
   *  if the top-level domain has an inferior dimension
   *  for input than for result.
   *  Example:
   *    F_1 -Modification-> F_2
   *    F_1 belongs to a shell that belongs directly to its body
   *    F_2 belongs to a shell that belongs to a volume
   *   The item will become:
   *    F_1 -Creation-> F_2
   *    F_1 -> Delete (if F_1 is in a copy body)
   * @param iConvertCreationToModifyWhenPossible
   *  A creation item is converted to a modification(or absorption) item,
   *  provided that the resulting item respects journal specifications
   *  and is not in conflict with previous options.
   * @param iAddMissingDeletions
   *  If a cell is to follow for a copy input and not for the result,
   *  and the journal doesn't describe its removal,
   *  add a Deletion item for it.
   * @param iAddMissingKeeps
   *  If a cell is to follow for a nocopy input and also for the result,
   *  and the journal doesn't contain a Keep item for it,
   *  add a Keep item.
   */
  void CorrectOutputs(CATBoolean iFullJournal,
    CATBoolean iAddOrphanCreations = TRUE,
    CATBoolean iEliminateRedondancy = FALSE,
    CATBoolean iForceCreationForIncreasingDimension = FALSE,
    CATBoolean iConvertCreationToModifyWhenPossible = FALSE,
    CATBoolean iAddMissingDeletions = TRUE,
    CATBoolean iAddMissingKeeps = TRUE,
    CATBoolean iImprintContext  = FALSE,
    CATBoolean iFollowVolumes   = FALSE);

  /** @nodoc */
  void CorrectMultiOutputs(ListPOfCATBody & iBodies, CATListPtrCATCGMJournal & iJournals, CATBoolean iFullJournal, CATBoolean iAddOrphanCreations = TRUE);

  /** post-traite le journal en remplacant des objets references dans le journal 
   *  mais non suivis (ex: un vertex non bord de wire) par les objets suivis 
   *  permettant de le nommer (ex: ses deux edges incidentes) 
   *
   *  ex :        E edge interne bordant F1 et F2
   *              (E -CREATION-> F)         devient   (F1,F2 -CREATION-> F)
   *              (E -SUBDIVISION-> E1,E2)  devient   (F1,F2 -CREATION-> E1,E2)
   */
   void ReplaceOperandes();
   int  IsInBody(CATGeometry* ipGeometry, CATBody* ipBody);

  /**
   * Supprime du journal les cellules resultats qui ne devraient pas etre
   * suivies (vertices et edges non bords).
   * Par defaut, on rajoute dans le journal des ordres de destruction sur les cellules
   * des reports concernes.
   * Avec iWithInactivation, on ne rajoute pas d'ordre, on inactive les ordres existants
   * Avec iSuppressDetached, on inactive les ordres sur les vertex et les edges qui
   *  ne sont plus lies au body (ils n'ont plus de cellules bordantes dans le body output)
   * iSuppressDetached n'est possible que dans le cas iWithInactivation
   */
      void TrimJournal(CATBoolean iWithInactivation = FALSE,
                    CATBoolean iSuppressDetached = FALSE);

   /**
   * Supprime du journal les cellules en deletion  qui ne devraient pas etre dans le journal
   * netoyage plus
   */
   void NetJournal(CATBoolean iDontTassJournal = FALSE);


   /** @nodoc @nocgmitf 
   * 120517@U29
   */
   static void DeactivateDeletionItems_Tass(CATCGMJournalList * ipJournal);

   /**
   * ajout des ordres keep pour les cellules bord de l'outputbody provenant des cellules du inputbody en No copy
   */
   void  KeepOrphan();

   /**
   * TRUE si la cell est dans le journal en mode Modification
   * JOURNAL COMPLET
   */
   CATBoolean IsCellModification(CATCell * inputCell);

   /**
   * ajout des ordres de deletion dans le JOURNAL COMPLET
   * des aretes et des vertices internes des volumes
   */
//   void InternalCellsDeletion(/*int WhithFaces=0*/);

   /**
   * FSQ(12/01/2009): Call this function to deactivate the new journal
   */
   void ActivateOldJournal();

  /**
   * Transforme du journal les cellules resultats qui ne devraient pas etre
   * suivies (vertices et edges non bords) en cellules suivies (cellules adjacentes).
   */
   void ConvertOutput();
  /**
   * Transforme les ordre de creation en ordre de modification lorsque 
   * la cellule input est de dimension inferieure a la cellule output
   * pour les cellules input dans le cas inverse les ordres de creation sont conserves.
   * Certains ordre de creation peuvent donc etre splite en 2 lorsqu'on a des operandes des deux categories
   */
   void ConvertCreationToModify();

  /**
   * Supprime du journal les ordres referencant des cellules d'entree n'appartenant
   * pas aux bodies d'entree
   */
   void ForgetOrdersWithCellsNotInInputBodies();

  /**
   * Supprime du journal les ordres referencant des cellules d'entree n'appartenant
   * pas aux bodies d'entree
   */
   void CellsInSeveralBodiesComputation();

	 /** 
    * @nocgmitf 
    *
    * Transform modification orders in creation orders
    * if the containing domain, contained into the body, has an inferior dimension
    * for input than for result (ex: [Face_i -Modif-> Face_r] / Face_i <- Shell_i <- Body_i
    * & Face_r <- Shell_r <- Volume_r <- Lump_r <- Body_r becomes [Face_i -Create-> Face_r])
    */
   void ConvertModifyToCreateForIncreasingDimension();

	 /** 
    * @nocgmitf 
    *
    * Split subdivision orders in modifications orders plus info,
    * the info depending of the orientation of the splitting traces
    * (ex: [Face_i -Subdiv-> Face_r1, Face_r2] becomes [Face_i -Modif-> Face_r1, info=1]
    * & [Face_i -Modif-> Face_r2, info=2] if Face_r1 is on the left of the edge linking
    * both result faces, Face_r2 being on the right)
    */
   void SplitSubdivideInModifyPlusInfo();

   /** 
    *
    * Put info when its necessary for de subdivision, modification and absortion orders,
    * the info depending if Face_r1 and Face_r2 are neighbors
    * (ex: [Face_i -Subdiv-> Face_r1, Face_r2] becomes [Face_i -Modif-> Face_r1, info=1]
    * & [Face_i -Modif-> Face_r2, info=2] 
    */
   void ReplaceSubdivideByModifyPlusInfo(int idim,short iAllowCellTagUsuage=1);

   /**
   * @nocgmitf
   * Context: 
   *  Service used by MultiTrim, DOCO and disconnect only.
   *  DO NOT USE WITHOUT READING WHAT IT REALLY DOES !
   * Goal:
   *  Replace subdivision orders by creation orders taking into account the disconnecting elements
   *  faces and/or edges of the wires. In case of ambiguity, infos are added.
   * 
   * @param ipHT_CellToCuttingsData
   *  HashTable linking the result cells (Edge or Face) with the cuttings orientations.
   *  This HashTable is used in the stabilization step.
   *  If this Hashtable is NULL other criteria (may be geometric) are used.
   *  
   */
   void ReplaceSubdivideByCreateWithCuttings(CATCGMHashTableWithAssoc* ipHT_CellToCuttingsData=NULL);

   /**
   * Context: 
   *  Service used by MultiTrim, DOCO, Compatible and Disconnect only !
   *  DO NOT USE WITHOUT READING WHAT IT REALLY DOES !
   *  This method requires a full journal as input.
   * Goal: 
   *   Put an imprint attribute on the new internal edges and report them in imprint journal.
   * SPECS:
   *   - New internal edge E can be imprinted if it respects criteria 1 & criteria 2
   *      -> Criteria 1: E is manifold (it is borded by at most 2 faces)
   *      -> Criteria 2:    The faces between E belong to the same operand  (CONDITION A)  
   *                     OR E belong to a confusion area ( CONDTION B)
   *        Rq: CONDITION A is retrieved from the journal <~> We analyse parent of the item where E appears.
   *            CONDITION B is retrieve from the journal  <~> there is a parent Edge and parent Face from same body.
   * 
   * @param ipHT_CellsToIgnore
   *  HashTable containing the cells to ignore even if they are good candidate.
   *
   */
   void ImprintNewInternalEdges(CATAdaptiveHashTable * ipHT_CellsToIgnore = NULL);


   /**
   * STATIC METHOD CATTopJournalTools::GetAllGeometries
   * Get all geometries contained in a JournalList, depending on the type of geometry and of journal item.
   *
   *  CATCGMJournalList * iJournal     = input journal
   *  unsigned char       iGetFirstsAndOrLasts    = 1 to get "First" objects, 0 to get "Last" objects and 2 to get both
   *  CATCGMHashTable   * oCreation               = the output hashtable to store Creation elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * oModification           = the output hashtable to store Modification elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * oSubdivision            = the output hashtable to store Subdivision elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * oAbsorption             = the output hashtable to store Absorption elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * oDeletion               = the output hashtable to store Deletion elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * oKeep                   = the output hashtable to store Keep elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * iOutputCellWithInfo     = the output hashtable to store Output elements with Info
   *  CATBoolean          iGetFaces               = TRUE if you want faces
   *  CATBoolean          iGetEdges               = TRUE if you want edges
   *  CATBoolean          iGetVertices            = TRUE if you want vertices
   *  CATBoolean          iWithTass               = TRUE if you want to duplicate and tass a non tassed Journal before retrieve The Geometries 
   *                                                referenced by the journal
   */
   static void GetAllGeometries(CATCGMJournalList * iJournal,                                                   
                                unsigned char iGetFirstsAndOrLasts,
                                CATCGMHashTable            * iCreation,
                                CATCGMHashTable            * iModification,
                                CATCGMHashTable            * iSubdivision,
                                CATCGMHashTable            * iAbsorption,
                                CATCGMHashTable            * iDeletion,
                                CATCGMHashTable            * iKeep,
                                CATCGMHashTableWithAssoc   * iOutputCellWithInfo,
                                CATBoolean                   iGetFaces,
                                CATBoolean                   iGetEdges,
                                CATBoolean                   iGetVertices,
                                CATBoolean                   iWithTass = TRUE);

	 /** @nodoc @nocgmitf */
	 static void MoveItemJournal(CATCGMJournalList *piSourceJournal,CATCGMJournalList *pioTargetJournal);

   /** @nodoc @nocgmitf */
	 static void CreateCellJournalOrder(CATCGMJournalList & ioJournal, CATListPtrCATCell * iParents, CATListPtrCATCell * iChildren);

	 /** @nodoc @nocgmitf */
	 static void DeactivateNonFaceOrders(CATCGMJournalList & ioJournalList);

   /** @nodoc @nocgmitf */
  static void FillJournalForCloneManager(CATCGMJournalList & ioJournal,
                                          short iLowestLevelForJournaling,
                                          CellHashTableAssocList & iUpwardLinks,
                                          CATBoolean iFullJournal,
                                          CATCloneManager & iCloneManager);

   /** @nodoc @nocgmitf */
   static void GetAllItemsWithoutTass(CATCGMJournalList & iJournal, CATLISTP(CATCGMJournal) & oItemList);

   /** @nodoc @nocgmitf */
   static CATCGMJournalList * GetJournalList(CATListPtrCATCGMJournal & Journals, int idx);

   /** @nodoc @nocgmitf
   * Insert in ioJournal a new journal item,
   * with iParents/iChildren as firsts/lasts,
   * and same type and info as iOtherItem.
   */
   static void ReportSameTypeSameInfo(CATCGMJournalList & ioJournal,
                                      CATLISTP(CATGeometry) & iParents,
                                      CATLISTP(CATGeometry) & iChildren,
                                      CATCGMJournalItem & iOtherItem);

	/**
	* STATIC METHOD CATTopJournalTools::ComputeJournalOfDomains
   * Compute the Journal of domains from a list of input bodies, the result body and a journal of cells that describe 
	* how cells of result body have been constructed from cells of input bodies given as arguments.
	*
	* 
   * Memory Allocation of the Journal Of domains is done by the service 
	* Life cycle of the journal has to be managed by the caller
	* If the output body or th Journal of Cell are NULL, no Journal of domains is computed and E_FAIL status is returned by the service
	* 
	* @param iListOfInputBodies
	*   List of input bodies
	* @param piOutputBody
	*   Output body resulted from the input bodies
	* @param piCGMJournalList
	*   Journal of cells that describe construction of the output from the input bodies.
	     The journal must be tassed
	* @param pioCGMJournalListOfDomains
	*   the Journal of domains as result of service. 
	*   
	* @return
   *   <dl>
	*	 <dt><tt>S_OK</tt>		<dd>if Computation is succedded
	*	 <dt><tt>E_FAIL</tt>    <dd>otherwise
	*	 </dl>
	*/
	 static HRESULT ComputeJournalOfDomains(CATLISTP(CATBody) &iListOfInputBodies, CATBody *piOutputBody, CATCGMJournalList *piCGMJournalList,CATCGMJournalList *&pioCGMJournalListOfDomains);

#ifdef CATIACGMR419CAA
   /** @nodoc @nocgmitf */
   static CATCGMJournalList *BuildJournalFromPolyConversionAndPolyOperJournal(CATLISTP(CATBody) &iListOfInputBody, CATListOfInt &iListOfCheckJournalType,CATCGMJournalList *piPolyOpJournal,CATCGMJournalList *piConversionPolyOpJournal);
#endif

private :

  enum CopyNoCopy
  { 
    None         = 0,
    Copy         = 40,   
    NoCopy       = 41   
  };

  CATSoftwareConfiguration * RetrieveConfiguration();

  CATBoolean GetValidInputCells(CATLISTP(CATGeometry) & iCandidates,
    CATCellHashTable & iCopyCells,
    CATCellHashTable & iNOCopyCells,
    CATCellHashTable & iResultCells,
    CATLISTP(CATGeometry) & oValidInputCells,
    CATBoolean iScanUpwardCellsIfInvalid,
    CATBoolean iRemoveRedondancy,
    CATBoolean iParentsAreSupposedToBeRemoved);

  CATBoolean GetValidResultCells(CATLISTP(CATGeometry) & iCandidates,
    CATCellHashTable & iCopyCells,
    CATCellHashTable & iNOCopyCells,
    CATCellHashTable & iResultCells,
    CATLISTP(CATGeometry) & oValidResultCells);

  static CATBoolean AllCellsHaveSameDimension(CATLISTP(CATGeometry) & iParents, CATLISTP(CATGeometry) & iChildren);

  CATCGMJournal::Type GetGoodTypeForReport(CATLISTP(CATGeometry) & iParents,
    CATLISTP(CATGeometry) & iChildren,
    CATBoolean iPreferTransfoIfPossible,
    CATBoolean iUseCreateForIncreasingDimension);

  CATBoolean IsIncreasingDimension(CATLISTP(CATGeometry) & iParents, CATLISTP(CATGeometry) & iChildren);

  void AddInputBody(CATBody* ipInBody, CATTopJournalTools::CopyNoCopy iCopyNoCopy);

  void ReplaceOperandes(const CATLISTP(CATGeometry)* ipListGeometries, CATCellHashTable* ipTabCellFromJournal);
  void ReplaceOperandes(const CATLISTP(CATGeometry)* ipListGeometries, CATBody* ipInputBody, CATCellHashTable*  ipTabInputBodiesInsideCells);
  void CellFromJournalInBodies(CATCellHashTable* ipTabCellFromJournal);
  void SortBorderCells(CATLISTP(CATGeometry)& iListGeometries, CATCellHashTable* ipTabCellFromJournal);

  void SortBorderCellsEx(CATLISTP(CATGeometry)& iListGeometries, CATBody* ipBody);

  CATBoolean IsCellSharedByBothBodies(CATCell * iCurCell, const CATLISTP(CATBody) & iListOfInputBodies);
  CATBoolean IsInputBodiesWireAndShell(const CATLISTP(CATBody) & iListOfInputBodies);

  int  IsInsideCell(CATCell* ipCell, CATBody* ipBody, CATLISTP(CATGeometry)& iListGeometriesToReplace);
  void ForgetOrdersWithCellsNotInInputBodies(CATCGMJournalList* ipReport, CATCGMListOfCATULONGPTR& ListOfSetsOfCells);

  void Init_TabOfHashTabOfCellsOfInputBodies();
  void Init_HashTabOfCellsOfOutputBody();
  void RetrieveCellsToFollow(CATBoolean iFullJournal, CATCellHashTable *& oCopyCells, CATCellHashTable *& oNOCopyCells, CATCellHashTable *& oResultCells, CATBoolean iImprintContext=FALSE, CATBoolean iFollowVolumes   = FALSE);
  void RetrieveCellsToFollow(CATBoolean iFullJournal, CATCellHashTable ** oCopyCells = NULL, CATCellHashTable ** oNOCopyCells = NULL, CATCellHashTable ** oResultCells = NULL, CATBoolean iImprintContext = FALSE, CATBoolean iFollowVolumes   = FALSE); //U29
  void RetrieveValidCells(CATCellHashTable * iCopyCells, CATCellHashTable * iNOCopyCells, CATCell * iInvalidCell, CATLISTP(CATGeometry) & oValidCells);

  void Init_UpwardLinksForAllBodies(CATBoolean iFullJournal = FALSE);
  void DeleteUpwardLinksForOneBody(int iPos);
  void DestroyUpwardLinksForAllBodies();

  CellHashTableAssocList * CreateUpwardLinksForOneBody(CATBody * iBody, CATBoolean iFullJournal=FALSE);

  int GetNbInputBodiesInHashTable();
  CellHashTableAssocList * GetTableForOutputBody();
  CellHashTableAssocList * GetTableForInputBody(int iPos, CATTopJournalTools::CopyNoCopy & oCopyNoCopy);

  void GetUpwardCellsInAllInputBodies(CATCell * iCell, CATAdaptiveHashTable & oUpwardCells);

  CATBoolean GetTreatItemsWithInfo();

  void ReplaceSubdivideByCreateWithCuttings_Kernel(CATCGMJournalList * ipReport,
                                                   CATLISTP(CATCGMJournal)& iItemsToTreat,
                                                   HashTableAssocList& iNewEdgesToCuttings,
                                                   JWC_LinksInOut& iLinkerInOut,
                                                   CATCGMJournalList* opNewItemsJournal);

  void ImprintNewInternalEdges_Kernel(CATCGMJournalList *ipReport,
                                      const CATLISTP(CATCGMJournal)& iItemsToTreat,
                                      CATAdaptiveHashTable& iHT_CellsToIgnore,
                                      CellHashTableAssocList& iBackwardTable,
                                      HashTableAssocList& iCellToBodies);


  CATLISTP(CATBody)         _ListOfInputBodies;
  CATListOfInt              _CopyNoCopyInfo;
  CATBody*                  _pOutputBody;
  CATCGMJournalList*        _pReport;
  CATCGMJournalList*        _pReportForReplaceOperands;
  CATCellHashTable*         _pNotBorderOutputVerticesAndEdges;
  CATListPV*                _pListTabInputBodiesInsideCells;
  CATBoolean                _ActivateOldJournal;
  CATCellHashTable          **_TabOfHashTabOfCellsOfInputBodies;
  CATCellHashTable          *_HashTabOfCellsOfOutputBody;

  CATListPV                * _UpwardLinksForAllBodies;

  CATBoolean                _CreateUpwardLinksOnlyForFollowedDimensions;

  short                     _TreatItemsWithInfo; //-1 -> unset, 0 -> false, 1 -> true

  CATSoftwareConfiguration * _Config;
};



#endif
