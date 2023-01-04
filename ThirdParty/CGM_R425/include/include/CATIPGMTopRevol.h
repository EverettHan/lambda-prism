#ifndef CATIPGMTopRevol_h_
#define CATIPGMTopRevol_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopExtrude.h"
#include "CATTopLimit.h"
#include "CATTopLimitType.h"
#include "CATMathDef.h"
#include "CATTopPropagationType.h"
#include "CATTopDefine.h"
#include "CATIACGMLevel.h"
#ifdef CATIACGMR217CAA
#include "CATExtrudeLimitSide.h"
#endif

class CATBody;
class CATCGMActivateDebug;
class CATCGMJournalList;
class CATGeoFactory;
class CATGeometry;
class CATMathAxis;
class CATMathDirection;
class CATMathPoint;
class CATTopData;
class CATLISTP(CATCell);
#ifdef CATIACGMR217CAA
#ifdef CATIACGMR418CAA
struct CATExtrudeLimitName;
#else
class CATExtrudeLimitName;
#endif
class CATLISTP(CATExtrudeLimitName);
#endif
class CATTopRevolContextForFastRun;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopRevol;

/**
 * Class representing the topological operator that revolves a profile.
 * <br>The operator revolves 
 * <ul><li>either a wire body, and creates a skin body
 * <li>or a skin body, and creates a volume body.
 * </ul>
 * <br> In addition to the revolution creation, this operator provides the capability
 * to use a Boolean operation between a body (called trimming body), and the 
 * created Revol. To obtain such result, use the @href CATIPGMTopExtrude#SetOperation
 * and @href CATIPGMTopExtrude#SetTrim mehods of the parent class.
 *<br>
 * The CATIPGMTopRevol operator follows the global frame of the topological operators 
 * and satisfies the smart mechanism: the
 * input body is not modified. A new resulting body is created, 
 * possibly sharing data with the input body. A CATIPGMTopRevol operator is not streamable.
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATPGMCreateTopRevol</tt> global function.
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
class ExportedByCATGMOperatorsInterfaces CATIPGMTopRevol: public CATIPGMTopExtrude
{
public:
  /**
   * Constructor
   */
  CATIPGMTopRevol();

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
    CATAngle iOffset,
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
    CATAngle iOffset,
    CATLISTP(CATCell) &iLimit,
    CATBody *iPropagationBody,
    CATTopPropagationType iPropagationFlag,
    CATLength iThickness = CATLength(0)) = 0;

  /**
 * Defines the type of limitation of each extremity along the profile.
 * <br>To be called for each extremity, if you do not want to keep
 * the default options of the global creation function.
 * @param iId
 * The first or last extremity.
 * @param iType
 * The type of limit on the extremity.
 * @param iOffset
 * The value of the offset if <tt>iType</tt> has the value <tt>CatLimOffsetFromProfile</tt> 
 * @param iLimit
 * The pointer to the geometry ( deprecated ) or a body that stops the extrusion.
 * @param iPropagationBody
 * The pointer to the body which contains <tt>iLimit</tt>, thus allowing the
 * propagation of the trimming specification. To use if <tt>iType = CatLimUntil</tt> and
 * <tt>iPropagationFlag = CatPropagClosing</tt>  or if <tt>iType = CatLimNextAlongAxis</tt>
 * or <tt>iType = CatLimLastAlongAxis</tt> 
 * @param iPropagationFlag
 * The management of the propagation.  
 * @param iIsThickness
 * Defines the value of the thickness to be applied from the body <tt>iPropagationBody</tt> to define the relimitation. 
  */
  virtual void SetProfileClosureLimit(
    CATTopLimit iId,
    CATTopLimitType iType,
    CATBoolean iIsAxisReverted,
    CATLength iOffset,
    CATGeometry *iLimit,
    CATBody *iPropagationBody,
    CATTopPropagationType iPropagationFlag,
    CATLength iThickness = CATLength(0)) = 0;

  /**
 * Defines the type of limitation of each extremity along the profile.
 * <br>To be called for each extremity, if you do not want to keep
 * the default options of the global creation function.
 * @param iId
 * The first or last extremity.
 * @param iType
 * The type of limit on the extremity.
 * @param iOffset
 * The value of the offset if <tt>iType</tt> is valued to <tt>CatLimOffsetFromProfile</tt>. 
 * @param iLimit
 * The pointer to the geometry ( deprecated ) or a body that stops the extrusion.
 * @param iPropagationBody
 * The pointer to the body which contains <tt>iLimit</tt>, thus allowing the
 * propagation of the trimming specification. To use if <tt>iType = CatLimUntil</tt> and
 * <tt>iPropagationFlag = CatPropagClosing</tt>  or if <tt>iType = CatLimNextAlongAxis</tt>
 * or <tt>iType = CatLimLastAlongAxis</tt> 
 * @param iPropagationFlag
 * The management of the propagation.  
 * @param iIsThickness
 * Defines the value of the thickness to be applied from the body <tt>iPropagationBody</tt> to define the relimitation. 
  */
  virtual void SetProfileClosureLimit(
    CATTopLimit iId,
    CATTopLimitType iType,
    CATBoolean iIsAxisReverted,
    CATLength iOffset,
    CATLISTP(CATCell) &iLimit,
    CATBody *iPropagationBody,
    CATTopPropagationType iPropagationFlag,
    CATLength iThickness = CATLength(0)) = 0;

  /**
 * @deprecated V5R21 SetProfileClosureLimit
 * Defines the type of limitation of each extremity along the profile.
 * <br>To be called for each extremity, if you do not want to keep
 * the default options of the global creation function.
 * @param iId
 * The first or last extremity.
 * @param iType
 * The type of limit on the extremity.
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
 * @param iIsThickness
 * Defines whether a thickness is applied from the body <tt>iPropagationBody</tt> to define the relimitation. 
 * In this case, the value of the the thickness is <tt>iOffset</tt>
 */
  virtual void SetLimit(
    CATTopLimit iId,
    CATTopLimitType iType,
    CATLength iOffset,
    CATGeometry *iLimit,
    CATBody *iPropagationBody,
    CATTopPropagationType iPropagationFlag,
    CATBoolean iIsThickness = CATBoolean(0)) = 0;

  /**
 * @deprecated V5R21 SetProfileClosureLimit
 * Defines the type of limitation of each extremity along the profile.
 * <br>To be called for each extremity , if you do not want to keep
 * the default options of the global creation function.
 * @param iId
 * The first or last extremity.
 * @param iType
 * The type of limit on the extremity.
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
    CATLength iOffset,
    CATLISTP(CATCell) &iLimit,
    CATBody *iPropagationBody,
    CATTopPropagationType iPropagationFlag,
    CATBoolean iIsThickness = CATBoolean(0)) = 0;

  #ifdef CATIACGMR420CAA
  /**
 * Defines an angular offset of the limitation of each extremity around the axis of revolution.
 * <br>The limitation type and geometry must be set using SetExtrudeLimit first. This is not to be used for
 * CatLimOffsetFromProfile limit types.
 * @param iId
 * The first or last extremity.
 * @param iAngle
 * The angular offset to apply to the limit. The limit is then equivalent to a transformation of the original
 * limiting geometry/geometries. The angle is not additive; subsequent calls will override any previous values.
 * It is not checked if the result intersects with the original limiting body.
 */
  virtual void SetExtrudeLimitAngleOffset(
    CATTopLimit iId, 
    CATAngle iOffset) = 0;
  #endif

  #ifdef CATIACGMR217CAA
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
 * Retrieves the main features of the created revolution.
 * <br>To use after the <tt>Run</tt> method, to retrieve an upper bound of the Revol length?
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

#ifdef CATIACGMR419CAA
 /**
 * @nodoc
 * Retrieves the main features of the created revolution.
 * <br>To use after the <tt>Run</tt> method, to retrieve an upper bound of the angle
 *subtended by the result.
 * @param oAngleMin
 * The angle from <tt>the profile</tt> to the first limit.
 * @param oAngleMax
 * The angle from <tt>the profile</tt> of the end limit.
 */
  virtual void GetAngles(double &oAngleMin, double &oAngleMax) = 0;
#endif
  /**
  * @nodoc
  */
  virtual void SetMatterSide(CATSide iMatterSide) = 0;

  /**
  * @nodoc
  */
  virtual void ApplyHalfRadShift() = 0;
#ifdef CATIACGMR418CAA
  /**
  * @nodoc
  * Gets the context for fast run for this operator.
  * @return [out, CATBaseUnknown#Release]
  */
  virtual CATTopRevolContextForFastRun *GetTopRevolContextForFastRun() = 0;

  /**
  * @nodoc
  * Gets or creates the context for fast run for this operator.
  * @return [out, CATBaseUnknown#Release]
  */
  virtual CATTopRevolContextForFastRun *GetOrCreateTopRevolContextForFastRun() = 0;
#endif // CATIACGMR418CAA

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopRevol(); // -> delete can't be called
};

/**
 * Creates a CATIPGMTopRevol operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iProfile
 * The pointer to the skin body or the (planar) wire body defining the profile of the revolution. 
 * @param iAxis
 * The axis system of the revolution, which third direction is the rotation axis. The first and second directions
 * of the axis system are not used in the definition of this CATIPGMTopRevol operator, even for the definition of
 * start and end angles.
 * @param iStartAngle
 * The first limitation of the rotation, measured (in degree) from each point of the profile. 
 * @param iEndAngle
 * The last limitation of the rotation, measured (in degree) from each point of the profile, 
 * such that <tt>iStartAngle < iEndAngle</tt>.
 * Notice for example that, if <tt>iStartAngle = - iEndAngle </tt>, the profile exactly defines the "middle" of the
 * generated surface.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopRevol *CATPGMCreateTopRevol(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iProfile,
  CATMathAxis *iAxis,
  CATAngle iStartAngle,
  CATAngle iEndAngle);

/**
 * @nodoc
 * Deprecated. Use CATPGMCreateTopRevol.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopRevol *CATPGMTopCreateRevol(
  CATGeoFactory *iFactory,
  CATBody *iProfile,
  CATMathAxis *iAxis,
  CATAngle iStartAngle,
  CATAngle iEndAngle,
  CATCGMJournalList *iJournal = NULL);

#endif /* CATIPGMTopRevol_h_ */
