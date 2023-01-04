#ifndef CATIPGMCGMV5InteropGMModItfBldr_h
#define CATIPGMCGMV5InteropGMModItfBldr_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATBoolean.h"

/*
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
*/

class CATICGMObject;
class CATICGMContainer;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMCGMV5InteropGMModItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework NewTopologicalObjects.
 */
class ExportedByCATGMModelInterfaces CATIPGMCGMV5InteropGMModItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATBoolean CATBackCGMCompatibility_CATPGMIsCompatible(CATICGMObject *iObject) = 0;

  virtual CATBoolean CATBackCGMCompatibility_CATPGMIsCompatible(CATICGMContainer* iCGMContainer) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework NewTopologicalObjects.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMModelInterfaces CATIPGMCGMV5InteropGMModItfBldr *CATCGMGetCGMV5InteropGMModItfBldr();

#endif /* CATIPGMCGMV5InteropGMModItfBldr_h */
