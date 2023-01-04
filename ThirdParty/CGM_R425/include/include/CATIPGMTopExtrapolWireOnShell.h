#ifndef CATIPGMTopExtrapolWireOnShell_h_
#define CATIPGMTopExtrapolWireOnShell_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopExtrapolWireOnShell;

/**
* @level Protected
* @usage U1
*/
//------------------------------------------------------------------------------
/**
* Class representing the operator that computes the extrapolation of a wire on a skin body.
* <br>The CATTopExtrapolWireOnShell operator follows the global frame of the topological operators
* and satisfies the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>A CATTopExtrapolWireOnShell operator is created with the <tt>CATCreateTopExtrapolWireOnShell</tt>
* global function.
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
*<li>The computation is done by the <tt>Run</tt> method. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory, after the operator deletion.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopExtrapolWireOnShell: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopExtrapolWireOnShell();

  /**
    * Runs <tt>this</tt> operator.
    */
  virtual int Run() = 0;

  /**
    * Returns the pointer to the resulting body.
    * @return
    * The pointer to the resulting body. If you do not want to keep it, 
    * use the @href CATICGMContainer#Remove method to remove it from the 
    * geometric factory, after the operator deletion.
    */
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopExtrapolWireOnShell(); // -> delete can't be called
};

/**
* Creates a CATExtrapolWireOnShell operator that computes the extrapolation of a wire on a shell.
* <b>Orientation</b>: The resulting wire is oriented as the input one.<br>
* @param iFactory
* The pointer to the factory of the resulting body.
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param iBodyWire
* The pointer to the body defining the wire to extrapolate. 
* @param iBodyShell
* The pointer to the body defining the support on which the input wire will be extrapolated.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopExtrapolWireOnShell *CATPGMCreateTopExtrapolWireOnShell(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyWire,
  CATBody *iBodyShell);

#endif /* CATIPGMTopExtrapolWireOnShell_h_ */
