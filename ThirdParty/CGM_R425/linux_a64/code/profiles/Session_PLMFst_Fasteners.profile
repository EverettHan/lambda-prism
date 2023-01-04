<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="PLMFst_Fasteners:LoadFastener">
    <Type>VPMReference</Type>
    <Query type="Expand">
      <AddType>VPMReference</AddType>
      <AddType>FastenerInstance</AddType>
      <AddType>Fastener</AddType>
      <AddType>SpotFastener_Representation</AddType>
      <AddType>BeadFastener_Representation</AddType>
      <AddType>LocFastener_Representation</AddType>
      <AddType>VPMRepInstance</AddType>
      <AddType>VPMRepReference</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">All</Level>
    <Level state="Full">None</Level>
  </Profile>
  <Profile name="PLMFst_Fasteners:LoadFastenerAndFastened">
    <Type>VPMInstance</Type>
    <Query type="ML" file="debug_FastenersAnalysis_PartToFastener_NT"/>
    <Level state="Light">None</Level>
    <Level state="Navigation">All</Level>
    <Level state="Full">None</Level>
    <LoadPointed from="PLMFst_MCX" role="Fst_Realization" category="Reference">OCCORE:Expand</LoadPointed>
    <LoadPointed from="PLMFst_MCX" role="Asd_LinkedZone" category="Reference3">OCCORE:Expand</LoadPointed>
  </Profile>
  <Profile name="PLMFst_Fasteners:LoadFastenerMCXs">
    <Type>VPMInstance</Type>
    <Query type="Navigate">
      <AddType level="Navigation">VPMInstance</AddType>
      <AddType level="Full">PLMFst_MCX</AddType>
      <Path>
        <Step from="VPMInstance" to="PLMFst_MCX" role="Asd_LinkedZone" category="Reference3" direct="false"> </Step>
      </Path>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">All</Level>
    <Level state="Full">None</Level>
  </Profile>
  <Profile name="PLMFst_Fasteners:LoadFasteners">
    <Type>PLMFst_MCX</Type>
    <Query type="Expand">
      <AddType level="Full">PLMFst_MCX</AddType>
    </Query>
    <LoadPointed from="PLMFst_MCX" role="Fst_Realization" category="Reference">OCCORE:Expand</LoadPointed>
    <Level state="Light">None</Level>
    <Level state="Navigation">Self</Level>
    <Level state="Full">None</Level>
  </Profile>
  <Profile name="PLMFst_Fasteners:LoadFastenedParts">
    <Type>PLMFst_MCX</Type>
    <Query type="Expand">
      <AddType level="Full">PLMFst_MCX</AddType>
    </Query>
    <LoadPointed from="PLMFst_MCX" role="Asd_LinkedZone" category="Reference3">OCCORE:Expand</LoadPointed>
    <Level state="Light">None</Level>
    <Level state="Navigation">Self</Level>
    <Level state="Full">None</Level>
  </Profile>
  <Profile name="PLMFst_Fasteners:LoadFastened">
    <Type>VPMInstance</Type>
    <Query type="ML" file="LNU_FastenersAnalysis_FastenerToPart_NT"/>
    <Level state="Light">None</Level>
    <Level state="Navigation">All</Level>
    <Level state="Full">None</Level>
    <LoadPointed from="PLMFst_MCX" role="Asd_LinkedZone" category="Reference3">OCCORE:Expand</LoadPointed>
  </Profile>
  <Profile name="PLMFst_Fasteners:SearchUnder">
    <Type>VPMReference</Type>
    <Query type="Expand">
      <AddType>FastenerInstance</AddType>
      <AddType>Fastener</AddType>
      <AddType>SpotFastener_Representation</AddType>
      <AddType>BeadFastener_Representation</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">1</Level>
    <Level state="Full">None</Level>
  </Profile>
  <Profile name="PLMFst_Fasteners:LoadMCXsFromRealizationLink">
    <Type>VPMInstance</Type>
    <Query type="Navigate">
      <AddType level="Navigation">VPMInstance</AddType>
      <AddType level="Full">PLMFst_MCX</AddType>
	  <AddType level="Full">PLMFst_MCX_X</AddType>
      <Path>
        <Step from="VPMInstance" to="PLMFst_MCX" role="Fst_Realization" category="Reference" direct="false"> </Step>
		<Step from="PLMFst_MCX" to="PLMFst_MCX_X" role="REL_IMPACTSON" category="Reference5" direct="false"> </Step>
      </Path>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">All</Level>
    <Level state="Full">None</Level>
  </Profile>
</Profiles>
