<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Explore">
    <Type>DMUValidationValidation</Type>
    <Query type="Expand">
      <AddType>DMUValidationValidation</AddType>
      <AddType>DMUValidationCheck</AddType>
      <AddType>DMUValidationExposedPresentation</AddType>
      <AddType>DMUValidationContext</AddType>
      <AddType>DMUValidationParticipants</AddType>
      <AddType>DMUValidationValidated</AddType>
      <AddType>DMUValidationReviewInstance</AddType>
      <AddType>DMUValidationReviewReference</AddType>
      <AddType>DMUValidationReviewRepInstance</AddType>
      <AddType>DMUValidationReviewRepReference</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <LoadPointed from="DMUValidationContext" to="PLMWspPVS" option="dmu_monocontext" role="DMU_Context">Explore</LoadPointed>
    <LoadPointed from="DMUValidationContext" to="VPMReference" option="dmu_monocontext" role="DMU_Context">Explore</LoadPointed>
    <LoadPointed from="DMUValidationContext" to="SIMItfSimulation" option="dmu_monocontext" role="DMU_Context">Explore</LoadPointed>
    <LoadPointed from="DMUValidationContext" to="PLMCoreReference" role="DMU_Context">Explore</LoadPointed>
    <LoadPointed from="DMUValidationContext" to="PLMCoreRepReference">ExploreForReview|Explore|Authoring</LoadPointed>
  </Profile>
  <Profile name="Explore">
    <Type>DMUValidationExposedPresentation</Type>
    <Query type="Navigate">
      <AddType>DMUValidationExposedPresentation</AddType>
      <AddType>DMUValidationValidation</AddType>
      <Path from="DMUValidationExposedPresentation" to="DMUValidationValidation" direct="false"/>    
    </Query>
    <Transition from="DMUValidationValidation">Explore</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
     <Level state="Full">All</Level>   
  </Profile>
</Profiles>
