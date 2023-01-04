<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <!--Note that, in order to be integrated in 3DLive Explore command, it is mandatory to provide a default profile called “Explore”.-->
  <Profile name="MainExplore">
    <Type>BioDigitalClinicStudy</Type>
    <Query type="Expand">
      <AddType>BioDigitalClinicStudy</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
  <Profile name="MainExplore">
    <Type>BioChemicalSafetyStudy</Type>
    <Query type="Expand">
      <AddType>BioChemicalSafetyStudy</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
  <Profile name="MainExplore">
    <Type>BioBiologicsSafetyStudy</Type>
    <Query type="Expand">
      <AddType>BioBiologicsSafetyStudy</AddType>
      <AddType>BioHasProtein</AddType>
      <AddType>BioMockUp_Protein</AddType>
      <Path>
        <Step from="BioBiologicsSafetyStudy" to="BioHasProtein" direct="false"/>
        <Step from="BioHasProtein" to="BioMockUp_Protein" direct="true"/>
      </Path>
    </Query>  
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile> 
  <Profile name="MainExplore">
    <Type>BioAdverseOutcomeStudy</Type>
    <Query type="Expand">
      <AddType>BioAdverseOutcomeStudy</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
</Profiles>
