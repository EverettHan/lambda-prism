#ifndef CATIPGMSurfacicInfraItfBldr_h
#define CATIPGMSurfacicInfraItfBldr_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSurfacicInfraItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework SurfacicInfrastructure.
 */
class ExportedByCATGMModelInterfaces CATIPGMSurfacicInfraItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
};

/**
 * Returns the factory of implementations of interfaces for the framework SurfacicInfrastructure.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMSurfacicInfraItfBldr *CATCGMGetSurfacicInfraItfBldr();

#endif /* CATIPGMSurfacicInfraItfBldr_h */
