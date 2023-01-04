
#ifndef CATBezierSurface_h
#define CATBezierSurface_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Do not use.
 */
#include "CATBaseUnknown.h"

#include <stdio.h>


#include "CATBSplineSurface.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATBezierSurface ;
#else
extern "C" const IID IID_CATBezierSurface ;
#endif

class ExportedByCATGMGeometricInterfaces CATBezierSurface : public CATBSplineSurface
{
  CATDeclareInterface;

public:
};
  CATDeclareHandler(CATBezierSurface,CATBSplineSurface);

#endif
