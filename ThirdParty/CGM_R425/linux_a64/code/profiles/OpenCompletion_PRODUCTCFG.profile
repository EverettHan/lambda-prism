<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  
 <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>VPMReference</Type>
    <Type>DELLmiAbstractProductionEntity</Type>
    <Type>DELFmiFunctionReference</Type>
    <Type>ObjectTypeReference</Type>
	<Type>DMUValidationReviewReference</Type>
    <Type>EnsSpecification</Type>
    <Query type="Expand">
      <AddType option="no_type_retriever">PLMCoreReference</AddType> 
      <AddType option="no_type_retriever">PLMCoreInstance</AddType>
      <AddType option="integrity_reps">LPPrivateRepInstance</AddType>
      <AddType option="integrity_reps">PGPRep</AddType>
      <AddType option="integrity_reps">InstanciationDefinition</AddType>
      <AddType option="integrity_reps">InstanciationValue</AddType>
      <AddType option="time_analysis">DELTimeAnalysisRepInstance</AddType>
      <AddType option="time_analysis">DELTimeAnalysisRepReference</AddType>
      <AddType option="integrity_reps">DELLmiDocRepInstance</AddType>
      <AddType option="integrity_reps">ProductionSystemDocumentation</AddType>
      <AddType option="integrity_reps">ProductionSystemDecoration</AddType>
      <AddType option="integrity_reps">ProductionSystemPlugBehavior</AddType>
      <AddType option="integrity_reps">ProductionSystemShiftSchedule</AddType>
      <AddType option="integrity_reps">DELFmiFunctionRepresentationInstance</AddType>
      <AddType option="integrity_reps">DELFmiPicture</AddType>
      <AddType option="integrity_reps">VPMRepInstance</AddType>
      <AddType option="integrity_reps">Behavior</AddType>
      <AddType option="aec_object_type">ObjectTypeRepInstance</AddType>
      <AddType option="aec_object_type">KnowledgewareObjectType</AddType>
      <AddType option="integrity_reps">HumanRepRef</AddType>
	  <AddType option="integrity_reps">Machining</AddType>
	  <AddType option="integrity_reps">NCMachiningPgmFiles</AddType>
      <AddType option="integrity_reps">ElecSymbol2DRep</AddType>
      <AddType option="integrity_reps">ElectricalConductorRepository</AddType>
      <AddType option="integrity_reps">RFLPLMFunctionalRepInstance</AddType>
      <AddType option="integrity_reps">Schema</AddType>
      <AddType option="integrity_reps">RFLVPMLogicalRepInstance</AddType>
      <AddType option="integrity_reps">Schema_Log</AddType>
      <AddType option="3dshape_reps">3DShape</AddType>
      <AddType option="3dshape_reps">CATSysBehaviorLibRepInstance</AddType>
      <AddType option="3dshape_reps">Behavior_Continuous_Root</AddType>
      <AddType option="3dshape_reps">Behavior_Discrete_Root</AddType>
      <AddType option="3dshape_reps">TestBehavior_Root</AddType>
      <AddType option="3dshape_reps">Review</AddType>
	  <AddType option="3dshape_reps">CAT_Distiller_RepRef</AddType>
      <AddType option="3dshape_reps">SpotFastener_Representation</AddType>
      <AddType option="3dshape_reps">BeadFastener_Representation</AddType>
      <AddType option="3dshape_reps">LocFastener_Representation</AddType>
      <AddType option="3dshape_reps">CbaRepSkeleton</AddType>
      <AddType option="custom_reps">Drawing</AddType>
      <AddType option="custom_reps">Knowledgeware</AddType>
      <AddType option="custom_reps">Mechanism</AddType>
      <AddType option="custom_reps">DMUValidationReviewRepInstance</AddType>
      <AddType option="custom_reps">VALReview</AddType>
      <AddType option="custom_reps">BehaviorSpecification</AddType>
      <AddType option="custom_reps">Human</AddType>
      <AddType option="custom_reps">Automation</AddType>
      <AddType option="custom_reps">Ambience</AddType>
      <AddType option="custom_reps">Rendering</AddType>
      <AddType option="custom_reps">FlatteningRepository</AddType>
      <AddType option="all_reps">PLMCoreRepInstance</AddType>
      <AddType option="all_reps">PLMCoreRepReference</AddType>
	  <AddType option="with_ports_and_cnxs">PLMConnection</AddType>
      <AddType option="with_ports_and_cnxs">PLMPort</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Inherited</Level>
  </Profile>
  <Profile name="SmartOpen" OldTypingSupport='Y'>
    <Type>3DShape</Type>
    <Type>SIMShape</Type>
    <Type>FEM</Type>
    <Type>VPMRepReference</Type> <!-- a supprimer qd on aura supprime old typing -->
    <Query type="Expand">
      <AddType>VPMReference</AddType>
      <AddType>VPMInstance</AddType>
      <AddType>3DShape</AddType>
      <AddType>SIMShape</AddType>
      <AddType>FEM</AddType>
      <AddType>VPMRepReference</AddType> <!-- a supprimer qd on aura supprime old typing -->
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
  </Profile>
  <Profile name="LoadPLMParameters" OldTypingSupport='Y'>
	<Type>RFLPLMFunctionalReference</Type>
    <Type>RFLVPMLogicalReference</Type>
    <Type>RFLPLMFunctionalCommunicationReference</Type>
    <Type>RFLVPMLogicalCommunicationReference</Type>
    <Query type="Expand">
	  <AddType>RFLPLMFunctionalReference</AddType>
      <AddType>RFLVPMLogicalReference</AddType>
	  <AddType>RFLPLMFunctionalCommunicationReference</AddType>
      <AddType>RFLVPMLogicalCommunicationReference</AddType>
      <AddType>ParameterUsage</AddType>
      <AddType>ParameterAggregation</AddType>
      <AddType>PlmParameter</AddType>
      <AddType>ParameterComposition</AddType>
      <AddType>ComposedParameter</AddType>
	</Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
  </Profile>
</Profiles>


