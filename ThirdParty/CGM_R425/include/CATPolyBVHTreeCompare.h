//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATPolyBVHTreeCompare.h
//
//=============================================================================
// 2009-05-26   JXO
//      * New
// 2013-06-21   JXO
//      * CATTolerance for XScale compliance
// 2014-01-15   JXO
//      * Move from PolyhedralbodyOperators
//=============================================================================
#ifndef CATPolyBVHTreeCompare_H
#define CATPolyBVHTreeCompare_H

#include "PolyBodyBVH.h"

// BVH
class CATBVHNodeConst;
class CATBVHTree;
class CATPolyBoundingVolume;

// Math
class CATTolerance;

//------------------------------------------------------------------

/**
 * This class compares two trees and returns 1 as soon as one difference is found
 */
class ExportedByPolyBodyBVH CATPolyBVHTreeCompare
{
public:
  CATPolyBVHTreeCompare(const CATTolerance & iTol);
  virtual ~CATPolyBVHTreeCompare();

  int Compare(CATBVHTree & Tree1, CATBVHTree & Tree2);

protected:
  // To be re-implemented:
  virtual int CompareAttributes(CATBVHNodeConst & Node1, CATBVHNodeConst & Node2)
  {
    return 0;
  }

private:
  int Descent(CATBVHTree & Tree1, CATBVHTree & Tree2);
  int Descent(CATBVHNodeConst & Node1, CATBVHNodeConst & Node2);
  int CompareBV(const CATPolyBoundingVolume & BV1, const CATPolyBoundingVolume & BV2);

private:
  double _LTol;
  double _RTol;

};

#endif // !CATPolyBVHTreeCompare_H
