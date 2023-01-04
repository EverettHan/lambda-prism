//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016
//=============================================================================
//
// CATPolyBodyBoundingEdgesCheckerObserver
//
// Check that surfaces have their bounding edges
//
//=============================================================================
// 2016-05-12 JXO: New.
//=============================================================================
#ifndef CATPolyBodyBoundingEdgesCheckerObserver_H
#define CATPolyBodyBoundingEdgesCheckerObserver_H

#include "PolyBodyTools.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATPolyRefCounted.h"

class CATPolyFace;

/**
 *
 */
class ExportedByPolyBodyTools CATPolyBodyBoundingEdgesCheckerObserver : public CATPolyRefCounted
{
public:
  virtual void AddFreeBar(const CATPolyFace& iFace, int v1, int v2) = 0;

protected:
  CATPolyBodyBoundingEdgesCheckerObserver ();
  ~CATPolyBodyBoundingEdgesCheckerObserver ();

};

#endif // !CATPolyBodyBoundingEdgesCheckerObserver_H
