<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Explore">
    <Type>PLMWspReference</Type>
    <Query type="Expand">
      <AddType>PLMWspSpecPVS</AddType>
      <AddType>PLMWspSpecUnderWspRef</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
    <!-- le lien est minor sensitive donc on devrait toujours chargé la spec de build afin qu'il soit toujours résolu en session -->
    <!-- l'attribut minorSensitive='false' est là pour surcharger cette propriété spécifique au PVS                              -->
    <LoadPointed from="PLMWspSpecPVS" to="VPMReference" role="WSPPvsRoot" category="Reference" minorSensitivity="false">Explore</LoadPointed> 
    <LoadPointed from="PLMWspSpecUnderWspRef" to="VPMReference" role="WSPPvsRoot" category="Reference" minorSensitivity="false">Explore</LoadPointed> 
  </Profile>
</Profiles>
