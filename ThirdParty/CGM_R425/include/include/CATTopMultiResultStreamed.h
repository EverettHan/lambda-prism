#ifndef CATTopMultiResultStreamed_h_
#define CATTopMultiResultStreamed_h_

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2020
//
// DESCRIPTION :
//     Declaration of methods for Read/Write output of
//     CGMReplays with multiple results
//
// Dec. 20	Creation                                                     DLR6
//=============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMOperator.h"
#include "CATTopMultiResult.h"
#include "CATIACGMLevel.h"

#include "CATCGMVirtualMacros.h"

#include "CATMathInline.h"

#include "CATBoolean.h"
#include "CATBodyFreezeMode.h"
#include "ListPOfCATBody.h"
#include "CATUnicodeString.h"

class CATExtTopMultiResult;
class CATTopData;
class CATGeoFactory;
class CATCGMJournalList;

class CATBody;

class CATSubdArrayInt;

class ExportedByCATTopologicalObjects CATTopMultiResultStreamed : public CATTopMultiResult
{
  CATCGMVirtualDeclareClass(CATTopMultiResultStreamed);

public :

  virtual ~CATTopMultiResultStreamed();

protected:

  //----------------------------------------------------------------------------------
  // Explicit import of constructors of mother CATTopMultiResult
  //----------------------------------------------------------------------------------

#ifdef CATIACGMR215CAA
  /**
   * @nodoc
   * New constructors, same signatures than CATTopOperator, for migration
   * Creates a CATTopMultiResult operator.
   * @param iMultiResultModeByDefault
   * To set the default mode since some operator can be Mono-result or Multi-result
   * @param iForCreation
   * The pointer to the factory where the resulting bodies are created.
   */
  CATTopMultiResultStreamed(CATBoolean             iMultiResultModeByDefault,
                            CATGeoFactory        * iFactory, 
                            CATTopData           * iTopData,
                            CATBodyFreezeMode      iBodyFreezeMode = CATBodyFreezeOn,
                            CATExtTopMultiResult * iExtensible = NULL);
   
   /** @nodoc */
  CATTopMultiResultStreamed(CATBoolean             iMultiResultModeByDefault,
                            CATGeoFactory        * factory, 
                            CATCGMJournalList    * journal = NULL,
                            CATBodyFreezeMode      iBodyFreezeMode = CATBodyFreezeOn,
                            CATExtTopMultiResult * iExtensible = NULL);
#else
  /**
   * @nodoc
   * Creates a CATTopMultiResult operator.
   * @param iForCreation
   * The pointer to the factory where the resulting bodies are created.
   */
  CATTopMultiResultStreamed(CATGeoFactory * iForCreation, CATExtTopMultiResult *iExtensible = NULL);
  /**
   * @nodoc
   * Creates a CATTopMultiResult operator.
   * @param iForCreation
   * The pointer to the factory where the resulting bodies are created.
   */
  CATTopMultiResultStreamed(CATGeoFactory * iForCreation, CATTopData * iTopData, CATExtTopMultiResult *iExtensible = NULL);
#endif

  //----------------------------------------------------------------------------------
  // STREAM MULTIPLE RESULTS
  //----------------------------------------------------------------------------------

  virtual void WriteInput (CATCGMStream & ioStream);
  virtual void WriteTopOutput(CATCGMStream &Str);

private:
  static  void RenameBodiesByPositionInList(const ListPOfCATBody& iListBodies, CATUnicodeString iNameBodiesOfList);

protected:

  virtual void DumpOutput( CATCGMOutput& os );

  virtual CATTopCheckJournal* ReadTopOutput(CATCGMStream &Str);

  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput &os);
  virtual CATBoolean  ValidateTopOutput(CATTopCheckJournal* iEquivalent, CATCGMOutput &os);


  /* Parametrize the behaviour of ValidateOutput to accept / reject results if they are mapped to the reference
   * but in a different order.
   *
   * It should always have the same value for all child operators depending on their class :
   * For each child operator of MultiResult, either they should ALWAYS accept results in a different order
   * or they should ALWAYS forbid it.
   * This should be set in the constructor of each child of CATTopMultiResultStreamed that allows for record of CGMReplay.
   * If it is not, different orders of results will be accepted by default, with a print of warning.
   */
  INLINE  void        AuthoriseResultsInADifferentOrder(CATBoolean iDoAuthoriseIt);
  INLINE  CATBoolean  ResultsInADifferentOrderWouldBeValid();
  

public:
  INLINE  CATBoolean  InvalidResultsAreTolerated();
  INLINE  void        AuthoriseInvalidResults(CATBoolean iDoAuthoriseIt);
  INLINE  void        DoCheckValidityOfResultBodies(CATBoolean iDoCheckIt);
  CATLONG32 GetNumCur();
  CATBody* RetrieveResult();


private :

  CATLONG32               _nbReferenceBodies;
  CATBody             **  _pReferenceBodies;
  CATCGMJournalList   **  _pReferenceJournals;

  CATBoolean              _authoriseResultsInDifferentOrder;
  // if FALSE and results are not in the same order as reference, then ValidateOutput will return FALSE

  CATBoolean              _authoriseInvalidResultBodies;
  CATBoolean              _checkValidityOfResultBodies;
  // FALSE by default
  // If TRUE and some bodies are invalid in CATChecker, then CheckOutput will return a Warning instead of an error

  //----------------------------------------------------------------------------------
  // Helper methods for mapping results to references
  //----------------------------------------------------------------------------------

  CATBoolean  DoBodyMapping(CATBody** ipResultBodies, CATSubdArrayInt& oIndexMatchingRefBody, CATCGMOutput &os, CATBoolean iPrintWarningIfBodiesDifferentOrder = TRUE);
  CATBoolean  DoJournalMapping(CATBody** ipResultBodies, CATCGMJournalList** ipResultJournals, const CATSubdArrayInt& iIndexMatchingRefBody, CATCGMOutput &os);

  static  CATBoolean  BodiesAreMapped(const CATBody* ipBodyA, const CATBody* ipBodyB, short iSilenceMapping);

};

INLINE  void        CATTopMultiResultStreamed::AuthoriseResultsInADifferentOrder(CATBoolean iDoAuthoriseIt)
{
  _authoriseResultsInDifferentOrder = iDoAuthoriseIt;
}

INLINE  CATBoolean  CATTopMultiResultStreamed::ResultsInADifferentOrderWouldBeValid()
{
  return _authoriseResultsInDifferentOrder;
}

INLINE  void        CATTopMultiResultStreamed::AuthoriseInvalidResults(CATBoolean iDoAuthoriseIt)
{
  _authoriseInvalidResultBodies = iDoAuthoriseIt;
}

INLINE  void        CATTopMultiResultStreamed::DoCheckValidityOfResultBodies(CATBoolean iDoCheckIt)
{
  _checkValidityOfResultBodies = iDoCheckIt;
}

INLINE  CATBoolean  CATTopMultiResultStreamed::InvalidResultsAreTolerated()
{
  return _authoriseInvalidResultBodies;
}


#endif // CATTopMultiResultStreamed_h_

