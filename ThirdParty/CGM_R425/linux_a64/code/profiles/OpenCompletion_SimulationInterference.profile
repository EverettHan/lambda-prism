<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="OpenWithPVS" OldTypingSupport='Y'>
    <Type>SIMItfSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
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
        <LoadPointed role="SIM_RootContext" category="Reference2" to="PLMWspPVS" compactable="false">Authoring</LoadPointed>
      </Alternate>
      <Alternate order="2">
        <LoadPointed role="SIM_SimulatedProduct" category="Reference3" to="VPMReference">Authoring</LoadPointed>
	    <LoadPointed role="SIM_SimulatedProduct" category="Reference3" to="PPRContext">GetFirstPPRLevel</LoadPointed>
      </Alternate>
    </Alternates>
    <LoadPointed from="SIMItfContextOfInterference"                                      role="PIM_RootContextToSCA" category="Reference3"></LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"      to="PLMPIMMetricReference"      role="PIM_Metric"           category="Reference4">LoadMetric</LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"      to="CATMCXMechanicalConnection" role="PIM_Probe"            category="Reference4"></LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"      to="PLMRule"                    role="PIM_Probe"            category="Reference4"></LoadPointed>
  </Profile>
  <Profile name="OpenWithoutModel" OldTypingSupport='Y'>
    <Type>SIMItfSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
      <AddType>SIMItfContextOfInterference</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <LoadPointed from="SIMItfContextOfInterference"                                      role="PIM_RootContextToSCA" category="Reference3"></LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"      to="PLMPIMMetricReference"      role="PIM_Metric"           category="Reference4">LoadMetric</LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"      to="CATMCXMechanicalConnection" role="PIM_Probe"            category="Reference4"></LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"      to="PLMRule"                    role="PIM_Probe"            category="Reference4"></LoadPointed>
  </Profile>
  <Profile name="OpenWithoutContext" OldTypingSupport='Y'>
    <Type>SIMItfSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
      <AddType>SIMItfContextOfInterference</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <LoadPointed from="SIMItfContextOfInterference"      to="PLMPIMMetricReference"      role="PIM_Metric"           category="Reference4">LoadMetricWithoutModel</LoadPointed>
  </Profile>
  <Profile name="OpenWithContext" OldTypingSupport='Y'>
    <Type>SIMItfSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
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
        <LoadPointed role="SIM_RootContext" category="Reference2" to="PLMWspPVS" compactable="false">Authoring</LoadPointed>
      </Alternate>
      <Alternate order="2">
        <LoadPointed role="SIM_SimulatedProduct" category="Reference3" to="VPMReference">Authoring</LoadPointed>
		<LoadPointed role="SIM_SimulatedProduct" category="Reference3" to="PPRContext">GetFirstPPRLevel</LoadPointed>
      </Alternate>
    </Alternates>
    <LoadPointed from="SIMItfContextOfInterference"      to="PLMPIMMetricReference"      role="PIM_Metric"           category="Reference4">LoadMetricWithoutModel</LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"      to="CATMCXMechanicalConnection" role="PIM_Probe"            category="Reference4"></LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"      to="PLMRule"                    role="PIM_Probe"            category="Reference4"></LoadPointed>
  </Profile>
  <Profile name="OpenWithInterferingParts" OldTypingSupport='Y'>
    <Type>SIMItfSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
      <AddType>SIMItfContextOfInterference</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <LoadPointed from="SIMItfContextOfInterference"                                      role="PIM_RootContextToSCA" category="Reference3"></LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"      to="PLMPIMMetricReference"      role="PIM_Metric"           category="Reference4">LoadMetric</LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"      to="CATMCXMechanicalConnection" role="PIM_Probe"            category="Reference4"></LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"      to="PLMRule"                    role="PIM_Probe"            category="Reference4"></LoadPointed>
  </Profile>

  <Profile name="OpenWithoutMetric" OldTypingSupport='Y'>
    <Type>SIMItfSimulation</Type>
    <Query type="Expand">
      <AddType>SIMObjSimulationCategoryReference</AddType>
      <AddType>SIMObjSimulationCategoryInstance</AddType>
      <AddType>SIMObjSimulationSystem</AddType>
      <AddType>SIMObjSimulationRepReference</AddType>
      <AddType>SIMObjSimulationRepInstance</AddType>
      <AddType>ParameterPort</AddType>
    </Query>
    <Alternates from="SIMObjSimulationSystem">
      <Alternate order="1">
        <Condition>
          <hasSR role="SIM_RootContext" category="Reference2">
          </hasSR>
        </Condition>
        <LoadPointed role="SIM_RootContext" category="Reference2" to="PLMWspPVS" compactable="false">Authoring</LoadPointed>
      </Alternate>
      <Alternate order="2">
        <LoadPointed role="SIM_SimulatedProduct" category="Reference3" to="VPMReference">Authoring</LoadPointed>
	    <LoadPointed role="SIM_SimulatedProduct" category="Reference3" to="PPRContext">GetFirstPPRLevel</LoadPointed>
      </Alternate>
    </Alternates>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
  <Profile name="OpenWithoutMetricWithoutContext" OldTypingSupport='Y'>
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
  </Profile>

  <Profile name="LoadMetricWithoutModel" OldTypingSupport='Y'>
    <Type>PLMPIMMetricReference</Type>
    <Query type="Expand">
      <AddType>PLMPIMMetricReference</AddType>
      <AddType>PLMPIMMetricFromSCAToOccurences</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
  </Profile>
  <Profile name="LoadMetric" OldTypingSupport='Y'>
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

  <Profile name="Authoring" OldTypingSupport='Y'>
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
    <Transition from="SIMItfSimulation">OpenWithoutMetric</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
  <Profile name="OpenWithContext" OldTypingSupport='Y'>
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
    <Transition from="SIMItfSimulation">OpenWithoutMetric</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
  <Profile name="OpenWithInterferingParts" OldTypingSupport='Y'>
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
    <Transition from="SIMItfSimulation">OpenWithoutMetricWithoutContext</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <LoadPointed from="SIMItfContextOfInterference"                                     role="PIM_RootContextToSCA" category="Reference3"></LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"     to="PLMRule"                    role="PIM_Probe"            category="Reference4"></LoadPointed>
    <LoadPointed from="SIMItfContextOfInterference"     to="CATMCXMechanicalConnection" role="PIM_Probe"            category="Reference4"></LoadPointed>
    <LoadPointed from="PLMPIMMetricFromSCAToOccurences"                                 role="PIM_InterferingOccs"  category="Reference3"></LoadPointed>
    <LoadPointed from="PLMPIMMetricFromSCAToOccurences" to="VPMReference"               role="PIM_SCA"              category="Reference4"></LoadPointed>
  </Profile>
  <Profile name="OpenWithoutContext" OldTypingSupport='Y'>
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
    <Transition from="SIMItfSimulation">OpenWithoutMetricWithoutContext</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>




</Profiles>
