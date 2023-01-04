#ifndef CATCircle_h
#define CATCircle_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
#include "CATConic.h"
#include "CATMathDef.h"
class CATMathPlane ;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCircle ;
#else
extern "C" const IID IID_CATCircle ;
#endif

//CAA_Exposed  CATIGemCircle
/**
 * Interface representing a geometric circle.
 *<br> The CATCircle is created by the <tt>CreateCircle</tt>
 * method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method.
 *<br>A CATCircle is defined with:
 *<table>
 * <tr><td>CATMathPlane</td><td><tt> (O,U,V) </tt></td>
 *                <td> The axis system </td></tr>
 * <tr><td>double</td><td><tt> R </tt></td>
 *                <td> The radius           </td></tr>
 * <tr><td>CATAngle</td><td><tt> iStart </tt></td>
 *                 <td> The low angle limitation </td></tr>
 * <tr><td>CATAngle</td><td><tt> iEnd </tt></td>
 *                 <td> The high angle limitation</td></tr>
 *</table>
 * with <tt> 0 <= iStart < CAT2PI</tt>, 
 * <tt>iStart < iEnd <= iStart + CAT2PI</tt>. The angles (in radian) are measured
 * from the first direction of the plane.
 */
class ExportedByCATGMGeometricInterfaces CATCircle : public CATConic
{
  CATDeclareInterface;

public:
	//CAA_Exposed
/**
 * Returns the circle radius.
 * @return
 * The radius.
 */
  virtual double GetRadius()const =0;

//CAA_Exposed
/**
 * Returns the start limitation of the arc circle angle.
 * @return
 * The first angle (in radian) limitation, measured from the first direction of the plane.
 */
  virtual CATAngle GetStartAngle() const = 0 ;

//CAA_Exposed
/**
 * Returns the end limitation of the arc circle angle.
 * @return
 * The end angle (in radian) limitation, measured from the first direction of the plane.
 */  
  virtual CATAngle GetEndAngle() const = 0 ;

//CAA_Exposed
/**
 * Modifies the circle characteristics.
 * @param iRadius
 * The new radius.
 * @param iSupport
 * The new plane. The circle origin will be at the origin of <tt>iSupport</tt>.
 * @param iStart
 * The first angle (in radian) limitation, measured from the first direction of the plane.
 * @param iEnd
 * The end angle (in radian) limitation, measured from the first direction of the plane.
 */  
  virtual void Set (const double   iRadius, 
		    const CATMathPlane      & iSupport,
		    const CATAngle            iStart,
		    const CATAngle            iEnd              ) = 0 ; 

//CAA_Exposed
/**
 * Modifies the circle radius.
 * @param iNewRadius
 * The new radius.
 */
  virtual void SetRadius(double iNewRadius)=0;

};
  CATDeclareHandler(CATCircle,CATConic);

#endif
