#ifndef CATIPGMTopPrism_h_
#define CATIPGMTopPrism_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopExtrude.h"
#include "CATTopLimit.h"
#include "CATTopLimitType.h"
#include "CATMathDef.h"
#include "CATTopPropagationType.h"
#include "CATTopDefine.h"
#include "CATIACGMLevel.h"
#include "CATExtrudeLimitSide.h"
#include "CATExtrudeLimitThicknessOrOffsetType.h"

class CATBody;
class CATCGMActivateDebug;
class CATCGMJournalList;
class CATExtTopPrism;
class CATGeoFactory;
class CATGeometry;
class CATMathDirection;
class CATMathPoint;
class CATTopData;
class CATTopPrismContextForFastRun;
class CATLISTP(CATCell);
#ifdef CATIACGMR217CAA
#ifdef CATIACGMR418CAA
struct CATExtrudeLimitName;
#else
class CATExtrudeLimitName;
#endif
class CATLISTP(CATExtrudeLimitName);
#endif

/**
 * @level Protected
 * @usage U1
 */

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopPrism;

/**
 * Class representing the topological operator that creates a prism. 
 * <br>The operator extrudes 
 * <ul>
 * <li>either a wire body, and creates a skin body
 * <li>or a skin body, ans creates a volume body.
 * </ul>
 * <br>In addition to the prism creation, this operator provides the capability
 * to use a Boolean operation between a body (called trimming body), and the 
 * created prism. A typical example is the stiffener. The stiffener itself is created by extruding a 
 * profile, the resulting body is obtained by specifying a boolaan operation to stick the stiffener to 
 * a support body. To obtain such result, use the @href CATIPGMTopExtrude#SetOperation
 * and @href CATIPGMTopExtrude#SetTrim mehods of the parent class.
 *<br>
 * The CATIPGMTopPrism operator follows the global frame of the topological operators 
 * and satisfies the smart mechanism: the
 * input body is not modified. A new resulting body is created, 
 * possibly sharing data with the input body. A CATIPGMTopPrism operator is not streamable.
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATPGMCreateTopPrism</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. In particular,
 * define the type of limitations, and, if needed, the Boolean operation.
 * <li>Run it
 * <li>Get the resulting extrusion with the @href CATIPGMTopExtrude#GetResult method, and the result
 * of the Boolean operation with the @href CATIPGMTopExtrude#GetBooleanResult method. If you do not want 
 * to keep these resulting bodies, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopPrism: public CATIPGMTopExtrude
{
public:
  /**
   * Constructor
   */
  CATIPGMTopPrism();


  /**
 * Defines the type of limitation of each extremity along the extrusion (center curve) direction.
 * <br>To be called for each extremity, if you do not want to keep
 * the default options of the global creation function.
 * @param iId
 * The first or last extremity.
 * @param iType
 * The type of limit on the extremity.
 * @param iIsAxisReverted
 * The orientation.
 * <br><b>Legal values</b>: <tt>TRUE</tt> for the same orientation as the direction defined at the operator
 * creation, <tt>FALSE</tt> for an opposite orientation. In general, use <tt>TRUE</tt> for the start limit,
 * and <tt>FALSE</tt> for the end limit.
 * @param iOffset
 * The value of the offset if <tt>iType</tt> has the value <tt>CatLimOffsetFromProfile</tt>.
 * @param iLimit
 * The pointer to the geometry or the topology that stops the extrusion.
 * @param iPropagationBody
 * The pointer to the body which contains <tt>iLimit</tt>, thus allowing the
 * propagation of the trimming specification. To use if <tt>iType = CatLimUntil</tt> and
 * <tt>iPropagationFlag = CatPropagClosing</tt>  or if <tt>iType = CatLimNextAlongAxis</tt>
 * or <tt>iType = CatLimLastAlongAxis</tt> 
 * @param iPropagationFlag
 * The management of the propagation.  
 * @param iThickness
 * defines the value of any thickness which must be applied to the considering relimitation
 */
  virtual void SetExtrudeLimit(
    CATTopLimit iId,
    CATTopLimitType iType,
    CATBoolean iIsAxisReverted,
    CATLength iOffset,
    CATGeometry *iLimit,
    CATBody *iPropagationBody,
    CATTopPropagationType iPropagationFlag,
    CATLength iThickness = CATLength(0)) = 0;

  /**
 * Defines the type of limitation of each extremity along the extrusion (center curve) direction.
 * <br>To be called for each extremity, if you do not want to keep
 * the default options of the global creation function.
 * @param iId
 * The first or last extremity.
 * @param iType
 * The type of limit on the extremity.
 * @param iIsAxisReverted
 * The orientation.
 * <br><b>Legal values</b>: <tt>TRUE</tt> for the same orientation as the direction defined at the operator
 * creation, <tt>FALSE</tt> for an opposite orientation. In general, use <tt>TRUE</tt> for the start limit,
 * and <tt>FALSE</tt> for the end limit.
 * @param iOffset
 * The value of the offset if <tt>iType</tt> has the value <tt>CatLimOffsetFromProfile</tt>.
 * @param iLimit
 * The pointer to the geometry or the topology that stops the extrusion.
 * @param iPropagationBody
 * The pointer to the body which contains <tt>iLimit</tt>, thus allowing the
 * propagation of the trimming specification. To use if <tt>iType = CatLimUntil</tt> and
 * <tt>iPropagationFlag = CatPropagClosing</tt>  or if <tt>iType = CatLimNextAlongAxis</tt>
 * or <tt>iType = CatLimLastAlongAxis</tt> 
 * @param iPropagationFlag
 * The management of the propagation.  
 * @param iThickness
 * defines the value of any thickness which must be applied to the considering relimitation
 */
  virtual void SetExtrudeLimit(
    CATTopLimit iId,
    CATTopLimitType iType,
    CATBoolean iIsAxisReverted,
    CATLength iOffset,
    CATLISTP(CATCell) &iLimit,
    CATBody *iPropagationBody,
    CATTopPropagationType iPropagationFlag,
    CATLength iThickness = CATLength(0)) = 0;

  /**
 * @deprecated V5R21 SetExtrudeLimit
 * Defines the type of limitation of each extremity along the extrusion direction.
 * <br>To be called for each extremity, if you do not want to keep
 * the default options of the global creation function.
 * @param iId
 * The first or last extremity.
 * @param iType
 * The type of limit on the extremity.
 * @param iIsAxisReverted
 * The orientation.
 * <br><b>Legal values</b>: <tt>FALSE</tt> for the same orientation as the direction defined at the operator
 * creation, <tt>TRUE</tt> for an opposite orientation. In general, use <tt>TRUE</tt> for the start limit,
 * and <tt>FALSE</tt> for the end limit.
 * @param iOffset
 * Either the value of the offset if <tt>iType</tt> is valued to <tt>CatLimOffsetFromProfile</tt>, 
 * or the value of the thickness if <tt>iIsThickness</tt>	is valued to <tt>CATBoolean(1)</tt> 
 * @param iLimit
 * The pointer to the geometry ( deprecated ) or a body that stops the extrusion.
 * @param iPropagationBody
 * The pointer to the body which contains <tt>iLimit</tt>, thus allowing the
 * propagation of the trimming specification. To use if <tt>iType = CatLimUntil</tt> and
 * <tt>iPropagationFlag = CatPropagClosing</tt>  or if <tt>iType = CatLimNextAlongAxis</tt>
 * or <tt>iType = CatLimLastAlongAxis</tt> 
 * @param iPropagationFlag
 * The management of the propagation.  
 * If <tt>iType = CatLimUntil</tt> and <tt>iPropagationFlag = CatPropagExtrapolated<tt> ,
 * extrapolation works only if <tt>iLimit<tt> is a single face body.
 * @param iIsThickness
 * Defines whether a thickness is applied from the body <tt>iPropagationBody</tt> to define the relimitation. 
 * In this case, the value of the the thickness is <tt>iOffset</tt>
 */
  virtual void SetLimit(
    CATTopLimit iId,
    CATTopLimitType iType,
    CATBoolean iIsAxisReverted,
    CATLength iOffset,
    CATGeometry *iLimit,
    CATBody *iPropagationBody,
    CATTopPropagationType iPropagationFlag,
    CATBoolean iIsThickness = CATBoolean(0)) = 0;

  /**
 * @deprecated V5R21 SetExtrudeLimit
 * Defines the type of limitation of each extremity along the extrusion direction.
 * <br>To be called for each extremity , if you do not want to keep
 * the default options of the global creation function.
 * @param iId
 * The first or last extremity.
 * @param iType
 * The type of limit on the extremity.
 * @param iIsAxisReverted
 * The orientation.
 * <br><b>Legal values</b>: <tt>TRUE</tt> for the same orientation as the direction defined at the operator
 * creation, <tt>FALSE</tt> for an opposite orientation. In general, use <tt>TRUE</tt> for the start limit,
 * and <tt>FALSE</tt> for the end limit.
 * @param iOffset
 * Either the value of the offset if <tt>iType</tt> is valued to <tt>CatLimOffsetFromProfile</tt>, 
 * or the value of the thickness if <tt>iIsThickness</tt>	is valued to <tt>CATBoolean(1)</tt> 
 * @param iLimit
 * The list of pointers to faces belonging to <tt>iPropagationBody</tt> that stop the extrusion.
 * @param iPropagationBody
 * The pointer to the body which contains <tt>iLimit</tt>, thus allowing the
 * propagation of the trimming specification. To use if <tt>iType = CatLimUntil</tt> and
 * <tt>iPropagationFlag = CatPropagClosing</tt>  or if <tt>iType = CatLimNextAlongAxis</tt>
 * or <tt>iType = CatLimLastAlongAxis</tt> 
 * @param iPropagationFlag
 * The management of the propagation.  
 * @param iIsThickness
 * Defines whether a thickness is applied from the body <tt>iPropagationBody</tt> to define the relimitation. 
 * In this case, the value of the the thickness is <tt>iOffset</tt>
 */
  virtual void SetLimit(
    CATTopLimit iId,
    CATTopLimitType iType,
    CATBoolean iIsAxisReverted,
    CATLength iOffset,
    CATLISTP(CATCell) &iLimit,
    CATBody *iPropagationBody,
    CATTopPropagationType iPropagationFlag,
    CATBoolean iIsThickness = CATBoolean(0)) = 0;


  /**
    * @nodoc
    * Sets the side of the intersection to choose for the limitation of each extremity along the extrusion
    * (center curve) direction when the type of limitation is CATLimUntil.
    * <br>To be called for each extremity, if you do not want to keep
    * the default options of the global creation function.
    * @param iId
    * The first or last extremity.
    * @param iSide
    * The side, i.e. whether the normal to the limiting geometry is aligned with extrusion direction or 
    * -extrusion direction.
    */
  virtual void SetExtrudeLimitSide(CATTopLimit iId, CATExtrudeLimitSide iSide) = 0;

  /**
    * @nodoc
    * Sets the number of the intersection to choose for the limitation of each extremity along the extrusion
    * (center curve) direction when the type of limitation is CATLimUntil.
    * <br>To be called for each extremity, if you do not want to keep
    * the default options of the global creation function.
    * @param iId
    * The first or last extremity.
    * @param iIntersectionNumber
    * The intersection number.
    * -extrusion direction.
    */
  virtual void SetExtrudeLimitIntersectionNumber(
    CATTopLimit iId,
    int iIntersectionNumber) = 0;

#ifdef CATIACGMR217CAA
   /** @nodoc
   * In case of contextual Limit and if there are several possible disconnecting intersections
   * between the extrusion and a contextual limit:
   * @param iIsRequested
   * if set to TRUE, it enables to get a list of possible naming after a first run. 
   */
   virtual void SetNamingLimitRequested (CATBoolean iIsRequested) = 0;

   /** @nodoc
   * In case of contextual Limit and if there are several possible disconnecting intersections
   * between the extrusion and a contextual limit, it enable to choose one intersection
   * between extrusion and the CATGeometry as limit.
   * @param iId
   * The first or last extremity.
   * @param iLimitName 
   * The CATSide and the IntersectionNumber
   */
  virtual void SetExtrudeLimitNaming(
    CATTopLimit iId,
    CATExtrudeLimitName *iLimitName) = 0;
 
    /** @nodoc
    * If SetNamingLimitRequested to TRUE, after a first Run, it provides the list of possible namings
    * @param iId
    * The first or last extremity.
    * @param oPossibleLimits 
    * The list of available CATExtrudeLimitName (CATSide and IntersectionNumber) 
    */
  virtual void GetExtrudeLimitNaming(
    CATTopLimit iId,
    CATLISTP(CATExtrudeLimitName) *oPossibleLimits) = 0;
#endif

  /**
 * @nodoc
 * Defines the type of limitation of each extremity along the extrusion (center curve) direction.
 * <br>To be called for each extremity, if you do not want to keep
 * the default options of the global creation function.
 * @param iId
 * The first or last extremity.
 * @param iThickness
 * defines the value of any thickness which must be applied to the considering relimitation
 * @param iThicknessOrOffsetType
 * defines the type of thickness or Offset to apply: 
 * an offset of the limit computed before extrusion
 * or a thickness applied on the resulting extrusion
 */
  virtual void SetLimitThickness(
    CATTopLimit iId,
                   CATLength                            iThickness,
                   CATExtrudeLimitThicknessOrOffsetType iThicknessOrOffsetType ) = 0;

 /**
 * @nodoc
 * Sets the stiffener mode.
 * @param iMatterSide
 * <ul>
 * <li> FALSE:  stiffener from "side" 
 * <li> TRUE:   stiffener from "top". The extrusion is performed normal to the profile plane 
 * and a thickness is added in the profile plane. 
 * In the "top" mode, the resulting stiffener is always trimmed to existing material.
 * </ul>
 */
  virtual void SetStiffenerMode(CATBoolean iMatterSide) = 0;

 /**
 * @nodoc
 * Specifies the matter side.
 * @param iMatterSide
 * The matter side is determined by standing along the direction of extrusion 
 * and watching in the direction of the wire (profile). 
 * <ul>
 * <li>Matter on your left: CATSideLeft
 * <li>Matter on you right: CATSideRight
 * </ul>
 * The specified matter side must be consistent with the stiffener creation.
 */
  virtual void SetMatterSide(CATSide iMatterSide) = 0;

 /**
 * Retrieves the main features of the created prism.
 * <br>To use after the <tt>Run</tt> method, to retrieve an upper bound of the prism length.
 * @param iOrigin
 * The reference from which the distances are computed.
 * @param iDirection
 * The direction in which the distances are computed.
 * @param oLengthMin
 * The distance from <tt>iOrigin</tt> of the first limit.
 * @param oLengthMax
 * The distance from <tt>iOrigin</tt> of the end limit.
 */
  virtual void GetLength(
    const CATMathPoint &iOrigin,
    const CATMathDirection &iDirection,
    double &oLengthMin,
    double &oLengthMax) = 0;

#ifdef CATIACGMR418CAA
  /**
   * @nodoc
   * Gets the context for fast run for this operator.
   * @return [out, CATBaseUnknown#Release]
   */
  virtual CATTopPrismContextForFastRun *GetTopPrismContextForFastRun() = 0;

  /**
   * @nodoc
   * Gets or creates the context for fast run for this operator.
   * @return [out, CATBaseUnknown#Release]
   */
  virtual CATTopPrismContextForFastRun *GetOrCreateTopPrismContextForFastRun() = 0;
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopPrism(); // -> delete can't be called
};

/**
 * Creates a CATIPGMTopPrism operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iProfile
 * The pointer to the wire or the skin body defining the profile of the prism. 
 * @param iDirection
 * The direction of the extrusion, not necessarily orthogonal to the profile.
 * @param iStartOffset
 * The first limitation along the extrusion direction.
 * @param iEndOffset
 * The second limitation along the extrusion direction, such that <tt>iStartOffset < iEndOffset</tt>.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopPrism *CATPGMCreateTopPrism(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iProfileBody,
  CATMathDirection *iDirection,
  CATLength iStartOffset,
  CATLength iEndOffset);

/**
 * @nodoc
 * Deprecated. Use CATPGMCreateTopPrism.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopPrism *CATPGMTopCreatePrism(
  CATGeoFactory *iFactory,
  CATBody *iProfileBody,
  CATMathDirection *iDirection,
  CATLength iStartOffset,
  CATLength iEndOffset,
  CATCGMJournalList *iJournal = NULL);

#endif /* CATIPGMTopPrism_h_ */
