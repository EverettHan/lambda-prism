#ifndef CATPCircle_h
#define CATPCircle_h

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
extern ExportedByCATGMGeometricInterfaces IID IID_CATPCircle ;
#else
extern "C" const IID IID_CATPCircle ;
#endif
	//CAA_Exposed CATIGemPCircle
/**
 * Interface representing a circle in the space of a surface.
 *<br>A CATPCircle is created by the <tt>CreatePCircle</tt>
 * method of the <tt>CATGeoFactory</tt> interface
 * and deleted with the <tt>Remove</tt> method
 *<br>A CATPCircle is defined with:
 *<table>
 * <tr><td>CATSurface</td><td><tt> Sur </tt></td>
 *               <td> The underlying surface </td></tr>
 * <tr><td>double</td><td><tt> R </tt></td>
 *               <td> The radius</td></tr>
 * <tr><td>CATAngle</td><td><tt> iStart </tt></td>
 *               <td> The low angle limitation </td></tr>
 * <tr><td>CATAngle</td><td><tt> iEnd </tt></td>
 *               <td> The high angle limitation</td></tr>
 *</table>
 * with <tt> 0 <= iStart < CAT2PI</tt>, 
 * <tt>iStart < iEnd <= iStart + CAT2PI</tt>. The angles (in radian) are measured
 * from the first direction of the surface.
 */
class ExportedByCATGMGeometricInterfaces CATPCircle : public CATPCurve
{
  CATDeclareInterface;

public :
	//CAA_Exposed
/**
 * Returns the radius of <tt>this</tt> CATPCircle.
 * @return
 * The radius.
 */
  virtual double GetRadius() const = 0 ;

  	//CAA_Exposed
/**
 * Returns the center of <tt>this</tt> CATPCircle.
 * @param ioCenter
 * The center.
 */
  virtual void GetCenter(CATSurParam &ioCenter) const = 0 ;

  	//CAA_Exposed
/**
 * Returns the low limitation angle of <tt>this</tt> CATPCircle.
 * @return
  * The first angle (in radian) limitation, measured from the first direction of the surface.
 */
  virtual CATAngle GetStartAngle() const = 0 ;

  	//CAA_Exposed
/**
 * Returns the high limitation angle of <tt>this</tt> CATPCircle.
  * @return
  * The end angle (in radian) limitation, measured from the first direction of the surface.
 */
  virtual CATAngle GetEndAngle() const = 0 ;
  
  	//CAA_Exposed
/**
 * Modifies the characteristics of <tt>this</tt> CATPCircle.
 * @param iRadius
 * The new value of the radius.
 * @param iNewCenter
 * The new center.
 * @param iStart
 * The first angle (in radian) limitation, measured from the first direction of the surface.
 * @param iEnd
 * The end angle (in radian) limitation, measured from the first direction of the surface.
 * param iSupport
 * A pointer to the underlying surface.
 */
  virtual void Set (const double   iRadius,
		    const CATSurParam       & iCenter,
		    const CATAngle            iStart,
		    const CATAngle            iEnd,
		          CATSurface*         iSupport)  = 0 ;

  	//CAA_Exposed
/**
 * Modifies the radius of <tt>this</tt> CATPCircle.
 * @param iRadius
 * The new value of the radius.
 */
  virtual void SetRadius(const double iNewRadius) = 0 ;
 
  	//CAA_Exposed
/**
 * Modifies the center of <tt>this</tt> CATPCircle.
 * @param iNewCenter
 * The new center.
 */
  virtual void SetCenter(const CATSurParam & iNewCenter) = 0 ;

//Deprecated
/** @nodoc */
  virtual CATSurParam GetCenter() const = 0 ;
};
  CATDeclareHandler(CATPCircle,CATPCurve);

#endif
