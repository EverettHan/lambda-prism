#ifndef CATRevolutionSurface_h
#define CATRevolutionSurface_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATSurface.h"
#include "CATMathDef.h"
#include "CATIACGMLevel.h"
class CATCurve ;
class CATCrvLimits ;
class CATMathAxis ;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATRevolutionSurface ;
#else
extern "C" const IID IID_CATRevolutionSurface ;
#endif

/**
 * Interface representing a revolution surface.
 *<br> The CATRevolutionSurface is created by the <tt>CreateRevolutionSurface</tt>
 * method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method. 
 *<br>A CATRevolutionSurface is the surface generated by the revolution of a
 * generative curve around a direction.
 *<table>
 * <tr><td>CATCurve</td><td><tt> Profile </tt></td>
 *                <td> The curve to rotate </td></tr>
 * <tr><td>CATMathAxis</td><td><tt> Axis </tt></td>
 *                <td> The axes system whose third direction is the rotation direction </td></tr>
 * <tr><td>CATAngle</td><td><tt> StartAngle </tt></td>
 *                <td> The low limitation of the rotation </td></tr>
 * <tr><td>CATAngle</td><td><tt> EndAngle </tt></td>
 *                <td> The end limitation of the rotation </td></tr>
 *</table>
 * A CATSurfaceRevolution can be trimmed by the curve limitations in one
 * direction and by a <tt>StartAngle</tt> and <tt>EndAngle</tt> measured 
 * from <tt>Axis</tt> first direction in the other direction.
 */
class ExportedByCATGMGeometricInterfaces CATRevolutionSurface : public CATSurface
{
  CATDeclareInterface;

public :
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Returns a pointer to the generating curve of <tt>this</tt> CATRevolutionSurface.
 * @return
 * The pointer to the generating curve.
 */
  virtual CATCurve* GetProfile()  const = 0  ;

/**
 * Returns a pointer to the generating curve of <tt>this</tt> CATRevolutionSurface.
 * @param ioProfileLimits
 * The limits of the returned generating curve
 * @return
 * The pointer to the generating curve.
 */
  virtual CATCurve* GetProfile(CATCrvLimits & ioProfileLimits)  const = 0  ;

/**
 * Returns the corresponding limitations of given limitations on <tt>this</tt>
 * CATRevolutionSurface along its profile.
 * @param iSurLim
 * The limitation on the surface.
 * @param ioProfileLimits
 * The current limitation along the profile.
 */
  virtual void GetLimitsOnProfile(const CATSurLimits &iSurLim,
                                  CATCrvLimits & ioProfileLimits ) const = 0 ;

/**
 * @nodoc
 * @deprecated V5R14 GetLimitsOnProfile
 * Returns the current limitations of  <tt>this</tt> CATRevolutionSurface along its profile.
 * @param ioProfileLimits
 * The current limitation along the profile, without taking care of mapping.
 */
  virtual void GetProfileLimits( CATCrvLimits & ioProfileLimits ) const = 0 ;

/**
 * Retrieves the CATMathAxis of <tt>this</tt> CATRevolutionSurface.
 * @param ioMathAxis 
 * The axes system.
 */  
  virtual void GetAxis(CATMathAxis &ioMathAxis) const =0;

/**
 * Retrieves the CATMathAxis characteristics of <tt>this</tt> CATRevolutionSurface.
 * @param ioOrigin
 * The origin of the axes system.
 * @param ioFirstDirection
 * The first direction of the axes system.
 * @param ioSecondDirection
 * The second direction of the axes system.
 * @param ioThirdDirection
 * The third direction of the axes system, corresponding to the rotation axis.
 */   
  virtual void GetAxis(CATMathPoint  &ioOrigin  ,
		       CATMathVector &ioFirstDirection,
		       CATMathVector &ioSecondDirection,
		       CATMathVector &ioThirdDirection) const =0;

/**
 * Returns the low limitation of the revolution angle of 
 * <tt>this</tt> CATRevolutionSurface.
 * @return
 * The angle value (in radian) measured from the first direction of <tt>iAxis</tt>.
 */
  virtual CATAngle GetStart()  const = 0 ;

/**
 * Returns the high limitation of the revolution angle of 
 * <tt>this</tt> CATRevolutionSurface.
 * @return
 * The angle value (in radian) measured from the first direction of <tt>iAxis</tt>.
 */ 
  virtual CATAngle GetEnd()  const = 0 ;
 
	/**
	 * Modifies the definition of <tt>this</tt> CATRevolutionSurface.
	 * @param iProfile
	 * The pointer to the new profile curve.
	 * @param iProfileLimits
	 * The new limitations of the profile.
	 * @param iRefAxis
	 * The new axes system.
	 * @param iStart
	 * The new value (in radian) of the low limitation of the rotation.
	 * @param iEnd
	 * The new value (in radian) of the high limitation of the rotation.
	 */
  virtual void Set (       CATCurve* iProfile,
                     const CATCrvLimits & iProfileLimits,
	                 const CATMathAxis &iRefAxis,
	                 const CATAngle &iStart,
	                 const CATAngle &iEnd) = 0 ;








  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * @nodoc
 * Updates CATTabulatedCylinder Data for Extrapolation
 */
  virtual void Extrapolation( const CATLONG32  &iOldNumberOfArcs, const CATLONG32 &iRelativOffset) =0;


/**
 * @nodoc
 * Do not use :
 * Changes the generating curve of a CATRevolutionSurface.
 */
  virtual void SetProfile ( CATCurve* iNewProfile )  = 0;

/**
 * @nodoc
 * Do not use :
 * Changes the axis of a CATRevolutionSurface.
 */ 
  virtual void SetAxis( const CATMathAxis & iRefAxis ) = 0;

/**
 * @nodoc 
 * Do not use :
 * Modifies the low limitation of the revolution angle of 
 * a CATRevolutionSurface.
 */ 
  virtual void SetStart ( const CATAngle iNewStartAngle ) = 0 ;

/**
 * @nodoc
 * Do not use :
 * Modifies the high limitation of the revolution angle of 
 * a CATRevolutionSurface.
 */
  virtual void SetEnd ( const CATAngle iNewEndAngle ) = 0 ;

/**
 * @nodoc
 * Do not use : 
 * Modifies the mean angle of a CATRevolutionSurface (which
 * determines its MaxLimits)
 */

 virtual void SetMeanAngle (const CATAngle iNewMeanAngle ) = 0;
  
/**
 * @nodoc
 * Do not use : 
 * Modifies the unity along the angular parameter (V) :
 * newV = oldV * iScale
 */
 virtual void ScaleAngularParameter(double iScale) = 0;


/////////////////////////////////////////////////////////////////////////////
//                          Methods that will disappear
/////////////////////////////////////////////////////////////////////////////
/**
 * @nodoc
 * Returns the CATMathAxis of a CATRevolutionSurface.
 */ 
  virtual CATMathAxis GetAxis()  const = 0 ;

};
  CATDeclareHandler(CATRevolutionSurface,CATSurface);

#endif
