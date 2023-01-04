#ifndef CATICGMTopSweep_h_
#define CATICGMTopSweep_h_

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
class CATExtTopSweep;
class CATGeoFactory;
class CATGeometry;
class CATMathVector;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopSweep;

/**
 * Class representing the topological operator that sweeps a profile. 
 * <br>The operator extrudes 
 * <ul><li>either a wire body, and creates a skin body
 * <li>or a skin body, and creates a volume body.
 * </ul>
 * <br> In addition to the sweep creation, this operator provides the capability
 * to use a Boolean operation between a body (called trimming body), and the 
 * created sweep. To obtain such result, use the @href CATICGMTopExtrude#SetOperation
 * and @href CATICGMTopExtrude#SetTrim mehods of the parent class.
 *<br>
 * The CATICGMTopSweep operator follows the global frame of the topological operators 
 * and satisfies the smart mechanism: the
 * input body is not modified. A new resulting body is created, 
 * possibly sharing data with the input body. A CATICGMTopPrism operator is not streamable.
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateTopSweep</tt> global function.
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
class ExportedByCATGMOperatorsInterfaces CATICGMTopSweep: public CATICGMTopExtrude
{
public:
  /**
   * Constructor
   */
  CATICGMTopSweep();

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
    CATLength iThickness = CATLength(0.0)) = 0;

  /**
 * @nodoc
 * deprecated V5R21 SetExtrudeLimit
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
 * Either the value of the offset if <tt>iType</tt> is valued to <tt>CatLimOffsetFromProfile</tt>, 
 * or the value of the thickness if <tt>iIsThickness</tt>	is valued to <tt>CATBoolean(1)</tt> 
 * @param iLimit
 * The pointer to the geometry or the topology that stops the extrusion.
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
    CATGeometry *iLimit,
    CATBody *iPropagationBody,
    CATTopPropagationType iPropagationFlag,
    CATBoolean iIsThickness = CATBoolean(0)) = 0;

  /**
 * Defines the pulling direction to replace the previously specified spine.
 * @param iPullingDirection
 * The direction defining an implicit spine to be the projection of the guide onto a plane
 * normal to this direction.
 */
  virtual void SetPullingDirection(CATMathVector *iPullingDirection = 0) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopSweep(); // -> delete can't be called
};

/**
 * Creates a CATICGMTopSweep operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iCenterBody
 * The pointer to the wire body defining the center curve of the sweep: this center curve is the 
 * curve along which the profile is swept.
 * @param iCenterSupport
 * The pointer to the body (containing a shell or a lump domain) or the surface 
 * on which the center curve is laying on.
 * @param iSpineBody
 * The pointer to the wire body defining the spine curve of the sweep: 
 * this spine curve handles the normal to the profile plane.
 * @param iProfile
 * The pointer to the wire or the skin body defining the profile of the prism. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATICGMTopSweep
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopSweep *CATCGMCreateTopSweep(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATBody *iCenterBody,
  CATGeometry *iCenterSupport,
  CATBody *iSpineBody,
  CATBody *iProfile);

#endif /* CATICGMTopSweep_h_ */
