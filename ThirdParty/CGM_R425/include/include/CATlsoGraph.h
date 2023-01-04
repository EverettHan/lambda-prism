#ifndef CATlsoGraph_H
#define CATlsoGraph_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "ListPOfCATlsoNodeEqClassGraph.h"
#include "ListPOfCATlsoEdgeEqClassGraph.h"
#include "CATlsoGraphElem.h"
#include "CATMathTransformation.h"
#include "ListPOfCATlsoGraph.h"
#include "CATCGMHashTable.h"
#include "CATlsoGraphFactory.h"


class CATlsoIncidenceHT;
class CATlsoGraphNode;
class CATlsoGraphEdge;
class CATlsoGraphGeomNode;
class CATlsoGraphTransfoEdge;
class HashTableAssocHashTable;
class CATlsoGraphNodeHashTable;
class CATlsoGraphEdgeHashTable;
    
class ExportedByPersistentCell CATlsoGraph : public CATlsoGraphElem
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation


  HRESULT CreateNodeEquivalenceClasses( HashTableAssocHashTable * iGeomEquivalences, CATLISTP(CATlsoNodeEqClassGraph) & oEqClassesList ) ; // Here HashTableAssocHashTable must be replace by an child class.
  HRESULT CreateEdgeEquivalenceClasses( CATLISTP(CATlsoEdgeEqClassGraph) & oEqClassesList ) ;
  HRESULT CreateEdgeEquivalenceClasses( CATlsoGraphEdgeHashTable * iEdgesHT, CATLISTP(CATlsoEdgeEqClassGraph) & oEqClassesList, CATBoolean iStrictEquivalenceClasses = FALSE ) ;

  CATBoolean HasEdges();

  CATlsoGraphGeomNode * CreateNode( CATGeometry * iGeom );
  CATlsoGraphTransfoEdge * CreateEdge( CATlsoGraphNode      * iStartNode,
                           CATlsoGraphNode      * iEndNode, 
                           CATMathTransformation & iTransfo );

  void  AddNode( CATlsoGraphNode * iNode );
  void  AddEdge( CATlsoGraphEdge * iEdge );
  void  AddEdge( CATlsoGraphEdgeHashTable * iEdgesHT );

  CATlsoGraphGeomNode * GetNode( CATGeometry * iGeom );

  CATlsoNodeEqClassGraph * ExtractNodeEqClassGraph( CATlsoGraphNodeHashTable * iSubGraphNodes );

  CATlsoGraphEdgeHashTable * GetAllEdges();
  CATlsoGraphNodeHashTable * GetAllNodes();

 // CATlsoGraphEdgeHashTable * GetEdgesThatTouchSubgraph( CATlsoGra);

  CATCGMHashTable * GetEdges( CATlsoGraphNode * iNode ) ;

  int GetNumberOfEdges();

  HRESULT ComputeConnexComponents( CATLISTP(CATlsoGraph) & oConnexComponents );

  HRESULT FindBijectionEdges(CATlsoGraph * iSubGraph1, CATlsoGraph * iSubGraph2, CATLISTP(CATlsoEdgeEqClassGraph) & oBijectionEdgesEqClassesList, CATlsoGraphEdgeHashTable ** oNonBijectiveBridgeEdges = NULL);

  // Return the Edges of this that link a Node of iSubGraph1 and a node of iSubGraph2.
  HRESULT FindBridgeEdges(CATlsoGraph * iSubGraph1, CATlsoGraph * iSubGraph2, CATlsoGraphEdgeHashTable *& oBridgeEdges);

  // Remove all the nodes of iNodesToRemove and all the Edges of this that touch a node of iNodesToRemove.
  HRESULT Remove( CATlsoGraphNodeHashTable * iNodesToRemove );
  HRESULT Remove( CATlsoGraphNode * iNodeToRemove );

  CATlsoGraphEdge * GetFirstEdge();

  void Dump( const char * iString = "CATlsoGraph"); 
  static void Dump( CATLISTP(CATlsoGraph)  & GraphList);
  static void Dump( CATLISTP(CATlsoEdgeEqClassGraph)  & GraphList);
  static void Dump( CATLISTP(CATlsoNodeEqClassGraph)  & GraphList);

protected : 

  CATlsoGraph( CATlsoGraphFactory * ilsoGraphFactory);
  ~CATlsoGraph();

  CATlsoIncidenceHT * GetIncidenceHT();
  CATlsoGraph( CATlsoIncidenceHT * iIncidenceHT, CATlsoGraphFactory * ilsoGraphFactory );

  HRESULT FindBijectionEdges(CATlsoGraph * iSubGraph1, CATlsoGraph * iSubGraph2, CATlsoEdgeEqClassGraph * iEdgesStrictEqClasse, CATlsoEdgeEqClassGraph *& oBijection);

  void PartialDump( CATCGMOutput & Output, int iColor = 1);

private : 

  void Init();
  CATlsoIncidenceHT * _IncidenceHT;

friend class CATlsoGraphFactory;



};

#endif // #ifdef COVERAGE_REMOVE_CODE

#endif
