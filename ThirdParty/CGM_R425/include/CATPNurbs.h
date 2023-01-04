#ifndef CATPNurbs_h
#define CATPNurbs_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATPCurve.h"
#include "CATCrvSide.h"
#include "CATMathDef.h"
#include "CATParameterizationOption.h"
#include "CATIAV5Level.h"

class CATSurParam ;
class CATMathSetOfPoints ;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPNurbs ;
#else
extern "C" const IID IID_CATPNurbs ;
#endif

//CAA_Exposed  CATIGemPNurbsCurve
/**
 * Interface representing a Nurbs curve in a surface space.
 *<br> The CATPNurbs is created by the <tt>CreatePNurbs</tt>
 * method of the <tt>CATGeoFactory</tt> interface  and deleted with the <tt>Remove</tt> method. 
 * It is defined with:
 *<table>
 * <tr><td>CATKnotVector</td><td><tt> KnotVector </tt></td>
 *                <td> The knot vector for the polynomial basis definition </td></tr>
 * <tr><td>CATMathSetOfPoints</td><td><tt> Vertices </tt></td>
 *                <td> The set of control points </td></tr>
 * <tr><td>CATBoolean</td><td><tt> IsRational </tt></td>
 *                <td> 1 if the nurbs is rational, else 0 </td></tr>
 * <tr><td>double[]</td><td><tt> Weigths </tt></td>
 *                <td> The weigths array if <tt>IsRational</tt> </td></tr>
  * <tr><td>CATSurface</td><td><tt> iSupport </tt></td>
 *                <td> The surface on which the Nurbs is defined </td></tr>
 *</table>
 * @see CATKnotVector
 */
class ExportedByCATGMGeometricInterfaces CATPNurbs : public CATPCurve
{
  CATDeclareInterface;

public :
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//CAA_Exposed
/**
 * Returns the number control points of <tt>this</tt> CATPNurbs.
 * @return
 * The number of control points.
 */
virtual  CATLONG32 GetNumberOfControlPoints() const = 0 ;

//CAA_Exposed
/**
 * Retrieves the parameter of a control point of <tt>this</tt> CATPNurbs.
 * @param iNum
 * The  control point number starting at 1.
 * @param ioControlPoint
 * The parameter corresponding to the <tt>iNum</tt>-th control point.
 */
virtual  void  GetOneControlPoint(CATLONG32 iNum, CATSurParam &ioControlPoint) const = 0 ;

//CAA_Exposed
/**
 * Modifies a control point definition of <tt>this</tt> CATPNurbs.
 * @param iNum
 * The  control point number starting at 1.
 * @param iNewCoord
 * The new parameter of the <tt>iNum</tt>-th control point.
 */
virtual  void SetOneControlPoint(CATLONG32 iNum, const CATSurParam & iNewCoord) = 0 ;

//CAA_Exposed
/**
 * Returns the weight associated with a control point of <tt>this</tt> CATPNurbs.
 * @param iNum
 * The  control point number starting at 1.
 * @param return
 * The associated weight.
 */
virtual  double GetOneWeight(CATLONG32 iNum) const = 0 ;

//CAA_Exposed
/**
 * Modifies the weight associated with a control point of <tt>this</tt> CATPNurbs.
 * @param iNum
 * The  control point number starting at 1.
 */
virtual  void SetOneWeight(CATLONG32 iNum, double iWeight) = 0 ;

//CAA_Exposed
/**
 * Tests if <tt>this</tt> CATPNurbs is rational.
 *@return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>FALSE</tt><dd>if it is not rational.
 *    <dt><tt>TRUE</tt><dd>if it is rational.</dl>
 */
virtual  CATBoolean IsRational () const = 0 ;

//#ifdef CATIAV5R14
//CAA_Exposed
/**
 * Modifies all the characteristics of <tt>this</tt> CATPNurbs.
  * @param iNewKnotVector
 * The new definition of the polynomial basis.
 * @param iNewIsRational
 * <b>Legal values</b>:
 *<dl><dt><tt>FALSE</tt><dd>if it is not rational.
 *    <dt><tt>TRUE</tt><dd>if it is rational.</dl>
 * @param iNewVertices
 * The set of new control points.
 * @param iNewWeights
 * The array of corresponding weights (one weight per control point).
 * @param iNewSupport
 * The new surface on which <tt>this</tt> CATPNurbs will be defined.
 * @param iParameterizationOption
 * The option of parameterization. By default, the parameterization of the NURBS is modified to better
 * fit internal criteria. In this case, you can recover the initial parameterization 
 * with the @href CATPNurbs#GetOriginalParametrisationDATA method.
 */
virtual  void SetData (const CATKnotVector &iNewKnotVector, 
                       const CATLONG32 &iNewIsRational, 
                       const double * iNewVertices,
                       const double * iNewWeights,
                       CATSurface* iNewSupport,
                       const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization) = 0 ;


//#endif

/**
 * @nodoc
 * @deprecated V5R14 SetData
 */
virtual  void Set ( CATKnotVector &iNewKnotVector, 
	            const CATLONG32 &iNewIsRational, 
 	            const double * iNewVertices,
	            const double * iNewWeights,
	            CATSurface* iNewSupport,
                    const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization) = 0 ;


//CAA_Exposed
/**
 * Gets the original parameterization.
 * <br>If created with the <tt>CatAutomaticParameterization</tt> default mode by the factory, the Nurbs
 * is internally re-parameterized. This allows you to recover the coefficient and the shift that
 * correspond to your own parameterization.
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
 * Modifies the extrapolation characteristics of <tt>this</tt> CATPNurbs.
  * @param iNewKnotVector
 * The new definition of the polynomial basis.
 * @param iNewIsRational
 * <b>Legal values</b>:
 *<dl><dt><tt>FALSE</tt><dd>if it is not rational.
 *    <dt><tt>TRUE</tt><dd>if it is rational.</dl>
 * @param iNewVertices
 * The set of new control points.
 * @param iNewWeights
 * The array of corresponding weights (one weight per control point).
 */
virtual  void Extrapol ( CATKnotVector &iNewKnotVector, 
			const CATLONG32 &iNewIsRational, 
			const double * iNewVertices,
			const double * iNewWeights) = 0 ;

/**
 * @nodoc
 */
virtual CATBoolean Unextrapol ( const CATCrvLimits &iNewLimits,CATLONG32 iSplitMode) = 0;

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
//                              Methods that will disappear
///////////////////////////////////////////////////////////////////////////////
/** @nodoc */
virtual  CATSurParam GetOneControlPoint(CATLONG32 iNum) const = 0 ;

};

CATDeclareHandler(CATPNurbs,CATPCurve);

#endif
