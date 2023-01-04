//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyPreAllocatedMesh.h
//
//=============================================================================
// 2007-04-19   BPG: New.
// November 2011   Revisited: NDO
// October 2014   JXO: Observers
// November 2015  NDO @see CATPolyCompactMesh
//=============================================================================
#ifndef CATPolyPreAllocatedMesh_H
#define CATPolyPreAllocatedMesh_H

#include "PolyMeshImpl.h"
#include "CATPolyCompactMesh.h"


/**
 * Do not use CATPolyPreAllocatedMesh.  
 * Replace by CATPolyCompactMesh which implements the same interface.
 *
 * @see CATPolyCompactMesh
 */
class ExportedByPolyMeshImpl CATPolyPreAllocatedMesh : public CATPolyCompactMesh
{

public:

/** @name Life Cycle
    @{ */

  /** 
   * @nodoc
   */
  POLY_DEPRECATED ("Do not use CATPolyPreAllocatedMesh.  Replace by CATPolyCompactMesh.",
  static CATPolyPreAllocatedMesh* New (const CATIPolyMesh& iMesh));

  /** 
   * @nodoc
   */
  POLY_DEPRECATED ("Do not use CATPolyPreAllocatedMesh.  Replace by CATPolyCompactMesh.",
  static CATPolyPreAllocatedMesh* New (int iNbVerticesToAllocate, int iNbTrianglesToAllocate,
                                       CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer));

  // DEPRECATED.
  POLY_DEPRECATED ("Do not use CATPolyPreAllocatedMesh.  Replace by CATPolyCompactMesh.",
  static CATPolyPreAllocatedMesh* New (int iNbVerticesToAllocate, int iNbTrianglesToAllocate,
                                       CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer, CATBoolean));

  virtual ~CATPolyPreAllocatedMesh ();

/** @} */

public:

/** @name Casting Methods.
    @{ */

  /**
   * @nodoc
   */
  POLY_DEPRECATED ("Do not use CATPolyPreAllocatedMesh.  Replace by CATPolyCompactMesh.",
  static const CATPolyPreAllocatedMesh* Cast (const CATIPolySurface* iSurface));

  /**
   * @nodoc
   */
  POLY_DEPRECATED ("Do not use CATPolyPreAllocatedMesh.  Replace by CATPolyCompactMesh.",
  static CATPolyPreAllocatedMesh* Cast (CATIPolySurface* iSurface));

/** @} */

private:

  // Private constructor.
  CATPolyPreAllocatedMesh (PolyPrecision iFD);

  friend class CATPolyCompactMesh;

};

#endif // #ifndef CATPolyPreAllocatedMesh_H
