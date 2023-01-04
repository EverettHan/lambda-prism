<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="MainExplore">
    <Type>BioMockUp_Protein</Type>
    <Query type="Expand">
      <AddType>BioMockUp_Protein</AddType>
      <AddType>BioMockUp_HasSequence</AddType>
      <AddType>BioMockUp_Sequence</AddType>
      <AddType>BioMockUp_HasPositionalFeature</AddType>
      <AddType>BioMockUp_PositionalFeature</AddType>
      <Path>
        <Step from="BioMockUp_Protein" to="BioMockUp_HasSequence" direct="false"/>
        <Step from="BioMockUp_HasSequence" to="BioMockUp_Sequence" direct="true"/>
        <Step from="BioMockUp_Sequence" to="BioMockUp_HasPositionalFeature" direct="false"/>
        <Step from="BioMockUp_HasPositionalFeature" to="BioMockUp_PositionalFeature" direct="true"/>
      </Path>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
  <Profile name="MainExplore">
    <Type>BioMockUp_Sequence</Type>
    <Query type="Expand">
      <AddType>BioMockUp_Sequence</AddType>
      <AddType>BioMockUp_HasPositionalFeature</AddType>
      <AddType>BioMockUp_PositionalFeature</AddType>
      <Path>
        <Step from="BioMockUp_Sequence" to="BioMockUp_HasPositionalFeature" direct="false"/>
        <Step from="BioMockUp_HasPositionalFeature" to="BioMockUp_PositionalFeature" direct="true"/>
      </Path>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
</Profiles>
