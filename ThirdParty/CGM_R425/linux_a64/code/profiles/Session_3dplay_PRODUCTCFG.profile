<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="3DPlay">
    <Type>VPMReference</Type>
    <Query type="Expand">
      <AddType>VPMReference</AddType>
      <AddType>VPMInstance</AddType>
      <AddType>VPMRepInstance</AddType>
      <AddType>VPMRepReference</AddType>
      <AddType>LPPrivateRepInstance</AddType>
      <AddType>LPPrivateRepReference</AddType>
      <RemoveType>FastenerInstance</RemoveType>
    </Query>
    <Transition from="VPMReference">DecorateProduct</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
  <Profile name="DecorateProduct">
    <Type>VPMReference</Type>
    <Type>VPMInstance</Type>
    <Query type="Expand">
      <AddType level="Full">PLMPort</AddType>
      <AddType level="Full">PLMConnection</AddType>
      <AddType level="Full">CATMatConnection</AddType>
      <AddType level="Full">PLMDocConnection</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
    <LoadPointed from="CATMatConnection" to="CATMatReference">3DPlay</LoadPointed>
    <LoadPointed from="PLMDocConnection" to="PLMDMTDocument">3DPlay</LoadPointed>
  </Profile>
  <Profile name="3DPlayForExperience">
    <Type>VPMReference</Type>
    <Query type="Expand">
      <AddType>VPMReference</AddType>
      <AddType>VPMInstance</AddType>
      <AddType>VPMRepInstance</AddType>
      <AddType>VPMRepReference</AddType>
      <AddType>LPPrivateRepInstance</AddType>
      <AddType>LPPrivateRepReference</AddType>
      <RemoveType>FastenerInstance</RemoveType>
    </Query>
    <Transition from="VPMReference" result="false">DecorateProductForExperience</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
  <Profile name="DecorateProductForExperience">
    <Type>VPMReference</Type>
    <Type>VPMInstance</Type>
    <Query type="Expand">
      <AddType level="Full">PLMPort</AddType>
      <AddType level="Full">PLMConnection</AddType>
      <AddType level="Full">CATMatConnection</AddType>
      <AddType level="Full">PLMDocConnection</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
    <LoadPointed from="CATMatConnection" to="CATMatReference" result="false">3DPlay</LoadPointed>
    <LoadPointed from="PLMDocConnection" to="PLMDMTDocument" result="false">3DPlay</LoadPointed>
  </Profile>
</Profiles>
