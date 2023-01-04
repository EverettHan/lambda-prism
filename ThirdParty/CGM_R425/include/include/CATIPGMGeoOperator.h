#ifndef CATIPGMGeoOperator_h_
#define CATIPGMGeoOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATGeoOpTimer;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMGeoOperator;

/**
 * Base class for the geometric operators.
 * <br>To use a geometric operator:
 *<ul><li>Create it with the corresponding <tt>CreateXxx</tt> global method
 * <li>Tune some parameters if needed
 * <li>Run it
 * <li>Read the results
 * <li>Release the operator with the <tt>Release</tt> method.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATIPGMGeoOperator: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMGeoOperator();

  /**
  * Runs <tt>this</tt> operator.
  */
  virtual int Run() = 0;

  /** @nodoc  */
  virtual CATGeoOpTimer *GetTimer() = 0;

  /** @nodoc
   * @return
   *   Not <tt>NULL</tt> if the operator is topological.
   *   Pay attention: do not release the returned pointer!
   */
  virtual CATIPGMTopOperator *IsTopological() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMGeoOperator(); // -> delete can't be called
};

#endif /* CATIPGMGeoOperator_h_ */
