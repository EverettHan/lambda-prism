#ifndef CATICGMTopologicalFillLight_h_
#define CATICGMTopologicalFillLight_h_

// COPYRIGHT DASSAULT SYSTEMES 2008

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATTopologicalFillType.h"
#include "CATMathDef.h"

class CATEdge;
class CATMathPoint;
class CATShell;
class CATVertex;
class CATTopData;
class CATLISTP(CATFace);
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopologicalFill;

/**
* Class defining the topological operator that fills a space defined by a set of wires.
* <br> The wires must define a closed area.
* Continuity criteria can be precised: G0, G1 if the supporting surfaces of the wire
* are given, G0 otherwise. The supporting surfaces must be coherent to allow the operator to
* compute a G1 continuity.
* <br>The CATICGMTopologicalFill operator creates the resulting filling skin body
* separately from the inputs: the wires of the input bodies are not used to define the topology
* of the resulting fill body.  
*<ul>
* <li>A CATCGMTopologicalFill operator is created with the <tt>CATCGMCreateTopologicalFill</tt> global function.
* It must be directly released with the <tt>Release</tt> method. It is is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory. Although several sucessive 
* <tt>Run</tt>s with different inputs
* are possible, it is strongly recommended to <tt>Run</tt> it only once.
* <li>The journal corresponding to the fill operation is not yet implemented.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopologicalFill: public CATICGMTopOperator
{
public:

 /**
  * Constructor
  */
  CATICGMTopologicalFill();

 /**
  * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
  * <br>It is possible to <tt>Run</tt> the operator several times,
  * with different parameters. After each <tt>Run</tt>, a new body is created.
  */
  virtual int Run() = 0;

 /**
  * Returns the maximum continuity gap on the result. 
  * @return
  * The value of maximum continuity gap.   
  */
  virtual double GetG0MaxDeviation() = 0;

 /**
  * Returns the maximum tangency gap (in radians) on the result.
  * @return
  * The value in radians of maximum tangency gap.  
  */
  virtual CATAngle GetG1MaxDeviation() = 0;

 /**
  * Returns the maximum admissible continuity gap on the result.
  * <br> This value is computed by taking into account some incompatibilities in the input model. 
  * Hence, it can be larger than the factory resolution.
  * @return
  * The value of maximum admissible continuity gap.  
  */
  virtual double GetG0MaxAccuracy() = 0;

 /**
  * Returns the result of <tt>this</tt> operator.
  * @return
  * The pointer to the created body. You must delete it with the @href CATICGMContainer#Remove 
  * method if you do not want to keep it. Note: in case of multiple <tt>Run</tt>s, the operator
  * deletes the intermediate bodies.
  */
  virtual CATBody *GetResult() = 0;

 /**
  * Checks whether holes must be detected in the input wires (<tt>ADVANCED mode</tt>).
  * @param iMode
  * The validation mode.
  * <br><b>Legal values</b>: 
  * <dl><dt><tt>1</tt></dt><dd> to check the inputs.
  *     <dt><tt>0</tt></dt><dd> no check (default mode). </dl>
  */
  virtual void SetInputValidationMode(const CATLONG32 iMode = 1) = 0;

 /**
  * Defines the continuity criteria to take into account for a given wire (<tt>ADVANCED mode</tt>).
  * @param iWhichWire
  * The rank (beginning at 1) of the input wire.
  * @param iTransitionContinuity
  * The continuity criteria
  * <br><b>Legal values</b>: 
  * <dl><dt><tt>0</tt></dt><dd> for G0 continuity (default mode).
  *     <dt><tt>1</tt></dt><dd> for G1 continuity. </dl>
  */
  virtual void SetTransitionContinuity(
    const CATLONG32 iWhichWire,
    const CATLONG32 iTransitionContinuity) = 0;
 
  /**
  * Returns the center point inside the hole to fill.
  * <br>The fill algorithm fills the hole with four sided faces. In case of not four sided input holes,
  * the algorithm defines a center point allowing it to create four sided faces. This point can also
  * be defined by the <tt>SetCenterPoint</tt> method (<tt>ADVANCED mode</tt>).
  * @param ioCenterPoint
  * The vertex representing the center point.
  */
  virtual void GetCenterPoint(CATVertex &ioCenterPoint) = 0;

 /**
  * Defines the center point inside the hole to fill (<tt>ADVANCED mode</tt>).
  * <br>The fill algorithm fills the hole with four sided faces. In case of not four sided input holes,
  * this method defines a center point allowing the algorithm to create four sided faces. 
  * @param iCenterPoint
  * The vertex representing the center point.
  */
  virtual void SetCenterPoint(CATVertex &iCenterPoint) = 0;

 /**
  * Removes the defined center point.
  * The algorithm defines the default center point.
  */
  virtual void ResetCenterPoint() = 0;

 /**
  * Activates the flat face mode.
  * @param iMode
  * The flat mode.
  * <br><b>Legal values</b>: 
  * <dl><dt>1</dt><dd> to activate the flat face mode: in this case, it creates a planar face if the hole
  * to fill is flat.
  * <dt>0</dt><dd> to deactivate the flat face mode: this is the default mode.
  *</dl>
  */
  virtual void SetFlatFaceMode(const CATLONG32 iMode = 1) = 0;

 /**
  * Checks the computation.
  * @return
  * <tt>0</tt> if the computation occured without problem.
  */
  virtual CATLONG32 Check() = 0;

 /**
 * Returns the fill type.
 * @return
 * The fill type.
 * <br>Useful in automatic mode to know which solution was chosen.
 */
  virtual CATTopologicalFillType GetFillType() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopologicalFill(); // -> delete can't be called
};

#endif /* CATICGMTopologicalFillLight_h_ */
