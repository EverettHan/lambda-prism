#ifndef CATCGMVersionningDefVarQCN5_h
#define CATCGMVersionningDefVarQCN5_h

//-------------------------------------------------------------------------------------
// Pour definir une nouvelle variable de versionning, decommenter les lignes suivantes
//-------------------------------------------------------------------------------------
// Ligne 1 : Verifie que la variable n'est pas declaree en officiel
// Ligne 2 : Definition de la variable et affectation (Version_Lvl_MaxValue non activee)


// QCN5 section 
// declared variables activated
#ifndef CGM_Versionning_Pattern_ReplaceSupportChamferSurface
#define CGM_Versionning_Pattern_ReplaceSupportChamferSurface Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Pattern_ReplaceSupportChamferSurface);

#ifndef CGM_Versionning_Journal_SearchInClassIfIVHasNoInter
#define CGM_Versionning_Journal_SearchInClassIfIVHasNoInter Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Journal_SearchInClassIfIVHasNoInter);

#ifndef CGM_Versionning_CheckValidityCEOfIntersectEdges
#define CGM_Versionning_CheckValidityCEOfIntersectEdges Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(CheckValidityCEOfIntersectEdges);

// declared variables not activated
#ifndef CGM_Versionning_PolarExtremumAngleBasedOnMaterial
#define CGM_Versionning_PolarExtremumAngleBasedOnMaterial Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(PolarExtremumAngleBasedOnMaterial);

// not declared variables
#ifndef CGM_Versionning_ConditionalNoMergeECForCE
#define CGM_Versionning_ConditionalNoMergeECForCE Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(ConditionalNoMergeECForCE);

#ifndef CGM_Versionning_SweepGraphPositionUsingEdgeCenter
#define CGM_Versionning_SweepGraphPositionUsingEdgeCenter Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(SweepGraphPositionUsingEdgeCenter);

#ifndef CGM_Versionning_SplitThrowSameElemLeftRight
#define CGM_Versionning_SplitThrowSameElemLeftRight Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(SplitThrowSameElemLeftRight);

#ifndef CGM_Versionning_AbsorbRedondantCEForWire
#define CGM_Versionning_AbsorbRedondantCEForWire Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(AbsorbRedondantCEForWire);
// QCN5 end section


#endif
