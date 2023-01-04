/*-*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
// CATDirectionalSurface Interface
//-----------------------------------------------------------------------------
// Mar. 99   Creation                                     NDN
//=============================================================================
//
// Usage notes:
//
//=============================================================================
#ifndef CATDirectionalSurface_h
#define CATDirectionalSurface_h
/**
 * Interface representing a Directional surface.
 *<br> The CATDirectionalSurface is created by the <tt>CreateDirectionalSurface</tt>
 * method of the <tt>CATGeoFactory</tt> interface. 
 */

class CATPCurve;
class CATGeoFactory;
class CATCrvLimits;

#include "CATBaseUnknown.h"
#include "CATSurface.h"
#include "ExportedByCATGMGeometricInterfaces.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATDirectionalSurface;
#else
extern "C" const IID IID_CATDirectionalSurface;
#endif

class ExportedByCATGMGeometricInterfaces CATDirectionalSurface : public CATSurface
{
  CATDeclareInterface;

 public:

/**
 * Return the PCurve used to generate the CATDirectionalSurface.
 */
	virtual CATPCurve * GetProfile () const =0;

/**
 * Updates CATDirectionalSurface Data for Extrapolation.
 */
  virtual void Extrapolation(const CATCrvLimits & NewLimitsOnProfile) =0;

/**
 * Get the limits used on the PCurve used to generate the CATDirectionalSurface.
 */
  virtual void GetLimitsForProfileCurve(CATCrvLimits & oLimitsForProfileCurve) const =0;

/**
 * Return the angle used to generate the CATDirectionalSurface.
 */
  virtual CATAngle GetAngle() const =0;
};
  CATDeclareHandler(CATDirectionalSurface, CATSurface);

#endif
