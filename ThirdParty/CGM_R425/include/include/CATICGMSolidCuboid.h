#ifndef CATICGMSolidCuboid_h_
#define CATICGMSolidCuboid_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMSolidPrimitive.h"

class CATMathPoint;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMSolidCuboid;

/**
 * Class defining the operator to create a topological cube.
 * <br><tt>CATICGMSolidCuboid</tt> follows the global frame of the topological operators.
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateSolidCuboid</tt> global function
 * <li>Run it 
 * <li>Get the result
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMSolidCuboid: public CATICGMSolidPrimitive
{
public:
  /**
   * Constructor
   */
  CATICGMSolidCuboid();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMSolidCuboid(); // -> delete can't be called
};

//--------------------------------------------------------------------------
/**
 * Constructs an operator that creates a topological cube.
 * The Run method must be used.
 * <pre>              ________
 *        iPt4 /        /| 
 *            /        / |
 *           /  |     /  |
 *          /________/   |
 *          |   |    |   |
 *          |        |   |
 *          |   |    |   | iPt3
 *          |iPt1-  -! - /
 *          |  /     |  /
 *          |        | /
 *     iPt2 |/       |/
 *          |________|  </pre>
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled. 
 * @param iPt1
 * The origin of the cube.
 * @param iPt2
 * The limitation in the first direction.
 * @param iPt3
 * The limitation in the second direction.
 * @param iPt4
 * The limitation in the third direction.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSolidCuboid *CATCGMTopCreateSolidCuboid(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iPt1,
  const CATMathPoint &iPt2,
  const CATMathPoint &iPt3,
  const CATMathPoint &iPt4);

//--------------------------------------------------------------------------
/**
 * @nodoc 
 * @deprecated R211 CATCGMTopCreateSolidCuboid
 * deprecated V5R21 CATCGMTopCreateSolidCuboid
 * Constructs an operator that creates a topological cube.
 *<pre>              ________
 *        iPt4 /        /| 
 *            /        / |
 *           /  |     /  |
 *          /________/   |
 *          |   |    |   |
 *          |        |   |
 *          |   |    |   | iPt3
 *          |iPt1-  -! - /
 *          |  /     |  /
 *          |        | /
 *     iPt2 |/       |/
 *          |________|  </pre>
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled. 
 * @param iPt1
 * The origin of the cube.
 * @param iPt2
 * The limitation in the first direction.
 * @param iPt3
 * The limitation in the second direction.
 * @param iPt4
 * The limitation in the third direction.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSolidCuboid *CATCGMCreateSolidCuboid(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iPt1,
  const CATMathPoint &iPt2,
  const CATMathPoint &iPt3,
  const CATMathPoint &iPt4);

#endif /* CATICGMSolidCuboid_h_ */
