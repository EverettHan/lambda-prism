// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyPointBaseConst.h
//
//===================================================================
// October 2013  Creation: NDO
//===================================================================
#ifndef CATPolyPointBaseConst_H
#define CATPolyPointBaseConst_H

#include "PolyhedralModel.h"
#include "CATIPolyPoint.h"


/**
Class providing a default implementation to a non-editable CATIPolyPoint.
All CATIPolyPoint adapter or read-only implementation can derive from this class.
All virtual methods should be implemented in a derived class unless otherwise noted.
*/
class ExportedByPolyhedralModel CATPolyPointBaseConst : public CATIPolyPoint
{

public:

  CATPolyPointBaseConst () {}
  virtual ~CATPolyPointBaseConst () {}

public:

/** @name Virtual methods that can be overriden in a derived class.
    @{ */

  virtual HRESULT GetPosition (CATMathPoint& oP) const;
  virtual HRESULT GetSupport (CATIPolySupport*& oSupport) const;

/** @} */

public:

/** @name Virtual methods that may be overriden in a derived class for customization (visitors, tools.)
    @{ */

  virtual HRESULT Accept (const CATIPolyPoint& iPoint, CATPolyPointConstVisitor& iV) const;
  virtual CATIPolyPointConstTools* GetConstTools () const;

/** @} */

public:

/** @name Methods implemented in this class. There is no need to override these methods.
    @{ */

  CATIPolyCurveVertex* CastToCurveVertex ();
  const CATIPolyCurveVertex* CastToCurveVertex () const;
  CATIPolySurfaceVertex* CastToSurfaceVertex ();
  const CATIPolySurfaceVertex* CastToSurfaceVertex () const;

  CATBoolean IsLyingOn (const CATIPolyCurve& c) const;
  CATBoolean IsLyingOn (const CATIPolySurface& s) const;

  const CATIPolyCurve* IsStartVertex () const;
  CATIPolyCurve* IsStartVertex ();
  const CATIPolyCurve* IsEndVertex () const;
  CATIPolyCurve* IsEndVertex ();

  CATBoolean IsEditable () const;

  HRESULT SetPosition (const CATMathPoint& iP);
  HRESULT SetSupport (CATIPolySupport* iSupport);

  HRESULT RegisterObserver (CATIPolyPointObserver& iObserver);
  HRESULT UnregisterObserver (CATIPolyPointObserver& iObserver);

  HRESULT Accept (CATIPolyPoint& iPoint, CATPolyPointVisitor& iV);
  CATIPolyPointTools* GetTools ();

/** @} */

};

#endif // !CATPolyPointBaseConst_H
