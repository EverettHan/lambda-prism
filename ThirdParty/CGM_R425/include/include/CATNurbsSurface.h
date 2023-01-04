#ifndef CATNurbsSurface_h
#define CATNurbsSurface_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

class CATSurParam ;
#include <stdio.h>
#include "CATSurface.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#include "CATSurSide.h"
#include "CATParameterizationOption.h"
#include "CATIAV5Level.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATNurbsSurface ;
#else
extern "C" const IID IID_CATNurbsSurface ;
#endif

/**
 * Interface representing a Nurbs surface.
 * This interface is used to describe:
 * <ul>
 * <li>Bezier surfaces which are single-patch Nurbs
 * <li>NUPBS which are 
 * special cases of Nurbs surfaces where all the weights of the control points equal to 1.
 * </ul>
 * NOTE: Periodic NURBS are not supported.
 * <br> The CATNurbsSurface is created by the <tt>CATCreateNurbsSurface</tt>
 * method of the <tt>CATGeoFactory</tt> interface  
 * and deleted with the <tt>Remove</tt> method. It is defined with:
 * <table>
 * <tr><td>CATKnotVector</td><td><tt> UKnotVector </tt></td>
 *                <td> The knot vector for the polynomial basis definition 
 * on the surface first direction</td></tr>
 * <tr><td>CATKnotVector</td><td><tt> VKnotVector </tt></td>
 *                <td> The knot vector for the polynomial basis definition 
 * on the surface second direction</td></tr>
 * <tr><td>CATMatSetOfPoints</td><td><tt> Vertices </tt></td>
 *                <td> The set of control points </td></tr>
 * <tr><td>CATBoolean</td><td><tt> IsRational </tt></td>
 *                <td> 1 if the nurbs is rational, else 0 (NUPBS) </td></tr>
 * <tr><td>double[]</td><td><tt> Weigths </tt></td>
 *                <td> The weigths array if <tt>IsRational</tt> </td></tr>
 *</table>
 */
class ExportedByCATGMGeometricInterfaces CATNurbsSurface : public CATSurface
{
  CATDeclareInterface;

public:
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Returns the mathematical definition of a control point of <tt>this</tt> CATNurbsSurface.
 * @param iUNum
 * The number (starting at 1) of the control point in the first direction.
 * @param iVNum
 * The number (starting at 1) of the control point in the second direction.
 * @param ioPoint
 * The corresponding mathematical definition.
 */
virtual void GetOneControlPoint(CATLONG32 iUNum,CATLONG32 iVNum, CATMathPoint & ioPoint) const =0;

/**
 * Modifies the mathematical definition of a control point of <tt>this</tt> CATNurbsSurface.
 * @param iUNum
 * The number (starting at 1) of the control point in the first direction.
 * @param iVNum
 * The number (starting at 1) of the control point in the second direction.
 * @param iNewCoord
 * The new mathematical definition.
 */
virtual void SetOneControlPoint(CATLONG32 iUNum,CATLONG32 iVNum, const CATMathPoint & iNewCoord) =0;

/**
 * Returns the weight associated with a control point of <tt>this</tt> CATNurbsSurface.
 * @param iUNum
 * The number (starting at 1) of the control point in the first direction.
 * @param iVNum
 * The number (starting at 1) of the control point in the second direction.
 * @return
 * The corresponding weight.
 */
virtual double GetOneWeight(CATLONG32 iUNum,CATLONG32 iVNum) const =0;

/**
 * Modifies the weight associated with a control point of <tt>this</tt> CATNurbsSurface.
 * @param iUNum
 * The number (starting at 1) of the control point in the first direction.
 * @param iVNum
 * The number (starting at 1) of the control point in the second direction.
 * @param iNewWeight
 * The new weight.
 */
virtual void SetOneWeight(CATLONG32 iUNum,CATLONG32 iVNum, double iNewWeight) =0;

/**
 * Tests whether <tt>this</tt> CATNurbsSurface is rational.
 *@return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>0</tt><dd>if it is not rational.
 *    <dt><tt>1</tt><dd>if it is rational.</dl>
 */
virtual CATBoolean IsRational () const =0;

//#ifdef CATIAV5R14
/**
 *Modifies the characteristics a <tt>this</tt> CATNurbsSurface.
 * @param iNewUKnotVector
 * The new nodal vector in the first direction.
 * @param iNewVKnotVector
 * The new nodal vector in the second direction.
 * @param iNewIsRational
 * <b>Legal values</b>: 1 if the Nurbs is rational, 0 otherwise.
 * @param iNewVertices
 * The grid of the new vertices.
 * @param iNewWeigths
 * The array of the new weights.
 * @param iParameterizationOption
 * The option of parameterization. By default, the parameterization of the NURBS is modified to better
 * fit internal criteria. In this case, you can recover the initial parameterization 
 * with the @href CATNurbsSurface#GetOriginalParametrisationDATA method.
 */
virtual void SetData(const CATKnotVector &iNewUKnotVector, 
                     const CATKnotVector &iNewVKnotVector,
                     const CATLONG32 &iNewIsRational,
                     const CATMathGridOfPoints &iNewVertices,
                     const double * iNewWeights,
                     const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization)  =0;

//#endif

/**
 * @nodoc
 * @deprecated V5R14 SetData
 */
virtual void Set( const CATKnotVector &iNewUKnotVector, 
		  const CATKnotVector &iNewVKnotVector,
		  const CATLONG32 &iNewIsRational,
		  const CATMathGridOfPoints &iNewVertices,
		  const double * iNewWeights,
                  const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization)  =0;


/**
 * Retrieves the original parameterization.
 * <br>If created with the <tt>CatAutomaticParameterization</tt> default mode by the factory, the Nurbs
 * is internally re-parameterized. This allows you to recover the coefficient and the shift that
 * correspond to your own parameterization:
 * <br>
 * <tt>ParameterAfterCreation = ioCoefficient*ParameterBeforeCreation + ioShift</tt> in each direction.
 * @param ioCoefficientU
 * The multiplicative coefficent in the first direction.
 * @param ioShiftU
 * The shift in the first direction.
 * @param ioCoefficientV
 * The multiplicative coefficent in the second direction.
 * @param ioShiftV
 * The shift in the second direction.
 */
  virtual void GetOriginalParametrisationDATA( double &ioCoefficientU,double &ioShiftU,
                                               double &ioCoefficientV, double &ioShiftV  ) =0;


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


/** @nodoc */
virtual CATMathPoint GetOneControlPoint(CATLONG32 iUNum,CATLONG32 iVNum) const =0;

/**
 * @nodoc
 * Modifies all the characteristics of a CATNurbsSurface in Extrapolation.
 */
virtual void Extrapol( const CATKnotVector &iNewUKnotVector, 
		      const CATKnotVector &iNewVKnotVector,
		      const CATLONG32 &iNewIsRational,
		      const CATMathGridOfPoints &iNewVertices,
		      const double * iNewWeights)  =0;

/**
 * @nodoc
 */
virtual CATBoolean GetOriginalLimits(CATSurLimits &ioOriginalLimits) const =0;

/**
 * @nodoc
 */
virtual CATBoolean IsExtrapolated(CATSurSide iSide) const =0;

/**
 * @nodoc
 */
virtual void GetOriginalDegrees(int &ioOriginalDegreeU, int &ioOriginalDegreeV) const =0;

/** @nodoc */  
  virtual void GetExtrapolationData(double *oAlpha,double *oBeta) const =0;

/** @nodoc */ 
  virtual void SetExtrapolationData(double *iAlpha,double *oBeta,
				    CATLONG32 IsExtrapolatedU,CATLONG32 IsExtrapolatedV) =0;
};

CATDeclareHandler(CATNurbsSurface,CATSurface);

#endif
