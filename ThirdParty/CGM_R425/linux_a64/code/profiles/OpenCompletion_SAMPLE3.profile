<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  
 <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>PLMSample3RefA</Type>
    <Type>PLMSample3InstA</Type>
    <Type>PLMSample3RepRefA</Type>
    <Type>PLMSample3RepInstA</Type>
    <Query type="Expand">
      <AddType option="no_type_retriever">PLMSample2BaseReference</AddType> 
      <AddType option="no_type_retriever">PLMSample2BaseInstance</AddType>
      <AddType>PLMSample3RepRefA</AddType> 
      <AddType>PLMSample3RepInstA</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Inherited</Level>
  </Profile>
  <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>PLMSample3RefAppliB</Type>
    <Type>PLMSample3InstB</Type>
    <Type>PLMSample3RepRefAppliB</Type>
    <Type>PLMSample3RepInstAppliB</Type>
    <Query type="Expand">
      <AddType option="no_type_retriever">PLMSample3RefAppliB</AddType> 
      <AddType option="no_type_retriever">PLMSample3InstB</AddType>
      <AddType option="no_type_retriever">PLMSample3RefA</AddType> 
      <AddType option="no_type_retriever">PLMSample3InstA</AddType>
      <AddType >PLMSample3RepRefAppliB</AddType> 
      <AddType >PLMSample3RepInstAppliB</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Inherited</Level>
  </Profile>
</Profiles>


