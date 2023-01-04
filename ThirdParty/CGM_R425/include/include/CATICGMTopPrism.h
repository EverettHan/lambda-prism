#ifndef CATICGMTopPrism_h_
#define CATICGMTopPrism_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopExtrude.h"
#include "CATTopLimit.h"
#include "CATTopLimitType.h"
#include "CATMathDef.h"
#include "CATTopPropagationType.h"
#include "CATIACGMLevel.h"

class CATBody;
class CATCGMActivateDebug;
class CATCGMJournalList;
class CATGeoFactory;
class CATGeometry;
class CATMathDirection;
class CATMathPoint;
class CATTopData;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopPrism;

/**
 * Class representing the topological operator that creates a prism. 
 * <br>The operator extrudes 
 * <ul>
 * <li>either a wire body, and creates a skin body
 * <li>or a skin body, ans creates a volume body.
 * </ul>
 * <br> In addition to the prism creation, this operator provides the capability
 * to use a Boolean operation between a body (called trimming body), and the 
 * created prism. A typical example is the stiffener. The stiffener itself is created by extruding a 
 * profile, the resulting body is obtained by specifying a boolaan operation to stick the stiffener to 
 * a support body. To obtain such result, use the @href CATICGMTopExtrude#SetOperation
 * and @href CATICGMTopExtrude#SetTrim mehods of the parent class.
 *<br>
 * The CATICGMTopPrism operator follows the global frame of the topological operators 
 * and satisfies the smart mechanism: the
 * input body is not modified. A new resulting body is created, 
 * possibly sharing data with the input body. A CATICGMTopPrism operator is not streamable.
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateTopPrism</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. In particular,
 * define the type of limitations, and, if needed, the Boolean operation.
 * <li>Run it
 * <li>Get the resulting extrusion with the @href CATICGMTopExtrude#GetResult method, and the result
 * of the Boolean operation with the @href CATICGMTopExtrude#GetBooleanResult method. If you do not want 
 * to keep these resulting bodies, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATICGMTopPrism: public CATICGMTopExtrude
{
public:
  /**
   * Constructor
   */
  CATICGMTopPrism();

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
 * @nodoc
 * deprecated V5R21 SetExtrudeLimit
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
 * @nodoc
 * deprecated V5R21 SetExtrudeLimit
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

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopPrism(); // -> delete can't be called
};

/**
 * Creates a CATICGMTopPrism operator.
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
ExportedByCATGMOperatorsInterfaces CATICGMTopPrism *CATCGMCreateTopPrism(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iProfileBody,
  CATMathDirection *iDirection,
  CATLength iStartOffset,
  CATLength iEndOffset);

#endif /* CATICGMTopPrism_h_ */
