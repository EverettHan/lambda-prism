#ifndef CATCreateSoftwareConfigurationLicensed_h
#define CATCreateSoftwareConfigurationLicensed_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2011
//
// DESCRIPTION : Utilities for licensed CATSoftwareConfiguration creation
//
// 23/09/11 NLD Creation
//              CATCreateSoftwareConfigurationLicensed()
//              CATSoftwareConfigurationCreation_License
// 27/09/11 NLD Ajout GetCATSoftwareConfigurationNbUnlicensedOpenCreations()
// 15/07/19 NLD Ajout CATSoftwareConfigurationCreation_ForSubdTemporary
//              (licence temporaire; usage restreint et transitoire)
// 19/10/20 NLD Ajout CATSoftwareConfigurationCreation_ForTessTemporary
//              (licence temporaire; usage restreint et transitoire)
//=============================================================================
#include "ExportedByCATMathStream.h"

typedef enum {
              CATSoftwareConfigurationCreation_NotLicensed        = 0,
              CATSoftwareConfigurationCreation_ForCGMObject       = 1,
              CATSoftwareConfigurationCreation_ForCGMReplay       = 2,
              CATSoftwareConfigurationCreation_ForCGMTest         = 3,
              CATSoftwareConfigurationCreation_ForCGMUnStream     = 4,
              // licences transitoires pour phase de migration
              CATSoftwareConfigurationCreation_ForSubdTemporary   = 11,
              CATSoftwareConfigurationCreation_ForTessTemporary   = 12
             }CATSoftwareConfigurationCreation_License;

extern "C" ExportedByCATMathStream
// NLD229011 Pour recensement statique (XRef) et dynamique des créations de configuration ouverte
//           N.B pas d'argument par défaut pour éviter conflit avec la signature sans argument
CATSoftwareConfiguration *CATCreateSoftwareConfiguration(CATSoftwareConfigurationCreation_License License);

//-------------------------------------------------------------
// Rend le compteur de création de configurations ouvertes sans licence
extern "C" ExportedByCATMathStream
int GetCATSoftwareConfigurationNbUnlicensedOpenCreations();

#endif
