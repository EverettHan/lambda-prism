#ifndef CATlsoGraphEdge_H
#define CATlsoGraphEdge_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "CATlsoGraphElem.h"
#include "CATlsoGraphFactory.h"

class CATlsoGraphNode;
class CATlsoGraphTransfoEdge;
    
class ExportedByPersistentCell CATlsoGraphEdge : public CATlsoGraphElem
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATlsoGraphTransfoEdge * GetAsTransfoEdge();
  virtual CATBoolean Equals( CATlsoGraphEdge * iEdgeToCompare );
  virtual void Dump( CATCGMOutput & Output, int iColor ) = 0;

  CATlsoGraphNode * GetStartNode();
  CATlsoGraphNode * GetEndNode();
  CATBoolean IsOriented();

  CATBoolean Contains( CATlsoGraphNode * iNode );

protected : 
   CATlsoGraphEdge( 
                   CATlsoGraphNode * iStartNode,
                   CATlsoGraphNode * iEndNode,
                   CATBoolean IsOriented,
                   CATlsoGraphFactory  * iLsoGraphFactory
                  );

  ~CATlsoGraphEdge(); 




private : 

  CATlsoGraphNode * _StartNode;
  CATlsoGraphNode * _EndNode;
  CATBoolean _IsOriented;

  friend class CATlsoGraphFactory;

  
};

#endif // #ifdef COVERAGE_REMOVE_CODE

#endif
