#ifndef CATICGMDynBoolean_h_
#define CATICGMDynBoolean_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMDynOperator.h"
#include "CATCollec.h"
#include "CATDynOperatorDef.h"

class CATBody;
class CATTopData;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMDynBoolean;

/**
* Class defining the boolean operations on skins and solids. Boolean operations
* on wires are performed by using the CATICGMHybBoolean operator as well as its derived classes.
*<br>
* The CATICGMDynBoolean operator follows the global frame of the topological operators and satisfies the smart mechanism: 
* the input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>A CATICGMDynBoolean operator is created with the <tt>CATCGMCreateDynBoolean</tt> global function:
* It must be directly released with the <tt>Release</tt> method. It is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. In particular, an optimized mode
* allows you to do some local operations in union mode.
*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory. 
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMDynBoolean: public CATICGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATICGMDynBoolean();

  /**
 * Defines an upper set of faces that are touched by the operation.
 * <br> This method must be called for both input bodies. This optimizes the boolean operation,
 * that only processes the faces declared here, and can be used to stick
 * bodies together when then share faces. It is important to give at least all
 * the faces that are in (even partial) contact or that are intersecting, otherwise
 * the Boolean operator cannot return a consistent result. In other words,
 * the result of boolean operation should not be changed by using this optimisation.
 * @param iBody
 * The pointer to the body for which the faces are given.
 * @param iContactFaces
 * The list of the pointers to the faces of <tt>iBody</tt> that are touched in the operation (at least).
 */
  virtual void SetContactFacesForUnion(
    CATBody *iBody,
    const CATLISTP(CATFace) &iContactFaces) = 0;

  /**
 * Defines a mode such that the resulting body is not simplified.
 */
  virtual void NoSimplif() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDynBoolean(); // -> delete can't be called
};

/**
 * Creates a CATICGMDynBoolean operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iOperation
 * The type of operation 
 *<dl><dt>CATBoolUnion</dt><dd>Boolean union.
 *    <dt>CATBoolIntersection</dt><dd>Boolean intersection.
 *    <dt>CATBoolRemoval</dt><dd><tt>iTool</tt> is subtracted to <tt>iPart</tt>.
 *</dl>
 * @param iPart
 * The pointer to the first body.
 * @param iPart
 * The pointer to the second body.  
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMDynBoolean *CATCGMCreateDynBoolean(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATDynBooleanType iOperation,
  CATBody *iPart,
  CATBody *iTool);

#endif /* CATICGMDynBoolean_h_ */
