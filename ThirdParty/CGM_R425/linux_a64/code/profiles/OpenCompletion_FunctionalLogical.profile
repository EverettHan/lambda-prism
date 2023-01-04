<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>RFLPLMFunctionalReference</Type>
	<Type>RFLPLMFunctionalCommunicationReference</Type>
	 <Type>RFLVPMLogicalReference</Type>
	<Type>RFLVPMLogicalCommunicationReference</Type>
    <Query type="Expand">
      <AddType>RFLPLMFunctionalReference</AddType>      
      <AddType>RFLPLMFunctionalInstance</AddType>
	  <AddType>RFLPLMFunctionalCommunicationReference</AddType>      
      <AddType>RFLPLMFunctionalCommunicationInstance</AddType>      
	   <AddType>RFLVPMLogicalReference</AddType>      
      <AddType>RFLVPMLogicalInstance</AddType>
	  <AddType>RFLVPMLogicalCommunicationReference</AddType> 
	  <AddType>RFLVPMLogicalCommunicationInstance</AddType>       
   </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Inherited</Level>
  </Profile>
  <Profile name="AuthoringDecoration" OldTypingSupport='Y'>
	<Type>RFLPLMFunctionalReference</Type>
	<Type>RFLPLMFunctionalCommunicationReference</Type>
	<Type>RFLVPMLogicalReference</Type>
	<Type>RFLVPMLogicalCommunicationReference</Type>
	<Type>RFLPLMFlowReference</Type>
    <Type>RFLVPMSystemTypeReference</Type>
    <Query type="Expand">
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
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
  </Profile>
  <Profile name="ExpandFlowAndTypesOneCall" OldTypingSupport='Y'>
    <Type>RFLPLMFlowReference</Type>
	<Type>RFLPLMFunctionalReference</Type>
	<Type>RFLPLMFunctionalCommunicationReference</Type>
	<Type>RFLVPMSystemTypeReference</Type>
	<Type>RFLVPMLogicalReference</Type>
	<Type>RFLVPMLogicalCommunicationReference</Type>
    <Query type="Expand">
	  <AddType>RFLPLMFlowReference</AddType>      
      <AddType>RFLPLMFlowInstance</AddType>
	  <AddType>RFLPLMFlowExpositionInstance</AddType>
	  <AddType>RFLVPMServicesExpositionInstance</AddType>    
	  <AddType>RFLVPMServicesReference</AddType> 
	  <AddType>RFLVPMSystemTypeReference</AddType>
	  <AddType>RFLVPMSystemTypeExpositionInstance</AddType>  
	  <AddType>RFLVPMSystemTypeInstance</AddType>  
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

   <!-- Completion specifique FL: si set FLCompletionMode=1 ou si ExpandLevel=OneLevel -->
   <Profile name="DecorateFunctionalRoot" OldTypingSupport='Y'>
	<Type>RFLPLMFunctionalCommunicationReference</Type>
	<Type>RFLVPMLogicalCommunicationReference</Type>
	<Type>RFLPLMFlowReference</Type>
	<Type>RFLPLMFunctionalReference</Type>
	<Type>RFLVPMSystemTypeReference</Type>
	<Type>RFLVPMLogicalReference</Type>
    <Type>RFLVPMServicesReference</Type> 
    <Query type="Expand">
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
    </Query>
	 <Level state="Light">None</Level>
     <Level state="Navigation">None</Level>
     <Level state="Full">1</Level>
   </Profile>
   <Profile name="DecorateFunctionalContext" OldTypingSupport='Y'>
    <Type>RFLPLMFlowReference</Type>
	<Type>RFLPLMFunctionalReference</Type>
	<Type>RFLPLMFunctionalCommunicationReference</Type>
	<Type>RFLVPMSystemTypeReference</Type>
	<Type>RFLVPMLogicalReference</Type>
	<Type>RFLVPMLogicalCommunicationReference</Type>
	<Type>RFLVPMServicesReference</Type> 
    <Query type="Expand">
	  <AddType>PLMCoreRepInstance</AddType>
      <AddType>Schema_Log</AddType>
      <AddType>Picture_Log</AddType>
	  <AddType>Schema</AddType>
      <AddType>Picture</AddType>
      <AddType>PLMEleGroup</AddType>
      <AddType>PLMEleGroupExtremity</AddType>
      <AddType>PLMElecLogicalPinAllocation</AddType>
      <AddType>PLMPort</AddType>
    </Query>
	 <Level state="Light">None</Level>
     <Level state="Navigation">None</Level>
     <Level state="Full">1</Level>
   </Profile>
   <Profile name="ExpandFlowAndTypes" OldTypingSupport='Y'>
    <Type>RFLPLMFlowReference</Type>
	<Type>RFLPLMFunctionalReference</Type>
	<Type>RFLVPMSystemTypeReference</Type>
	<Type>RFLVPMLogicalReference</Type>
	<Type>RFLVPMServicesReference</Type> 
    <Query type="Expand">
	  <AddType>RFLPLMFlowReference</AddType>      
      <AddType>RFLPLMFlowInstance</AddType>
	  <AddType>RFLPLMFlowExpositionInstance</AddType>
	  <AddType>RFLVPMServicesExpositionInstance</AddType>    
	  <AddType>RFLVPMServicesReference</AddType> 
	  <AddType>RFLVPMSystemTypeReference</AddType> 
	  <AddType>RFLVPMSystemTypeExpositionInstance</AddType>  
	  <AddType>RFLVPMSystemTypeInstance</AddType>
    </Query>
	 <Level state="Light">None</Level>
     <Level state="Navigation">None</Level>
     <Level state="Full">1</Level>
   </Profile>
   <Profile name="ExpandFlowAndTypes" OldTypingSupport='Y'>
	<Type>RFLPLMFunctionalCommunicationReference</Type>
	<Type>RFLVPMLogicalCommunicationReference</Type>
    <Query type="Expand">
	  <AddType>RFLPLMFlowReference</AddType>      
      <AddType>RFLPLMFlowInstance</AddType>
	  <AddType>RFLPLMFlowExpositionInstance</AddType>
	  <AddType>RFLVPMServicesExpositionInstance</AddType>    
	  <AddType>RFLVPMServicesReference</AddType> 
	  <AddType>RFLVPMSystemTypeReference</AddType> 
	  <AddType>RFLVPMSystemTypeExpositionInstance</AddType>  
	  <AddType>RFLVPMSystemTypeInstance</AddType>
    </Query>
	 <Level state="Light">None</Level>
     <Level state="Navigation">None</Level>
     <Level state="Full">2</Level>
   </Profile>
</Profiles>
