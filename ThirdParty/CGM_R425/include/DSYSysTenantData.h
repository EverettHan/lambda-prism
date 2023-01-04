// COPYRIGHT DASSAULT SYSTEMES 2021
#ifndef DSYSysTenantData_H
#define DSYSysTenantData_H

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "DSYString.h"
#include "JS0HTTP.h"   // ExportedByDSYSysDlg

#if defined(__DSYSysDlg)
# define ExportedByDSYSysDlg  DSYExport
#else  // __DSYSysDlg
# define ExportedByDSYSysDlg  DSYImport
#endif // __DSYSysDlg

constexpr const char TENANTDATA_ARG_TENANTID[]   = "tenant";
constexpr const char TENANTDATA_ARG_CLUSTERID[]  = "clusterID";
constexpr const char TENANTDATA_ARG_MYAPPS[]     = "MyAppsURL";
constexpr const char TENANTDATA_ARG_3DSPACE[]    = "Url";
constexpr const char TENANTDATA_ARG_3DREGISTRY[] = "3DRegistryURL";
constexpr const char TENANTDATA_ARG_TRANSIENTURL[] = "x3ds_transient_auth_url";

/**
 * @class DSYSysTenantData
 * Contains tenant name and id, as well as a list of URLs used often enough to have direct access.
 * CAUTION!!! It's not valued by default, that has to be done by the friend class DSYSysServicesRetrieving.
 */
class ExportedByDSYSysDlg DSYSysTenantData final
{
  friend class DSYSysServicesRetrieving;
  friend class DSYSysTenantDataSingleton;
public:
  struct DSYSysServicesBitField
  {
    union
    {
      unsigned long _Brief;
      struct
      {
        // MyApps/3DCompass and 3DRegistry are retrieved by default.
        unsigned long _3DAnalytics : 1;
        unsigned long _3DDashboard : 1;
        unsigned long _3DDrive : 1;
        unsigned long _3DGeoSciSurvey : 1;
        unsigned long _3DMessaging : 1;
        unsigned long _3DNotifications : 1;
        unsigned long _3DPassport : 1;
        unsigned long _3DPassportNta : 1;
        unsigned long _3DPlanetData : 1;
        unsigned long _3DSearch : 1;
        unsigned long _3DSpace : 1;
        unsigned long _3DSywm : 1;
        unsigned long _BusinessInsight : 1;
        unsigned long _DataPreAuthoring : 1;
        unsigned long _Dfcs : 1;
        unsigned long _Dsls : 1;
        unsigned long _GeoService : 1;
        unsigned long _Grid : 1;
        unsigned long _MPPresentation : 1;
        unsigned long _OnePart : 1; // OnPremise service.
        unsigned long _OnePartWrapper : 1;
        unsigned long _SPAContentOptimizer : 1;

        unsigned long _Spare : 10; //spare = 32 - <other element of the struct>
      };
    };
  };

  enum AuthenticationType
  {
    _Unknown = 0,
    _3DPassport,
    _Delegated
  };

private:
  enum DataOrigin
  {
    _Unusable = 0,
    _3DRegistryArg,
    _MyAppsArg,
    _UrlTo3DRegistryArg,
    _UrlToMyAppsArg,
    _3DRegistryInput,
    _MyAppsInput
  };

public:
  DSYSysTenantData() :m_Origin{ DataOrigin::_Unusable }, m_bHasCASData(false), m_AuthenticationType{ AuthenticationType::_Unknown }, m_UrlsAsked{ 0 }, m_UrlsFound{ 0 }{};
  [[deprecated("Will be removed ASAP")]]DSYSysTenantData(const CATUnicodeString&) :DSYSysTenantData() {};
  ~DSYSysTenantData() = default;

  // Verifiers.
  bool IsInitializedNoCAS() const;
  bool IsInitializedCAS() const;
  bool IsComplete() const;
  bool HasThoseUrls(const unsigned long& iBrief) const;

  // Accessors.
  bool IsCloud() const; // Based on the tenant id (true if TenantId is not null and different from "OnPremise").*
  [[deprecated("For System usage only (contact us if needed)")]] AuthenticationType GetAuthenticationType() const{ return m_AuthenticationType; }; // RESERVED TO SYSTEM USE!!!
  CATUnicodeString GetMyAppsUrl() const { return m_MyApps; };
  CATUnicodeString Get3DRegistryUrl() const { return m_3DRegistry; };
  DSYSysServicesBitField GetUrlsAsked() const { return m_UrlsAsked; };
  DSYSysServicesBitField GetUrlsFound() const { return m_UrlsFound; };
  CATUnicodeString GetTenantId() const { return m_TenantId; };
  [[deprecated("If your env is based on 3DRegistry, will not be valued")]] CATUnicodeString GetTenantName() const { return m_TenantName; }; // RESERVED TO SYSTEM USE!!!
  CATUnicodeString Get3DAnalytics() const { return m_3DAnalytics; };
  CATUnicodeString Get3DDashboardUrl() const { return m_3DDashboard; };
  CATUnicodeString Get3DDriveUrl() const { return  m_3DDrive; };
  CATUnicodeString Get3DGeoSciSurveyUrl() const { return  m_3DGeoSciSurvey; };
  CATUnicodeString Get3DMessagingUrl() const { return  m_3DMessaging; };
  CATUnicodeString Get3DNotificationsUrl() const { return  m_3DNotifications; };
  CATUnicodeString Get3DPassportUrl() const { return m_3DPassport; };
  CATUnicodeString Get3DPassportNtaUrl() const { return m_3DPassportNta; };
  CATUnicodeString Get3DPlanetDataUrl() const { return m_3DPlanetData; };
  CATUnicodeString Get3DSearchUrl() const { return m_3DSearch; };
  CATUnicodeString Get3DSpaceUrl() const { return  m_3DSpace; };
  CATUnicodeString Get3DSywmUrl() const { return m_3DSywm; };
  CATUnicodeString GetBusinessInsightUrl() const { return  m_BusinessInsight; };
  CATUnicodeString GetDataPreAuthoringUrl() const { return  m_DataPrepAuthoring; };
  CATUnicodeString GetDfcsUrl() const { return m_Dfcs; };
  CATUnicodeString GetDslsUrl() const { return m_Dsls; };
  CATUnicodeString GetGeoServiceUrl() const { return m_GeoService; };
  CATUnicodeString GetGridUrl() const { return m_Grid; };
  CATUnicodeString GetMPPresentationUrl() const { return m_MPPresentation; };
  CATUnicodeString GetOnePartUrl() const { return m_OnePart; };
  CATUnicodeString GetOnePartWrapperUrl() const { return m_OnePartWrapper; };
  CATUnicodeString GetSPAContentOptimizerUrl() const { return m_SPAContentOptimizer; };

private:
  // Members.
  DataOrigin              m_Origin;
  AuthenticationType      m_AuthenticationType;
  bool                    m_bHasCASData;
  CATUnicodeString        m_MyApps;
  CATUnicodeString        m_3DRegistry;
  DSYSysServicesBitField  m_UrlsAsked;
  DSYSysServicesBitField  m_UrlsFound;
  CATUnicodeString        m_TenantId;
  CATUnicodeString        m_TenantName;
  CATUnicodeString        m_3DAnalytics;
  CATUnicodeString        m_3DDashboard;
  CATUnicodeString        m_3DDrive;
  CATUnicodeString        m_3DGeoSciSurvey;
  CATUnicodeString        m_3DMessaging;
  CATUnicodeString        m_3DNotifications;
  CATUnicodeString        m_3DPassport;
  CATUnicodeString        m_3DPassportNta;
  CATUnicodeString        m_3DPlanetData;
  CATUnicodeString        m_3DSearch;
  CATUnicodeString        m_3DSpace;
  CATUnicodeString        m_3DSywm;
  CATUnicodeString        m_BusinessInsight;
  CATUnicodeString        m_DataPrepAuthoring;
  CATUnicodeString        m_Dfcs;
  CATUnicodeString        m_Dsls;
  CATUnicodeString        m_GeoService;
  CATUnicodeString        m_Grid;
  CATUnicodeString        m_MPPresentation;
  CATUnicodeString        m_OnePart;
  CATUnicodeString        m_OnePartWrapper;
  CATUnicodeString        m_SPAContentOptimizer;
};


/**
* Get an object gathering data about the single tenant corresponding to the duo orign URL (MyAppsURL, Url our 3DRegistryUrl) and the tenant found in args.
* @param oData   The data.
* @return S_OK if the data is initialized with all requested URLs,
*         S_FALSE if the data is initialized but at least one URL is missing,
*         E_NOT_VALID_STATE if the data is not initialized (call the reset of the singleton),
*         E_FAIL if the allocation of the singleton failed.
*/
HRESULT ExportedByDSYSysDlg DSYSysGetCurrentTenantData(DSYSysTenantData& oData);


/**
* Get an object gathering data about the single tenant corresponding to the duo orign URL (MyAppsURL, Url our 3DRegistryUrl) and the tenant found in args.
* Filled only with calls to no-CAS WS (missing at least the tenant display name).
* @param oData   The data.
* @return S_OK if the data is initialized with all requested URLs,
*         S_FALSE if the data is initialized but at least one URL is missing,
*         E_NOT_VALID_STATE if the data is not initialized (call the reset of the singleton),
*         E_FAIL if the allocation of the singleton failed.
*/
HRESULT ExportedByDSYSysDlg DSYSysGetCurrentTenantDataNoCAS(DSYSysTenantData& oData);


/**
* Get an object gathering data about the public tenant corresponding to the duo orign URL (MyAppsURL, Url our 3DRegistryUrl) and the tenant found in args.
* @param oData   The data.
* @return S_OK if the data is initialized with all requested URLs,
*         S_FALSE if the data is initialized but at least one URL is missing,
*         E_NOT_VALID_STATE if the data is not initialized (call the reset of the singleton),
*         WS_E_INVALID_ENDPOINT_URL if the singletion is ok but it is not expected to have a public tenant (OnPremise or tenant with delegated authentication),
*         E_FAIL if the allocation of the singleton failed.
*/
HRESULT ExportedByDSYSysDlg DSYSysGetPublicTenantData(DSYSysTenantData& oData);

#endif  // DSYSysTenantData_H
