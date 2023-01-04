#ifndef CATOrientable_h
#define CATOrientable_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Do not use.
 */
#include "CATBaseUnknown.h"

#include <stdio.h>


#include "CATGeometry.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATOrientable ;
#else
extern "C" const IID IID_CATOrientable ;
#endif

class ExportedByCATGMGeometricInterfaces CATOrientable : public CATBaseUnknown
{
  CATDeclareInterface;

public:
virtual void SetOrientation(CATLONG32 iOrientation)=0;
virtual CATLONG32 GetOrientation()const =0;
virtual CATGeometry *GetSupport()const =0;
};
  CATDeclareHandler(CATOrientable,CATBaseUnknown);

#endif
