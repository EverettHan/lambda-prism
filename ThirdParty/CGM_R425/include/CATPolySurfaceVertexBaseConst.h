// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVertexBaseConst.h
//
//===================================================================
// October 2013  Creation: NDO
//===================================================================
#ifndef CATPolySurfaceVertexBaseConst_H
#define CATPolySurfaceVertexBaseConst_H

#include "PolyhedralModel.h"
#include "CATIPolySurfaceVertex.h"


/**
Class providing a default implementation to a non-editable CATIPolySurfaceVertex.
All CATIPolySurfaceVertex adapter or read-only implementation can derive from this class.
All virtual methods should be implemented in a derived class unless otherwise noted.
*/
class ExportedByPolyhedralModel CATPolySurfaceVertexBaseConst : public CATIPolySurfaceVertex
{

public:

  CATPolySurfaceVertexBaseConst () {}
  virtual ~CATPolySurfaceVertexBaseConst ();

public:

/** @name Virtual methods to must be defined in a derived class.
    @{ */

  virtual CATIPolySurface& GetSurface () = 0;
  virtual const CATIPolySurface& GetSurface () const = 0;

  virtual CATBoolean IsLyingOn (const CATIPolyCurve& c) const = 0;
  virtual CATBoolean IsLyingOn (const CATIPolySurface& s) const = 0;

  virtual int GetSurfaceVertexIndex () const = 0;

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

#endif // !CATPolySurfaceVertexBaseConst_H
