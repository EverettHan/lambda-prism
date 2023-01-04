#ifndef CATIPGMCreateImplicitBodyTopOper_h_
#define CATIPGMCreateImplicitBodyTopOper_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMImplicitTopOperator.h"

class CATBody;
class CATFace;
class CATGeoFactory;
class CATTopData;
class CATVolume;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCreateImplicitBodyTopOper;

/**
* Class defining an operator that put implicit specifications (the provided expression) on the specified volume.
* <ul>
*     <li> A <tt>CATIPGMCreateImplicitBodyTopOper</tt> operator is created with the <tt>CATIPGMCreateImplicitBodyTopOper</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMCreateImplicitBodyTopOper: public CATIPGMImplicitTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCreateImplicitBodyTopOper();

  //=============================================================================
  // Settings
  //=============================================================================
  /**
  * Volume to which attach implicit specs.
  *
  * @param a CATVolume specifying the cavity to which we need to attach specs.
  */
  virtual void SetVolume(CATVolume *iCavityVolume) = 0;

  /**
  * The Scalar Field expression (SFDag spec) to be associated with the ImplicitSurface
  * that will be created and associated with the specified volume of the body. These
  * expression should not be assembled by hand but built with the CATImplicitExpressionBuilder.
  * All you do via this builder object will work on the long term, while the expression
  * themselves as encoded in the CATUnicodeString should be considered as opaque encoding
  * that might have several versions in the future (although they should remain fairly
  * readable for convenience). To navigate and query expression check the CATImplicitExpressionQuery
  * facade.
  *
  * Note: When the CATBuildExplicitPolyBody operator will be called the specified
  * expression will be modified to ensure you get an intersection of what is
  * expressed via the provided expression and the cavity volume as well as a blending
  * of that scalar field with the contact faces of that cavity. All faces of that volume
  * that are also faces of other volumes of the partitioned body are considered contact
  * faces while all faces unique to the cavity volume are considered not to be contact faces.
  * So you don't have to express yourself these intersection and blending in the expression
  * that you assemble but in situations where you would like to express more specific treatments
  * that do involve the cavity shape (or any other CGM Geometry by the way) you should
  * use the SetDependency mechanism to set these dependencies with the associated expressionId
  * that you plan to use to refer to them in your expression.
  * Please note that in the case in which you want to do very specific stuff with the cavity shape
  * even if you want to apply the same treatment to several cavity as of today you will thus have
  * to assemble those specific expression and dependency set cavity per cavity. If on the other
  * hand your expression is independent of the specific shape of the domain on which it is evaluated
  * then you can obviously associate your unique expression and it's set of dependencies to several volume.
  *
  * @param a CATUnicodeString that contain an encoded view of your expression .
  */
  virtual void SetExpression(const CATUnicodeString &iExpression) = 0;

  /**
  * The expression you want to associate with a specific volume might have
  * specific dependencies on CGM objects which might be used within the scalar
  * field computation. Thus on top of providing the expression, you need
  * to specify dependencies by providing them to the operator.
  *
  * @param iExpressionId the string identifier of the resource that will be used in the expression.
  * @param iDependency, the CGM object on which the expression depends.
  */
  virtual void SetDependency(
    const CATUnicodeString &iExpressionId,
    CATICGMObject *iDependency) = 0;

  /**
  * The expression you want to associate with a specific volume might have
  * specific resources on which it depends to compute the scalar
  * field. Thus on top of providing the expression, you need
  * to specify by providing them to the operator.
  *
  * @param iExpressionId, the string identifier of the resource that will be used in the expression.
  * @param iResource, a CATImplicitResource* passed as a void* (to be consistent with CATGeoImplicitSurface).
  */
  virtual void SetResource(
    const CATUnicodeString &iExpressionId,
    void *iResources) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCreateImplicitBodyTopOper(); // -> delete can't be called
};

/**
 * Creates a CATIPGMCreateImplicitBodyTopOper operator
 * @param iFactory
 * The factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt>
 * is <tt>NULL</tt>, it is not filled.
 * @param iBodyWithCavityToLattice
 * The pointer to the 2D body to offset (under progress, not yet available) or the 3D body to thick
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCreateImplicitBodyTopOper *CATPGMCreateCreateImplicitBodyTopOper(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iInputBody);

#endif /* CATIPGMCreateImplicitBodyTopOper_h_ */
