// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATBVHPickingOperator
//
//=============================================================================
// 2009-04-28   JXO
//      * New
//=============================================================================
#ifndef CATBVHPickingOperator_H
#define CATBVHPickingOperator_H

#include "BVHOperators.h"
#include "CATErrorDef.h"

class CATBVHTree;
class CATBVHPickingCallback;
class CATMathPoint;
class CATMathVector;


/**
 * The BVH picking operator is a accelerator for high-level operators. For instance, this operator can be used
 * to accelerate picking CATCell's from a CATBody; when the number of cells is large, picking can be greatly 
 * accelerated by a data structure that optimizes the spatial distribution of the cells like a CATBVHTree.
 * 
 * To construct an instance of a CATBVHPickingOperator, two objects are needed.  The first is an object that
 * encapsulates callbacks.  These callbacks are made while nodes of a tree are being picked.  The second is 
 * the radius of the aperture or equivalently of the picking ray.  The ray is assumed to be cylindrical.
 */
class ExportedByBVHOperators CATBVHPickingOperator
{

public:

  /*
   * Construct a CATBVHPickingOperator.
   * @param iCallback
   *   This input argument provides two virtual functions Filter () an Intersect ().
   *   Filter is called systematically before a node is tested.  Intersect is called when there
   *   is an intersection of the ray with one of the bounding volumes of the node.
   */
  CATBVHPickingOperator (CATBVHPickingCallback& iCallback, const double iRadiusAperture);

  ~CATBVHPickingOperator ();

public:

  /*
   * Run the picking operator on a BVH tree.
   * The operator spans the tree from top to bottom and makes a callback for every node whose bounding 
   * volumes intersect the input ray.  A first call to the CATBVHPickingCallback::Filter () method 
   * is made before testing whether the ray intersects the bounding volumes associated to the visited node.  
   * If the method returns TRUE, the test proceeds and if the method returns FALSE the node and all its 
   * children are skipped.  If the ray intersects one of the bounding volumes, then the method proceeds with
   * the children of the node iteratively after a call to the CATBVHPickingCallback::Intersect () method.
   * @param iBVHTree
   *   The tree to be tested by the picking operator.
   * @param iRayOrigin
   *   The origin of the ray for picking.
   * @param i
   * @return
   *   S_OK upon a successful span of the tree.
   *   Otherwise, the method returns an error.
   */
  HRESULT Run (const CATBVHTree& iBVHTree, const CATMathPoint& iRayOrigin, const CATMathVector& iRayDirection);

private:

  CATBVHPickingCallback& _Callback;

  double _Aperture;  // The radius of the picking ray.

};


#endif // !CATBVHPickingOperator_H
