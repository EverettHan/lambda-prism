#ifndef CATlsoGraphUtilities_H
#define CATlsoGraphUtilities_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "CATlsoEdgeEqClassGraph.h"
#include "ListPOfCATlsoEdgeEqClassGraph.h"

class CATlsoGraphNodeHashTable;
class CATlsoGraphNode;

class ExportedByPersistentCell CATlsoGraphUtilities
{
public:

  static CATlsoEdgeEqClassGraph * SelectGraphWithMostElements( CATLISTP(CATlsoEdgeEqClassGraph) & iEdgeEqClasseList );
  static CATlsoEdgeEqClassGraph * SelectGraphWithMostEdges( CATLISTP(CATlsoEdgeEqClassGraph) & iEdgeEqClasseList );
  static CATlsoGraphEdgeHashTable * GetAllEdges( CATLISTP(CATlsoEdgeEqClassGraph) & iGraphList ) ;
  static CATlsoGraphGeomNode * MergeNodes(CATlsoGraphNodeHashTable * iNodes);

};

#endif // #ifdef COVERAGE_REMOVE_CODE

#endif

