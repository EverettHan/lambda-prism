<?xml version="1.0" encoding="utf-8"?>
<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Explore">
    <Type>VPMCfgConfiguration</Type>
    <Query type="Navigate">
      <AddType>VPMCfgConfiguration</AddType>
      <AddType>VPMReference</AddType>
      <Path from="VPMCfgConfiguration" to="VPMReference" direct="false"/>
    </Query>
    <Transition from="VPMReference">Explore</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
</Profiles>


