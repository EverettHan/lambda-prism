#ifndef CATIPGMSolidTorus_h_
#define CATIPGMSolidTorus_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMSolidPrimitive.h"

class CATMathAxis;
class CATMathDirection;
class CATMathPoint;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSolidTorus;

/**
 * Class defining the operator to create a topological torus.
 * <br><tt>CATIPGMSolidTorus</tt> follows the global frame of the topological operators.
 *<ul>
 * <li>Create it with the <tt>CATPGMCreateSolidTorus</tt> global function 
 * <li>Run it 
 * <li>Get the result
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSolidTorus: public CATIPGMSolidPrimitive
{
public:
  /**
   * Constructor
   */
  CATIPGMSolidTorus();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSolidTorus(); // -> delete can't be called
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
ExportedByCATGMOperatorsInterfaces CATIPGMSolidTorus *CATPGMTopCreateSolidTorus(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathAxis &iAxis,
  const CATMathPoint &iMajor,
  const CATMathPoint &iMinor);

//------------------------------------------------------------------------
/**
 * @deprecated R211 CATPGMTopCreateSolidTorus
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
ExportedByCATGMOperatorsInterfaces CATIPGMSolidTorus *CATPGMCreateSolidTorus(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathAxis &iAxis,
  const CATMathPoint &iMajor,
  const CATMathPoint &iMinor);

#endif /* CATIPGMSolidTorus_h_ */
