#ifndef CATDraftCrvCutOnC1Discontinuities_h
#define CATDraftCrvCutOnC1Discontinuities_h

#include "CATGeoOperator.h"
#include "Connect.h"
class CATCrvParam;
class CATGeoFactory;
class CATEdgeCurve;
class CATCrvLimits;
class CATPCurve;
class CATLaw;
class CATMathDirection;

class ExportedByConnect CATDraftCrvCutOnC1Discontinuities : public CATGeoOperator
{
public:

  CATDraftCrvCutOnC1Discontinuities(CATGeoFactory *iFactory);

  ~CATDraftCrvCutOnC1Discontinuities();

  virtual CATLONG32 GetNbDiscontinuities()=0;

  virtual void Beginning()=0;
  
  virtual CATBoolean Next()=0;

  virtual void GetDiscontinuity(CATCrvParam& oParam)=0;
                
};

ExportedByConnect CATDraftCrvCutOnC1Discontinuities* CreateDraftCrvCutOnC1Discontinuities(CATGeoFactory *iFactory,
                                                                                          CATSoftwareConfiguration * iConfig,
                                                                                          const CATEdgeCurve * iEC,
                                                                                          const CATCrvLimits & iECLimits,
                                                                                          const CATPCurve* iSupportPCurve,
                                                                                          const CATLaw * iAngleLaw,
                                                                                          const CATLaw * iMappingLaw,
                                                                                          const CATMathDirection &iPullingDirection,
                                                                                          const CATPCurve* iInitialPCurve,
                                                                                          const double iLenght1,
                                                                                          const double iLength2,
                                                                                          short iAngleOrientation=0);


#endif
