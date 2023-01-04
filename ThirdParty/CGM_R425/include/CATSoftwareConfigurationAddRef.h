#ifndef CATSoftwareConfigurationAddRef_h
#define CATSoftwareConfigurationAddRef_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2007
// 
// DESCRIPTION : Utilities for signe AddRef/Release on CATSoftwareConfiguration
//
// 11/06/07 NLD Creation
// 14/06/07 NLD Changement de signatures pour CATSoftwareConfigurationAddRef() et CATSoftwareConfigurationModifyRef
//              pour duplication en debug
// 29/07/10 NLD Ajout CATGetSoftwareConfigurationAddRefDuplicateMode() et CATSetSoftwareConfigurationAddRefDuplicateMode()
//              puis  CATGetSoftwareConfigurationDebugMode() et CATSetSoftwareConfigurationDebugMode()
//=============================================================================
#include "ExportedByCATMathStream.h"

extern "C" ExportedByCATMathStream
int CATSoftwareConfigurationAddRef(CATSoftwareConfiguration*& iSoftwareConfiguration, void* iReferencing) ;

extern "C" ExportedByCATMathStream
int CATSoftwareConfigurationRelease(CATSoftwareConfiguration* iSoftwareConfiguration, void* iReferencing) ;

extern "C" ExportedByCATMathStream
int CATSoftwareConfigurationModifyRef(CATSoftwareConfiguration*& iSoftwareConfiguration, void* iReferencing, void* iOldReferencing) ;


// Very restricted use: access to duplicate mode of CATSoftwareConfigurationAddRef
// -------------------------------------------------------------------------------

// Gets current duplicate mode
extern "C" ExportedByCATMathStream
int CATGetSoftwareConfigurationAddRefDuplicateMode();

// Sets current duplicate mode
// 0 : inactive duplicate mode
// 1 : inactive duplicate mode
extern "C" ExportedByCATMathStream
void CATSetSoftwareConfigurationAddRefDuplicateMode(int iMode);

// Very restricted use: access to debug mode
// Gets current debug mode
//-------------------------------------------------------------
extern "C" ExportedByCATMathStream
int CATGetSoftwareConfigurationDebugMode();
// Sets current debug mode
// 0 : inactive debug mode
// 1 : inactive debug mode
//-------------------------------------------------------------
extern "C" ExportedByCATMathStream
void CATSetSoftwareConfigurationDebugMode(int iMode);

#endif
