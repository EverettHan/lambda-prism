// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVertexLineBaseConst.h
//
//===================================================================
// June 2010  Creation: NDO
//===================================================================
#ifndef CATPolySurfaceVertexLineBaseConst_H
#define CATPolySurfaceVertexLineBaseConst_H

#include "PolyhedralModel.h"
#include "CATIPolySurfaceVertexLine.h"


/**
Class providing a default implementation to a non-editable CATIPolySurfaceVertexLine.
All CATIPolySurfaceVertexLine adapter or read-only implementation can derive from this class.
All virtual methods should be implemented in a derived class unless otherwise noted.
*/
class ExportedByPolyhedralModel CATPolySurfaceVertexLineBaseConst : public CATIPolySurfaceVertexLine
{

public:

  CATPolySurfaceVertexLineBaseConst () {}
  virtual ~CATPolySurfaceVertexLineBaseConst ();

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual CATIPolySurface& GetSurface () = 0;
  virtual const CATIPolySurface& GetSurface () const = 0;

  virtual int GetSurfaceVertex (int w) const;

  virtual HRESULT FindBar (int sv0, int sv1, int& v0, int& v1) const;

  virtual CATBoolean IsLyingOn (const CATIPolySurface &s) const;

/** @} */

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
  virtual HRESULT GetVertexWLayer(CATIPolyCurveVertexWConstLayer *&oLayer) const;

  virtual HRESULT GetSupport (CATIPolySupport*& oSupport) const;

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

/** @name Methods implemented in this class. There is no need to override these methods.
    @{ */

  CATIPolySurfaceVertexLine* CastToSurfaceVertexLine ();
  const CATIPolySurfaceVertexLine* CastToSurfaceVertexLine () const;

  CATBoolean IsEditable () const;

/** @} */

public:

/** @name Methods returning S_FALSE if called.
    Do not override these methods.
    @{ */

  HRESULT AppendVertex (int &v);

  HRESULT AppendSurfaceVertex (int sv, int& v);
  HRESULT InsertSurfaceVertex (int sv, int vn, int& v);

  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionLayer *&oLayer);
  HRESULT GetVertexTangentLayer(CATIPolyCurveVertexTangentLayer *&oLayer);
  HRESULT GetVertexWLayer(CATIPolyCurveVertexWLayer *&oLayer);

  HRESULT SetSupport (CATIPolySupport* iSupport);

  HRESULT SplitBar (const int v0, const int v1, int &n);
  HRESULT SplitBarWithSurfaceVertex (int v0, int v1, int iSurfaceVertex, int& v);
  HRESULT MergeVertices (const int v0, const int v1);
  HRESULT MergeVerticesSVL (const int v0, const int v1);
  virtual HRESULT ReactToSetVertexPosition (int cv, const CATMathPoint& P);

  HRESULT Close ();
  HRESULT Open ();

  HRESULT Accept (CATIPolyCurve& iCurve, CATPolyCurveVisitor& iV);

/** @} */

public:

/** @name Methods returning S_FALSE if called.
    Do not override these methods.
    @{ */

  HRESULT RegisterObserver (CATIPolyCurveObserver &iObserver);
  HRESULT UnregisterObserver (CATIPolyCurveObserver &iObserver);

/** @} */

public:

/** @name Deprecated methods returning E_FAIL if called.
    Do not use this method.  (Shouldn't be calling these methods.)
    @{ */

  HRESULT AppendVertex (const CATMathPoint &P, int &v);

  virtual HRESULT GetVertexPosition (const int iIdxVertex, CATMathPoint &oPoint) const;
  HRESULT SetVertexPosition (const int v, const CATMathPoint &P);

  int GetNbBars () const;
  HRESULT GetBar (const int iIdxBar, int oIdxVertices[2]) const;

/** @} */

};

#endif // !CATPolySurfaceVertexLineBaseConst_H
