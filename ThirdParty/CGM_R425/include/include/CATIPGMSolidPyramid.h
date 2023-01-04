#ifndef CATIPGMSolidPyramid_h_
#define CATIPGMSolidPyramid_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMSolidPrimitive.h"

class CATFace;
class CATLoop;
class CATMathPoint;
class CATSurParam;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSolidPyramid;

/**
 * Class defining the operator to create a topological pyramid.
 * <br><tt>CATIPGMSolidPyramid</tt> follows the global frame of the topological operators.
 *<ul>
 * <li>Create it with the <tt>CATPGMCreateSolidPyramid</tt> global function 
 * <li>Run it 
 * <li>Get the result
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSolidPyramid: public CATIPGMSolidPrimitive
{
public:
  /**
   * Constructor
   */
  CATIPGMSolidPyramid();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSolidPyramid(); // -> delete can't be called
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
ExportedByCATGMOperatorsInterfaces CATIPGMSolidPyramid *CATPGMTopCreateSolidPyramid(
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
ExportedByCATGMOperatorsInterfaces CATIPGMSolidPyramid *CATPGMTopCreateSolidPyramid(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATFace *iBase,
  const CATMathPoint &iTop);

//---------------------------------------------------------------
/**
 * @deprecated R211 CATPGMTopCreateSolidPyramid
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
ExportedByCATGMOperatorsInterfaces CATIPGMSolidPyramid *CATPGMCreateSolidPyramid(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const CATMathPoint &iPt1,
  const CATMathPoint &iPt2,
  const CATMathPoint &iPt3,
  const CATMathPoint &iTop);

/**
 * @deprecated R211 CATPGMTopCreateSolidPyramid
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
ExportedByCATGMOperatorsInterfaces CATIPGMSolidPyramid *CATPGMCreateSolidPyramid(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATFace *iBase,
  const CATMathPoint &iTop);

#endif /* CATIPGMSolidPyramid_h_ */
