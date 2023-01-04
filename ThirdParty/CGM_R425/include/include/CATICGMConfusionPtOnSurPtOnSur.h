#ifndef CATICGMConfusionPtOnSurPtOnSur_h_
#define CATICGMConfusionPtOnSurPtOnSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMOperator.h"
#include "CATBoolean.h"

extern ExportedByCATGMModelInterfaces IID IID_CATICGMConfusionPtOnSurPtOnSur;

/**
 * Class defining the operator testing the overlap of two points on a CATSurface.
 *<ul>
 *<li>The CATICGMConfusionPtOnSurPtOnSur is created with the <tt>CreateConfusion</tt> method and 
 * directly released with the <tt>Release</tt> method. It is not streamable. 
 *<li>The operation is automatically done at the operator creation. 
 *<li>The result is accessed with to the <tt>GetConfusion</tt> method.
 * </ul>
 */
class ExportedByCATGMModelInterfaces CATICGMConfusionPtOnSurPtOnSur: public CATICGMOperator
{
public:
  /**
   * Constructor
   */
  CATICGMConfusionPtOnSurPtOnSur();

  /**
 * Returns the result of <tt>this</tt> CATICGMConfusionPtOnSurPtOnSur operator.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl>
 * <dt><tt>TRUE</tt> <dd> if the distance between the two CATPointOnSurfaces
 * is less than the tolerance given at the operator creation.
 *    <dt><tt>FALSE</tt> <dd> otherwise.  </dl> 
 */
  virtual CATBoolean GetConfusion() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMConfusionPtOnSurPtOnSur(); // -> delete can't be called
};

#endif /* CATICGMConfusionPtOnSurPtOnSur_h_ */
