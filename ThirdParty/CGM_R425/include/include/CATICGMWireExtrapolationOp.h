#ifndef CATICGMWireExtrapolationOp_h_
#define CATICGMWireExtrapolationOp_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATVertex;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMWireExtrapolationOp;

/**
 * Class defining the extrapolation operator on a wire body.
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateWireExtrapolationOp</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting GetResult method. If you do not want 
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 */
class ExportedByCATGMOperatorsInterfaces CATICGMWireExtrapolationOp: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMWireExtrapolationOp();

  /** 
 * Set extrapolation length for specified vertex.
  * @param iVertex
  * The vertex to be extrapolated.
  * @param iLength
  * The extrapolation length.
 */
  virtual void SetExtrapolation(CATVertex *iVertex, double iLength) = 0;

  /** 
 * Runs <tt>this</tt> operator.
 */
  virtual int Run() = 0;

  /**
 * Returns a pointer to the resulting CATBody of <tt>this</tt> operator.
 * <br> Must be called after the <tt>Run</tt> method.
 */
  virtual CATBody *GetResult() = 0;

  /**
	 * Returns the mode in which the resulting body is created.
	 * @return
	 * The smart mode.
	 */
  virtual CATBodyFreezeMode GetFreezeMode() const = 0;

  /**
	 * Defines the state of the resulting body.
	 * @param iOnOrOff
	 * The state of the resulting body. 
	 */
  virtual void SetFreezeMode(CATBodyFreezeMode iOnOrOff) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMWireExtrapolationOp(); // -> delete can't be called
};

/**
 * Creates a CATICGMWireExtrapolationOp operator.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iTopData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iBodyToExtrapolate
 * The pointer to the wire body to be extrapolated.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMWireExtrapolationOp *CATCGMCreateWireExtrapolationOp(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyToExtrapolate);

#endif /* CATICGMWireExtrapolationOp_h_ */
