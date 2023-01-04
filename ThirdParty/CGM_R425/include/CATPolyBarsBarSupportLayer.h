// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarsBarSupportLayer.h
// Header definition of CATPolyBarsBarSupportLayer
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// March 2008 Creation: ndo
//===================================================================
#ifndef CATPolyBarsBarSupportLayer_H
#define CATPolyBarsBarSupportLayer_H

#include "PolyMeshImpl.h"
#include "CATPolyRefCounted.h"
#include "CATPolyBuckets_T.h"
#include "CATErrorDef.h"  // HRESULT

class CATPolyBars;
class CATCGMOutput;


class ExportedByPolyMeshImpl CATPolyBarsBarSupportLayer : public CATPolyRefCounted
{

public:

  CATPolyBarsBarSupportLayer (const CATPolyBars& iBars);
  virtual ~CATPolyBarsBarSupportLayer() {}

public:

  /**
   * Set the key of the support of a bar.
   */
  HRESULT Set (const int iBar, const int iKeySupport);

  /**
   * Get the key of the support of a bar.
   */
  HRESULT Get (const int iBar, int& oKeySupport) const;

public:

  // For debugging purpose.
  void Print (CATCGMOutput& stream) const;

private:

  // Buckets of integers.
  class Specialize_CATPolyBuckets_T (BarToKeySupportBuckets, int);

protected:

  const CATPolyBars& _Bars;

  // Map a bar to the key of its support.
  BarToKeySupportBuckets _MapBarToKeySupport;

};

#endif // !CATPolyBarsBarSupportLayer_H
