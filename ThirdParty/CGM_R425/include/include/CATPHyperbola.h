#ifndef CATPHyperbola_h
#define CATPHyperbola_h

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
extern ExportedByCATGMGeometricInterfaces IID IID_CATPHyperbola ;
#else
extern "C" const IID IID_CATPHyperbola ;
#endif

//CAA_Exposed CATIGemPHyperbola
/**
 * Interface representing an hyperbola in the space of a surface.
 *<br> The CATPHyperbola is created by the <tt>CreatePHyperbola</tt>
 * method of the <tt>CATGeoFactory</tt> interface  and deleted with the <tt>Remove</tt> method. 
 * It is defined with:
 *<table>
 * <tr><td>CATMathAxis2D</td><td><tt> iAxis </tt></td>
 *                <td> The axis of the hyperbola in the space of the surface </td></tr>
 * <tr><td>CATSurface</td><td><tt> iSupport </tt></td>
 *                <td> The surface on which the hyperbola is defined </td></tr>
 * <tr><td>double</td><td><tt> iA</tt></td>
 *                <td> The length between the center and the vertex.</td></tr>
 * <tr><td>double</td><td><tt> iB</tt></td>
 *                <td> The distance between focus and center <tt>c = sqrt(iA^2+iB^2)</tt></td></tr>
 *</table>
 * The eccentricity is defined by <tt>e = c/iA > 1</tt>.
 * With this definition, the hyperbola is the branch
 * along the positive X corresponding to the implicit equation
 *       <tt>X^2/(iA^2) - Y^2/(iB^2) = 1</tt>
 * To define the limits of the hyperbola, consider the parameter <tt>t</tt> such that:
 *   <tt>X(t) = a*cosh(t), Y(t) = b*sinh(t)</tt>  , where  X and Y are relative to <tt>iAxis</tt>.
 *  <br>Notice that this parameterization is not the internal parameterization.
 */
class ExportedByCATGMGeometricInterfaces CATPHyperbola : public CATPCurve
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
 * Modifies the characteristics of <tt>this</tt> CATPHyperbola.
 * @param iAxis
 * The axis of the hyperbola in the surface space.
 * @param iA 
 * The length between the center and the vertex.
 * @param iB
 * The distance between focus and center <tt>c = sqrt(iA^2+iB^2)</tt>.
 * @param iLimits
 * An array [2] of the parameter values definining the limitations. If <tt>NULL</tt>, the hyperbola is unlimited.
 * @param iSupport
 * A pointer to the surface on which the hyperbola is defined.
 */
  virtual void Set (const CATMathAxis2D   &iAxis2D,
		    const double          &iA,
		    const double          &iB,
		    const double          *iLimits,
		    CATSurface*       iSupport) = 0 ;

  
//CAA_Exposed
/**
 * Returns the canonical lengths of <tt>this</tt> CATPHyperbola.
 * @param ioA 
 * The length between the center and the vertex.
 * @param ioB
 * The distance between focus and center <tt>c = sqrt(iA^2+iB^2)</tt>.
 * @param iLimits
 */
  virtual void GetCanonicalParams(double &ioA,
				  double &ioB) const = 0 ; 

/**
 * Returns the low and high limitations of <tt>this</tt> CATPHyperbola.
 * @param ioLowLimitation
 * The parameter value of the first limitation of <tt>this</tt> CATPHyperbola.
 * @param ioHighLimitation
 * The parameter value of the second limitation of <tt>this</tt> CATPHyperbola.
 */
  virtual void GetExtremities(double &ioLowLimitation, double &ioHighLimitation) const = 0 ;

  //CAA_Exposed
/** 
 * Modifies the reference axis of <tt>this</tt> CATPHyperbola.
 * @param iAxis
 * The axis of the hyperbola in the surface space.
 */
  virtual void SetReferenceAxis(const CATMathAxis2D &iAxis2D) = 0;

  //CAA_Exposed
/** 
 * Modifies the canonical lengths of <tt>this</tt> CATPHyperbola.
 * @param iA 
 * The length between the center and the vertex.
 * @param iB
 * The distance between focus and center <tt>c = sqrt(iA^2+iB^2)</tt>.
 */
  virtual void SetCanonicalParams(const double &iA,
				  const double &iB) = 0 ;

/**
 * Modifies the low and high Limimitations of <tt>this</tt> CATPHyperbola.
 * @param iLowParam
 * The parameter value of the first limitation of <tt>this</tt> CATPHyperbola.
 * @param iHighParam
 * The parameter value of the second limitation of <tt>this</tt> CATPHyperbola.
 */
  virtual void SetExtremities(const double &iLowParam, const double &iHighParam) = 0 ;


/**
 * Returns the reference axis of <tt>this</tt> CATPHyperbola.
 * @param ioAxis
 * The axis of the hyperbola in the surface space.
 */
  virtual void GetReferenceAxis(CATMathAxis2D &ioAxis2D) const = 0;

};

CATDeclareHandler(CATPHyperbola,CATPCurve);

#endif


