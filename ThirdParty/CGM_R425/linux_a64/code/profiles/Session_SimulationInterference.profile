<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Explore">
    <Type>SIMItfSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
      <!-- Pour ramener les Contextuelles-->
      <AddType>SIMItfContextOfInterference</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <Alternates from="SIMObjSimulationSystem">
      <Alternate order="1">
        <Condition>
          <hasSR role="SIM_RootContext" category="Reference2">
          </hasSR>
        </Condition>
        <LoadPointed role="SIM_RootContext" category="Reference2" to="PLMWspPVS">Explore</LoadPointed>
      </Alternate>
      <Alternate order="2">
        <LoadPointed role="SIM_SimulatedProduct" category="Reference3" to="VPMReference">Explore</LoadPointed>
      </Alternate>
    </Alternates>
    <LoadPointed from="SIMItfContextOfInterference"      to="PLMPIMMetricReference"      role="PIM_Metric"           category="Reference4" result="false">LoadMetric</LoadPointed>
  </Profile>
  <Profile name="ExploreWithoutMetrics">
    <Type>SIMItfSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <Alternates from="SIMObjSimulationSystem">
      <Alternate order="1">
        <Condition>
          <hasSR role="SIM_RootContext" category="Reference2">
          </hasSR>
        </Condition>
        <LoadPointed role="SIM_RootContext" category="Reference2" to="PLMWspPVS">Explore</LoadPointed>
      </Alternate>
      <Alternate order="2">
        <LoadPointed role="SIM_SimulatedProduct" category="Reference3" to="VPMReference">Explore</LoadPointed>
      </Alternate>
    </Alternates>
  </Profile>
  <Profile name="LoadMetric">
    <Type>PLMPIMMetricReference</Type>
    <Query type="Expand">
      <AddType>PLMPIMMetricReference</AddType>
      <AddType>PLMPIMMetricFromSCAToOccurences</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
    <LoadPointed from="PLMPIMMetricFromSCAToOccurences"                               role="PIM_InterferingOccs"  category="Reference3"></LoadPointed>
    <LoadPointed from="PLMPIMMetricFromSCAToOccurences" to="VPMReference"             role="PIM_SCA"              category="Reference4"></LoadPointed>
  </Profile>
  <Profile name="Explore">
    <Type>PLMPIMMetricReference</Type>
    <Query type="Navigate">
      <AddType>PLMPIMMetricReference</AddType>
      <AddType>PLMPIMMetricFromSCAToOccurences</AddType>
      <AddType>SIMItfContextOfInterference</AddType>
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMItfSimulation</AddType>
      <Path>
        <Step from="PLMPIMMetricReference" to="SIMItfContextOfInterference" role="PIM_Metric" category="Reference4" direct="false"> </Step>
        <Step from="SIMItfContextOfInterference" to="SIMObjSimulationCategoryReference" direct="false"> </Step>
        <Step from="SIMObjSimulationCategoryReference" to="SIMObjSimulationCategoryInstance" direct="true"> </Step>
        <Step from="SIMObjSimulationCategoryInstance" to="SIMItfSimulation" direct="false"> </Step>
      </Path>
      <Path from="PLMPIMMetricReference" to="PLMPIMMetricFromSCAToOccurences"> </Path>
    </Query>
    <Transition from="SIMItfSimulation">ExploreWithoutMetrics</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
</Profiles>
