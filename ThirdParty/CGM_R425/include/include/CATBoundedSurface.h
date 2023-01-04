
#ifndef CATBoundedSurface_h
#define CATBoundedSurface_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Do not use.
 */

#include "CATBaseUnknown.h"

#include <stdio.h>


#include "CATSurface.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATBoundedSurface ;
#else
extern "C" const IID IID_CATBoundedSurface ;
#endif

class ExportedByCATGMGeometricInterfaces CATBoundedSurface : public CATSurface
{
  CATDeclareInterface;

public:
};
  CATDeclareHandler(CATBoundedSurface,CATSurface);

#endif
