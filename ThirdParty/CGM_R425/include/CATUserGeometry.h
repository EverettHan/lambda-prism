#ifndef CATUserGeometry_h
#define CATUserGeometry_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATBaseUnknown.h"

#include "CATPoint.h"

#include "CATMathDef.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATUserGeometry ;
#else
extern "C" const IID IID_CATUserGeometry ;
#endif

class ExportedByCATGMGeometricInterfaces CATUserGeometry : public CATGeometry
{
  CATDeclareInterface;

public:
  virtual void SetGeometry(CATGeometry* Geometry)=0;
  virtual CATGeometry* GetGeometry()=0;
};

  CATDeclareHandler(CATUserGeometry,CATGeometry);

#endif
