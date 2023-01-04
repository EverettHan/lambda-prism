<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>DesignSight</Type>
    <Query type="Expand">
      <AddType level="Full">dsc_Model_Category_Ref</AddType>
      <AddType level="Full">dsc_Scenario_Category_Ref</AddType>
      <AddType level="Full">dsc_Result_Category_Ref</AddType>
      <AddType level="Full">SIMObjSimulationCategoryInstance</AddType>
      <AddType level="Full">SIMObjSimulationCategoryReference</AddType>
      <AddType level="Full">SIMObjSimulationSystem</AddType>
      <AddType level="Full">SIMObjSimulationRepReference</AddType>
      <AddType level="Full">SIMObjSimulationRepInstance</AddType>
      <AddType level="Full">ParameterPort</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <LoadPointed from="SIMObjSimulationSystem" to="VPMReference" role="SIM_SimulatedProduct" category="Reference3">DecoratePortsAndCnxs</LoadPointed>
    <LoadPointed from="SIMObjSimulationRepReference" to="FEM" role="SIM_StateVariable" category="Reference3">AuthoringFEM</LoadPointed>
  </Profile>
  <Profile name="AuthoringFEM" OldTypingSupport='Y'>
    <Type>FEM</Type>
    <Query type="Navigate">
      <AddType level="Full">VPMReference</AddType>
      <AddType level="Full">VPMInstance</AddType>
      <AddType level="Full">FEM</AddType>
      <AddType level="Full">SIMShape</AddType>
      <AddType level="Full">3DShape</AddType>
      <AddType level="Full">VPMRepInstance</AddType>
      <Path>
        <Step from="FEM" to="FEM" role="SIM_FmtAssembledFEMRep" category="Reference3" direct="true"> </Step>
      </Path>
      <Path>
        <Step from="FEM" to="3DShape" role="SIM_FmtLinked3DShape" category="Reference2" direct="true"> </Step>
      </Path>
      <Path>
        <Step from="FEM" to="SIMShape" role="SIM_FmtLinked3DShape" category="Reference2" direct="true"> </Step>
      </Path>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <Transition from="PLMCoreRepReference">GetRepInstance</Transition>
    <LoadPointed from="FEM" role="SIM_FmtLinked3DShape">SmartOpen</LoadPointed>
    <LoadPointed from="FEM" role="SIM_FmtAssembledFEMRep" category="Reference3">SmartOpen</LoadPointed>
  </Profile>
  <Profile name="GetRepInstance" OldTypingSupport='Y'>
    <Type>PLMCoreRepReference</Type>
    <Query type="ReverseExpand">
      <AddType>PLMCoreRepReference</AddType>
      <AddType>PLMCoreRepInstance</AddType>
      <AddType>PLMCoreReference</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
  <!-- OpenWithPVS de GHA -->
  <Profile name="OpenWithPVS" OldTypingSupport='Y'>
    <Type>DesignSight</Type>
    <Query type="Expand">
      <AddType level="Full">dsc_Model_Category_Ref</AddType>
      <AddType level="Full">dsc_Scenario_Category_Ref</AddType>
      <AddType level="Full">dsc_Result_Category_Ref</AddType>
      <AddType level="Full">SIMObjSimulationCategoryInstance</AddType>
      <AddType level="Full">SIMObjSimulationSystem</AddType>
      <AddType level="Full">SIMObjSimulationRepReference</AddType>
      <AddType level="Full">SIMObjSimulationRepInstance</AddType>
      <AddType level="Full">ParameterPort</AddType>
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
      </Alternate>
    </Alternates>
  </Profile>
    <Profile name="OpenWithPVS" OldTypingSupport='Y'>
    <Type>FEM</Type>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
    <LoadPointed from="FEM" to="PLMWspPVS" role="SIM_FmtUsedFilter" compactable="false">Authoring</LoadPointed>
  </Profile>

</Profiles>
