#ifndef __CATContextForFastRun_H__
#define __CATContextForFastRun_H__
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//
//  In order to accelerate the update of an operator run,
//  the context regroups the previous run informations
//  see http://wikigm/mediawiki/index.php/Fast_Update
//  It is now generalized to deal with multi-result operators except:
//  GetFastJournal(), GetFastLevel().
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

#include "CATGMModelInterfaces.h"
#include "ListPOfCATBody.h"
#include "CATFastRunStatus.h"
#include "CATSmartificationStatus.h"
#include "CATDataType.h"
#include "CATString.h"
#include "CATListOfCATCGMJournals.h"
#include "CATResultIDForFastRun.h"

class CATBody;
class CATTopology;
class CATCGMJournalList;
class CATContextForFastRunExt;
class CATCGMOutput;
class CATCGMStream;
class CATGeoFactory;
class CATTopData;
class CATCGMHashTable;
class CATTopOperator;
class CATListPtrCATICGMObject;
class CATContextForFastRunAdapt;
class CATCGMBodyAndCells;

#define FASTRUNMULTIRESULT
#define FASTRUN_InternalContexts

class ExportedByCATGMModelInterfaces CATContextForFastRun
{
protected:

  /**
   * Constructor
   */
  CATContextForFastRun();

  /**
   * Destructor
   */
  virtual ~CATContextForFastRun();

public:

  /**
   * Set number of results you expect.   We use internal contexts, so result IDs are 2, 3, 4 etc.
   */
	virtual void SetNbOldResults(int iNbOldResults);

  /**
   * Get the internal context for a particular Result ID.  
   * if (ResultID == 1) {
   *   if (We're using internal contexts)
   *     return NULL;
   *   else
   *     return this;
   * Throw if the internal context list is incomplete.
   */
  virtual CATContextForFastRun * GetInternalContextForFastRun(CATResultIDForFastRun iResultID);

  /**
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
  virtual CATContextForFastRun * GetInternalContextForFastRun(int i, CATResultIDForFastRun &oResultID);

  virtual CATLONG32 GetNbInternalContextForFastRun();

  /**
   * Get owning context.  This is NULL for a context that isn't an internal one.
   */
  virtual CATContextForFastRun * GetOwningContext();

  /**
   * Returns the type of Context
   */
  virtual CATString GetType(); 

  /**
   * Attributes interfaces (no AddRef neither Release to do)
   */
  virtual void AddInput(CATBody * iOldInput, CATBody * iNewInput);

  /**
   * Defines a couple of old/new input body of the operation, by specifying also the cells to follow of the old input.
   * @param iOldInputAndFollowedCells
   *   The structure containing the old input body and its cells to follow.
   * @param iNewInput
   *   The new input body.
   */
  virtual void AddInput(
    CATCGMBodyAndCells & iOldInputAndFollowedCells,
    CATBody * iNewInput);

  virtual void ChangeNewInput(CATBody * iOldInput, CATBody * iNewInput);

  /**
   * Add a new output body and journal, being careful to obey the rules about Internal contexts and 
   * ResultIDs stated at the top of this file.  We use GetInternalContextForFastRun to check this.
   * If the result ID has already been used, replace the data instead of throwing (JHN, 23/06/2014).  
   * Don't throw if iOldOutput == NULL or iOldJournal == NULL.
   * If we create a new internal context and _OldOutput or _OldJournal has been set, throw.
   * Warning: If other data has been set and we create our first internal context, that data will
   * cease to be accessible.
   */
  virtual void SetOldResult(CATBody * iOldOutput, CATCGMJournalList * iOldJournal, CATResultIDForFastRun iResultID = 1);

  /**
   * Defines the old result and old journal of the operation, by specifying also the cells to follow of the old result.
   * @param iOldOutputAndFollowedCells
   *   The structure containing the old result body and its cells to follow.
   * @param iOldJournal
   *   The old journal.
   */
  virtual void SetOldResult(
    CATCGMBodyAndCells & iOldOutputAndFollowedCells,
    CATCGMJournalList * iOldJournal);

  virtual const CATLISTP(CATBody) * GetNewInputList();

  virtual const CATLISTP(CATBody) * GetOldInputList();

  /**
   * Get journal list or result body for a particular ResultID.  If the body with that ID doesn't exist, 
   * return NULL.
   */
  virtual CATCGMJournalList * GetOldJournal(CATResultIDForFastRun iResultID = 1);

  virtual CATBody * GetOldResult(CATResultIDForFastRun iResultID = 1);

  /* 
   * Get all journals, results, result IDs, smaritification statuses or numbers of old journal elements
   * retrieved by smartification.
   */
  virtual void GetAllOldResult  (ListPOfCATBody & oOldResultList);
  virtual void GetAllOldJournal (CATLISTP(CATCGMJournal) & oOldJournalList);
  virtual void GetAllResultIDs   (ListOfCATResultIDForFastRun & oResultIDList);

  // Get the default result ID.
  virtual CATResultIDForFastRun GetResultID();

/*-------------------------------------------------------------------------------------------------------
 Define methods to set data from or copy data to another context.
 Warnings:
   These functions does not check whether we have a main context or an internal context.  
   It is recommended that they are called for main contexts only (not internal contexts) 
   because only main contexts are guaranteed to have up to data data apart from the OldResults and 
   OldJournals.  
   If there are internal contexts in this or the other context, we must use these or their result IDs to
   copy OldResults and OldJournals.  GetAllOldResult(), GetAllOldJournal() and GetAllResultIDs() from this
   or pOtherCtx can be very helpful for this.   
   If there are no internal contexts, the OldResult and OldJournal will automatically be forwarded.

 SetDataFromAnotherContext:
 Copying the Context input and output data from another Context.  
 If there are any inconsistencies between the other context and
 data that has already been set in this context, throw.
 If smartification of a result body is impossible, transfer that information.
 Only transfer the input bodies if we don't already have input bodies in this context.

 2014 Nov   12  The Result ID doesn't have to exist in the other context.                G5S
 2015 Mar   10  There is only one smart level and smartification status.
  */
  virtual void SetDataFromAnotherContext(CATContextForFastRun * pOtherCtx);

  /**
   * Set fast run status, smartification status and number of old journal elements retrieved by smartification.  
   * We are allowed to have a NULL output body (JHN, 23/06/2014)
   * 2015 Mar   10  There is only one smart level and smartification status.
   */
  virtual void SetStatusFromAnotherContext(CATContextForFastRun * pOtherCtx);

  /**
   * Copying the Context input data in another Context.  If there are any inconsistencies between this
   * context and data that has already been set in the other context, throw.
  /* 2014 Jun   06  We no longer forward the smartification status.                        G5S
   */
  virtual void ForwardInputInAnotherContext(CATContextForFastRun * pOtherCtx);

  /**
  *  Copying the Context old output data to another Context. 
  *  2014 Nov   11  The Result ID doesn't have to exist in this context.                   G5S
  *  2015 Mar   10  There is only one smart level and smartification status.               G5S
  *
  * Restrictions:
  *    If neither this context nor the other contain internal contexts and 
  *    Fast run status != Impossible, we will overwrite the output data for the other
  *    context.
  */
  virtual void ForwardOutputInAnotherContext(CATContextForFastRun * pOtherCtx);
/*-------------------------------------------------------------------------------------------------------*/

  /**
   * Set Substitute List to replace the actual one
   */
  virtual void SetSubstitueNewInputList(CATLISTP(CATBody) & SubstitueNewInputList);

  virtual void SetSubstitueOldInputList(CATLISTP(CATBody) & SubstitueOldInputList);

  /**
   * Call this method to prohibit both "fast run" and "smartification"
   */
  virtual void SetStatusImpossible(const char * Info = "");

  /**
   * Call this method to prohibit "fast run"
   */
  virtual void SetFastRunStatusImpossible(const char * Info = "");

  virtual CATFastRunStatus GetStatus();

  /**
   * Search the given body in new input list and, if it finds it, compare it to
   * the corresponding old body to determine if they are equal, i.e. they have
   * the same cells (same pointers for cells of the given dimension) 
   * @param ipNewInputBody
   * The New Input Body which has to be compare to its corresponding old one
   * @param iDimensionToCompare
   * How far down the diagnostic goes, by default -1 implies 
   * a dimension of comparison equal to the body highest cells dimension
   * @return
   * True if equality, False if not or if the Body is not found in the context list
   */
  virtual CATBoolean IsEqualToOldCorrespondingInput(CATBody * ipNewInputBody,
                                                    int       iDimensionToCompare = -1);

  /**
   * Compare both input bodies to verify if they are equal
   * By default, the comparison verifies if they have the same cells 
   * (same pointers for cells of the given dimension)
   * @param ipOldInputBody
   * First body to compare
   * @param ipNewInputBody
   * Second body to compare
   * @param iDimensionToCompare
   * How far down the diagnostic goes, by default -1 implies 
   * a dimension of comparison equal to the new body highest cells dimension
   * @return
   * True if equality, False if not or if an input pointer is NULL
   */
  virtual CATBoolean AreTheyEqualInputBodies(CATBody * ipOldInputBody,
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

  /**
   * Compare both input parameters (real) to verify if they are equal
   * By default, the comparison verifies if they are strictly equal (bitwise)
   * This could be overloaded according to each operator rules
   * @param iOldInputValue
   * First parameter to compare
   * @param iNewInputValue
   * Second parameter to compare
   * @return
   * True if equality, False if not
   */
  virtual CATBoolean AreTheyEqualInputParameters(double iOldInputValue, 
                                                 double iNewInputValue);

  //------------------ Not yet generalized for multi-result operators.----------------------------------
  /**
   * Fast Journal gives not computed operations which have been retrieved from Old Run.
   * @return
   * The pointer to the Fast Journal
   */
  virtual CATCGMJournalList * GetFastJournal();

  /**
   * A comparison, between Fast and Old journals, completes the Status to control Fast Run level
   * Implemented only for some context (Toolbox apporach).  Not yet generalized for multi-result
   * operators.
   * @param opOldJournalSize
   * Optional pointer to the size of the Old Journal
   * @param opLevelPercentage
   * Optional pointer to the quotient Fast on Old in percentage (100xFast/Old)
   * @return
   * The size of the Fast Journal
   */
  virtual CATLONG32 GetFastLevel(CATLONG32 * opOldJournalSize = NULL, double * opLevelPercentage = NULL);
  //-----------------------------------------------------------------------------------------------------------

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
  /**
   * The status determines if the smartification is possible, and if it has been done
   */
  virtual CATSmartificationStatus GetSmartificationStatus();

  /**
   * To forbid the Smartification (manual and automatic calls), Info gives optionally the reason for that
   */
  virtual void SetSmartificationStatusImpossible(const char * Info = "");
  
  /**
   * For operators implementing Smartification, it returns the number of OldJournal elements that are
   * inside the new resulting body.
   * If no Smartification is done, it is equal to the FastLevel.
   * Implemented only for some context (Toolbox apporach)
   * @return
   * The number of OldJournal elements that are inside the new resulting body
   */
  virtual CATLONG32 GetSmartLevel();

  /**
   * Complete and in one line visualization stream
   */
  virtual void Dump( CATCGMOutput & os );

  virtual CATString GetStatusInfo();

  //------------------ Not yet generalized for multi-result operators.----------------------------------
  /**
  * Check made at the end of a CGMReplay replay
  */
  virtual CATBoolean CheckStatusForReplay(CATCGMOutput & os, CATString & KOreport);
  //----------------------------------------------------------------------------------------------------

  /**
   * For CGM only
   */
  virtual void SetOperator(CATTopOperator* ipOperator);

  /**
   * For CGM only
   */
  virtual void SetInterface(CATContextForFastRun* ipInterface);

  /**
   * For CGM only
   */
  virtual CATContextForFastRunExt * GetExtensible();

	// This tells us whether the input bodies in another context match the input bodies of this context.
  virtual CATBoolean InputBodiesMatch (CATContextForFastRun * pOtherCtx);

  /**
   * If this context is of type CATContextForFastRunAdapt, returns the casted pointer.
   */
  virtual CATContextForFastRunAdapt * CastToAdapt();

  /**
   * For CGM only
   */
  virtual void BeforeRun_ContextFR();

  /**
   * For CGM only
   */
  virtual void AfterRun_ContextFR();

  /**
   * For CGM only
   */
  virtual CATBoolean SetIgnoreAttributeManagement(CATBoolean iIgnoreAttributeManagement);

  /**
  * Increases the reference count.
  * Reference count is set to 1 at construction.
  * Object is deleted as soon as the reference count is decreased to 0.
  */
  void AddRef();
  
  /**
  * Decreases the reference count.
  * Reference count is set to 1 at construction.
  * Object is deleted as soon as the reference count is decreased to 0.
  */
  void Release();

  /**
  * @deprecated
  * DO NOT USE
  */
  int IsNull();

  /**
  * @deprecated
  * DO NOT USE: this function always returns NULL
  */
  static const char * MetaObject();

protected:

  friend class CATContextForFastRunAdapt;

  /**
   * Use this function to attach the fast run attribute containing all operator parameters to body iNewResult.
   */
  virtual void TransferFastRunAttribute(CATBody * iNewResult);

  /**
   * The status change is restricted, to set to impossible, use SetStatusImpossible
   * The following interface is restricted to Context responsible only
   */
  virtual void SetStatus(CATFastRunStatus iStatus);

  /**
   * Determine what is Persistent, Appeared or Disappeared between old and new inputs
   * @param iInfDimension
   * How far down the diagnostic goes (by default is the 2D cells, which means the Faces) 
   * @param StopToFirstNonPersistent
   * To stop the diagnostic process to the first found non-persistent cell 
   * @return
   * A Status linked to the persitency (Possible if all is persitent, Impossible if  
   * it is asked and stopped to a first non-persistent, Unset otherwise)
   */
  virtual CATFastRunStatus ComputeMultiPAD(int        iInfDimension            = 2,
                                           CATBoolean StopToFirstNonPersistent = FALSE);

  /**
   * Determine if a specific Cell is Persistent, which means the cell is the same
   * in the corresponding old and new imput
   * @param ipTopoObj
   * The cell
   * @param iRecursiveSearch 
   * DEPRECATED option
   * @param oInWhichBody
   * Index of input bodies where the cell is persistent (first bodies couple), 0 otherwise
   * @return
   * TRUE or FALSE
   */
  virtual CATBoolean IsPersistentForFastRun(CATTopology * ipTopoObj,
                                            CATBoolean    iRecursiveSearch = FALSE,
                                            int         * oInWhichBody     = NULL);

  /**
   * Determine if a whole Journal is Persistent, which means all the left cells are Persistent
   * for order Creation, Modification, Subdivision and Absorption (Delete and Keep are not considered) 
   * @param ipJournal
   * The Journal (which is tassed, duplicate it if you want to keep it not tassed)
   * @param opTableOfPersistentResultCells
   * Optional pointer of pointer of hash table containing all the result cells (at the right
   * of the journal) which are determined as persistent (give a not null pointer and the
   * table will be created and filled, so you must delete it) - not filled if returns FALSE
   * @return
   * TRUE or FALSE
   */
  virtual CATBoolean IsAPersistentJournalForFastRun(CATCGMJournalList * ipJournal,
                                                    CATCGMHashTable * * opTableOfPersistentResultCells = NULL);

  /**
   * Determine if a whole Result Body is Persistent, which means all the followed cells are 
   * Persistent (followed cells are Faces, Edges and Vertices according to the Body dimension)
   * @param ipResultBody
   * The Result Body
   * @param ipResultJournal
   * Optional Journal of the Operation of which the previous Body is the Result
   * If a Journal is given the Followed cells will be also said Persistent according
   * to the previous service's rule (into a Journal Order, the Result (right/first/from))
   * is Persistent if all the Inputs (left/last/to) are Persistent)
   * This Journal is tassed, duplicate it if you want to keep it not tassed
   * @return
   * TRUE or FALSE
   */
  virtual CATBoolean IsAPersistentResultForFastRun(CATBody           * ipResultBody,
                                                   CATCGMJournalList * ipResultJournal = NULL);

  /**
   * Create a New Body with all the same domains that the Old Result
   * @param oppJournal
   * Pointer of Pointer on an optional Journal, duplication of the Old One,
   * which is created or just inserted if *oppJournal != NULL
   * @return
   * The New Body
   */
  virtual CATBody * CreateNewResultEqualToOldResult(CATCGMJournalList * * oppJournal = NULL,
    CATResultIDForFastRun iResultID = 1);

  CATContextForFastRun * _Extensible;

private:
  int _RefCount;

};

#endif /* CATContextForFastRun_h_ */
