#ifndef CATIPGMTopMultiResult_h_
#define CATIPGMTopMultiResult_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATExtTopMultiResult;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATString;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopMultiResult;

/**
 * Base class for all the operators that output several resulting bodies.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopMultiResult: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopMultiResult();

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  /**
  * Returns the number of bodies that are created after a run of <tt>this</tt> operator.
	*/
  virtual CATLONG32 GetNumberOfResults() const = 0;

  /**
  * Initializes the iterator to the resulting bodies created after a run of <tt>this</tt> operator.
	*/
  virtual void BeginningResult() = 0;

  /** 
	 * Skips to the next (and the first in particular) resulting body created after a run of <tt>this</tt> operator.
	 * @return
	 * The existence of the current resulting body.
	 * <br><b>Legal values</b>:
	 * <dl><dt><tt>TRUE</tt></dt><dd>if there is a next solution body.
	 * <dt><tt>FALSE</tt></dt><dd>there is no solution body anymore.
	 */
  virtual CATBoolean NextResult() = 0;

  /**
	 * Returns a pointer to the current body.
	 * <br>To call after the <tt>Next</tt> method.
	 * @param iJournal
	 * The associated journal if not <tt>0</tt>.
	 * @return
	 * A pointer to the current body.
	 */
  virtual CATBody *GetResult(CATCGMJournalList *iJournal) = 0;

  /**
   * Returns a pointer to the current body.
   * <br>To call after the <tt>Next</tt> method.
   * @return
   * A pointer to the current body.
   */
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopMultiResult(); // -> delete can't be called
};

#endif /* CATIPGMTopMultiResult_h_ */
