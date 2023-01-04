#ifndef CATICGMConfusionPtOnCrvPtOnCrv_h_
#define CATICGMConfusionPtOnCrvPtOnCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMOperator.h"
#include "CATBoolean.h"

extern ExportedByCATGMModelInterfaces IID IID_CATICGMConfusionPtOnCrvPtOnCrv;

/**
 * Class defining the operator testing the overlap of two points on a CATCurve.
 *<ul>
 *<li>The CATICGMConfusionPtOnCrvPtOnCrv is created with the <tt>CATCGMCreateConfusion</tt> method and 
 * directly released with the <tt>Release</tt> method. It is not streamable. 
 *<li>The operation is automatically done at the operator creation. 
 *<li>The result is accessed with to the <tt>GetConfusion</tt> method.
 * </ul>
 */
class ExportedByCATGMModelInterfaces CATICGMConfusionPtOnCrvPtOnCrv: public CATICGMOperator
{
public:
  /**
   * Constructor
   */
  CATICGMConfusionPtOnCrvPtOnCrv();

  /**
 * Returns the result of <tt>this</tt> CATICGMConfusionPtOnCrvPtOnCrv operator.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl>
 * <dt><tt>TRUE</tt> <dd> if the distance between the two CATPointOnCurves
 * is less than the tolerance given at the operator creation.
 *    <dt><tt>FALSE</tt> <dd> otherwise.  </dl> 
 */
  virtual CATBoolean GetConfusion() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMConfusionPtOnCrvPtOnCrv(); // -> delete can't be called
};

#endif /* CATICGMConfusionPtOnCrvPtOnCrv_h_ */
