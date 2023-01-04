#ifndef CATPParabola_h
#define CATPParabola_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATPCurve.h"
#include "CATMathDef.h"
class CATSurParam ;
class CATMathAxis2D;


#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPParabola ;
#else
extern "C" const IID IID_CATPParabola ;
#endif
/**
 * Interface representing a parabola in the space of a surface.
 *<br> The CATPParabola is created by the <tt>CreatePParabola</tt>
 * method of the <tt>CATGeoFactory</tt> interface  and deleted with the <tt>Remove</tt> method. 
 * It is defined with:
 *<table>
 * <tr><td>CATMathAxis2D</td><td><tt> iAxis </tt></td>
 *                <td> The axis of the parabola in the space of the surface .
 * In this system, the implicit equation is
 *       <tt>Y^2 = 2*iP*X</tt>.</td></tr>
 * <tr><td>CATSurface</td><td><tt> iSupport </tt></td>
 *                <td> The surface on which the parabola is defined. </td></tr>
 * <tr><td>double</td><td><tt> iP</tt></td>
 *                <td> Twice the length from the vertex of the parabola to its focus.</td></tr>
 *</table>
 * To define limits of the parabola, consider the parameter <tt>t</tt> such that:
 *   <tt>X(t) = t^2/(2*p),  Y(t) = t </tt>  , where X and Y are relative to <tt>iAxis</tt>.
 *  <br>Notice that this parameterization is not the internal paramaterization.
 */
class ExportedByCATGMGeometricInterfaces CATPParabola : public CATPCurve
{
  CATDeclareInterface;

public :

/**
 * Modifies the characteristics of <tt>this</tt> CAPParabola.
 * @param iAxis2D
 * The axis system of the parabola in the surface space.
 * @param iFocalParameter
 * Twice the length from the vertex of the parabola to its focus.
 * @param iLimits
 * An array [2] of the parameter values definining the limitations. If <tt>NULL</tt>, the parabola is unlimited.
 * @param iSupport
 * A pointer to the surface on which the parabola is defined.
 */
  virtual void Set (const CATMathAxis2D   &iAxis2D,
		    const double          &iFocalParameter,
		    const double          *iLimits,
		    CATSurface*            iSupport) = 0 ;

/**
 * Returns the axis system of <tt>this</tt> CATPParabola.
 * @param ioAxis2D
 * The axis system of the parabola in the surface space.
 */
  virtual void GetReferenceAxis (CATMathAxis2D &ioAxis2D) const = 0;

/**
 * Returns the focal parameter of a CATPParabola.
 * @return
 * Twice the length from the vertex of the parabola to its focus.
 */
  virtual double GetFocalParam() const = 0 ; 

/**
 * Returns the low and high limitations of <tt>this</tt> CATPParabola.
 * @param ioLowLimitation
 * The parameter value of the first limitation of <tt>this</tt> CATPParabola.
 * @param ioHighLimitation
 * The parameter value of the second limitation of <tt>this</tt> CATPParabola. 
 */
  virtual void GetExtremities(double &ioLowLimitation, double &ioHighLimitation) const = 0 ;

/** 
 * Modifies the reference axis of <tt>this</tt> CATPParabola.
 * @param iAxis
 * The axis of the parabola in the surface space.
 */
  virtual void SetReferenceAxis(const CATMathAxis2D   &iAxis2D) = 0;

/** 
 * Modifies the focal length of <tt>this</tt> CATPParabola.
 * @param iFocalParameter
 * Twice the length from the vertex of the parabola to its focus.
 */
  virtual void SetFocalParam(const double &iFocalParameter) = 0 ;
 
/**
 * Modifies the low and high Limimitations of <tt>this</tt> CATPParabola.
 * @param iLowParam
 * The parameter value of the first limitation of <tt>this</tt> CATPParabola.
 * @param iHighParam
 * The parameter value of the second limitation of <tt>this</tt> CATPParabola.
 */
  virtual void SetExtremities(const double &iLowParam, const double &iHighParam) = 0 ;

};
  CATDeclareHandler(CATPParabola,CATPCurve);

#endif
