<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  
  <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>3DExperience</Type>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
    <LoadPointed from="3DExperience" to="VPMReference" role="PLMExp_toAsset">Authoring</LoadPointed>
    <LoadPointed from="3DExperience" to="CATMatReference" role="PLMExp_toAsset">Authoring</LoadPointed>
    <LoadPointed from="3DExperience" to="PLMWspPVS" role="PLMExp_toAsset" compactable="false">Authoring</LoadPointed>
    <LoadPointed from="3DExperience" to="Abstract3DExperienceObject" role="PLMExp_toPrototype" result="false"></LoadPointed>
    <LoadPointed from="3DExperience" to="SIMObjSimulationObjectGeneric" role="PLMExp_toAsset" result="false"></LoadPointed>
    <LoadPointed from="3DExperience" to="3DExperience" role="PLMExp_toPrototype">Authoring</LoadPointed>
    <LoadPointed from="3DExperience" to="3DExperience" role="PLMExp_toVariable">Authoring</LoadPointed>
    <LoadPointed from="3DExperience" to="3DExperience" role="PLMExp_toValue">Authoring</LoadPointed>
  </Profile>

   <!-- Completion specifique pour 3DExperience pointant un asset PPR (chargement depuis CV) -->
   <Profile name="AuthoringWithAssetLight" OldTypingSupport='Y'>
    <Type>3DExperience</Type>
    <Query type="Expand">
      <AddType level="Full">3DExperience</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
	<LoadPointed from="3DExperience" to="PPRContext" role="PLMExp_toAsset">LightAsset</LoadPointed>
    <LoadPointed from="3DExperience" to="PLMWspPVS" role="PLMExp_toAsset" compactable="false">Authoring</LoadPointed>
    <LoadPointed from="3DExperience" to="3DExperience" role="PLMExp_toPrototype">Authoring</LoadPointed>
    <LoadPointed from="3DExperience" to="3DExperience" role="PLMExp_toVariable">Authoring</LoadPointed>
    <LoadPointed from="3DExperience" to="3DExperience" role="PLMExp_toValue">Authoring</LoadPointed>
  </Profile>
  
   <Profile name="AuthoringLight" OldTypingSupport='Y'>
    <Type>3DExperience</Type>
    <Query type="Expand">
      <AddType level="Full">3DExperience</AddType>
    </Query>
	<Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
  </Profile>
</Profiles>

