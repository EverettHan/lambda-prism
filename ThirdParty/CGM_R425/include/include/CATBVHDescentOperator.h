// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBVHDescentOperator
//
//===================================================================
//
// July 2009  Creation: NDO
// Aug  2009  Migration: JXO
//===================================================================
#ifndef CATBVHDescentOperator_H
#define CATBVHDescentOperator_H

#include "BVHOperators.h"
#include "CATErrorDef.h"
#include "CATSysBoolean.h"

class CATBVHNodeConst;
class CATBVHTree;


/**
 * This class makes tree traversals easier.
 * Any Operator on BVHTree can derive from this class and re-implement
 * virtual methods.
 */
class ExportedByBVHOperators CATBVHDescentOperator
{

public:
  CATBVHDescentOperator();
  virtual ~CATBVHDescentOperator(){}

  /**
   * Travels into one tree.
   */
  HRESULT Descend(CATBVHTree& iBVHTree);

  /**
   * Travels into two trees.
   */
  HRESULT Descend(CATBVHTree& iBVHTree1, CATBVHTree& iBVHTree2);


protected:

  /*
   * Virtual method called before ONE node is processed by the operator
   * If the method returns TRUE, then the node is processed.
   * If the method returns FALSE, then the node and all its descendants are skipped.
   */
  virtual CATBoolean Filter(CATBVHNodeConst& iBVHNode)
  {
    return TRUE;
  }

  /*
   * Virtual method called when ONE terminal node needs to be processed.
   * If the method returns S_OK, then the operator proceeds with rest of the tree.
   * If the method returns an error, E_FAIL or any other error, then the operator stops its span
   * of the tree.
   */
  virtual HRESULT ProcessLeafNode(CATBVHNodeConst& iBVHNode)
  {
    return S_OK;
  }

  /*
   * When this method is called and returns TRUE, then the operator stops 
   * the span of the tree. Used for unary and binary descent.
   */
  virtual CATBoolean Cancel() const
  {
    return FALSE;
  }

  /*
   * Virtual method called before TWO nodes are processed by the binary operator
   * If the method returns TRUE, then the nodes are processed.
   * If the method returns FALSE, then the nodes and all their descendants are skipped.
   */
  virtual CATBoolean Filter(CATBVHNodeConst& iBVHNode1, CATBVHNodeConst& iBVHNode2)
  {
    return TRUE;
  }

  /*
   * Virtual method called when TWO terminal nodes need to be processed.
   * If the method returns S_OK, then the operator proceeds with rest of the trees.
   * If the method returns an error, E_FAIL or any other error, then the operator stops its span
   * of the trees.
   */
  virtual HRESULT ProcessLeafNodes(CATBVHNodeConst& iBVHNode1, CATBVHNodeConst& iBVHNode2)
  {
    return S_OK;
  }

  /**
   * Called to choose between iBVHNode1 or iBVHNode2 when both nodes have children
   *    0: N1xN2 traversal
   *    1: iBVHNode1 first
   *    2: iBVHNode2 first
   */
  virtual int Choose(CATBVHNodeConst& iBVHNode1, CATBVHNodeConst& iBVHNode2)
  {
    return 0;
  }

  /**
   * Called after traversal of children and after ProcessLeafNodes
   */
  virtual void End(CATBVHNodeConst& iBVHNode1, CATBVHNodeConst& iBVHNode2){}




protected:

  /**
   * Recursive method called by the tree descent.
   */
  HRESULT Descend(CATBVHNodeConst& iBVHNode);

  /**
   * Recursive method called by the tree descent.
   */
  HRESULT Descend(CATBVHNodeConst& iBVHNode1, CATBVHNodeConst& iBVHNode2);

protected:
  /**
   * Usefull data
   * Tree depth during traversal
   */
  int _level;
  int _level1;
  int _level2;

};


#endif // !CATBVHDescentOperator_H
