// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraphBarCellLayer.h
//
//===================================================================
// October 2011  Creation NDO
//===================================================================
#ifndef CATPolyBodyBarGraphBarCellLayer_H
#define CATPolyBodyBarGraphBarCellLayer_H

#include "PolyBarGraph.h"
#include "CATPolyBuckets.h"
#include "CATPolyBucketsImpl.h"
#include "CATErrorDef.h"

#include "CATMapOfIntToInt.h"


/**
 * Layer of cell attributes for the bars of a CATPolyBodyBarGraph object.
 */
class ExportedByPolyBarGraph CATPolyBodyBarGraphBarCellLayer 
{

public:

  CATPolyBodyBarGraphBarCellLayer () {}

  ~CATPolyBodyBarGraphBarCellLayer () {}

public:

  /**
   * Adds a bar to the cell layer.
   */
  HRESULT AddBar (const unsigned int b);

  /**
   * Removes a bar from the cell layer.
   */
  HRESULT RemoveBar (const unsigned int b);

public:

  HRESULT SetEdge (const unsigned int b, const unsigned int e);
  HRESULT SetFace (const unsigned int b, const unsigned int f);
  HRESULT SetForcedEdge(const unsigned int b, CATBoolean isForced);

  inline unsigned int GetCell (const unsigned int b) const;

public:

  /**
   * An edge bar refers to an edge cell.
   * @return
   *   <tt>TRUE</tt> if the bar refers to a CATPolyEdge and <tt>FALSE</tt> otherwise.
   */
  inline CATBoolean IsEdgeBar (const unsigned int b) const;

  /**
   * An edge bar refers to an edge cell, it's not mandatory for a forced edge.
   * @return
   *   <tt>TRUE</tt> if the most restrictive status between the real and the forced one is edge bar, <tt>FALSE</tt> otherwise.
   */
  inline CATBoolean IsForcedEdgeBar(const unsigned int b) const;

  /**
   * A boundary bar is a bar that is adjacent to at most one face.
   */
  inline CATBoolean IsBoundaryBar (const unsigned int b) const;

  /**
   * Returns <tt>TRUE</tt> if the bar has no adjacent face.
   */
  inline CATBoolean IsBarWithoutAdjacentFace (const unsigned int b) const;

public:

  void UnsetAdjacentFace0 (const unsigned int b);
  void UnsetAdjacentFace1 (const unsigned int b);

  HRESULT SetAdjacentFace0 (const unsigned int b, const unsigned int f);
  HRESULT SetAdjacentFace1 (const unsigned int b, const unsigned int f);

  CATBoolean GetAdjacentFace0 (const unsigned int b, unsigned int& f) const;
  CATBoolean GetAdjacentFace1 (const unsigned int b, unsigned int& f) const;

public:

  inline unsigned int& HeapIndex (const unsigned int b);
  inline unsigned int HeapIndex (const unsigned int b) const;

public:

  /**
   * @param u : use TRUE if the bar b should be uncollapsable, FALSE otherwise
   */
  inline void SetUncollapsable(const unsigned int b, CATBoolean u);

  /**
   * @return TRUE if the bar b is uncollapsable, FALSE otherwise
   */
  inline CATBoolean IsUncollapsable(const unsigned int b);

private:

  struct BarData     // Optimize size as four unsigned integers?
  {
    unsigned int _Cell;
    unsigned int _HeapIndex;        // Reserved for a heap index.
    unsigned int _BitU : 1;         // Set when the bar is uncollapsable
    unsigned int _BitsE : 2;        // Bar type. Bit 1 set when the bar is on an edge (edge-bar). Otherwise, it's a face-bar. (see Edge below.)
    unsigned int _BitsA : 3;        // Three bits reserved for bar adjacencies (see Adjacencies below.)
    unsigned int _BitField : 26;    // Unused
  };

  /**
   * State of the adjacencies to the bar.
   */
  enum Adjacencies
  {
    /** No adjacency. */                                                 eNoAdjacency     = 0x00,  // 000
    /** One adjacent face on left (same as bar cell) */                  eCellAdjacency0  = 0x04,  // 100 (Boundary Bar)
    /** One adjacent face on right (same as bar cell). */                eCellAdjacency1  = 0x05,  // 101 (Boundary Bar)
    /** One adjacent face on left (other than bar cell). */              eFaceAdjacency0  = 0x06,  // 110 (Boundary Bar)
    /** One adjacent face on right (other than bar cell). */             eFaceAdjacency1  = 0x07,  // 111 (Boundary Bar)
    /** Adjacent faces on left and right (same as bar cell). */          eCellAdjacencies = 0x01,  // 001
    /** Adjacent faces on left and right (other than bar cell). */       eFaceAdjacencies = 0x03,  // 011
  };

  enum Edge
  {
    /** Bit 1 (_BitsE) is edge bar bit. */       eEdgeBar = 0x01 , //01
    /** Bit 2 (_BitsE) is forced edge bit. */      eForcedEdgeBar = 0x02, //10
  };

  /**
   * Masks.
   */
  enum Masks
  {
    /** Bit 3 (_BitsA) is boundary bit (see Adjacencies). */                        MaskBoundary      = 0x04,
    /** Bit 2 (_BitsA) means one or two face adjacencies other than bar cell. */    MaskFaceAdjacency = 0x02
  };

  using BarCellLayer = CATPolyBuckets<BarData>;

private:

  BarCellLayer _Layer;

  CATMapOfIntToInt _BarToAdjacentFace0;   // A map of a bar to its adjacent face on the left (CCW) from Node 0.
  CATMapOfIntToInt _BarToAdjacentFace1;   // A map of a bar to its adjacent face on the left (CCW) from Node 1.

  friend class CATPolyBodyBarGraphBoundaryBarIterator;

};

inline unsigned int CATPolyBodyBarGraphBarCellLayer::GetCell (const unsigned int b) const
{
  return _Layer[b]._Cell;
}

inline CATBoolean CATPolyBodyBarGraphBarCellLayer::IsEdgeBar (const unsigned int b) const
{
  return _Layer[b]._BitsE & eEdgeBar;
}

inline CATBoolean CATPolyBodyBarGraphBarCellLayer::IsBoundaryBar (const unsigned int b) const
{
  unsigned int a = _Layer[b]._BitsA;
  return a & MaskBoundary;
}

inline CATBoolean CATPolyBodyBarGraphBarCellLayer::IsForcedEdgeBar(const unsigned int b) const
{
  unsigned int e = _Layer[b]._BitsE;
  return e & (eEdgeBar | eForcedEdgeBar);
}

inline CATBoolean CATPolyBodyBarGraphBarCellLayer::IsBarWithoutAdjacentFace (const unsigned int b) const
{
  return _Layer[b]._BitsA  == eNoAdjacency;
}

inline unsigned int& CATPolyBodyBarGraphBarCellLayer::HeapIndex (const unsigned int b)
{
  return _Layer[b]._HeapIndex;  // No checks of value of b.
}

inline unsigned int CATPolyBodyBarGraphBarCellLayer::HeapIndex (const unsigned int b) const
{
  return _Layer[b]._HeapIndex;  // No checks of value of b.
}

inline void CATPolyBodyBarGraphBarCellLayer::SetUncollapsable(const unsigned int b, CATBoolean u)
{
  _Layer[b]._BitU = static_cast<unsigned int>(u);
}

inline CATBoolean CATPolyBodyBarGraphBarCellLayer::IsUncollapsable(const unsigned int b)
{
  return static_cast<CATBoolean>(_Layer[b]._BitU);
}

#endif
