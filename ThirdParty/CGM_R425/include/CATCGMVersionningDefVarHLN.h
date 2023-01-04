#ifndef CATCGMVersionningDefVarHLN_h
#define CATCGMVersionningDefVarHLN_h

//******* Usage reserve HLN
// 26/06/17 HLN 
// 30/09/16 HLN 
// 26/05/15 HLN 6124
// 19/03/13 HLN 4939 -> 5342
// 19/03/13 HLN 4932 -> 4939
// 14/02/13 HLN Creation
//-------------------------------------------------------------------------------------
// Pour definir une nouvelle variable de versionning, decommenter les lignes suivantes
//-------------------------------------------------------------------------------------
// Ligne 1 : Verifie que la variable n'est pas declaree en officiel
// Ligne 2 : Definition de la variable et affectation (32000 non activee)

// #ifndef CGM_Versionning_Fillet_OnlyFacesNotTwistedChecked
// #define CGM_Versionning_Fillet_OnlyFacesNotTwistedChecked 6124
// #endif

#ifndef CGM_Versionning_Fillet_RelevantLimits
//#define CGM_Versionning_Fillet_RelevantLimits 7450
#define CGM_Versionning_Fillet_RelevantLimits 32000
#endif

#ifndef CGM_Versionning_Fillet_HoldCurveTracks
//#define CGM_Versionning_Fillet_HoldCurveTracks 7450
#define CGM_Versionning_Fillet_HoldCurveTracks 32000
#endif

#endif
