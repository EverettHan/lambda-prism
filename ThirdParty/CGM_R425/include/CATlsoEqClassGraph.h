#ifndef CATlsoEqClassGraph_H
#define CATlsoEqClassGraph_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "CATlsoGraph.h"
#include "CATlsoGraphFactory.h"
    
class ExportedByPersistentCell CATlsoEqClassGraph : public CATlsoGraph
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

protected : 
  CATlsoEqClassGraph(CATlsoGraphFactory * iLsoGraphFactory);
  ~CATlsoEqClassGraph();

friend class CATlsoGraphFactory;

};
#endif // #ifdef COVERAGE_REMOVE_CODE
#endif
