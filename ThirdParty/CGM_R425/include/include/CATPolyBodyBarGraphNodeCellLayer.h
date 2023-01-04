// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraphNodeCellLayer.h
//
//===================================================================
// September 2011  Creation NDO
//===================================================================
#ifndef CATPolyBodyBarGraphNodeCellLayer_H
#define CATPolyBodyBarGraphNodeCellLayer_H

#include "PolyBarGraph.h"
#include "CATPolyBuckets.h"
#include "CATPolyBucketsImpl.h"
#include "CATErrorDef.h"


/**
 * Layer of cell attributes for the nodes of a CATPolyBodyBarGraph object.
 */
class ExportedByPolyBarGraph CATPolyBodyBarGraphNodeCellLayer 
{

public:

  CATPolyBodyBarGraphNodeCellLayer () {}

  ~CATPolyBodyBarGraphNodeCellLayer () {}

public:

  /**
   * Adds a node to the cell layer.
   */
  HRESULT AddNode (const unsigned int n);

  /**
   * Removes a node from the cell layer.
   */
  inline HRESULT RemoveNode (const unsigned int n);

public:

  inline HRESULT SetVertex (const unsigned int n, const unsigned int v);
  inline HRESULT SetEdge (const unsigned int n, const unsigned int e);
  inline HRESULT SetFace (const unsigned int n, const unsigned int f);

  inline unsigned int GetCell (const unsigned int n) const;

public:

  /**
   * Sets the boundary flag for a node to <tt>TRUE</tt> or <tt>FALSE</tt>
   * A boundary node is any node that refers to a boundary edge.
   */
  inline void SetBoundaryStatus (const unsigned int n, CATBoolean isBoundaryNode);

  /**
   * Unsets the boundary flag for a node.
   * Once unsets, the status of whether the node is on a boundary or not is undetermined.
   */
  inline void UnsetBoundaryStatus (const unsigned int n);

  /**
   * Gets the boundary flag for a node.
   * If the output boundary flag is set (<tt>TRUE</tt> or <tt>FALSE</tt>), 
   * returns <tt>S_OK</tt>, otherwise returns <tt>S_FALSE</tt>.
   * A boundary node is any node that refers to a boundary bar.
   */
  inline HRESULT GetBoundaryStatus (const unsigned int n, CATBoolean& isBoundaryNode) const;

  /**
   * Set the cut status flag for a node to <tt>isCutNode</tt>.
   * A node with a cut status is any node that have at least two different textures coordinates around it.
   */
  inline void SetCutStatus(const unsigned int n, CATBoolean isCutNode);

  /**
   * Get the cut status flag for a node.
   * A node with a cut status is any node that have at least two different textures coordinates around it.
   */
  inline CATBoolean GetCutStatus(const unsigned int n) const;

  /**
   * Set the forced vertex status flag for a node.
   */
  inline void SetForcedVertex(const unsigned int n, CATBoolean isForced);

  /**
   * Set the forced edge status flag for a node.
   */
  inline void SetForcedEdge(const unsigned int n, CATBoolean isForced);

  /**
   * Returns the type of the node:
   * <ul>
   *   <li> CATPolyBodyBarGraph::eVertexNode
   *   <li> CATPolyBodyBarGraph::eEdgeNode
   *   <li> CATPolyBodyBarGraph::eFaceNode
   * </ul>
   */
  int GetNodeType (const unsigned int n) const;

  /**
   * Returns the most restrictive type between real and forced one:
   * <ul>
   *   <li> CATPolyBodyBarGraph::eVertexNode
   *   <li> CATPolyBodyBarGraph::eEdgeNode
   *   <li> CATPolyBodyBarGraph::eFaceNode
   * </ul>
   */
  int GetForcedNodeType(const unsigned int n) const;

public:

  inline unsigned int& Index (const unsigned int n);
  inline unsigned int Index (const unsigned int n) const;

private:

  struct CellData
  {
    unsigned int _Cell;
    unsigned int _BitFlags;  // A flag indicating the type of the node (vertex, edge or face node.)
    unsigned int _Index;     // An index giving the address of attributes stored in various layers.
  };

  using NodeCellLayer = CATPolyBuckets<CellData>;

private:

  NodeCellLayer _Layer;

private:

  enum
  {
    /** Vertex-node */                  eBitVertex       = 0x01,
    /** Edge-node */                    eBitEdge         = 0x02,
    /** Face-node */                    eBitFace         = 0x04,
    /** Boundary-node */                eBitBoundary     = 0x08,
    /** Boundary-node */                eBitBoundarySet  = 0x10,
    /** Cut-node */                     eBitCut          = 0x20,
    /** Fake Vertex-Node */             eBitForcedVertex   = 0x40,
    /** Fake Edge-Node */               eBitForcedEdge     = 0x80,

    /** Forced Node mask */             eMaskForced      = eBitForcedVertex | eBitForcedEdge,
    /** Reset preservation mask */      eMaskPreserve    = eBitCut | eMaskForced
  };

};


inline HRESULT CATPolyBodyBarGraphNodeCellLayer::RemoveNode (const unsigned int n)
{
  CellData& d = _Layer[n];
  memset (&d, 0, sizeof (CellData));
  return S_OK;
}

inline HRESULT CATPolyBodyBarGraphNodeCellLayer::SetVertex (const unsigned int n, const unsigned int v)
{
  CellData& d = _Layer[n];
  d._Cell = v;
  d._BitFlags &= eMaskPreserve;
  d._BitFlags |= eBitVertex;
  return S_OK;
}

inline HRESULT CATPolyBodyBarGraphNodeCellLayer::SetEdge (const unsigned int n, const unsigned int e)
{
  CellData& d = _Layer[n];
  d._Cell = e;
  d._BitFlags &= eMaskPreserve;
  d._BitFlags |= eBitEdge;
  return S_OK;
}

inline HRESULT CATPolyBodyBarGraphNodeCellLayer::SetFace (const unsigned int n, const unsigned int f)
{
  CellData& d = _Layer[n];
  d._Cell = f;
  d._BitFlags &= eMaskPreserve;
  d._BitFlags |= eBitFace;
  return S_OK;
}

inline unsigned int CATPolyBodyBarGraphNodeCellLayer::GetCell (const unsigned int n) const
{
  return _Layer[n]._Cell;
}

inline void CATPolyBodyBarGraphNodeCellLayer::SetBoundaryStatus (const unsigned int n, CATBoolean isBoundaryNode)
{
  CellData& d = _Layer[n];
  if (isBoundaryNode)
    d._BitFlags |= eBitBoundary;
  else
    d._BitFlags &= ~eBitBoundary;
  d._BitFlags |= eBitBoundarySet;
}

inline void CATPolyBodyBarGraphNodeCellLayer::UnsetBoundaryStatus (const unsigned int n)
{
  CellData& d = _Layer[n];
  d._BitFlags &= ~eBitBoundary;
  d._BitFlags &= ~eBitBoundarySet;
}

inline HRESULT CATPolyBodyBarGraphNodeCellLayer::GetBoundaryStatus (const unsigned int n, CATBoolean& isBoundaryNode) const
{
  const CellData& d = _Layer[n];
  if (d._BitFlags & eBitBoundarySet)
  {
    isBoundaryNode = d._BitFlags & eBitBoundary;
    return S_OK;
  }
  return S_FALSE;
}

inline void CATPolyBodyBarGraphNodeCellLayer::SetCutStatus(const unsigned int n, CATBoolean isCutNode)
{
  CellData& d = _Layer[n];
  if (isCutNode)
    d._BitFlags |= eBitCut;
  else
    d._BitFlags &= ~eBitCut;
}

inline CATBoolean CATPolyBodyBarGraphNodeCellLayer::GetCutStatus(const unsigned int n) const
{
  const CellData& d = _Layer[n];
  return (d._BitFlags & eBitCut) ? TRUE : FALSE;
}

inline void CATPolyBodyBarGraphNodeCellLayer::SetForcedVertex(const unsigned int n, CATBoolean isForced)
{
  CellData& d = _Layer[n];
  if (isForced) {
    d._BitFlags &= ~eBitForcedEdge;
    d._BitFlags |= eBitForcedVertex;
  }
  else
    d._BitFlags &= ~eBitForcedVertex;
}

inline void CATPolyBodyBarGraphNodeCellLayer::SetForcedEdge(const unsigned int n, CATBoolean isForced)
{
  CellData& d = _Layer[n];
  if (isForced) {
    d._BitFlags &= ~eBitForcedVertex;
    d._BitFlags |= eBitForcedEdge;
  }
  else
    d._BitFlags &= ~eBitForcedEdge;
}

inline unsigned int& CATPolyBodyBarGraphNodeCellLayer::Index (const unsigned int n)
{
  return _Layer[n]._Index;  // No checks of value of n.
}

inline unsigned int CATPolyBodyBarGraphNodeCellLayer::Index (const unsigned int n) const
{
  return _Layer[n]._Index;  // No checks of value of n.
}

#endif
