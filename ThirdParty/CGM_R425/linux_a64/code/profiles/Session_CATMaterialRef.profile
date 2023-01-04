<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Explore">
    <Type>CATMatReference</Type>
    <Query type="Expand">
      <AddType>CATMatReference</AddType>
      <AddType>CATMatRefInstance</AddType>
      <AddType level="Navigation">MaterialDomainInstance</AddType>
      <AddType>MaterialDomain</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <LoadPointed prereq="true" from="MaterialDomain" to="PLMDMTDocument">Authoring</LoadPointed>
  </Profile>
</Profiles>
