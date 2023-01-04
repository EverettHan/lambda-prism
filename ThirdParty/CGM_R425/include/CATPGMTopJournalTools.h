#ifndef CATPGMTopJournalTools_h_
#define CATPGMTopJournalTools_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATErrorDef.h"
#include "CATGMModelInterfaces.h"
#include "CATCollec.h"
#include "CATBoolean.h"

#ifndef NULL
#define NULL 0
#endif


class CATBody;
class CATCGMJournalList;
class CATCell;
class CATGeometry;
class CATCGMHashTable;
class CATListPtrCATCGMJournal;
class CATLISTP(CATBody);
class CATCGMHashTableWithAssoc;
class CATAdaptiveHashTable;

class ExportedByCATGMModelInterfaces CATPGMTopJournalTools
{
public:
  /**
   * Constructor
   */
  CATPGMTopJournalTools();

  /**
   * Destructor
   */
  virtual ~CATPGMTopJournalTools();

  /** @nodoc */
  virtual void SetOutputBodyAndJournal(CATBody *ipOutBody, CATCGMJournalList *ipReport) = 0;

  /** @nodoc */
  virtual void AddInputBodies(
    CATLISTP(CATBody) &iCopyInputBodies,
    CATLISTP(CATBody) &iNoCopyInputBodies) = 0;

  // pour donner la sortie de l'operateur
  virtual void SetOutputBody(CATBody *ipOutBody) = 0;

  // adds an input body without specifying Copy or NoCopy mode
  virtual void AddInputBody(CATBody *ipInBody) = 0;

  // adds a list of input bodies without specifying Copy or NoCopy mode
  virtual void AddInputBodies(const CATLISTP(CATBody) &iListInBodies) = 0;

  // adds an input body in Copy mode
  virtual void AddInputCopyBody(CATBody *ipInBody) = 0;

  // adds an input body in NoCopy mode
  virtual void AddInputNoCopyBody(CATBody *ipInBody) = 0;

  /** @nodoc */
  virtual void SetCreateUpwardLinksOnlyForFollowedDimensions(CATBoolean iValue) = 0;

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
  virtual void CorrectOutputs(
    CATBoolean iFullJournal,
    CATBoolean iAddOrphanCreations = TRUE,
    CATBoolean iEliminateRedondancy = FALSE,
    CATBoolean iForceCreationForIncreasingDimension = FALSE,
    CATBoolean iConvertCreationToModifyWhenPossible = FALSE,
    CATBoolean iAddMissingDeletions = TRUE,
    CATBoolean iAddMissingKeeps = TRUE,
    CATBoolean iImprintContext = FALSE,
    CATBoolean iFollowVolumes = FALSE) = 0;

  /** @nodoc */
  virtual void CorrectMultiOutputs(
    CATLISTP(CATBody) &iBodies,
    CATListPtrCATCGMJournal & iJournals,
    CATBoolean iFullJournal,
    CATBoolean iAddOrphanCreations = TRUE) = 0;

  /** post-traite le journal en remplacant des objets references dans le journal 
   *  mais non suivis (ex: un vertex non bord de wire) par les objets suivis 
   *  permettant de le nommer (ex: ses deux edges incidentes) 
   *
   *  ex :        E edge interne bordant F1 et F2
   *              (E -CREATION-> F)         devient   (F1,F2 -CREATION-> F)
   *              (E -SUBDIVISION-> E1,E2)  devient   (F1,F2 -CREATION-> E1,E2)
   */
  virtual void ReplaceOperandes() = 0;

  virtual int IsInBody(CATGeometry *ipGeometry, CATBody *ipBody) = 0;

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
  virtual void TrimJournal(
    CATBoolean iWithInactivation = FALSE,
    CATBoolean iSuppressDetached = FALSE) = 0;

  /**
   * Supprime du journal les cellules en deletion  qui ne devraient pas etre dans le journal
   * netoyage plus
   */
  virtual void NetJournal(CATBoolean iDontTassJournal = FALSE) = 0;

  /**
   * ajout des ordres keep pour les cellules bord de l'outputbody provenant des cellules du inputbody en No copy
   */
  virtual void KeepOrphan() = 0;

  /**
   * TRUE si la cell est dans le journal en mode Modification
   * JOURNAL COMPLET
   */
  virtual CATBoolean IsCellModification(CATCell *inputCell) = 0;

  /**
   * ajout des ordres de deletion dans le JOURNAL COMPLET
   * des aretes et des vertices internes des volumes
   */
//  virtual void InternalCellsDeletion(/*int WhithFaces = 0*/) = 0;

  /**
   * FSQ(12/01/2009): Call this function to deactivate the new journal
   */
  virtual void ActivateOldJournal() = 0;

  /**
   * Transforme du journal les cellules resultats qui ne devraient pas etre
   * suivies (vertices et edges non bords) en cellules suivies (cellules adjacentes).
   */
  virtual void ConvertOutput() = 0;

  /**
   * Transforme les ordre de creation en ordre de modification lorsque 
   * la cellule input est de dimension inferieure a la cellule output
   * pour les cellules input dans le cas inverse les ordres de creation sont conserves.
   * Certains ordre de creation peuvent donc etre splite en 2 lorsqu'on a des operandes des deux categories
   */
  virtual void ConvertCreationToModify() = 0;

  /**
   * Supprime du journal les ordres referencant des cellules d'entree n'appartenant
   * pas aux bodies d'entree
   */
  virtual void ForgetOrdersWithCellsNotInInputBodies() = 0;

  /**
   * Supprime du journal les ordres referencant des cellules d'entree n'appartenant
   * pas aux bodies d'entree
   */
  virtual void CellsInSeveralBodiesComputation() = 0;

  /** 
  *
  * Put info when its necessary for de subdivision, modification and absortion orders,
  * the info depending if Face_r1 and Face_r2 are neighbors
  * (ex: [Face_i -Subdiv-> Face_r1, Face_r2] becomes [Face_i -Modif-> Face_r1, info=1]
  * & [Face_i -Modif-> Face_r2, info=2] 
  */
  virtual void ReplaceSubdivideByModifyPlusInfo(int idim,short iAllowCellTagUsuage=1) = 0;

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
  virtual void ImprintNewInternalEdges(CATAdaptiveHashTable *ipHT_CellsToIgnore = NULL) = 0;

  /**
   * STATIC METHOD CATPGMTopJournalTools::GetAllGeometries
   * Get all geometries contained in a JournalList, depending on the type of geometry and of journal item.
   *
   *  CATCGMJournalList * iJournal     = input journal
   *  unsigned char       iGetFirstsAndOrLasts    = 1 to get "First" objects, 0 to get "Last" objects and 2 to get both
   *  CATCGMHashTable   * oCreation               = the output hashtable to store Creation elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * oModification           = the output hashtable to store Modification elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * oSubdivision               = the output hashtable to store Subdivision elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * oAbsorption               = the output hashtable to store Absorption elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * oDeletion               = the output hashtable to store Deletion elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * oKeep                   = the output hashtable to store Keep elements; leave NULL if you don't want them.
   *  CATCGMHashTable   * iOutputCellWithInfo     = the output hashtable to store Output elements with Info
   *  CATBoolean          iGetFaces               = TRUE if you want faces
   *  CATBoolean          iGetEdges               = TRUE if you want edges
   *  CATBoolean          iGetVertices            = TRUE if you want vertices
   *  CATBoolean          iWithTass               = TRUE if you want to duplicate and tass a non tassed Journal before retrieve The Geometries 
   *                                                referenced by the journal
   */
  static void GetAllGeometries(
    CATCGMJournalList *iJournal,
    unsigned char iGetFirstsAndOrLasts,
    CATCGMHashTable *iCreation,
    CATCGMHashTable *iModification,
    CATCGMHashTable *iSubdivision,
    CATCGMHashTable *iAbsorption,
    CATCGMHashTable *iDeletion,
    CATCGMHashTable *iKeep,
    CATCGMHashTableWithAssoc *iOutputCellWithInfo,
    CATBoolean iGetFaces,
    CATBoolean iGetEdges,
    CATBoolean iGetVertices,
    CATBoolean iWithTass = TRUE);

  /**
	* STATIC METHOD CATPGMTopJournalTools::ComputeJournalOfDomains
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
  static HRESULT ComputeJournalOfDomains(
    CATLISTP(CATBody) &iListOfInputBodies,
    CATBody *piOutputBody,
    CATCGMJournalList *piCGMJournalList,
    CATCGMJournalList *&pioCGMJournalListOfDomains);

};

ExportedByCATGMModelInterfaces CATPGMTopJournalTools *CATPGMCreateTopJournalTools(
  CATCGMJournalList *ipReport,
  CATBody *ipOutBody = NULL);

#endif /* CATPGMTopJournalTools_h_ */
