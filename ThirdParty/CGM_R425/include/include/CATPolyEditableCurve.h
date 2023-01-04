// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyEditableCurve.h
//
//===================================================================
// July 2018  Creation NDO
//===================================================================
#ifndef CATPolyEditableCurve_H
#define CATPolyEditableCurve_H

#include "PolyMeshImpl.h"
#include "CATIPolyCurve.h"
#include "CATPolyLine.h"
#include "CATMapOfIntToInt.h"
#include "CATPolyCurveObserverList.h"


/**
 * Class representing an editable poly-curve constructed from a constant poly-curve.
 * An editable poly-curve consists of a (non-editable) reference poly-curve and editable fields recording the changes
 * made to reference curve.
 * An editable poly-curve provides an editable view of the reference poly-curve.
 */
class ExportedByPolyMeshImpl CATPolyEditableCurve : public CATIPolyCurve
{

public:

  /**
   * Constructor of an editable curve from an existing constant CATIPolyCurve.
   * @param iCurve
   *   The reference curve  It is not edited by the methods of this class (const.)
   */
  static CATPolyEditableCurve* New (const CATIPolyCurve& iCurve);

  CATBoolean IsEditable () const;

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolyCurve as a const CATPolyEditableCurve.
   */
  static const CATPolyEditableCurve* Cast (const CATIPolyCurve* C);

  /**
   * Casts a CATIPolyCurve as a CATPolyEditableCurve.
   */
  static CATPolyEditableCurve* Cast (CATIPolyCurve* C);

/** @} */

public:

  HRESULT AppendVertex (int& v);
  HRESULT AppendVertex (const CATMathPoint& P, int& v);

public:

  int GetNbVertices () const;

  HRESULT GetVertexIterator (CATIPolyCurveVertexIterator*& oIterator) const;

  int GetStartVertex () const;
  int GetEndVertex () const;

  int GetNextVertex (int v) const;
  int GetPrevVertex (int v) const;

public:

/** @name Const Layers
    @{ */

  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionConstLayer*& oLayer) const;
  HRESULT GetVertexWLayer (CATIPolyCurveVertexWConstLayer*& oLayer) const;
  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentConstLayer*& oLayer) const;
  HRESULT GetSupport (CATIPolySupport*& oSupport) const;

/** @} */

public:

/** @name Layers
    @{ */

  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionLayer*& oLayer);
  HRESULT GetVertexWLayer (CATIPolyCurveVertexWLayer*& oLayer);
  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentLayer*& oLayer);
  HRESULT SetSupport (CATIPolySupport* iSupport);

/** @} */

public:

  HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolyCurveObserver* obs = 0);

  HRESULT RemoveLayer (CATIPolyLayer& iLayer);

  HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  bool HasLayer (const CLSID& id) const;

  HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

public:

  HRESULT SplitBar (const int v0, const int v1, int &n);
  HRESULT MergeVertices (const int v0, const int v1);

public:

  CATBoolean IsClosed () const;
  HRESULT Close ();
  HRESULT Open ();

public:

  HRESULT RegisterObserver (CATIPolyCurveObserver &iObserver);
  HRESULT UnregisterObserver (CATIPolyCurveObserver &iObserver);

  HRESULT Accept (const CATIPolyCurve& iCurve, CATPolyCurveConstVisitor& iVisitor) const;
  HRESULT Accept (CATIPolyCurve& iCurve, CATPolyCurveVisitor& iVisitor);

  CATIPolyCurveConstTools* GetConstTools () const;
  CATIPolyCurveTools* GetTools ();

public:

  CATIPolySurfaceVertexLine* CastToSurfaceVertexLine ();
  const CATIPolySurfaceVertexLine* CastToSurfaceVertexLine () const;

  const CATIPolyMeshCurve* CastToMeshCurve () const;
  CATIPolyMeshCurve* CastToMeshCurve ();

  CATBoolean IsLyingOn (const CATIPolySurface &s) const;

public:

  /** @name Methods specific to the editable curve implementation.
  @{ */

  /**
   * Returns the (non-editable) parent curve.
   */
  inline const CATIPolyCurve& GetParentCurve () const;

  /**
   * Returns true if the vertex is a parent vertex. 
   * A parent vertex may have its position or tangent edited.
   */
  inline bool IsParentVertex (const int v) const;

  /**
   * Returns true if the curve has been edited.
   */
  inline bool IsEdited () const;

  /** @} */

private:

  // No copy constructor and assignment operator allowed.
  CATPolyEditableCurve (const CATPolyEditableCurve &iRHS);
  CATPolyEditableCurve& operator= (const CATPolyEditableCurve &iRHS);

private:

  const CATIPolyCurve& _PolyCurve;
  CATPolyLine& _PolyLine;

  int _OffsetVertex;          // Maximum index of new curve vertex (always negative.)
  int _NbNewVertices;         // Number of new vertices added to the curve.
  unsigned int _Flags;        // Various flags.

  CATMapOfIntToInt _LineToEditVertexMap;  // Map a vertex from poly-line to a vertex from editable curve.
  CATMapOfIntToInt _EditToLineVertexMap;  // Map a vertex from editable curve to a vertex from poly-line.

  CATPolyCurveObserverList _Observers;  // List of observers of the editable curve.

private:

  /**
   * Masks for various flags.
   */
  enum Masks
  {
    /** Bit 0 for edited objects. */                    MaskEdited = 0x0001
  };

private:

  // Private New (Unstream).
  static CATPolyEditableCurve* New (const CATIPolyCurve& iCurve, 
                                    CATLONG32* verticesParent, CATLONG32 verticesEditable[], 
                                    const CATULONG32 nbVertices, const CATLONG32 offsetVertex);

  // Private constructor (see New ()).
  CATPolyEditableCurve (const CATIPolyCurve& iCurve, CATPolyLine& iPolyLine);

  // Private constructor (see New ()).
  CATPolyEditableCurve (const CATIPolyCurve& iCurve, CATPolyLine& iPolyLine,
                        CATLONG32* verticesParent, CATLONG32 verticesEditable[], 
                        const CATULONG32 nbVerticesEditable, const CATLONG32 offsetVertex);

  virtual ~CATPolyEditableCurve ();

  // Return a new editable vertex associated to the poly-line vertex cvl.
  int NewEditableVertex (int cvl);

  inline void SetEdited ();
  inline void UnsetEdited ();

  class VertexIterator;
  class VertexPositionLayer;
  class VertexTangentLayer;
  class VertexWLayer;

  friend class CATPolyCurveDefaultStreamer;
  friend class CATPolyCurveDefaultUnstreamer;

private:

/** @name Deprecated methods.
    @{ */

  // Deprecated.
  HRESULT GetVertexPosition (const int v, CATMathPoint& P) const;

  // Deprecated.
  HRESULT SetVertexPosition (const int v, const CATMathPoint& P);

/** @} */

};

inline const CATIPolyCurve& CATPolyEditableCurve::GetParentCurve () const
{
  return _PolyCurve;
}

inline bool CATPolyEditableCurve::IsParentVertex (const int v) const
{
  return v > _OffsetVertex;
}

inline void CATPolyEditableCurve::SetEdited ()
{
  _Flags |= MaskEdited;
}

inline void CATPolyEditableCurve::UnsetEdited ()
{
  _Flags &= ~MaskEdited;
}

inline bool CATPolyEditableCurve::IsEdited () const
{
  return _Flags & MaskEdited ? true : false;
}

#endif // !CATPolyEditableCurve_H
