#ifndef CATICGMSolidPyramid_h_
#define CATICGMSolidPyramid_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMSolidPrimitive.h"

class CATFace;
class CATLoop;
class CATMathPoint;
class CATSurParam;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMSolidPyramid;

/**
 * Class defining the operator to create a topological pyramid.
 * <br><tt>CATICGMSolidPyramid</tt> follows the global frame of the topological operators.
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateSolidPyramid</tt> global function 
 * <li>Run it 
 * <li>Get the result
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMSolidPyramid: public CATICGMSolidPrimitive
{
public:
  /**
   * Constructor
   */
  CATICGMSolidPyramid();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMSolidPyramid(); // -> delete can't be called
};

//---------------------------------------------------------------
/**
 * Constructs an operator that creates a topological pyramid.
 * The Run method must be used to generate a result.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iPt1
 * The first point of the base.
 * @param iPt2
 * The second point of the base.
 * @param iPt3
 * The third point of the base.
 * @param iTop
 * The point defining the top of the pyramid.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSolidPyramid *CATCGMTopCreateSolidPyramid(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iPt1,
  const CATMathPoint &iPt2,
  const CATMathPoint &iPt3,
  const CATMathPoint &iTop);

/**
 * Constructs an operator that creates a topological pyramid.
 * The Run method must be used to generate a result.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iBase
 * The pointer to the face defining the base of the pyramid.
 * @param iTop
 * The point defining the top of the pyramid.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSolidPyramid *CATCGMTopCreateSolidPyramid(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATFace *iBase,
  const CATMathPoint &iTop);

//---------------------------------------------------------------
/**
 * @nodoc
 * deprecated V5R21 CATCGMTopCreateSolidPyramid
 * @deprecated R211 CATCGMTopCreateSolidPyramid
 * Constructs an operator that creates a topological pyramid.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iPt1
 * The first point of the base.
 * @param iPt2
 * The second point of the base.
 * @param iPt3
 * The third point of the base.
 * @param iTop
 * The point defining the top of the pyramid.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSolidPyramid *CATCGMCreateSolidPyramid(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iPt1,
  const CATMathPoint &iPt2,
  const CATMathPoint &iPt3,
  const CATMathPoint &iTop);

/**
 * @nodoc
 * deprecated V5R21 CATCGMTopCreateSolidPyramid
 * @deprecated R211 CATCGMTopCreateSolidPyramid
 * Constructs an operator that creates a topological pyramid.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iBase
 * The pointer to the face defining the base of the pyramid.
 * @param iTop
 * The point defining the top of the pyramid.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSolidPyramid *CATCGMCreateSolidPyramid(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATFace *iBase,
  const CATMathPoint &iTop);

#endif /* CATICGMSolidPyramid_h_ */
