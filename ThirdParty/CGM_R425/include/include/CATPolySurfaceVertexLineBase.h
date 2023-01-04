// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVertexLineBase.h
//
//===================================================================
// September 2013  Creation: NDO
//===================================================================
#ifndef CATPolySurfaceVertexLineBase_H
#define CATPolySurfaceVertexLineBase_H

#include "PolyhedralModel.h"
#include "CATIPolySurfaceVertexLine.h"


/**
Class providing a default implementation to an editable CATIPolySurfaceVertexLine.
All (editable) CATIPolySurfaceVertexLine implementations can derive from this class.
All virtual methods should be implemented in a derived class unless otherwise noted.
@see CATPolySurfaceVertexLineBaseConst
*/
class ExportedByPolyhedralModel CATPolySurfaceVertexLineBase : public CATIPolySurfaceVertexLine
{

public:

  CATPolySurfaceVertexLineBase () {}
  virtual ~CATPolySurfaceVertexLineBase ();

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual CATIPolySurface& GetSurface () = 0;
  virtual const CATIPolySurface& GetSurface () const = 0;

  virtual CATBoolean IsLyingOn (const CATIPolySurface &s) const;

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT AppendSurfaceVertex (int sv, int& v);
  virtual HRESULT InsertSurfaceVertex (int sv, int vn, int& v);

  virtual int GetSurfaceVertex (int v) const;

  virtual HRESULT FindBar (int sv0, int sv1, int& v0, int& v1) const;

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT AppendVertex (int &v);

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

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionLayer *&oLayer);
  virtual HRESULT GetVertexTangentLayer(CATIPolyCurveVertexTangentLayer *&oLayer);
  virtual HRESULT GetVertexWLayer(CATIPolyCurveVertexWLayer *&oLayer);

  virtual HRESULT SetSupport (CATIPolySupport* iSupport);

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

  virtual HRESULT SplitBar (const int v0, const int v1, int &n);
  virtual HRESULT SplitBarWithSurfaceVertex (int v0, int v1, int iSurfaceVertex, int& v);
  virtual HRESULT MergeVertices (const int v0, const int v1);
  virtual HRESULT MergeVerticesSVL (const int v0, const int v1);
  virtual HRESULT ReactToSetVertexPosition (int cv, const CATMathPoint& P);

  virtual HRESULT Close ();
  virtual HRESULT Open ();

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT RegisterObserver (CATIPolyCurveObserver &iObserver);
  virtual HRESULT UnregisterObserver (CATIPolyCurveObserver &iObserver);

/** @} */

public:

/** @name Virtual methods to be overriden in a derived class.
    @{ */

  virtual HRESULT Accept (const CATIPolyCurve& iCurve, CATPolyCurveConstVisitor& iV) const;
  virtual HRESULT Accept (CATIPolyCurve& iCurve, CATPolyCurveVisitor& iV);

/** @} */

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

/** @name Methods returning S_FALSE or E_FAIL if called.
    Do not override these methods.  Should not be calling these methods.
    @{ */

  HRESULT AppendVertex (const CATMathPoint &P, int &v);

  HRESULT GetVertexPosition (const int iIdxVertex, CATMathPoint &oPoint) const;
  HRESULT SetVertexPosition (const int v, const CATMathPoint &P);

  int GetNbBars () const;
  HRESULT GetBar (const int iIdxBar, int oIdxVertices[]) const;

/** @} */

};

#endif // !CATPolySurfaceVertexLineBase_H
