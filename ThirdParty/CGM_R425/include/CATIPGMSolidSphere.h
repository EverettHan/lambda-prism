#ifndef CATIPGMSolidSphere_h_
#define CATIPGMSolidSphere_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMSolidPrimitive.h"

class CATMathPoint;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSolidSphere;

/**
 * Class defining the operator to create a topological sphere.
 * <br><tt>CATIPGMSolidSphere</tt> follows the global frame of the topological operators.
 *<ul>
 * <li>Create it with the <tt>CATPGMCreateSolidSphere</tt> global function 
 * <li>Run it 
 * <li>Get the result
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSolidSphere: public CATIPGMSolidPrimitive
{
public:
  /**
   * Constructor
   */
  CATIPGMSolidSphere();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSolidSphere(); // -> delete can't be called
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
ExportedByCATGMOperatorsInterfaces CATIPGMSolidSphere *CATPGMTopCreateSolidSphere(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iCenter,
  double iRadius);

//--------------------------------------------------------------------------
/**
 * @deprecated R211 CATPGMTopCreateSolidSphere
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
ExportedByCATGMOperatorsInterfaces CATIPGMSolidSphere *CATPGMCreateSolidSphere(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iCenter,
  double iRadius);

#endif /* CATIPGMSolidSphere_h_ */
