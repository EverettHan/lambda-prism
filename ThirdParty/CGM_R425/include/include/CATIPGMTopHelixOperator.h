#ifndef CATIPGMTopHelixOperator_h_
#define CATIPGMTopHelixOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopCurveOperator.h"
#include "CATDataType.h"
#include "CATMathDef.h"

class CATCompositeLaw;
class CATMathVector;
class CATPlane;
class CATLaw;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopHelixOperator;

/**
* Class defining a topological operator that builds an helix Body.
* <br>An helix is defined by:
* <dl><dt><tt>iHelixAxis</tt></dt><dd> The body containing a wire with a single linear
* edge. 
* <dt><tt>iHelixAxisOrientation</tt></dt><dd>The orientation of the helix
* with regards to the axis: <tt>iHelixAxisOrientation=1</tt> if the helix and
* <tt>iHelixAxis</tt> have the same orientation, <tt>-1</tt> otherwise.
* <dt><tt>iHelixOrigin</tt></dt><dd>The body containing a vertex which point 
* is the origin point of the helix. 
*  <dt><tt>iStartAngle</tt></dt><dd>The first limitation of the helix from the
* origin point. This angle is considered on the helix itself, rotating about iHelixAxis
* according to iTrigoOrientation parameter.
*  <dt><tt>iEndAngle</tt></dt><dd>The last limitation of the helix from the
* origin point. This angle is considered on the helix itself, rotating about iHelixAxis
* according to iTrigoOrientation parameter.
*  <dt><tt>iPitch</tt></dt><dd>The heigth between two turns.
*  <dt><tt>iTrigoOrientation</tt></dt><dd>The orientation of the rotation about
* the axis oriented by <tt>iHelixAxisOrientation</tt>: <tt>1</tt> to turn counterclockwise,
* <-1> to turn clockwise.
*  <dt><tt>iTaperAngle</tt></dt><dd>Defines the half angle of the cone on which the helix
* is laying: if <tt>0</tt>, the helix is computed on a cylinder.
*  <dt><tt>iTaperAngleOrientation</tt></dt><dd>Defines the location of the cone apex: 
* if <tt>1</tt>, the cone is widening along the oriented axis, <tt>-1</tt>, the cone is
* sharpening along the oriented axis.  
*</dl>
* Notice the following definition rules:  
* <ul>
* <li> <tt>iStartAngle < iEndAngle</tt>
* <li> <tt>iHelixOrigin</tt> is not on the axis.
* <li> <tt>0 <= iTaperAngle < CATPIBY2 </tt>
*</ul>
*<br> An topological helix can be created using two modes:
* <ul>
* <li>Basic mode: use directly the <tt>CATCGMCreateTopHelix</tt> global function,
* that returns the pointer to the created body.
* <li>Advanced mode: use the CATIPGMTopHelixOperator as any topological operator:
*<ul>
*<li> Create the operator with the function <tt>CATPGMCreateTopHelixOperator</tt>,
*<li> Set the parameters to tune the helix properties such as <tt>SetTaperAngle</tt>, 
*<li> Run,
*<li> Get the resulting body, 
*<li> Release the operator with the <tt>Release</tt> method after use.
*</ul>
* </ul>
*<br>The created body can be removed from the factory with the @href CATICGMContainer#Remove 
* method as any CATICGMObject.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopHelixOperator: public CATIPGMTopCurveOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopHelixOperator();

  /**
 * Defines the half angle of the cone on which the helix is laying.
 * @param iTaperAngle
 * if <tt>0</tt> the helix is computed on a cylinder.
 * @return
 * Not null in case of error.
 */
  virtual CATLONG32 SetTaperAngle(CATAngle iTaperAngle) = 0;

  /**
 * Defines the location of the cone apex.
 * @param iTaperAngleOrientation
 * if <tt>1</tt>, the cone is widening along the oriented axis,
 * <tt>-1</tt>, the cone is sharpening along the oriented axis.
 * @return
 * Not null in case of error.
 */
  virtual CATLONG32 SetTaperAngleOrientation(CATLONG32 iTaperAngleOrientation) = 0;

  /**
 * Defines the radius profile of the helix.
 * @param iProfile
 * The pointer to the wire body containing a single planar wire.
 * This wire describes the radius variation of the helix along the helix axis.
 * The wire may be composed of several edges. 
 * For each edge of the wire, an helix piece is be built. 
 * The result body returned by GetResult() contains a single wire where all 
 * the helix pieces are connected.
 * @param iPlaneBody
 * The pointer to a single shell body, which face is lying on a planar surface.
 * @return
 * Not null in case of error.
 */
  virtual CATLONG32 SetProfile(CATBody *iProfileBody, CATBody *iPlaneBody) = 0;

  /**
 * @nodoc
 */
#ifdef CATIACGMV5R22
  virtual CATLONG32 SetPitchLaw(CATLaw *) = 0;
#else
  virtual CATLONG32 SetPitchLaw(CATCompositeLaw *) = 0;
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopHelixOperator(); // -> delete can't be called
};

/**
 * Creates a topological operator that builds a helix body.
 * @param iFactory
 * The factory that creates the resulting body.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iHelixAxis
 * The body containing a wire with a single linear edge. 
 * @param iHelixAxisOrientation
 * The orientation of the helix with regards to the axis: <tt>iHelixAxisOrientation=1</tt> 
 * if the helix and <tt>iHelixAxis</tt> have the same orientation, <tt>-1</tt> otherwise.
 * @param iHelixOrigin
 * The pointer to the vertex body, origin of the helix.
 * @param iStartAngle
 * The first limitation of the helix from the origin point.
 * @param iEndAngle
 * The last limitation of the helix from the origin point. 
 * origin point. 
 * @param iPitch
 * The heigth between two turns.
 * @param iTrigoOrientation
 * The orientation of the rotation about the axis oriented by <tt>iHelixAxisOrientation</tt>:
 * <tt>1</tt> to turn counterclockwise, <-1> to turn clockwise.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopHelixOperator *CATPGMCreateTopHelixOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iHelixAxis,
  CATLONG32 iHelixAxisOrientation,
  CATBody *iHelixOrigin,
  CATAngle iStartAngle,
  CATAngle iEndAngle,
  CATLength iPitch,
  CATLONG32 iTrigoOrientation);

#endif /* CATIPGMTopHelixOperator_h_ */
