#ifndef CATICGMComputePointOnWire_h_
#define CATICGMComputePointOnWire_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATGeoFactory;
class CATMathPoint;
class CATTopData;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMComputePointOnWire;

/**
 * Class defining the operator that computes mathematical points on a wire.
 *<br> This operator follows the general scheme of the topological operators:
 *<ul>
 *<li> Create the operator with the global function <tt>CATCGMCreateComputePointOnWire</tt>
 *<li> Set parameters if necessary
 *<li> Run with the <tt>Run</tt> method
 *<li> Get the result mathematical point with the <tt>GetMathPoint</tt> method.
 * Here, the <tt>GetResult</tt> method will always return <tt>NULL</tt>, and there is no associated
 * journal, because the operator does not create any body. 
 *<li> Release the operator with the <tt>Release</tt> method.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATICGMComputePointOnWire: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMComputePointOnWire();

  /**
   * Defines the ratio between the point to be computed 
   * and the wire length. The computed CATMathpoint is then retrieved by using <tt>GetMathPoint</tt>.
   * @param iValue
   * The value, according to the computation mode.
   */
  virtual void SetValue(double iValue) = 0;

  /**
   * Defines the mathematical point. The ratio between the length of wire portion defined by 
   * the CATMathPoint and the total wire length is then 
   * retrieved by using <tt>GetValue</tt>.
   * @param iPoint
   * The CATMathPoint.
   */
  virtual void SetMathPoint(const CATMathPoint &iPoint) = 0;

  /**
   * Runs <tt>this</tt> operator.
   * @return
   * Not <tt>NULL</tt> in case of error.
   */
  virtual int Run() = 0;

  /**
   * Retrieves the corresponding mathematical point.
   * @param ioResultPoint
   * The result as a CATMathPoint.
   */
  virtual void GetMathPoint(CATMathPoint &ioResultPoint) = 0;

  /**
   * Retrieves the corresponding value for the computation.
   * @param oResultValue
   * The value, according to the computation mode.
   */
  virtual void GetValue(double &oResultValue) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMComputePointOnWire(); // -> delete can't be called
};

/**
* Creates an operator that computes mathematical points on a wire.
* @param iFactory
* The factory of the geometry.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. The journal is
* not filled, because there is no body creation.
* @param iWire
* The pointer to the wire body on which the mathematical point is computed.
* @param iValue
* The ratio between the curvilinear abscissa of the point to be computed and the length of the wire.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMComputePointOnWire *CATCGMCreateComputePointOnWire(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWire,
  double iValue);

#endif /* CATICGMComputePointOnWire_h_ */
