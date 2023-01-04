<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>PLMProfile</Type>
    <Type>PLMCheck</Type>
    <Type>PLMPreCondCheck</Type>
    <Type>PLMFilteringCheck</Type>
    <Query type="Expand">
      <AddType>PLMProfile</AddType>
      <AddType>PLMProfileProcessingGroup</AddType>
      <AddType>PLMProfileCheckInstance</AddType>
      <AddType>PLMStopCondition</AddType>
      <AddType>PLMAssessmentResultRepReference</AddType>
      <AddType>PLMFilteringCheck</AddType>
      <AddType>PLMPreCondCheck</AddType>
      <AddType>PLMCheck</AddType>
      <AddType>PLMProfileCheckInstancetoPLMCheck</AddType>
      <AddType>PLMProfiletoPLMProfileCheckInstance</AddType>
      <AddType>PLMProfileCheckInstancetoPLMPreCondCheck</AddType>
      <AddType>PLMProfileCheckInstancetoPLMFilteringCheck</AddType>
      <AddType>PLMProfiletoPLMProfileProcessingGroup</AddType>
      <AddType>PLMProfileProcessingGrouptoPLMPreCondCheck</AddType>
      <AddType>PLMCoreReferencetoPLMAssessmentResultRepReference</AddType>
      <AddType>PLMProfileProcessingGrouptoPLMStopCondition</AddType>
      <AddType>PlmParameter</AddType>
      <AddType>ParameterAggregation</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Inherited</Level>
  </Profile>
</Profiles>
