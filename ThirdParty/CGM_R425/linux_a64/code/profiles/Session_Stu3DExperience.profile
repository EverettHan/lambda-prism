<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Explore">
    <Type>Stu3DExperience</Type>
    <Query type="Expand">
      <AddType level="Full">Stu3DExperience</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
    <LoadPointed from="Stu3DExperience" to="VPMReference" role="PLMExp_toAsset">Explore</LoadPointed>

    <!--En commentaire car on se limite aux Stu3DExperience consommant un product – restriction demandée par LLV-->
    <!--<LoadPointed from="Stu3DExperience" to="CATMatReference" role="PLMExp_toAsset">Explore</LoadPointed>-->
    <!--<LoadPointed from="Stu3DExperience" to="PLMWspPVS" role="PLMExp_toAsset" compactable="false">Explore</LoadPointed>-->

    <LoadPointed from="Stu3DExperience" to="Stu3DExperience" role="PLMExp_toPrototype">Explore</LoadPointed>
    <LoadPointed from="Stu3DExperience" to="Stu3DExperience" role="PLMExp_toVariable">Explore</LoadPointed>
    <LoadPointed from="Stu3DExperience" to="Stu3DExperience" role="PLMExp_toValue">Explore</LoadPointed>
  </Profile>
</Profiles>
