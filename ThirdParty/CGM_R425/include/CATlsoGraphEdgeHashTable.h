#ifndef CATlsoGraphEdgeHashTable_H
#define CATlsoGraphEdgeHashTable_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "CATlsoGraphElem.h"
#include "CATCGMHashTable.h"

class CATlsoGraphEdge;
    
class ExportedByPersistentCell CATlsoGraphEdgeHashTable : public CATCGMHashTable
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation
  CATlsoGraphEdgeHashTable();
  ~CATlsoGraphEdgeHashTable();

  int Insert(CATlsoGraphEdge * ipElem);

  CATlsoGraphEdge*  Get(int iPos) const;

  void Insert( CATlsoGraphEdgeHashTable * iHT );

  void Dump( const char * iString = NULL );


};

#endif // #ifdef COVERAGE_REMOVE_CODE

#endif
