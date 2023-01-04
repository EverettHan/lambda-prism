//==================================================================-*- C++ -*-
// COPYRIGHT DASSAULT SYSTEMES 2010
//=============================================================================
//
// CATIPolyCurveVertexWConstLayer
//
//=============================================================================
// June 2010   NDO: New
//=============================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolyDoublesLayer.h"
#include "CATErrorDef.h"


/**
* Interface to layer of curve vertex w parameter.
*/
class ExportedByPolyhedralAttributes CATIPolyCurveVertexWConstLayer : public CATIPolyDoublesLayer
{

public:

  unsigned int GetDimension () const { return 1; }

  virtual HRESULT Set (int v, const double* a) { return S_FALSE; }
  virtual HRESULT Get (int v, double* a) const;

public:

  /**
   * Return the w parameter associated to a curve vertex.
   * @param iVertex
   *   A curve vertex.
   * @param w
   *   The returned parameter.
   * @return
   *   S_OK on success or E_FAIL or another error otherwise.
   */
  virtual HRESULT Get(int iVertex, double &w) const = 0;

public:

  static const CATIPolyCurveVertexWConstLayer* Cast (const CATIPolyLayer*);
  static CATIPolyCurveVertexWConstLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

protected:

  CATIPolyCurveVertexWConstLayer () {}
  virtual ~CATIPolyCurveVertexWConstLayer () {}

};
