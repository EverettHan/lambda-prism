<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>ManufacturingSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
      <AddType>SIMObjectSimulationPublishedResultCnx</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
	<LoadPointed from="SIMObjSimulationSystem" role="SIM_SimulatedProduct" category="Reference3" to="VPMReference">Authoring</LoadPointed>
	<LoadPointed from="SIMObjSimulationSystem" role="SIM_SimulatedProduct" category="Reference3" to="PPRContext">GetFirstPPRLevel</LoadPointed>
    <LoadPointed from="SIMObjectSimulationPublishedResultCnx" role="SIM_PublishedCnxOUT" to="PLMDmtDocument"></LoadPointed>
    <LoadPointed from="SIMObjectSimulationPublishedResultCnx" role="SIM_PublishedCnxOUT" to="VPMRepReference"></LoadPointed>
  </Profile>
  <Profile name="AuthoringCloudview" OldTypingSupport='Y'>
    <Type>ManufacturingSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
      <AddType>SIMObjectSimulationPublishedResultCnx</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
	<LoadPointed from="SIMObjSimulationSystem" role="SIM_SimulatedProduct" category="Reference3" to="VPMReference">Authoring</LoadPointed>
	<LoadPointed from="SIMObjSimulationSystem" role="SIM_SimulatedProduct" category="Reference3" to="PPRContext">AuthoringCloudview</LoadPointed>
    <LoadPointed from="SIMObjectSimulationPublishedResultCnx" role="SIM_PublishedCnxOUT" to="PLMDmtDocument"></LoadPointed>
    <LoadPointed from="SIMObjectSimulationPublishedResultCnx" role="SIM_PublishedCnxOUT" to="VPMRepReference"></LoadPointed>
  </Profile>
  <Profile name="AuthoringCloudviewNoRep" OldTypingSupport='Y'>
    <Type>ManufacturingSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
      <AddType>SIMObjectSimulationPublishedResultCnx</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
	<LoadPointed from="SIMObjSimulationSystem" role="SIM_SimulatedProduct" category="Reference3" to="VPMReference">Authoring</LoadPointed>
	<LoadPointed from="SIMObjSimulationSystem" role="SIM_SimulatedProduct" category="Reference3" to="PPRContext">AuthoringCloudviewNoRep</LoadPointed>
    <LoadPointed from="SIMObjectSimulationPublishedResultCnx" role="SIM_PublishedCnxOUT" to="PLMDmtDocument"></LoadPointed>
    <LoadPointed from="SIMObjectSimulationPublishedResultCnx" role="SIM_PublishedCnxOUT" to="VPMRepReference"></LoadPointed>
  </Profile>
  <Profile name="OpenWithoutModel" OldTypingSupport='Y'>
    <Type>ManufacturingSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
      <AddType>SIMObjectSimulationPublishedResultCnx</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <LoadPointed from="SIMObjectSimulationPublishedResultCnx" role="SIM_PublishedCnxOUT" to="PLMDmtDocument"></LoadPointed>
    <LoadPointed from="SIMObjectSimulationPublishedResultCnx" role="SIM_PublishedCnxOUT" to="VPMRepReference"></LoadPointed>
  </Profile>
</Profiles>
