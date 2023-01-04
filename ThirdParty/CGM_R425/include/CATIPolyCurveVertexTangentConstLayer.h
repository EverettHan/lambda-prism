//==================================================================-*- C++ -*-
// COPYRIGHT DASSAULT SYSTEMES 2010
//=============================================================================
//
// CATIPolyCurveVertexTangentConstLayer
//
//=============================================================================
// June 2010   NDO: New
//=============================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolyDoublesLayer.h"
#include "CATErrorDef.h"

class CATMathVector;


/**
* Interface to layer of curve vertex tangents
*/
class ExportedByPolyhedralAttributes CATIPolyCurveVertexTangentConstLayer : public CATIPolyDoublesLayer
{

public:

  unsigned int GetDimension () const { return 3; }

  virtual HRESULT Set (int v, const double* a) { return S_FALSE; }
  virtual HRESULT Get (int v, double* a) const;

public:

  /**
   * Return the tangent associated to a curve vertex.
   * @param iVertex
   *   A curve vertex.
   * @param oTangent
   *   The returned tangent.
   * @return
   *   S_OK on success or E_FAIL or another error otherwise.
   */
  virtual HRESULT Get (int iVertex, CATMathVector& oTangent) const = 0;

public:

  static const CATIPolyCurveVertexTangentConstLayer* Cast (const CATIPolyLayer*);
  static CATIPolyCurveVertexTangentConstLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

protected:

  CATIPolyCurveVertexTangentConstLayer () {}
  virtual ~CATIPolyCurveVertexTangentConstLayer () {}

};
