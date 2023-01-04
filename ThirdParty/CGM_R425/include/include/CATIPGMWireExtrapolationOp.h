#ifndef CATIPGMWireExtrapolationOp_h_
#define CATIPGMWireExtrapolationOp_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATVertex;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMWireExtrapolationOp;

/**
 * @level Protected
 * @usage U1
 */

/**
 * Class defining the extrapolation operator on a wire body.
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATPGMCreateWireExtrapolationOp</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting GetResult method. If you do not want 
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMWireExtrapolationOp: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMWireExtrapolationOp();

  /** 
 * Set extrapolation length for specified vertex.
  * @param iVertex
  * The vertex to be extrapolated.
  * @param iLength
  * The extrapolation length.
 */
  virtual void SetExtrapolation(CATVertex *iVertex, double iLength) = 0;

  /** @nodoc */
  virtual void SetVersionNumber(CATLONG32 iVersionNumber) = 0;

  /** 
 * Runs <tt>this</tt> CATIPGMWireExtrapolationOp.
 */
  virtual int Run() = 0;

  /**
 * Returns a pointer to the resulting CATBody of <tt>this</tt> CATIPGMWireExtrapolationOp.
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
  virtual ~CATIPGMWireExtrapolationOp(); // -> delete can't be called
};

/**
 * Creates a CATIPGMWireExtrapolationOp operator.
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
ExportedByCATGMOperatorsInterfaces CATIPGMWireExtrapolationOp *CATPGMCreateWireExtrapolationOp(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyToExtrapolate);

#endif /* CATIPGMWireExtrapolationOp_h_ */
