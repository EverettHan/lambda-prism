//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATIPolySurfaceOrientedBarTangentLayer
//
//=============================================================================
// 2008-06-23   BPG: New
//=============================================================================
#ifndef CATIPolySurfaceOrientedBarTangentLayer_H
#define CATIPolySurfaceOrientedBarTangentLayer_H

#include "PolyhedralAttributes.h"
#include "CATIPolySurfaceOrientedBarTangentConstLayer.h"
#include "CATErrorDef.h"


class ExportedByPolyhedralAttributes CATIPolySurfaceOrientedBarTangentLayer : public CATIPolySurfaceOrientedBarTangentConstLayer
{

public:

  /**
   * @return 
   *   S_OK on success.
   */
  virtual HRESULT Set(int v0, int v1, const CATMathVector &iTangent) = 0;

  /**
   * @return
   *   S_OK on success.
   */
  virtual HRESULT Unset(int v0, int v1) = 0;

public:

  /**
   * Casts as a non-const layer.
   */
  CATIPolySurfaceOrientedBarTangentLayer* NonConstCast ();

protected:

  virtual ~CATIPolySurfaceOrientedBarTangentLayer () {}

};

#endif // !CATIPolySurfaceOrientedBarTangentLayer_H
