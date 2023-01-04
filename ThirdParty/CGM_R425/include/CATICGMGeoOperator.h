#ifndef CATICGMGeoOperator_h_
#define CATICGMGeoOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMOperator.h"

//class CATGeoOpTimer;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMGeoOperator;

/**
 * Base class for the geometric operators.
 * <br>To use a geometric operator:
 *<ul><li>Create it with the corresponding <tt>CreateXxx</tt> global method
 * <li>Tune some parameters if needed
 * <li>Run it
 * <li>Read the results
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATICGMGeoOperator: public CATICGMOperator
{
public:
  /**
   * Constructor
   */
  CATICGMGeoOperator();

  /**
  * Runs <tt>this</tt> operator.
  */
  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMGeoOperator(); // -> delete can't be called
};

#endif /* CATICGMGeoOperator_h_ */
