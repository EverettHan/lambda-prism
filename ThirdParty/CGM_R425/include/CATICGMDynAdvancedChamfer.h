#ifndef CATICGMDynAdvancedChamfer_h_
#define CATICGMDynAdvancedChamfer_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMDynChamfer.h"
#include "CATFreeFormDef.h"
#include "CATMathDef.h"

class CATBody;
class CATDynSolidChamferCGM;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMDynAdvancedChamfer;

/**
 * Class defining the operator to chamfer edges of a 3D body or a skin body.
 * This operator offers more capabilities that <tt>CATICGMDynChamfer</tt> and 
 * generates a result in cases where <tt>CATICGMDynChamfer</tt> fails.
 * <br>Several chamfering operations (called ribbons, <tt>CATDynChamferRibbon</tt>) 
 * can be defined in the same operator. 
 * By default, a ribbon is automatically propagated by following the tangential
 * continuity of its support, but this propagation can be switched off.
 *<br>
 * The <tt>CATICGMDynAdvancedChamfer</tt> operator follows the global frame of the topological 
 * operators and satisfies the smart mechanism: 
 * the input bodies are not modified. A new resulting body is created, 
 * possibly sharing data with the input bodies.
 *<ul>
 * <li>A <tt>CATICGMDynAdvancedChamfer</tt> operator is created with the <tt>CATCGMCreateDynAdvancedChamfer</tt> global function:
 * It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
 *<li>Options can be precised (such as the faces or edges to chamfer) with the appropriate methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMDynAdvancedChamfer: public CATICGMDynChamfer
{
public:
  /**
   * Constructor
   */
  CATICGMDynAdvancedChamfer();

  /**
   * Sets internal continuity level of chamfer ribbon
   * @param iContinuityLevel
   * Continuity level requested. Use either CATFrFPointCont or CATFrFTangentCont. Default is CATFrFPointCont.
   * @param iTolerance
   * Maximum deformation allowed to achieve the continuity. Not used as of now.
   */
  virtual void SetContinuityLevel(
    const CATFrFContinuity iContinuityLevel,
    const CATPositiveLength iTolerance = 0.) = 0;

  /**
   * Activates "cap" shape of chamfer corners
   */
  virtual void SetCornerCap() = 0;

  /**
   * Turns on the mode for the treatment of bad shapes, if encountered. 
   * It is recommended that you always call this method after creating this chamfer operator.
   */
  virtual void SetBadShapeTreatmentOn() = 0;

  /**
  * To keep features that are entirely engulfed by the result of a chamfer operation the method SetKeepFeature should be used.
  * @param iKeepFeature
  * Keep feature option: CATTrue – feature kept; CATFalse – feature not kept. 
  * By default a chamfer operation does not keep any feature that isn’t interfering with the boundary of the chamfer. 
  */
  virtual void SetKeepFeature(CATBoolean iKeepFeature) = 0;

  /**
  * Sets the approx mode - The chamfer distances will not be respected.
  * Useful to avoid twists and bad shapes.
  * Only D1D2 type chamfer supported currently.
  */
  virtual void SetApproxChamferMode() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDynAdvancedChamfer(); // -> delete can't be called
};

/**
 * Creates a CATICGMDynAdvancedChamfer operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iPart
 * The pointer to the body to chamfer.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.  To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMDynAdvancedChamfer *CATCGMCreateDynAdvancedChamfer(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iPart);

#endif /* CATICGMDynAdvancedChamfer_h_ */
