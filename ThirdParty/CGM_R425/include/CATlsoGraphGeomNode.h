#ifndef CATlsoGraphGeomNode_H
#define CATlsoGraphGeomNode_H

#ifdef COVERAGE_REMOVE_CODE

#include "CATPersistentCell.h"
#include "CATlsoGraphNode.h"
#include "CATListOfCATGeometries.h"
#include "CATlsoGraphFactory.h"
    
class ExportedByPersistentCell CATlsoGraphGeomNode : public CATlsoGraphNode
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATBoolean IsGeomNode();
  virtual CATlsoGraphGeomNode * GetAsGeomNode();

  void GetGeomList( CATLISTP(CATGeometry) & oGeomList);

  CATBoolean Locate( CATGeometry * iGeom );

  virtual CATMathPoint GetCentroide();

protected : 
  CATlsoGraphGeomNode( CATGeometry * iGeom, CATlsoGraphFactory  * iLsoGraphFactory );
  CATlsoGraphGeomNode( CATLISTP(CATGeometry) & iGeomList, CATlsoGraphFactory  * iLsoGraphFactory);
  ~CATlsoGraphGeomNode();

private :

  CATLISTP(CATGeometry) _GeomList;

friend class CATlsoGraphFactory;
};

#endif // #ifdef COVERAGE_REMOVE_CODE

#endif

