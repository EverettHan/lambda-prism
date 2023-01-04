
// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTrianglePartitionDefiner.h
// Header definition of CATPolyTrianglePartitionDefiner
//
//===================================================================
//
// Usage notes: 
// CallBack class used by CATPolySurfaceSubdividor
// in order to externalize the criteria of the surface partition
//
//===================================================================
//
// November 2012 Creation: dps
//===================================================================

#ifndef CATPolyTrianglePartitionDefiner_H
#define CATPolyTrianglePartitionDefiner_H

#include "PolyMeshTools.h"         // ExportedBy


class ExportedByPolyMeshTools CATPolyTrianglePartitionDefiner
{

public:

  CATPolyTrianglePartitionDefiner() {};
  virtual ~CATPolyTrianglePartitionDefiner() {};

  virtual int GetPartitionValue(int iTriangleID)=0;

};

/*
* Default implementation of CATPolyTrianglePartitionDefiner for a CATPolySurfaceSubdividor
* consisting in making one SubMesh per triangle with its own index as PartitionValue
*/
class ExportedByPolyMeshTools CATPolyTriangleDisconnection : public CATPolyTrianglePartitionDefiner
{

public:

  CATPolyTriangleDisconnection() {};
  virtual ~CATPolyTriangleDisconnection() {};

  virtual int GetPartitionValue(int iTriangleID) { return iTriangleID; };

};

// H7W : Janvier 2015
/*
* Default implementation of CATPolyTrianglePartitionDefiner for a CATPolySurfaceSubdividor
* consisting in making one SubMesh per set of connected triangles with the input PartitionValue
*/
class ExportedByPolyMeshTools CATPolyTriangleConnection : public CATPolyTrianglePartitionDefiner
{

private:
  int _PartitionValue;

public:

  CATPolyTriangleConnection(int iPartitionValue = 0) { _PartitionValue = iPartitionValue; };
  virtual ~CATPolyTriangleConnection() {};

  virtual int GetPartitionValue(int iTriangleID) { return _PartitionValue; };

};

#endif
