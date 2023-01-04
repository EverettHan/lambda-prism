<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Explore">
    <Type>Part</Type>
    <Query type="Expand">
      <AddType>Part</AddType>
      <AddType>EBOM</AddType>
      <AddType option="documents">Document</AddType>
      <AddType option="documents">Reference Document</AddType>
      <AddType level="Full">CATMatConnection</AddType>
    </Query>
    <Level state="Light">Inherited</Level>
    <Level state="Navigation">Inherited</Level>
    <Level state="Full">None</Level>
    <LoadPointed from="CATMatConnection" to="CATMatReference">Explore</LoadPointed>
	<Transition from="Document">Authoring</Transition>
  </Profile>
  <Profile name="Authoring">
    <Type>Part</Type>
    <Query type="Expand">
      <AddType>Part</AddType>
      <AddType>EBOM</AddType>
    </Query>
    <Level state="Light">Inherited</Level>
    <Level state="Navigation">Inherited</Level>
    <Level state="Full">None</Level>
  </Profile>
</Profiles>
