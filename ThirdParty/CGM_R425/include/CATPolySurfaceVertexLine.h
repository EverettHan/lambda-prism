//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolySurfaceVertexLine.h
//
//=============================================================================
// 2011-05-20   NDO: Revisited
// 2007-07-04   BPG: New
//=============================================================================
#ifndef CATPolySurfaceVertexLine_H
#define CATPolySurfaceVertexLine_H

#include "PolyMeshImpl.h"
#include "CATPolySurfaceVertexLineBase.h"
#include "CATPolyIntDoublyLinkedList.h"
#include "CATPolyCurveObserverList.h"
#include "CATIPolySurfaceObserver.h"

class CATPolyDoubleDoublyLinkedList;
class CATPolyVector3dDoublyLinkedList;


/**
 * PolyhedralObjects implementation of a CATIPolySurfaceVertexLine.
 */
class ExportedByPolyMeshImpl CATPolySurfaceVertexLine : public CATPolySurfaceVertexLineBase
{

public:

  /**
   * Implementation of a surface-vertex line.
   * A surface-vertex line is a CATIPolyCurve that lies on a CATIPolySurface and whose segments define a vertex path on the surface.
   */
  static CATPolySurfaceVertexLine* New (CATIPolySurface& iPolySurface, CATBoolean iWithWLayer = FALSE, CATBoolean iWithTangentLayer = FALSE);

public:

/** @name Casting Methods.
    @{ */

      /**
       * Casts a const CATIPolyCurve as a const CATPolySurfaceVertexLine.
       */
  static const CATPolySurfaceVertexLine* Cast (const CATIPolyCurve* C);

  /**
   * Casts a CATIPolyCurve as a CATPolySurfaceVertexLine.
   */
  static CATPolySurfaceVertexLine* Cast (CATIPolyCurve* C);

/** @} */

public:

  CATIPolySurface& GetSurface ();
  const CATIPolySurface& GetSurface () const;
  int GetSurfaceVertex (int v) const;
  CATBoolean IsLyingOn (const CATIPolySurface &s) const;

public:

  /**
   * Creates a new surface vertex and appends it to the end of the surface vertex line.
   * @param v
   *   The output curve vertex that has been appended.
   */
  HRESULT AppendVertex (int& v);

  /**
   * Appends a surface vertex to the end of the vertex line.
   * @param sv
   *   The input surface vertex.  This vertex should be: 
   *      (1) a valid surface vertex and 
   *      (2) contiguous to the last vertex the curve refers to.
   * @param v
   *   The output curve vertex that has been appended.
   */
  HRESULT AppendSurfaceVertex (int sv, int &v);

  /*
   * Inserts a new curve vertex before another curve vertex.
   * The new curve vertex refers to the input surface vertex.
   * @param sv
   *   The input surface vertex.
   * @param vn 
   *   The input curve vertex; the new curve vertex will be inserted before this vertex.
   * @param v
   *   The output curve vertex.
   */
  HRESULT InsertSurfaceVertex (int sv, int vn, int& v);

  /**
   * Given two surface vertices, finds the corresponding line segment (bar) on the line.
   * The returned two vertices are consecutive on the line.
   * @param sv0
   *   The first input surface vertex.
   * @param sv1
   *   The second input surface vertex.
   * @param v0
   *   The output curve vertex corresponding to sv0.
   * @param v1
   *   The output curve vertex corresponding to sv1.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> A bar from the surface vertex line has been found.
   *     <li> <tt>S_FALSE</tt> No bar has been found.
   *   </ul>
   */
  HRESULT FindBar (int sv0, int sv1, int& v0, int& v1) const;

public:

  int GetNbVertices () const;

  HRESULT GetVertexIterator (CATIPolyCurveVertexIterator *&oIterator) const;

  int GetStartVertex () const;
  int GetEndVertex () const;

  int GetNextVertex (int v) const;
  int GetPrevVertex (int v) const;

public:

  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionConstLayer *&oLayer) const;
  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionLayer *&oLayer);

  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentConstLayer *&oLayer) const;
  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentLayer *&oLayer);

  HRESULT GetVertexWLayer (CATIPolyCurveVertexWConstLayer *&oLayer) const;
  HRESULT GetVertexWLayer (CATIPolyCurveVertexWLayer *&oLayer);

  HRESULT SetSupport (CATIPolySupport* iSupport);
  HRESULT GetSupport (CATIPolySupport*& oSupport) const;

public:

  HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolyCurveObserver* obs = 0);

  HRESULT RemoveLayer (CATIPolyLayer& iLayer);

  HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  bool HasLayer (const CLSID& id) const;

  HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

public:

  /**
   * Splits the bar in two by insertion of a new curve vertex.
   * A new vertex is propagated to the underlying mesh
   * (addition of a new vertex.)
   * The modification is propagated to the underlying mesh.
   * @param v0
   *   The first curve vertex.
   * @param v1
   *   The second curve vertex.
   * @param v
   *   The new curve vertex created during the split.
   */
  HRESULT SplitBar (const int v0, const int v1, int& v);

  /**
   * Splits a bar from the CATPolySurfaceVertexLine with a surface vertex.
   * @param v0
   *   The first curve vertex.
   * @param v1
   *   The second curve vertex.
   * @param sv
   *   The surface vertex used to split the bar (v0, v1).
   * @param v
   *   The output curve vertex.
   */
  HRESULT SplitBarWithSurfaceVertex (int v0, int v1, int sv, int& v);

  /**
   * Merges the two curve vertices.
   * This method propagates the merge to the underlying surface.
   */
  HRESULT MergeVertices (const int v0, const int v1);

  /**
   * Merges the two curve vertices.
   * This method does not propagate the merge to the underlying surface.
   */
  HRESULT MergeVerticesSVL (const int v0, const int v1);

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

/** @name Methods specific to this implementation
    @{ */

  /**
   * Given a curve vertex, updates the surface vertex it refers to.
   * @param v
   *   A valid curve vertex.
   * @param sv
   *   A valid surface vertex.  This vertex should be:
   *     (1) a valid surface vertex and
   *     (2) contiguous to the two adjacent surface vertices that the previous and next curve vertices refer to.
   */
  HRESULT UpdateSurfaceVertex (int v, int sv);

protected:

  /**
   * Finds the curve vertex that refers to the input surface vertex and returns it.
   * @param iSurfaceVertex
   *   The input surface vertex.
   * @return
   *   The curve vertex referring to the surface vertex.
   */
  int FindSurfaceVertex (int iSurfaceVertex) const;

public:

  inline int GetStartSurfaceVertex () const;
  inline int GetEndSurfaceVertex () const;

  /**
   * Returns the native surface support.
   * Do not release the support that is returned.
   */
  inline CATIPolySupport* GetNativeSupport () const;

public:

  void DisableSurfaceObserver ();
  void EnableSurfaceObserver ();

/** @} */

private:

  // No copy constructor and assignment operator allowed.
  CATPolySurfaceVertexLine (const CATPolySurfaceVertexLine &iRHS);
  CATPolySurfaceVertexLine& operator = (const CATPolySurfaceVertexLine &iRHS);

private:

  class SurfaceObserver;

  CATIPolySurface& _PolySurface;
  CATPolyDoubleDoublyLinkedList* _Ws;
  CATPolyVector3dDoublyLinkedList* _Tangents;
  CATIPolySupport* _Support;
  SurfaceObserver* _SurfaceObserver;

  CATPolyIntDoublyLinkedList _SurfaceVertices;
  CATPolyCurveObserverList _SVLObservers;  // List of observers of the CATIPolySurfaceVertexLine.

  CATBoolean _IsClosed;
  unsigned int _SurfaceVertex;
  unsigned int _Flag : 16;       // Set to 1 to indicate the surface observer is suspended when an action is being performed.
  unsigned int _Disabled : 16;   // Incremented/decremented each time the surface observer is disabled/enabled.

  friend class CATPolySurfaceVertexLineVertexPositionLayer;
  friend class CATPolySurfaceVertexLineTangentLayer;
  friend class CATPolySurfaceVertexLineWLayer;
  friend class CATPolyMeshVertexLine;  // To get rid of.

protected:

  CATPolySurfaceVertexLine (CATIPolySurface& iPolySurface, CATBoolean iWithWLayer, CATBoolean iWithTangentLayer);
  virtual ~CATPolySurfaceVertexLine ();

  HRESULT SetPositionLocal (int cv, const CATMathPoint& P);

  /**
   * Inserts a new curve vertex before an existing curve vertex, a.
   * Associates the new curve vertex to the surface vertex sv.
   */
  HRESULT SplitBarLocal (int cv0, int cv1, int a, int sv, int& v);

  /**
   * Merges the two vertices.
   */
  HRESULT MergeVerticesLocal (int cv0, int cv1);

public:

/** @name Deprecated methods.
    @{ */

  // Deprecated.
  virtual HRESULT AppendVertex (const CATMathPoint &P, int &v);

  // Deprecated.
  virtual HRESULT GetVertexPosition (const int v, CATMathPoint &oPoint) const;

  // Deprecated.
  virtual HRESULT SetVertexPosition (const int v, const CATMathPoint &iPoint);

/** @} */

};

inline int CATPolySurfaceVertexLine::GetStartSurfaceVertex () const
{
  return 0 < _SurfaceVertices.Size () ? _SurfaceVertices.Front () : 0;
}

inline int CATPolySurfaceVertexLine::GetEndSurfaceVertex () const
{
  return 0 < _SurfaceVertices.Size () ? _SurfaceVertices.Back () : 0;
}

inline CATIPolySupport* CATPolySurfaceVertexLine::GetNativeSupport () const
{
  return _Support;
}

#endif // !CATPolySurfaceVertexLine_H
