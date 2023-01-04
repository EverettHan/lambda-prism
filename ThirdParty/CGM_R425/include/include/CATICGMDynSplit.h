#ifndef CATICGMDynSplit_h_
#define CATICGMDynSplit_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMDynOperator.h"
#include "CATDynOperatorDef.h"

class CATBody;
class CATPlane;
class CATSurface;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMDynSplit;

/**
	* Class defining the operator that splits a 3D body.
	*<br>
	* The CATICGMDynSplit operator follows the global frame of the topological operators and satisfies the smart mechanism: 
	* the input bodies are not modified. A new resulting body is created, 
	* possibly sharing data with the input bodies.
	*<ul>
	* <li>A CATICGMDynSplit operator is created with the <tt>CATCGMCreateDynSplit</tt> global function:
	* It must be directly released with the <tt>Release</tt> method. It is not streamable. 
	*<li>Options can be precised (such as the splitting object) with the <tt>SetXxx</tt> methods, before
	* asking for the computation with the <tt>Run</tt> method. 
	*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
	* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
	* geometric factory.
	*</ul>
	*/
class ExportedByCATGMOperatorsInterfaces CATICGMDynSplit: public CATICGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATICGMDynSplit();

  /**
	 * Defines the splitting plane.
	 * @param iSplittingPlane
	 * The pointer to the plane that splits the input body.
	 */
  virtual void SetSplit(CATPlane *iSplittingPlane) = 0;

  /**
	 * Defines the splitting surface.
	 * @param iSplittingSurface
	 * The pointer to the surface that splits the input body.
	 */
  virtual void SetSplit(CATSurface *iSplittingSurface) = 0;

  /**
	 * Defines the splitting body.
	 * @param iSplittingBody
	 * The pointer to the body that splits the input body. <tt>iSplittingBody</tt> can contain several
	 * shell domains if their orientations are compatible.
	 */
  virtual void SetSplit(CATBody *iSplittingBody) = 0;

  /**
	 * Indicates whether the Split Operation has removed some material to the body or not.
	 * @return
     * <tt>TRUE</tt> if it has removed some material, <tt>FALSE</tt> otherwise.
    */
  virtual CATBoolean GetRelimitation() = 0;

#ifdef CATIACGMR216CAA

  /**
  * Sets Selection Mode.
  * Allows to decide among 3 possible behaviors for the split operator
  * (CATDynPositionVsPlaneMode, CATDynKeepMode, CATDynRemoveMode)
  * @param iSelectionMode
  * The selection mode. CATDynPositionVsPlaneMode by default.
  */
  virtual void SetSelectionMode(CATDynSelectionMode iSelectionMode) = 0;

#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDynSplit(); // -> delete can't be called
};

/**
* Creates a CATICGMDynSplit operator.
* @param iFactory
* The factory of the geometry. 
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param iBody
* The pointer to the body to split.
* @param iSplitType
* The portion of <tt>iBody</tt> to keep. 
* <dl>
* <dt><tt>CATSplitPositiveSideOnly</tt></dt><dd>
* The portion of <tt>iBody</tt> on the positive side of the splitting object is kept.
* <dt><tt>CATSplitNegativeSideOnly</tt></dt><dd>
* The portion of <tt>iBody</tt> on the negative side of the splitting object is kept.
* </dl>
* @param iBody
* The pointer to the body to split.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMDynSplit *CATCGMCreateDynSplit(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody,
  CATDynSplitType iSplitType);

#ifdef CATIACGMR215CAA
/**
* Creates a CATICGMDynSplit operator.
* @param iFactory
* The factory of the geometry. 
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param iBody
* The pointer to the body to split.
* @param iSplitType
* The portion of <tt>iBody</tt> to keep. 
* <dl>
* <dt><tt>CATSplitPositiveSideOnly</tt></dt><dd>
* The portion of <tt>iBody</tt> on the positive side of the splitting object is kept.
* <dt><tt>CATSplitNegativeSideOnly</tt></dt><dd>
* The portion of <tt>iBody</tt> on the negative side of the splitting object is kept.
* </dl>
* @param iSelectionMode
* Allows to decide among 3 possible behaviors for the split operator
* (CATDynPositionVsPlaneMode, CATDynKeepMode, CATDynRemoveMode)
* @param iBody
* The pointer to the body to split.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMDynSplit *CATCGMCreateDynSplit(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody,
  CATDynSplitType iSplitType,
  CATDynSelectionMode iSelectionMode);
#endif

#endif /* CATICGMDynSplit_h_ */
