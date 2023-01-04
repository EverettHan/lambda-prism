#ifndef CATEllipse_h
#define CATEllipse_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
#include <stdio.h>
#include "CATConic.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATEllipse ;
#else
extern "C" const IID IID_CATEllipse ;
#endif

//CAA_Exposed  CATIGemEllipse
/**
* Interface representing an ellipse.
 *<br>A CATEllipse is created by the <tt>CreateEllipse</tt>
 * method of the <tt>CATGeoFactory</tt> interface 
 * and deleted with the <tt>Remove</tt> method. 
 *<br>A CATEllipse is defined with:
 *<table>
 * <tr><td>CATMathPlane</td><td><tt>(O,U,V) </tt></td>
 *                 <td> The axis system</td></tr>
 * <tr><td>double</td><td><tt>A</tt></td>
 *                 <td> The half length of the major axis</td></tr>
 * <tr><td>double</td><td><tt>B</tt></td>
 *                 <td> The half length of the minor axis</td></tr>
 * <tr><td>CATAngle</td><td><tt> iStart </tt></td>
 *                 <td> The low angle limitation </td></tr>
 * <tr><td>CATAngle</td><td><tt> iEnd </tt></td>
 *                 <td> The high angle limitation</td></tr>
 *</table>
 * with <tt> 0 <= iStart < CAT2PI</tt>, 
 * <tt>iStart < iEnd <= iStart + CAT2PI</tt>, <tt>B <= A</tt>.
 * The direction of the major axis is the first direction of the plane.
 * The angles are measured from the major axis.<br> 
 * The parametric equation of the ellipse on its plane is:
 * <tt>X=a*cos(theta), Y=b*sin(theta)</tt>.
 * Notice that the CATSurParam (on the ellipse plane) associated with (X,Y) 
 * may not correspond to <tt>theta</tt>. So, do not make any assumption on the
 * internal ellipse parameterization.<br>
 * The ellipse equation
 * in its axis system is <tt>X&sup2;/A&sup2; + Y&sup2;/B&sup2; = 1</tt>.
 */
class ExportedByCATGMGeometricInterfaces CATEllipse : public CATConic
{
  CATDeclareInterface;

public:
//CAA_Exposed
/**
 * Returns the half length of the ellipse major axis.
 * @return
 * The half length of the major axis
 */
  virtual double GetMajorAxis()const = 0 ;

//CAA_Exposed
/**
 * Returns the half length of the ellipse minor axis.
 * @return
 * The half length of the minor axis
 */
  virtual double GetMinorAxis()const = 0 ;

//CAA_Exposed
/**
 * Modifies the half length of the ellipse major axis.
 * @param iNewMajorAxis
 * The half length of the major axis.
 */
  virtual void SetMajorAxis(double iNewMajorAxis) = 0 ;

  //CAA_Exposed
/**
 * Modifies the half length of the ellipse minor axis.
 * @param iNewMinorAxis
 * The half length of the minor axis.
 */
  virtual void SetMinorAxis(double iNewMinorAxis)= 0 ;

  //CAA_Exposed
/**
 * Returns the start limitation of the ellipse arc angle.
 * @return
 * The first limitation angle. 
 */
  virtual CATAngle GetStartAngle() const = 0 ;
  
  //CAA_Exposed
/**
 * Returns the end limitation of the ellipse arc angle.
 * @return
 * The last limitation angle. 
 */
  virtual CATAngle GetEndAngle() const = 0 ;

  //CAA_Exposed
/**
 * Modifies the ellipse characteristics.
 * @param iMajorAxis
 * The half length of the major axis.
 * @param iMinorAxis
 * The half length of the minor axis.
 * @param iSupport
 * The new plane. The ellipse center will be at the origin of <tt>iSupport</tt>.
 * @param iStart
 * The first angle (in radian) limitation, measured from the first direction of the plane.
 * @param iEnd
 * The end angle (in radian) limitation, measured from the first direction of the plane.
 */
  virtual void Set (const double   iMajorAxis, 
		    const double   iMinorAxis, 
		    const CATMathPlane      & iSupport,
		    const CATAngle            iStart,
		    const CATAngle            iEnd               ) = 0 ; 

};
  CATDeclareHandler(CATEllipse,CATConic);

#endif
