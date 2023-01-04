#ifndef CATIPGMCurvBsdInfraItfBldr_h
#define CATIPGMCurvBsdInfraItfBldr_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMCurvBsdInfraItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework CurveBasedInfrastructure.
 */
class ExportedByCATGMModelInterfaces CATIPGMCurvBsdInfraItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
};

/**
 * Returns the factory of implementations of interfaces for the framework CurveBasedInfrastructure.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMCurvBsdInfraItfBldr *CATCGMGetCurvBsdInfraItfBldr();

#endif /* CATIPGMCurvBsdInfraItfBldr_h */
