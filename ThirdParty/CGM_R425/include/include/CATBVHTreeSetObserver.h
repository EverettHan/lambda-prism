// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBVHTreeSetObserver.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Oct 2011 Creation: JXO
//===================================================================

#ifndef CATBVHTreeSetObserver_h
#define CATBVHTreeSetObserver_h

#include "BVHObjects.h"

// Math
#include "CATMathTransformation.h"

// PolyMathematics
#include "CATPolyObserver.h"
#include "CATPolyBoundingVolume.h"
#include "CATBVHTreeBuilder.h"
class CATBVHTree;
class CATBVHNode;
class CATBVHTreeSet;

// System
#include "CATErrorDef.h"
#include "CATSysBoolean.h"

/**
 *
 */
class ExportedByBVHObjects CATBVHTreeSetObserver : public CATPolyObserver<CATBVHTreeSetObserver>
{
public:


  /**
   * Constructor and destructor
   */
  CATBVHTreeSetObserver(){}
  virtual ~CATBVHTreeSetObserver(){}

  virtual HRESULT AddTree(int objectId, CATBVHTree * object, const CATMathTransformation * pos) = 0;
  virtual HRESULT ModifyTreePosition(int objectId, const CATMathTransformation * pos) = 0;
  virtual HRESULT DesactivateTree(int objectId) = 0;
  virtual HRESULT ActivateTree(int objectId) = 0;
  virtual HRESULT DeactivateAll() = 0;
  virtual HRESULT ActivateAll() = 0;
  virtual HRESULT RemoveTree(int objectId) = 0;
  // Actual removal of tree, always called by RemoveTree, RemovePolyBody or RemoveRep:
  virtual HRESULT PrepareToRemoveTree(int objectId) = 0;
  virtual HRESULT PrepareToFlushTree(int objectId) = 0;

  // If you don't know what this is... Should return -1!
  virtual int CheckPoint() = 0;

};

#endif /* CATPolyVisuInterfBVHTreeSet_h */
