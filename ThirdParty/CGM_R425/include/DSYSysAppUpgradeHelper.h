// COPYRIGHT DASSAULT SYSTEMES 2015
#ifndef DSYSysAppUpgradeHelper_H
#define DSYSysAppUpgradeHelper_H
/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#if defined(__DSYSysAppUpgrade)
# define ExportedByDSYSysAppUpgrade   DSYExport
#else // __DSDriveSyncCore
# define ExportedByDSYSysAppUpgrade   DSYImport
#endif  // __DSDriveSyncCore

#define APPUPGRADEH_TRACENAME                                   "AppUpgrade"
#define APPUPGRADEH_ARG_STARTUP                                 "3DEXP_StartUpdChk"
#define APPUPGRADEH_ARGMASK_NOSTARTUPCHECK                      1
#define APPUPGRADEH_ARGMASK_FORCERECOMDIALOG                    2
#define APPUPGRADEH_ARGMASK_SPECIFICEXIT                        4
#define APPUPGRADEH_EXITCODE_UPGRADE                            10
#define APPUPGRADEH_EXITCODE_USERCLICK                          11
#if defined (_WINDOWS_SOURCE)
#define APPUPGRADEH_SUPPORTED
#endif

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "DSYExport.h"
#include "DSYString.h"
#include "CATHttpClient.h"
#include "DSYSysJSON.h"
#include <vector>

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

  /**
  * @struct DSYSysAppUpgradePodInfo
  */
  struct DSYSysAppUpgradePodInfo
  {
    /// POD release identifier.
    CATUnicodeString _PodReleaseId;

    /// Environment.
    CATUnicodeString _EnvironmentUrl;

    /// Cluster Identifier.
    CATUnicodeString _ClusterId;
  };

  /**
  * @struct DSYSysAppUpgradeParamCheck Struct of inputs required to check upgrade availability.
  */
  struct DSYSysAppUpgradeParamCheck
  {
    CATUnicodeString _MyAppsUrl;
    CATUnicodeString _Type;         // Type of the app (CODE, CNT or ALL).
    CATUnicodeString _CodeType;     // Name of the app in the registry, used by the Launcher(which names it installationType).
    CATUnicodeString _CodeLevel;    // CodeLevel of the current media, in fact its build time in YYYYMMDDThhmmssZ format (by example 20180307T194514Z).
    CATUnicodeString _SPLevel;      // SPLevel of the current media (by example 420.5).
    //CATUnicodeString _Process;      // Process of the media, i.e. its linked role with double-quotes (by example "IFW_RP").
    size_t           _Process;      // Which process of the vector to use as reference (by default the first one, so _Process = 0).
    std::vector <CATUnicodeString> _Processes;    // Processes on which search the media(at least process, by example "IFW_RP", "IFS_RP").
  };

  /**
  * @struct DSYSysAppUpgradeAccessLocks about download access locks.
  */
  struct ExportedByDSYSysAppUpgrade DSYSysAppUpgradeAccessLocks
  {
    /// Value of "Lock access to optional content installation for all members".
    bool _Additional;

    /// Value of "Lock access to application installation for all members".
    bool _Install;

    /// Value of "Lock access to installation of application updates for all members".
    bool _Upgrade;
  };

#ifdef __cplusplus
};
#endif  // __cplusplus

/**
 * @class DSYSysAppUpgradeInfo
 */
class ExportedByDSYSysAppUpgrade DSYSysAppUpgradeInfo
{
  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:
  /// Enumeration for instruction (used since v2 version).
  typedef enum Instruction_t
  {
    /// Keep/Nothing to do.
    _Keep = 0

    /// Propose/Optional upgrade without uninstall (upgrade compatible .
    , _ProposeCompatible = 1

    /// Propose/Optional upgrade with uninstall.
    , _ProposeUninstall = 2

    /// Force/Mandatory upgrade without uninstall.
    , _ForceCompatible = 3

    /// Force/Mandatory upgrade with uninstall.
    , _ForceUninstall = 4

    /// Launch additional install from scratch.
    , _Additional = 5

    /// Error.
    , _Error = 6
  } InstructionType;


  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor (default).
  DSYSysAppUpgradeInfo();

  /// Constructor (copy).
  DSYSysAppUpgradeInfo(const DSYSysAppUpgradeInfo& irMedia);

  /// Destructor.
  virtual ~DSYSysAppUpgradeInfo();

  /// Assigment operator.
  DSYSysAppUpgradeInfo& operator=(const DSYSysAppUpgradeInfo& irMedia);

  /// Compare operator.
  bool operator==(const DSYSysAppUpgradeInfo &other) const;

  /// Greater then operator.
  bool operator<(const DSYSysAppUpgradeInfo& irMedia) const;

  /// Lesser then operator.
  bool operator>(const DSYSysAppUpgradeInfo& irMedia) const;

  /// Compare release version of medias.
  int CompareReleaseVersion(const DSYSysAppUpgradeInfo& irMedia) const;

  /// Set code level
  void SetLevelClient(void);

  /// Get code build time.
  time_t GetCodeBuildTime(void) const
  { return m_CodeBuildTime; }

  /// Set code build time from code level.
  void SetBuildTimeFromCodeLevel(void)
  { m_CodeBuildTime = ConvertXmlDateTimeToTimeT(m_CodeLevel); }

  /// Get code level.
  CATUnicodeString GetCodeLevel(void) const
  { return m_CodeLevel; }

  /// Set code level.
  void SetCodeLevel(const CATUnicodeString& irCodeLevel)
  { m_CodeLevel = irCodeLevel; }

  /// Get code version.
  CATUnicodeString GetCodeVersion(void) const
  { return m_CodeVersion; }

  /// Set media status (useless).
  void SetStatus(const int iStatus)
  { m_Status = iStatus; }

  /// Set instruction.
  void SetInstruction(const int iInstruction)
  { m_Instruction = (InstructionType)iInstruction; }

  InstructionType GetInstruction() const
  { return m_Instruction; }

  /// Set code type.
  void SetCodeType(const CATUnicodeString& irCodeType)
  { m_CodeType = irCodeType; }

  /// Get release.
  CATUnicodeString GetRelease() const
  { return m_Release; }

  /// Set release.
  void SetRelease(const CATUnicodeString& irRelease)
  { m_Release = irRelease; }

  /// Get commercial name.
  CATUnicodeString GetCommercialName() const
  { return m_CommercialName; }

  /// Set commercial name.
  void SetCommercialName(const CATUnicodeString& irCommercialName)
  { m_CommercialName = irCommercialName; }

  /// Get SPlevel.
  CATUnicodeString GetSPlevel() const
  { return m_SPlevel; }

  /// Set SPlevel.
  void SetSPlevel(const CATUnicodeString& irSPlevel)
  { m_SPlevel = irSPlevel; }

  /// Convert an XML datetime to a time_t.
  time_t ConvertXmlDateTimeToTimeT(const CATUnicodeString iXmlDateTime) const;

  /// Check if the code type is the same.
  bool IsSameCodeType(const CATUnicodeString iCodeType) const
  { return (TRUE == (m_CodeType == iCodeType)); }

//USELESS FOR NOW--------------------------------
//  /// Set media place.
//  void SetPlace(const int iPlace)
//  { m_Place = iPlace; }
//USELESS FOR NOW--------------------------------

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
//USELESS FOR NOW--------------------------------
//  /// Media place (on the download platform, so GA->0, etc.).
//  int m_Place;
//USELESS FOR NOW--------------------------------

  /// Data get from web (JSON) else from local data.
  bool m_FromWeb;

  /// OIF map status (0 optional, 1 recommended, 2 mandatory, 3 deprecated).
  int m_Status;

  /// Code build time.
  time_t m_CodeBuildTime;

  /// Code level.
  CATUnicodeString m_CodeLevel;

  /// Code type.
  CATUnicodeString m_CodeType;

  /// Release level.
  CATUnicodeString m_Release;

  /// Version (X.X.X.X format), not from JSON.
  CATUnicodeString m_CodeVersion;

  /// Commercial name.
  CATUnicodeString m_CommercialName;

  /// SPlevel.
  CATUnicodeString m_SPlevel;

  /// Instruction about local install according to the web.
  InstructionType m_Instruction;
};


/************************************************************************/
/* Functions declaration                                                */
/************************************************************************/

//=======================================================================
ExportedByDSYSysAppUpgrade HRESULT DSYSysAppUpgradeGetInfo( DSYSysAppUpgradeInfo &oMediaInfo
                                                          , const DSYSysAppUpgradeParamCheck iParams);
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade HRESULT DSYSysAppUpgradeGetInfoFull( DSYSysAppUpgradeInfo &oMediaInfo
                                                              , const DSYSysAppUpgradePodInfo iPodInfo
                                                              , const DSYSysAppUpgradeParamCheck iParams);
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade HRESULT DSYSysAppUpgradeCheckForUpgrade( DSYSysAppUpgradeInfo &oMediaInfo
                                                                  , DSYSysAppUpgradeParamCheck* ioParams);
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade HRESULT DSYSysAppUpgradeParseJSONRpc( DSYSysAppUpgradeInfo &oMediaInfo
                                                               , const char* ipBuff
                                                               , const CATUnicodeString iCodeType);
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade bool DSYSysAppUpgradeToolsCheckForLoginRedirect( CATHttpClient &iHttpClient);
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade HRESULT DSYSysAppUpgradeToolsGetPodInfo( DSYSysAppUpgradePodInfo& irPodInfo
                                                                        , const char* ipMyAppsUrl);
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade const char* DSYSysAppUpgradeToolsGetClusterFromMyAppsUrl( const CATUnicodeString iMyAppsUrl);
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade int DSYSysAppUpgradeToolsCompareVersion( const CATUnicodeString iRef
                                                                  , const CATUnicodeString iComp
                                                                  , const CATUnicodeString &iDelimiterCharacters);
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade HRESULT DSYSysAppUpgradeToolsGetAppData( DSYSysAppUpgradeParamCheck *ioData
                                                                  , const bool iRemoveExtension = false);
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade HRESULT DSYSysAppUpgradeToolsGetPrdList( std::vector<CATUnicodeString> &oPrdList
                                                                  , const bool & iRemoveExtension = false);
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade HRESULT DSYSysAppUpgradeToolsGetRegistryJson(DSYSysJSONValue &oJsonValue);
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade bool DSYSysAppUpgradeToolsIsAppUpgradeActive();
//=======================================================================

//=======================================================================
ExportedByDSYSysAppUpgrade HRESULT DSYSysAppUpgradeToolsGetAccessLocks( DSYSysAppUpgradeAccessLocks &oLocks
                                                                      , const CATUnicodeString iMyAppsUrl);
//=======================================================================


#endif  // DSYSysAppUpgradeHelper_H

