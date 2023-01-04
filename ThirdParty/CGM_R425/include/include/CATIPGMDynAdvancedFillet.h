#ifndef CATIPGMDynAdvancedFillet_h_
#define CATIPGMDynAdvancedFillet_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynFillet.h"
#include "CATFreeFormDef.h"
#include "CATMathDef.h"

/**
 * @level Protected
 * @usage U1
 */

class CATBody;
class CATDynSolidFilletCGM;
class CATFilletCrossPartingLinker;
class CATGeoFactory;
class CATTopData;
class CATFilletVariousParameters;
class CATMathPoint;
class CATIPGMTopCheckJournal;
class CATRibbonsReorderTracker;
class CATLISTP(CATMathDirection);
class CATLISTP(CATMathPoint);
class CATLISTP(CATDynFilletVertexRibbonOrder);
class CATLISTP(CATDynEdgeFilletRibbon);
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynAdvancedFillet;
/**
* Class defining an operator to create a fillet.
* This operator offers more capabilities than <tt>CATICGMDynFillet</tt> and 
* might be able to generate a result in cases where <tt>CATICGMDynFillet</tt> could fail.
* <br>
* <br>
* The <tt>CATIPGMDynAdvancedFillet</tt> operator follows the global frame of the topological
* operators and satisfies the smart mechanism: 
* the input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>A <tt>CATIPGMDynAdvancedFillet</tt> operator is created with the <tt>CATPGMCreateDynAdvancedFillet</tt> global function:
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
* <li>Options must be precised (such as the faces or edges to fillet) with the appropriate methods, before
* asking for the computation with the <tt>Run</tt> method. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMDynAdvancedFillet: public CATIPGMDynFillet
{
public:
  /**
   * Constructor
   */
  CATIPGMDynAdvancedFillet();

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
  * @nodoc
  */
  virtual void SetRadiusLawMode(const CATLONG32 iRadiusLawMode) = 0;

  /**
  * @nodoc
  */
  virtual void SetFilletVariousParameters(const CATFilletVariousParameters *iFilletParams) = 0;

   /**
	 * Defines a face or plane to stop the fillet. 
     * @param iBody
	 * The body which contains the shell used as a limiting element.
	 * @param iSkin
	 * The shell to be used as a limiting element.
	 * @param iOrientation
	 * The orientation of the edge with respect to the limiting element.
	 * @param iSmartCrossParting
	 * The parting option:
	 * <ul>
	 * <li> 0: no parting
	 * <li> 1: parting is activated
	 * </ul>
	 */
#ifdef CATIACGMV5R23
  /** @nodoc */
  virtual void AddLimitingElement(
    CATBody *iBody,
    CATDomain *iSkin,
    const CATOrientation iOrientation) = 0;

  /** @nodoc */
  virtual void AddLimitingElement(
    CATBody *iBody,
    CATDomain *iSkin,
    const CATOrientation iOrientation,
    const int iSmartCrossParting) = 0;

#else
  /** @nodoc */
  virtual void AddLimitingElement(
    CATBody *iBody,
    CATDomain *iSkin,
    const CATOrientation iOrientation,
    const int iSmartCrossParting = 0) = 0;
#endif

  /**
  * @nodoc
  */
  virtual void CreateLimitingBodiesFrom(
    const CATLISTP(CATMathPoint) &iPoints,
    const CATLISTP(CATMathDirection) &iDirections,
    const CATListOfInt *iListOfInfo = NULL) = 0;

  /**
  * @nodoc
  */
  virtual void CreateCallBackForG1Tracks( ) = 0;

    /**
  * @nodoc
  */
  virtual HRESULT ConvertSetbacksFromRelativeToAbsolute(
    const CATLISTP(CATDynEdgeFilletRibbon) &iRibbonsList,
    const CATListOfDouble *iRelativeSetbacks,
    CATListOfDouble &ioAbsoluteSetbacks,
    CATLISTP(CATEdge) &ioEdgesList,
    CATListOfDouble &ioRatioList,
    CATListOfInt &ioDirectionList,
    CATMathPoint * iCommonVtxMathPoint = NULL) = 0;

  /**
  * @nodoc
  */
  virtual void SetCollisionCheckMode(CATBoolean iCollisionCheckMode) = 0;

  /**
  * @nodoc
  */
  virtual void SetMultiRibbonSafeMode(CATBoolean iMultiRibbonSafeMode) = 0;

  /**
  * @nodoc
  */
  virtual void SetCreateZeroSetbackDiabolo(CATBoolean iZeroSetbackDiabolo) = 0;

  /**
  * @nodoc
  */
  virtual void SetFilletIntersectionMode() = 0;

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
  * @nodoc
  */
  virtual void SetFlatEnding() = 0;

  /**
  * To keep features that are entirely engulfed by the result of a fillet operation the method SetKeepFeature should be used.
  * @param iKeepFeature
  * Keep feature option: CATTrue – feature kept; CATFalse – feature not kept. 
  * By default a fillet operation does not keep any feature that isn’t interfering with the boundary of the fillet. 
  */
  virtual void SetKeepFeature( CATBoolean iKeepFeature ) = 0;

  /**
  * @nodoc
  */
  virtual void SetVariableJointEnabled(CATBoolean iSmoothCornerPreferred) = 0;

  /**
  * @nodoc
  */
  virtual void SetSmoothCornerPreferred(CATBoolean iSmoothCornerPreferred) = 0;

  /**
  * @nodoc
  */
  virtual void SetCrossPartingLinker(CATFilletCrossPartingLinker *iLinker = NULL) = 0;

  /**
  * @nodoc
  */
  virtual void SetVertexRibbonOrderList(
    CATLISTP(CATDynFilletVertexRibbonOrder) &iVertexRibbonOrderList) = 0;

  /**
  * @nodoc
  * INTERNAL USE. DEDICATED TO LIVEFILLET<br>
  * Assign a Ribbons Reorder Tracker.
  */
  virtual void SetRibbonsReorderTracker(CATRibbonsReorderTracker *iTracker) = 0;

  /**
  * @nodoc
  * INTERNAL USE. DEDICATED TO AUTOFILLET<br>
  * Does not simplify the possible fat edges bounding the computed ribbon.
  */
  virtual void DisableFatEdgesSimplification() = 0;

   /**
  * @nodoc
  * INTERNAL USE. DEDICATED TO AUTOFILLET.
  */
  virtual void DisableRelimitation(CATBoolean iDisableRelimitation) = 0;

  /**
  * @nodoc
  * INTERNAL USE. DEDICATED TO AUTOFILLET.
  */
  virtual void AddSupportJournalInfo(CATBoolean iAddSupportJournalInfo) = 0;
 
   /**
  * @nodoc
  * INTERNAL USE. DEDICATED TO AUTOFILLET.
  */
  virtual void EnableSuperMaxOption(CATBoolean iEnableSuperMaxOption) = 0;

   /**
  * @nodoc
  * INTERNAL USE. DEDICATED TO AUTOFILLET.
  */
  virtual void SetBestInInSelectionPoint(CATMathPoint &iBestInInSelectionPoint) = 0;

   /**
  * @nodoc
  * INTERNAL USE. DEDICATED TO AUTOFILLET.
  */
  virtual CATBoolean IsUntwistFillFunctionUsed() const = 0;

   /**
  * @nodoc
  * INTERNAL USE. 
  * Activates support curvature control to filter ribbons crossing support skin .
  */ 
  virtual void SetSupportCurvatureCheck() = 0;

   /**
  * @nodoc
  * INTERNAL USE. DEDICATED TO AUTOFILLET.
  * Activate new tritangent fillet algorithm.
  */
  virtual void SetDoubleCircleTritangentFilletMode() = 0;

  /**
  * @nodoc
  * When several ribbons are possible in a FaceFace Fillet, 
  * use a Help Point to choose the edge where the ribbon must be computed.
  */
  virtual void SetHelpPoint(CATMathPoint &iHelpPoint) = 0;

  /**
  * @nodoc
  * Allow or forbid (default) use of DRep information. 
  */
  virtual void SetLiveBodyAllowed(CATBoolean iLiveBodyAllowed) = 0;

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

  // IZE wk. 01 2010 IR 021460 Some checks are too restrictive for SheetMetal configurations
  /**
   * @nodoc
   */
  virtual void SetUnplugChecksForSheetMetal(CATBoolean iUnplugChecksForSheetMetal) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynAdvancedFillet(); // -> delete can't be called
};

/**
 * Creates a CATIPGMDynAdvancedFillet operator.
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
ExportedByCATGMOperatorsInterfaces CATIPGMDynAdvancedFillet *CATPGMCreateDynAdvancedFillet(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iPart = NULL);

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynFillet *CATPGMCreateAdvancedDynFillet(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iPart,
  CATBoolean iMultiRibbSafeMode);

#endif /* CATIPGMDynAdvancedFillet_h_ */
