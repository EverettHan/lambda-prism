#ifndef CATTopMultiResult_h_
#define CATTopMultiResult_h_

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATMathConstant.h"

class CATString;
class CATGeoFactory;
class CATBody;
class CATCGMJournalList;
class CATSoftwareConfiguration;
class CATExtTopMultiResult;

/**
*  ***********************************************************************
*  *******                         WARNING                         *******
*  ***********************************************************************
*  *******
*  *******  This class is Not supported any longer.
*  *******  it has been replaced by CATICGMTopMultiResult
*  *******
*  *******
*  ***********************************************************************
*  ***********************************************************************
*
*  CATTopMultiResult  class has been removed from CAA in 3DEXPERIENCE level and
*  has been replaced by CATICGMTopMultiResult.
*  We recommend you to use only CATICGMTopMultiResult, in order you will  be
*  able to easily migrate your CAA code from  V5 to 3DEXPERIENCE level.
*
*  **************************************************************************
*
 * Base class for all the operators that output several resulting bodies.
 */
class ExportedByCATTopologicalObjects CATTopMultiResult : public CATTopOperator 
{
  CATCGMVirtualDeclareClass(CATTopMultiResult);
public:

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

 /**
  * Returns the number of bodies that are created after a run of <tt>this</tt> operator.
	*/
  CATLONG32 GetNumberOfResults () const;     

  /**
  * Initializes the iterator to the resulting bodies created after a run of <tt>this</tt> operator.
	*/
  void BeginningResult ();     

  /** 
	 * Skips to the next (and the first in particular) resulting body created after a run of <tt>this</tt> operator.
	 * @return
	 * The existence of the current resulting body.
	 * <br><b>Legal values</b>:
	 * <dl><dt><tt>TRUE</tt></dt><dd>if there is a next solution body.
	 * <dt><tt>FALSE</tt></dt><dd>there is no solution body anymore.
	 */
  CATBoolean NextResult ();

	/**
	 * Returns a pointer to the current body.
	 * <br>To call after the <tt>Next</tt> method.
	 * @param iJournal
	 * The associated journal if not <tt>0</tt>.
	 * @return
	 * A pointer to the current body.
	 */
  virtual CATBody * GetResult(CATCGMJournalList* iJournal);


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  //
  // constructors and destructors
  //
  virtual ~CATTopMultiResult();

#ifdef CATIACGMR215CAA
  /**
   * Returns a pointer to the current body.
   * <br>To call after the <tt>Next</tt> method.
   * @return
   * A pointer to the current body.
   */
  virtual CATBody *GetResult();

  /** @nodoc @nocgmitf
  * Some operators can have both behaviors (mono-result and multi-result)
  * To know the current one of this operator
  * @return
  * TRUE if this operator is in multi-result mode (CATTopMultiResult)
  * FALSE if this operator is in mono-result mode (CATTopOperator)
  */
  CATBoolean IsInMultiResultMode();

  /** @nodoc @nocgmitf
  * Some operators can have both behaviors (mono-result and multi-result)
  * To set the current one for this operator (before its Run)
  * @param
  * TRUE if this operator must be in multi-result mode (CATTopMultiResult)
  * FALSE if this operator must be in mono-result mode (CATTopOperator)
  */
  void SetInMultiResultMode(CATBoolean iMode = TRUE);
#else
  /** @nodoc */
  virtual CATBody *GetResult();
#endif

   /** 
   * @nodoc @nocgmitf
   *  Returns CATTopMultiResult if this operator is multiple result.
   * @return
   * return CATTopMultiResult * result
   */
	CATTopMultiResult * IsMultiResult();
  
   /** 
   * @nodoc
   *  Must be called after Run() 
   *  Create a cell tracker service 
   * @return
   * A pointer on the created cell tracker
   * You must delete the cell tracker after usage
   */
	virtual    CATCGMCellTracker * CreateCellTracker();

protected :

	/** 
	 * @nodoc @nocgmitf
   * Journal of index inum
   */
  virtual CATCGMJournalList * GetNumReportForCellTracker(CATLONG32 iInum); 

public :

#ifdef CATIACGMR419CAA

  /** @nodoc @nocgmitf Operator Delegation Management */
  virtual int TransferGenericSettingsToDelegateBeforeRun(CATTopOperator &iDelegateOperator);  
  /** 
  * @nodoc @nocgmitf 
  * Operator Delegation Management : ioDelegateJournal might be a concatenated journal different from the one filled by the Delegate Operator
  * The mechanism allows the caller to insert an operation (conversion from exact to poly ...) before the Run and then merge the 2 journals before recording the results
  * If ioDelegateJournal is not valuated to NULL during this call, the caller is still responsible of its life cycle management
  */
  virtual int TransferResultDataFromDelegateAfterRun(CATTopOperator &iDelegateOperator, CATCGMJournalList * &ioDelegateJournal);

#endif

protected :

#ifdef CATIACGMR217CAA

  /** @nodoc */
  virtual void CopyTopMultiResultDataPreRunFrom (CATCGMOperator const *  iSource);

  /** @nodoc */
  virtual void CopyTopMultiResultDataPostRunFrom (CATCGMOperator const *  iSource);
#endif

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
   CATTopMultiResult(CATBoolean             iMultiResultModeByDefault,
                     CATGeoFactory        * iFactory, 
                     CATTopData           * iTopData,
                     CATBodyFreezeMode      iBodyFreezeMode = CATBodyFreezeOn,
                     CATExtTopMultiResult * iExtensible = NULL);
   
   /** @nodoc */
   CATTopMultiResult(CATBoolean             iMultiResultModeByDefault,
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
  CATTopMultiResult (CATGeoFactory * iForCreation, CATExtTopMultiResult *iExtensible = NULL);
  /**
   * @nodoc
   * Creates a CATTopMultiResult operator.
   * @param iForCreation
   * The pointer to the factory where the resulting bodies are created.
   */
  CATTopMultiResult (CATGeoFactory * iForCreation, CATTopData * iTopData, CATExtTopMultiResult *iExtensible = NULL);
#endif

	/** @nodoc */
  void AddResults(CATBody ** NewResults, CATCGMJournalList ** NewJourn, CATLONG32 nbres=1,CATCGMJournalList **  JournauxComplets=NULL);
  void ReplaceResult(CATLONG32 iNum, CATBody * NewResults, CATCGMJournalList * NewJourn);
	/** @nodoc */
  void ReleaseResults();
	/** @nodoc */
  void ReleaseResultsFrom(CATLONG32 iNum);
	/** 
	 * @nodoc 
	 * Index of the current resulting body
	 */
  CATLONG32 GetNumCur() const;
	/** 
	 * @nodoc 
	 * Pointer to the current resulting body
	 */
  CATBody * GetNumBody(CATLONG32 iInum);
	/** 
	 * @nodoc 
   * Journal of index inum
   */
  CATCGMJournalList * GetNumReport(CATLONG32 iInum); 
  
  /** @nodoc  */
  inline CATExtTopMultiResult *GetMultiResultExtension(CATBoolean iRequired = TRUE) const;


private :

 
  /** @nodoc  forbidden functionnality */
  CATTopMultiResult(const CATTopMultiResult&);

  /** @nodoc   forbidden functionnality */
  CATTopMultiResult& operator=(const CATTopMultiResult&);
};

/** @nodoc  */
inline CATExtTopMultiResult *CATTopMultiResult::GetMultiResultExtension(CATBoolean iRequired) const
{
  return (CATExtTopMultiResult *) (void *) ((_Extensible || !iRequired) ? _Extensible  : RequireExtensible() );
}


#endif
