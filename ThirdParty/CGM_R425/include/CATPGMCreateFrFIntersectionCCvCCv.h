#ifndef CATPGMCreateFrFIntersectionCCvCCv_h_
#define CATPGMCreateFrFIntersectionCCvCCv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATSoftwareConfiguration;
class CATFrFIntersectionCCvCCv;
class CATGeoFactory;
class CATFrFCompositeCurve;

#ifndef NULL
#define NULL 0
#endif

ExportedByCATGMOperatorsInterfaces CATFrFIntersectionCCvCCv *CATPGMCreateFrFIntersectionCCvCCv(
  CATGeoFactory *iFactory,
  CATFrFCompositeCurve *iCCv1,
  CATFrFCompositeCurve *iCCv2,
  CATSkillValue iMode = BASIC,
  const CATSoftwareConfiguration *iConfig = NULL);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateFrFIntersectionCCvCCv.
 */
inline CATFrFIntersectionCCvCCv *CreateFrFIntersectionCCvCCv(
  CATGeoFactory *iFactory,
  CATFrFCompositeCurve *iCCv1,
  CATFrFCompositeCurve *iCCv2,
  CATSkillValue iMode = BASIC,
  const CATSoftwareConfiguration *iConfig = NULL)
{
  return CATPGMCreateFrFIntersectionCCvCCv(iFactory, iCCv1, iCCv2, iMode, iConfig);
}

//
ExportedByCATGMOperatorsInterfaces
void Remove(CATFrFIntersectionCCvCCv *& iOperator);  

#endif /* CATPGMCreateFrFIntersectionCCvCCv_h_ */
