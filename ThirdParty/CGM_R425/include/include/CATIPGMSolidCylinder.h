#ifndef CATIPGMSolidCylinder_h_
#define CATIPGMSolidCylinder_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMSolidPrimitive.h"

class CATMathPoint;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSolidCylinder;

/**
 * Class defining the operator to create a topological cylinder.
 * <br><tt>CATIPGMSolidCylinder</tt> follows the global frame of the topological operators.
 *<ul>
 * <li>Create it with the <tt>CATPGMCreateSolidCylinder</tt> global function 
 * <li>Run it 
 * <li>Get the result
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSolidCylinder: public CATIPGMSolidPrimitive
{
public:
  /**
   * Constructor
   */
  CATIPGMSolidCylinder();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSolidCylinder(); // -> delete can't be called
};

//---------------------------------------------------------------
/**
 * Constructs an operator that creates a topological cylinder.
 * The Run method must be used to generate a result.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iFirstPointOnAxis
 * The first limit of the axis.
 * @param iSecondPointOnAxis
 * The second limit of the axis.
 * @param iPointOnSurface
 * A point belonging to the boundary of the cylinder (to define the radius).
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSolidCylinder *CATPGMTopCreateSolidCylinder(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iFirstPointOnAxis,
  const CATMathPoint &iSecondPointOnAxis,
  const CATMathPoint &iPointOnSurface);

/**
 * Constructs an operator that creates a topological cylinder.
 * The Run method must be used to generate a result.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iFirstPointOnAxis
 * The first limit of the axis.
 * @param iSecondPointOnAxis
 * The second limit of the axis.
 * @param iRadius
 * The radius value.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSolidCylinder *CATPGMTopCreateSolidCylinder(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iFirstPointOnAxis,
  const CATMathPoint &iSecondPointOnAxis,
  double iRadius);

//---------------------------------------------------------------
/**
 * @deprecated R211 CATPGMTopCreateSolidCylinder
 * Constructs an operator that creates a topological cylinder.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iFirstPointOnAxis
 * The first limit of the axis.
 * @param iSecondPointOnAxis
 * The second limit of the axis.
 * @param iPointOnSurface
 * A point belonging to the boundary of the cylinder (to define the radius).
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSolidCylinder *CATPGMCreateSolidCylinder(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iFirstPointOnAxis,
  const CATMathPoint &iSecondPointOnAxis,
  const CATMathPoint &iPointOnSurface);

/**
 * @deprecated R211 CATPGMTopCreateSolidCylinder
 * Constructs an operator that creates a topological cylinder.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iFirstPointOnAxis
 * The first limit of the axis.
 * @param iSecondPointOnAxis
 * The second limit of the axis.
 * @param iRadius
 * The radius value.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSolidCylinder *CATPGMCreateSolidCylinder(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iFirstPointOnAxis,
  const CATMathPoint &iSecondPointOnAxis,
  double iRadius);

#endif /* CATIPGMSolidCylinder_h_ */
