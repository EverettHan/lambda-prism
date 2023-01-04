#ifndef CATIPGMPolyhedrBodiesItfBldr_h
#define CATIPGMPolyhedrBodiesItfBldr_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMPolyhedrBodiesItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework PolyhedralBodies.
 */
class ExportedByCATGMModelInterfaces CATIPGMPolyhedrBodiesItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
};

/**
 * Returns the factory of implementations of interfaces for the framework PolyhedralBodies.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMPolyhedrBodiesItfBldr *CATCGMGetPolyhedrBodiesItfBldr();

#endif /* CATIPGMPolyhedrBodiesItfBldr_h */
