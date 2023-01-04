<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Explore">
    <Type>Drawing</Type>
    <Query type="Expand">
      <AddType>VPMReference</AddType>
      <AddType>VPMInstance</AddType>
      <AddType>VPMRepInstance</AddType>
      <AddType>Drawing</AddType>
    </Query>
    <Transition from="Drawing" result="false">Authoring</Transition>
    <Level state="Light">Inherited</Level>
    <Level state="Navigation">Inherited</Level>
    <Level state="Full">None</Level>
  </Profile>
  <Profile name="Authoring">
    <Type>Drawing</Type>
    <Query type="Expand">
      <AddType>Drawing</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
  </Profile>
 </Profiles>
