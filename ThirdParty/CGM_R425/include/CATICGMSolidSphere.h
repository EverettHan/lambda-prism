#ifndef CATICGMSolidSphere_h_
#define CATICGMSolidSphere_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMSolidPrimitive.h"

class CATMathPoint;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMSolidSphere;

/**
 * Class defining the operator to create a topological sphere.
 * <br><tt>CATICGMSolidSphere</tt> follows the global frame of the topological operators.
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateSolidSphere</tt> global function 
 * <li>Run it 
 * <li>Get the result
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMSolidSphere: public CATICGMSolidPrimitive
{
public:
  /**
   * Constructor
   */
  CATICGMSolidSphere();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMSolidSphere(); // -> delete can't be called
};

//--------------------------------------------------------------------------
/**
 * Constructs an operator that creates a topological sphere.
 * The Run method must be used.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iCenter
 * The center of the sphere.
 * @param iRadius
 * The radius of the sphere.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSolidSphere *CATCGMTopCreateSolidSphere(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iCenter,
  double iRadius);

//--------------------------------------------------------------------------
/**
 * @nodoc
 * deprecated V5R21 CATCGMTopCreateSolidSphere
 * @deprecated R211 CATCGMTopCreateSolidSphere
 * Constructs an operator that creates a topological sphere.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iCenter
 * The center of the sphere.
 * @param iRadius
 * The radius of the sphere.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSolidSphere *CATCGMCreateSolidSphere(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iCenter,
  double iRadius);

#endif /* CATICGMSolidSphere_h_ */
