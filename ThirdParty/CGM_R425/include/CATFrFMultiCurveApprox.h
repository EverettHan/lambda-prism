#ifndef CATFrFMultiCurveApprox_H 
#define CATFrFMultiCurveApprox_H 

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================

#include "Y30Approx.h"
#include "CATCGMOperator.h"
#include "CATSkillValue.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATCrvLimits.h"
#include "CATListOfCATMathCurveFunction.h"
#include "CATListOfDouble.h"
#include "CATCreateFrFMultiCurveApprox.h" //EAB - 27/11/03

class CATGeoFactory;
class CATFrFNurbsMultiForm;
class CATCurve;
class CATCrvLimits;
class CATMathInterval;
class CATMathFunctionX;
class CATCrvParam;
class CATSoftwareConfiguration;

/**
 * Class defining the operator that computes a Nurbs approximation of a set of curves or/and combs.
 * The approximation is global : all the output Nurbs have the same Knot vector.
 * The input curves and combs can be defined as CATCurves or through 3 CATMathFunctionX.
 * The output is a CATFrFNurbsMultiForm.
 *<br>
 * This operator follows the global frame of the geometrical operators.
 * It is not streamable.
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATCreateMultiCurveFitting</tt> global function 
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods 
 * <li>Run it
 * <li>Get the result with the <tt>GetResult</tt> method. 
 * <li>Delete it with the usual C++ <tt>delete</tt> operator after use.
 *</ul>  
 */

//-----------------------------------------------------------------------------
class ExportedByY30Approx CATFrFMultiCurveApprox : public CATCGMOperator
{
public :
	 
	/**
	 * Runs <tt>this</tt> operator.
	 */
	virtual int Run() = 0;

	/**
	* Returns the resulting MultiForm for a given curve.
	* @param iCurveRank
	* The rank (beginning at <tt>1</tt>) of the input curve to consider.
	* @return
    * The pointer to the corresponding Multiform.
	*/
	virtual CATFrFNurbsMultiForm *  GetResult(int iCurveRank) = 0;
	
	/**
	* Defines the reference curve.
	* @param iCurveRank
    * The rank <tt>(1 <=iCurveRank <= NbCurve)</tt> of the curve.
	* The default value for iCurveRank is 1, if one or more CATCurve are in the input.
	*/
	virtual void SetReferenceCurve(int iCurveRank ) = 0;

	/**
	* Returns the maximum deviation between the input curves and the result.
	* @return
    * The maximum deviation value. 
	*/
	virtual double GetMaxDeviation() const= 0;

	/**
	* Returns the maximum deviation for one given curve between the input curve and 
	* the resulting curve.
	* @param iCurveRank
    * The rank <tt>(1 <=iCurveRank <= NbCurve)</tt> of the Curve.
	* @return
    * The maximum deviation value. 
	*/	
	virtual double GetCurveMaxDeviation(int iCurveRank) const = 0;
		
	/**
	* Defines the tolerance for one given curve.
	* @param iTolerance
    * The tolerance for one curve
    * @param iCurveRank
    * The rank <tt>(1 <=iCurveRank <= NbCurve)</tt> of the curve.
	*/   
	virtual void SetTolerance(double iTolerance, int iCurveRank) = 0;
	
	/**
	* Defines the internal min length for one given curve.
	* @param iInternalMinLength
    * The internal min length for one curve
    * @param iCurveRank
    * The rank <tt>(1 <=iCurveRank <= NbCurve)</tt> of the curve.
	*/   
	virtual void SetInternalMinLength(double iInternalMinLength, int iCurveRank) = 0;
	
	/**
	*Defines the internal behaviour for using MinLength.
    * @param iSurfacixMode
    * 0: arcs of each curve must be grater than MinLength
    * 1: At least on one curve, the arc is greather than MinLength
    * @param iCurveRank
    * The rank <tt>(1 <=iCurveRank <= NbCurve)</tt> of the curve.
	*/   
   virtual void SetSurfacicMode(int iSurfacixMode) =0;
	/**
	* Defines the orientation for one given curve.
	* @param iOrientation
    * The orientation for one curve with repect to the reference curve.
    * @param iCurveRank
    * The rank <tt>(1 <=iCurveRank <= NbCurve)</tt> of the curve.
	*/   
	virtual void SetOrientation(CATLONG32 iOrientation, int iCurveRank) = 0;
	
	/**
	* Sets the maximum degree of the resulting MultiForm.
    *
	* @param iMaxDegree
    * The maximum degree for the Multiform.
	* It is equal to the maximum degree for conversion, if exact conversion, and equal to 5 otherwise. 
	*/	
	virtual void SetMaxDegree(int iMaxDegree ) = 0;
		
	/**
	* Sets the maximum number of Arcs for the result.
    *
	* @param iMaxArcs
    * The maximum number of Arcs.
	* The default value is 64.
	*/
	virtual void SetMaxArcs(int iMaxArcs ) = 0;
	
	/**
	* @nodoc
    *Set the list of preference cuts, ie the preferred parameters for the arc limits.
    *
	* @param iPreferenceCuts
    * The list of preferred parameters for arc limits.
    * @param iCurveRank
    * The rank (beginning at <tt>1</tt>) of the curve.
	*/
	virtual void SetPreferenceCuts(const CATListOfDouble & iPreferenceCuts, int iCurveRank) = 0;

	/**
	* @nodoc
    *Set the list of Mandatory cuts, ie the Mandatory parameters for the arc limits.
    *
	* @param iMandatoryCuts
    * The list of Mandatory parameters for arc limits.
    * @param iCurveRank
    * The rank (beginning at <tt>1</tt>) of the curve.
	*/
    virtual void SetMandatoryCuts(const CATListOfDouble & iMandatoryCuts, int iCurveRank) = 0;
    
  /**
	* @nodoc
    *Set the internal continuity of the result.
    *The default value is 2.
    *Legal values: 0 (ie the result curves are C0).
    *              1 (ie the result curves are C1).
    *              2 (ie the result curves are C2).
    *
    *Warning: C0 or C1 curves can only be used for internal purpose.
    *         It is illegal to have a persistent non-C2 CATCurve in a
    *         CATIA Model.
    *
    * @param iInternalContinuity
    * The internal continuity of the result.
	*/
	virtual void SetInternalContinuity(CATLONG32 iInternalContinuity) = 0;

  /**
	* Defines the continuity to keep at the extremities.
	* @param iSideContinuity
  * Continuity to keep
  * Legal values: 0 (C0 continuity)
  *               1 (C1 continuity)
  *               2 (C2 continuity)
  */
  virtual void SetSideContinuity(int iSideContinuity) = 0;

  /**
	* Defines the continuity to keep at the extremities.
	* @param iSideContinuityLeft
  * Continuity to keep at the left extremity
	* @param iSideContinuityRight
  * Continuity to keep at the right extremity
  * Legal values: 0 (C0 continuity)
  *               1 (C1 continuity)
  *               2 (C2 continuity)
  */
  virtual void SetSideContinuity(int iSideContinuityLeft, int iSideContinuityRight) = 0;


  virtual ~CATFrFMultiCurveApprox();

	
  protected :
	  
	  CATFrFMultiCurveApprox(CATGeoFactory *iFactory);
	  
  private :
	  
CATFrFMultiCurveApprox();
CATFrFMultiCurveApprox(const CATFrFMultiCurveApprox &);
void operator = (const CATFrFMultiCurveApprox &);

	  
};

#endif



