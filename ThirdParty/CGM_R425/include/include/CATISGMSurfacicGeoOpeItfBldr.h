#ifndef CATISGMSurfacicGeoOpeItfBldr_h
#define CATISGMSurfacicGeoOpeItfBldr_h

#include "CATSGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"

class CATISGMGeoFilling;
class CATGeoFactory;
class CATSurface;

extern ExportedByCATSGMOperatorsInterfaces IID IID_CATISGMSurfacicGeoOpeItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework SurfacicGeoOperators.
 */
class ExportedByCATSGMOperatorsInterfaces CATISGMSurfacicGeoOpeItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATISGMGeoFilling *CATSGMCreateGeoFilling(
    CATGeoFactory *iFactory,
    CATSurface *iInitialSurface) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework SurfacicGeoOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATISGMSurfacicGeoOpeItfBldr *CATSGMGetSurfacicGeoOpeItfBldr();

#endif /* CATISGMSurfacicGeoOpeItfBldr_h */
