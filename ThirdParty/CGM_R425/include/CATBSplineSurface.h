
#ifndef CATBSplineSurface_h
#define CATBSplineSurface_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Do not use.
 */

#include "CATBaseUnknown.h"

#include <stdio.h>


#include "CATBoundedSurface.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATBSplineSurface ;
#else
extern "C" const IID IID_CATBSplineSurface ;
#endif

class ExportedByCATGMGeometricInterfaces CATBSplineSurface : public CATBoundedSurface
{
  CATDeclareInterface;

public:
virtual void GetNumberOfControlPoints(CATLONG32 & oNbrCtrlPtsU,
CATLONG32 & oNbrCtrlPtsV)const =0;
virtual CATMathPoint GetOneControlPoint(CATLONG32 iPointIndexU,
CATLONG32 iPointIndexV)const =0;
virtual void GetDegree(CATLONG32 & oDegreeU,
CATLONG32 & oDegreeV)const =0;
};
  CATDeclareHandler(CATBSplineSurface,CATBoundedSurface);

#endif
