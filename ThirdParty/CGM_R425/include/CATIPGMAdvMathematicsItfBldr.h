#ifndef CATIPGMAdvMathematicsItfBldr_h
#define CATIPGMAdvMathematicsItfBldr_h

#include "CATAdvancedMathematics.h"
#include "CATBaseUnknown.h"

extern ExportedByCATAdvancedMathematics const IID IID_CATIPGMAdvMathematicsItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework AdvancedMathematics.
 */
class ExportedByCATAdvancedMathematics CATIPGMAdvMathematicsItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
};

/**
 * Returns the factory of implementations of interfaces for the framework AdvancedMathematics.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATAdvancedMathematics CATIPGMAdvMathematicsItfBldr *CATCGMGetAdvMathematicsItfBldr();

#endif /* CATIPGMAdvMathematicsItfBldr_h */
