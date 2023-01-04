// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCurveVertexBaseConst.h
//
//===================================================================
// October 2013  Creation: NDO
//===================================================================
#ifndef CATPolyCurveVertexBaseConst_H
#define CATPolyCurveVertexBaseConst_H

#include "PolyhedralModel.h"
#include "CATIPolyCurveVertex.h"


/**
Class providing a default implementation to a non-editable CATIPolyCurveVertex.
All CATIPolyCurveVertex adapter or read-only implementation can derive from this class.
All virtual methods should be implemented in a derived class unless otherwise noted.
*/
class ExportedByPolyhedralModel CATPolyCurveVertexBaseConst : public CATIPolyCurveVertex
{

public:

  CATPolyCurveVertexBaseConst () {}
  virtual ~CATPolyCurveVertexBaseConst () {}

public:

/** @name Virtual methods to must be defined in a derived class.
    @{ */

  virtual CATIPolyCurve& GetCurve () = 0;
  virtual const CATIPolyCurve& GetCurve () const = 0;

  virtual CATBoolean IsLyingOn (const CATIPolyCurve& c) const = 0;
  virtual CATBoolean IsLyingOn (const CATIPolySurface& s) const = 0;

  virtual const CATIPolyCurve* IsStartVertex () const = 0;
  virtual CATIPolyCurve* IsStartVertex () = 0;

  virtual const CATIPolyCurve* IsEndVertex () const = 0;
  virtual CATIPolyCurve* IsEndVertex () = 0;

  virtual int GetCurveVertexIndex () const = 0;

/** @} */

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

  CATBoolean IsEditable () const;

  HRESULT SetPosition (const CATMathPoint& iP);
  HRESULT SetSupport (CATIPolySupport* iSupport);

  HRESULT RegisterObserver (CATIPolyPointObserver& iObserver);
  HRESULT UnregisterObserver (CATIPolyPointObserver& iObserver);

  HRESULT Accept (CATIPolyPoint& iPoint, CATPolyPointVisitor& iV);
  CATIPolyPointTools* GetTools ();

/** @} */

};

#endif // !CATPolyCurveVertexBaseConst_H
