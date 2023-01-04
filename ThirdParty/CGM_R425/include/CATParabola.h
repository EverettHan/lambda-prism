#ifndef CATParabola_h
#define CATParabola_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATBaseUnknown.h"

#include <stdio.h>


#include "CATConic.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATParabola ;
#else
extern "C" const IID IID_CATParabola ;
#endif

class ExportedByCATGMGeometricInterfaces CATParabola : public CATConic
{
  CATDeclareInterface;

public:
virtual CATLength GetFocalDistance()const =0;
virtual CATMathPoint GetFocus()const =0;
virtual void SetFocalDistance(CATLength iNewFocalDistance)=0;
};
  CATDeclareHandler(CATParabola,CATConic);

#endif
