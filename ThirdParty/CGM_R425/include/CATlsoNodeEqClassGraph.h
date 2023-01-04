#ifndef CATlsoNodeEqClassGraph_H
#define CATlsoNodeEqClassGraph_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "CATlsoEqClassGraph.h"
#include "CATlsoGraphFactory.h"
    
class ExportedByPersistentCell CATlsoNodeEqClassGraph : public CATlsoEqClassGraph
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  static HRESULT MergeClassesWithNeighboursFaces ( CATLISTP(CATlsoNodeEqClassGraph) & iFacesNodeEqClasseList, CATLISTP(CATlsoNodeEqClassGraph) & oNodeEqClasseList );

protected : 
  CATlsoNodeEqClassGraph( CATlsoGraphFactory * iLsoGraphFactory );
  ~CATlsoNodeEqClassGraph();

friend class CATlsoGraphFactory;

};

#endif // #ifdef COVERAGE_REMOVE_CODE

#endif
