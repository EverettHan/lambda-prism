#ifndef CATPGMFrFDistanceMinCcvCcv_h_
#define CATPGMFrFDistanceMinCcvCcv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"

class CATCrvLimits;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATFrFCCvParam;
class CATFrFCompositeCurve;

//-------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATPGMFrFDistanceMinCcvCcv: public CATCGMVirtual
{
public:
  /**
   * Constructor
   */
  CATPGMFrFDistanceMinCcvCcv();

  /**
   * Destructor
   */
  virtual ~CATPGMFrFDistanceMinCcvCcv();

  virtual void Run() = 0;

  virtual CATFrFCCvParam *GetResultingCCVParam(CATLONG32 iNumCCV) = 0;

  // iNumCCV vaut 1 ou 2
  virtual double GetMinDist() = 0;

  virtual CATLONG32 Min1IsTheStart() = 0;

  virtual CATLONG32 Min1IsTheEnd() = 0;

  virtual CATLONG32 Min2IsTheStart() = 0;

  virtual CATLONG32 Min2IsTheEnd() = 0;

  virtual void SetArcLengthTolerance(double minExtremityArcLengthTolerance) = 0;
};

ExportedByCATGMOperatorsInterfaces CATPGMFrFDistanceMinCcvCcv *CATPGMCreateFrFDistanceMinCcvCcv(
  CATGeoFactory *factory,
  CATFrFCompositeCurve *CCV1,
  CATFrFCompositeCurve *CCV2,
  CATSoftwareConfiguration *iConfig = 0);

#endif /* CATPGMFrFDistanceMinCcvCcv_h_ */
