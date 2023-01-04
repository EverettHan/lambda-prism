#ifndef CATPGMExtremumTools_h_
#define CATPGMExtremumTools_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMModelInterfaces.h"
#include "CATErrorMacros.h"
#include "CATListOfDouble.h"

class CATCurve;
class CATFrFNurbsMultiForm;
class CATGeoFactory;
class CATMathPlane;
class CATMathPoint;
class CATMathVector;
class CATPCurve;
class CATCrvLimits;
class CATSoftwareConfiguration;


class ExportedByCATGMModelInterfaces CATPGMExtremumTools
{
public:
  static HRESULT GetMinDistance(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATFrFNurbsMultiForm *iMFNurbs,
    CATListOfDouble & oMinList,
    CATListOfDouble & owsList);

  static HRESULT GetMaxDistance(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATFrFNurbsMultiForm *iMFNurbs,
    CATListOfDouble & oMaxList,
    CATListOfDouble & owsList);

  static HRESULT GetLocalMinDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATFrFNurbsMultiForm *iMFNurbs,
    CATListOfDouble &oMinList,
    CATListOfDouble &owsList,
    CATListOfInt &oMinNatureList);

  static HRESULT GetLocalMaxDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATFrFNurbsMultiForm *iMFNurbs,
    CATListOfDouble &oMaxList,
    CATListOfDouble &owsList,
    CATListOfInt &oMaxNatureList);

  static HRESULT GetLocalExtremumDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATFrFNurbsMultiForm *iMFNurbs,
    CATListOfDouble &oExtrList,
    CATListOfDouble &owsList,
    CATListOfInt &oExtrNatureList);

  static HRESULT GetMinDistance(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATCurve *iCurve,
    const CATCrvLimits & iLim,
    CATListOfDouble & oMinList,
    CATListOfDouble & owsList);

  static HRESULT GetMaxDistance(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATCurve *iCurve,
    const CATCrvLimits & iLim,
    CATListOfDouble & oMaxList,
    CATListOfDouble & owsList);

  static HRESULT GetLocalMinDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATCurve *iCurve,
    const CATCrvLimits & iLim,
    CATListOfDouble &oMinList,
    CATListOfDouble &owsList,
    CATListOfInt &oMinNatureList);

  static HRESULT GetLocalMaxDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATCurve *iCurve,
    const CATCrvLimits & iLim,
    CATListOfDouble &oMaxList,
    CATListOfDouble &owsList,
    CATListOfInt &oMaxNatureList);

  static HRESULT GetLocalExtremumDistances(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    const CATMathPoint &iPoint,
    CATCurve *iCurve,
    const CATCrvLimits & iLim,
    CATListOfDouble &oExtrList,
    CATListOfDouble &owsList,
    CATListOfInt &oExtrNatureList);

   static HRESULT GetMinDistance(
     CATGeoFactory *iFactory,
     CATSoftwareConfiguration *iConfig,
     CATCurve *iCurve1,
     const CATCrvLimits & iLim1,
     CATCurve *iCurve2,
     const CATCrvLimits & iLim2,
     CATListOfDouble & oMinList,
     CATListOfDouble & oCrv1WsList,
     CATListOfDouble & oCrv2WsList);
};

#endif /* CATPGMExtremumTools_h_ */
