// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarGraphNodePositionLayer.h
//
//===================================================================
// October 2011  Creation NDO
//===================================================================
#ifndef CATPolyBarGraphNodePositionLayer_H
#define CATPolyBarGraphNodePositionLayer_H

#include "PolyBarGraph.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATPolyBuckets.h"
#include "CATPolyBucketsImpl.h"


/**
 * Layer of node coordinates for a CATPolyBarGraph.
 */
class ExportedByPolyBarGraph CATPolyBarGraphNodePositionLayer
{

public :

  CATPolyBarGraphNodePositionLayer () {}

  ~CATPolyBarGraphNodePositionLayer () {}

public:

  /**
   * Adds a node to the position layer.
   */
  HRESULT AddNode (const unsigned int iNode);

public:

  /**
   * Returns the 3D position of a node.
   */
  inline double* Get (const unsigned int iNode);

  inline const double* Get (const unsigned int iNode) const;

private:

  struct Position
  {
    double _Coord[3];
  };

  using PositionLayer = CATPolyBuckets<Position>;

private:

  PositionLayer _Layer;

};

double* CATPolyBarGraphNodePositionLayer::Get (const unsigned int iNode)
{
  return _Layer[iNode]._Coord;
}

const double* CATPolyBarGraphNodePositionLayer::Get (const unsigned int iNode) const
{
  return _Layer[iNode]._Coord;
}

#endif
