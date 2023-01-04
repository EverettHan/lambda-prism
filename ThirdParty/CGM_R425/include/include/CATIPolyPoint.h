//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================
#ifndef CATIPolyPoint_H
#define CATIPolyPoint_H

#include "PolyhedralModel.h"
#include "CATIPolyObject.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

// Subclasses.
class CATIPolyCurveVertex;
class CATIPolySurfaceVertex;
class CATIPolyCurvePoint;
class CATIPolyMeshPoint;

// Supports.
class CATIPolySupport;

// Tools.
class CATIPolyPointConstTools;
class CATIPolyPointTools;

// Extensions: Observers, Visitors.
class CATIPolyPointObserver;
class CATPolyPointConstVisitor;
class CATPolyPointVisitor;

class CATIPolyCurve;
class CATIPolySurface;
class CATMathPoint;


/**
* Interface to a polyhedral point.
*
* Implementations of this interface should be thread-safe for use with the polyhedral operators.
*
*/
class ExportedByPolyhedralModel CATIPolyPoint : public CATIPolyObject
{

public:

/** @name Downcasters
    @{ */

  inline static const CATIPolyPoint* Cast (const CATIPolyObject&);

  inline static CATIPolyPoint* Cast (CATIPolyObject&);

  inline static const CATIPolyPoint* Cast (const CATIPolyObject*);

  inline static CATIPolyPoint* Cast (CATIPolyObject*);

/** @} */

public:

/** @name Cross Services with Polyhedral Curves
    @{ */

  /**
   * Checks if the point lies on a polyhedral curve.
   * @param c
   *   The input polyhedral curve.
   * @return
   *   <tt>TRUE</tt> if the point lies on the polyhedral curve and <tt>FALSE</tt> otherwise.
   */
  virtual CATBoolean IsLyingOn (const CATIPolyCurve& c) const = 0;

  /**
   * Returns the curve whose CATIPolyPoint is the start of.
   */
  virtual const CATIPolyCurve* IsStartVertex () const = 0;

  /**
   * Returns the curve whose CATIPolyPoint is the start of.
   */
  virtual CATIPolyCurve* IsStartVertex () = 0;

  /**
   * Returns the curve whose CATIPolyPoint is the end of.
   */
  virtual const CATIPolyCurve* IsEndVertex () const = 0;

  /**
   * Returns the curve whose CATIPolyPoint is the end of.
   */
  virtual CATIPolyCurve* IsEndVertex () = 0;

/** @} */

public:

/** @name Cross Services with Polyhedral Surfaces
    @{ */

  /**
   * Checks if the point lies on a polyhedral surface.
   * @param s
   *   The input polyhedral surface.
   * @return
   *   <tt>TRUE</tt> if the point lies on the polyhedral surface and <tt>FALSE</tt> otherwise.
   */
  virtual CATBoolean IsLyingOn (const CATIPolySurface& s) const = 0;

/** @} */

public:

/** @name Layers
    @{ */

  /**
   * Returns the vertex coordinates.
   */
  virtual HRESULT GetPosition (CATMathPoint& oP) const = 0;

  /**
   * Sets the vertex coordinates.
   */
  virtual HRESULT SetPosition (const CATMathPoint& iP) = 0;

/** @} */

public:

/** @name Point Support
    @{ */

  /**
   * @nodoc
   * Returns the underlying point support, if any. 
   * @param oSupport
   *   The point support.  The returned support must be released (ref-counted.)
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a support is successfully returned.
   *   <li> <tt>S_FALSE</tt> if a support is not available.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  virtual HRESULT GetSupport (CATIPolySupport*& oSupport) const = 0;

  /**
   * @nodoc
   * Sets the underlying point support.
   * @param iSupport
   *   A pointer to the point support.  The method does and AddRef () on the support.
   *   Any previous support owned by the object will be released.
   * @return 
   *   S_OK if the support is set, and
   *   E_FAIL otherwise.
   */
  virtual HRESULT SetSupport (CATIPolySupport* iSupport) = 0;

/** @} */

public:

/** @name Event Listener. 
    Event listener are used to update attributes (user-defined layers.)
    @{ */

  /** 
   * @nodoc
   * Registers an observer (event listener) with the instance. 
   * @param iObserver
   *   The observer that is registered with the instance.
   * @return 
   *   S_OK if the observer is successfully registered with the point.
   *   E_FAIL otherwise.
   */
  virtual HRESULT RegisterObserver (CATIPolyPointObserver &iObserver) = 0;

  /** 
   * @nodoc
   * Unregisters an observer (event listener) with the instance. 
   * @param iObserver
   *   The observer that is unregistered with the instance.
   * @return 
   *   S_OK if the observer is successfully unregistered with the point.
   *   E_FAIL otherwise.
   */
  virtual HRESULT UnregisterObserver (CATIPolyPointObserver &iObserver) = 0;

/** @} */

public:

/** @name Visitors.  
    Access to concrete types.
    @{ */

  /**
   * @nodoc
   * Access the concrete type through a const visitor.
   * @return
   *   The status of the application of the visitor.
   */
  virtual HRESULT Accept (const CATIPolyPoint& iPoint, CATPolyPointConstVisitor& iV) const = 0;

  /**
   * @nodoc
   * Access the concrete type through a non-const visitor.
   * @return
   *   The status of the application of the visitor
   */
  virtual HRESULT Accept (CATIPolyPoint& iPoint, CATPolyPointVisitor& iV) = 0;

/** @} */

public:

/** @name Other services
    Tools provide access to various point services. 
    Do not use in frameworks other than in PolyhedralInterfaces and PolyhedralObjects.
    @{ */

  /**
   * @nodoc
   * Do not delete tools.
   */
  virtual CATIPolyPointConstTools* GetConstTools () const = 0;

  /**
   * @nodoc
   * Do not delete tools.
   */
  virtual CATIPolyPointTools* GetTools () = 0;

/** @} */

protected:

  virtual ~CATIPolyPoint() {}

  const CATIPolyPoint* CastToPolyPoint () const { return this; }
  CATIPolyPoint* CastToPolyPoint () { return this; }

public:

  /**
   * Casts a const CATIPolyPoint to a const CATIPolyCurveVertex.
   * @return
   *   The cast as a const CATIPolyCurveVertex.
   */
  virtual CATIPolyCurveVertex* CastToCurveVertex () { return 0; }

  /**
   * Casts a const CATIPolyPoint to a const CATIPolyCurveVertex.
   * @return
   *   The cast as a const CATIPolyCurveVertex.
   */
  virtual const CATIPolyCurveVertex* CastToCurveVertex () const { return 0; }

  /**
   * Casts a const CATIPolyPoint to a const CATIPolySurfaceVertex.
   * @return
   *   The cast as a const CATIPolySurfaceVertex.
   */
  virtual CATIPolySurfaceVertex* CastToSurfaceVertex () { return 0; }

  /**
   * Casts a const CATIPolyPoint to a const CATIPolySurfaceVertex.
   * @return
   *   The cast as a const CATIPolySurfaceVertex.
   */
  virtual const CATIPolySurfaceVertex* CastToSurfaceVertex () const { return 0; }

  /**
   * Casts a const CATIPolyPoint to a const CATIPolyCurvePoint.
   * @return
   *   The cast as a const CATIPolyCurvePoint.
   */
  virtual CATIPolyCurvePoint* CastToCurvePoint () { return 0; }

  /**
   * Casts a const CATIPolyPoint to a const CATIPolyCurvePoint.
   * @return
   *   The cast as a const CATIPolyCurvePoint.
   */
  virtual const CATIPolyCurvePoint* CastToCurvePoint () const { return 0; }

  /**
   * Casts a const CATIPolyPoint to a const CATIPolyMeshPoint.
   * @return
   *   The cast as a const CATIPolyMeshPoint.
   */
  virtual CATIPolyMeshPoint* CastToMeshPoint () { return 0; }

  /**
   * Casts a const CATIPolyPoint to a const CATIPolyMeshPoint.
   * @return
   *   The cast as a const CATIPolyMeshPoint.
   */
  virtual const CATIPolyMeshPoint* CastToMeshPoint () const { return 0; }

};

inline const CATIPolyPoint* CATIPolyPoint::Cast (const CATIPolyObject& iObject)
{
  return iObject.CastToPolyPoint ();
}

inline CATIPolyPoint* CATIPolyPoint::Cast (CATIPolyObject& iObject)
{
  return iObject.CastToPolyPoint ();
}

inline const CATIPolyPoint* CATIPolyPoint::Cast (const CATIPolyObject* iObject)
{
  return iObject ? CATIPolyPoint::Cast (*iObject) : 0;
}

inline CATIPolyPoint* CATIPolyPoint::Cast (CATIPolyObject* iObject)
{
  return iObject ? CATIPolyPoint::Cast (*iObject) : 0;
}

#endif // !CATIPolyPoint_H
