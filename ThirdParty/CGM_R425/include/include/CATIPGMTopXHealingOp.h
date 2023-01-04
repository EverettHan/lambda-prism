#ifndef CATIPGMTopXHealingOp_h_
#define CATIPGMTopXHealingOp_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "ListPOfCATFace.h"

class CATBody;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopXHealingOp;

/**
* Class defining the Healing operator on body imported from other modeling system into NCGM format.
*<br>
* The CATTopXHealing operator follows the global frame of the topological operators 
* and satisfies the smart mechanism: the input bodies are not modified. A new resulting body 
* is created, possibly sharing data with the input body.
* The Healing operator failed in case of non-manifold topology detected.
*<ul>
* <li>A CATTopXHealing operator is created with the <tt>CATCreateTopXHealing</tt> global function:
* It must be directly deleted after use with the usual C++ <tt>delete</tt> operator. It is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. These methods define the healing strategy.
*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory. 
*</ul>
* @see CATCreateTopXHealing
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopXHealingOp: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopXHealingOp();

  /**
	* SetOperatorMode
	* <br><b>Defines the operator mode
	* @param iMode
	* @See CATTopXHealingMode for Legal values
	*/
  virtual void SetMode(const int iMode) = 0;

  /**
	* SetShapeMaxDeformation
	* <br><b>Defines the maximum value of shape deformation allowed. 
	* @param iMaxShapeDeformation
	*/
  virtual void SetMaxShapeDeformation(const double iMaxShapeDeformation) = 0;

  /**
	* SetMinOffSetValue
	* <br><b>Defines the minimum offset value for each face in Input. 
	* All faces whose the curvature radius is less than this value will be regularized.
	* @param iMinOffsetValue
	* Minimum offset value of the result. Its absolute value must be 
	* greater than factory resolution.
	*/
  virtual void SetMinOffSetValue(const double iMinOffsetValue) = 0;

  /**
	* AddSetOfFaces
	* <br><b>To set a set of faces to merge </b>
	* <br>The faces must be G1 connected open shell. Simplify mode must be activated before
	* @param ilFaces
	* The list of faces for this set
	* @return
	* <br><b>Legal values</b>:
	* <dl><dt><tt>0</tt><dd> for success
	*     <dt><tt>non zero </tt><dd> for failure</dl>
	* 
	*/
  virtual int AddSetOfFaces(CATLISTP(CATFace) &ilFaces) = 0;

  /** @name Deprecated Member Functions
    Do not use any of these methods.  They are not supported.
    @{ */
  /**
	* SetG0GapTolerance
	* <br><b>Defines the global default for the G0 continuity tolerance required after Healing.</b>: 
	* @param iTolG0
	* The G0 continuity tolerance. Its value must be between factory resolution and 
	* 100 times of this. The default value is  10 times of the factory resolution
	* @return
	* 
	*/
  virtual void SetG0GapTolerance(const double iTolG0) = 0;

  //------------------------------------------------------------------------------------
  // O P T I O N S 
  //------------------------------------------------------------------------------------
  /**
	* SetSimplifyMode
	* <br><b>Activates the simplification mode</b>
	* <br>if Activates, the operator replaces a set of N connected g1 faces (a shell ) by single face.
	* In this mode, topology is modified. Several set can be done. By default it's desactivated.
	* @param iActivate
	* <br><b>Legal values</b>:
	* <dl><dt><tt>TRUE</tt><dd> To activate simplification mode
	*     <dt><tt>FALSE</tt><dd> To desactivate simplification mode. Default behaviour.</dl>	
	* @param iMaxDeviationAllowed
	* Maximum deviation allowed. It must greater than the resolution.
	* @param iSimplifyBoundaries
	* Activate, the operator replaces any subset of connected G1 boundary edges by a single one.
	* <br><b>Legal values</b>:
	* <dl><dt><tt>TRUE</tt><dd> To activate . Default behaviour.
	*     <dt><tt>FALSE</tt><dd> To desactivate</dl>
	* @return
	* 
	*/
  virtual void SetSimplifyMode(
    const CATBoolean iActivate,
    const double iMaxDeviationAllowed,
    const CATBoolean iSimplifyBoundaries = TRUE) = 0;

  /**
	* SetRegularizationMode
	* <br><b>Activates the regularizatiom mode</b>
	* <br> if Activates, the operator replaces one face by one or two faces to improve
	* its quality (twist, offset ..). In this mode, topology is modified.. Several cells can be done.	
	* @param iActivate
	* <br><b>Legal values</b>:
	* <dl><dt><tt>TRUE</tt><dd> To activate Regularization mode
	*     <dt><tt>FALSE</tt><dd> To desactivate Regularization mode. Default behaviour.</dl>
	* @param iMaxDeviationAllowed
	* Maximum deviation allowed. It must greater than the resolution.
	* @param iMinOffsetValue
	* Minimum offset value of the result.
	* @return
	* 
	*/
  virtual void SetRegulMode(
    const CATBoolean iActivate,
    const double iMaxDeviationAllowed,
    const double iMinOffsetValue) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopXHealingOp(); // -> delete can't be called
};

/**
* Creates a CATTopXHealing operator.
* @param ipFactory
* The factory of the geometry. 
* @param ipTopData
* @param ipBodyToHeal
* The pointer to the body to heal.
* @param iMode
* Defines the operator mode. 
* The behaviour can be changed by calling the method @SetMode.
* @See CATTopXHealingMode for Legal values
* @return
* The pointer to the created operator. 
* To delete after use with the usual C++ <tt>delete</tt> operator.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopXHealingOp *CATPGMCreateTopXHealing(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *ipBodyToHeal,
  const int iMode);

/**  Deprecated Member Functions
* Do not use. Willbe deleted
* Creates a CATTopXHealing operator.
* @param ipFactory
* The factory of the geometry. 
* @param ipTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param ipBodyToHeal
* The pointer to the body to heal.
* @return
* The pointer to the created operator. To delete after use with the usual C++ <tt>delete</tt> operator.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopXHealingOp *CATPGMCreateTopXHealing(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *ipBodyToHeal);

#endif /* CATIPGMTopXHealingOp_h_ */
