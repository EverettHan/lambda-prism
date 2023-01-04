#ifndef CATICGMSolidTorus_h_
#define CATICGMSolidTorus_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMSolidPrimitive.h"

class CATMathAxis;
class CATMathDirection;
class CATMathPoint;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMSolidTorus;

/**
 * Class defining the operator to create a topological torus.
 * <br><tt>CATICGMSolidTorus</tt> follows the global frame of the topological operators.
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateSolidTorus</tt> global function 
 * <li>Run it 
 * <li>Get the result
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMSolidTorus: public CATICGMSolidPrimitive
{
public:
  /**
   * Constructor
   */
  CATICGMSolidTorus();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMSolidTorus(); // -> delete can't be called
};

//------------------------------------------------------------------------
/**
 * Constructs an operator that creates a topological torus.
 * The Run method must be used to generate a result.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iAxis
 * The axes system of the torus.
 * @param iMajor
 * The point defining the major ring, such that its distance to the third direction of <tt>iAxis</tt> is the radius
 * of the major ring.
 * @param iMinor
 * The point defining the minor ring, such that its distance to <tt>iMajor</tt> is the radius
 * of the minor ring.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSolidTorus *CATCGMTopCreateSolidTorus(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathAxis &iAxis,
  const CATMathPoint &iMajor,
  const CATMathPoint &iMinor);

//------------------------------------------------------------------------
/**
 * @ndoc
 * deprecated V5R21 CATCGMTopCreateSolidTorus
 * @deprecated R211 CATCGMTopCreateSolidTorus
 * Constructs an operator that creates a topological torus.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iAxis
 * The axes system of the torus.
 * @param iMajor
 * The point defining the major ring, such that its distance to the third direction of <tt>iAxis</tt> is the radius
 * of the major ring.
 * @param iMinor
 * The point defining the minor ring, such that its distance to <tt>iMajor</tt> is the radius
 * of the minor ring.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSolidTorus *CATCGMCreateSolidTorus(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathAxis &iAxis,
  const CATMathPoint &iMajor,
  const CATMathPoint &iMinor);

#endif /* CATICGMSolidTorus_h_ */
