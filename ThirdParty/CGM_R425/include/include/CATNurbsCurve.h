#ifndef CATNurbsCurve_h
#define CATNurbsCurve_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
class CATMathSetOfPoints ;
#include <stdio.h>
#include "CATCurve.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#include "CATCrvSide.h"
#include "CATParameterizationOption.h"
#include "CATIAV5Level.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATNurbsCurve ;
#else
extern "C" const IID IID_CATNurbsCurve ;
#endif

/**
 * Interface representing a Nurbs curve.
 * This interface is used to describe:
 * <ul>
 * <li>Bezier curves which are single-arc Nurbs
 * <li>NUPBS (Non Uniform Polynomial Base Spline) which are 
 * special cases of Nurbs curves where all the weight of the control points equal to 1.
 * </ul>
 * NOTE: Periodic Nurbs are not supported.
 * <br>A CATNurbsCurve is created by the <tt>CATCreateNurbsCurve</tt>
 * method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method.
 * It is defined with:
 * <table>
 * <tr><td>CATKnotVector</td><td><tt> KnotVector </tt></td>
 *                <td> The knot vector for the polynomial basis definition </td></tr>
 * <tr><td>CATMatSetOfPoints</td><td><tt> Vertices </tt></td>
 *                <td> The set of control points </td></tr>
 * <tr><td>CATBoolean</td><td><tt> IsRational </tt></td>
 *                <td> <tt>TRUE</tt> if the nurbs is rational, <tt>FALSE</tt> otherwise (NUPBS)</td></tr>
 * <tr><td>double[]</td><td><tt> Weights </tt></td>
 *                <td> The array of weights if <tt>IsRational</tt> </td></tr>
 * </table>
 * @see CATKnotVector
 */
class ExportedByCATGMGeometricInterfaces CATNurbsCurve : public CATCurve
{
  CATDeclareInterface;

public:

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//CAA_Exposed
/**
 * Returns a control point of <tt>this</tt> CATNurbsCurve.
 * @param iNum
 * The control point number starting at 1.
 * @param ioControlPoint
 * The corresponding control point.
 */
virtual void GetOneControlPoint(CATLONG32 iNum, CATMathPoint &ioControlPoint) const =0;

//CAA_Exposed
/**
 * Modifies the definition of a control point of <tt>this</tt> CATNurbsCurve.
 * @param iNum
 * The control point number starting at 1.
 * @param iNewCoord
 * The new definition of the control point.
 */
virtual void SetOneControlPoint(CATLONG32 iNum, const CATMathPoint & iNewCoord) =0;

//CAA_Exposed
/**
 * Returns the weight associated with a control point of <tt>this</tt> CATNurbsCurve.
 * @param iNum
 * The  control point number starting at 1.
 * @return
 * The weight.
 */
virtual double GetOneWeight(CATLONG32 iNum) const =0;

//CAA_Exposed
/**
 * Modifies the weight associated with a control point of <tt>this</tt> CATNurbsCurve.
 * @param iNum
 * The  control point number starting at 1.
 * @param iNewWeight
 * The new value of the weight.
 */
virtual void SetOneWeight(CATLONG32 iNum, double iNewWeight) =0;

//CAA_Exposed
/**
 * Tests whether <tt>this</tt> CATNurbsCurve is rational.
 *@return
  * <b>Legal values</b>:
 *<dl><dt><tt>FALSE</tt><dd>if it is not rational.
 *    <dt><tt>TRUE</tt><dd>if it is rational.</dl>
 */
virtual CATBoolean IsRational () const =0;

//#ifdef CATIAV5R14
//CAA_Exposed
/**
 * Modifies the characteristics of <tt>this</tt> CATNurbsCurve.
 * @param iNewKnotVector
 * The new definition of the polynomial basis.
 * @param NewIsRational
 * <b>Legal values</b>:
 *<dl><dt><tt>FALSE</tt><dd>if it is not rational.
 *    <dt><tt>TRUE</tt><dd>if it is rational.</dl>
 * @param iNewVertices
 * The set of control points.
 * @param iNewWeights
 * The array of corresponding weights (one weight per control point).
 * @param iParameterizationOption
 * The option of parameterization. By default, the parameterization of the NURBS is modified to better
 * fit internal criteria. In this case, you can recover the initial parameterization 
 * with the @href CATNurbsCurve#GetOriginalParametrisationDATA method.
 */
virtual void SetData(const CATKnotVector &iNewKnotVector, 
                     const CATLONG32 &iNewIsRational,
                     const CATMathSetOfPoints &iNewVertices,
                     const double * iNewWeights,
                     const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization)  =0;

//#endif

/**
 * @nodoc
 * @deprecated V5R14 SetData
 */
virtual void Set( const CATKnotVector &iNewKnotVector, 
		  const CATLONG32 &iNewIsRational,
		  const CATMathSetOfPoints &iNewVertices,
		  const double * iNewWeights,
                  const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization)  =0;

//CAA_Exposed
/**
 * Retrieves the original parameterization.
 * <br>If created with the <tt>CatAutomaticParameterization</tt> default mode by the factory, the Nurbs
 * is internally re-parameterized. This allows you to recover the coefficient and the shift that
 * correspond to your own parameterization
 * <br>
 * <tt>ParameterAfterCreation = ioCoefficient*ParameterBeforeCreation + ioShift</tt> in each direction.
 * @param ioCoefficient
 * The multiplicative coefficent.
 * @param ioShift
 * The shift.
 */
  virtual void GetOriginalParametrisationDATA( double &ioCoefficient, double &ioShift) =0;


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * @nodoc
 * Modifies the characteristics of <tt>this</tt> CATNurbsCurve in extrapolation.
 */
virtual void Extrapol( const CATKnotVector &iNewKnotVector, 
		      const CATLONG32 &iNewIsRational,
		      const CATMathSetOfPoints &iNewVertices,
		      const double * iNewWeights)  =0;

/**
 * @nodoc
 */
virtual CATBoolean GetOriginalLimits(CATCrvLimits &ioOriginalLimits) const = 0;

/**
 * @nodoc
 */
virtual CATBoolean IsExtrapolated(CATCrvSide iSide) const = 0;

/**
 * @nodoc
 */
virtual void GetOriginalDegree(int &ioOriginalDegree) const = 0;

///////////////////////////////////////////////////////////////////////////////
//                         Methods that will disappear
///////////////////////////////////////////////////////////////////////////////
/** @nodoc */
virtual CATMathPoint GetOneControlPoint(CATLONG32 iNum) const =0;
  
};

CATDeclareHandler(CATNurbsCurve,CATCurve);

#endif
