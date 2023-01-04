#ifndef CATIPGMConfusionPtOnSurPtOnSur_h_
#define CATIPGMConfusionPtOnSurPtOnSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATSurParam;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMConfusionPtOnSurPtOnSur;

/**
 * @level Protected
 * @usage U1
 */
/**
 * Class defining the operator testing the overlap of two points on a CATSurface.
 *<ul>
 *<li>The CATIPGMConfusionPtOnSurPtOnSur is created with the <tt>CreateConfusion</tt> method and 
 * directly released with the <tt<Release</tt> method. It is not streamable. 
 *<li>The operation is automatically done at the operator creation. 
 *<li>The result is accessed with to the <tt>GetConfusion</tt> method.
 * </ul>
 */
class ExportedByCATGMModelInterfaces CATIPGMConfusionPtOnSurPtOnSur: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMConfusionPtOnSurPtOnSur();

  /**
 * Returns the result of <tt>this</tt> CATIPGMConfusionPtOnSurPtOnSur operator.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl>
 * <dt><tt>TRUE</tt> <dd> if the distance between the two CATPointOnSurfaces
 * is less than the tolerance given at the operator creation.
 *    <dt><tt>FALSE</tt> <dd> otherwise.  </dl> 
 */
  virtual CATBoolean GetConfusion() = 0;

  /**  
 *  @nodoc  
 *    Setting  parameters  without  changing  the  surface
 */
  virtual void SetParameters(
    const CATSurParam &param1,
    const CATSurParam &param2) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConfusionPtOnSurPtOnSur(); // -> delete can't be called
};

#endif /* CATIPGMConfusionPtOnSurPtOnSur_h_ */
