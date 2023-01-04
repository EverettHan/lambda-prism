#ifndef CATIPGMSubdApproxItfBldr_h
#define CATIPGMSubdApproxItfBldr_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSubdApproxItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework CATSubdivisionApproximation.
 */
class ExportedByCATGMModelInterfaces CATIPGMSubdApproxItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
};

/**
 * Returns the factory of implementations of interfaces for the framework CATSubdivisionApproximation.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMSubdApproxItfBldr *CATCGMGetSubdApproxItfBldr();

#endif /* CATIPGMSubdApproxItfBldr_h */
