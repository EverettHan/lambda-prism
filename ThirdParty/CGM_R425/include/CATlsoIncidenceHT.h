#ifndef CATlsoIncidenceHT_H
#define CATlsoIncidenceHT_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "HashTableAssocHashTable.h"

class CATlsoGraphNode;
class CATlsoGraphEdge;

    
class ExportedByPersistentCell CATlsoIncidenceHT : public HashTableAssocHashTable
{
public:

  CATlsoIncidenceHT( int iExpectedSize = 0 );
  ~CATlsoIncidenceHT();


  void AddNode( CATlsoGraphNode * iNode );
  void AddEdge( CATlsoGraphEdge * iEdge );

  void RemoveNode( CATlsoGraphNode * iNode );

  CATlsoGraphNode * GetItem(int iElem);

};

#endif // #ifdef COVERAGE_REMOVE_CODE

#endif
