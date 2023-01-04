#ifndef CATCGMVersionningDefVarMHF_h
#define CATCGMVersionningDefVarMHF_h

//-------------------------------------------------------------------------------------
// Pour definir une nouvelle variable de versionning, decommenter les lignes suivantes
//-------------------------------------------------------------------------------------
// Ligne 1 : Verifie que la variable n'est pas declaree en officiel
// Ligne 2 : Definition de la variable et affectation (32000 non activee)

// #ifndef CGM_Versionning_MaVariableDeVersionning
// #define CGM_Versionning_MaVariableDeVersionning 32000
// #endif

// DPS : 2021 April
// Add Journal Info on faces and side edges per strip in SweepDraft result
#ifndef CGM_Versionning_PolySweepDraft_AddStripJournalInfo
#define CGM_Versionning_PolySweepDraft_AddStripJournalInfo 32000
#endif

#ifndef CGM_Versionning_Tess_Fix_SplitNonMonotonic
#define CGM_Versionning_Tess_Fix_SplitNonMonotonic 32000
#endif

#ifndef CGM_Versionning_Tess_OutOfSAG
#define CGM_Versionning_Tess_OutOfSAG 32000
#endif

#ifndef CGM_Versionning_Tess_EdgeCurve_SetPComplexity
#define CGM_Versionning_Tess_EdgeCurve_SetPComplexity 32000
#endif

#endif
