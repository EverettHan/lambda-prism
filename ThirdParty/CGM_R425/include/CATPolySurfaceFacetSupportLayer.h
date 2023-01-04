// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceFacetSupportLayer.h
// Header definition of CATPolySurfaceFacetSupportLayer
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// March 2008 Creation: ndo
//===================================================================
#ifndef CATPolySurfaceFacetSupportLayer_H
#define CATPolySurfaceFacetSupportLayer_H

#include "PolyMeshImpl.h"
#include "CATPolyRefCounted.h"
#include "CATPolyBuckets_T.h"
#include "CATErrorDef.h"  // HRESULT

class CATIPolySurface;
class CATCGMOutput;


class ExportedByPolyMeshImpl CATPolySurfaceFacetSupportLayer : public CATPolyRefCounted
{

public:

  CATPolySurfaceFacetSupportLayer (const CATIPolySurface& iSurface);
  virtual ~CATPolySurfaceFacetSupportLayer() {}

public:

  /**
   * Set the key of the support of a facet.
   */
  HRESULT Set (const int iFacet, const int iKeySupport);

  /**
   * Get the key of the support of a facet.
   */
  HRESULT Get (const int iFacet, int& oKeySupport) const;

public:

  // For debugging purpose.
  void Print (CATCGMOutput& stream) const;

private:

  // Buckets of integers.
  class Specialize_CATPolyBuckets_T (FacetToKeySupportBuckets, int);

private:

  const CATIPolySurface& _Surface;

  // Map a facet to the key of its support.
  FacetToKeySupportBuckets _MapFacetToKeySupport;

};

#endif // !CATPolySurfaceFacetSupportLayer_H
