<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="3DShapeByMeWithAssembly_Explore">
    <Type>VPMReference</Type>
    <Query type="Expand">
      <AddType>VPMReference</AddType>
      <AddType>3DShape</AddType>
      <AddType>VPMInstance</AddType>
      <AddType>VPMRepInstance</AddType>
      <AddType>CATMCXMechanicalConnection</AddType>
      <RemoveType>PLMFst_MCX</RemoveType>
      <RemoveType>PLMFst_MCX_X</RemoveType>
    </Query>
    <Level state="Light">Inherited</Level>
    <Level state="Navigation">Inherited</Level>
    <Level state="Full">Inherited</Level>
    <LoadPointed from="CATMCXMechanicalConnection" to="VPMReference">3DShapeByMeWithAssembly_Explore</LoadPointed>
  </Profile>
</Profiles>
