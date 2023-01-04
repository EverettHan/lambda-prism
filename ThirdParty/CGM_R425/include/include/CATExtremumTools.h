/* -*-c++-*- */
#ifndef CATExtremumTools_H
#define CATExtremumTools_H
//==================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010
//04Jun2010 KJD : Creation 
//==================================================================
#include "Y30UIUTI.h"
#include "CATError.h"
#include "CATListOfDouble.h"
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATFrFNurbsMultiForm;
class CATCurve;
class CATPCurve;
class CATMathPlane;
class CATMathPoint;
class CATMathVector;
class CATCrvLimits;

class ExportedByY30UIUTI CATExtremumTools
{
public: 
// Distance PtCrv
  static HRESULT GetMinDistance(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, CATFrFNurbsMultiForm *iMFNurbs, CATListOfDouble & oMinList, CATListOfDouble & owsList);
  static HRESULT GetMaxDistance(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, CATFrFNurbsMultiForm *iMFNurbs, CATListOfDouble & oMaxList, CATListOfDouble & owsList);

  static HRESULT GetLocalMinDistances(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, CATFrFNurbsMultiForm *iMFNurbs, 
                                                                     CATListOfDouble & oMinList, CATListOfDouble & owsList, CATListOfInt & oMinNatureList);
  static HRESULT GetLocalMaxDistances(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, CATFrFNurbsMultiForm *iMFNurbs,
                                                                      CATListOfDouble & oMaxList, CATListOfDouble & owsList, CATListOfInt & oMaxNatureList);
  static HRESULT GetLocalExtremumDistances(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, CATFrFNurbsMultiForm *iMFNurbs,
                                                                                CATListOfDouble & oExtrList, CATListOfDouble & owsList, CATListOfInt & oExtrNatureList);

  static HRESULT GetMinDistance(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, CATCurve *iCurve, const CATCrvLimits & iLim, CATListOfDouble & oMinList, CATListOfDouble & owsList);
  static HRESULT GetMaxDistance(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, CATCurve *iCurve, const CATCrvLimits & iLim, CATListOfDouble & oMaxList, CATListOfDouble & owsList); 

  static HRESULT GetLocalMinDistances(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, CATCurve *iCurve, const CATCrvLimits & iLim,
                                                                    CATListOfDouble & oMinList, CATListOfDouble & owsList, CATListOfInt & oMinNatureList);
  static HRESULT GetLocalMaxDistances(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, CATCurve *iCurve,  const CATCrvLimits & iLim,
                                                                      CATListOfDouble & oMaxList, CATListOfDouble & owsList, CATListOfInt & oMaxNatureList);
  static HRESULT GetLocalExtremumDistances(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, const CATMathPoint &iPoint, CATCurve *iCurve, const CATCrvLimits & iLim,
                                                                                CATListOfDouble & oExtrList, CATListOfDouble & owsList, CATListOfInt & oExtrNatureList);
  
  // Distance CrvCrv : 
  static HRESULT GetMinDistance(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, CATCurve *iCurve1, const CATCrvLimits & iLim1, CATCurve *iCurve2, const CATCrvLimits & iLim2, CATListOfDouble & oMinList, CATListOfDouble & oCrv1WsList, CATListOfDouble & oCrv2WsList);

  //NE PAS LES APPELER POUR l'INSTANT !!!
  // kjd 02dec2010 : les methodes ci-dessous sont en cours d'implementation
  static HRESULT GetMaxDistance(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, CATCurve *iCurve1, const CATCrvLimits & iLim1, CATCurve *iCurve2, const CATCrvLimits & iLim2, CATListOfDouble & oMaxList, CATListOfDouble & oCrv1WsList, CATListOfDouble & oCrv2WsList); 
  static HRESULT GetLocalMinDistances(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, CATCurve *iCurve1, const CATCrvLimits & iLim1, CATCurve *iCurve2,const CATCrvLimits & iLim2,
    CATListOfDouble & oMinList, CATListOfDouble & oCrv1WsList, CATListOfDouble & oCrv2WsList, CATListOfInt & oMinNatureList);
  static HRESULT GetLocalMaxDistances(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, CATCurve *iCurve1, const CATCrvLimits & iLim1, CATCurve *iCurve2,const CATCrvLimits & iLim2,
    CATListOfDouble & oMaxList, CATListOfDouble & oCrv1WsList, CATListOfDouble & oCrv2WsList, CATListOfInt & oMaxNatureList);
  static HRESULT GetLocalExtremumDistances(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, CATCurve *iCurve1, const CATCrvLimits & iLim1, CATCurve *iCurve2,const CATCrvLimits & iLim2,
    CATListOfDouble & oExtrList, CATListOfDouble & oCrv1WsList, CATListOfDouble & oCrv2WsList, CATListOfInt & oExtrNatureList);
};
#endif
