//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyMeshConsistentOrientationChecker.h
//
//=============================================================================
// 2007-07-25   BPG: New.
//=============================================================================
#ifndef CATPolyMeshConsistentOrientationChecker_H
#define CATPolyMeshConsistentOrientationChecker_H

#include "CATErrorDef.h"
#include "PolyMeshImpl.h"

class CATIPolyMesh;


/**
 * This mesh checker verifies that the orientation of the triangles around each bar
 * is consistent.  The sum of the triangle orientations around a bar (for all triangles 
 * adjacent to the bar) must be equal to 0 for all the bars.
 */
class ExportedByPolyMeshImpl CATPolyMeshConsistentOrientationChecker
{

public:

  inline CATPolyMeshConsistentOrientationChecker() {}

public:

  /**
   * Checks that a mesh has consistent triangle orientations and is manifold.
   * @return
   *   <ul>
   *     <li> S_OK The mesh passes this test.
   *     <li> S_FALSE The mesh fails this test.
   *     <li> E_FAIL A serious error occured during the check of the mesh.
   *   </ul>
   */
  HRESULT Check (const CATIPolyMesh &iMesh) const;

};

#endif // !CATPolyMeshConsistentOrientationChecker_H
