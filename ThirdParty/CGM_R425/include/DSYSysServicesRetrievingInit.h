// COPYRIGHT DASSAULT SYSTEMES 2021
#ifndef DSYSysServicesRetrievingInit_H
#define DSYSysServicesRetrievingInit_H

#include "WebLogonPanel.h"

/////////////////////
//ONLY FOR SYSTEMTS//
/////////////////////
#if defined(_WINDOWS_SOURCE) || defined(_LINUX_SOURCE)
/**
* DEPRECATED: duplicate of DSYSysTenantDataSingletonInitCAS
*/
ExportedByDSYSysDlg [[deprecated("Will be removed ASAP")]] void	DSYSysTenantDataSingletonInit();
#else
ExportedByDSYSysDlg void	DSYSysTenantDataSingletonInit();
#endif
/**
* Initialize the singleton with no-CAS WS (3DRegistry: tenant ids, services URLs).
*/
ExportedByDSYSysDlg bool	DSYSysTenantDataSingletonInitNoCAS();
/**
* Initialize totally the singleton with no-CAS WS if not already initialized (3DRegistry: tenant ids, services URLs) and CAS WS (MyApps: tenant display name).
*/
ExportedByDSYSysDlg bool	DSYSysTenantDataSingletonInitCAS();
/////////////////////
/////////////////////

#endif  // DSYSysServicesRetrieving_H
