<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="AuthoringDecoration" OldTypingSupport='Y' PathSupport='Y' ReversePath='N'>
    <Type>DELLmiProductionPlanReference</Type>
    <Type>DELLmiWorkOrderReference</Type>
    <Type>DELLmiOperationUPRReference</Type>
    <Query type="Navigate">
      <AddType>DELLmiProductionPlanReference</AddType>
      <AddType>DELLmiWorkOrderReference</AddType>
      <AddType>DELLmiOperationUPRReference</AddType>
      <AddType>UPR_LinkToWhereResource</AddType>
      <AddType>UPR_LinkToWhoResource</AddType>
      <AddType type="DELLmiExecTimeConstraintRelation">
        <FilterOnDependencies>true</FilterOnDependencies>
      </AddType>
      <AddType>VPMReference</AddType>
      <!--Direct expand xMQL: on ne spécifie que le premier path qui nous sert à déterminer si on fait de l'expand inverse ou direct.
      Les autres ne servent à rien.-->
      <Path from="DELLmiProductionPlanReference" through="UPR_LinkToWhereResource"   to="VPMReference"/>
      <Path from="DELLmiWorkOrderReference" through="UPR_LinkToWhereResource"   to="VPMReference"/>
      <Path from="DELLmiOperationUPRReference" through="UPR_LinkToWhereResource"   to="VPMReference"/>
      <Path from="DELLmiOperationUPRReference" through="UPR_LinkToWhoResource"   to="VPMReference"/>
      <Path from="DELLmiOperationUPRReference" through="DELLmiExecTimeConstraintRelation"   to="DELLmiOperationUPRReference"/>
    </Query>
    <Transition from="VPMReference">AuthoringDecoration</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Inherited</Level>
  </Profile>
  <Profile name="AuthoringDecorationNoRep" OldTypingSupport='Y' PathSupport='Y' ReversePath='N'>
    <Type>DELLmiProductionPlanReference</Type>
    <Type>DELLmiWorkOrderReference</Type>
    <Type>DELLmiOperationUPRReference</Type>
    <Query type="Navigate">
      <AddType>DELLmiProductionPlanReference</AddType>
      <AddType>DELLmiWorkOrderReference</AddType>
      <AddType>DELLmiOperationUPRReference</AddType>
      <AddType>UPR_LinkToWhereResource</AddType>
      <AddType>UPR_LinkToWhoResource</AddType>
      <AddType type="DELLmiExecTimeConstraintRelation">
        <FilterOnDependencies>true</FilterOnDependencies>
      </AddType>
      <AddType>VPMReference</AddType>
      <!--Direct expand xMQL: on ne spécifie que le premier path qui nous sert à déterminer si on fait de l'expand inverse ou direct.
      Les autres ne servent à rien.-->
      <Path from="DELLmiProductionPlanReference" through="UPR_LinkToWhereResource"   to="VPMReference"/>
      <Path from="DELLmiWorkOrderReference" through="UPR_LinkToWhereResource"   to="VPMReference"/>
      <Path from="DELLmiOperationUPRReference" through="UPR_LinkToWhereResource"   to="VPMReference"/>
      <Path from="DELLmiOperationUPRReference" through="UPR_LinkToWhoResource"   to="VPMReference"/>
      <Path from="DELLmiOperationUPRReference" through="DELLmiExecTimeConstraintRelation"   to="DELLmiOperationUPRReference"/>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Inherited</Level>
  </Profile>
  <Profile name="GetFirstPPRLevel" OldTypingSupport='Y'>
    <Type>PPRContext</Type>
    <Type>VPMReference</Type> <!-- uniquement pour support old typing .. à supprimer très vite !! -->
    <Query type="Expand">
      <AddType>PPRContext</AddType>
      <AddType>VPMReference</AddType> <!-- uniquement pour support old typing .. à supprimer très vite !! -->
      <AddType type="PLMDELPPRProcessCnx">
        <PointedRetriever role="PLM_PPRContextLink_Process"></PointedRetriever>
      </AddType>
      <AddType type="PLMDELPPRSystemCnx">
        <PointedRetriever role="PLM_PPRContextLink_System"></PointedRetriever>
      </AddType>
    </Query>
    <Transition from="PLMCoreReference">Authoring</Transition>
	<Transition from="Part">Authoring</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
  </Profile>

  <Profile name="AuthoringCloudview" OldTypingSupport='Y'>
    <Type>PPRContext</Type>
    <Query type="xMQLProcedure" name="PPRExpandIndexProcedure" version="latest">
    </Query>
    <Transition from="PLMCoreReference" optimizable="false">AuthoringDecoration</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
  </Profile>
    <Profile name="AuthoringCloudviewNoRep" OldTypingSupport='Y'>
    <Type>PPRContext</Type>
    <Query type="xMQLProcedure" name="PPRExpandIndexProcedure" version="latest">
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
  </Profile>

  <!-- Completion specifique pour 3DExperience pointant un asset PPR (chargement depuis CV) -->
  <Profile name="LightAsset" OldTypingSupport='Y'>
    <Type>PPRContext</Type>
    <Query type="Expand">
      <AddType>PPRContext</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
  </Profile>
</Profiles>
