#ifndef CATSpatialHashTable_TopoTools_h
#define CATSpatialHashTable_TopoTools_h

#include "CATBoolean.h"
#include "ExportedByCATTopologicalObjects.h"

class CATVertex;
class CATMathPoint;
class CellHashTableAssocList;
class CATAdaptiveHashTable;
class CATListPtrCATVertex;
class CATSubdVertex;
class CATListValCATMathPoint;
class CATRawCollPV;
class CATSpatialHashTable;

/**
* Creates a table and fill it from a list of vertices.
*/
ExportedByCATTopologicalObjects  CATSpatialHashTable * CreateAndFillSpatialTableFromVertexList(CATListPtrCATVertex & iVertices, double iTolerance);

/**
* Creates a table and fill it from an hash table of vertices.
*/
ExportedByCATTopologicalObjects   CATSpatialHashTable * CreateAndFillSpatialTableFromVertexCHTAL(CellHashTableAssocList & iVertices, double iTolerance);

/**
* Creates a table and fill it from an hash table of CATSubdVertex.
*/
ExportedByCATTopologicalObjects CATSpatialHashTable * CreateAndFillSpatialTableFromSubdVertexHashTable(CATAdaptiveHashTable & iSubdVertices, double iTolerance);

/**
* Retrieves the mathpoint from a vertex.
*/
ExportedByCATTopologicalObjects void RetrieveMathPoint(CATVertex * iVertex, CATMathPoint & oMathPoint);

/**
* Retrieves the mathpoint from a subdvertex.
*/
ExportedByCATTopologicalObjects void RetrieveMathPoint(CATSubdVertex * iSubdVertex, CATMathPoint & oMathPoint);


/**
* Retrieves the vertex from the SpatialHashTable
*/
void ExportedByCATTopologicalObjects RemoveFromSpatialHashTable(CATSpatialHashTable * iSpatialTable, CATVertex * iVertex);


#endif
