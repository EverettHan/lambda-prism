#ifndef CATSphere_h
#define CATSphere_h
// COPYRIGHT DASSAULT SYSTEMES  1999
/**
* @CAA2Level L1
* @CAA2Usage U3
*/ 
#include "CATBaseUnknown.h"
#include "CATElementarySurface.h"
#include "CATMathDef.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATSphere ;
#else
extern "C" const IID IID_CATSphere ;
#endif

/**
* Interface representing a geometric sphere.
* <br> The CATSphere is created by the <tt>CreateSphere</tt>
* method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method. 
* A sphere is defined by an axis and a radius. The third direction of the axis is the rotation
* axis.
* A piece of a full sphere is defined by limiting the meridian and parallel angles. 
* The meridian planes pass through the axis third direction, 
* the parallel planes are orthogonal to the axis third direction. A piece of a sphere 
* is defined by:
* <ul>
* <li>Meridian start angle: 
* the low angle value of the meridians. Positive angles are defined by the right-hand rule. 
* <tt>Meridian start angle < Meridian end angle</tt>. 
* If specified angles are too large, the surface is swept around 2*Pi.</li>
* <li>Meridian end angle: 
* the high angle value of the meridians. Positive angles are defined by the right-hand rule.
* <tt>iMeridianStart < iMeridianEnd</tt>. 
* If specified angles are too large, the surface is swept around 2*Pi.</li>
* <li>Parallel start angle: 
* the low angle value of the parallels. Positive angles are in the 
* direction of the sphere axis. Angles are counted from 
* the radius in the plane
* defined by the first and second direction of the sphere axis. 
* <tt>iParallelStart >= -Pi/2 </tt>; <tt>iParallelStart < iParallelEnd </tt> </li>
* <li>Parallel end angle: 
* the high angle value of the parallels. Positive angles are in the 
* direction of the sphere axis. Angles are counted from 
* the radius in the plane
* defined by the first and second direction of the sphere axis. 
* <tt>iParallelEnd <= Pi/2</tt>; <tt>iParallelStart < iParallelEnd </tt></li>
* </ul>
*/
class ExportedByCATGMGeometricInterfaces CATSphere : public CATElementarySurface
{
	CATDeclareInterface;

public:
	/**
	* Returns the radius of the CATSphere. 
	* @return
	* The radius value.
	*/
	virtual double GetRadius()const =0;

	/**
	* Returns the low limitation of the meridians existence of <tt>this</tt> CATSphere.
	* @return
	* The low angle value of the meridians.
	*/
	virtual CATAngle GetMeridianStartAngle() const =0;

	/**
	* Returns the high limitation of the meridians existence of <tt>this</tt> CATSphere.
	* @return
	* The high angle value of the meridians.
	*/
	virtual CATAngle GetMeridianEndAngle() const=0 ;

	/**
	* Returns the low limitation of the parallels existence of <tt>this</tt> CATSphere.
	* @return
	* The low angle value of the parallels.
	*/
	virtual CATAngle GetParallelStartAngle() const=0 ;

	/**
	* Returns the high limitation of the parallels existence of <tt>this</tt> CATSphere.
	* @return
	* The high angle value of the parallels.
	*/
	virtual CATAngle GetParallelEndAngle() const=0 ;

	/**
	* Modifies all the characteristics of <tt>this</tt> CATSphere.
	* @param iAxis
	* The new axes system.
	* @param iRadius
	* The new radius.
	* @param iMeridianStart
	* The low angle value of the meridians.
	* @param iMeridianEnd
	* The high angle value of the meridians.
	* @param iParallelStart
	* The low angle value of the parallels.
	* @param iParallelEnd
	* The high angle value of the parallels.
	*/
	virtual void Set(const CATMathAxis       &iAxis,
		const double  iRadius,
		const CATAngle           iMeridianStart,
		const CATAngle           iMeridianEnd, 
		const CATAngle           iParallelStart,
		const CATAngle           iParallelEnd)=0 ; 

	/**
	* Modifies the radius of <tt>this</tt> CATSphere.
	* @param iRadius
	* The new radius value.
	*/
	virtual void SetRadius(double iRadius)=0;

};

CATDeclareHandler(CATSphere,CATElementarySurface);

#endif
