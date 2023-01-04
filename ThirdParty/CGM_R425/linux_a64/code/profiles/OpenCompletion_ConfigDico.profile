<Profiles xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>Model</Type>
    <Type>Product Configuration</Type>
    <Type>Model</Type>
    <Type>Builds</Type>
    <Type>Manufacturing Plan Master</Type>
    <Type>Manufacturing Plan</Type>
    <Type>Products</Type>
    <Type>CONFIGURATION FEATURES</Type>
    <Type>Series Master</Type>
    <Type>Relation.Products</Type>
    <Type>Relation.Product Configuration</Type>
    <Type>CONFIGURATION STRUCTURES</Type>
    <Type>Managed Series</Type>
    <Type>Model Build</Type>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">Self</Level>
  </Profile>
   <Profile name="CompleteProductConfiguration" OldTypingSupport='Y'>
    <Type>Product Configuration</Type>
    <Query type="ReverseExpand">
      <AddType>Product Configuration</AddType>
      <AddType>Relation.Product Configuration</AddType>
      <AddType>Products</AddType>
      <AddType>Relation.Products</AddType>
      <AddType>Model</AddType>
	  <AddType>Child Composition Binary</AddType>
    </Query>
    <Transition from="Model">GetAggregatedModels</Transition>
	<Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">2</Level>
  </Profile>
  <Profile name="GetAggregatedModels" OldTypingSupport='Y'>
    <Type>Model</Type>
    <Query type="Expand">
	  <AddType>Model</AddType>
      <AddType>Model Template</AddType>
	</Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">1</Level>
  </Profile>
</Profiles>


