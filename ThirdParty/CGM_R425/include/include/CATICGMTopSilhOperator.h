#ifndef CATICGMTopSilhOperator_h_
#define CATICGMTopSilhOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2015

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATIACGMLevel.h"

class CATBody;
class CATDomain;
class CATExtTopOperator;
class CATMathDirection;
class CATMathPlane;
class CATMathPoint;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopSilhOperator;

/**
* Class defining the operator that computes the silhouette for a given body.
*<br>
* It follows the general frame of all operators and satisfies the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>CATICGMTopSilhOperator is created with the CATCGMCreateTopSilhouette global function. 
* It must be directly deleted with the usual C++ <tt>delete</tt> operator after use.
* It is not streamable. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATCGMCreateTopSilhouette in CATICGMTopSilhouette.h for the instanciation
 * -----------------------------------------------------------------------------------
 * July. 15     Creation DPS
 * -----------------------------------------------------------------------------------
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopSilhOperator: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopSilhOperator();

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
  *   <li> <tt>TRUE</tt> if the planar normal direction shows the light source.
  *   <li> <tt>FALSE</tt> if the light source is behind the screen.
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
  virtual ~CATICGMTopSilhOperator(); // -> delete can't be called
};

#endif /* CATICGMTopSilhOperator_h_ */
