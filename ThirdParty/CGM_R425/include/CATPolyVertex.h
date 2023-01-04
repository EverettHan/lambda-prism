// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyVertex
// Vertex from a polyhedral body.
//
//=============================================================================
// 2009-11-03   NDO: Revisited implementation, optimizations (size of CATPolyCell objects.)
// 2006-08-27   BPG: New
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATErrorDef.h"
#include "CATPolyCell.h"
#include "CATPolyMacroTopologyFwd.h"
#include "CATPolyMicroTopologyFwd.h"

class CATPolyVertexPoint;


// This class cannot be virtual.
class ExportedByPolyMODEL CATPolyVertex : public CATPolyCell
{

public:

/** @name Casting methods
    @{ */

  /**
   * Casts a CATPolyCell as a CATPolyVertex.
   */
  inline static CATPolyVertex* Cast (CATPolyCell* iCell);

  /**
   * Casts a const CATPolyCell as a const CATPolyVertex.
   */
  inline static const CATPolyVertex* Cast (const CATPolyCell* iCell);

/** @} */

public:

/** @name Methods
    @{ */

  /**
   * Returns true if the vertex is incident to one or more edges or faces.
   */
  bool HasIncidentCells () const;

  /** 
   * Returns true if the vertex is manifold and false otherwise.
   */ 
  inline bool IsManifold () const;

/** @} */

private:

  friend class CATPolyBody;

  CATPolyVertexPoint& GetVertexPoint ();

private:

/** @name Life cycle
    @{ */

  CATPolyVertex (unsigned int iTag = 0);

  /** 
   * Creates a CATPolyVertex.
   */
  static inline CATPolyVertex* New (unsigned int iTag = 0);

public: // CPT: please compile all impacted fw

  ~CATPolyVertex ();  // Not virtual!

/** @} */

private:

  // Forbidden constructs.
  CATPolyVertex (const CATPolyVertex& RHS);
  CATPolyVertex& operator= (const CATPolyVertex& RHS);
  int operator== (const CATPolyVertex& RHS) const;
  int operator!= (const CATPolyVertex& RHS) const;

};

inline CATPolyVertex* CATPolyVertex::New (unsigned int iTag)
{
  return new CATPolyVertex (iTag);
}

inline CATPolyVertex* CATPolyVertex::Cast (CATPolyCell* iCell)
{
  return iCell ? iCell->CastToVertex () : 0;
}

inline const CATPolyVertex* CATPolyVertex::Cast (const CATPolyCell* iCell)
{
  return iCell ? iCell->CastToVertex () : 0;
}

inline bool CATPolyVertex::IsManifold () const
{
  return !(HasMultipleOrbits<CATPolyDart2> () || HasMultipleOrbits<CATPolyDart3> ());
}
