// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBVHPickingCallback
//
//===================================================================
//
// July 2009  Creation: NDO
//===================================================================
#ifndef CATBVHPickingCallback_H
#define CATBVHPickingCallback_H

#include "BVHOperators.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

class CATBVHNode;


/**
 * This class encapsulates the callbacks made during picking.
 */
class ExportedByBVHOperators CATBVHPickingCallback
{

public:

  virtual ~CATBVHPickingCallback () {}

public:

  /*
   * Virtual method called before a node is tested by CATBVHPickingOperator.
   * If the method returns TRUE, then the node is tested.
   * If the method returns FALSE, then the node and all its descendants are skipped.
   */
  virtual CATBoolean Filter (CATBVHNode& iBVHNode) = 0;

  /*
   * Virtual method called when a node intersects the picking ray by CATBVHPickingOperator.
   * If the method returns S_OK, then the picking operator proceeds with the children of the node.
   * If the method returns S_FALSE, then the picking operator skips the children of the node.
   * If the method returns an error, E_FAIL or any other error, then the operator stops its span
   * of the tree.
   */
  virtual HRESULT Intersect (CATBVHNode& iBVHNode) = 0;

  /*
   * When this method is called by CATBVHPickingOperator and returns TRUE, then the operator stops 
   * the span of the tree.
   */
  virtual CATBoolean Cancel () const = 0;

};


#endif // !CATBVHPickingCallback_H
