<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>PLMWspReference</Type>
    <Query type="Expand">
      <AddType>PLMWspSpecConnection</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <LoadPointed from="PLMWspSpecConnection" to="VPMReference" role="WSPPvsRoot" category="Reference">Authoring</LoadPointed>
  </Profile>
</Profiles>
