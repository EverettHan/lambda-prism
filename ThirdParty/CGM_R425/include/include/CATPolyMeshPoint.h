// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshPoint.h
//
//===================================================================
// May 2015  Creation NDO
//===================================================================
#ifndef CATPolyMeshPoint_H
#define CATPolyMeshPoint_H

#include "PolyMeshImpl.h"
#include "CATIPolyMeshPoint.h"
#include "CATPolyMeshPointDef.h"
#include "CATIPolyMeshObserver.h"

#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATMathPoint.h"
#include "CATPoly.h"

class CATIPolyMesh;


/**
 * Class defining a mesh-point.
 * A mesh-point lies on a CATIPolyMesh.  It refers to a sub-element of the mesh which can be
 * a vertex (surface-vertex), a bar (surface-bar) or a triangle of the mesh. 
 */
class ExportedByPolyMeshImpl CATPolyMeshPoint : public CATIPolyMeshPoint
{

public:

  /**
   * Construction of a CATPolyMeshPoint.
   * @param mesh
   *   The mesh on which the point lies.
   */
  static CATPolyMeshPoint* New (const CATIPolyMesh& mesh);

  CATBoolean IsEditable () const;

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolyPoint as a const CATPolyMeshPoint.
   */
  static const CATPolyMeshPoint* Cast (const CATIPolyPoint* C);

  /**
   * Casts a CATIPolyPoint as a CATPolyMeshPoint.
   */
  static CATPolyMeshPoint* Cast (CATIPolyPoint* C);

/** @} */

public:

  inline const CATIPolyMesh& GetMesh () const;

  CATBoolean IsLyingOn (const CATIPolySurface &s) const;

public:

  CATBoolean IsLyingOn (const CATIPolyCurve& c) const;

  const CATIPolyCurve* IsStartVertex () const;
  CATIPolyCurve* IsStartVertex ();

  const CATIPolyCurve* IsEndVertex () const;
  CATIPolyCurve* IsEndVertex ();

public:

/** @name Mesh-Point Definition
    @{ */

  HRESULT SetMeshPoint (const CATPolyMeshPointDef& mp);

  HRESULT GetMeshPoint (CATPolyMeshPointDef& oMP) const;

/** @} */

public:

  HRESULT GetPosition (CATMathPoint& P) const;
  HRESULT SetPosition (const CATMathPoint& P);

  HRESULT SetSupport (CATIPolySupport* iSupport);
  HRESULT GetSupport (CATIPolySupport*& oSupport) const;

public:

  HRESULT RegisterObserver (CATIPolyPointObserver &iObserver);
  HRESULT UnregisterObserver (CATIPolyPointObserver &iObserver);

  HRESULT Accept (const CATIPolyPoint& iPoint, CATPolyPointConstVisitor& iV) const;
  HRESULT Accept (CATIPolyPoint& iPoint, CATPolyPointVisitor& iV);

  CATIPolyPointConstTools* GetConstTools () const;
  CATIPolyPointTools* GetTools ();

private:

  const CATIPolyMesh& _Mesh;
  CATIPolyPointObserver *_Observer;

  CATPolyMeshPointDef _MeshPoint;
  CATMathPoint _Position;  // Computed from the barycentric coordinates.

private:

  // Copy constructor/operator are forbidden.
  CATPolyMeshPoint (const CATPolyMeshPoint& iRHS);
  CATPolyMeshPoint& operator= (const CATPolyMeshPoint& iRHS);

private:

  CATPolyMeshPoint (const CATIPolyMesh& mesh);
  virtual ~CATPolyMeshPoint ();

};


inline const CATIPolyMesh& CATPolyMeshPoint::GetMesh () const
{
  return _Mesh;
}

#endif
