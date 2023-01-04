<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="3DPlay">
    <Type>Stu3DExperience</Type>
    <Query type="Expand">
      <AddType level="Full">Stu3DExperience</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
    <LoadPointed from="Stu3DExperience" to="VPMReference" role="PLMExp_toAsset" prereq="true" result="false">3DPlayForExperience</LoadPointed>
    <LoadPointed from="Stu3DExperience" to="CATMatReference" role="PLMExp_toAsset" result="false">3DPlay</LoadPointed>
    <!-- 3DExperience -> 3DExperience-->
    <LoadPointed from="Stu3DExperience" to="Actor3DExperience" role="PLMExp_toPrototype" >3DPlay</LoadPointed>
    <LoadPointed from="Stu3DExperience" to="Behavior3DExperience" role="PLMExp_toPrototype" >3DPlay</LoadPointed>
    <LoadPointed from="Stu3DExperience" to="Stu3DExperience" role="PLMExp_toVariable" >3DPlay</LoadPointed>
    <LoadPointed from="Stu3DExperience" to="Stu3DExperience" role="PLMExp_toValue" >3DPlay</LoadPointed>
  </Profile>
  <Profile name="3DPlay">
    <Type>Actor3DExperience</Type>
    <Query type="Expand">
      <AddType level="Full">Actor3DExperience </AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
    <LoadPointed from="Actor3DExperience" to="VPMReference" role="PLMExp_toAsset" prereq="true" result="false">3DPlayForExperience</LoadPointed>
    <LoadPointed from="Actor3DExperience" to="CATMatReference" role="PLMExp_toAsset" result="false">3DPlay</LoadPointed>
    <!-- 3DExperience -> 3DExperience-->
    <LoadPointed from="Actor3DExperience" to="Actor3DExperience" role="PLMExp_toPrototype" >3DPlay</LoadPointed>
    <LoadPointed from="Actor3DExperience" to="Behavior3DExperience" role="PLMExp_toPrototype" >3DPlay</LoadPointed> 
    <LoadPointed from="Actor3DExperience" to="Stu3DExperience" role="PLMExp_toVariable" >3DPlay</LoadPointed>
    <LoadPointed from="Actor3DExperience" to="Stu3DExperience" role="PLMExp_toValue" >3DPlay</LoadPointed>
  </Profile>
  <Profile name="3DPlay">
    <Type>Behavior3DExperience</Type>
    <Query type="Expand">
      <AddType level="Full">Behavior3DExperience </AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
    <LoadPointed from="Behavior3DExperience" to="VPMReference" role="PLMExp_toAsset" prereq="true" result="false">3DPlayForExperience</LoadPointed>
    <LoadPointed from="Behavior3DExperience" to="CATMatReference" role="PLMExp_toAsset" result="false">3DPlay</LoadPointed>
    <!-- 3DExperience -> 3DExperience-->
    <LoadPointed from="Behavior3DExperience" to="Actor3DExperience" role="PLMExp_toPrototype" >3DPlay</LoadPointed>
    <LoadPointed from="Behavior3DExperience" to="Behavior3DExperience" role="PLMExp_toPrototype" >3DPlay</LoadPointed> 
    <LoadPointed from="Behavior3DExperience" to="Stu3DExperience" role="PLMExp_toVariable" >3DPlay</LoadPointed>
    <LoadPointed from="Behavior3DExperience" to="Stu3DExperience" role="PLMExp_toValue" >3DPlay</LoadPointed>
  </Profile>
  <Profile name="3DPlay">
    <Type>Abstract3DExperienceObject</Type>
    <Query type="Expand">
      <AddType level="Full">Abstract3DExperienceObject</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
    <LoadPointed from="Abstract3DExperienceObject" to="VPMReference" role="PLMExp_toAsset" prereq="true" result="false">3DPlayForExperience</LoadPointed>
    <LoadPointed from="Abstract3DExperienceObject" to="CATMatReference" role="PLMExp_toAsset" result="false">3DPlay</LoadPointed>
    <!-- 3DExperience -> 3DExperience-->
    <LoadPointed from="Abstract3DExperienceObject" to="Abstract3DExperienceObject" role="PLMExp_toPrototype" >3DPlay</LoadPointed>
    <LoadPointed from="Abstract3DExperienceObject" to="Abstract3DExperienceObject" role="PLMExp_toVariable" >3DPlay</LoadPointed>
    <LoadPointed from="Abstract3DExperienceObject" to="Abstract3DExperienceObject" role="PLMExp_toValue" >3DPlay</LoadPointed>
  </Profile>
</Profiles>

