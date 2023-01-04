// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyEditableSurfaceVertexLine.h
//
//===================================================================
// September 2013  Creation NDO
//===================================================================
#ifndef CATPolyEditableSurfaceVertexLine_H
#define CATPolyEditableSurfaceVertexLine_H

#include "PolyMeshImpl.h"
#include "CATPolySurfaceVertexLineBase.h"
#include "CATIPolySurface.h"
#include "CATMapOfIntToPtr.h"
#include "CATPolyCurveObserverList.h"

class CATPolySurfaceVertexLineSurfaceObserver;


/**
 * Class representing an editable surface vertex line constructed from a constant surface vertex line.
 * An editable surface vertex line consists of a (non-editable) reference SVL and editable fields recording the changes
 * made to reference SVL.
 * An editable SVL provides an editable view of the reference SVL.
 */
class ExportedByPolyMeshImpl CATPolyEditableSurfaceVertexLine : public CATPolySurfaceVertexLineBase
{

public:

  /**
   * Constructor of an editable surface vertex line from an existing constant CATIPolySurfaceVertexLine.
   * @param iPolySurface
   *   The editable surface on which the editable surface vertex line lies.
   * @param iSVL
   *   The reference surface vertex line.  It is not edited by the methods of this class (const.)
   */
  static CATPolyEditableSurfaceVertexLine* New (CATIPolySurface& iPolySurface, const CATIPolySurfaceVertexLine& iSVL,
                                                bool iDisableSurfaceObserver = false);

public:

/** @name Casting Methods.
  @{ */

  /**
   * Casts a const CATIPolyCurve as a const CATPolyEditableSurfaceVertexLine.
   */
  static const CATPolyEditableSurfaceVertexLine* Cast (const CATIPolyCurve* iCurve);

  /**
  * Casts a CATIPolyCurve as a CATPolyEditableSurfaceVertexLine.
  */
  static CATPolyEditableSurfaceVertexLine* Cast (CATIPolyCurve* iCurve);

/** @} */

public:

/** @name CATIPolySurface Services
    @{ */

  /**
   * Returns the CATIPolySurface on which the surface vertex line lies.
   */
  CATIPolySurface& GetSurface ();

  /**
   * Returns the CATIPolySurface on which the surface vertex line lies.
   */
  const CATIPolySurface& GetSurface () const;

  /**
   * Given an index of a vertex on the line, returns the surface vertex index.
   * @param w
   *   The index of the vertex on the line.
   * @return 
   *   The index of the vertex on the surface.
   */
  int GetSurfaceVertex (int w) const;

  CATBoolean IsLyingOn (const CATIPolySurface& s) const;

/** @} */

public:

/** @name Vertices Management
    @{ */

  /**
   * Creates a new surface vertex and appends it at the end of the curve.
   * @param v
   *   The index of the new curve vertex.
   * @return 
   *   S_OK on success or E_FAIL or another error otherwise.
   */
  HRESULT AppendVertex (int& v);

  /**
   * Appends a surface vertex to the end of the vertex line.
   * @param sv
   *   The input surface vertex.  This vertex should be: 
   *      (1) a valid surface vertex and 
   *      (2) contiguous to the last vertex the curve refers to.
   * @param v
   *   The output curve vertex.
   */
  HRESULT AppendSurfaceVertex (int sv, int& v);

  /*
   * Inserts a new curve vertex before another curve vertex.
   * The new curve vertex refers to the input surface vertex.
   * @param iSurfaceVertex
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

  /** 
   * Returns the number of vertices of the polyhedral curve.
   * @return 
   *   The number of vertices of the discrete curve.
   */
  int GetNbVertices () const;

  /**
   * Returns a vertex iterator (explicit).
   * @param oIterator
   *   The output iterator.  The returned instance must be released. (ref-counted.)
   * @return
   *   <tt>S_OK</tt> on success and <tt>E_FAIL</tt> or another error otherwise.
   */
  HRESULT GetVertexIterator (CATIPolyCurveVertexIterator*& oIterator) const;

  int GetStartVertex () const;
  int GetEndVertex () const;

  int GetNextVertex (int v) const;
  int GetPrevVertex (int v) const;

  CATBoolean IsClosed () const;

/** @} */

public:

/** @name Vertex Layers
    @{ */

  /**
   * Returns the vertex position layer if any. 
   * @param oLayer [out, IUnknown#Release] 
   *   The layer that is returned.  The returned layer must be released (ref-counted.)
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a layer is successfully returned.
   *   <li> <tt>S_FALSE</tt> if a layer is not available.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionConstLayer*& oLayer) const;

  /**
   * Returns the vertex position layer if any. 
   * @param oLayer [out, IUnknown#Release] 
   *   The layer that is returned.  The returned layer must be released (ref-counted.)
   * @return
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a layer is successfully returned.
   *   <li> <tt>S_FALSE</tt> if a layer is not available.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionLayer*& oLayer);

  /**
   * Returns the vertex tangent layer if any. 
   * @param oLayer [out, IUnknown#Release] 
   *   The layer that is returned.  The returned layer must be released (ref-counted.)
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a layer is successfully returned.
   *   <li> <tt>S_FALSE</tt> if a layer is not available.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentConstLayer*& oLayer) const;

  /**
   * Returns the vertex tangent layer if any. 
   * @param oLayer [out, IUnknown#Release] 
   *   The layer that is returned.  The returned layer must be released (ref-counted.)
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a layer is successfully returned.
   *   <li> <tt>S_FALSE</tt> if a layer is not available.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentLayer*& oLayer);

/** @} */

public:

  HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolyCurveObserver* obs = 0);

  HRESULT RemoveLayer (CATIPolyLayer& iLayer);

  HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  bool HasLayer (const CLSID& id) const;

  HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

public:

  /**
   * Creates a new vertex n to split the bar (v0, v1). 
   * The coordinates of n are undefined and must be set.  (See the vertex position layer.)
   * @param v0
   *   The first vertex of the bar.
   * @param v1
   *   The second vertex of the bar.
   * @param v
   *   The index of the new vertex.
   * @return
   *   <tt>S_OK</tt> if the curve is successfully edited and <tt>E_FAIL</tt> otherwise.
   */
  HRESULT SplitBar (const int v0, const int v1, int& v);

  /**
   * Splits a bar from the surface vertex line with a surface vertex.
   * @param v0
   *   The first curve vertex.
   * @param v1
   *   The second curve vertex.
   * @param iSurfaceVertex
   *   The surface vertex used to split the bar (v0, v1).
   * @param v
   *   The output curve vertex.
   */
  HRESULT SplitBarWithSurfaceVertex (int v0, int v1, int iSurfaceVertex, int& v);

  /**
   * Merges Vertices v0 and v1 by collapse of the bar (v0, v1).
   * The two vertices must be contiguous.
   * This method deletes the second vertex after the merge.
   * @param v0
   *   The first vertex of the bar.
   * @param v1
   *   The second vertex of the bar.
   * @return
   *   S_OK if the curve is successfully edited and E_FAIL otherwise.
   */
  HRESULT MergeVertices (const int v0, const int v1);

  /**
   * Merges the two curve vertices.
   * This method does not propagate the merge to the underlying surface.
   */
  HRESULT MergeVerticesSVL (const int v0, const int v1);

public:

  HRESULT RegisterObserver (CATIPolyCurveObserver &iObserver);
  HRESULT UnregisterObserver (CATIPolyCurveObserver &iObserver);

  HRESULT Accept (const CATIPolyCurve& iCurve, CATPolyCurveConstVisitor& iVisitor) const;
  HRESULT Accept (CATIPolyCurve& iCurve, CATPolyCurveVisitor& iVisitor);

  CATIPolyCurveConstTools* GetConstTools () const;
  CATIPolyCurveTools* GetTools ();

public:

  void DisableSurfaceObserver ();
  void EnableSurfaceObserver ();

public:

/** @name Methods specific to editable surface-vertex line implementation
    @{ */

  /**
   * Returns the (non-editable) parent surface-vertex line.
   */
  inline const CATIPolySurfaceVertexLine& GetParentSurfaceVertexLine () const;

  /**
   * Returns true if the vertex is a parent vertex. 
   * A parent vertex may have its position or tangent edited.
   */
  inline bool IsParentVertex (const int v) const;

  /**
   * Returns true if the surface-vertex line has been edited.
   */
  inline bool IsEdited () const;

/** @} */

private:

  struct Node
  {
    Node* _Prev;
    Node* _Next;
    int _SurfaceVertex;  // Vertex on the editable input CATIPolySurface.
    int _SVLVertex;      // Set to the input SVL vertex and to 0 for a new SVL vertex.

    Node () : _Prev (0), _Next (0), _SurfaceVertex (0), _SVLVertex (0) {}
  };

private:

  CATIPolySurface& _PolySurface;
  const CATIPolySurfaceVertexLine& _SVL;

  CATIPolyCurveVertexPositionLayer* _PosLayer;
  CATIPolyCurveVertexTangentLayer* _TangentLayer;

  CATPolySurfaceVertexLineSurfaceObserver* _SurfaceObserver;  // Also contains SVL observers.

  Node* _Head;
  Node* _Tail;
  Node* _FreeNode;            // For recycling.
  int _OffsetVertex;          // Maximum index of new curve vertex (always negative.)
  int _NbNewVertices;         // Number of new vertices added to the curve.
  unsigned int _Flags;        // Various flags.

  CATMapOfIntToPtr _Nodes;

  CATPolyCurveObserverList _SVLObservers;  // List of observers of the CATIPolySurfaceVertexLine.

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
  static CATPolyEditableSurfaceVertexLine* New (CATIPolySurface& iPolySurface, const CATIPolySurfaceVertexLine& iSVL,
                                                CATLONG32* vParent, CATLONG32 vEditable[], CATLONG32 svEditable[],
                                                const CATULONG32 nbVerticesEditable, const CATLONG32 offsetVertex,
                                                bool iDisableSurfaceObserver = false);

  // Private constructor (see New ()).
  CATPolyEditableSurfaceVertexLine (CATIPolySurface& iPolySurface, const CATIPolySurfaceVertexLine& iSVL,
                                    bool iDisableSurfaceObserver);

  // Private constructor (see New ()).
  CATPolyEditableSurfaceVertexLine (CATIPolySurface& iPolySurface, const CATIPolySurfaceVertexLine& iSVL,
                                    CATLONG32* vParent, CATLONG32 vEditable[], CATLONG32 svEditable[],
                                    const CATULONG32 nbVerticesEditable, const CATLONG32 offsetVertex,
                                    bool iDisableSurfaceObserver);

  virtual ~CATPolyEditableSurfaceVertexLine ();

  // No copy constructor and assignment operator.
  CATPolyEditableSurfaceVertexLine(const CATPolyEditableSurfaceVertexLine &iRHS);
  CATPolyEditableSurfaceVertexLine& operator=(const CATPolyEditableSurfaceVertexLine &iRHS);

private:

  class VertexIterator;
  class VertexPositionLayer;

  friend class CATPolyCurveDefaultStreamer;
  friend class CATPolyCurveDefaultUnstreamer;

  void Initialize ();

  void PushFreeNode (Node& N);
  Node* PopFreeNode ();
  void ReleaseNodes ();

  inline void SetEdited ();
  inline void UnsetEdited ();

private:

  // Adds a node to the map given an original curve vertex.
  inline Node* AddNode (const int cv);

  // Adds a node to the map for a new curve vertex.
  Node* AddNode ();

  // Remove a node from the map.
  void RemoveNode (Node& N);

  // Gets a node from the map given a curve vertex.
  inline Node* GetNode (int cv) const;

private:

  void AppendToCurve (Node& N);
  //void PrependToCurve (Node& N);

  // Removes a node from the curve.
  HRESULT RemoveFromCurve (Node& N);

private:

  // Inserts a new curve vertex **after** an existing vertex associated to N0.
  HRESULT InsertAfter (const int sv, Node& N0, int& v);

  // Inserts a new curve vertex **before** an existing vertex associated to N1.
  HRESULT InsertBefore (const int sv, Node& N1, int& v);

private:

/** @name Deprecated methods.
    @{ */

  // Deprecated.
  HRESULT GetVertexPosition (const int v, CATMathPoint& P) const;

  // Deprecated.
  HRESULT SetVertexPosition (const int v, const CATMathPoint& P);

/** @} */

};

inline CATPolyEditableSurfaceVertexLine::Node* CATPolyEditableSurfaceVertexLine::AddNode (const int cv)
{
  Node* N = new Node;
  N->_SVLVertex = cv;
  _Nodes.Insert (N->_SVLVertex, N);
  return N;
}

inline CATPolyEditableSurfaceVertexLine::Node* CATPolyEditableSurfaceVertexLine::GetNode (int cv) const
{
  Node* N = 0;
  _Nodes.Locate (cv, (void*&)N);
  return N;
}

inline const CATIPolySurfaceVertexLine& CATPolyEditableSurfaceVertexLine::GetParentSurfaceVertexLine () const
{
  return _SVL;
}

inline bool CATPolyEditableSurfaceVertexLine::IsParentVertex (const int v) const
{
  return v > _OffsetVertex;
}

inline void CATPolyEditableSurfaceVertexLine::SetEdited ()
{
  _Flags |= MaskEdited;
}

inline void CATPolyEditableSurfaceVertexLine::UnsetEdited ()
{
  _Flags &= ~MaskEdited;
}

inline bool CATPolyEditableSurfaceVertexLine::IsEdited () const
{
  return _Flags & MaskEdited ? true : false;
}

#endif // !CATPolyEditableSurfaceVertexLine_H
