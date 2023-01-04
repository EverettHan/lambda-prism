// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyMeshCurve.h
//
//===================================================================
// June 2016  Creation NDO
//===================================================================
#ifndef CATIPolyMeshCurve_H
#define CATIPolyMeshCurve_H

#include "PolyhedralModel.h"
#include "CATIPolyCurve.h"

class CATIPolyMesh;
class CATPolyMeshPointDef;


/**
 * Interface to a polyhedral mesh-curve.
 *
 * A mesh-curve is a CATIPolyCurve that lies on a CATIPolyMesh.  
 * Each segment of the curve lies on a sub-element of the mesh (bar or triangle).
 * 
 * Implementations of this interface should be thread-safe for use with the polyhedral operators.
 */
class ExportedByPolyhedralModel CATIPolyMeshCurve : public CATIPolyCurve
{

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a CATIPolyCurve into a CATIPolyMeshCurve.
   */
  inline static CATIPolyMeshCurve* Cast (CATIPolyCurve* C);

  /**
   * Casts a const CATIPolyCurve into a const CATIPolyMeshCurve.
   */
  inline static const CATIPolyMeshCurve* Cast (const CATIPolyCurve* C);

  const CATIPolySurfaceVertexLine* CastToSurfaceVertexLine () const;
  CATIPolySurfaceVertexLine* CastToSurfaceVertexLine ();

  const CATIPolyMeshCurve* CastToMeshCurve () const;
  CATIPolyMeshCurve* CastToMeshCurve ();

/** @} */

public:

  /**
   * Returns the mesh on which the mesh-curve is defined.
   */
  virtual const CATIPolyMesh& GetMesh () const = 0;

public:

/** @name Mesh-Point Queries
    @{ */

  /**
   * Returns the mesh-point associated to a given curve-vertex.
   * @param v
   *   The input curve-vertex.
   * @param oMP
   *   The output definition of the mesh-point.
   */
  virtual HRESULT GetMeshPoint (int v, CATPolyMeshPointDef& oMP) const = 0;

/** @} */

};

inline CATIPolyMeshCurve* CATIPolyMeshCurve::Cast (CATIPolyCurve* C)
{
  return C ? C->CastToMeshCurve () : 0;
}

inline const CATIPolyMeshCurve* CATIPolyMeshCurve::Cast (const CATIPolyCurve* C)
{
  return C ? C->CastToMeshCurve () : 0;
}

#endif // !CATIPolyMeshCurve_H
