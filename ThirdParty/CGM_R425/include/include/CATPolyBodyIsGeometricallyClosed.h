// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyIsGeometricallyClosed.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// 2008-12-22   NDO: New
// 2010-09-29   JXO: Optimizations
//===================================================================
#ifndef CATPolyBodyIsGeometricallyClosed_H
#define CATPolyBodyIsGeometricallyClosed_H

#include "PolyBodyTools.h"
#include "CATErrorDef.h"  // Definition of HRESULT.
#include "CATIAV5Level.h"
#include "CATechExt.h"
class CATPolyBody;
class CATIPolySurface;
class CATIPolyMesh;
class CATCompareFloatPoints;
class CATSetOfFloatPoints;
class CATMapOfPtrPtrToInt;
class littlesurfiterator;

#ifdef CATIAR418
class CATPolyBodyIsGeometricallyClosedObserver;
#endif //CATIAR418
/**
 * This operator checks if a CATPolyBody object is geometrically closed (and orientable) or not.
 * A CATPolyBody is geometrically closed if after the merge of all the vertices with the same positions
 * none of its facets has an open border.  The closure test for each facet border consists of summing up
 * the orientation of the border in all the adjacent facets.  Adjacent faces do not need to share the
 * same vertices along their common border but just the same vertex positions. 
 * This verification is purely geometrical.
 *
 * A comparaison function determines if two distinct vertices have the same position or not.  This function
 * is optional and by default, two vertices have the same positions if their coordinates are identical.
 */
class ExportedByPolyBodyTools CATPolyBodyIsGeometricallyClosed
{

public:

  /*
   * By default the comparison function is a lexicographic sort with strict equality between floats.
   * However, the comparaison function is customizable by derivation from CATCompareFloatPoints.
   */
  CATPolyBodyIsGeometricallyClosed (const CATCompareFloatPoints* iCompareFunction = 0);
  ~CATPolyBodyIsGeometricallyClosed ();

public: 

  // @param
  //   The polybody that is to be checked for watertightness.
  // @param oNbOpenBars
  //   An optional argument to count the number of bars that fail the closure test.
  // @return
  //   S_FALSE if the CATPolyBody is open.
  //   S_OK if the CATPolyBody is closed.
  //   E_FAIL on failure.
  HRESULT IsBodyClosed (const CATPolyBody& iPolyBody, int* opNbOpenBars = 0) const;

  // JXO 2010/08/12 to manage precisely lifecyle
  HRESULT ReleaseFaces();

protected:

  const CATCompareFloatPoints* _Compare;

  littlesurfiterator & _surfaces;

  HRESULT ProcessMesh (const CATIPolyMesh& iMesh, 
                       CATSetOfFloatPoints& points, CATMapOfPtrPtrToInt& multiplicities, int multiplicity) const;

  HRESULT ProcessSurface (const CATIPolySurface& iSurface, 
                          CATSetOfFloatPoints& points, CATMapOfPtrPtrToInt& multiplicities, int multiplicity) const;

#ifdef CATIAR418
// For Internal use
public:
  inline void SetObserver (CATPolyBodyIsGeometricallyClosedObserver* iObserver);
  inline CATPolyBodyIsGeometricallyClosedObserver* GetObserver () const;

protected:
  CATPolyBodyIsGeometricallyClosedObserver* _Observer;
  CATechExt *_Extension;
#endif //CATIAR418
};

#ifdef CATIAR418
inline void CATPolyBodyIsGeometricallyClosed::SetObserver (CATPolyBodyIsGeometricallyClosedObserver* iObserver)
{
  _Observer = iObserver;
}

inline CATPolyBodyIsGeometricallyClosedObserver* CATPolyBodyIsGeometricallyClosed::GetObserver () const
{
  return _Observer;
}
#endif //CATIAR418

#endif
