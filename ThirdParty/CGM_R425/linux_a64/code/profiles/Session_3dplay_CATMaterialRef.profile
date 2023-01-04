<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="3DPlay">
    <Type>CATMatReference</Type>
    <Query type="Expand">
      <AddType>CATMatReference</AddType>
      <AddType>CATMatRefInstance</AddType>
      <AddType>MaterialDomainInstance</AddType>
      <AddType>MaterialDomain</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <LoadPointed from="MaterialDomain" to="PLMDMTDocument" result="false">3DPlay</LoadPointed>
    <LoadPointed from="MaterialDomain" to="dsc_matref_rep_Rendering" result="false">3DPlay</LoadPointed>
  </Profile>
</Profiles>
