#ifndef CATICGMTopSilhouette_h_
#define CATICGMTopSilhouette_h_

// COPYRIGHT DASSAULT SYSTEMES 2012

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopSilhOperator.h"
#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"
class CATLISTP(CATBody);

class CATBody;
class CATDomain;
class CATMathDirection;
class CATMathPoint;
class CATTopSilhouetteImpl;
class CATTopData;
class CATMathPlane;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopSilhouette;

/**
* Class defining the operator that computes the silhouette for a given body.
* <br>
* It follows the general frame of all operators and satisfies the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
* <ul>
* <li>CATICGMTopSilhouette is created with the CATCGMCreateTopSilhouette global function. 
* It must be released with the <tt>Release</tt> method after use.
* It is not streamable. 
* <li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
* </ul>
* @see CATCGMCreateTopSilhouette
*/
#if defined(CATIAV5R26) || defined(CATIAR418)
class ExportedByCATGMOperatorsInterfaces CATICGMTopSilhouette: public CATICGMTopSilhOperator
#else
class ExportedByCATGMOperatorsInterfaces CATICGMTopSilhouette: public CATICGMTopOperator
#endif
{
public:
  /**
   * Constructor
   */
  CATICGMTopSilhouette();

 /**
  * Sets the operator to project shadows on a planar screen whose the normal is the projection direction.
  * @param iScreenBody
  *   The infinite or trimmed planar screen to project the shadows.
  * @param iLightSourceInFront
  *   The side from which the light comes : 
  *   This side influences the location of points on the boundary of the shadow.
  *   <li> <tt>TRUE</tt> if the planar normal direction shows the light source.
  *   <li> <tt>FALSE</tt> if the light source is behind the screen.
  * @param iFillHoles
  *   If this optional argument is set to TRUE, the holes inside the shadows will be filled 
  *   and each returned face will be bounded by a single external loop, ignoring the internal silhouettes
  * @return
  */
  virtual void SetProjectionScreenForShadows(
    CATBody *iScreenBody,
    CATBoolean iLightSourceInFront,
    CATBoolean iFillHoles = FALSE) = 0;


 /**
  * Sets the operator to project shadows on a planar screen whose the normal is the projection direction.
  * @param iScreenPlane
  *   The infinite planar screen to project the shadows.
  * @param iLightSourceInFront
  *   The side from which the light comes : 
  *   This side influences the location of points on the boundary of the shadow.
  *     <li> <tt>TRUE</tt> if the planar normal direction shows the light source.
  *     <li> <tt>FALSE</tt> if the light source is behind the screen.
  * @param iFillHoles
  *   If this optional argument is set to TRUE, the holes inside the shadows will be filled 
  *   and each returned face will be bounded by a single external loop, ignoring the internal silhouettes
  * @return
  */
  virtual void SetProjectionScreenForShadows(
    const CATMathPlane &iScreenPlane,
    CATBoolean iLightSourceInFront,
    CATBoolean iFillHoles = FALSE) = 0;


 /**
  * Sets the operator to return wires instead of faces : 
  * those wires are equivalent to the loops bounding the shadow faces
  * and will contain all the external silhouettes, plus the internal silhouettes if the option FillHoles is disabled
  * @return
  */  
  virtual void EnableWireMode() = 0;


protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopSilhouette(); // -> delete can't be called
};

/**
 * Creates a CATICGMTopSilhouette operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iBody
 * The pointer to the body whose sihouette needs to be computed.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopSilhouette *CATCGMCreateTopSilhouette(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody);


/**
 * Creates a CATICGMTopSilhouette operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iInputBodies
 * The list of bodies to compute silhouettes 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopSilhouette *CATCGMCreateTopSilhouette(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  const CATLISTP(CATBody) & iInputBodies);


/**
 * @deprecated R423 CATCGMCreateTopSilhouette(CATGeoFactory *, CATTopData *, const CATLISTP(CATBody) &)
 * Creates a CATICGMTopSilhouette operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iInputBodies
 * The pointer to the list of bodies whose sihouette needs to be computed.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopSilhouette *CATCGMCreateTopSilhouette(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATBody) *iInputBodies);

#endif /* CATICGMTopSilhouette_h_ */
