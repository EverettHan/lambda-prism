#ifndef CATGeoAxis_H
#define CATGeoAxis_H
// COPYRIGHT DASSAULT SYSTEMES  1999

#include "CATBaseUnknown.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#include "CATMathAxis.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoAxis ;
#else
extern "C" const IID IID_CATGeoAxis ;
#endif


class ExportedByCATGMGeometricInterfaces CATGeoAxis : public CATBaseUnknown
{
  CATDeclareInterface;

 public :
	
  // reads the mathematical definition 
  virtual HRESULT GetMathAxis(CATMathAxis & oMathAxis) const = 0;		
};

CATDeclareHandler(CATGeoAxis,CATBaseUnknown);
#endif
