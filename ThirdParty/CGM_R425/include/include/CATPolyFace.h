// COPYRIGHT DASSAULT SYSTEMES 2003, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyFace
// Polyhedral macro face
//
//=============================================================================
// 2016-01-04   JXO: const GetSurfaceVertexCellLayer
// 2009-11-03   NDO: Revisited implementation, optimizations (size of CATPolyCell objects.)
// 2008-01-22   MNA: Ajout de la méthode RemoveDart pour les methodes Remove sur le polyBody
// 2006-08-27   BPG: Raise
// 2003-03-20   FDS: New
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATErrorDef.h"
#include "CATPolyCell.h"
#include "CATPolyMacroTopologyFwd.h"
#include "CATPolyDart.h"

class CATIPolySurfaceVertexCellConstLayer;
class CATIPolySurfaceVertexCellLayer;


// This class cannot be virtual.
class ExportedByPolyMODEL CATPolyFace : public CATPolyCell
{

public:

/** @name Casting methods
    @{ */

  /**
   * Casts a CATPolyCell as a CATPolyFace.
   */
  inline static CATPolyFace* Cast (CATPolyCell* iCell);

  /**
   * Casts a const CATPolyCell as a const CATPolyFace.
   */
  inline static const CATPolyFace* Cast (const CATPolyCell* iCell);

/** @} */

public:

/** @name Orientation
    @{ */

  /**
   * Sets the relative orientation of the face in the context of its body. 
   */
  inline void SetRelativeOrientation (int iOrientation);

  /**
   * Gets the relative orientation of the face in the context of its body.
   */
  inline int GetRelativeOrientation () const;

/** @} */

public:

/** @name Geometry
    @{ */

  /**
   * @return
   *   The CATIPolySurface associated to this face.
   */
  const CATIPolySurface& GetSurface () const;

  /**
   * @return
   *   The CATIPolySurface associated to this face.
   */
  CATIPolySurface& GetSurface ();

  /**
   * Returns the surface vertex cell layer.
   * This is an upward link from the CATIPolySurface to the macro-topology of the
   * CATPolyBody: CATPolyVertex, CATPolyEdge or CATPolyFace cells.
   * @param oLayer [out, IUnknown#Release] 
   *   The ouput layer.  The returned layer must be released (ref-counted.)
   * @return
   *   S_OK if a layer is successfully returned.
   *   S_FALSE if a layer is not available.
   *   E_FAIL if an error occurs.
   */
  HRESULT GetSurfaceVertexCellLayer (CATIPolySurfaceVertexCellConstLayer*& oLayer) const;

  /**
   * Substitutes the native geometry by another native geometry.
   * This applies only if the CATPolyFace refers to a native geometry.
   */
  HRESULT Substitute (CATIPolySurface& Sin);

/** @} */

public:

  /**
   * Reserved for construction of CATPolyBody.
   * Temporary layer should not be needed.
   */
  void AbsorbSurfaceVertexCellLayer (CATIPolySurfaceVertexCellLayer* iLayer);

  /**
   * Reserved for construction of CATPolyBody.
   * Temporary layer should not be needed.
   */
  void FlushSurfaceVertexCellLayer ();

  /**
   * Reserved for CATPolyBody.
   * This method does not create a surface vertex cell layer if none is available.
   * No release for returned surface vertex cell layer.
   */
  CATIPolySurfaceVertexCellLayer* FetchVertexCellLayer ();

  /**
   * Reserved for CATPolyBody.
   * This method will create a surface vertex cell layer if one is not available.
   * No release for returned surface vertex cell layer.
   */
  CATIPolySurfaceVertexCellLayer* GetVertexCellLayer ();

  /**
   * Reserved for CATPolyBody.
   * This method will create a surface vertex cell layer if one is not available.
   * No release for returned surface vertex cell layer.
   */
  CATIPolySurfaceVertexCellConstLayer* GetVertexCellConstLayer ();

private:

  /**
   * Adding 2-orbits (loops).
   * Loops are not stored explicitely in the model.
   * Add an orbit to the face by giving the starting dart of the orbit.
   * For an open-orbit, the start dart is the extremity having smallest address.
   * For a close orbit, the start dart is the dart with the smallest address around the orbit.
   * See AddOrbit () and RemoveOrbit () methods from CATPolyCell.
   */

  friend class CATPolyBody;

  /**
    * Relative orientation of a face in its body.
    * By default, the relative orientation of a CATPolyFace in a CATPolyBody is positive and equal to +1;
    * (for skin and solid bodies).
    */
  enum FaceBodyOrientation
  {
    /* Positive orientation */   PosFaceBody = 0x04,
    /* Null orientation */       NulFaceBody = 0x05,
    /* Negative orientation */   NegFaceBody = 0x06
  };

private:

/** @name Life-cycle
    @{ */

  CATPolyFace (CATIPolySurface& iSurface, unsigned int iTag = 0);

  /**
   * Creates a CATPolyFace.
   */
  static CATPolyFace* New (CATIPolySurface& iSurface, unsigned int iTag = 0);

public:  // Private?

  ~CATPolyFace ();  // Not virtual!

/** @} */

private:

  // Forbidden constructs.
  CATPolyFace(const CATPolyFace &RHS);
  CATPolyFace &operator=(const CATPolyFace &RHS);
  int operator==(const CATPolyFace &RHS) const;
  int operator!=(const CATPolyFace &RHS) const;

};

namespace Poly
{
  // Returns true if the face-orbit is open.
  // Its first dart is 0-free or 1-free.
  ExportedByPolyMODEL bool IsOpen (const CATPolyFaceOrbit& orbit);
}

inline CATPolyFace* CATPolyFace::Cast (CATPolyCell* iCell)
{
  return iCell ? iCell->CastToFace() : 0;
}

inline const CATPolyFace* CATPolyFace::Cast (const CATPolyCell* iCell)
{
  return iCell ? iCell->CastToFace () : 0;
}

inline void CATPolyFace::SetRelativeOrientation (int iOrientation)
{
  _BitFields &= ~MaskCells;  // Clear the first three bits.
  if (iOrientation > 0)
    _BitFields |= PosFaceBody;
  else if (iOrientation == 0)
    _BitFields |= NulFaceBody;
  else
    _BitFields |= NegFaceBody;
}

inline int CATPolyFace::GetRelativeOrientation () const
{
  switch (MaskCells & _BitFields)
  {
  case PosFaceBody:
  default:
    return 1;
  case NulFaceBody:
    return 0;
  case NegFaceBody:
    return -1;
  };
}
