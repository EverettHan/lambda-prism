//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolySurfaceOrientedBarTangentLayerImpl
//
//=============================================================================
// 2008-06-23   BPG: New
//=============================================================================
#ifndef CATPolySurfaceOrientedBarTangentLayerImpl_H
#define CATPolySurfaceOrientedBarTangentLayerImpl_H

#include "CATIPolySurfaceOrientedBarTangentLayer.h"

#include "CATPolyBuckets_T.h"
#include "CATPolyIntIntRedBlackTree.h"

#include "CATMathVector.h"

//
class CATPolySurfaceOrientedBarTangentLayerImpl
  : public CATIPolySurfaceOrientedBarTangentLayer
{
public:
  CATPolySurfaceOrientedBarTangentLayerImpl();
  virtual ~CATPolySurfaceOrientedBarTangentLayerImpl();

public:
  virtual HRESULT Get(int v0, int v1, CATMathVector &oTangent) const;

public:
  virtual HRESULT Set(int v0, int v1, const CATMathVector &iTangent);

  virtual HRESULT Unset(int v0, int v1);

protected:
  int PushFront(int h,
                int v1, const CATMathVector &iTangent);

protected:
  struct BarTangent
  {
    int _SecondExtremity;
    CATMathVector _Tangent;

    int _Next;
  };
  class Specialize_CATPolyBuckets_T(BarTangentBuckets, BarTangent);

protected:
  CATPolyIntIntRedBlackTree _FirstVertex;
  BarTangentBuckets _BarTangents;
  int _FreeHead;
};

#endif // !CATPolySurfaceOrientedBarTangentLayerImpl_H
