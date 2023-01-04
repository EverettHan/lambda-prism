#ifndef CATHyperbola_h
#define CATHyperbola_h
#include "CATBaseUnknown.h"

// COPYRIGHT DASSAULT SYSTEMES 1999

#include <stdio.h>

#include "CATConic.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATHyperbola ;
#else
extern "C" const IID IID_CATHyperbola ;
#endif

class ExportedByCATGMGeometricInterfaces CATHyperbola : public CATConic
{
  CATDeclareInterface;

public:
virtual CATPositiveLength GetMajorAxis()const =0;
virtual CATPositiveLength GetMinorAxis()const =0;
virtual void SetMajorAxis(CATPositiveLength iNewMajorAxis)=0;
virtual void SetMinorAxis(CATPositiveLength iNewMinorAxis)=0;
};
  CATDeclareHandler(CATHyperbola,CATConic);

#endif
