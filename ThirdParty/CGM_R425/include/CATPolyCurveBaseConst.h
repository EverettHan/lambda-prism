// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCurveBaseConst.h
//
//===================================================================
//
// June 2010  Creation: NDO
//===================================================================
#ifndef CATPolyCurveBaseConst_H
#define CATPolyCurveBaseConst_H

#include "PolyhedralModel.h"
#include "CATIPolyCurve.h"


/**
Class providing a default implementation to a non-editable CATIPolyCurve.
All CATIPolyCurve adapter or read-only implementation can derive from this class.
All virtual methods should be implemented in a derived class unless otherwise noted.
*/
class ExportedByPolyhedralModel CATPolyCurveBaseConst : public CATIPolyCurve
{

public:

  CATPolyCurveBaseConst () {}
  virtual ~CATPolyCurveBaseConst ();

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual int GetNbVertices () const;

  virtual int GetStartVertex () const;
  virtual int GetEndVertex () const;

  virtual int GetNextVertex (int v) const;
  virtual int GetPrevVertex (int v) const;

  virtual CATBoolean IsClosed () const;

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT GetVertexIterator (CATIPolyCurveVertexIterator *&oIterator) const;

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionConstLayer *&oLayer) const;
  virtual HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentConstLayer *&oLayer) const;
  virtual HRESULT GetVertexWLayer (CATIPolyCurveVertexWConstLayer *&oLayer) const;

  virtual HRESULT GetSupport (CATIPolySupport*& oSupport) const;

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT Accept (const CATIPolyCurve& iCurve, CATPolyCurveConstVisitor& iV) const;

/** @} */

public:

  virtual HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolyCurveObserver* obs = 0);

  virtual HRESULT RemoveLayer (CATIPolyLayer& iLayer);

  virtual HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  virtual bool HasLayer (const CLSID& id) const;

  virtual HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  virtual HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual CATIPolyCurveConstTools* GetConstTools () const;
  virtual CATIPolyCurveTools* GetTools ();

/** @} */

public:

/** @name Methods implemented in this class.
    No need to override these methods.
    @{ */

  CATIPolySurfaceVertexLine* CastToSurfaceVertexLine ();
  const CATIPolySurfaceVertexLine* CastToSurfaceVertexLine () const;

  const CATIPolyMeshCurve* CastToMeshCurve () const;
  CATIPolyMeshCurve* CastToMeshCurve ();

  virtual CATBoolean IsLyingOn (const CATIPolySurface &s) const;

  CATBoolean IsEditable () const;

/** @} */

public:

/** @name Deprecated methods returning E_FAIL if called.
    Do not use this method.  (Shouldn't be using this method.)
    @{ */

  virtual HRESULT GetVertexPosition (const int iIdxVertex, CATMathPoint &oPoint) const;

/** @} */

public:

/** @name Methods returning E_FAIL if called.
    Do not override these methods.
    @{ */

  HRESULT AppendVertex (int &v);
  HRESULT AppendVertex (const CATMathPoint &P, int &v);

  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionLayer *&oLayer);
  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentLayer *&oLayer);
  HRESULT GetVertexWLayer (CATIPolyCurveVertexWLayer *&oLayer);

  HRESULT SetSupport (CATIPolySupport* iSupport);

  HRESULT SetVertexPosition (const int v, const CATMathPoint &P);

  HRESULT SplitBar (const int v0, const int v1, int &n);
  HRESULT MergeVertices (const int v0, const int v1);

  HRESULT Close ();
  HRESULT Open ();

  HRESULT RegisterObserver (CATIPolyCurveObserver &iObserver);
  HRESULT UnregisterObserver (CATIPolyCurveObserver &iObserver);

  HRESULT Accept (CATIPolyCurve& iCurve, CATPolyCurveVisitor& iV);

/** @} */

};

#endif // !CATPolyCurveBaseConst_H
