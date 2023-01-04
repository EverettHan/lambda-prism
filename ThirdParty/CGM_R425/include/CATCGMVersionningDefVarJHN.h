#ifndef CATCGMVersionningDefVarJHN_h
#define CATCGMVersionningDefVarJHN_h

//-------------------------------------------------------------------------------------
// Pour definir une nouvelle variable de versionning, decommenter les lignes suivantes
//-------------------------------------------------------------------------------------
// Ligne 1 : Verifie que la variable n'est pas declaree en officiel
// Ligne 2 : Definition de la variable et affectation (Version_Lvl_MaxValue non activee)


// JHN section 
// declared variables activated
BOO_VERSIONNING_FUNCTION(WirePolyline_Journal);
BOO_VERSIONNING_FUNCTION(Laydown_VertexOnMissing);
BOO_VERSIONNING_FUNCTION(Compatible_RemoveMonomial);
BOO_VERSIONNING_FUNCTION(RelimitByVolume_ExternalShell);
BOO_VERSIONNING_FUNCTION(Spline_TooManyConnectionCurves);
BOO_VERSIONNING_FUNCTION(JournalTools_NoInsideCells);
BOO_VERSIONNING_FUNCTION(Posage_DegeneratedCEAfterMoveOn);
BOO_VERSIONNING_FUNCTION(Projection_VersionningForProjectionReport);
BOO_VERSIONNING_FUNCTION(AssembleWire_Quicker);
BOO_VERSIONNING_FUNCTION(SmartProjection_MaxDistance);
BOO_VERSIONNING_FUNCTION(PlaneAngle_MultiLine);
BOO_VERSIONNING_FUNCTION(Compatible_InternalWallsBetweenVolumes);
BOO_VERSIONNING_FUNCTION(Revol_ProfileExtrapolation);
BOO_VERSIONNING_FUNCTION(Projection_DontRemoveOtherExtremity);
BOO_VERSIONNING_FUNCTION(LayDown_ConnectionWithTolerance);
BOO_VERSIONNING_FUNCTION(Boolean_NoHomogenizeOnCLE);
BOO_VERSIONNING_FUNCTION(Compatible_NoDuplicateForBinomials);
BOO_VERSIONNING_FUNCTION(Projection_RebuildHomogenisationTable);
BOO_VERSIONNING_FUNCTION(Compatible_NonManifoldArtifact);
BOO_VERSIONNING_FUNCTION(MakeManifold_ExactComputation);
BOO_VERSIONNING_FUNCTION(Disconnect_SolutionFor6Edges);
BOO_VERSIONNING_FUNCTION(Compatible_WallFourFaceEdges);
BOO_VERSIONNING_FUNCTION(Compatible_OneSidePointSolution);
BOO_VERSIONNING_FUNCTION(Extrude_AllowIntersectingInDeadEnd);
BOO_VERSIONNING_FUNCTION(InteriorHealer_RemoveBoundaryIS);
BOO_VERSIONNING_FUNCTION(Untrim_DiscretizeBoxUV);
BOO_VERSIONNING_FUNCTION(Untrim_ResolutionForOriginalOnNurbs);
BOO_VERSIONNING_FUNCTION(Boolean_SortSameVertices);
BOO_VERSIONNING_FUNCTION(Compatible_NoAbsorbSignForEdgeAnd3Faces);
BOO_VERSIONNING_FUNCTION(Compatible_NoRealTwinForWalls);
BOO_VERSIONNING_FUNCTION(Boolean_UpdatePOECOnIV);
BOO_VERSIONNING_FUNCTION(Boolean_CouplingOnPointSolution);
BOO_VERSIONNING_FUNCTION(Intersect_InfinitePlanes);
BOO_VERSIONNING_FUNCTION(Projection_WrongHomogenizeOfEdges);
BOO_VERSIONNING_FUNCTION(BodyFromLength_GeometryOrientation);
BOO_VERSIONNING_FUNCTION(IntersectWW_SameSurfaceOnClosure);
BOO_VERSIONNING_FUNCTION(MultiTrim_NoExtrapolationForKeepAll);
BOO_VERSIONNING_FUNCTION(SplitShellByWires_RemoveDegeneratedEdges);
BOO_VERSIONNING_FUNCTION(Boolean_RetrieveRelimitationWithoutShell);
BOO_VERSIONNING_FUNCTION(Fillet_UpdateAdjacentBoundingVertex);
BOO_VERSIONNING_FUNCTION(Boolean_MultiConfusedCLEInDIsconnection);
BOO_VERSIONNING_FUNCTION(Compatible_InputAsHelpForError);
BOO_VERSIONNING_FUNCTION(Compatible_ChangeCurveAtClassUpdate);
BOO_VERSIONNING_FUNCTION(SmartProject_HiddenSeamAllowed);
BOO_VERSIONNING_FUNCTION(Trim_PerfoKeepRemove);
BOO_VERSIONNING_FUNCTION(Boolean_SoftwareConfigForMerge);
BOO_VERSIONNING_FUNCTION(Compatible_JournalUnCheck);
BOO_VERSIONNING_FUNCTION(Compatible_JournalInComputeNewVertex);
BOO_VERSIONNING_FUNCTION(Assemble_RemoveTinyFacesWithWrongOuterLocation);
BOO_VERSIONNING_FUNCTION(NewJoin_NoToleranceForMergeOfEqualEdges);
BOO_VERSIONNING_FUNCTION(Boolean_TransferIVToDestroy);
BOO_VERSIONNING_FUNCTION(RelimitBody_CleanBoolean);
BOO_VERSIONNING_FUNCTION(Close_JoinFreeBoundaries);
BOO_VERSIONNING_FUNCTION(DisconnectShell_LayDownWithArtefact);
BOO_VERSIONNING_FUNCTION(ExtrudeOperandChecker_NormalOnVertexOfLoop);
BOO_VERSIONNING_FUNCTION(Compatible_ArtifactOnConfusion);
BOO_VERSIONNING_FUNCTION(Projection_UseMissingForConfusion);
BOO_VERSIONNING_FUNCTION(Boolean_DegenerateInLightMerge);
BOO_VERSIONNING_FUNCTION(Compatible_SimpleArtefact);
BOO_VERSIONNING_FUNCTION(Compatible_ClosedSurfacePriority);
BOO_VERSIONNING_FUNCTION(Compatible_VirtualEdgeOnClosedSurface);
BOO_VERSIONNING_FUNCTION(Healing_PostJournalOptimization);
BOO_VERSIONNING_FUNCTION(Split_KeepIVFromDegenerateIE);
BOO_VERSIONNING_FUNCTION(LayDown_CouplingForAdmissible);
BOO_VERSIONNING_FUNCTION(Boolean_NoHomogenizeBetweenCFAndIE);

// declared variables not activated

#ifndef CGM_Versionning_Projection_CheckOnMissing
#define CGM_Versionning_Projection_CheckOnMissing Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Projection_NoCouplingOnWireExtremity
#define CGM_Versionning_Projection_NoCouplingOnWireExtremity Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Posage_SortTouchDownData
#define CGM_Versionning_Posage_SortTouchDownData Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Posage_SortTouchDownData);

#ifndef CGM_Versionning_Assemble_SimplifForKeptFaces
#define CGM_Versionning_Assemble_SimplifForKeptFaces   Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Assemble_SimplifForKeptFaces);

#ifndef CGM_Versionning_Compatible_JournalUselessFace
#define CGM_Versionning_Compatible_JournalUselessFace Version_Lvl_MaxValue
#endif 
BOO_VERSIONNING_FUNCTION(Compatible_JournalUselessFace);

#ifndef CGM_Versionning_BoundaryHealer_AllowMultipleResult
#define CGM_Versionning_BoundaryHealer_AllowMultipleResult Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(BoundaryHealer_AllowMultipleResult);

#ifndef CGM_Versionning_AutoCheck_TooLargeIntersection
#define CGM_Versionning_AutoCheck_TooLargeIntersection Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(AutoCheck_TooLargeIntersection);

// not declared variables

#ifndef CGM_Versionning_Projection_TrapErrorOnEdge
#define CGM_Versionning_Projection_TrapErrorOnEdge Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Projection_TrapErrorOnEdge);

#ifndef CGM_Versionning_Split_ComputeIVByProjection
#define CGM_Versionning_Split_ComputeIVByProjection Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Split_ComputeIVByProjection);

#ifndef CGM_Versionning_BodyHealer_UpdateInvalidFaces
#define CGM_Versionning_BodyHealer_UpdateInvalidFaces Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(BodyHealer_UpdateInvalidFaces);

#ifndef CGM_Versionning_BodyHealer_UpdateFacesAfterSimplifyECrv
#define CGM_Versionning_BodyHealer_UpdateFacesAfterSimplifyECrv Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(BodyHealer_UpdateFacesAfterSimplifyECrv);

#ifndef CGM_Versionning_Disconnect_CompleteConnectedBarSet
#define CGM_Versionning_Disconnect_CompleteConnectedBarSet Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Disconnect_CompleteConnectedBarSet);

#ifndef CGM_Versionning_Boolean_QuickMaxContourPositionnning
#define CGM_Versionning_Boolean_QuickMaxContourPositionnning Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Boolean_QuickMaxContourPositionnning);

#ifndef CGM_Versionning_Projection_MostContinuous
#define CGM_Versionning_Projection_MostContinuous Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Projection_MostContinuous);

#ifndef CGM_Versionning_Split_BoundaryOfShell
#define CGM_Versionning_Split_BoundaryOfShell Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Split_BoundaryOfShell);


#ifndef CGM_Versionning_Healer_EdgeDegeneration
#define CGM_Versionning_Healer_EdgeDegeneration Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Healer_EdgeDegeneration);

#ifndef CGM_Versionning_Trim_UnknownPositionning
#define CGM_Versionning_Trim_UnknownPositionning Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Trim_UnknownPositionning);

#ifndef CGM_Versionning_Compatible_KeepInterOnDegenerated
#define CGM_Versionning_Compatible_KeepInterOnDegenerated Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Compatible_KeepInterOnDegenerated);

#ifndef CGM_Versionning_Boolean_UntouchedEdge
#define CGM_Versionning_Boolean_UntouchedEdge Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Boolean_UntouchedEdge);

#ifndef CGM_Versionning_Assemble_StrangledFaces
#define CGM_Versionning_Assemble_StrangledFaces  Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Assemble_StrangledFaces);

#ifndef CGM_Versionning_Compatible_EndOfLyingOn
#define CGM_Versionning_Compatible_EndOfLyingOn Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Compatible_EndOfLyingOn);

#ifndef CGM_Versionning_Boolean_RemoveDuplicationInHomogenisation
#define CGM_Versionning_Boolean_RemoveDuplicationInHomogenisation Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Boolean_RemoveDuplicationInHomogenisation);

#ifndef CGM_Versionning_TopWire_DetectWireClosure
#define CGM_Versionning_TopWire_DetectWireClosure Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(TopWire_DetectWireClosure);

#ifndef CGM_Versionning_RelimitBody_ErrorBody
#define CGM_Versionning_RelimitBody_ErrorBody Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_StaticGlobalRatio_LengthAllocate
#define CGM_Versionning_StaticGlobalRatio_LengthAllocate Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_PropagationFace_OptionsForPointPropagation
#define CGM_Versionning_PropagationFace_OptionsForPointPropagation Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(PropagationFace_OptionsForPointPropagation);

#ifndef CGM_Versionning_LayDown_ReportSameClass
#define CGM_Versionning_LayDown_ReportSameClass Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(LayDown_ReportSameClass);

#ifndef CGM_Versionning_Compatible_DegeneratedFaceContact
#define CGM_Versionning_Compatible_DegeneratedFaceContact Version_Lvl_MaxValue
#endif
BOO_VERSIONNING_FUNCTION(Compatible_DegeneratedFaceContact);

#ifndef CGM_Versionning_MultiTrim_RemoveRedondantIV
#define CGM_Versionning_MultiTrim_RemoveRedondantIV Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Boolean_FindAllIE
#define CGM_Versionning_Boolean_FindAllIE Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Projection_MergeOnSeveralProjectedEdges
#define CGM_Versionning_Projection_MergeOnSeveralProjectedEdges Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Projection_GoOnNormalcoupling
#define CGM_Versionning_Projection_GoOnNormalcoupling Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Projection_ConfusionOnConnexVertex
#define CGM_Versionning_Projection_ConfusionOnConnexVertex Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Projection_DifferentEdgesWireConnection
#define CGM_Versionning_Projection_DifferentEdgesWireConnection Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Projection_ProjExtremityWire
#define CGM_Versionning_Projection_ProjExtremityWire Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Boolean_NarrowPartOfFace 
#define CGM_Versionning_Boolean_NarrowPartOfFace Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Projection_NoThrowAdequatReceiver
#define CGM_Versionning_Projection_NoThrowAdequatReceiver Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Projection_ChooseSideForCoupling
#define CGM_Versionning_Projection_ChooseSideForCoupling Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_LayDown_Journal
#define CGM_Versionning_LayDown_Journal Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Journal_UselessDeleteItems
#define CGM_Versionning_Journal_UselessDeleteItems Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_BooleanFace_NonManifold
#define CGM_Versionning_BooleanFace_NonManifold Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_VoB_MultiInputBdies
#define CGM_Versionning_VoB_MultiInputBdies Version_Lvl_MaxValue
#endif
// JHN end section


#endif
