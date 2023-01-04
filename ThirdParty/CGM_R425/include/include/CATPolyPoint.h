//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyPoint.h
//
//=============================================================================
// 2007-03-15   BPG: New
//=============================================================================
#ifndef CATPolyPoint_H
#define CATPolyPoint_H

#include "CATIPolyPoint.h"
#include "CATMathPoint.h"
#include "PolyMeshImpl.h"


class ExportedByPolyMeshImpl CATPolyPoint : public CATIPolyPoint
{

public:

  /**
   * Creates an instance of a CATPolyPoint.
   * The position of a CATPolyPoint is in double precision.
   */
  static CATPolyPoint* New ();

  /**
   * Creates an instance of a CATPolyPoint.
   * The position of a CATPolyPoint is in double precision.
   */
  static CATPolyPoint* New (const CATMathPoint& P);

public:

  CATIPolyCurveVertex* CastToCurveVertex ();
  const CATIPolyCurveVertex* CastToCurveVertex () const;

  CATIPolySurfaceVertex* CastToSurfaceVertex ();
  const CATIPolySurfaceVertex* CastToSurfaceVertex () const;

public:

  CATBoolean IsEditable () const;

  virtual CATBoolean IsLyingOn (const CATIPolyCurve &c) const;

  virtual const CATIPolyCurve *IsStartVertex() const;
  virtual CATIPolyCurve *IsStartVertex();

  virtual const CATIPolyCurve *IsEndVertex() const;
  virtual CATIPolyCurve *IsEndVertex();

public:

  virtual CATBoolean IsLyingOn(const CATIPolySurface &s) const;

public:

  virtual HRESULT GetPosition(CATMathPoint &P) const;
  virtual HRESULT SetPosition(const CATMathPoint &P);

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

public:

  // 
  // Public methods that are not visible through the interface.
  // Reserved for visitors.
  //

  // Return the native point support.  Do not delete the support that is returned.
  inline CATIPolySupport* GetNativeSupport () const;

private:

  // Copy constructor/operator shall not be implemented
  CATPolyPoint(const CATPolyPoint &iRHS);
  CATPolyPoint& operator=(const CATPolyPoint &iRHS);

protected:

  CATMathPoint _P;

  CATIPolyPointObserver *_Observer;
  CATIPolySupport* _Support;

public:  // Should be protected.

  CATPolyPoint ();
  CATPolyPoint (const CATMathPoint &P);
  virtual ~CATPolyPoint ();

};


inline CATIPolySupport* CATPolyPoint::GetNativeSupport () const
{
  return _Support;
}

#endif // !CATPolyPoint_H
