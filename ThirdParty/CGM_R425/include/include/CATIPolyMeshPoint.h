// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyMeshPoint.h
//
//===================================================================
// June 2016  Creation NDO
//===================================================================
#ifndef CATIPolyMeshPoint_H
#define CATIPolyMeshPoint_H

#include "PolyhedralModel.h"
#include "CATIPolyPoint.h"

class CATIPolyMesh;
class CATPolyMeshPointDef;


/**
 * Interface to a polyhedral mesh-point.
 *
 * A mesh-point is a CATIPolyPoint that lies on a CATIPolyMesh.  
 * Implementations of this interface should be thread-safe for use with the polyhedral operators.
 */
class ExportedByPolyhedralModel CATIPolyMeshPoint : public CATIPolyPoint
{

public:

/** @name Casting Methods.
    @{ */

  const CATIPolyMeshPoint* CastToMeshPoint () const;
  CATIPolyMeshPoint* CastToMeshPoint ();

/** @} */

public:

  /**
   * Returns the mesh on which the mesh-point is defined.
   */
  virtual const CATIPolyMesh& GetMesh () const = 0;

public:

/** @name Mesh-Point Definition
    @{ */

  /**
   * Returns the definition of the mesh-point.
   * @param oMP
   *   The output definition of the mesh-point.
   */
  virtual HRESULT GetMeshPoint (CATPolyMeshPointDef& oMP) const = 0;

/** @} */

};

#endif // !CATIPolyMeshPoint_H
