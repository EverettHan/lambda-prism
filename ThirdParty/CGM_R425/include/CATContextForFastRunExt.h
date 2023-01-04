#ifndef CATContextForFastRunExt_h
#define CATContextForFastRunExt_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//
//  Implementation de CATContextForFastRun
//  Most functions are now generalized to deal with multi-result operators.  Those that are not have a clear
//  comment surrounding them.
//
// * For multi-result operators, use a list of internal contexts, but for single-result
//   operators, use the member variables in this context.  
// * If both are being used, the set methods that take a ResultID will detect this situation and throw.  The
//   get methods and methods that don't take a Result ID don't throw in this situation.    
// * Result ID > 1 in the multi-result case and ResultID = 1 otherwise.
// * We don't allow internal context objects to have their own internal context objects.
// * When we create a new internal context object, the data is not passed to it.  
// * When using Result IDs, GetInternalContext should always be called to check that these
//   rules are adhered to.
// * Apart from the Results, Result IDs and journals, the internal context data is not kept up to date.  The
//   caller should instead consult the main context using InternalContext->GetOwningContext().
//==========================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"

#include "CATContextForFastRun.h"
#include "CATFastRunStatus.h"
#include "CATFastRunSolution.h"
#include "CATSmartificationStatus.h"

#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATListPV.h"
#include "CATListOfInt.h"
#include "CATUnicodeString.h"
#include "ListPOfCATContextForFastRunInternal.h"
#include "ListPOfListPOfCATCell.h"

class CATSoftwareConfiguration;
class CATTopOperator;
class CATGeoFactory;
class CATTopData;

class CATTopology;
class CATCXTopology;
class CATSubdOccurence;
class CATBody;

class CATListPtrCATBody;
class CATCGMJournalList;
class CATFaceHashTable;

class CATString;
class CATCGMOutput;
class CATCGMStreamImpl;

class CATJournalUtilitiesForFastRun;
class CATMultiPAD;
class CATFastRunAttribute;
class CATListPtrCATICGMObject;
class ListOfListOfIntegers;
class CATListPtrCATCell;
class CATListPtrListPOfCATCell;
class CATAdaptiveHashTable;
class CATCGMBodyAndCells;

class ExportedByCATTopologicalObjects CATContextForFastRunExt : public CATContextForFastRun
{
public :
  CATContextForFastRunExt();
  virtual ~CATContextForFastRunExt();
  CATCGMNewClassArrayDeclare;

  // Acces au journal des operations fast
  virtual CATCGMJournalList * GetFastJournal();
  void                        SetFastJournal(CATCGMJournalList * ipFastJournal);

	// Create internal contexts.   Result IDs are 2, 3, 4 etc.
  virtual void SetNbOldResults(int iNbInternalContexts);

  /** @return [out, CATBaseUnknown#Release]
  * Get the internal context for a particular Result ID.  
  * if (ResultID == 1) {
  *   if (We're using internal contexts)
  *     return NULL;
  *   else
  *     return this;
  * Throw if the internal context list is incomplete.
  */
  virtual CATContextForFastRun * GetInternalContextForFastRun (CATResultIDForFastRun iResultID);

  /** @return [out, CATBaseUnknown#Release]
	* Get the ith internal context and its result ID.
	* if (i == 0) {
	*   oResultID = 1;
	* if (We're using internal contexts)
	*   return NULL;
	* else
	*   return this;
	*   
	* Throw if the internal context list is incomplete.
  */
	virtual CATContextForFastRun * GetInternalContextForFastRun (int i, CATResultIDForFastRun &oResultID);

	virtual CATLONG32 GetNbInternalContextForFastRun() {return _InternalContextList.Size();}

	// Get owning context.  This is NULL for a context that isn't an internal one.
	virtual CATContextForFastRunExt * GetOwningContext() {return NULL;}

  // Ayant une interface dans CATContextForFastRun.h
  virtual CATContextForFastRunExt * GetExtensible();
  virtual CATString           GetType();
  virtual void                AddInput(CATBody *iOldInput, 
                                       CATBody *iNewInput);
  virtual void                AddInput(CATCGMBodyAndCells & iOldInputAndFollowedCells,
                                       CATBody * iNewInput);
  virtual void                ChangeNewInput(CATBody *iOldInput, 
                                             CATBody *iNewInput);
  
  /** @nodoc @nocgmitf */
  void ReplaceNewInput(CATBody *iNewInputToReplace,
                       CATBody *iReplacingNewInput);

	// Add a new output body and journal, being careful to obey the rules about Internal contexts and 
  // ResultIDs stated at the top of this file.  We use GetInternalContextForFastRun to check this.
  // If the result ID has already been used, replace the data instead of throwing (JHN, 23/06/2014).  
  // Don't throw if iOldOutput == NULL or iOldJournal == NULL.
  // If we create a new internal context and _OldOutput or _OldJournal has been set, throw.
  // Warning: If other data has been set and we create our first internal context, that data will
  // cease to be accessible.
  virtual void                SetOldResult(CATBody *iOldOutput, CATCGMJournalList *iOldJournal, CATResultIDForFastRun iResultID = 1);

  virtual void                SetOldResult(CATCGMBodyAndCells & iOldOutputAndFollowedCells, CATCGMJournalList * iOldJournal);

  virtual void                SetAllContextResults(CATTopOperator * iCurOpe);

  virtual const CATLISTP(CATBody)   * GetNewInputList();
  virtual const CATLISTP(CATBody)   * GetOldInputList();

  // Get a particular output result or journal.  If body for the result ID given doesn't exist, return NULL.  
  virtual CATCGMJournalList * GetOldJournal(CATResultIDForFastRun iResultID = 1);
  virtual CATBody           * GetOldResult (CATResultIDForFastRun iResultID = 1);

  // Get all journals or results or result IDs.
  virtual void GetAllOldResult  (ListPOfCATBody              & oOldResultList);
  virtual void GetAllOldJournal (CATLISTP(CATCGMJournal)     & oOldJournalList);
  void GetAllFastJournal (CATLISTP(CATCGMJournal)     & oFastJournalList);
  virtual void GetAllResultIDs  (ListOfCATResultIDForFastRun & oResultIDList);

  // Get the default result ID.
  virtual CATResultIDForFastRun GetResultID() {return 1;};


//-------------------------------------------------------------------------------------------------------
// Define methods to set data from or copy data to another context.
// Warnings:
//   These functions does not check whether we have a main context or an internal context.  
//   It is recommended that they are called for main contexts only (not internal contexts) 
//   because only main contexts are guaranteed to have up to data data apart from the OldResults and 
//   OldJournals.  
//   If there are internal contexts in this or the other context, we must use these or their result IDs to
//   copy OldResults and OldJournals.  GetAllOldResult(), GetAllOldJournal() and GetAllResultIDs() from this
//   or pOtherCtx can be very helpful for this.   
//   If there are no internal contexts, the OldResult and OldJournal will automatically be forwarded.
//
// SetDataFromAnotherContext:
// Copying the Context input and output data from another Context.  
// If there are any inconsistencies between the other context and
// data that has already been set in this context, throw.
// If smartification of a result body is impossible, transfer that information.
// Only transfer the input bodies if we don't already have input bodies in this context.
//
// 2014 Nov   12  The Result ID doesn't have to exist in the other context.                G5S
// 2015 Mar   10  There is only one smart level and smartification status.                 G5S
  virtual void                 SetDataFromAnotherContext(CATContextForFastRun * pOtherCtx);

// Set fast run status, smartification status and number of old journal elements retrieved by smartification.  
// We are allowed to have a NULL output body (JHN, 23/06/2014)
// 2015 Mar   10  There is only one smart level and smartification status.
  virtual void                 SetStatusFromAnotherContext(CATContextForFastRun * pOtherCtx);

  // Copying the Context input data in another Context.  If there are any inconsistencies between this
  // context and data that has already been set in the other context, throw. 
  // 2014 Jun   06  We no longer forward the smartification status.                        G5S
  virtual void                 ForwardInputInAnotherContext(CATContextForFastRun * pOtherCtx);

  // Copying the Context old output data to another Context. 
  // 2014 Nov   11  The Result ID doesn't have to exist in this context.                   G5S
  // 2015 Mar   10  There is only one smart level and smartification status. 
  //
  // Restrictions:
  //   If neither this context nor the other contain internal contexts and 
  //   Fast run status != Impossible, we will overwrite the output data for the other
  //   context.
  virtual void                 ForwardOutputInAnotherContext(CATContextForFastRun * pOtherCtx);

//--------------------------------------------------------------------------------------------------

  // Set Substitute List to replace the actual one.
  virtual void                 SetSubstitueNewInputList(CATLISTP(CATBody) & SubstitueNewInputList);
  virtual void                 SetSubstitueOldInputList(CATLISTP(CATBody) & SubstitueOldInputList);

  //To prohibit both "fast run" and "smartification"
  virtual void                 SetStatusImpossible(const char * Info = "");

  //To prohibit "fast run"
  virtual void                 SetFastRunStatusImpossible(const char * Info = "");

  //To get "fast run" status
  virtual CATFastRunStatus     GetStatus();

  // Search the given body in new input list and, if it finds it, compare it to
  // the corresponding old body to determine if they are equal, i.e. they have
  // the same cells (same pointers for cells of the given dimension) 
  // @param ipNewInputBody
  // The New Input Body which has to be compare to its corresponding old one
  // @param iDimensionToCompare
  // How far down the diagnostic goes, by default -1 implies 
  // a dimension of comparison equal to the body highest cells dimension
  // @return
  // True if equality, False if not or if the Body is not found in the context list
  virtual CATBoolean          IsEqualToOldCorrespondingInput(CATBody * ipNewInputBody,
                                                             int       iDimensionToCompare = -1);

  // Compare both input bodies to verify if they are equal
  // By default, the comparison verifies if they have the same cells 
  // (same pointers for cells of the given dimension)
  // @param ipOldInputBody
  // First body to compare
  // @param ipNewInputBody
  // Second body to compare
  // @param iDimensionToCompare
  // How far down the diagnostic goes, by default -1 implies 
  // a dimension of comparison equal to the new body highest cells dimension
  // @return
  // True if equality, False if not or if an input pointer is NULL
  virtual CATBoolean          AreTheyEqualInputBodies(CATBody * ipOldInputBody,
                                                      CATBody * ipNewInputBody,
                                                      int       iDimensionToCompare = -1,
                                                      CATCGMOutput * ipStream=NULL);

  /**
   * Compare the two bodies to verify if they contain the same high level cells.
   * @param ipOldBody
   * First body to compare
   * @param iOldBodyIdentifier
   * The identifier of the first body to compare.
   * It is used as a security check to verify the coherence of the information regarding the first body.
   * @param ipNewBody
   * Second body to compare
   * @return
   * TRUE if the identifier of the first body is coherent and the 2 bodies contain the same cells.
   */
  virtual CATBoolean AreOldAndNewBodyEqual(CATBody * ipOldBody,
                                           CATULONG32 iOldBodyIdentifier,
                                           CATBody * ipNewBody);

  /**
   * Returns the identifier associated to a body.
   * @param ipBody
   * The body whose identifier is asked.
   * @return
   * The identifier of the body.
   */
  virtual CATULONG32 GetBodyIdentifier(CATBody * ipBody);

  // Fast Journal gives not computed operations which have been retrieved from Old Run.
  // Not yet generalized for multi-result operators.
  // @return
  // The pointer to the Fast Journal
  virtual CATBoolean          AreTheyEqualInputParameters(double iOldInputValue, 
                                                          double iNewInputValue);

  // A comparison, between Fast and Old journals, completes the Status to control Fast Run level
  // Implemented only for some context (Toolbox apporach).  Not yet generalized for multi-result
  // operators.
  // @param opOldJournalSize
  // Optional pointer to the size of the Old Journal
  // @param opLevelPercentage
  // Optional pointer to the quotient Fast on Old in percentage (100xFast/Old)
  // @return
  // The size of the Fast Journal
  virtual CATLONG32           GetFastLevel(CATLONG32 * opOldJournalSize = NULL, 
                                           double * opLevelPercentage = NULL);
  //-----------------------------------------------------------------------------------------------------

  /**
   * Makes Smartification of the given new result with topologies coming from the old result stored in this.
   * The smartified topologies are filtered by identification between old (stored) and new (given) journal.
   * @param iopTopData
   * Contains the Software Configuration and the journal into which the Smartification's journal (the
   * substitutions) will be inserted
   * @param ipNewOperationResult
   * Body, new result of the operation, from which the Smartification starts and which will not be modified
   * @param iDummy
   * NOT USED ANYMORE, you can leave it to NULL
   * @param iObjectsToKeep
   * Optional pointer.
   * The objects contained in this list will be "INVARIANT", and will not be replaced by Smartification:
   * if an object OBJ, contained in ipNewOperationResult, points towards an invariant,
   * and OBJ is replaced in the smartification result by a new object OBJ',
   * then OBJ' will continue to point towards the invariant.
   * Restriction: only objects of type "CATSurface" are accepted as invariant.
   * @return
   * The new Smartified Body, strictly geometricaly equal to ipNewOperationResult, but with, as much as
   * possible, the topologies coming from the Old Result stored in this Context
   */
  virtual CATBody *           SmartificationFromOldResult(CATTopData              * iopTopData           , 
                                                          const CATBody           * ipNewOperationResult ,
                                                          void                    * iDummy = NULL,
                                                          CATListPtrCATICGMObject * iObjectsToKeep = NULL);

  // The status determines if the smartification is possible, and if it has been done
  virtual CATSmartificationStatus GetSmartificationStatus() {return _SmartificationStatus;}

  // To forbid the smartification.
  virtual void        SetSmartificationStatusImpossible(const char * Info = "");

  // For operators implementing Smartification, it returns the number of OldJournal elements that are
  // inside the new resulting body.
  // If no Smartification is done, it is equal to the FastLevel.
  // Implemented only for some context (Toolbox apporach)
  // @return
  // The number of OldJournal elements that are inside the new resulting body
  virtual CATLONG32           GetSmartLevel();

  // Complete and in one line visualization stream
  virtual void                Dump(CATCGMOutput& os);

  virtual CATFastRunSolution  GetFastRunSolution();
  virtual CATString           GetStatusInfo();

  // Acces aux donnees sans interface 

  // The status determines if fast run is possible.
  virtual void                SetStatus(CATFastRunStatus iStatus);

  virtual void                SetOperator(CATTopOperator* iOperator);
  CATTopOperator            * GetOperator();
  virtual void                SetInterface(CATContextForFastRun* ipInterface);
  CATContextForFastRun      * GetInterface();
  virtual CATSoftwareConfiguration* GetSoftwareConfiguration();
  void                        SetLevelToExecute(short iLevel);
  short                       GetLevelToExecute();

  // If first element of NewInputs and first element of iOperatorBodies are not the same,
  // New and Old input lists are inversed.
  void EventuallyCorrectInputOrder(CATLISTP(CATBody) & iOperatorBodies);

  // Acces aux donnees interpretees.
  //------------------ Not yet generalized for multi-result operators.----------------------------------
  CATFaceHashTable          * GetOrigineFacesFromJournal();
  CATFaceHashTable          * GetModifiedFacesFromJournal();
  CATFaceHashTable          * GetCreatedFacesFromJournal();
  CATFaceHashTable          * GetDeletedFacesFromJournal();
  //-----------------------------------------------------------------------------------------------------

  CATListPV                 & GetPADs();
  CATMultiPAD*                GetMultiPAD();

  // Determine what is Persistent, Appeared or Disappeared between old and new inputs
  // @param iInfDimension
  // How far down the diagnostic goes (by default is the 2D cells, which means the Faces) 
  // @param StopToFirstNonPersistent
  // To stop the diagnostic process to the first found non-persistent cell 
  // @return
  // A Status linked to the persitency (Possible if all is persitent, Impossible if  
  // it is asked and stopped to a first non-persistent, Unset otherwise)
  virtual CATFastRunStatus ComputeMultiPAD(int iInfDimension = 2,
                                           CATBoolean StopToFirstNonPersistent = FALSE);

  // Determine if a specific Cell is Persistent, which means the cell is the same
  // in the corresponding old and new imput
  // @param ipTopoObj
  // The cell
  // @param iRecursiveSearch 
  // DEPRECATED option
  // @param oInWhichBody
  // Index of input bodies where the cell is persistent (first bodies couple), 0 otherwise
  // @return
  // TRUE or FALSE                    
  virtual CATBoolean IsPersistentForFastRun(CATCXTopology * ipTopoObj,
                                            CATBoolean      iRecursiveSearch = FALSE,
                                            int           * oInWhichBody     = NULL );
  virtual CATBoolean IsPersistentForFastRun(CATTopology   * ipTopoObj,
                                            CATBoolean      iRecursiveSearch = FALSE,
                                            int           * oInWhichBody     = NULL );
  virtual CATBoolean IsPersistentForFastRun(CATSubdOccurence * ipSubdTopoObj,
                                            CATBoolean         iRecursiveSearch = FALSE,
                                            int              * oInWhichBody     = NULL );

  // Est-ce Apparu/Nouveau au sens Fast Run ?
  CATBoolean IsAppearedForFastRun( CATSubdOccurence * ipSubdTopoObj,
                                   int              * oInWhichBody = NULL );

  CATBoolean IsAppearedForFastRun( CATCXTopology    * ipTopoObj,
                                   int              * oInWhichBody = NULL );

  CATBoolean IsAppearedForFastRun( CATTopology      * ipTopoObj,
                                    int              * oInWhichBody = NULL );
  // Est-ce Disparu/Ancien au sens Fast Run ?
  CATBoolean IsDisappearedForFastRun( CATSubdOccurence * ipSubdTopoObj,
                                      int              * oInWhichBody = NULL );
  CATBoolean IsDisappearedForFastRun( CATCXTopology    * ipTopoObj,
                                      int              * oInWhichBody = NULL );
  CATBoolean IsDisappearedForFastRun( CATTopology      * ipTopoObj,
                                      int              * oInWhichBody = NULL );


  // Determine if a whole Journal is Persistent, which means all the left cells are Persistent
  // for order Creation, Modification, Subdivision and Absorption (Delete and Keep are not considered) 
  // @param ipJournal
  // The Journal (which is tassed, duplicate it if you want to keep it not tassed)
  // @param opTableOfPersistentResultCells
  // Optional pointer of pointer of hash table containing all the result cells (at the right
  // of the journal) which are determined as persistent (give a not null pointer and the
  // table will be created and filled, so you must delete it) - not filled if returns FALSE
  // @return
  // TRUE or FALSE
  virtual CATBoolean IsAPersistentJournalForFastRun(CATCGMJournalList * ipJournal,
                                                    CATCGMHashTable * * opTableOfPersistentResultCells = NULL);

  // Determine if a whole Result Body is Persistent, which means all the followed cells are 
  // Persistent (followed cells are Faces, Edges and Vertices according to the Body dimension)
  // @param ipResultBody
  // The Result Body
  // @param ipResultJournal
  // Optional Journal of the Operation of which the previous Body is the Result
  // If a Journal is given the Followed cells will be also said Persistent according
  // to the previous service's rule (into a Journal Order, the Result (right/first/from))
  // is Persistent if all the Inputs (left/last/to) are Persistent)
  // This Journal is tassed, duplicate it if you want to keep it not tassed
  // @return
  // TRUE or FALSE
  virtual CATBoolean IsAPersistentResultForFastRun(CATBody           * ipResultBody,
                                                   CATCGMJournalList * ipResultJournal = NULL);
  
  // Create a New Body with all the same domains that the Old Result
  // @param oppJournal
  // Pointer of Pointer on an optional Journal, duplication of the Old One,
  // which is created or just inserted if *oppJournal != NULL
  // @return
  // The New Body
  // Scenario 0 rien n a change
  virtual CATBody * CreateNewResultEqualToOldResult(CATCGMJournalList * * oppJournal = NULL, CATResultIDForFastRun iResultID = 1);

  // Fonctionnalites CGMReplay
  // CGMReplay generic stream and unstream.  Read all old output bodies and journals.
  virtual void                WriteInput(CATCGMStream & ioStream, 
                                         CATGeoFactory* ipFactory);
  virtual void                ReadInput(CATCGMStream & ioStream, 
                                        CATGeoFactory* ipFactory);

  // The smartification status determines if the smartification is possible, and if it has been done.
  virtual void SetSmartificationStatusStoredForReplay(CATSmartificationStatus iStatus) 
    {_SmartificationStatusStoredForReplay = iStatus;}

  virtual void SetSmartLevelStoredForReplay(CATLONG32 iSmartLevel) 
    {_SmartLevelStoredForReplay = iSmartLevel;}

  virtual CATSmartificationStatus GetSmartificationStatusStoredForReplay() 
    {return _SmartificationStatusStoredForReplay;}

  virtual CATLONG32 GetSmartLevelStoredForReplay() {return _SmartLevelStoredForReplay;}

  INLINE CATBoolean GetUnstreamedFromAReplayFile() {return _UnstreamedFromAReplayFile;}

  INLINE void SetReadingReferenceResult(CATBoolean iReadingReferenceResult) {_ReadingReferenceResult = iReadingReferenceResult;}

  CATBoolean GetNewInputsByReportingType(CATListPtrCATBody & oNewInputsCopy, CATListPtrCATBody & oNewInputsNoCopy);

  CATBoolean GetOldInputsByReportingType(CATListPtrCATBody & oOldInputsCopy, CATListPtrCATBody & oOldInputsNoCopy);

  //For Debug/ODT purpose only.
  void SimulateGNBehaviorOnOldJournal();

  //                      CheckStatusForReplay
  //
  // June 09 WQO	Check generique pour sauvegarde CGMReplay
  // June 14 G5S  Ensure it builds when we generalize everything else for multi-result operators.
  // Mar  15 G5S  We only have one smart level and smartification status for the main context.
  //--------------------------------------------------------------------------
  virtual CATBoolean          CheckStatusForReplay(CATCGMOutput& os, 
                                                   CATString & KOreport);
  //------------------ Not yet generalized for multi-result operators.----------------------------------

  void                        SetStatusStoredForReplay(CATFastRunStatus iStatus);
  CATFastRunStatus            GetStatusStoredForReplay();

  //------------------ Not yet generalized for multi-result operators.----------------------------------

  virtual void                SetFastLevelPercentageStoredForReplay(double ipFastLevelPercentageStoredForReplay);
  virtual void                SetFastJournalSizeStoredForReplay(int ipFastJournalSizeStoredForReplay);
  virtual void                SetFastJournalSize(int ipOldJournalSize);
  virtual void                SetOldJournalSize(int ipOldJournalSize);
  virtual double              GetFastLevelPercentageStoredForReplay();
  virtual int                 GetFastJournalSizeStoredForReplay();
  virtual int                 GetFastJournalSize();
  virtual int                 GetOldJournalSize();
  //--------------------------------------------------------------------------------------------------

  INLINE int                  GetId() {return _ContextFastRun_Id;}

  CATUnicodeString            GetIdAsStringOfNCharacters(int N);

  // STATIC METHODS *************************************************************************************
  static CATBoolean           JournalContainsSomething(CATSoftwareConfiguration & iConfig, CATCGMJournalList & iJournalList);
  static CATLONG32            GetNumberOfResultsInJournal(CATCGMJournalList & iJournal, CATBoolean iGetFaces, CATBoolean iGetEdges, CATBoolean iGetVertices);
  static CATLONG32            GetNumberOfResultsInJournals(CATLISTP(CATCGMJournal) & iJournals, CATBoolean iGetFaces, CATBoolean iGetEdges, CATBoolean iGetVertices);
  static CATBoolean           CheckDomainDimension(CATBody * iBody,
                                                   CATBoolean iAcceptLumps,
                                                   CATBoolean iAcceptShells,
                                                   CATBoolean iAcceptWires,
                                                   CATBoolean iAcceptVIV);

  /** @nodoc @nocgmitf */
  INLINE CATString            GetInfoOnFastRunImpossible() {return _InfoOnFastRunImpossible;}

  // Smartification
  virtual CATBoolean          IsValidForSmartification(CATResultIDForFastRun iResultID = 1);
  virtual void                DoSmartification(CATSoftwareConfiguration * iConfig,
                                               CATBody *& ioOperatorResult,
                                               CATCGMJournalList * ioOperatorJournal,
                                               CATResultIDForFastRun iResultID = 1);

  void                        DoMultiSmartification(CATGeoFactory & iFactory,
                                                    CATSoftwareConfiguration & iConfig,
                                                    CATListPtrCATBody & iBodiesToSmartify,
                                                    ListOfCATResultIDForFastRun & iResultIDs,
                                                    CATListPtrCATBody & oSmartifiedBodies,
                                                    CATListPtrCATCGMJournal & ioToSmartifyJournals,
                                                    CATListPtrCATICGMObject * iObjectsToKeep = NULL,
                                                    ListOfListOfIntegers * iJournalCrossDependency = NULL);

  CATBody *                   DoSingleSmartification(CATGeoFactory            & iFactory,
                                                     CATSoftwareConfiguration & iConfig,
                                                     CATBody                  * ipNewResult ,
                                                     CATCGMJournalList        * ipNewJournal,
                                                     CATListPtrCATICGMObject  * iObjectsToKeep,
                                                     CATResultIDForFastRun      iResultID);

  INLINE CATString            GetInfoOnSmartificationImpossible() {return _InfoOnSmartificationImpossible;}

	// This tells us whether the input bodies in another context match the input bodies of this context.
  virtual CATBoolean InputBodiesMatch (CATContextForFastRun * pOtherCtx);

  //Methods called for all operators, inside CATCGMOperator::Run.
  virtual void BeforeRun_ContextFR();
  virtual void AfterRun_ContextFR();

  static CATBoolean CompareFastRunAttributes(
    CATFastRunAttribute & iOldOperationAttribute,
    CATFastRunAttribute & iNewOperationAttribute,
    CATContextForFastRunExt * iContextForDebug = NULL);

  virtual CATBoolean SetIgnoreAttributeManagement(CATBoolean iIgnoreAttributeManagement);

  static CATBoolean GetDoJournalCompletionBeforeRun();

  void WriteFastRunBodies(
    int & ioNbFastRunOldBodies, 
    CATListPtrCATICGMObject & ioAllObjects);

protected : 

  virtual CATContextForFastRunExt * GetInternalContextForFastRunExt(CATResultIDForFastRun iResultID);
	virtual CATContextForFastRunExt * GetInternalContextForFastRunExt(int i, CATResultIDForFastRun &oResultID);

  //Overload this function and move inside it all checks on forbidden options:
  //in this way the filter will be done very early (during BeforeRun) and you will avoid for example
  //an useless creation of a CATFastRunAttribute.
  virtual CATBoolean CheckForbiddenOptions();

  //Overload this function for multi-result contexts, otherwise it will set fast run status to impossible.
  //Parameter iUntilWhichLevel IS IGNORED FOR THE MOMENT! Implementation to be done...
  virtual void ContextJournalCompletion(short iUntilWhichLevel = 0);
  void SetDoJournalCompletion(CATBoolean iDoJournalCompletion);
  CATBoolean GetDoJournalCompletion();

	  CATBody              * GetOldOutput (CATResultIDForFastRun iResultID = 1);

  void CheckNoOrphanCreationInOldJournal();

  // Services internes de stream
  //------------------ Not yet generalized for multi-result operators.----------------------------------
  void                        WriteFastLevelToStream(CATCGMStreamImpl * pStrImpl);
  void                        ReadFastLevelFromStream(CATCGMStreamImpl * pStrImpl);
    //---------------------------------------------------------------------------------------------------

  void                        GenericDump(CATCGMOutput& os);
  virtual void                SpecificDump(CATCGMOutput& os);

virtual CATLONG32 GetNbOldJournalElementsRetrievedBySmartification() 
  {return _NbOldJournalElementsRetrievedBySmartification;}

    INLINE CATJournalUtilitiesForFastRun*  GetOldJournalUtilities() { return _OldJournalUtilities; }

  //---------------------------------------------------------------------------------------------------
  // Management of CATFastRunAttribute
  //---------------------------------------------------------------------------------------------------

  //The 3 functions to overload to integrate attribute mechanism for old/new parameter comparison
  virtual CATBoolean IsAttributeManagementActive();
  virtual void FillFastRunBuffer(CATCGMStream & oBuffer);
  virtual void TransferFastRunAttributeToResult();

  //Overload this function if you want to create a different type of CATFastRunAttribute
  virtual CATFastRunAttribute * AttributeCreation();

  //Function to retrieve all input CGM objects of the current operation
  virtual CATBoolean GetAllOperatorInputObjects(
    CATListPtrCATICGMObject * oInputsCopy,
    CATListPtrCATICGMObject * oInputsNoCopy,
    CATListPtrCATICGMObject * oInputsNeutral);

  //Overload this function if the retrieval of old operation attribute is more complex (multi result cases?)
  virtual CATFastRunAttribute * RetrieveOldOperationAttribute();

  //Tools for parameter comparisons, to be called by children classes
  CATFastRunAttribute * GetFastRunAttribute();
  CATBoolean IsThereAFastRunAttribute();
  virtual void TransferFastRunAttribute(CATBody * iNewResult);
  CATFastRunAttribute * GetOrRetrieveOldOperationAttribute();
  
  //---------------------------------------------------------------------------------------------------
  
private:

  void PrivateAddInput(
    CATBody * iOldInput,
    CATListPtrCATCell * iOldInputFollowedCells,
    CATBody * iNewInput);

  void PrivateSetOldResult(
    CATBody * iOldOutput,
    CATListPtrCATCell * iOldOutputFollowedCells,
    CATCGMJournalList * iOldJournal,
    CATBoolean iJournalCompleted);

  void PrivateSetSubstitueOldInputList(
    CATLISTP(CATBody) & iOldInputList,
    CATListPtrListPOfCATCell * iOldInputsFollowedCells);

  CATListPtrCATCell * GetOldInputFollowedCells(int iIdx);
  CATListPtrCATCell * GetOldOutputFollowedCells();
  CATBoolean GetJournalCompleted();

  CATBoolean AreFollowedCellsDefined();
  void GetCellsToFollowByType(
    CATAdaptiveHashTable & oCopyCellsToFollow,
    CATAdaptiveHashTable & oNoCopyCellsToFollow,
    CATAdaptiveHashTable & oResultCellsToFollow);
  void CompleteJournalUsingFollowedCells();

  void CompleteJournalUsingBodies();

  void ComputeFollowedCellsForAllBodies();

  void CallCGMJournalCompletion();

  CATCGMJournalList * DuplicateOldJournal();

  void CheckFastRunAntiVariable();

  void DumpFastRunStatusChange();
  void DumpSmartificationStatusChange();

  void SetSmartificationDone(int iNbOldJournalElementsRetrievedBySmartification);

  virtual void SetSmartificationStatus(CATSmartificationStatus iStatus);

  virtual void SetNbOldJournalElementsRetrievedBySmartification(CATLONG32 iVal) 
  {_NbOldJournalElementsRetrievedBySmartification = iVal;}

  //Private methods for management of CATFastRunAttribute
  void CreateFastRunAttributeAndFillBuffer();
  void DumpCallStackOfBufferFilling(size_t iAfterWhichByte);
  void CheckPersistencyOfOperationParameters();
  void CheckThatAllOperationInputsAreInContext();
  void CheckPersistencyOfOptionsAndObjects();
  CATBoolean GetIgnoreAttributeManagement() {return _IgnoreAttributeManagement;}

  //Friends will be friends
  friend void AttributeFillerForContext(CATCGMStream&, void *);

  // DEPRECATED
  // If smartification is able to do something, the function returns the body after smartification, and oSubstitutionsJournal
  //  contains the substitution orders.
  // Else, oSubstitutionsJournal is NULL, and a NULL pointer is returned too.
  // ATTENTION: if iNewResult is Modifiable, modifications are done inside it, and so iNewResult is returned.
  // DEPRECATED
  virtual CATBody *           SmartifyBody(CATSoftwareConfiguration *  iConfig,
                                           CATCGMJournalList        *& oSmartificationJournal,
                                           CATBody                  *  iOperatorResult,
                                           CATCGMJournalList        *  iOperatorJournal, 
                                           CATResultIDForFastRun iResultID = 1);

  //Private methods for CGMReplay
  INLINE void SetUnstreamedFromAReplayFile(CATBoolean iUnstreamedFromAReplayFile) {_UnstreamedFromAReplayFile = iUnstreamedFromAReplayFile;}
  INLINE CATBoolean GetReadingReferenceResult() {return _ReadingReferenceResult;}
  void StoreNbOldResultsComingFromStream(int iNbInternalContexts);
  void StoreFastRunStatusComingFromStream(CATFastRunStatus iUnstreamedFastRunStatus);
  void StoreFastLevelComingFromStream(CATLONG32 iUnstreamedFastLevel);
  void StoreFastLevelPercentageComingFromStream(double iUnstreamedFastLevelPercentage);
  void StoreSmartificationStatusComingFromStream(CATSmartificationStatus iUnstreamedSmartificationStatus);
  void StoreSmartLevelComingFromStream(CATLONG32 iUnstreamedSmartLevel);

  // Donnees generiques d un contexte 
  CATTopOperator            * _Operator;
  CATContextForFastRun      * _Interface;
  CATLISTP(CATBody)           _OldInputs;
  CATListPtrListPOfCATCell    _OldInputsFollowedCells;
  CATLISTP(CATBody)           _NewInputs;

  // The _ResultIDList and _InternalContextList are kept in step and they don't have an entry if we're not in
	// the multi result case and therefore we're not using internal contexts.
	ListOfCATResultIDForFastRun         _ResultIDList;  
	ListPOfCATContextForFastRunInternal _InternalContextList;

  CATBody                   * _OldOutput;
  CATListPtrCATCell         * _OldOutputFollowedCells;
  CATCGMJournalList         * _OldJournal;
  CATBoolean                  _JournalCompleted;

  // Donnees d interpretations
  CATMultiPAD*                    _pMultiPAD;
  CATJournalUtilitiesForFastRun * _OldJournalUtilities;

  // Smartification status/level
  CATSmartificationStatus     _SmartificationStatus;
  CATString                   _InfoOnSmartificationImpossible;
  CATLONG32                   _NbOldJournalElementsRetrievedBySmartification;
  // Journal des operations recuperees du Old Result et donc economisees (i.e. Fast)
  CATCGMJournalList         * _FastJournal;

  // Fast run status/level
  CATFastRunStatus            _FastRunStatus;
  CATString                   _InfoOnFastRunImpossible;
  CATLONG32                   _FastJournalSize;
  CATLONG32                   _OldJournalSize;

  // Donnees pour le CGMReplay
  CATFastRunStatus            _FastRunStatusStoredForReplay;
  CATSmartificationStatus     _SmartificationStatusStoredForReplay;
  double                      _FastLevelPercentageStoredForReplay;
  CATLONG32                   _FastJournalSizeStoredForReplay;
  CATLONG32                   _SmartLevelStoredForReplay;
  CATBoolean                  _UnstreamedFromAReplayFile;
  CATBoolean                  _ReadingReferenceResult;

  short                       _LevelToExecute; // Versionning CGM

  static int                  _ContextFastRun_MaxId;
  int                         _ContextFastRun_Id;

  // Data for attribute management
  CATFastRunAttribute       * _NewOperationAttribute;
  CATFastRunAttribute       * _OldOperationAttribute;
  CATBoolean                  _IgnoreAttributeManagement;

  // Data for journal completion
  CATBoolean _DoJournalCompletion;
};

#endif
