//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyCurveVertex.h
//
//=============================================================================
// 2007-03-22   BPG: New
//=============================================================================
#ifndef CATPolyCurveVertex_H
#define CATPolyCurveVertex_H

#include "PolyMeshImpl.h"
#include "CATIPolyCurveVertex.h"

#include "CATPolyMicroTopologyFwd.h"
#include "CATIPolyCurve.h"

class ExportedByPolyMeshImpl CATPolyCurveVertex : public CATIPolyCurveVertex
{

public:

  inline static CATPolyCurveVertex* New (CATIPolyCurve& iPolyCurve, int v);

public:

  CATBoolean IsEditable () const;

  virtual CATBoolean IsLyingOn(const CATIPolyCurve &c) const;

  virtual const CATIPolyCurve *IsStartVertex() const;
  virtual CATIPolyCurve *IsStartVertex();

  virtual const CATIPolyCurve *IsEndVertex() const;
  virtual CATIPolyCurve *IsEndVertex();

  virtual CATBoolean IsLyingOn(const CATIPolySurface &s) const;

public:

  virtual HRESULT GetPosition(CATMathPoint &oP) const;
  virtual HRESULT SetPosition(const CATMathPoint &iP);

public:

  inline CATIPolyCurve &GetCurve();
  inline const CATIPolyCurve &GetCurve() const;

  inline int GetCurveVertexIndex() const;

public:

  virtual HRESULT SetSupport (CATIPolySupport* iSupport);
  virtual HRESULT GetSupport (CATIPolySupport*& oSupport) const;

public:

  HRESULT RegisterObserver (CATIPolyPointObserver &iObserver);
  HRESULT UnregisterObserver (CATIPolyPointObserver &iObserver);

public:

  HRESULT Accept (const CATIPolyPoint& iPoint, CATPolyPointConstVisitor& iV) const;
  HRESULT Accept (CATIPolyPoint& iPoint, CATPolyPointVisitor& iV);

  CATIPolyPointConstTools* GetConstTools () const;
  CATIPolyPointTools* GetTools ();

protected:

  CATIPolyCurve &_Curve;
  int _w;

  CATIPolyPointObserver* _Observer;
  CATIPolySupport* _Support;

public:  // Should be protected.
//protected:

  CATPolyCurveVertex (CATIPolyCurve &iCurve, int w);
  virtual ~CATPolyCurveVertex();

};

inline CATPolyCurveVertex* CATPolyCurveVertex::New (CATIPolyCurve& iPolyCurve, int v)
{
  if(0 == v)
    return 0;
  if((!iPolyCurve.GetPrevVertex(v)) && (!iPolyCurve.GetNextVertex(v)))
    return 0;
  return new CATPolyCurveVertex (iPolyCurve, v);
}

inline CATIPolyCurve& CATPolyCurveVertex::GetCurve()
{
  return _Curve;
}

inline const CATIPolyCurve& CATPolyCurveVertex::GetCurve() const
{
  return _Curve;
}

inline int CATPolyCurveVertex::GetCurveVertexIndex () const
{
  return _w;
}

#endif // !CATPolyCurveVertex_H
