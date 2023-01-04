//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolySurfaceVertex.h
//
//=============================================================================
// 2007-06-28   BPG: New
//=============================================================================
#ifndef CATPolySurfaceVertex_H
#define CATPolySurfaceVertex_H

#include "PolyMeshImpl.h"
#include "CATIPolySurfaceVertex.h"

#include "CATPolyMicroTopologyFwd.h"


class ExportedByPolyMeshImpl CATPolySurfaceVertex : public CATIPolySurfaceVertex
{

public:

  inline static CATPolySurfaceVertex* New (CATIPolySurface& iPolySurface, int v);

public:

  CATBoolean IsEditable () const;

  CATIPolySurface& GetSurface ();
  const CATIPolySurface& GetSurface () const;

  CATBoolean IsLyingOn (const CATIPolyCurve& c) const;
  CATBoolean IsLyingOn (const CATIPolySurface& s) const;

  const CATIPolyCurve* IsStartVertex () const;
  CATIPolyCurve* IsStartVertex ();

  const CATIPolyCurve* IsEndVertex () const;
  CATIPolyCurve* IsEndVertex ();

  int GetSurfaceVertexIndex () const;

public:

  HRESULT GetPosition (CATMathPoint& oP) const;
  HRESULT SetPosition (const CATMathPoint& iP);

  HRESULT GetSupport (CATIPolySupport*& oSupport) const;
  HRESULT SetSupport (CATIPolySupport* iSupport);

public:

  HRESULT RegisterObserver (CATIPolyPointObserver &iObserver);
  HRESULT UnregisterObserver (CATIPolyPointObserver &iObserver);

public:

  HRESULT Accept (const CATIPolyPoint& iPoint, CATPolyPointConstVisitor& iV) const;
  HRESULT Accept (CATIPolyPoint& iPoint, CATPolyPointVisitor& iV);

  CATIPolyPointConstTools* GetConstTools () const;
  CATIPolyPointTools* GetTools ();

public:

  inline int Get () const;

protected:

  int _Vertex;

  CATIPolySurface& _PolySurface;

  CATIPolyPointObserver* _Observer;
  CATIPolySupport* _Support;

protected:

  CATPolySurfaceVertex (CATIPolySurface& iPolySurface, int v);

  virtual ~CATPolySurfaceVertex ();

};

inline CATPolySurfaceVertex* CATPolySurfaceVertex::New (CATIPolySurface& iPolySurface, int v)
{
  return new CATPolySurfaceVertex (iPolySurface, v);
}

inline int CATPolySurfaceVertex::Get () const
{
  return _Vertex;
}

#endif // !CATPolySurfaceVertex_H
