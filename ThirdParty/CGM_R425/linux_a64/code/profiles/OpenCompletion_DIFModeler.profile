<Profiles  xmlns="http://tempuri.org/XMLSchema.xsd">
  <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>DIFLayout</Type>
    <Type>DIFSheet</Type>
    <Type>DIFView</Type>
    <Type>DIFSymbolRefStream</Type>
    <Type>DIFShapeRep</Type>
    <Type>DIFViewStream</Type>
    <Type>DIFBackgroundViewRep</Type>
    <Query type="Expand">
      <AddType>DIFLayout</AddType>
      <AddType>DIFSheetInstance</AddType>
      <AddType>DIFSheet</AddType>
      <AddType>DIFAbstractViewInstance</AddType>
      <AddType>DIFAbstractView</AddType>
      <AddType>DIFViewStreamInstance</AddType>
      <AddType>DIFViewInstance</AddType>
      <AddType>DIFView</AddType>
	  <AddType type="DIFViewStream">
        <PointedRetriever option="layouts" role="DIFStandardProvider" category="Reference4"></PointedRetriever>
      </AddType>
      <AddType>DIFBackgroundViewRepInstance</AddType>
	  <AddType type="DIFBackgroundViewRep">
        <PointedRetriever option="layouts" role="DIFStandardProvider" category="Reference4"></PointedRetriever>
      </AddType>
	  <AddType type="DIFSymbolRefStream">
        <PointedRetriever option="layouts" role="DIFStandardProvider" category="Reference4"></PointedRetriever>
      </AddType>
	  <AddType type="DIFShapeRep">
        <PointedRetriever option="layouts" role="DIFStandardProvider" category="Reference4"></PointedRetriever>
      </AddType>
      <AddType>DIFStandardRepInstance</AddType>
      <AddType>DIFStandardRep</AddType>
	  <AddType>DIFIsAPresentationOf</AddType>
	  <AddType>RFLPLMImplementConnection</AddType>
	  <AddType>VPMCfgEffectivity</AddType>
	  <AddType>VPMCfgContext</AddType>
	  <AddType>VPMCfgInstanceConfiguration</AddType>
  	  <AddType>SequenceDiagramInstance</AddType>
  	  <AddType>SequenceDiagram</AddType>
	  <AddType>UseCaseDiagramInstance</AddType>
	  <AddType>UseCaseDiagram</AddType>
	  <AddType>StateMachineDiagramInstance</AddType>
	  <AddType>StateMachineDiagram</AddType>
	  <AddType>ContextDiagramInstance</AddType>
	  <AddType>ContextDiagram</AddType>
	  <AddType>AllocationDiagramInstance</AddType>
	  <AddType>AllocationDiagram</AddType>
	  <AddType>ActivityDiagramInstance</AddType>
	  <AddType>ActivityDiagram</AddType>
      <AddType>DIFSupplementalGeometry</AddType>
      <AddType>DIFSupplementalGeometryInstance</AddType>
      <AddType>DIF3DShapeInstance</AddType>
      <AddType>DIF3DShape</AddType>
      <AddType>DIFAttachedPresentation</AddType>
    </Query>
    <LoadPointed from="DIFAttachedPresentation" option="layouts" role="DIFAttachedPresentation" category="Reference">Authoring</LoadPointed>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
    <Profile name="Authoring" OldTypingSupport='Y'>
    <Type>DIFAnnotationSet</Type>
    <Query type="Expand">
      <AddType>DIFAnnotationSet</AddType>
      <AddType>DIFLayout</AddType>
      <AddType>DIFSheetInstance</AddType>
      <AddType>DIFSheet</AddType>
      <AddType>DIFAbstractViewInstance</AddType>
      <AddType>DIFAbstractView</AddType>
      <AddType>DIFAnnotatedProduct</AddType>
      <AddType option="all_reps">DIFViewStreamInstance</AddType>
	  <AddType type="DIFViewStream" option="all_reps">
        <PointedRetriever option="layouts" role="DIFStandardProvider" category="Reference4"></PointedRetriever>
      </AddType>
      <AddType option="all_reps">DIFBackgroundViewRepInstance</AddType>
	  <AddType type="DIFBackgroundViewRep" option="all_reps">
        <PointedRetriever option="layouts" role="DIFStandardProvider" category="Reference4"></PointedRetriever>
      </AddType>
	  <AddType type="DIFSymbolRefStream" option="all_reps">
        <PointedRetriever option="layouts" role="DIFStandardProvider" category="Reference4"></PointedRetriever>
      </AddType>
	  <AddType type="DIFShapeRep" option="all_reps">
        <PointedRetriever option="layouts" role="DIFStandardProvider" category="Reference4"></PointedRetriever>
      </AddType>
      <AddType option="all_reps">DIFStandardRepInstance</AddType>
      <AddType option="all_reps">DIFStandardRep</AddType>
	  <AddType>DIFIsAPresentationOf</AddType>
	  <AddType>RFLPLMImplementConnection</AddType>
	  <AddType>VPMCfgEffectivity</AddType>
	  <AddType>VPMCfgContext</AddType>
	  <AddType>VPMCfgInstanceConfiguration</AddType>
  	  <AddType>SequenceDiagramInstance</AddType>
  	  <AddType>SequenceDiagram</AddType>
	  <AddType>UseCaseDiagramInstance</AddType>
	  <AddType>UseCaseDiagram</AddType>
	  <AddType>StateMachineDiagramInstance</AddType>
	  <AddType>StateMachineDiagram</AddType>
	  <AddType>ContextDiagramInstance</AddType>
	  <AddType>ContextDiagram</AddType>
	  <AddType>AllocationDiagramInstance</AddType>
	  <AddType>AllocationDiagram</AddType>
	  <AddType>ActivityDiagramInstance</AddType>
	  <AddType>ActivityDiagram</AddType>
      <AddType>DIFSupplementalGeometry</AddType>
      <AddType>DIFSupplementalGeometryInstance</AddType>
      <AddType>DIF3DShapeInstance</AddType>
      <AddType>DIF3DShape</AddType>
    </Query>
    <Level state="Light">None</Level>
    <Level state="Navigation">None</Level>
    <Level state="Full">All</Level>
  </Profile>
</Profiles>
