// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshOBBSpliter
//
//===================================================================
// 2009-08-31   JXO
//      * New
//===================================================================
#ifndef CATPolyMeshOBBSpliter_H
#define CATPolyMeshOBBSpliter_H

#include "PolyBodyBVH.h"

// System
#include "CATErrorDef.h"

//Math
class CATPolyOBB;
class CATIPolyMesh;

// Polyhedral
class CATIPolySurfaceIterator;


/**
 * Several functions sued to split a mesh.
 */
class ExportedByPolyBodyBVH CATPolyMeshOBBSpliter 
{

public:

  CATPolyMeshOBBSpliter();
  ~CATPolyMeshOBBSpliter();

public:

  /**
   * Split the surface into several sub surfaces. The created subSurfaces
   * define a partition of the splited surface. The decompostion requires
   * the OBB of the surface. If not already computed, you might use the above
   * GetOBB method.
   * @param iOrigMesh mesh to split.
   * @param iSurfaceOBB OBB of the surface. As usual the tighter the OBB, the better
   *                   the result.
   * @param iNaxNbSplit if >= 1 define the maximum number of subsurfaces to create,
   *                    otherwise the number of split is automatic.
   * @param oSplitedSurfaces resulting subsurfaces, must be deleted afterwards.
   * @return S_OK if the split was successfull, E_INVALIDARG if the surface kind
   *         does not allow split, S_FALSE if the surface kind is OK but the algorithm
   *         did not manage to split it, E_FAIL if something wrong and unexpected happened.
   */
  static HRESULT OBBSplit(CATIPolyMesh & iOrigMesh, const CATPolyOBB & iMeshOBB, int maxNbSplit,
                          CATIPolySurfaceIterator *& oSplitedSurfaces);

  /**
   * Split the surface into several sub surfaces. The created subSurfaces
   * define a partition of the splited surface. This function does not
   * require an OBB as a parameter. However, the OBB will be computed during
   * the computation, and then increase computation time.
   * If not already computed, you might use the above
   * GetOBB method.
   * @param iOrigMesh mesh to split.
   * @param iNaxNbSplit if >= 1 define the maximum number of subsurfaces to create,
   *                    otherwise the number of split is automatic.
   * @param oSplitedSurfaces resulting subsurfaces, must be deleted afterwards.
   * @return S_OK if the split was successfull, E_INVALIDARG if the surface kind
   *         does not allow split, S_FALSE if the surface kind is OK but the algorithm
   *         did not manage to split it, E_FAIL if something wrong and unexpected happened.
   */
  static HRESULT OBBSplit(CATIPolyMesh & iOrigMesh, int maxNbSplit,
                          CATIPolySurfaceIterator *& oSplitedSurfaces);


  /**
   * Split the surface into several sub surfaces. The created subSurfaces
   * define a partition of the splited surface. This function does not
   * require an OBB as a parameter. However, the OBB will be computed during
   * the computation, and then increase computation time.
   * If not already computed, you might use the above
   * GetOBB method.
   * @param iOrigMesh mesh to split.
   * @param iNaxNbSplit if >= 1 define the maximum number of subsurfaces to create,
   *                    otherwise the number of split is automatic.
   * @param obbInflateFactor inflate value to be used for inflating the OBB.
   *                         To be used in order to get the same result with the first form of
   *                         OBBSplit if the given OBB has been inflated prior to the computation.
   * @param oSplitedSurfaces resulting subsurfaces, must be deleted afterwards.
   * @return S_OK if the split was successfull, E_INVALIDARG if the surface kind
   *         does not allow split, S_FALSE if the surface kind is OK but the algorithm
   *         did not manage to split it, E_FAIL if something wrong and unexpected happened.
   */
  static HRESULT OBBSplit(CATIPolyMesh & iOrigMesh, int maxNbSplit, double obbInflateValue,
                          CATIPolySurfaceIterator *& oSplitedSurfaces);
};

#endif
