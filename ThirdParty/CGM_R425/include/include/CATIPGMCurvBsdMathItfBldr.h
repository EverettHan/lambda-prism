#ifndef CATIPGMCurvBsdMathItfBldr_h
#define CATIPGMCurvBsdMathItfBldr_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMCurvBsdMathItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework CurveBasedMathematics.
 */
class ExportedByCATGMModelInterfaces CATIPGMCurvBsdMathItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
};

/**
 * Returns the factory of implementations of interfaces for the framework CurveBasedMathematics.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMCurvBsdMathItfBldr *CATCGMGetCurvBsdMathItfBldr();

#endif /* CATIPGMCurvBsdMathItfBldr_h */
