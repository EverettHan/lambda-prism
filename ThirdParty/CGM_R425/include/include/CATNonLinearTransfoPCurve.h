#ifndef CATNonLinearTransfoPCurve_h
#define CATNonLinearTransfoPCurve_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Interface representing an CATNonLinearTransfoPCurve
 */


#include "CATPCurve.h"
#include "CATMathDef.h"


#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATNonLinearTransfoPCurve ;
#else
extern "C" const IID IID_CATNonLinearTransfoPCurve ;
#endif

class ExportedByCATGMGeometricInterfaces CATNonLinearTransfoPCurve : public CATPCurve
{
  CATDeclareInterface;

public :

  virtual const CATPCurve * GetReference() const = 0;


};
  CATDeclareHandler(CATNonLinearTransfoPCurve,CATPCurve);

#endif
