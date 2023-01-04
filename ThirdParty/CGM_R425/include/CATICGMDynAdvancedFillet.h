#ifndef CATICGMDynAdvancedFillet_h_
#define CATICGMDynAdvancedFillet_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMDynFillet.h"
#include "CATFreeFormDef.h"
#include "CATMathDef.h"

class CATBody;
class CATDynSolidFilletCGM;
class CATFilletCrossPartingLinker;
class CATFilletVariousParameters;
class CATGeoFactory;
class CATMathPoint;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMDynAdvancedFillet;

/**
* Class defining an operator to create a fillet.
* This operator offers more capabilities than <tt>CATICGMDynFillet</tt> and 
* might be able to generate a result in cases where <tt>CATICGMDynFillet</tt> could fail.
* <br>
* <br>
* The <tt>CATICGMDynAdvancedFillet</tt> operator follows the global frame of the topological
* operators and satisfies the smart mechanism: 
* the input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>A <tt>CATICGMDynAdvancedFillet</tt> operator is created with the <tt>CATCGMCreateDynAdvancedFillet</tt> global function:
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
* <li>Options must be precised (such as the faces or edges to fillet) with the appropriate methods, before
* asking for the computation with the <tt>Run</tt> method. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMDynAdvancedFillet: public CATICGMDynFillet
{
public:
  /**
   * Constructor
   */
  CATICGMDynAdvancedFillet();

  /**
   * Sets internal continuity level of fillet ribbon
   * @param iContinuityLevel
   * Continuity level requested. Use either CATFrFPointCont or CATFrFTangentCont. Default is CATFrFPointCont.
   * @param iTolerance
   * Maximum deformation allowed to achieve the continuity. Not used as of now.
   */
  virtual void SetContinuityLevel(
    const CATFrFContinuity iContinuityLevel,
    const CATPositiveLength iTolerance = 0.) = 0;

  /**
   * Set fast fillet preview
   */
  virtual void SetFastPreview() = 0;

  /**
  *	Setting the FilletLongPropagation option on allows controlling the relimitation of the fillet 
  * in case it encounters a sharp edge on one support and then a smooth edge on the second 
  * support in the relimitation zone. Without this option, the fillet is extrapolated 
  * after the second smooth edge and the relimitation may be sharp but will be shorter. 
  * If the option is activated, the fillet will be able to roll on to the next support after 
  * the smooth edge and thus will offer a smooth relimitation at the cost of its length.
  * This option is de-activated by default.
  */
  virtual void SetFilletLongPropagation() = 0;

  /**
  * To keep features that are entirely engulfed by the result of a fillet operation the method SetKeepFeature should be used.
  * @param iKeepFeature
  * Keep feature option: CATTrue – feature kept; CATFalse – feature not kept. 
  * By default a fillet operation does not keep any feature that isn’t interfering with the boundary of the fillet. 
  */
  virtual void SetKeepFeature(CATBoolean iKeepFeature) = 0;

  /**
   * If CATDynImplicitKeepEdgeMode has been specified for edge fillet ribbons, use the 
   * specified CATDynKeepEdgeSameConvexityMode also for potential implicit keep edges.
   * @param iUseKeepEdgeSameConvexityMode
   * <ul>
   * <li> FALSE: Turn the mode off
   * <li> TRUE : Turn the mode on
   * </ul>
   */
  virtual void UseKeepEdgeSameConvexityModeForImplicitKeepEdges(
    CATBoolean iUseKeepEdgeSameConvexityMode) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDynAdvancedFillet(); // -> delete can't be called
};

/**
 * Creates a CATICGMDynAdvancedFillet operator.
 * @param iContainer
 * The factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.  
 * @param iPart
 * The pointer to the body to fillet. 
 * When set to <tt>NULL</tt>, the different ribbons can be defined on several bodies.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMDynAdvancedFillet *CATCGMCreateDynAdvancedFillet(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iPart = NULL);

#endif /* CATICGMDynAdvancedFillet_h_ */
