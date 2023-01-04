#ifndef CATIPGMTopCorner_h_
#define CATIPGMTopCorner_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopTangentCurveOperator.h"
#include "CATCircleMode.h"
#include "CATMathConstant.h"

class CATBody;
class CATMathDirection;
class CATMathPoint;
class CATWire;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopCorner;

/**
* Class representing the operator that computes a round corner between two wire bodies.
* <br>There is no unique solution to the corner computation: the input wires
* cut the corner in two portions. These two portions can be retrieved together, or one can choose
* the portion to keep (<tt>CATCircleMode</tt>).
* Moreover, when choosing  the <tt>Direct</tt> or <tt>Complementary</tt> modes, the operator
* can assemble the computed corner
* on the input wires on demand (<tt>SetSupportTrimmingMode</tt>).
* <br>The center of the corner is defined at the intersection of the parallels
* to the input wires. Once given a wire on a shell, there are two parallel
* to a wire: one on each side. The side defines the orientation of the
* parallel:
* <ul>
* <li>The cross product of the normal to the shell and the tangent to the wire is positive
* side (+1)
* <li>The opposite of the cross product of the normal to the shell and the tangent 
* to the wire is the negative side (-1).
* </ul> 
* <br>The CATIPGMTopCorner operator satisfies the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
* It follows the global frame of the topological operators, except that it can return several 
* bodies, corresponding to the multiple solution it found.
*<ul>
* <li>A CATIPGMTopCorner operator is created with the <tt>CATPGMCreateTopCorner</tt> global method.
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. 
*<li>The result is accessed with 
* <ul><li>the <tt>GetResult</tt> method: all the computed corners are put in the same resulting body.
*     <li>the iterator on the solutions (<tt>BeginningCorner</tt>, <tt>NextCorner</tt>, <tt>GetCorner</tt>):
* each solution corner is put in a different body.
* </ul> 
* If you do not want 
* to keep the resulting bodies, use the @href CATICGMContainer#Remove method to remove them from the 
* geometric factory, after the operator deletion.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopCorner: public CATIPGMTopTangentCurveOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopCorner();

  /**
	* Runs <tt>this</tt> operator.
	*/
  virtual int Run() = 0;

  /**
	* Returns the number of computed corners.
	* @return
	* The number of corners.
	*/
  virtual CATLONG32 GetNumberOfCorners() const = 0;

  /**
	* Initializes the iterator of the resulting corners.
	*/
  virtual void BeginningCorner() = 0;

  /**
	* Skips to the next solution corner of <tt>this</tt> CATIPGMTopCorner operator.
	*<br>After <tt>BeginningCorner</tt>, it skips to the first solution. 
	* @return
	* The existence of the next solution.
	* <br><b>Legal values</b>:
	* <dl><dt><tt>TRUE</tt> <dd>if there is a solution
	*    <dt><tt>FALSE</tt> <dd>no more solution.</dl>
	*/
  virtual CATBoolean NextCorner() = 0;

  // This method returns 
  //    a one-domain body if the geometric solution is full in face 
  //    a multi-domain if not
  /**
	* Creates the current corner.
	* @param iCurrentJournal
	* The pointer to the journal corresponding to the creation of the current corner.
	* If <tt>NULL</tt>, the journal is not written.
	* @return
	* The pointer to the created body. If you do not want to keep it,
	* use the @CATICGMContainer#Remove method to remove it from the geometric factory, after the deletion
	* of <tt>this</tt> operator.
    */
  virtual CATBody *GetCorner(CATCGMJournalList *iCurrentJournal = NULL) = 0;

  /**
	* Retrieves the orientation of the parallels used to compute the center
	* of the corner.
	* @param ioOr1
	* The orientation of the parallel to the first wire.
	* @param ioOr2
	* The orientation of the parallel to the second wire.
	* @param ioOr3
	* The orientation of the parallel to the third wire, only in case of
	* tritangent corner.
	*/
  virtual void GetCurOrients(
    CATOrientation &ioOr1,
    CATOrientation &ioOr2,
    CATOrientation &ioOr3) const = 0;

  /**
    * @nodoc
    */
  virtual void GetCurBeginOfCorner(int &oNumWire) = 0;

  /**
	* Returns the definition of the current corner.
	* <br>To be called after the <tt>GetCorner</tt> method.
	* @param ioCenter
	* The center of the current corner.
	* @param ioRadius
	* The radius value of the current corner.
	*/
  virtual void GetCenterRadius(CATMathPoint &ioCenter, double &ioRadius) = 0;

  /**
 * Defines the orientations to take for the parallels to the input wires.
 * @param iOrientCrv1
 * The orientation of the parallel to the first wire. If <tt>0</tt>, 
 * the two sides parallels are computed.
 * @param iOrientCrv2
 * The orientation of the parallel to the second wire. If <tt>0</tt>, 
 * the two sides parallels are computed.
 * @param iOrientCrv3
 * The orientation of the parallel to the third wire. If <tt>0</tt>, 
 * the two sides parallels are computed. In case of tritangent corner only.
 */
  virtual void SetOffsetOrientation(
    int iOrientCrv1,
    int iOrientCrv2,
    int iOrientCrv3 = 0) = 0;

  /**
    * @nodoc
    */
  virtual void SetBeginOfCorner(int iNumWire) = 0;

  /**
    * @nodoc
    */
  virtual void GetBeginOfCorner(int &oNumWire) = 0;

  /**
 * Retrieves the defined orientations to take for the parallels to the input wires.
 * @param ioOrientCrv1
 * The orientation of the parallel to the first wire. If <tt>0</tt>, 
 * the two sides parallels are computed.
 * @param ioOrientCrv2
 * The orientation of the parallel to the second wire. If <tt>0</tt>, 
 * the two sides parallels are computed.
 * @param ioOrientCrv3
 * The orientation of the parallel to the third wire. If <tt>0</tt>, 
 * the two sides parallels are computed. In case of tritangent corner only.
	*/
  virtual void GetOffsetOrientation(
    int &ioOrientCrv1,
    int &ioOrientCrv2,
    int &ioOrientCrv3) const = 0;

  /**
	* Returns all the computed corners in a single body.
	* <br>In this case, <tt>GetNumberOfCorners</tt> and <tt>GetResult()->GetNumberOfDomain()</tt> can be different.
	* @return
	* The pointer to the resulting body. If you do not want to keep it, use the @href CATICGMContainer#Remove method
	* to remove it from the geometric factory after the <tt>delet</tt>ion</tt> of <tt>this</tt> operator.
	*/
  virtual CATBody *GetResult() = 0;

  /**
    * @nodoc
    * Defines whether the input wires must be assembled in the resulting body.
    * In this case, the iterator cannot be used.
    * @param iTrimmingMode
    * The assembly mode.
    * <br><b>Legal values</b>:
    * <tt>1</tt> if the assembly must be done, <tt>0</tt> otherwise.
    * @return
    * <tt>0</tt> if the assembly is compatible with the relimitation mode, <tt>1</tt> otherwise. 
    * In this last case, <tt>CATCircleMode</tt> must changed to <tt>Direct</tt>.
    */
  virtual CATLONG32 SetSupportTrimmingMode(const CATLONG32 iTrimmingMode) = 0;

  /**
    * @nodoc
    * Returns whether the input wires must be assembled in the resulting body.
    * In this case, the iterator cannot be used.
    * @param iTrimmingMode
    * The assembly mode.
    * <br><b>Legal values</b>:
    * <tt>1</tt> if the assembly must be done, <tt>0</tt> otherwise.
    * @return
    * <tt>0</tt> if the assembly is compatible with the relimitation mode, <tt>1</tt> otherwise. 
    * In this last case, <tt>CATCircleMode</tt> must changed to <tt>Direct</tt>.
    */
  virtual CATLONG32 GetSupportTrimmingMode(CATLONG32 &iTrimmingMode) = 0;

  /**
  * Defines whether the input wires can be assembled in the resulting body, and how they can be assembled.
  * @param iTrimmingSide
  * The assembly side
  * <br><b>Legal values</b>: 
  * <tt>0</tt> if the assembly can be done for all input wires,
  * <tt>1</tt> if the assembly can be done just for the first input wire,
  * <tt>2</tt> if the assembly can be done just for the last input wire.
  * @param iTrimmingMode
  * The assembly mode.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if the assembly must be done, <tt>0</tt> otherwise.
  * @return
  * <br><b>Legal values</b>:
  * <tt>1</tt> if the assembly must be done, <tt>0</tt> otherwise.
  * In this last case, <tt>CATCircleMode</tt> must changed to <tt>Direct</tt>.
  */
  virtual CATLONG32 SetSupportTrimmingSideAndMode(
    const CATLONG32 iTrimmingSide,
    const CATLONG32 iTrimmingMode) = 0;

  /**
  * Returns whether the input wires can be assembled in the resulting body, and how they can be assembled.
  * In this case, the iterator cannot be used.
  * @param oTrimmingSide
  * The assembly side.
  * <br><b>Legal values</b>:
  * <tt>0</tt> if the assembly can be done for all input wires,
  * <tt>1</tt> if the assembly can be done just for the first input wire,
  * <tt>2</tt> if the assembly can be done just for the last input wire.
  * @param oTrimmingMode
  * The assembly mode.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if the assembly must be done, <tt>0</tt> otherwise.
  * @return
  * <tt>0</tt> if the assembly is compatible with the relimitation mode, <tt>1</tt> otherwise. 
  */
  virtual CATLONG32 GetSupportTrimmingSideAndMode(
    CATLONG32 &oTrimmingSide,
    CATLONG32 &oTrimmingMode) = 0;

  /** @nodoc */
  virtual CATLONG32 SetSupportTrim(
    const CATLONG32 iTrimmingSide,
    const CATLONG32 iTrimmingMode) = 0;

  /** @nodoc */
  virtual CATLONG32 GetSupportTrim(
    CATLONG32 iTrimmingSide,
    CATLONG32 &oTrimmingMode) = 0;

  /**
	* Defines the relimition mode of <tt>this</tt> corner operator.
	* @param iCircleMode
	* The relimitation mode of the corner. Do not use the <tt>Angular</tt>
	* value.
	* @param iStart
	* Not to be used.
	* @param iEnd
	* Not to be used.
	* @return
	* <tt>0</tt> if the relimitation mode is compatible with the assembly mode, <tt>1</tt> otherwise.
	* In this last case, the <tt>Direct</tt> mode must be set.
	*/
  virtual CATLONG32 SetCircleMode(
    CATCircleMode iCircleMode,
    double iStart = 0.0,
    double iEnd = 0.0) = 0;

  /**
	* Retrieves the relimitation mode of <tt>this</tt> corner operator.
	* @param ioCircleMode
	* The relimitation mode.
	* @param ioStart
	* The value is not touched.
	* @param ioEnd
	* The value is not touched.
	*/
  virtual void GetCircleMode(
    CATCircleMode &ioCircleMode,
    double &ioStart,
    double &ioEnd) = 0;

  /** @nodoc */
  virtual CATBoolean GetCircularData(
    CATMathPoint &oCenter,
    CATAngle &oRadius,
    CATMathDirection &oFirst,
    CATMathDirection &oSecond,
    CATAngle &oStartAngle,
    CATAngle &oEndAngle) const = 0;

  /**
	* Set the direction .
  * To be used only in case of 3D corner definition (by default a direction will be automatically calculated)
	* @param iDirectionFor3DCorner
	* This is the direction of the cylinder which will be the support of the 3D corner.
	*/
  virtual void SetDirection(const CATMathDirection &iDirectionFor3DCorner) = 0;

  /**
	* Get the direction.
  * To be used only in case of 3D corner definition (by default a direction will be automatically calculated)
	* @param oDirectionFor3DCorner
	* The computed direction.
	* @param oAutomaticModeForDirection
  * Returns whether the direction has been computed.
	*/
  virtual void GetDirection(
    CATMathDirection &oDirectionFor3DCorner,
    CATBoolean &oAutomaticModeForDirection) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopCorner(); // -> delete can't be called
};

/**
* Creates a CATIPGMTopCorner operator that computes a rounded corner between two wires lying
* on a shell domain.
* <br><b>Orientation</b>: The resulting wire is oriented from the first input wire
* to the second one for open corner. On the other hand,
* a complete corner is oriented in the direct sense with regards to the shell orientation.<br>
* <br><b>Journal</b>: The corner edge is written as created.
* @param iFactory
* The pointer to the factory of the resulting body.
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param iCurve1
* The pointer to the body defining the first wire. 
* @param iCurve2
* The pointer to the body defining the second wire.
* @param iSupport
* The pointer to the body defining the common support of the two input wires.
* @param iRadius
* The radius of the rounded corner.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCorner *CATPGMCreateTopCorner(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iCurve1,
  CATBody *iCurve2,
  CATBody *iSupport,
  double iRadius);

#endif /* CATIPGMTopCorner_h_ */
