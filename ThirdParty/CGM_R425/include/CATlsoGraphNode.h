#ifndef CATlsoGraphNode_H
#define CATlsoGraphNode_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "CATlsoGraphElem.h"
#include "CATlsoGraphFactory.h"

class CATlsoGraphGeomNode;
    
class ExportedByPersistentCell CATlsoGraphNode : public CATlsoGraphElem
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATBoolean IsGeomNode();
  virtual CATlsoGraphGeomNode * GetAsGeomNode();

  virtual CATMathPoint GetCentroide() = 0;

protected : 
  CATlsoGraphNode( CATlsoGraphFactory  * iLsoGraphFactory );
  ~CATlsoGraphNode();

 friend class CATlsoGraphFactory;

};

#endif // #ifdef COVERAGE_REMOVE_CODE

#endif
