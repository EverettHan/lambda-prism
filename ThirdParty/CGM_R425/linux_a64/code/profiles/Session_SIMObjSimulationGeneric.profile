<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Explore">
    <Type>SIMObjSimulationObjectGeneric</Type>
    <Query type="Expand">
      <AddType type="SIMObjSimulationObjectGeneric"/>
      <AddType type="SIMObjSimulationCategoryInstance"/>
      <AddType type="SIMObjSimulationV5RepInstanceGeneric"/>
      <AddType type="SIMObjSimulationRepInstanceGeneric"/>
      <AddType type="SIMObjSimulationRepReferenceGeneric"/>
      <AddType type="PLMDocConnection"/>
      <AddType type="SIMObjectSimulationPublishedResultCnx"/>
      <AddType type="SIMObjSimulationSystem"/>
      <AddType type="SIMObjSimulationCategoryReference" level="Navigation">
        <ExtraAttribute>V_discipline</ExtraAttribute>
      </AddType>
      <AddType type="SIMObjSimulationV5RepReferenceGeneric" level="Navigation">
        <ExtraAttribute>V_discipline</ExtraAttribute>
      </AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">All</Level>
    <Level state="Full">None</Level>
  </Profile>
</Profiles>
