#ifndef CATIPGMPowerFill_h_
#define CATIPGMPowerFill_h_

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "ListPOfCATBody.h"
#include "CATMathConstant.h"

class CATBody;
class CATEdge;
class CATMathPoint;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMPowerFill;

/**
* Class defining the topological operator that fills a space defined by a set of wires.
* <br> The wires must define a closed area and be connected.
* Continuity criteria can be specified: G0, G1, or G2 if the supporting surfaces of the wire
* are given, G0 otherwise. The supporting surfaces must be coherent to allow the operator to
* compute a G1 or G2 continuity.
* If the given continuity constraints are not compatible, the fill result will not
* satisfy the continuity contraints. 
* If the given continuity constraints define a too scattered set of normals, the shape of
* the fill result may not be correct.  It is also possible to have no result.  
* 
* <br>The CATIPGMPowerFill operator creates the resulting filling skin body
* separately from the inputs: the wires of the input bodies are not used to define the topology
* of the resulting fill body.  
*<ul>
* <li>A CATIPGMPowerFill operator is created with the <tt>CATPGMCreatePowerFill</tt> global function.
* It must be directly released with the Release method. It is is not streamable. 
*<li>Options can be specified with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
* <li>The journal corresponding to the fill operation is not yet implemented.
*</ul>
*/
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMPowerFill: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPowerFill();

  //=============
  //  Set Methods  
  //=============
  /** 
   * Sets one inner wire. An inner wire is an inner boundary of the fill result. 
   * To set N inner wires, the method AddInnerWires must be called N times. 
   * @param iListOfWires
   * The list of pointers to wire bodies representing the inner wire.
   * @param iListOfSupports
   * The list of pointers to shell bodies representing the supports associated with the wire bodies.
   * If a  wire  body has no support, the corresponding element of <tt> iListOfSupports</tt> must be
   * set to <tt> NULL</tt>.  
   * @param iListOfInnerTransitionContinuity
   * The list of the continuity criteria associated with the wire bodies.
   * The continuity criteria
   * <br><b>Legal values</b>: <tt>0</tt> for G0 continuity (default mode), <tt>1</tt> for G1 continuity,
   * or <tt>2</tt> for G2 continuity.
   */
  virtual void AddInnerWires(
    CATLISTP(CATBody) const &iListOfWires,
    CATLISTP(CATBody) const &iListOfSupports,
    CATListOfInt &iListOfInnerTransitionContinuity) = 0;

  /** 
   * Sets a list of passing curves. The resulting fill surface must pass by the passing curves,
   * but the passing curves do not belong to the resulting topology. In particular, a passing curve
   * is not a boundary of the fill surface.  
   * @param iListOfWires
   * The list of bodies (wires) representing the passing curves.
  */
  virtual void SetPassingCurves(CATLISTP(CATBody) const &iListOfWires) = 0;

  /** 
   * Sets a list of passing points. The fill result must pass through these points.   
   * @param iListOfVertices  
   * The list of pointers to vertex bodies representing the passing points.  
   */
  virtual void SetPassingPoints(CATLISTP(CATBody) const &iListOfVertices) = 0;

  /**
	 * Defines the continuity criterion to use for a given wire.
	 * @param iWhichWire
	 * The index (beginning at 1) of the input wire.
	 * @param iTransitionContinuity
	 * The continuity criterion.
	 * <br><b>Legal values</b>: <tt>0</tt> for G0 continuity (default mode), <tt>1</tt> for G1 continuity,
	 * or <tt>2</tt> for G2 continuity.
	 */
  virtual void SetTransitionContinuity(
    const CATLONG32 iWhichWire,
    const CATLONG32 iTransitionContinuity) = 0;

  /**
   * Defines the orientation of the fill face. 
   * The fill face is oriented according to the orientation of the first
   * edge in the first wire. 
   */
  virtual void OrientationByFirstEdge() = 0;

  /**
 * Activates the flat face mode.
 * In this mode, a planar face is created if the hole being filled is flat.
 * @param iMode
 * The flat mode.
 * <br><b>Legal values</b>: 
 * <dl><dt>1</dt><dd> to activate the flat face mode.
 * <dt>0</dt><dd> to deactivate the flat face mode.
 *</dl>
 */
  virtual void SetFlatFaceMode(const CATLONG32 iMode = 1) = 0;

  /**
     * Enables the replacement of the fill surface by a canonical surface when
	 * it is detected that this is valid.
	 * This method is effective only over rectangular regions, and supports
	 * replacement by cylinders, spheres, and cones only.
   */
  virtual void SetCanonicalDetection() = 0;

  //=============
  //  Get Methods  
  //=============
  /**
 * Returns the maximum continuity gap in the result. 
 */
  virtual double GetG0MaxDeviation() = 0;

  /**
 * Returns the maximum tangency gap (in radians) in the result.
 */
  virtual CATAngle GetG1MaxDeviation() = 0;

  /**
 * Returns the maximum curvature gap in the result.
 */
  virtual double GetG2MaxDeviation() = 0;

  /**
* Returns the maximum continuity gap with regard to a particular edge. 
* If ioMaxPoint is not null, then it will be filled with the coordinates
* where the maximum has been reached.
*/
  virtual double GetG0MaxDeviation(
    const CATEdge *iEdge,
    CATMathPoint *ioMaxPoint = NULL) = 0;

  /**
* Returns the maximum tangency gap (in radians) with regard to a particular edge.
* If ioMaxPoint is not null, then it will be filled with the coordinates
* where the maximum has been reached.
*/
  virtual CATAngle GetG1MaxDeviation(
    const CATEdge *iEdge,
    CATMathPoint *ioMaxPoint = NULL) = 0;

  /**
* Returns the maximum curvature gap with regard to a particular edge.
* If ioMaxPoint is not null, then it will be filled with the coordinates
* where the maximum has been reached.
*/
  virtual double GetG2MaxDeviation(
    const CATEdge *iEdge,
    CATMathPoint *ioMaxPoint = NULL) = 0;

  /**
* Returns the maximum admissible continuity gap in the result.
* This value is computed by taking into account some incompatibilities in the input model.
* Hence, it can be larger than the factory resolution.
*/
  virtual double GetG0MaxAccuracy() = 0;

  /**
* Returns the maximum admissible tangency gap (in radians) in the result.
* This value is computed by taking into account some incompatibilities in the model.
*/
  virtual double GetG1MaxAccuracy() = 0;

  /**
  * Asks for a lay down of each input wire on the corresponding support.
  * If this method is not called, the wire is presumed to be already laid down on its support.
  * @param iLayDownTolerance
  * The pointer to the lay down tolerance (maximum distance between wire to be laid down
  * and its support surface).
   */
  virtual void SetLayDownRequest(const double iLayDownTolerance) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPowerFill(); // -> delete can't be called
};

/**
 * Creates a topological operator that fills a closed area defined by a set of wires.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iListOfWires
 * The list of pointers to the wire bodies, each containing only one wire. 
 * The set of wires must define a closed area and be connected. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATIPGMTopologicalFill
 */
ExportedByCATGMOperatorsInterfaces CATIPGMPowerFill *CATPGMCreatePowerFill(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATBody) const &iListOfWires);

/**
 * Creates a topological operator that fills a closed area defined by a set of wires.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iListOfWires
 * The list of pointers to the wire bodies, each containing only one wire. 
 * The set of wires must define a closed area and be connected.
 * @param iListOfSupports
 * The list of pointers to the supporting bodies of the wires, thus allowing you to define G1 or G2 continuity
 * criteria. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMPowerFill *CATPGMCreatePowerFill(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATBody) const &iListOfWires,
  CATLISTP(CATBody) const &iListOfSupports);

#endif /* CATIPGMPowerFill_h_ */
