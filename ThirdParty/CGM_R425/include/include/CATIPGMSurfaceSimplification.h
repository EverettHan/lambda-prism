#ifndef CATIPGMSurfaceSimplification_h_
#define CATIPGMSurfaceSimplification_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATListOfDouble.h"
#include "CATLISTV_CATMathPoint.h"

class CATBody;
class CATCGMProgressBar;
class CATFace;
class CATGeoFactory;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSurfaceSimplification;

/**
 * Class defining the operator that simplifies an input body by replacing N sets of connected faces.  
 * Each set is replaced by a single face.
 * The input body must be a shell. 
 * The result is a body composed with the N simplified faces and the not impacted faces of input body. 
 *<ul>
 * <li>A CATIPGMSurfaceSimplification operator is created with the <tt>CATIPGMSurfaceSimplification(</tt> global method:
 * It must be directly <tt>delete</tt>d after use. It is not streamable. 
 *<li>Options can be precised, before asking for the computation with the <tt>Run</tt> method. 
 *<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSurfaceSimplification: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSurfaceSimplification();

  /**
	 * @param FaceImpacted 
	 * A set of connected faces of input body impacted by simplification.
	 * This method can be called several times for each set of connected faces. 
	 * If AddImpactedFaces is not called, the operator simplifies all faces of input body
	 */
  virtual int AddImpactedFaces(CATLISTP(CATFace) &FacesImpacted) = 0;

  /**
   *  Activation of constraints Level G0 or G1.
   *
   *  iConstraintsLevel=0 : only G0 constraints are loaded. Maximum G0 tolerance iMaxG0
   *  set in method SetMaxBoundDeviation  must be respected on the result.  
   *  If iMaxG0 is not set, default value used is 0.001mm. 
   *
   *  iConstraintsLevel=1 : G0 constraints and G1 constraints are loaded. Maximum G0 tolerance iMaxG0 
   *  and maximum G1 tolerance iMaxG1 set in method SetMaxBoundDeviation must be respected on the result. 
   *  If iMaxG0 or  iMaxG1 are not set default values are 0.001mm and 0.5 degree.
   *  
   *  Even if only G0 constraints are loaded, a maximum G1 deviation is computed on the result.  
   *  Often imposing only G0 constraints is sufficient to reach G1 max deviation but not guaranteed.  
   *  Of course imposing G1 constraints increases computation time. 
   *  
   *  if method SetConstraintsLevel is not called or if iConstraintsLevel is not 0 or 1, G0 constraints are loaded. 
   **/
  virtual void SetConstraintsLevel(const int iConstraintsLevel = 0) = 0;

  /**
   *    User's G0 and G1 Deviations on bounds   
   *    if method SetMaxBoundDeviation is not called, default tolerances are used:
   *    iMaxG0=0.001mm and iMaxG1=0.5 degree . 
   */
  virtual void SetMaxBoundDeviation(
    const double iMaxG0 = 0.001,
    const double iMaxG1 = 0.5) = 0;

  /**
   *   User's  internal deviation 
   */
  virtual void SetMaxInnerDeviation(const double iMaxDev) = 0;

 /**
   * if possible a global simplification is done
   * if there is only a body and no set of faces a global simplification is done on the body
   * => if no simplification is possible , a NULL result is given.
   * if there are sets of faces,  first a global simplification is done on each set and also on the complementary body. 
   * After that the behavior of CATIPGMSurfaceSimplification still remains the same on the sets to simplify. 
   */
    virtual void SetGlobalMode()=0;

 /**
   * if possible only a simplification using CATIPGMTopSimplify is done.
   * if there is only a body and no set of faces  TopSimplify is done on the whole body
   * => if no simplification is possible , a NULL result and a warning are given. 
   * if there is one ore more sets of faces,  TopSimplify is done on each set and the complementary body is not simplified =>
   * if any set can't be simplified a NULL result and a warning on each set are returned. 
   * If a least one of the sets can be simplified (totally or partially ) a result is returned and a warning on each set 
   * which could not be simplified is returned.  
   */ 
    virtual void SetOnlyTopSimplifyMode()=0;

 /**
   *  if this method is set the result is given  only if the required precision is reached. 
   */ 
	virtual void SetResultWithReachedPrecision()=0;

  /**
   * SetOnlyPlanarDectionContext
   * This fundamentally changes the behaviour of the operator.
   * In this context, only the detection of the  planes will be operated.
   * If a Set is reached to the Plane according to the user's deviation parameters it will be replaced by a CATPlane
   * if not no simplification will be done.
   * @SetOnlyTopSimplifyMode and  @SetGlobalMode are inhibited by this context. 
   */
  virtual void SetOnlyPlanarDectionContext() = 0;

  /**
	* Run method
  * 
	* returns 0  : No Problem 
	* returns 1  : Null Pointer 
	* CATTopOpInError The simplification is not done  because the input body is not a shell
	* returns -1 : There is a warning concerning one or more sets
	* If one (or more)  set is not simplified , a corresponding warning is displayed and also the set.
	* The warnings are the following:
	*   The simplification is not done or is partial  because all or some impacted faces do not belong to input body .
	*   The simplification is not done or is partial  because some impacted sets have not connected faces.
	*   The simplification is not done or is partial  because all or some impacted  sets have only one face.
	*   The simplification is not done or is partial  because some impacted sets have internal boundary.
	*   The simplification is not done or is partial  because some impacted sets  have sharp edges
	*   The simplification is not done or is partial  because all or some impacted elements  are not faces
	*   The simplification is not done or is partial  because all or some impacted sets have common faces
  */
  // virtual int  Run()=0 
  /**
	* Maximum G0 deviation on bounds  
  */
  virtual double GetMaxBoundG0Deviation() const = 0;

  /**
	* Maximum G1 deviation on bounds
  */
  virtual double GetMaxBoundG1Deviation() const = 0;

  /**
	
	* Maximum internal deviation
  */
  virtual double GetMaxInnerDeviation() const = 0;

  /**
	* Maximum G0 deviation on bounds on set iSetNum 
	* The number of sets is defined by the number of calls of method AddImpactedFaces.
	* if AddImpactedFaces is not called , the number of set is equal to 1 
  */
  virtual double GetMaxBoundG0Deviation(const int iSetNum) const = 0;

  /**
	* Maximum G1 deviation on bounds  on set iSetNum
	* The number of sets is defined by the number of calls of method AddImpactedFaces.
	* if AddImpactedFaces is not called , the number of set is equal to 1 
  */
  virtual double GetMaxBoundG1Deviation(const int iSetNum) const = 0;

  /**
	* Maximum internal deviation on set iSetNum  
	* The number of sets is defined by the number of calls of method AddImpactedFaces.
	* if AddImpactedFaces is not called , the number of set is equal to 1 
  */
  virtual double GetMaxInnerDeviation(const int iSetNum) const = 0;

  /**
	* List of points and associated deviations when G0 user's deviation on bounds is not reached on set iSetNum  
	* The number of sets is defined by the number of calls of method AddImpactedFaces.
	* if AddImpactedFaces is not called , the number of set is equal to 1 
    */
  virtual void GetPointsOnG0Error(
    const int iSetNum,
    CATLISTV(CATMathPoint) &ListPointsG0Error,
    CATListOfDouble &ListOfValuesG0Error) const = 0;

	/**
	 * List of points and associated deviations when G1 user's deviation on bounds is not reached on set iSetNum  
	 * The number of sets is defined by the number of calls of method AddImpactedFaces.
	 * if AddImpactedFaces is not called , the number of set is equal to 1 
     */
  virtual void GetPointsOnG1Error(
    const int iSetNum,
    CATLISTV(CATMathPoint) &ListPointsG1Error,
    CATListOfDouble &ListOfValuesG1Error) const = 0;

	/**
	 * List of points and associated deviations when internal user's deviation is not reached on set iSetNum  
	 * The number of sets is defined by the number of calls of method AddImpactedFaces.
	 * if AddImpactedFaces is not called , the number of set is equal to 1 
     */
  virtual void GetPointsOnInnerError(
    const int iSetNum,
    CATLISTV(CATMathPoint) &ListPointsInnerError,
    CATListOfDouble &ListOfValuesInnerError) const = 0;

  /**
	* Set the callback instance for tracking progress and interrupt when the operator runs.
	**/
  virtual void SetCallback(CATCGMProgressBar *ipCallback) = 0;

  /** 
	 * @nodoc internal use.
	 */
  virtual void ActivateSplitIfClosedInOneDir() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSurfaceSimplification(); // -> delete can't be called
};

/**
 * Creates the operator that simplifies an input body by replacing  one set of connected faces  
 * by a single face.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iTopData
 * The pointer to the data defining the configuration.
 * @param iBodyToBeSimplified
 * The pointer to the body to simplify. As the operator follows the smart mechanism, 
 * this input body is not modified. A new one is created, it can be retrieved with 
 * the <tt>GetResult</tt> method.
 * @return [out,IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSurfaceSimplification *CATPGMCreateSurfaceSimplification(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyToBeSimplified);

#endif /* CATIPGMSurfaceSimplification_h_ */
