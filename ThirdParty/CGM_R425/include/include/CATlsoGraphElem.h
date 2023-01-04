#ifndef CATlsoGraphElem_H
#define CATlsoGraphElem_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "CATlsoGraphFactory.h"

class ExportedByPersistentCell CATlsoGraphElem
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  // WARNING : for debug use ONLY !
  int GetDebugTag();

  CATlsoGraphFactory * GetlsoGraphFactory();

protected : 
  CATlsoGraphElem( CATlsoGraphFactory * iLsoGraphFactory );
  virtual ~CATlsoGraphElem();

  int _DebugTag;
    
  CATlsoGraphFactory * _lsoGraphFactory;

  friend class CATlsoGraphFactory;

};
#endif // #ifdef COVERAGE_REMOVE_CODE

#endif
