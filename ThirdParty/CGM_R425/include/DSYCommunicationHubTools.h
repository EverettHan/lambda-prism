//===========================================================================
// COPYRIGHT DASSAULT SYSTEMES 1996                                          
//===========================================================================
//                                                                           
//  CATSettingRepository                                                     
//                                                                           
//  Usage Notes: Environment Managing                                                 
//===========================================================================
//  Creation decembre 1996                                 adt              
//===========================================================================
#ifndef __DSYCOMMUNICATIONHUB
#define __DSYCOMMUNICATIONHUB

#include "CATHttp.h"
#include "DSYString.h"

ExportedByJS0HTTP int GetDSYCommunicationHubPort();
ExportedByJS0HTTP bool IsDSYCommunicationHubOn();
ExportedByJS0HTTP int SetDSYCommunicationHubEnv(const CATUnicodeString& iCusPort);
ExportedByJS0HTTP HRESULT StartDSYCommunicationHub(CATUnicodeString *iPath=NULL);

#endif 
