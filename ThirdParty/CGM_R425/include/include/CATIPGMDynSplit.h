#ifndef CATIPGMDynSplit_h_
#define CATIPGMDynSplit_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"
#include "CATDynOperatorDef.h"

class CATBody;
class CATPlane;
class CATSurface;
class CATTopData;
class CATLISTP(CATCell);
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynSplit;

/**
	* Class defining the operator that splits a 3D body.
	*<br>
	* The CATIPGMDynSplit operator follows the global frame of the topological operators and satisfies the smart mechanism: 
	* the input bodies are not modified. A new resulting body is created, 
	* possibly sharing data with the input bodies.
	*<ul>
	* <li>A CATIPGMDynSplit operator is created with the <tt>CATPGMCreateDynSplit</tt> global function:
	* It must be directly released with the <tt>Release</tt> method. It is not streamable. 
	*<li>Options can be precised (such as the splitting object) with the <tt>SetXxx</tt> methods, before
	* asking for the computation with the <tt>Run</tt> method. 
	*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
	* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
	* geometric factory.
	*</ul>
	*/
class ExportedByCATGMOperatorsInterfaces CATIPGMDynSplit: public CATIPGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynSplit();

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
    * @nodoc
	 * Returns the cells of the Result Body which have been arbitrarily kept (not cut by the SplittingBody).
	 * Nota : if the SplittingBody is a planar skin, these cells are positionned versus the plane.
    * @param iUnknownPositionCells
	 */
  virtual void GetUnknownPositionCells(
    CATLISTP(CATCell) &iUnknownPositionCells) = 0;

  /**
	 * Indicates whether the Split Operation has removed some material to the body or not.
	 * @return
     * <tt>TRUE</tt> if it has removed some material, <tt>FALSE</tt> otherwise.
    */
  virtual CATBoolean GetRelimitation() = 0;

  /**
  * @nodoc
  * Sets Extrapolation Mode. Used if the splitting body does not fully split the body to split.
  * The splitting body will be extrapolated according to the extrapolation mode set.
  * @param iExtrapolMode
  * The extrapolation mode. DYN_NO_EXTRAPOLATION by default.
  */
  virtual void SetExtrapolationMode(CATDynExtrapolationMode iExtrapolMode) = 0;

  /**
  * Sets Selection Mode.
  * Allows to decide among 3 possible behaviors for the split operator
  * (CATDynPositionVsPlaneMode, CATDynKeepMode, CATDynRemoveMode)
  * @param iSelectionMode
  * The selection mode. CATDynPositionVsPlaneMode by default.
  */
  virtual void SetSelectionMode(CATDynSelectionMode iSelectionMode) = 0;


#ifndef CATIACGMR217CAA
  /**
  * @nodoc
  * Internal use only.
  */
  virtual void SetExtrapolMode(short iExtrapolMode) = 0;
#endif

  /*
  * @nodoc
  * Sets Extrapolation Limit. Used if the splitting body does not fully split the body to split and we need to
  * extrapolate it.  
  * 
  * DYN_BODYBOUNDINGBOX - Extrapolate the splitting body to the oriented bounding box of the body to split.
  * DYN_THRUNEXTCONNECTED - Extrapolate the splitting body to the oriented bounding box, but only keep the 
  *                         parts of the extrapolated body that are inside the body to split and connected to
  *                         the original splitting body.   
  * The splitting body will be extrapolated according to the extrapolation mode set.
  * @param iExtrapolLimit
  * The extrapolation mode. DYN_THRUNEXTCONNECTED by default.
  */
  virtual void SetExtrapolationLimit(CATDynExtrapolationLimit iExtrapolLimit) = 0;

  /**
	* Option to simplify or not the volumes of the result 
	* @param iNoVolumicSimplif
	* Simplify or not the volumes, simplify by default
	*/
  virtual void SetNoVolumicSimplif(CATBoolean iNoVolumicSimplif) = 0;

  /**
	* Option to all volumes of the same lump 
	* @param iLumpPropagation
	* propagate or not the volumes, no propagation by default
	*/
  virtual void SetLumpPropagation(CATBoolean iLumpPropagation) = 0;
protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynSplit(); // -> delete can't be called
};

/**
* Creates a CATIPGMDynSplit operator.
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
ExportedByCATGMOperatorsInterfaces CATIPGMDynSplit *CATPGMCreateDynSplit(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody,
  CATDynSplitType iSplitType);

/**
* @nodoc
* Deprecated. Use CATPGMCreateDynSplit.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMDynSplit *CATPGMDynCreateSplit(
  CATGeoFactory *iFactory,
  CATBody *iBody,
  CATDynSplitType iSplitType,
  CATCGMJournalList *iJournal = NULL);

#endif /* CATIPGMDynSplit_h_ */
