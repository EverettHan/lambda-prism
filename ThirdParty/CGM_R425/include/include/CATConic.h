#ifndef CATConic_h
#define CATConic_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
#include <stdio.h>
#include "CATCurve.h"
#include "CATMathPlane.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATConic ;
#else
extern "C" const IID IID_CATConic ;
#endif

/**
 * Base interface representing the conics.
 *<br>A CATConic is a planar geometrical curve of the second order,
 * that can be produced by intersecting a plane with a cone.
 * Its axis system is defined by a CATMathPlane: the center of
 * the conics is the plane origin and its axes those of the plane.
 */
class ExportedByCATGMGeometricInterfaces CATConic : public CATCurve
{
  CATDeclareInterface;

public:

/**
 * Returns the axis system of <tt>this</tt> CATConic.
 * @param ioSupport
 * The plane of <tt>this</tt> conics.
 */
virtual void GetSupport(CATMathPlane &ioSupport)const =0;

/**
 * Returns the eccentricity of <tt>this</tt> CATConic.
 * @return
 * The eccentricity.
 */
virtual double GetEccentricity()const =0;

/**
 * Retrieves the center of <tt>this</tt> CATConic.
 * @param ioCenter
 * The center.
 */
virtual void GetOrigin (CATMathPoint &ioCenter) const =0;

/**
 * Modifies the center of <tt>this</tt> CATConic.
 * @param iNewCenter
 * The new center.
 *<br> The plane of the CATConics is translated to have its origin at
 * the point <tt>iNewCenter</tt>.
 */
virtual void SetOrigin(const CATMathPoint & iNewCenter)=0;

/**
 * Returns the axis system of <tt>this</tt> CATConic.
 * @return
 * The plane of <tt>this</tt> CATConic.
 */
virtual CATMathPlane GetAxis()const =0;

/**
 * Retrieves the center of <tt>this</tt> CATConic.
 * @return
 * The center.
 */
virtual CATMathPoint GetOrigin()const =0;
};

CATDeclareHandler(CATConic,CATCurve);

#endif
