#ifndef CATCGMVersionningDefVarTHM_h
#define CATCGMVersionningDefVarTHM_h

//-------------------------------------------------------------------------------------
// Pour definir une nouvelle variable de versionning, decommenter les lignes suivantes
//-------------------------------------------------------------------------------------
// Ligne 1 : Verifie que la variable n'est pas declaree en officiel
// Ligne 2 : Definition de la variable et affectation (32000 non activee)


// THM section
// Not declared section:

#ifndef CGM_Versionning_Boolean_AllowMultiFaceBoundarySkins
#define CGM_Versionning_Boolean_AllowMultiFaceBoundarySkins Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Boolean_AllowMultiFaceBoundarySkins)

#ifndef CGM_Versionning_Boolean_InterSkinMergeFromSameShell
#define CGM_Versionning_Boolean_InterSkinMergeFromSameShell Version_Lvl_MaxValue
#endif

BOO_VERSIONNING_FUNCTION(Boolean_InterSkinMergeFromSameShell);


#ifndef CGM_Versionning_SplitDOCO_RetryExtrapolationC1
#define CGM_Versionning_SplitDOCO_RetryExtrapolationC1 Version_Lvl_MaxValue
#endif


BOO_VERSIONNING_FUNCTION(SplitDOCO_RetryExtrapolationC1);
BOO_VERSIONNING_FUNCTION(CompatibleMultiBody_EmptyInputs);
BOO_VERSIONNING_FUNCTION(TopoPCrvExtrem);
BOO_VERSIONNING_FUNCTION(Revol_ReorderIfProfileOnAxis);
BOO_VERSIONNING_FUNCTION(CompatibleMultiBody_SuppressMode);
BOO_VERSIONNING_FUNCTION(Disconnect_JournalSuppressCuttingVertices);
BOO_VERSIONNING_FUNCTION(SubdGraph_OrphanBarDelayConnectorDelete);
BOO_VERSIONNING_FUNCTION(Extrude_NoECSharing_Closed2EdgeProfile);



#ifndef CGM_Versionning_ThickWireTwoOffsets
#define CGM_Versionning_ThickWireTwoOffsets Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_SweepRelimit_UpdateSimplifyJournalNonUnion
#define CGM_Versionning_SweepRelimit_UpdateSimplifyJournalNonUnion Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Extrude_BestRelimitation3_Prism
#define CGM_Versionning_Extrude_BestRelimitation3_Prism Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Extrude_BestRelimitation3_Revol
#define CGM_Versionning_Extrude_BestRelimitation3_Revol Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Revol_SelectIntersection_ProfileOnAxis
#define CGM_Versionning_Revol_SelectIntersection_ProfileOnAxis Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Extrude_EmptyTrimBodyGuard
#define CGM_Versionning_Extrude_EmptyTrimBodyGuard Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Extrude_EmptyTrimBodyGuard);

#ifndef CGM_Versionning_Extrude_PreventMixedLimitInterfaceCalls
#define CGM_Versionning_Extrude_PreventMixedLimitInterfaceCalls Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Extrude_PreventMixedLimitInterfaceCalls);

// Currently used for prototype code which tries to make CATSweepGraph independent
#ifndef CGM_Versionning_Extrude_Relimit4
#define CGM_Versionning_Extrude_Relimit4 Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Extrude_Relimit4);

// Declared not activated section:

BOO_VERSIONNING_FUNCTION(InterTopo_ReportByCuttingsAlways);

// Prototype fix for IR576261
#ifndef CGM_Versionning_MarkAdjoiningEdgesAfterEliminateDegenerate
#define CGM_Versionning_MarkAdjoiningEdgesAfterEliminateDegenerate Version_Lvl_MaxValue
#endif

// Avoids some plane positioning for Profile Closure cases.
// Currently causes issues with ThinSolid profile closure cases
// NewTopoRIRevol1 Case017, NewTopoThinSolidRevol Case024, Case026A
#ifndef CGM_Versionning_Revol_UseInitialProfileForPositionBody 
#define CGM_Versionning_Revol_UseInitialProfileForPositionBody Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Extrude_SelectUsingWireProfile
#define CGM_Versionning_Extrude_SelectUsingWireProfile Version_Lvl_MaxValue
#endif

// Switch Sweep Journal mode on by default
#ifndef CGM_Versionning_Extrude_AddLimitJournalInfoDefault
#define CGM_Versionning_Extrude_AddLimitJournalInfoDefault Version_Lvl_MaxValue
#endif

// For use in removing the filter which still applies the shift to certain cases
#ifndef CGM_Versionning_FullRevolutionWithoutShiftComplete
#define CGM_Versionning_FullRevolutionWithoutShiftComplete Version_Lvl_MaxValue
#endif

// Protects existing Revol journal coherence failures, and fixes for those failures
// Defined officially; kept here as a record of what needs to be done to activate it
#ifndef CGM_Versionning_Extrude_RevolJournalCoherence
#define CGM_Versionning_Extrude_RevolJournalCoherence Version_Lvl_MaxValue
#endif
// THM End section


#endif
