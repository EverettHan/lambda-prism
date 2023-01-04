#ifndef CATIPGMConfusionPtOnCrvPtOnCrv_h_
#define CATIPGMConfusionPtOnCrvPtOnCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATCrvParam;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMConfusionPtOnCrvPtOnCrv;

/**
 * @level Protected
 * @usage U1
 */
/**
 * Class defining the operator testing the overlap of two points on a CATCurve.
 *<ul>
 *<li>The CATIPGMConfusionPtOnCrvPtOnCrv is created with the <tt>CreateConfusion</tt> method and 
 * directly released with the <tt<Release</tt> method. It is not streamable. 
 *<li>The operation is automatically done at the operator creation. 
 *<li>The result is accessed with to the <tt>GetConfusion</tt> method.
 * </ul>
 */
class ExportedByCATGMModelInterfaces CATIPGMConfusionPtOnCrvPtOnCrv: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMConfusionPtOnCrvPtOnCrv();

  /**
 * Returns the result of <tt>this</tt> CATIPGMConfusionPtOnCrvPtOnCrv operator.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl>
 * <dt><tt>TRUE</tt> <dd> if the distance between the two CATPointOnCurves
 * is less than the tolerance given at the operator creation.
 *    <dt><tt>FALSE</tt> <dd> otherwise.  </dl> 
 */
  virtual CATBoolean GetConfusion() = 0;

  //#ifdef CATIAV5R14
  /**
  * @nodoc
	*  Setting parameters without changing the curve
  */
  virtual void SetParameters(
    const CATCrvParam &param1,
    const CATCrvParam &param2) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConfusionPtOnCrvPtOnCrv(); // -> delete can't be called
};

#endif /* CATIPGMConfusionPtOnCrvPtOnCrv_h_ */
