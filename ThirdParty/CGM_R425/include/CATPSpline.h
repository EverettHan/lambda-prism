#ifndef CATPSPLINE_h
#define CATPSPLINE_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U3
*/ 

#include "CATPCurve.h"
#include "CATMathDef.h"
#include "CATIACGMLevel.h"
#include "CATCrvSide.h"
class CATSurParam;
class CATMathVector2D;
class CATMathSetOfPointsND;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPSpline ;
#else
extern "C" const IID IID_CATPSpline ;
#endif

/**
* Interface representing a curve interpolated between a set of points on surface
* with a spline interpolation .
*<br> The CATPSpline is created by the <tt>CreatePSpline</tt>
* method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method. 
* It is defined with:
*<table>
* <tr><td>CATMathSetOfPoints</td><td><tt> Points </tt></td>
*                <td> The set of points on surface defining the curve</td></tr>
* <tr><td>CATSurface</td><td><tt> iSupport </tt></td>
*                <td> The surface on which the Spline is defined </td></tr>
*</table>
*The user may define its own parameterization on the curve.
*/
class ExportedByCATGMGeometricInterfaces CATPSpline : public CATPCurve
{
  CATDeclareInterface;

public :

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  /**
  * Returns the number points defining <tt>this</tt> CATPSpline.
  * @return
  * The number of points
  */
  virtual CATLONG32 GetNumberOfPoints() const = 0 ;

  /**
  * Returns the parameter of a definition point of <tt>this</tt> CATPSpline.
  * @param iNum
  * The number of the definition point starting at 1.
  * @param ioParam
  * The corresponding parameter on the underlying surface. 
  */
  virtual void GetOnePoint(CATLONG32 iNum, CATSurParam &ioParam) const = 0 ;

  /**
  * Returns the tangent at a definition point of <tt>this</tt> CATPSpline.
  * @param iNum
  * The number of the definition point starting at 1.
  * @param ioTangentVector
  * The corresponding tangent on the underlying surface. 
  */
  virtual void GetOneTangent(CATLONG32 iNum, CATMathVector2D &ioTangentVector ) const = 0 ;

  /**
  * Returns the second derivative at a definition point of <tt>this</tt> CATPSpline.
  * @param iNum
  * The number of the definition point starting at 1.
  * @param ioSecondDerivativeVector
  * The corresponding second derivative on the underlying surface. 
  */
  virtual void GetOneSecondDerivative(CATLONG32 iNum, CATMathVector2D &ioSecondDerivativeVector ) const = 0 ;

  /**
  * Returns the global parameter of a definition point of <tt>this</tt> CATPSpline .
  * @param iNum
  * The number of the definition point starting at 1.
  * @return
  * The parameter value on the curve.
  */
  virtual double GetOneParameter(CATLONG32 iNum) const = 0 ;

  /**
  * Modifies the definition of one point of <tt>this</tt>.
  * @param iNum
  * The number of the definition point starting at 1.
  * @param iNewCoord
  * The new parameter value on the surface.
  */
  virtual void ReplaceOnePoint(CATLONG32 iNum, const CATSurParam & iNewCoord) = 0 ;


  /**
  * @nodoc
  * @deprecated V5R17 ReplaceOnePoint
  */
  virtual void SetOnePoint(CATLONG32 iNum, const CATSurParam & iNewCoord) = 0 ;

  /**
  * Modifies the tangent of one definition point of <tt>this</tt> CATPSpline.
  * @param iNum
  * The number of the definition point starting at 1.
  * @param iNewTangent
  * The corresponding tangent on the underlying surface. 
  */
  virtual void ReplaceOneTangent(CATLONG32 iNum, const CATMathVector2D & iNewTangent) = 0 ;


  /**
  * @nodoc
  * @deprecated V5R17 ReplaceOneTangent
  */
  virtual void SetOneTangent(CATLONG32 iNum, const CATMathVector2D & iNewTangent) = 0 ;

  /**
  * Modifies the second derivative of a point of <tt>this</tt> CATPSpline. 
  * @param iNum
  * The number of the definition point starting at 1.
  * @param iSecondDerivativeVector
  * The corresponding second derivative on the underlying surface. If the spline degree is 3, this does nothing.
  */
  virtual void SetOneSecondDerivative(CATLONG32 iNum, const CATMathVector2D &iSecondDerivativeVector ) = 0 ;

  /**
  * Modifies <tt>this</tt> CATPSpline definition point parameter.
  * @param iNum
  * The number of the definition point starting at 1.
  * @param iNewParameter
  * The new parameter value on the curve.
  */
  virtual  void ReplaceOneParameter(CATLONG32 iNum, const double & iNewParameter) = 0 ;

  /**
  * @nodoc
  * @deprecated V5R17 ReplaceOneParameter
  */
  virtual void SetOneParameter(CATLONG32 iNum, const double & iNewParameter) = 0 ;

  /**
  * Adds a point to the definition of <tt>this</tt> CATPSpline.
  * @param iRankNumber
  * The position of the added point
  * (1 to be inserted between the first and the second point).
  * @param iParam
  * The parameter of the added point on the curve
  * @param iPoint 
  * The array  of the point coordinates.
  * @param iTangent
  * The array  of the tangent coordinates.
  * @param iSecondDerivative
  * The array  of the second derivative coordinates.
  * @param iFirstCoordIndex
  * This index is such that the point, tangent and second derivative of the
  * first coordinate of the spline are the values of index iFirstCoordIndex
  * @param iSecondCoordIndex
  * Idem as iFirstCoordIndex but for the second coordinate of the spline.
  */
  virtual CATBoolean AddOnePoint(const CATLONG32 iRankNumber,
                                 const double iParam,
                                 const double * iPoint,
                                 const double * iTangent,
                                 const double * iSecondDerivative,
                                 const CATLONG32 iFirstCoordIndex,
                                 const CATLONG32 iSecondCoordIndex) = 0;

  /**
  * Get the degree of <tt>this</tt> CATPSpline .
  * @return
  * The degree of <tt>this</tt> CATPSpline .
  */
  virtual CATLONG32 GetDegree() const = 0 ;



  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  /**
  * @nodoc
  * Add points, tangents and secondderivatives to extrapol <tt>this</tt> CATPSpline.
  * <br>iParams must contain value which connect exactly with the 
  * parameters before extrapolation.
  * <br>The PSpline must be a quintic for this method to be valid.
  */
  virtual void Extrapol(const CATMathSetOfPointsND * iParams,
                        const CATMathSetOfPointsND * iPoints,
                        const CATMathSetOfPointsND * iTangents,
                        const CATMathSetOfPointsND * iSecondDerivatives,
                        const CATLONG32 iFirstCoordIndex,
                        const CATLONG32 iSecondCoordIndex) = 0;


  /** @nodoc */
  virtual CATSurParam GetOnePoint(CATLONG32 iNum) const = 0 ;


  /** @nodoc */
  virtual CATMathVector2D GetOneTangent(CATLONG32 iNum) const = 0 ;

  /** @nodoc */
  virtual CATBoolean Unextrapol(const CATCrvLimits &iNewLimits,CATLONG32 iSplitMode) = 0;

#ifdef CATIACGMR421CAA
  /** @nodoc */
  virtual CATBoolean IsExtrapolated(CATCrvSide iSide) const = 0;
#endif

};

CATDeclareHandler(CATPSpline,CATPCurve);

#endif
