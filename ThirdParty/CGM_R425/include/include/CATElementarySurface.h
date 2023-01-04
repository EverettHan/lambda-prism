#ifndef CATElementarySurface_h
#define CATElementarySurface_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
#include <stdio.h>
#include "CATSurface.h"
#include "CATMathAxis.h"
#include "CATMathPoint.h"
class CATMathVector;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATElementarySurface ;
#else
extern "C" const IID IID_CATElementarySurface ;
#endif

/**
 * Interface representing a canonical surface of revolution.
 *<br>The common feature of all canonical surfaces of revolution is the revolution
 * axis. The revolution direction is the third direction of the axes system, and
 * the angle reference is the first direction of the axes system.
 */
class ExportedByCATGMGeometricInterfaces CATElementarySurface : public CATSurface
{
  CATDeclareInterface;

public:

/**
 * Retrieves the axes system associated with <tt>this</tt> CATElementarySurface.
 * @param ioMathAxis
 * The axis defining the elementary surface. In peculiar, 
 * the revolution direction is the third direction of the axes system, and
 * the angle reference is the first direction of the axes system.
 */
virtual void GetAxis(CATMathAxis &ioMathAxis) const =0;

/**
 * Retrieves the origin and the three directions of the axes system associated 
 * with <tt>this</tt> CATElementarySurface.
 * @param ioOrigin
 * The origin of the axis.
 * @param ioFirstDirection
 * The first normalized direction of the axes system.
 * @param ioSecondDirection
 * The second ortho-normalized direction of the axes system.
 * @param ioThirdDirection
 * The third ortho-normalized direction of the axes system. This is the revolution direction.
 */
virtual void GetAxis(CATMathPoint  &ioOrigin  ,
		     CATMathVector &ioFirstDirection,
		     CATMathVector &ioSecondDirection,
		     CATMathVector &ioThirdDirection) const =0;

/**
 * Modifies the axes system associated with <tt>this</tt> CATElementarySurface.
 * @param ioNewOrigin
 * The new origin of the axis.
 */
virtual void SetOrigin(const CATMathPoint & ioNewOrigin)=0;


/**
 * Retrieves the axes system associated with <tt>this</tt> CATElementarySurface. The signature
 * which returns the axes system in output argument should be preferably used.
 * @return
 * The axes system.
 */
virtual CATMathAxis GetAxis()const =0;

};

CATDeclareHandler(CATElementarySurface,CATSurface);

#endif
