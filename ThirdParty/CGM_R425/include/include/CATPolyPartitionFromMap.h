
// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyPartitionFromMap.h
// Header definition of CATPolyPartitionFromMap
//
//===================================================================
//
// Usage notes: Associates a partition number for each triangle of the mesh,
//   according to the value associated to its ID in the map.
//
//===================================================================
//
// July 2020 Creation: RBU3
//===================================================================

#ifndef CATPolyPartitionFromMap_H
#define CATPolyPartitionFromMap_H

#include "CATPolyTrianglePartitionDefiner.h" // derivation
#include "PolyMeshTools.h"                   // ExportedBy

#include "CATBoolean.h" 
#include "CATSysBoolean.h" 

#include "CATMapOfIntToInt.h"

class CATIPolyMesh;


class ExportedByPolyMeshTools CATPolyPartitionFromMap : public CATPolyTrianglePartitionDefiner
{

public:

  CATPolyPartitionFromMap(const CATMapOfIntToInt &iMapTrIdToPartition);

  ~CATPolyPartitionFromMap();

  virtual int GetPartitionValue(int iTriangleID);


private:


  // INPUT
  // =====

  const CATMapOfIntToInt             & _MapTrIdToPartition;

};

#endif
