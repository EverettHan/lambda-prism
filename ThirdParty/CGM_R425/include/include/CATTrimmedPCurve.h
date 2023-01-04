#ifndef CATTrimmedPCurve_h
#define CATTrimmedPCurve_h

// COPYRIGHT DASSAULT SYSTEMES  2000

#include "CATPCurve.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATTrimmedPCurve ;
#else
extern "C" const IID IID_CATTrimmedPCurve ;
#endif

class CATCrvLimits;

class ExportedByCATGMGeometricInterfaces CATTrimmedPCurve : public CATPCurve
{
  CATDeclareInterface;

public :
/**
 * @nodoc
 */
  virtual void Set(CATSurface * iSupport, CATPCurve * iReference, const CATCrvLimits & iLimits) = 0;
/**
 * @nodoc
 */
  virtual void SetMaxLimits(const CATCrvLimits & iLimits) = 0;
/**
 * @nodoc
 */
  virtual const CATPCurve * GetReference() const = 0;

};
  CATDeclareHandler(CATTrimmedPCurve,CATPCurve);

#endif
