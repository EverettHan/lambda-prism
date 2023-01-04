#ifndef CATIPGMTopologicalOpeGMModItfBldr_h
#define CATIPGMTopologicalOpeGMModItfBldr_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATBoolean.h"

class CATPGMChain;
class CATGeoFactory;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopologicalOpeGMModItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework TopologicalOperators in GMModelInterfaces.
 */
class ExportedByCATGMModelInterfaces CATIPGMTopologicalOpeGMModItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATPGMChain *CATPGMCreateCGMTopoChain(CATGeoFactory *ifactory)=0;

  virtual CATBoolean CATPGMWriteCGMTopoChain(CATPGMChain * iChain, char* iFileName)=0;
};

/**
 * Returns the factory of implementations of interfaces for the framework TopologicalOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMModelInterfaces CATIPGMTopologicalOpeGMModItfBldr *CATCGMGetTopologicalOpeGMModItfBldr();

#endif /* CATIPGMTopologicalOpeGMModItfBldr_h */
