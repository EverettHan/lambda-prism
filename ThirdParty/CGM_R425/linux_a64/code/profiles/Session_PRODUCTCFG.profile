<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Explore">
    <Type>VPMReference</Type>
    <Query type="Expand">
      <AddType>VPMReference</AddType>
      <AddType>VPMInstance</AddType>
      <AddType option="reps">VPMRepInstance</AddType>
      <AddType option="reps">VPMRepReference</AddType>
      <AddType level="Full" option="materials">CATMatConnection</AddType>
      <RemoveType option="fasteners">FastenerInstance</RemoveType>
      <AddType level="Full" option="layouts">DIFAttachedPresentation</AddType>
      <AddType level="Full" option="documents">PLMDocConnection</AddType>
    </Query>
    <Level state="Light">Inherited</Level>
    <Level state="Navigation">Inherited</Level>
    <Level state="Full">None</Level>
    <Transition from="ErgoHuman">Explore</Transition>
    <Transition from="Review" result="false" option="reviews">Authoring</Transition>
    <LoadPointed from="CATMatConnection" to="CATMatReference" option="materials">Explore</LoadPointed>
    <LoadPointed from="DIFAttachedPresentation" to="DIFSheet" option="layouts">Explore</LoadPointed>
    <LoadPointed from="DIFAttachedPresentation" to="DIFLayout" option="layouts">Explore</LoadPointed>
    <LoadPointed from="PLMDocConnection" to="PLMDMTDocument" option="documents">Authoring</LoadPointed>
    <LoadPointed from="PLMDocConnection" to="Document" option="documents">Authoring</LoadPointed>
  </Profile>
  <Profile name="Explore">
    <Type>Review</Type>
    <Query type="Expand">
      <AddType>VPMReference</AddType>
      <AddType>VPMInstance</AddType>
      <AddType>VPMRepInstance</AddType>
      <AddType>Review</AddType>
    </Query>
    <Transition from="Review" result="false">Authoring</Transition>
    <Level state="Light">Inherited</Level>
    <Level state="Navigation">Inherited</Level>
    <Level state="Full">None</Level>
  </Profile>
  <Profile name="Authoring">
    <Type>Review</Type>
    <Query type="Expand">
      <AddType>Review</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
  </Profile>
  <Profile name="Upgrade">
    <Type>VPMReference</Type>
    <Query type="Expand">
      <AddType type='VPMReference' level='Full'></AddType>
      <AddType type='VPMInstance'></AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
    <Alternates from='VPMReference'>
      <Alternate order='1'>
        <Condition>
          <hasAttr name='V_hasConfigContext' value='true' type='boolean'></hasAttr>
        </Condition>
        <Transition>GetConfigCnxs</Transition>
      </Alternate>
    </Alternates>
  </Profile>
  <Profile name="GetConfigCnxs">
    <Type>VPMReference</Type>
    <Query type="Expand">
      <AddType>VPMCfgConfiguration</AddType>
      <AddType>VPMCfgContext</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
  </Profile>
</Profiles>
