// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATBVHTree
//
//=============================================================================
// 2015-03-04   JXO
//      * New
//=============================================================================
#ifndef CATBVHTreeObserver_H
#define CATBVHTreeObserver_H

#include "BVHObjects.h"
#include "CATPolyObserver.h"


/**
 * Bounding volume hierarchies are defined by a tree.
 * Observer on top of CATBVHTree
 */
class ExportedByBVHObjects CATBVHTreeObserver : public CATPolyObserver<CATBVHTreeObserver>
{
public:
  CATBVHTreeObserver();
  ~CATBVHTreeObserver();

  virtual void PrepareToDeleteTree() = 0;
  virtual void PrepareToFlushMemory() = 0;
};

#endif

