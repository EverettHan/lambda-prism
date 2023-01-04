#ifndef CATIPGMGeomObjCGMItfBldr_h
#define CATIPGMGeomObjCGMItfBldr_h

#include "ExportedByCATGeometricObjectsCGM.h"
#include "CATBaseUnknown.h"

extern ExportedByCATGeometricObjectsCGM IID IID_CATIPGMGeomObjCGMItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework GeometricObjectsCGM.
 */
class ExportedByCATGeometricObjectsCGM CATIPGMGeomObjCGMItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
};

/**
 * Returns the factory of implementations of interfaces for the framework GeometricObjectsCGM.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGeometricObjectsCGM CATIPGMGeomObjCGMItfBldr *CATCGMGetGeomObjCGMItfBldr();

#endif /* CATIPGMGeomObjCGMItfBldr_h */
