#ifndef CATSplineCurve_h
#define CATSplineCurve_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U3
*/ 

#include "CATCurve.h"
#include "CATMathDef.h"
#include "CATIACGMLevel.h"
#include "CATCrvSide.h"
class CATMathPoint;
class CATMathVector;
class CATMathSetOfPointsND;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATSplineCurve ;
#else
extern "C" const IID IID_CATSplineCurve ;
#endif

//CAA_Exposed  CATIGemSplineCurve
/**
* Interface representing a curve interpolated between a set of points
* with a spline interpolation.
*<br> The CATSplineCurve is created by the <tt>CreateSplineCurve</tt>
* method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method.
* It is defined with:
*<table>
* <tr><td>CATMathSetOfPoints</td><td><tt> Points </tt></td>
*                <td> The definition points of the curve </td></tr>
*</table>
*The user can defined its own parameterization on the curve.
*/
class ExportedByCATGMGeometricInterfaces CATSplineCurve : public CATCurve
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
  * Returns the number of points defining <tt>this</tt> CATSplineCurve.
  * @return
  * The number of definition points.
  */
  virtual CATLONG32 GetNumberOfPoints() const = 0 ;

  //CAA_Exposed
  /**
  * Returns a definition point of
  * <tt>this</tt> CATSplineCurve.
  * @param iNum
  * The number of the definition point starting at 1.
  * @param ioPoint
  * The corresponding point.
  */
  virtual void GetOnePoint(CATLONG32 iNum, CATMathPoint &ioPoint) const = 0 ;

  //CAA_Exposed
  /**
  * Returns the tangent at a definition point of <tt>this</tt> CATSplineCurve.
  * @param iNum
  * The number of the definition point starting at 1.
  * @param ioTangent
  * The corresponding tangent.
  */
  virtual void GetOneTangent(CATLONG32 iNum, CATMathVector &ioTangent) const = 0 ;

  //CAA_Exposed
  /**
  * Returns the parameter of a definition point of <tt>this</tt> CATSplineCurve.
  * @param iNum
  * The number of the definition point starting at 1.
  * @return
  * The corresponding parameter on <tt>this</tt> CATSplineCurve.
  */
  virtual double GetOneParameter(CATLONG32 iNum) const = 0 ;


  //CAA_Exposed
  /**
  * Modifies a definition point of <tt>this</tt> CATSplineCurve.
  * This Curve must be C2 continuous and a quintic.
  * @param iNum
  * The number of the definition point starting at 1.
  * @param iNewCoord
  * The new coordinates of the point.
  */
  virtual void ReplaceOnePoint(CATLONG32 iNum, const CATMathPoint & iNewCoord) = 0 ;


  /**
  * @nodoc
  * @deprecated V5R17 ReplaceOnePoint
  */
  virtual void SetOnePoint(CATLONG32 iNum, const CATMathPoint & iNewCoord) = 0 ;


  //CAA_Exposed
  /**
  * Modifies the tangent at a definition point of <tt>this</tt> CATSplineCurve.
  * This Curve must be C2 continuous and a quintic.
  * @param iNum
  * The number of the definition point starting at 1.
  * @param iNewCoord
  * The new coordinates of the point.
  */
  virtual void ReplaceOneTangent(CATLONG32 iNum, const CATMathVector & iNewTangent) = 0 ;


  /**
  * @nodoc
  * @deprecated V5R17 ReplaceOneTangent
  */

  virtual void SetOneTangent(CATLONG32 iNum, const CATMathVector & iNewTangent) = 0 ;

  /**
  * Returns the tangent at a definition point of <tt>this</tt> CATSplineCurve.
  * This Curve must be C2 continuous.
  * @param iNum
  * The number of the definition point starting at 1.
  * @return
  * The tangent.
  */
  virtual CATMathVector GetOneTangent(CATLONG32 iNum) const = 0 ;




  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


  /**
  * @nodoc
  * Modifies the parameter of <tt>this</tt> CATSplineCurve definition point.
  * <br>The number of the definition point starting at 1.
  */
  virtual void SetOneParameter(CATLONG32 iNumr, const double & iNewParameter) = 0 ;


  /**
  * @nodoc
  * Defines a quintic extrapolation for <tt>this</tt> CATSplineCurve, with a user defined parameterization.
  * <br> <tt>iPoints</tt>, <tt>iTangents</tt> and <tt>iSecondDerivatives</tt> must have the same N dimension.
  * @param iParams
  * A pointer to the set of points containing the user parameterization. The parameter is defined as
  * the first index (=0) coordinate of the ND point.
  * @param iPoints
  * A pointer to the CATMathSetOfPointsND specifiying the coordinates of the definition points.
  * @param iTangents
  * A pointer to the CATMathSetOfPointsND specifiying the tangent coordinates at the definition points.
  * @param iSecondDerivatives
  * A pointer to the CATMathSetOfPointsND specifiying the second derivative coordinates at the definition points.
  * @param iFirstCoordIndex
  * The index (begins at 0) coordinate of the ND point 
  * defining the first (point, tangent, second derivative) coordinate .
  * @param iSecondCoordIndex
  * The index (begins at 0) coordinate of the ND point
  * defining the second (point, tangent, second derivative) coordinate .
  * @param iSecondCoordIndex
  * The index (begins at 0) coordinate of the ND point of the 
  * defining the third (point, tangent, second derivative) coordinate .
  */
  virtual void Extrapol(const CATMathSetOfPointsND * iParams,
                        const CATMathSetOfPointsND * iPoints,
                        const CATMathSetOfPointsND * iTangents,
                        const CATMathSetOfPointsND * iSecondDerivatives,
                        const CATLONG32 iFirstCoordIndex,
                        const CATLONG32 iSecondCoordIndex,
                        const CATLONG32 iThirdCoordIndex)=0;

  /** @nodoc */
  virtual CATMathPoint GetOnePoint(CATLONG32 iNum) const = 0 ;

#ifdef CATIACGMR421CAA
  /** @nodoc */
  virtual CATBoolean IsExtrapolated(CATCrvSide iSide) const = 0;
#endif

};

CATDeclareHandler(CATSplineCurve,CATCurve);

#endif
