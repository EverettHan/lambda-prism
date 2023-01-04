#ifndef CATINTERSECTCRVCRV_H
#define CATINTERSECTCRVCRV_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "CATCreateIntersection.h"
#include "CATMathDef.h"
#include "CATCrvParam.h"
#include "CATCGMOperator.h"
#include "Y30C3XGG.h"

class CATGeoFactory;
class CATCartesianPoint;
class CATCrvParam;
class CATCrvLimits;
class CATCurve;
class CATEdgeCurve;
class CATPointOnCurve;
class CATPointOnEdgeCurve;

/**
 * Class defining the operator of the intersection of two curves.
 *<br>The operator outputs the isolated solutions (points) and the
 * overlapping solutions (curves).
 *<ul>
 *<li>The CATIntersectionCrvCrv operator is created with the <tt>CreateIntersection</tt> method and 
 * directly <tt>delete</tt>d with the usual C++ delete operator.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with different curves.
 *<li>In both cases, the result is accessed with two specific interators, one for the solution points,
 * the other for the solution curves.
 *</ul>
 */
class ExportedByY30C3XGG CATIntersectionCrvCrv : public CATCGMOperator
{

  CATCGMVirtualDeclareClass(CATIntersectionCrvCrv);
public:
/**
 * @nodoc
 * Use the <tt>CreateIntersection</tt> global method.
 */
   CATIntersectionCrvCrv(CATGeoFactory * factory) ;

/**
 * Destructor.
 */
   virtual ~CATIntersectionCrvCrv() ;

/**
 * Returns the number of isolated resulting points of <tt>this</tt> CATIntersectionCrvCrv operator.
 * @return
 * The number of isolated points.
 */
   virtual CATLONG32 GetNumberOfPoints() const = 0;
/**
 * @nodoc
 * Do not use will be suppressed soon.
 */
   virtual CATLONG32 GetNumberOfPointSolutions() const = 0;

/**
 * Initializes the iterator of the resulting points.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
   virtual void BeginningPoint() = 0;

/**
 * Skips to the next solution point of <tt>this</tt> CATIntersectionCrvCrv operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
   virtual CATBoolean NextPoint() = 0;

/**
 * Creates the next solution point of <tt>this</tt> CATIntersectionCrvCrv operator.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
   virtual CATCartesianPoint * GetCartesianPoint() = 0;

/**
 * Creates the next solution point on curve of <tt>this</tt> CATIntersectionCrvCrv operator.
 * @param iCurve
 * The pointer to the first or second curve which are intersected.
 * @param iIndex
 * Internal use.
 * @return
 * The pointer to the created point on curve. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
   virtual CATPointOnCurve * GetPointOnCurve( CATCurve *iCurve,
     const CATLONG32 iIndex = 0) const = 0;

/** @nodoc */
   virtual CATCrvParam GetCurveParam( CATCurve *iCurve, const CATLONG32 iIndex =0 ) const = 0;

/**
 * Retrieves the parameter of the next solution point of <tt>this</tt> CATIntersectionCrvCrv operator.
 * @param iCurve
 * The pointer to the first or second curve which are intersected. 
 * @param ioCrvParam
 * The parameter.
 * @param iIndex
 * Internal use.
 */
   virtual void GetCurveParam( CATCurve *iCurve, CATCrvParam & ioCrvParam, const CATLONG32 iIndex=0) const = 0;
   
   
/**
 * Returns the number of solution curves of <tt>this</tt> CATIntersectionCrvCrv operator.
 * @return
 * The number of resulting curves.
 */
   virtual CATLONG32 GetNumberOfCurves() const = 0;
/**
 * @nodoc
 * Do not use will be suppressed soon.
 */
   virtual CATLONG32 GetNumberOfCurveSolutions() const = 0;

/**
 * Initializes the iterator of the solution curves.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
   virtual void BeginningCurve() = 0;

/**
 * Skips to the next solution curve of <tt>this</tt> CATIntersectionCrvCrv operator.
 *<br>After <tt>BeginningCurve</tt>, it skips to the first curve. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution curve
 *    <dt><tt>FALSE</tt> <dd>no more solution curve.</dl>
 */
   virtual CATBoolean NextCurve() = 0;
/**
 * Returns the domain of the next solution curve of <tt>this</tt> CATIntersectionCrvCrv operator.
 * @param iCurve
 * The first or the second operand of the operator, on which the domain is output.
 * @param ioLimits
 * The domain of the solution curve.
 */

   virtual void GetCurveLimits(CATCurve* iCurve, CATCrvLimits &ioLimits) const =0;


/**
 * Creates the next solution curve of <tt>this</tt> CATIntersectionCrvCrv operator as an edge curve.
 * <br>The edge curve is composed of parts of each inital curve. 
 * @param oStart
 * The pointer to the created point representing the first extremity of the solution curve.
 * A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 * @param oEnd
 * The pointer to the created point representing the last extremity of the solution curve.
 * A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 * @return
 * The pointer to the created edge curve, <tt>NULL</tt> if it cannot be created.
 * A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
 * and the POEC extremities oStart and oEnd on this edgecurve.
 */
   virtual CATEdgeCurve * GetEdgeCurve(CATPointOnEdgeCurve * & oStart, CATPointOnEdgeCurve * & oEnd) const =0;

/**
 * Defines the intersection with another second curve (<tt>ADVANCED</tt> mode).
 * @param iNewSecondCurve
 * The pointer to the new second curve.
 */
   virtual void SetCurve( CATCurve *iNewSecondCurve ) = 0;

/**
 * @nodoc
 * Modifies the tolerance of a CATIntersectionCrvCrv operator.
 *<br>These tolerances are the tolerance of confusion of the curve extremity
 * with another curve and the tolerance of confusion of two piece of curves.
 *<br>In case of <tt>ADVANCED</tt> mode.
 * Use after the <tt>Run</tt> method.
 */
   virtual void SetTolerance(double iNewTolerance) = 0;

/**
 * Modifies the curve domain to take into account for <tt>this</tt>
 * CATIntersectionCrvCrv operator (<tt>ADVANCED</tt> mode).
 *<br> It does not change the current curve limitations.
 * @param iLimitsForCurve1
 * The pointer to the new domain of the first curve. If <tt>NULL</tt>, the current limitation of the first
 * curve is used.
 * @param iLimitsForCurve2
 * The pointer to the new domain of the second curve. If <tt>NULL</tt>, the current limitation of the second
 * curve is used.
 */
   virtual void UseLimits( CATCrvLimits *iLimitsForCurve1,
                        CATCrvLimits *iLimitsForCurve2 ) = 0;

/**
 * @nodoc
 * DO NOT USE
 */
   virtual CATCrvLimits GetCurveLimits(CATCurve *BID) const = 0;

/**
 * @nodoc 
 * Tangential warning diagnostic associated to a curve solution, return TRUE is the curve solution is
 *  in an instable tangential configuration
 */
   virtual CATBoolean GetTangentialWarningDiagnostic() const=0;

//#ifdef CATIAV5R14
/**
 * @nodoc
 * Get Curve parameters of first point of a confusion.
 * @param Param1
 * Curve parameter of the point on Curve1.
 * @param Param2
 * Curve parameter of the point on Curve2.
 */
  virtual void GetFirstConfusionParam(CATCrvParam & Param1, CATCrvParam & Param2) const =0 ;

/**
 * @nodoc
 * Get Curve parameters of end point of a confusion.
 * @param Param1
 * Curve parameter of the point on Curve1.
 * @param Param2
 * Curve parameter of the point on Curve2.
 */
  virtual void GetSecondConfusionParam(CATCrvParam & Param1, CATCrvParam & Param2) const = 0;

/**
 * @nodoc
 * Get Curve parameters of best point of a confusion.
 * Reconvergence option must have been set.
 * @param Param1
 * Curve parameter of the point on Curve1.
 * @param Param2
 * Curve parameter of the point on Curve2.
 */
  virtual void GetBestConfusionParam(CATCrvParam & Param1, CATCrvParam & Param2) const = 0;

/**
 * @nodoc
 * Forces 3D computation in the case of 2D input Curves.
 * (<tt>ADVANCED</tt> mode)
 * <br>By default this option is unset for operator.
 * @param iForce3D
 * <br><b>Legal values</b>:
 * <dl><dt><tt>TRUE</tt></dt><dd> 3D computation active.
 *     <dt><tt>FALSE</tt></dt><dd> 3D computation not active.</dl>
 */
	virtual void Force3DCompute(CATBoolean iForce3D = TRUE) = 0;

/**
 * @nodoc
 * Set Reconvergence calculation in the case of a confusion.
 * (<tt>ADVANCED</tt> mode)
 * <br>By default this option is unset for operator.
 * @param NewConvergence
 * <br><b>Legal values</b>:
 * <dl><dt><tt>1</tt> </dt><dd> Reconvergence is set.
 *     <dt><tt>0</tt> </dt><dd> Reconvergence isn't set.</dl>
 */
  virtual void SetReconvergence(int NewReconvergence) = 0;
/**
 * @nodoc
 * Use Plane computation method.
 * (<tt>ADVANCED</tt> mode)
 * <br>By default this option is unset for operator.
 * @param iForcePlaneMethod
 * <br><b>Legal values</b>:
 * <dl><dt><tt>TRUE</tt> </dt><dd> Plane method used.
 *     <dt><tt>FALSE</tt> </dt><dd> Plane method not used.</dl>
 */
  virtual void SetPlaneMethod(CATBoolean iForcePlaneMethod = TRUE) = 0;
//#endif
};

#include "CreateIntersection.h"
#endif
