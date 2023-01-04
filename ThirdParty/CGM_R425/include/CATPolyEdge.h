// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyEdge
// Polyhedral macro edge
//
//=============================================================================
// 2009-11-03   NDO: Revisited implementation, optimizations (size of CATPolyCell objects.)
// 2006-08-27   BPG: Raise
// 2003-03-20   FDS: New
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATErrorDef.h"
#include "CATPolyCell.h"
#include "CATPolyMicroTopologyFwd.h"
#include "CATPolyMacroTopologyFwd.h"

class CATPolyEdgeCurve;


// This class cannot be virtual.
class ExportedByPolyMODEL CATPolyEdge : public CATPolyCell
{

public:

/** @name Casting methods
    @{ */

  /**
   * Casts a CATPolyCell as a CATPolyEdge.
   */
  inline static CATPolyEdge* Cast (CATPolyCell* iCell);

  /**
   * Casts a const CATPolyCell as a const CATPolyEdge.
   */
  inline static const CATPolyEdge* Cast (const CATPolyCell* iCell);

/** @} */

public:

/** @name Topology
    @{ */

  /**
   * @return 
   *   The start vertex of the edge.
   */
  CATPolyVertex* GetStartVertex ();

  /**
   * @return 
   *   The end vertex of the edge.
   */
  CATPolyVertex* GetEndVertex ();

  /**
   * @return 
   *   The index of the starting vertex of the underlying curves.
   */
  int GetStartPoint () const;

  /**
   * @return 
   *   The index of the end vertex of the underlying curves.
   */
  int GetEndPoint () const;

  /** 
   * Returns true if the edge is incident to one or more faces.
   */
  bool HasIncidentFaces () const;

  // To get rid of (see DraftingGenModeler and GeometryVisualization).
  inline bool IsFree () const;

  /* 
   * Return true if the edge is manifold and false otherwise.
   */ 
  inline bool IsManifold () const;

/** @} */

public:  // Private?

  friend class CATPolyBody;

  CATPolyEdgeCurve& GetEdgeCurve ();

private:

/** @name Life-cycle
    @{ */

  CATPolyEdge (unsigned int iTag = 0);

  /** 
   * Creates a CATPolyEdge.
   */
  static inline CATPolyEdge* New (unsigned int iTag = 0);

public:  // Private?

  ~CATPolyEdge ();  // Not virtual!

/** @} */

private:

  // Forbidden constructs.
  CATPolyEdge(const CATPolyEdge &);
  CATPolyEdge &operator=(const CATPolyEdge &RHS);
  int operator==(const CATPolyEdge &RHS) const;
  int operator!=(const CATPolyEdge &RHS) const;

};

inline CATPolyEdge* CATPolyEdge::New (unsigned int iTag)
{
  return new CATPolyEdge (iTag);
}

inline CATPolyEdge* CATPolyEdge::Cast (CATPolyCell* iCell)
{
  return iCell ? iCell->CastToEdge() : 0;
}

inline const CATPolyEdge* CATPolyEdge::Cast (const CATPolyCell* iCell)
{
  return iCell ? iCell->CastToEdge () : 0;
}

inline bool CATPolyEdge::IsManifold () const
{
  return !(HasMultipleOrbits<CATPolyDart2> () || HasMultipleOrbits<CATPolyDart3> ());
}

inline bool CATPolyEdge::IsFree () const
{
  return !HasIncidentFaces ();
}
