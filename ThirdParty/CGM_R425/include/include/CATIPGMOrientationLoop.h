#ifndef CATIPGMOrientationLoop_h_
#define CATIPGMOrientationLoop_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATGeoFactory;
class CATMathFunctionX;
class CATPCurve;
class CATSoftwareConfiguration;
class CATCrvParam;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMOrientationLoop;

class ExportedByCATGMModelInterfaces CATIPGMOrientationLoop: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMOrientationLoop();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------
  virtual CATLONG32 GetOrientation() const = 0;

  virtual double GetArea() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMOrientationLoop(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMOrientationLoop *CATPGMCreateOrientationLoop(
  CATGeoFactory *iFactory,
  const CATLONG32 iNbPCrv,
  const CATPCurve **iPCrv,
  const CATCrvParam *iStartParam,
  const CATCrvParam *iEndParam);

#endif /* CATIPGMOrientationLoop_h_ */
