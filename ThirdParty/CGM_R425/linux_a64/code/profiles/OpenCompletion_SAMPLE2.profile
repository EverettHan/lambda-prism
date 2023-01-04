<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  
 <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>PLMSample2BaseReference</Type>
    <Type>PLMSample2BaseInstance</Type>
    <Type>PLMSample2RepReference</Type>
    <Type>PLMSample2RepInstance</Type>
    <Query type="Expand">
      <AddType option="no_type_retriever">PLMSample2BaseReference</AddType> 
      <AddType option="no_type_retriever">PLMSample2BaseInstance</AddType>
      <AddType option="integrity_reps">PLMSample2RepReference</AddType> 
      <AddType option="integrity_reps">PLMSample2RepInstance</AddType>
      <AddType option="integrity_reps">PLMSAMPLERepComposed</AddType> 
      <!--<AddType option="integrity_reps">PLMSAMPLERepCompositional</AddType>-->
      <AddType option="integrity_reps">PLMSample3RepRefAppliB</AddType>
      <AddType option="integrity_reps">PLMSample3RepInstAppliB</AddType>
      <!--<AddType option="all_reps">PLMSAMPLERepCompositional</AddType>-->
      <AddType option="all_reps">PLMCoreRepInstance</AddType>
      <AddType option="all_reps">PLMCoreRepReference</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Inherited</Level>
  </Profile>
    <Profile name="AuthoringDecoration" OldTypingSupport='Y'>
    <Type>PLMSample2BaseReference</Type>
    <Type>PLMSample2BaseInstance</Type>
    <Type>PLMSample2RepReference</Type>
    <Type>PLMSample2RepInstance</Type>
    <Query type="Expand">
      <AddType>PLMSample2BaseReference</AddType>
      <AddType option="integrity_reps">PLMSample2RepReference</AddType> 
      <AddType option="integrity_reps">PLMSample2RepInstance</AddType>
      <AddType option="integrity_reps">PLMSAMPLERepComposed</AddType> 
      <!--<AddType option="integrity_reps">PLMSAMPLERepCompositional</AddType>-->
      <AddType option="integrity_reps">PLMSample3RepRefAppliB</AddType>
      <AddType option="integrity_reps">PLMSample3RepInstAppliB</AddType>
      <!--<AddType option="all_reps">PLMSAMPLERepCompositional</AddType>-->
      <AddType option="all_reps">PLMCoreRepInstance</AddType>
      <AddType option="all_reps">PLMCoreRepReference</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
  </Profile>
    <Profile name="QueryMissingIntegrityReps" OldTypingSupport='Y'>
    <Type>PLMSample2BaseReference</Type>
    <Type>PLMSample2BaseInstance</Type>
    <Type>PLMSample2RepReference</Type>
    <Type>PLMSample2RepInstance</Type>
    <Query type="Expand">
      <AddType>PLMSample2BaseReference</AddType>
      <AddType option="integrity_reps">PLMSample2RepReference</AddType> 
      <AddType option="integrity_reps">PLMSample2RepInstance</AddType>
      <AddType option="integrity_reps">PLMSAMPLERepComposed</AddType> 
      <!--<AddType option="integrity_reps">PLMSAMPLERepCompositional</AddType>-->
      <AddType option="integrity_reps">PLMSample3RepRefAppliB</AddType>
      <AddType option="integrity_reps">PLMSample3RepInstAppliB</AddType>
      <!--<AddType option="all_reps">PLMSAMPLERepCompositional</AddType>-->
      <AddType option="all_reps">PLMCoreRepInstance</AddType>
      <AddType option="all_reps">PLMCoreRepReference</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
  </Profile>
</Profiles>


