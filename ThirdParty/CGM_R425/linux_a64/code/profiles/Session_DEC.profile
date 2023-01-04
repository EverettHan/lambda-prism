<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Explore">
    <Type>MCAD Assembly</Type>
    <Query type="Expand">
      <AddType>CgrViewable</AddType>
      <AddType>CAD SubComponent</AddType>
      <AddType>Viewable</AddType>
      <AddType>MCAD Assembly</AddType>
      <AddType>MCAD Component</AddType>
      <Path from="MCAD Assembly" through="CAD SubComponent" to="MCAD Component"/>
      <Path from="MCAD Assembly" through="CAD SubComponent" to="MCAD Assembly"/>
      <Path from="MCAD Component" through="Viewable" to="CgrViewable"/>
    </Query>
    <Level state="Light">Inherited</Level>
    <Level state="Navigation">Inherited</Level>
    <Level state="Full">None</Level>
  </Profile>
  <Profile name="Explore">
    <Type>MCAD Component</Type>
    <Query type="Expand">
      <AddType>CgrViewable</AddType>
      <AddType>Viewable</AddType>
      <AddType>MCAD Component</AddType>
      <Path from="MCAD Component" through="Viewable" to="CgrViewable"/>
    </Query>
    <Level state="Light">Inherited</Level>
    <Level state="Navigation">Inherited</Level>
    <Level state="Full">None</Level>
  </Profile>
</Profiles>
