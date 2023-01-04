// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBVHSmartNode
//
//===================================================================
// 2009-09-11   JXO
//      * New
//===================================================================
#ifndef CATBVHSmartNode_H
#define CATBVHSmartNode_H

#include "CATErrorDef.h"
#include "CATBoolean.h"

#include "CATBVHNode.h"
#include "PolyBodyBVH.h"
#include "CATPolyPool.h"


#include "CATPolySetOfMutex.h"

// System
#include "CATMutex.h"

#include <atomic>

class CATPolyBVHAttribute;

/**
 * This class represents a smart node.
 * This is a node in a BVH tree (built with poly attributes) that can span itself
 * on demand. As soon as children are accessed the node will expand and split itself.
 * So the call to GetNbChildren or to the children iterator can be CPU costly.
 */
class ExportedByPolyBodyBVH CATBVHSmartNode: public CATBVHNode
{
  CATPolyDeclarePooledNew;

public:
  /**
   * Basic constructors and destructor
   */
  CATBVHSmartNode (int iMaxNbFacetsPerNode = -1, CATBoolean iMutexFree = FALSE, CATBoolean deleteIntermediateData = FALSE);
  CATBVHSmartNode (CATPolyBoundingVolume * pBV, CATBoolean iMutexFree = FALSE, CATBoolean deleteIntermediateData = FALSE);
  CATBVHSmartNode (const CATBVHSmartNode& iNode);

  virtual ~CATBVHSmartNode (); 

  /**
   * Sets the threshold number of triangles for splitting.
   * If this node owns less triangles than this threshold, 
   * it won't split itself.
   * Default value is -1: no split will ever be done.
   * A good value can be 100.
   */
  inline void SetMaxNbOfChildrenPerNode(int nb)
  {
    _MaxNbOfChildrenPerNode = nb;
  }
  /**
   * Returns the threshold number of triangles for splitting.
   */
  inline int GetMaxNbOfChildrenPerNode()
  {
    return _MaxNbOfChildrenPerNode;
  }
  /**
   * Momentary stops the expand of all smart nodes
   * @param iStop
   *    TRUE: stops expand
   *    FALSE: restart expand
   */
  static void StopExpand(CATBoolean iStop = TRUE);
  static CATBoolean IsStopped();

  /**
   * Smart Implementations:
   */
public:
  virtual int GetNbChildren () const;
  // collapses but does not flush polybodies
  virtual void ForceCollapse(int iCollapseMode = 0);
  // Note that smart nodes do not actually collapse their children.
  // Children are emptied (they only keep a list of triangle indices)
  virtual void FlushMemory();

  virtual BVHNodeType GetType(){return Smart;}

protected:
  virtual CATBVHNodeConstList & GetChildren();

protected:
  CATPolyBVHAttribute * _ParentPolyBodyAttribute;

  int _MaxNbOfChildrenPerNode;
  mutable int m_NbChildren;
  std::atomic<bool> m_childrenok;
  CATBoolean m_deleteIntermediateData;


  static CATBoolean _stopexpand;
  static CATMutex _mutStop;
  static CATPolySetOfMutex _mutExpand;


};

#endif
