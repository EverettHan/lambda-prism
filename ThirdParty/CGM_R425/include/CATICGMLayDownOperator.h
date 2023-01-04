#ifndef CATICGMLayDownOperator_h_
#define CATICGMLayDownOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATCell;
class CATDomain;
class CATGeoFactory;
class CATICGMHybOperator;
class CATShell;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMLayDownOperator;

/**
* Class defining the operator that projects a body onto another one referred to as the support and returns a solution
* only if the distance is lower than the factory resolution. If the body to be projected
* is lying on the support, the operator returns the input body (the body to be projeceted).
* The body to be projected and the support body (on which the projection is made) can contain 
* several domains.
* <br><b>Orientation</b>:(In case of the projection of a wire on a shell).
* The orientation of two points on the resulting wire is the same as
* the orientation of the points from which they are projected.
* <br><b>Journal</b>: 
*<ul>
* <li>Edges are written as <tt>CATCGMJournal::Creation</tt> from their corresponding
* edge (in the body to be projected project) and face (on the body support).
* <li>The first and last vertices are written as  <tt>CATCGMJournal::Creation</tt>.
* </ul>
* It follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>The operator is created with the <tt>CATCGMCreateTopLaydown</tt> global function.
* It must be
* directly released with the <tt>Release</tt> method after use.
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATCGMCreateTopLayDown
*/
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATICGMLayDownOperator: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMLayDownOperator();

  /**  
	* Runs the operator.
	*/
  virtual int Run() = 0;

  /**  
	* Returns the projected body or the initial body.
	* @return
    * The result Body.
	*/
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMLayDownOperator(); // -> delete can't be called
};

#endif /* CATICGMLayDownOperator_h_ */
