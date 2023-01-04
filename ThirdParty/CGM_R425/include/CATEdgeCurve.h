#ifndef CATEdgeCurve_h
#define CATEdgeCurve_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATCurve.h"
#include "CATMathDef.h"
#include "CATGeoDef.h"
#include "CATIACGMLevel.h"


class CATSurface ;
class CATPCurve ;
class CATMathFunctionX ;
class CATMapX;
class CATCX_CHECKUP;
class CATPointOnEdgeCurve;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATEdgeCurve ;
#else
extern "C" const IID IID_CATEdgeCurve ;
#endif

/**
 * Interface defining a curve representing several other curves.
 * <b>Role</b>: A CATEdgeCurve is the geometry of a topological edge. As an edge can
 * bound several faces (with different geometry), 
 * a CATEdgeCurve is a curve that presents a common behavior for
 * several curves. 
 * <br>The aggregation of the CATPCurves resulting of an intersection 
 * leads to a CATIntCurve, the aggregation of identical CATCurves 
 * leads to a CATSimCurve and the aggregation of CATCurves with different limits 
 * or parameterizations leads to a 
 * CATMergedCurve. To create a CATMergedCurve, use the @href CATEdgeCurveComputation operator.
 *<br>The aggregation is a recursive notion, and you can aggregate
 * CATEdgeCurves.
 *<br>One aggregated curve plays a special role: its manages the evaluations and is called the reference curve.
 */
class ExportedByCATGMGeometricInterfaces CATEdgeCurve : public CATCurve
{
  CATDeclareInterface;

public:
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
  * Scans the CATCurves represented by <tt>this</tt> CATEdgeCurve.
  * @param iCurrentSubElement
  * The pointer to the CATCurve from which the search is initialized, may
  * be <tt>NULL</tt> for retrieving the first CATCurve.
  * @return
  * The pointer to the next CATCurve of the aggregation. Remember that a 
  * CATEdgeCurve is also a CATCurve.
  *<br><b>Sample</b>: Search of all CATCurves of a CATEdgeCurve.
  *<pre> 
  * const CATCurve * Current=NULL
  * while (Current = MyEdgeCurve->Next(Current) ) 
  *  { ... process Current ... }
  *</pre>
  */
  virtual const CATCurve* Next ( const CATCurve *iCurrentSubElement ) const = 0 ;

/**
 * @nodoc
 * @deprecated V5R12 CATEdgeCurveIterator
 * Recursively scans the CATCurves of <tt>this</tt> CATEdgeCurve, without returning
 * the imbedded CATEdgeCurves.
 * @param iCurrentSubElement
 * The pointer to the CATCurve from which the search is initialized, may
 * be <tt>NULL</tt> for retrieving the first CATCurve.
 * @return
 * The pointer to the next CATCurve (not being a CATEdgeCurve) of the aggregation.
 */
  virtual const CATCurve* NextThru ( const CATCurve *iCurrentSubElement ) const = 0 ;

/**
 * Returns the parameter on <tt>this</tt> EdgeCurve corresponding to the point defined by
 * parameters on its components.
 * @param iNbOfCurves
 * The number of CATCurves.
 * @param iCurves[]
 * The array of <tt>iNbOfCurves</tt> CATCurve pointers.
 * @param iParams[]
 * The corresponding parameters on the CATCurves.
 * @param ioCalcParam
 * The parameter of the point on <tt>this</tt> CATEdgeCurve.
 */
  virtual void GetEquivalentParam( const CATLONG32 iNbOfCurves, 
						      const CATCurve*     iCurves[],
						      const CATCrvParam   iParams[],
						      CATCrvParam&        ioCalcParam) const = 0 ; 

  
	/**
	 * The confusion diagnosis of a point on an CATEdgeCurve.
	 * @param Equal
	 * Same geometrical points with same parameter.
	 * @param Similar 
	 * Same geometrical points with different parameters.
	 * @param Distinct
	 * Distinct geometrical points.
	 */
	enum CATCompareDiagnostic { Equal, Similar, Distinct } ;

/**
 * Checks whether points can be merged within the same CATPointOnEdgeCurve.
 * @param iNbOfCurves
 * The number of CATCurves.
 * @param iCurves[]
 * The array of <tt>iNbOfCurves</tt> CATCurve pointers.
 * @param iParams[]
 * The corresponding parameters of the points to merge.
 * @param ioSuggestedParam
 * The parameter of the corresponding point on <tt>this</tt> CATEdgeCurve.
 * @param ioGap
 * The maximum distance between the points. If <tt>NULL</tt>, this distance is not output.
 * @return
 * The diagnosis of confusion.
 */
  virtual CATEdgeCurve::CATCompareDiagnostic Compare( const CATLONG32 iNbOfCurves, 
						      const CATCurve*     iCurves[],
						      const CATCrvParam   iParams[],
						      CATCrvParam & ioSuggestedParam,
						      CATPositiveLength* ioGap = NULL) const = 0 ; 

/** 
 * Reports a point from a curve to another one.
 * @param iParamOnCurrentCurve
 * The parameter on <tt>iCurrentCurveOrEdgeCurve</tt>.
 * @param iCurrentCurveOrEdgeCurve
 * The initial CATCurve.
 * @param iEquivalentCurve
 * The CATCurve on which the point is to be expressed.
 * @param ioParamOnEquivalentCurve
 * The equivalent parameter on <tt>iEquivalentCurve</tt>.
 * @param iConverge
 * The type of computation.
 * <br><b>Legal values</b>:
 * <dl><dt>1</dt><dd>An exact computation.
 * <dt>0</dt><dd>An approximated (and faster) computation.</dl>
 */
  virtual void GetEquivalentPoint ( const CATCrvParam &iParamOnCurrentCurve,
				    const CATCurve    *iCurrentCurveOrEdgeCurve,
				    const CATCurve    *iEquivalentCurve, 
				      CATCrvParam     &ioParamOnEquivalentCurve,
              short           iConverge=1) const  = 0 ;

 
/**
 * Retrieves the parametric orientation of a CATCurve with regards to the 
 * orientation of <tt>this</tt> CATEdgeCurve.
 * @param iCurrentCurve
 * A pointer to a curve of <tt>this</tt> CATEdgeCurve.
 * @return
 * The relative orientation
 *<dl> <dt> 1 <dd> <tt>this</tt> and <tt>iCurrentCurve</tt> have the same orientation.
 *     <dt> -1 <dd> <tt>this</tt> and <tt>iCurrentCurve</tt> have an opposite orientation.</dl>  
 */
  virtual short GetRelativeOrientation( const CATCurve *iCurrentCurve ) const = 0 ;

// The gap is computed (for a CATMergedCurve) or specified (for a CATSimCurve) at the CATEdgeCurve creation.
  /**
  * Returns a length larger than the distance between any couple of corresponding evaluated 
  * points on all subcurves.
  * @return
  * The gap between the curves.
  * If the gap is 0., @href CATCurve#EvalPoint returns the same value whatever the subcurve 
  * it applies to.
  * The gap of an CATIntCurve is always 0., because the evaluators always return an exact value in this case.
  * However, the equation of a CATIntCurve may not return an exact solution.
  */
  virtual CATPositiveLength GetMaxGap() const = 0 ;

/**
  * Returns the reference curve of <tt>this</tt> CATEdgeCurve.
	* <br> The reference curve manages the evaluations.
	* @return
	* A pointer to the curve of <tt>this</tt> CATEdgeCurve. 
  */  
  virtual CATCurve* GetRefCurve() const = 0;


/**
  * Retrieves the sharpness between the underlying surfaces of two CATPCurves.
	* @param iC1
	* A pointer to the first CATPCurve.
	* @param iC2
	* A pointer to the second CATPCurve. 
	* @param ioContinuity
	* The tangential continuity.
	* @param ioConvexity
	* The tangential convexity. If <tt>NULL</tt>, this argument is not written.
  */
  virtual short GetSharpness ( 
              const CATPCurve   *iC1,
              const CATPCurve   *iC2,
              CATGeoContinuity  *ioContinuity,
              CATGeoConvexity   *ioConvexity=0) const = 0;

/**
  * Imposes the sharpness between the underlying surfaces of two CATPCurves.
	* @param iC1
	* A pointer to the first CATPCurve.
	* @param iC2
	* A pointer to the second CATPCurve. 
	* @param iContinuity
	* The tangential continuity to impose.
	* @param iConvexity
	* The tangential convexity to impose. 
  */
  virtual void SetSharpness (
              const CATPCurve*                  iC1,
              const CATPCurve*                  iC2,
              const CATGeoContinuity            iContinuity,
              const CATGeoConvexity             iConvexity = CATUnknownConvexity) = 0;









  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * @nodoc
 * Use a CATEdgeCurveIterator.
 * Scans the CATPCurves of <tt>this</tt> CATEdgeCurve lying on a given CATSurface.
 *<br>This scan is recursive in order to find all the CATPCurves lying on
 * the surface.
 * @param iCurrentSubElement
 * The pointer to the CATPCurve from which the search is initialized, may
 * be <tt>NULL</tt> for retrieving the first CATPCurve.
 * @return
 * The pointer to the next CATPCurve of the aggregation.
 */
  virtual const CATPCurve* NextOnSupport ( const CATCurve *iCurrentSubElement, 
					   const CATSurface* iSupport          ) const = 0 ;



///////////////////////////////////////////////////////////////////////////////
//                      Methods that will disappear
///////////////////////////////////////////////////////////////////////////////
/** 
 * @nodoc
 * Reports a point from a curve to another one.
 * @param iParamOnCurrentCurve
 * The parameter on <tt>iCurrentCurveOrEdgeCurve</tt>.
 * @param iCurrentCurveOrEdgeCurve
 * The initial CATCurve.
 * @param iEquivalentCurve
 * The CATCurve with which parameters the point is to be expressed.
 * @return
 * The equivalent parameter on <tt>iEquivalentCurve</tt>.
 */
  virtual CATCrvParam GetEquivalentPoint ( const CATCrvParam &iParamOnCurrentCurve,
					   const CATCurve    *iCurrentCurveOrEdgeCurve,
	 				   const CATCurve    *iEquivalentCurve,
             const short        iReconverge=1) const  = 0 ;

/**
 * @nodoc
 *  Creates and returns the parameter mapping between two curves within this EdgeCurve.
 *  Caller must delete the returned object.
 *  Returned function f verifies: Curvefw(f(w)) <=> Curvew(w)
 *  iDomain contains the limits from iCurvew and iCurvefw
 */
  virtual CATMathFunctionX* GetParamMap ( const CATCurve *iCurvew,
					  const CATCurve *iCurvefw, CATBoolean iAdjustedC2=0, const double * iDomain=0 ) const  = 0 ;


	/** @nodoc */
  virtual CATBoolean CheckGeometry(CATPointOnEdgeCurve *StartPOEC=0, CATPointOnEdgeCurve *EndPOEC=0, double iTol=0.,
		                 CATCX_CHECKUP* report=0) const = 0;


/** @nodoc */
  virtual CATBoolean IsContainingWithLimits ( const CATCurve* iContained, CATPointOnEdgeCurve *StartPOECOnEdgeCurve,
                                                                          CATPointOnEdgeCurve *EndPOECOnEdgeCurve,
                                                                          CATPointOnEdgeCurve *StartPOECOnCurve,
                                                                          CATPointOnEdgeCurve *EndPOECOnCurve) const=0; 
/** @nodoc */
  virtual CATPositiveLength ComputeMaxGap() = 0 ;

/** @nodoc */
  virtual CATCurve * Simplify(CATSurface * iSurface1,
			      CATSurface * iSurface2,
			      CATMathFunctionX * &oMapping) const = 0;

/**
 * @nodoc
  * Gets the mapping between the RefCurve and one of the curve of <tt>this</tt> EdgeCurve
  * specified by iCurve.
  * The returned object can be modified but MUST NOT be deleted. It belongs to the EdgeCurve.
  */
  virtual CATMapX* GetMapX(const CATCurve* iCurve) const = 0;

/**
* @nodoc
 *  Creates and returns the parameter mapping between two curves within <tt>this</tt> EdgeCurve.
 *  Caller must delete the returned object.
 *  The returned MapX RefCurve is iCurve1.
 */
  virtual CATMapX* GetMapX(const CATCurve* iCurve1,const CATCurve* iCurve2) const = 0;

/**
* @nodoc
  * Sets the mapping between the RefCurve and a Curve. If this mapping already exists
  * the old mapping is first deleted before being replaced by this one.
  */
  virtual void SetMapX(const CATMapX* iMapX) = 0;

/**
 * @nodoc
  * Not yet implemented.
  */
  virtual void UpdateMapX() = 0;


/** 
 * @nodoc
 * Reports a point from a curve to another one.
 * @param iParamOnCurrentCurve
 *   The parameter on <tt>iCurrentCurveOrEdgeCurve</tt>.
 * @param iCurrentCurveOrEdgeCurve
 *   The initial CATCurve.
 * @param iEquivalentCurve
 *   The CATCurve with which parameters the point is to be expressed.
 * @param iApproximateResolution
 *   Approximate resolution.
 * @param ioParamOnEquivalentCurve
 *   The equivalent parameter on <tt>iEquivalentCurve</tt>.
 * @return
 * The equivalent parameter on <tt>iEquivalentCurve</tt>.
 */
  virtual HRESULT GetApproximateEquivalentPoint( const CATCrvParam       &  iParamOnCurrentCurve,
				         const CATCurve          *  iCurrentCurveOrEdgeCurve,
	 			         const CATCurve          *  iEquivalentCurve,
                                                 const CATPositiveLength &  iApproximateResolution ,
                                	         CATCrvParam             &  ioParamOnEquivalentCurve ) const  = 0 ;

};
CATDeclareHandler(CATEdgeCurve,CATCurve);

#endif
