<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Authoring" OldTypingSupport='Y' PathSupport='Y' ReversePath='N'>
    <Type>Requirement Specification</Type>
    <Type>Chapter</Type>
    <Type>Comment</Type>
    <Type>Requirement</Type>
    <Type>Requirement Group</Type>
    <Type>Use Case</Type>
    <Query type="Navigate">
      <AddType>Requirement Specification</AddType>
      <AddType>Chapter</AddType>
      <AddType>Comment</AddType>
      <AddType>Requirement</AddType>
      <AddType>Requirement Group</AddType>
      <AddType>Specification Structure</AddType>
      <AddType>Sub Requirement</AddType>
      <AddType>Derived Requirement</AddType>
      <AddType>Requirement Group Content</AddType>
      <AddType>Sub Requirement Group</AddType>
      <AddType>Use Case</AddType>
      <AddType>Sub Use Case</AddType>
      <AddType>PlmParameter</AddType>
      <AddType>ParameterUsage</AddType>
      <AddType>ParameterAggregation</AddType>
	  <AddType>ParameterComposition</AddType>
      <AddType>ComposedParameter</AddType>
      <AddType>RFLPLMImplementConnection</AddType>
      <AddType option="test_case">Test Case</AddType>
      <AddType option="test_case">Requirement Validation</AddType>
      <AddType option="test_case">Sub Test Case</AddType>
      <!--Direct expand xMQL: on ne spécifie que le premier path qui nous sert à déterminer si on fait de l'expand inverse ou direct.
      Les autres ne servent à rien.-->
      <Path from="Requirement Specification" through="Specification Structure"   to="Chapter"/>
      <Path from="Chapter"                   through="Specification Structure"   to="Comment"/>
      <Path from="Chapter"                   through="Specification Structure"   to="Requirement"/>
      <Path from="Chapter"                   through="Specification Structure"   to="Chapter"/>
      <Path from="Requirement Specification" through="Specification Structure"   to="Comment"/>
      <Path from="Requirement Specification" through="Specification Structure"   to="Requirement"/>
      <Path from="Requirement"               through="Sub Requirement"           to="Requirement"/>
      <Path from="Requirement"               through="Derived Requirement"       to="Requirement"/>
      <Path from="Requirement Group"         through="Sub Requirement Group"     to="Requirement Group"/>
      <Path from="Requirement Group"         through="Requirement Group Content" to="Requirement Specification"/>
      <Path from="Requirement"               through="ParameterUsage"            to="PlmParameter"/>
      <Path from="Requirement"               through="ParameterAggregation"      to="PlmParameter"/>
	  <Path from="Requirement"               through="ParameterComposition"      to="ComposedParameter"/>
      <Path from="Use Case"                  through="Sub Use Case"              to="Use Case"/>
      <Path from="Requirement Specification"                                     to="RFLPLMImplementConnection"/>
      <Path from="Requirement"                                                   to="RFLPLMImplementConnection"/>
      <Path from="Requirement Group"                                             to="RFLPLMImplementConnection"/>
      <Path option="test_case" from="Requirement"               through="Requirement Validation"    to="Test Case"/>
      <Path option="test_case" from="Test Case"                 through="Sub Test Case"             to="Test Case"/>
    </Query>
    <LoadPointed from="RFLPLMImplementConnection" role="PLM_ImplementLink_Target" category="Reference3">Authoring</LoadPointed>
    <Transition option="test_case" from="Test Case">Authoring</Transition>
    <Transition option="test_exec" from="Test Execution">Authoring</Transition>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Inherited</Level>
  </Profile>
  <Profile name="Authoring" OldTypingSupport='Y' PathSupport='Y' ReversePath='N'>
    <Type>Test Case</Type>
    <Query type="Navigate">
      <AddType>Test Case</AddType>
      <AddType option="test_case">Sub Test Case</AddType>
      <AddType option="test_case">PlmParameter</AddType>
      <AddType option="test_case">ParameterUsage</AddType>
      <AddType option="test_case">ParameterAggregation</AddType>
	  <AddType option="test_case">ParameterComposition</AddType>
      <AddType option="test_case">ComposedParameter</AddType>
      <AddType option="test_exec">Test Execution</AddType>
      <AddType option="test_exec">Test Execution Test Case</AddType>
      <!--Direct expand xMQL: on ne spécifie que le premier path qui nous sert à déterminer si on fait de l'expand inverse ou direct.
      Les autres ne servent à rien.-->
      <Path option="test_case" from="Test Case" through="Sub Test Case" to="Test Case"/>
      <Path option="test_case" from="Test Case" through="ParameterUsage" to="PlmParameter"/>
      <Path option="test_case" from="Test Case" through="ParameterAggregation" to="PlmParameter"/>
	  <Path option="test_case" from="Test Case" through="ParameterComposition" to="ComposedParameter"/>
      <Path option="test_exec">
        <Step from="Test Case" to="Test Execution Test Case" direct="true"> </Step>
        <Step from="Test Execution Test Case" to="Test Execution" direct="false"> </Step>
      </Path>
      <Path option="test_case" from="Test Execution" through="ParameterUsage" to="PlmParameter"/>
      <Path option="test_case" from="Test Execution" through="ParameterAggregation" to="PlmParameter"/>
	  <Path option="test_case" from="Test Execution" through="ParameterComposition" to="ComposedParameter"/>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Inherited</Level>
  </Profile>
  <Profile name="Authoring" OldTypingSupport='Y' PathSupport='Y' ReversePath='N'>
    <Type>Test Execution</Type>
    <Query type="Navigate">
      <AddType>Test Execution</AddType>
      <AddType option="test_exec">Sub Test Execution</AddType>
      <AddType option="test_exec">PlmParameter</AddType>
      <AddType option="test_exec">ParameterUsage</AddType>
      <AddType option="test_exec">ParameterAggregation</AddType>
	  <AddType option="test_exec">ParameterComposition</AddType>
      <AddType option="test_exec">ComposedParameter</AddType>
      <AddType option="test_case">Test Execution Test Case</AddType>
      <AddType option="test_case">Test Case</AddType>
      <Path option="test_exec" from="Test Execution" through="ParameterUsage" to="PlmParameter"/>
      <Path option="test_exec" from="Test Execution" through="ParameterAggregation" to="PlmParameter"/>
	  <Path option="test_exec" from="Test Execution" through="ParameterComposition" to="ComposedParameter"/>
      <Path option="test_case" from="Test Execution" through="Test Execution Test Case" to="Test Case"/>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Inherited</Level>
  </Profile>
</Profiles>
