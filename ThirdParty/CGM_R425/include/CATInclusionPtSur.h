#ifndef CATInclusionPtSur_H
#define CATInclusionPtSur_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "CATCreateInclusionPtSur.h"
#include "CreateInclusionPtSur.h"
#include "CATGeoOperator.h"

#include "CATMathDef.h"
#include "CATSurParam.h"
//#ifdef CATIAV5R14
#include "CATMathBox.h"
//#endif

class CATGeoFactory;
class CATPoint;
class CATPointOnSurface;
class CATSurface;
class CATMathPoint;
class CATSurLimits;

/**
 * Class defining the operator for testing the inclusion of a point
 * in a surface.
 *<br>The inclusion is tested within a given tolerance. The operator gets all
 * the points closed enough (at the tolerance) to the surface, spaced 
 * each other by a curvilinear distance at least equal to <tt>2*Tol</tt>.
 * This operator is optimized for low values of <tt>Tol</tt>. It differs from the
 * CATDistanceMinPtSur operator, that only outputs one point realizing
 * the minimum distance without tolerance.
 *<ul>
 *<li>The CATInclusionPtSur operator is created with the <tt>CreateInclusion</tt> method and 
 * directly <tt>delete</tt>d with the usual C++ delete operator.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with different points.
 *<li>In both cases, the result is accessed with a specific interator.
 *</ul>
 */
class CATInclusionPtSur : public CATGeoOperator
{    
  CATCGMVirtualDeclareClass(CATInclusionPtSur);
  public:
/**
 * @nodoc
 * Use the <tt>CreateInclusion</tt> global method.
 */
    CATInclusionPtSur(CATGeoFactory * factory);

/**
 * Destructor.
 */
    virtual ~CATInclusionPtSur();

/**
 * Returns the number of resulting points of <tt>this</tt> CATInclusionPtCrv operator.
 * @return
 * The number of solutions.
 */
    virtual CATLONG32 GetNumberOfPoints() const=0;  
	
/**
 * Initializes the iterator of the resulting points of <tt>this</tt> 
 * CATInclusionPtSur operator.
 *<br>By default, the initialization is performed once the operator runs,
 * and this is therefore only used to read the solutions again.
 */
    virtual void BeginningPoint()  =0;

/**
 * Skips to the next solution point of <tt>this</tt> CATInclusionPtSur operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. The points are
 * spaced each other by a curvilinear length at least equal to <tt>2*Tol</tt>.
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
    virtual CATBoolean NextPoint() =0;

/**
 * Creates the next solution point of <tt>this</tt> CATInclusionPtSur operator.
 * @return
 * The pointer to the created point on surface. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
    virtual CATPointOnSurface * GetPointOnSurface() const=0;

/**
 * Retrieves the parameter of the next solution point of <tt>this</tt> CATInclusionPtSur operator.
 * @return
 * The parameter.
 */
    virtual CATSurParam  GetSurParam() const=0;
/**
 * Returns the distance of a solution point and the surface.
 * @return
 * The distance.
 */
    virtual double GetDistance()  const=0;

/**
 * Returns the signature of the solution point.
 * @return
 * The signature.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt></dt><dd> if the point is on the surface
 * <dt><tt>-1</tt> of <tt>1</tt></dt><dd>according to the sign of the
 * dot product : <tt>(Point-Projection(Point))*NormalToSurface(Projection(Point))</tt>.
 * </dl>
 */
    virtual CATLONG32 GetSignature()  const = 0;

/**
 * Sets a new point for <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
 * @param iPt
 * The pointer to the new point to take into account.
 */
    virtual void SetPoint(CATPoint * iPt) = 0 ;

		/**
 * Sets a new point for <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
 * @param iMathPt
 * The new point to take into account.
 */
    virtual void SetPoint(CATMathPoint & iMathPt) = 0;
/**
 * Defines the curve new limitations to take into account for <tt>this</tt> operator in 
 * <tt>ADVANCED</tt> mode.
 * @param iNewLimits
 * The new limitations on the curve.
 */
    virtual void SetLimits(const CATSurLimits & iNewLimits) = 0 ;


/**
 * @nodoc
 * Do not use.
 */
    virtual double GetTolerance() const=0; 

//#ifdef CATIAV5R14
    /**
    * @nodoc
    */
    virtual void SetSearchOnBoundary( CATBoolean TrueFalse) = 0;
    /**
    * @nodoc
    */
    virtual void SetFastInclusion (CATBoolean NewDist=1) = 0;
    /**
    * @nodoc
    */
    virtual void SetBox (CATMathBox &) = 0;
		/**
    * @nodoc
    */
    virtual void SetPointAndInit ( CATPoint *, CATSurParam) = 0;
		/**
    * @nodoc
    */
    virtual void SetPointAndInit ( CATMathPoint &, CATSurParam) = 0;
//#endif

};


#endif
