#ifndef CATPEllipse_h
#define CATPEllipse_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATPCurve.h"
#include "CATMathDef.h"
class CATSurParam ;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPEllipse ;
#else
extern "C" const IID IID_CATPEllipse ;
#endif
	//CAA_Exposed CATIGemPEllipse
/**
 * Interface representing an ellipse in the space of a surface.
 *<br> The CATPEllipse is created by the <tt>CreatePEllipse</tt>
 * method of the <tt>CATGeoFactory</tt> interface 
 * and deleted with the <tt>Remove</tt> method.
 *<br>A CATPEllipse is defined with:
 *<table>
 * <tr><td>CATSurface</td><td><tt>Sur </tt></td>
 *                 <td> The underlying surface</td></tr>
 * <tr><td>double</td><td><tt>A</tt></td>
 *                 <td> The half length of the major axis</td></tr>
 * <tr><td>double</td><td><tt>B</tt></td>
 *                 <td> The half length of minor axis </td></tr>
 * <tr><td>CATAngle</td><td><tt> iOffset </tt></td>
 *                 <td> The angle between the surface first direction and the
 *                       major axis</td></tr>
 * <tr><td>CATAngle</td><td><tt> iStart </tt></td>
 *                 <td> The low angle limitation </td></tr>
 * <tr><td>CATAngle</td><td><tt> iEnd </tt></td>
 *                 <td> The high angle limitation</td></tr>
 *</table>
 * with <tt> 0 <= iStart < CAT2PI</tt>, 
 * <tt>iStart < iEnd <= iStart + CAT2PI</tt>, <tt>B <= A</tt>.
 * The <tt>iStart</tt> and <tt>iEnd</tt> angles are measured
 * from the major axis.<br> 
 * The parametric equation of the ellipse in the surface is:
 * <tt>U=a*cos(theta), V=b*sin(theta)</tt>.
 * Notice that the CATSurParam associated with (U,V) 
 * may not correspond to <tt>theta</tt>. So, do not make any assumption on the
 * internal ellipse parameterization.<br>
 * The ellipse equation
 * in its axis system is <tt>U&sup2;/A&sup2; + V&sup2;/B&sup2; = 1</tt>.
 */
class ExportedByCATGMGeometricInterfaces CATPEllipse : public CATPCurve
{
  CATDeclareInterface;

public :

/**
 * Returns the half length of the major axis.
 *@return
 * The half length of the major axis.
 */
  virtual double GetMajorAxis() const = 0 ;

/**
 * Returns the half length of minor axis.
 *@return
 * The half length of the minor axis.
 */
  virtual double GetMinorAxis() const = 0 ;

/**
 * Returns the angle between the surface first direction and the major axis
 * of <tt>this</tt> CATPEllipse.
 * @return
 * The angle.
 */
  virtual CATAngle GetOffsetAngle() const = 0 ;

/**
 * Returns the center of a CATPEllipse.
 * @param ioCenter
 * The center.
 */
  virtual void GetCenter(CATSurParam &ioCenter) const = 0 ;

/**
 * Returns the low angle limitation of <tt>this</tt> CATPEllipse.
 * @return
 * The first limitation angle. 
 */
  virtual CATAngle GetStartAngle() const = 0 ;

/**
 * Returns the high angle limitation of <tt>this</tt> CATPEllipse.
 * @return
 * The end limitation angle. 
 */
  virtual CATAngle GetEndAngle() const = 0 ;

/**
 * Modifies the characteristics of <tt>this</tt> CAPEllipse.
 * @param iMajorAxis
 * The new value.
 * @param iMinorAxis
 * The new value.
 * @param iOffsetAngle
 * The new offset angle value.
 * @param iCenter
 * The new center.
 * @param iStart
 * The first limitation angle.
 * @param iEnd
 * The end limitation angle.
 */
  virtual void Set (const double iMajorAxis,
		    const double iMinorAxis,	
		    const CATAngle          iOffsetAngle,
		    const CATSurParam      &iCenter,
		    const CATAngle          iStart,
		    const CATAngle          iEnd,
		          CATSurface*       iSupport) = 0 ;
/** 
 * Modifies the half length of the major axis of <tt>this</tt> CATPEllipse.
 * @param iNewMajorAxis
 * The new value.
 */
  virtual void SetMajorAxis(const double iNewMajorAxis) = 0 ;

/** 
 * Modifies the half length of minor axis of <tt>this</tt> CATPEllipse.
 * @param iNewMinorAxis
 * The new value.
 */
  virtual void SetMinorAxis(const double iNewMinorAxis) = 0 ;
 
/**
 * Modifies the angle between the surface first direction and the major axis
 * of <tt>this</tt> CATPEllipse.
 * @param iNewOffsetAngle
 * The new angle value.
 */
  virtual void SetOffsetAngle(const CATAngle iNewOffsetAngle) = 0 ;

/**
 * Modifies the center of a CATPEllipse.
 * @param iNewCenter
 * The new center.
 */
  virtual void SetCenter(const CATSurParam & iNewCenter) = 0 ;

/**
 * Returns the center of a CATPEllipse.
 * Use preferably the signature which returns the center in output argument.
 * @return
 * The center.
 */
  virtual CATSurParam GetCenter() const = 0 ;

};
  CATDeclareHandler(CATPEllipse,CATPCurve);

#endif
