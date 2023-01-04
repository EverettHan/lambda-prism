#ifndef CATCylinder_h
#define CATCylinder_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
class CATSurParam ;
#include "CATElementarySurface.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCylinder ;
#else
extern "C" const IID IID_CATCylinder ;
#endif

/**
 * Interface representing a geometric cylinder.
 * <br> The CATCylinder is created by the <tt>CreateCylinder</tt>
 * method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method. 
 * It derives from the <tt>CATElementarySurface</tt> and is defined by:
 * <ul>
 * <li>a CATMathAxis for the axis system in which the third
 * direction is the cylinder direction</li>
 * <li>a double for the radius </li>
 * <li>a CATAngle for the start angle. Positive angles comply with the right-hand rule. If angle values are
 *  too large or inconsistent, a 2*Pi surface is created.</li>
 * <li>a CATAngle for the end angle. Positive angles comply with the right-hand rule. If angle values are
 *  too large or inconsistent, a 2*Pi surface is created.</li>
 * <li>a double for the start limit in the third direction of the CATMathAxis </li>
 * <li>a double for the end limit in the third direction of the CATMathAxis </li>
 * </ul> 
 */
class ExportedByCATGMGeometricInterfaces CATCylinder : public CATElementarySurface
{
  CATDeclareInterface;

public:
/**
 * Returns the radius of <tt>this</tt> CATCylinder.
 * @return
 * The radius value.
 */
  virtual double GetRadius()const =0;

/**
 * Returns the low length limitation of <tt>this</tt> CATCylinder .
 * @return
 * The low length limitation value.
 */ 
  virtual double GetStartLength()const =0;

/**
 * Returns the high limitation on <tt>this</tt> CATCylinder.
 * @return
 * The high length limitation value.
 */ 
  virtual double GetEndLength()const =0;
 
/**
 * Returns the low angle limitation of <tt>this</tt> CATCylinder .
 * @return
 * The low angle limitation value, measured from the first direction of the axes system. 
 * Positive angles comply with the right-hand rule
 */
  virtual CATAngle GetStartAngle()const =0;

/**
 * Returns the high angle limitation of <tt>this</tt> CATCylinder .
 * @return
 * The high angle limitation value, measured from the first direction of the axes system. 
 * Positive angles comply with the right-hand rule
 */ 
  virtual CATAngle GetEndAngle()const =0;
  
/**
 * Modifies the radius of <tt>this</tt> CATCylinder.
 * @param iRadius
 * The new radius value.
 */
  virtual void SetRadius(double iRadius)=0;

/**
 * Modifies the length limitations of <tt>this</tt> CATCylinder.
 * @param iStartLength
 * The start limitation of the length.
 * @param iEndLength
 * The end limitation of the length.
 */ 
  virtual void SetLength(double iStartLength, double iEndLength)=0;
  
/**
 * Modifies the angle limitations of <tt>this</tt> CATCylinder.
 * @param iStartAngle
 * The new start angle limitation. The angle reference is the first direction of the cylinder axis.
 * @param iEndAngle
 * The new end angle limitation. The angle reference is the first direction of the cylinder axis.
 */ 
  virtual void SetAngle(CATAngle iStartAngle, CATAngle iEndAngle)=0;




//#if defined ( CATIAV5R14 )
 /** @nodoc */
  virtual void GetCylinderParam(double & iUnitU,double & iMinParam,double & iStartParam,double & iEndParam) = 0;
 /** @nodoc */
  virtual void SetCylinderParam(double iUnitU,double iMinParam,double iStartParam,double iEndParam) = 0;
//#endif

};
  CATDeclareHandler(CATCylinder,CATElementarySurface);

#endif
