#ifndef CATConfusionPtOnSurPtOnSur_H
#define CATConfusionPtOnSurPtOnSur_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "CATCreateConfusionPtOnSurPtOnSur.h"
#include "CreateConfusionPtOnSurPtOnSur.h"
#include "CATCGMOperator.h"
#include "CATMathDef.h"

/**
 * Class defining the operator testing the overlap of two points on a CATSurface.
 *<ul>
 *<li>The CATConfusionPtOnSurPtOnSur is created with the <tt>CreateConfusion</tt> method and 
 * directly <tt>delete</tt>d with the usual C++ delete operator. It is not streamable. 
 *<li>The operation is automatically done at the operator creation. 
 *<li>The result is accessed with to the <tt>GetConfusion</tt> method.
 * </ul>
 */
class CATConfusionPtOnSurPtOnSur: public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATConfusionPtOnSurPtOnSur);
 public:
/**
 * Destructor.
 */
  virtual ~CATConfusionPtOnSurPtOnSur();
	/**
    * @nodoc
	* Use the <tt>CreateConfusion</tt> global method.
	*/
  CATConfusionPtOnSurPtOnSur(CATGeoFactory * factory);

/**
 * Returns the result of <tt>this</tt> CATConfusionPtOnSurPtOnSur operator.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl>
 * <dt><tt>TRUE</tt> <dd> if the distance between the two CATPointOnSurfaces
 * is less than the tolerance given at the operator creation.
 *    <dt><tt>FALSE</tt> <dd> otherwise.  </dl> 
 */
  virtual CATBoolean GetConfusion() = 0;

#ifdef CATIACGMV5R20
/**  
 *  @nodoc  
 *    Setting  parameters  without  changing  the  surface
 */    
  virtual  void  SetParameters(const  CATSurParam  &  param1,  const  CATSurParam  &  param2)  =  0;
#endif  

};

#endif
