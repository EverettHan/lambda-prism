#ifndef CATIACGMExport_H
#define CATIACGMExport_H
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
// COPYRIGHT DASSAULT SYSTEMES 2017

#include "CATIACGMLevel.h"

//==========================================================================
// 1) for modules migrated in July 2017, under CATIACGMR420CAA flag,  and with _STATIC_SOURCE special case
//    please use CGMExportR420CAA
//           and CGMImportR420CAA
// 2) for modules migrated in 2016 on DSYExport/DSYImport             and with _STATIC_SOURCE special case
//    (without level flag because not in public interfaces)
//    please use CGMExport     
//           and CGMImport     
//
// see FDS,VXG for DSYExport,DSYImport general principles
// see FDS     for V6    initial DSYExport, DSYImport deployment      2016
// see FDS     for V6    global  DSYExport, DSYImport deployment July 2017
// see FDS/CPT for V5/V6 equivalence                             July 2017
// see NLD for this synthetic CGM definition
//==========================================================================
// 13/07/17 NLD Creation
// 25/07/17 NLD Variables distinction according to CGM deployment 2017
//                 with    (for Public    interfaces)              (CGMExportR420CAA/CGMImportR420CAA)
//              or without (for Protected interfaces) version flag (CGMExport       /CGMImport)
//==========================================================================

    #if defined _WINDOWS_SOURCE
      #define CGMExportOld     __declspec(dllexport)
      #define CGMImportOld     __declspec(dllimport)
    #else
      #define CGMExportOld    
      #define CGMImportOld    
    #endif

#ifdef _STATIC_SOURCE
  #define CGMExportR420CAA
  #define CGMImportR420CAA
  #define CGMExport     
  #define CGMImport     
#else

  // please keep this security version test for environments/levels without DSYExport available
  #ifdef CATIACGMV5R25
      #define CGMExport        DSYExport
      #define CGMImport        DSYImport
      #include "DSYExport.h"
  #else
      #define CGMExport        CGMExportOld
      #define CGMImport        CGMImportOld
  #endif

  #ifdef CATIACGMR420CAA
      #define CGMExportR420CAA DSYExport
      #define CGMImportR420CAA DSYImport
      #include "DSYExport.h"
  #else
      #define CGMExportR420CAA CGMExportOld
      #define CGMImportR420CAA CGMImportOld
  #endif
#endif

#endif
