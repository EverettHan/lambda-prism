#ifndef CATConfusionPtOnCrvPtOnCrv_H
#define CATConfusionPtOnCrvPtOnCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "CATCreateConfusionPtOnCrvPtOnCrv.h"
#include "CreateConfusionPtOnCrvPtOnCrv.h"
#include "CATCGMOperator.h"
#include "CATMathDef.h"
#include "Y30A3HGG.h"

/**
 * Class defining the operator testing the overlap of two points on a CATCurve.
 *<ul>
 *<li>The CATConfusionPtOnCrvPtOnCrv is created with the <tt>CreateConfusion</tt> method and 
 * directly <tt>delete</tt>d with the usual C++ delete operator. It is not streamable. 
 *<li>The operation is automatically done at the operator creation. 
 *<li>The result is accessed with to the <tt>GetConfusion</tt> method.
 * </ul>
 */
class ExportedByY30A3HGG CATConfusionPtOnCrvPtOnCrv: public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATConfusionPtOnCrvPtOnCrv);
 public:

/**
 * Destructor.
 */ 
  virtual ~CATConfusionPtOnCrvPtOnCrv();
	/**
    * @nodoc
	* Use the <tt>CreateConfusion</tt> global method.
	*/
  CATConfusionPtOnCrvPtOnCrv(CATGeoFactory * factory);

/**
 * Returns the result of <tt>this</tt> CATConfusionPtOnCrvPtOnCrv operator.
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
  virtual void SetParameters(const CATCrvParam & param1, const CATCrvParam & param2) = 0;
//#endif

};
                                        
#endif
