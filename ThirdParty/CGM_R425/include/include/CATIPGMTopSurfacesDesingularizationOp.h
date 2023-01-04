#ifndef CATIPGMTopSurfacesDesingularizationOp_h_
#define CATIPGMTopSurfacesDesingularizationOp_h_

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATFace;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopSurfacesDesingularizationOp;

/**
* Class defining an operator of surfaces desingularization of a body .
*<br>
* This operator retrieves all none conic singular faces and replaces them by  none singular surfaces 
*<br>
* The CATIPGMTopSurfacesDesingularizationOp operator follows the global frame of the topological operators 
* and satisfies the smart mechanism: the input bodies are not modified. A new resulting body 
* is created, possibly sharing data with the input body.
* The Healing operator failed in case of non-manifold topology detected.
*<ul>
* <li>A CATIPGMTopSurfacesDesingularizationOp operator is created with the <tt>CATPGMCreateTopSurfacesDesingularizationOp</tt> global function:
* It must be directly deleted after use with the usual C++ <tt>delete</tt> operator. It is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. These methods define the healing strategy.
*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory. 
*</ul>
* @see CATPGMCreateTopSurfacesDesingularizationOp
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopSurfacesDesingularizationOp: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopSurfacesDesingularizationOp();

  /**
	* SetTolerance
	* <br><b>Defines the deviation allowed between the result and the input.</b>: 
	* @param iMaxDeviationAllowed
	* The maximum allowed deviation. Its value must be greater or equal than the factory resolution. 
	* The default value is  10 times of the factory resolution
	*/
  virtual void SetDeviationAllowed(const double iMaxDeviationAllowed) = 0;

  /**
	* SetRatioOfReachPoints
	* <br><b>Defines the minimum rate of the coverage of each regularized surface in deviation term..
	* @param iRatio
	*/
  virtual void SetRatioOfReachPoints(const double iRatio = 0.9999) = 0;

  /*
	* <br><b>SetFaces</b>
	* <br>To Set Degenerated Face to regularize
	* @param ipFaceToRegularize : 
	* The face to regularize.
	* @return	
	*	<ul>
	*	<li><tt>-1</tt>: if this face is duplicated, or out of scope or it's not belong the body.
	*	<li><tt> 0</tt>: on success
	*	<li><tt> 1</tt>: On faillure (internal)
	*	</ul>
	*/
  virtual int SetFace(CATFace *ipFaceToRegularize) = 0;

  /*
	* <br><b>GetFaceDiag</b>
	* <br>To retrieve the diagnostics relate to a CATFace To regularize.
	* @param ipFaceToRegularize 
	* The face to regularize.
	* @param oDiag 
	* the status relate to this face. Legacy Values
	* <br><b>Legal values:</b>
	*	<ul>
	*   <li><tt>-2</tt>:  internal error
	*	<li><tt>-1</tt>: the ipFaceToRegularize is not a target of this operation ( may be see rc of @SetFace) 
	*	<li><tt> 0</tt>: the regularization has done and has a result
	*	<li><tt> 1</tt>: the regularization has done and has failed
	*	</ul>
	* @param oMaxG0Deviation 
	*  has sense only if oDiag!= 0
	* @param oMaxG1Deviation 
	*  has sense only if oDiag!= 0
	* @param oMaxInnerDeviation 
	*  Maximum deviation inside the result. see @SetDeviationAllowed. has sense only if oDiag!= 0
	* @return
	*   The image of ipFaceToRegularize belonging to the result body
	* <br><b> According to @oDiag:</b>
	*	<ul>
	*   <li><tt>Negative</tt>:  It' NULL
	*	<li><tt> 0 </tt>: It's the result of @ipFaceToRegularize
	*	<li><tt> 1 </tt>: It could be @ipFaceToRegularize itself or its image from a smart duplication.
	*	</ul>
	*/
  virtual CATFace *GetFaceDiag(
    CATFace *ipFaceToRegularize,
    int &oDiag,
    double &oMaxG0Deviation,
    double &oMaxG1Deviation,
    double &oMaxInnerDeviation) = 0;

  /**
	* GetMaxBoundG0Deviation
	* <br><b> Returns maximum G0 deviation on bounds of input.
	*/
  virtual double GetMaxBoundG0Deviation() const = 0;

  /**
	* GetMaxBoundG1Deviation
	* <br><b> Returns maximum G1 deviation on bounds of input
	*/
  virtual double GetMaxBoundG1Deviation() const = 0;

  /**
	* GetMaxInnerDeviation
	* <br><b> Returns maximum internal deviation of input
	*/
  virtual double GetMaxInnerDeviation() const = 0;

  /**
	* GetNumberOfAllSingularFaces
	* <br><b> Returns the number of all found singular faces
	*/
  virtual int GetNumberOfAllSingularFaces() const = 0;

  /**
	* GetNumberOfTreatedFaces
	* <br><b> Returns number of treated faces
	*/
  virtual int GetNumberOfTreatedFaces() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopSurfacesDesingularizationOp(); // -> delete can't be called
};

/**
* Creates a CATIPGMTopSurfacesDesingularizationOp operator.
* @param ipFactory
* The factory of the geometry. 
* @param ipTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param ipBody
* The pointer to the body to regularize.
* @return
* The pointer to the created operator. To delete after use with the usual C++ <tt>delete</tt> operator.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopSurfacesDesingularizationOp *CATPGMCreateTopSurfacesDesingularizationOp(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *ipBody);

#endif /* CATIPGMTopSurfacesDesingularizationOp_h_ */
