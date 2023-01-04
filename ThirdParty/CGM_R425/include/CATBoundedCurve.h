
#ifndef CATBoundedCurve_h
#define CATBoundedCurve_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Use now the CATNurbsCurve class.
 */

#include "CATBaseUnknown.h"

#include <stdio.h>


#include "CATCurve.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATBoundedCurve ;
#else
extern "C" const IID IID_CATBoundedCurve ;
#endif

class ExportedByCATGMGeometricInterfaces CATBoundedCurve : public CATCurve
{
  CATDeclareInterface;

public:
};
  CATDeclareHandler(CATBoundedCurve,CATCurve);

#endif
