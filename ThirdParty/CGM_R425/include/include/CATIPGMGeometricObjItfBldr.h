#ifndef CATIPGMGeometricObjItfBldr_h
#define CATIPGMGeometricObjItfBldr_h

#include "ExportedByCATGMGeometricInterfaces.h"
#include "CATBaseUnknown.h"

extern ExportedByCATGMGeometricInterfaces IID IID_CATIPGMGeometricObjItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework GeometricObjects.
 */
class ExportedByCATGMGeometricInterfaces CATIPGMGeometricObjItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
};

/**
 * Returns the factory of implementations of interfaces for the framework GeometricObjects.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMGeometricInterfaces CATIPGMGeometricObjItfBldr *CATCGMGetGeometricObjItfBldr();

#endif /* CATIPGMGeometricObjItfBldr_h */
