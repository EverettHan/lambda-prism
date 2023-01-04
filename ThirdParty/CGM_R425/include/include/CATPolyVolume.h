// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyVolume
//
//=============================================================================
// 2022-02-02   NDO: New
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATErrorDef.h"
#include "CATPolyCell.h"
#include "CATPolyMacroTopologyFwd.h"


// This class cannot be virtual.
class ExportedByPolyMODEL CATPolyVolume : public CATPolyCell
{

public:

/** @name Casting methods
    @{ */

  /**
   * Casts a CATPolyCell into a CATPolyVolume.
   */
  inline static CATPolyVolume* Cast (CATPolyCell* iCell);

  /**
   * Casts a const CATPolyCell into a const CATPolyVolume.
   */
  inline static const CATPolyVolume* Cast (const CATPolyCell* iCell);

/** @} */

public:

/** @name Orientation
    @{ */

  /**
   * Sets the relative orientation of a face w.r.t. the volume.
   */
  void SetRelativeOrientation (CATPolyFace& iFace, RelativeOrientation iOrientation);

  /**
   * Gets the relative orientation of a face w.r.t. the volume.
   */
  RelativeOrientation GetRelativeOrientation (CATPolyFace& iFace) const;

/** @} */

private:

  friend class CATPolyBody;
  friend class CATPolyBodyHelpers;

private:

/** @name Life-cycle
    @{ */

  CATPolyVolume (unsigned int iTag = 0);
  ~CATPolyVolume ();  // Not virtual!

  /** Creates a CATPolyVolume. */
  static CATPolyVolume* New (unsigned int iTag = 0);

/** @} */

private:

  // Forbidden constructs.
  CATPolyVolume (const CATPolyVolume& RHS);
  CATPolyVolume& operator= (const CATPolyVolume& RHS);
  int operator== (const CATPolyVolume& RHS) const;
  int operator!= (const CATPolyVolume& RHS) const;

};

inline CATPolyVolume* CATPolyVolume::Cast (CATPolyCell* iCell)
{
  return iCell ? iCell->CastToVolume () : 0;
}

inline const CATPolyVolume* CATPolyVolume::Cast (const CATPolyCell* iCell)
{
  return iCell ? iCell->CastToVolume () : 0;
}
