#ifndef CATlsoEdgeEqClassGraph_H
#define CATlsoEdgeEqClassGraph_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "CATlsoEqClassGraph.h"
#include "ListPOfCATlsoEdgeEqClassGraph.h"
#include "CATlsoGraphFactory.h"
#include "CATGMLiveShapeMathUtilities.h"
    
class ExportedByPersistentCell CATlsoEdgeEqClassGraph : public CATlsoEqClassGraph
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  static int CheckConnexComponents( CATLISTP(CATlsoEdgeEqClassGraph) & iConnexComponents );

  HRESULT PartialSplit( CATLISTP(CATlsoEdgeEqClassGraph)  & oSplitClassess );

  HRESULT InsertIfEquivalentToClass( CATlsoGraphEdge * iEdge );

  CATBoolean IsEquivalentToClass( CATlsoGraphEdge * iEdge, CATBoolean iStrictEquivalence = FALSE );

  HRESULT ComputeConnexComponents( CATLISTP(CATlsoEdgeEqClassGraph) & oConnexComponents );

  CATBoolean IsClassOfRotations();
  CATBoolean IsClassOfTranslations();


private : 

   CATlsoEdgeEqClassGraph( CATlsoGraphFactory * iLsoGraphFactory );
   ~CATlsoEdgeEqClassGraph();

  CATBoolean EdgesAreEqual();

  CATBoolean VerifySplitCondition();

  CATlsoTransformationType GetTransfoType();

friend class CATlsoGraphFactory;

};

#endif // #ifdef COVERAGE_REMOVE_CODE

#endif
