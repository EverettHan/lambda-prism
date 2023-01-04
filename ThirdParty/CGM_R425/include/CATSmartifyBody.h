#ifndef CATSmartifyBody_H
#define CATSmartifyBody_H

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATDataType.h"
#include "CATSmartificationStatus.h"

class CATGeoFactory;
class CATBody;
class CATTopData;
class CATExtTopOperator;
class CATCGMJournalList;
class CATSmartifyBodyExt;
class CATListPtrCATBody;
class CATListPtrCATCGMJournal;
class CATListPtrCATICGMObject;
class CATCGMOutput;
class CATListValCATUnicodeString;
class ListOfListOfIntegers;
class CATString;

/** 
 * Class representing the operator that takes a body <ToSmartify>, and creates a result body that:
 *  1) will be geometrically identical to the input body <ToSmartify>
 *  2) will share as many geometrical and topological elements with another body <Reference>
 */
class ExportedByCATTopologicalObjects CATSmartifyBody : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATSmartifyBody);

public:

  /**
  * @nodoc @nocgmitf
  */
  virtual ~CATSmartifyBody();

  /**
  * @nodoc @nocgmitf
  * To be called before Run.
  * Activates or deactivates journaling.
  * If not called, journaling is done by default.
  */
  virtual void SetDoJournaling(CATBoolean iDoJournaling);

  /**
  * @nodoc
  * To be called before Run.
  * Activates or deactivates journaling on internal cells.
  * If not called, journaling on internal cells is not done by default.
  */
  virtual void SetFullJournal(CATBoolean iFullJournal);

  /**
  * @nodoc @nocgmitf
  * To be called after Run.
  * If the operation was done on 1 body
  *  - returns the result of the transformation of that body
  *  - at first call, fills TopData journal with operation journal (if journaling is active)
  * If the operation was done on more than 1 body, returns NULL:
  * use GetSmartifiedBody in that case.
  */
  virtual CATBody * GetResult();

  /**
  * @nodoc
  * To be called after Run.
  * Value representing the efficacy of smartification (a.k.a. "smart level").
  * The real meaning of this value depends on the method used to create the operator,
  * because different types of smartification exist.
  */
  virtual CATLONG32 GetNbRetrieved1stLevelElements();

  /**
  * @nodoc
  * To be called after Run.
  * Returns the result of the transformation of the body at position iIdx in input list.
  * If ioJournal is not NULL and journaling is active,
  * the journal describing the transformation of the body is duplicated inside ioJournal.
  */
  virtual CATBody * GetSmartifiedBody(int iIdx, CATCGMJournalList * ioJournal);

  /**
  * @nodoc @nocgmitf
  * Static "oneliner" to execute smartification on a list of bodies.
  * Main features:
  * - iBodiesToSmartify[i] is associated to iReferenceBodies[i], ioToSmartifyJournals[i] and iReferenceJournals[i].
  * - The cells to replace are found by making a comparison between journals.
  * - oSmartifiedBodies[i] will contain the result of smartification of input iBodiesToSmartify[i]
  * - journals of list ioToSmartifyJournals are automatically updated according to the operation
  * - "smart level" is returned
  */
  static CATSmartificationStatus SmartifyBodiesAndUpdateJournals(
    CATGeoFactory & iFactory,
    CATSoftwareConfiguration & iConfig,
    CATListPtrCATBody & iBodiesToSmartify,
    CATListPtrCATBody & iReferenceBodies,
    CATListPtrCATBody & oSmartifiedBodies,
    CATListPtrCATCGMJournal & ioToSmartifyJournals,
    CATListPtrCATCGMJournal & iReferenceJournals,
    CATListPtrCATICGMObject * iObjectsToKeep = NULL,
    ListOfListOfIntegers * iJournalCrossDependency = NULL,
    CATLONG32 * oSmartLevel = NULL,
    CATString * oReasonOfFailure = NULL,
    CATString * oSmartifInfo = NULL);

  /**
  * @nodoc @nocgmitf
  * Same as "SmartifyBodiesAndUpdateJournals", but for the single-result case.
  */
  static CATSmartificationStatus SmartifyOneBodyAndUpdateJournal(
    CATGeoFactory & iFactory,
    CATSoftwareConfiguration & iConfig,
    CATBody * iBodyToSmartify,
    CATBody * iReferenceBody,
    CATBody *& oSmartifiedBody,
    CATCGMJournalList * ioToSmartifyJournal,
    CATCGMJournalList * iReferenceJournal,
    CATListPtrCATICGMObject * iObjectsToKeep = NULL,
    CATLONG32 * oSmartLevel = NULL,
    CATString * oReasonOfFailure = NULL);

  /**
  * @nodoc @nocgmitf
  */
  static CATSmartificationStatus SmartifyAfterOperationAndUpdateJournal(
    CATGeoFactory & iFactory,
    CATSoftwareConfiguration & iConfig,
    CATBody *& ioOperationResult, //pointer is modified by the method!
    CATCGMJournalList * ioOperationJournal, //journal content is modified by the method!
    ListPOfCATBody * iOperationCopyInputs,
    ListPOfCATBody * iOperationNOCopyInputs,
    CATBoolean iFullJournal = FALSE,
    CATLONG32 * oSmartLevel = NULL,
    CATString * oReasonOfFailure = NULL);

  /**
  * @nodoc @nocgmitf
  * Creates a CATSmartifyBody from a CATSmartifyBodyExt.
  */
  static CATSmartifyBody * Create(CATSmartifyBodyExt & iExtensible);

  /**
  * @nodoc @nocgmitf
  * Returns the ID of the operator.
  */
  virtual const CATString * GetOperatorId();

  /**
  * @nodoc @nocgmitf
  * To be called after Run.
  * Updates ioJournal, replacing its cells
  * if they were impacted by the operation.
  * This method is independent from journaling options:
  * it works even if SetDoJournaling(FALSE) was called,
  * or if the journal of CATTopData is NULL.
  */
  virtual void UpdateJournalItems(CATCGMJournalList & ioJournal);

  /**
  * @nodoc
  * Internal use only.
  */
  CATBoolean CheckAfterRun(CATListValCATUnicodeString & oSucceeding, CATListValCATUnicodeString & oFailing);

protected:

  CATSmartifyBody(CATGeoFactory * iFactory, CATTopData * iTopData, CATExtTopOperator * iExtensible);
  virtual int RunOperator();
  CATSmartifyBodyExt & GetSmartifyBodyExt();

  virtual void RequireDefinitionOfInputAndOutputObjects();

private:

  virtual CATBody* GetResult(CATCGMJournalList* iJournal);
};

#endif

