<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>CATMatReference</Type>
    <Query type="Expand">
      <AddType>CATMatReference</AddType>
      <AddType>CATMatRefInstance</AddType>
      <AddType>MaterialDomainInstance</AddType>
      <AddType type="MaterialDomain">
        <PointedRetriever role="CATMaterialReferenceToTextureLink" category="Reference"></PointedRetriever>
        <PointedRetriever role="CATMaterialReferenceToReflectionLink" category="Reference"></PointedRetriever>
        <PointedRetriever role="CATMaterialReferenceToShaderLink" category="Reference"></PointedRetriever>
        <PointedRetriever role="CATMaterialReferenceToAssetLink" category="Reference"></PointedRetriever>
      </AddType>
      <AddType>CATMatRefConnection</AddType>
      <AddType>CATMatRefElemConnection</AddType>
	  <AddType>CATMatPort</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">2</Level>
  </Profile>
    <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>CATMatPort</Type>
    <Query type="ReverseExpand">
      <AddType>CATMatReference</AddType>
      <AddType>CATMatPort</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
	<Transition from="CATMatReference">Authoring</Transition>
  </Profile>
  <Profile name="Authoring">
    <Type>dsc_matref_rep_Rendering</Type>
    <Type>dsc_matrefelem_cnx_SmaBehavior</Type>
    <Query type="Expand">
      <AddType>dsc_matref_rep_Rendering</AddType>
      <AddType>dsc_matrefelem_cnx_SmaBehavior</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
  </Profile>
  <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>Internal Material</Type>
    <Query type="Expand">
      <AddType>Internal Material</AddType>
      <AddType>ComposedOfDomains</AddType>
      <AddType>UsingDomains</AddType>
      <AddType>MaterialDomain</AddType>
      <Path from="Internal Material" through="ComposedOfDomains"   to="MaterialDomain"/>
      <Path from="Internal Material" through="UsingDomains"   to="MaterialDomain"/>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">2</Level>
    <LoadPointed prereq="true" from="MaterialDomain" to="PLMDMTDocument">Authoring</LoadPointed>
    <LoadPointed prereq="true" from="MaterialDomain" to="dsc_matref_rep_Rendering">Authoring</LoadPointed>
  </Profile>
</Profiles>
