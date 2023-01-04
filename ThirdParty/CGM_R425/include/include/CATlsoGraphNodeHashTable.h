#ifndef CATlsoGraphNodeHashTable_H
#define CATlsoGraphNodeHashTable_H

#include "CATPersistentCell.h"
#include "CATlsoGraphElem.h"
#include "CATCGMHashTable.h"

class CATlsoGraphNode;
    
class ExportedByPersistentCell CATlsoGraphNodeHashTable : public CATCGMHashTable
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation
  CATlsoGraphNodeHashTable();
  ~CATlsoGraphNodeHashTable();

  int Insert(CATlsoGraphNode * ipElem);

  CATlsoGraphNode*  Get(int iPos) const;

  void Insert( CATlsoGraphNodeHashTable * iGraphNodeHT);


};

#endif
