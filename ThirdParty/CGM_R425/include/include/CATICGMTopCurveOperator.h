#ifndef CATICGMTopCurveOperator_h_
#define CATICGMTopCurveOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATIAV5Level.h"
#include "CATIACGMLevel.h" 

#include "CATGMOperatorsInterfaces.h"
#ifdef CATIACGMR215CAA
#include "CATICGMTopMultiResult.h"
#else
#include "CATICGMTopOperator.h"
#endif
#include "CATDataType.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopCurveOperator;


/**
 * Abstract class of the topological operators that creates 
 * 1D bodies from geometry.
 * The curve can lie on a support, defined as an unique shell domain
 * of a body.
 */
#ifdef CATIACGMR215CAA
class ExportedByCATGMOperatorsInterfaces CATICGMTopCurveOperator: public CATICGMTopMultiResult
#else
class ExportedByCATGMOperatorsInterfaces CATICGMTopCurveOperator: public CATICGMTopOperator
#endif
{
public:
  /**
   * Constructor
   */
  CATICGMTopCurveOperator();

  /** 
 * Sets whether the curve is closed.
 * @param iClosed
 * The closure of the curve:
 * <b>Legal values</b>:
 *<dl><dt>2</dt><dd> for a closed curve with C2 Curvature respect on the closure</dd>
 *    <dt>1</dt><dd> for a closed curve</dd>
 *    <dt>0</dt><dd> for an open curve</dd>
 *</dl>
 * @return
 * 0 if the closure is compatible with the geometry, 
 * positive otherwise (in case of a closure setting for a line) 
 */
  virtual CATLONG32 SetClosure(CATLONG32 iClosed) = 0;

  /**
 * Sets the support of the curve.
 * @param iSupport
 * The body containing an unique shell domain. This shell domain is
 * the support of the curve.
 */
  virtual CATLONG32 SetSupport(CATBody *iSupport) = 0;

  /**
 * Retrieves the closure of the curve.
 * @param ioClosed
  * The closure of the curve:
 * <b>Legal values</b>:
 *<dl><dt>1</dt><dd> for a closed curve</dd>
 *    <dt>0</dt><dd> for an open curve</dd>
 *</dl>
 */
  virtual CATLONG32 GetClosure(CATLONG32 &ioClosed) = 0;

  /**
 * Retrieves the support of the curve.
 * @param ioSupport
 * The body containing an unique shell domain, if the curve
 * has a support. NULL otherwise. 
 *
*/
  virtual CATLONG32 GetSupport(CATBody *&ioSupport) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopCurveOperator(); // -> delete can't be called
};

#endif /* CATICGMTopCurveOperator_h_ */
