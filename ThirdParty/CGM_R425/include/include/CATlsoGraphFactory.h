#ifndef CATlsoGraphFactory_H
#define CATlsoGraphFactory_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "ListPOfCATlsoGraphElem.h"

class CATlsoGraph;
class CATlsoEdgeEqClassGraph;
class CATlsoEqClassGraph;
class CATlsoGraphEdge;
class CATlsoGraphNode;
class CATlsoGraphGeomNode;
class CATlsoGraphTransfoEdge;
class CATlsoNodeEqClassGraph;
class CATTolerance;


class ExportedByPersistentCell CATlsoGraphFactory
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation
  CATlsoGraphFactory(const CATTolerance& iTolerance);
  virtual ~CATlsoGraphFactory();


  // WARNING : for debug use ONLY !
  int GetDebugTag();

  CATlsoGraph            * CreateCATlsoGraph();
  CATlsoEdgeEqClassGraph * CreateCATlsoEdgeEqClassGraph();
  CATlsoEqClassGraph     * CreateCATlsoEqClassGraph();
  //CATlsoGraphEdge        * CreateCATlsoGraphEdge( CATlsoGraphNode * iStartNode,
  //                                                CATlsoGraphNode * iEndNode,
  //                                                CATBoolean IsOriented
  //                                               );
  //CATlsoGraphNode        * CreateCATlsoGraphNode();
  CATlsoGraphGeomNode    * CreateCATlsoGraphGeomNode( CATGeometry * iGeom );
  CATlsoGraphGeomNode    * CreateCATlsoGraphGeomNode( CATLISTP(CATGeometry) & iGeomList );
  CATlsoGraphTransfoEdge * CreateCATlsoGraphTransfoEdge( CATlsoGraphNode * iStartNode,
                                                  CATlsoGraphNode * iEndNode,
                                                  CATBoolean IsOriented,
                                                  CATMathTransformation& iTransfo
                                                 );
  CATlsoNodeEqClassGraph * CreateCATlsoNodeEqClassGraph();
  
  double GetLargeEpsgForAngleTest() const;
  double GetEpsgForLengthTest() const;
  double GetLargeEpsgForLengthTest() const;

protected : 
  
  int _DebugTag;
  const CATTolerance& _Tolerance;

  CATLISTP(CATlsoGraphElem) _GraphElemList;

};

#endif // #ifdef COVERAGE_REMOVE_CODE

#endif
