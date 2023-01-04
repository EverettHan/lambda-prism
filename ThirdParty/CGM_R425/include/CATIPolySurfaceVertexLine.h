// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceVertexLine.h
//
//===================================================================
// June 2010  Creation: NDO
//===================================================================
#ifndef CATIPolySurfaceVertexLine_H
#define CATIPolySurfaceVertexLine_H

#include "PolyhedralModel.h"
#include "CATIPolyCurve.h"

class CATIPolySurface;


/**
* Interface to a polyhedral surface vertex line.
*
* A polyhedral surface vertex line is a CATIPolyCurve that consists of a sequence of CATIPolySurface vertices.  
* A surface vertex line lies on a CATIPolySurface.
* 
* As a CATIPolyCurve, the vertices are referenced by integer indices.  Each surface vertex line vertex is associated to a CATIPolySurface
* vertex.
* 
* Implementations of this interface should be thread-safe for use with the polyhedral operators.
*
*/
class ExportedByPolyhedralModel CATIPolySurfaceVertexLine : public CATIPolyCurve
{

public:

/** @name Casting Methods
    @{ */

  inline static CATIPolySurfaceVertexLine* Cast (CATIPolyCurve&);

  inline static const CATIPolySurfaceVertexLine* Cast (const CATIPolyCurve&);

  inline static CATIPolySurfaceVertexLine* Cast (CATIPolyCurve*);

  inline static const CATIPolySurfaceVertexLine* Cast (const CATIPolyCurve*);

  inline static CATIPolySurfaceVertexLine* Cast (CATIPolyObject&);

  inline static const CATIPolySurfaceVertexLine* Cast (const CATIPolyObject&);

  inline static CATIPolySurfaceVertexLine* Cast (CATIPolyObject*);

  inline static const CATIPolySurfaceVertexLine* Cast (const CATIPolyObject*);

/** @} */

public:

/** @name Access to CATIPolySurface
    @{ */

  /**
   * Returns the CATIPolySurface on which the surface vertex line lies.
   */
  virtual CATIPolySurface& GetSurface () = 0;

  /**
   * Returns the CATIPolySurface on which the surface vertex line lies.
   */
  virtual const CATIPolySurface& GetSurface () const = 0;

/** @} */

public:

/** @name Vertex Events and Queries
    @{ */

  /**
   * Appends a surface vertex to the end of the vertex line.
   * @param sv
   *   The input surface vertex.  This vertex should be: 
   *      (1) a valid surface vertex and 
   *      (2) contiguous to the last vertex the curve refers to.
   * @param v
   *   The output curve vertex.
   */
  virtual HRESULT AppendSurfaceVertex (int sv, int& v) = 0;

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
  virtual HRESULT InsertSurfaceVertex (int sv, int vn, int& v) = 0;

  /**
   * Given a vertex on the line, returns the surface vertex.
   * @param w
   *   The index of the vertex on the line.
   * @return 
   *   The index of the vertex on the surface.
   */
  virtual int GetSurfaceVertex (int v) const = 0;

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
  virtual HRESULT FindBar (int sv0, int sv1, int& v0, int& v1) const = 0;

/** @} */

public:

/** @name Topological Services
    @{ */

  /**
   * Splits a bar from the surface vertex line given a surface-vertex
   * and with creation of a new curve-vertex.
   * This method does not propagate the split to the underlying surface.
   * @param v0
   *   The first curve-vertex.
   * @param v1
   *   The second curve-vertex.
   * @param sv
   *   An exiting surface vertex used to split the bar (v0, v1).
   * @param n
   *   The output curve vertex.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> if the bar is split.
   *     <li> <tt>S_FALSE</tt> if the bar is not split (for instance if the two vertices are consecutive).
   *     <li> <tt>E_FAIL</tt> if an error occurs.
   *   </ul>
   */
  virtual HRESULT SplitBarWithSurfaceVertex (int cv0, int cv1, int sv, int& n) = 0;

  /**
   * Merges the curve vertices v0 and v1 by collapse of the bar (v0, v1).
   * Topologically, the curve vertex v1 is removed.
   * This method does not propagate the merge to the underlying surface.
   * The two vertices must be contiguous.
   * @param v0
   *   The first curve-vertex.
   * @param v1
   *   The second curve-vertex.
   * @return
   *   S_OK if the curve is successfully edited and E_FAIL otherwise.
   */
  virtual HRESULT MergeVerticesSVL (const int v0, const int v1) = 0;

  /**
   * Call made to inform the surface-vertex line that there was a change of a vertex position.
   * Used to inform surface-vertex line observers.
   * @param cv
   *   The index of the curve-vertex.
   */
  virtual HRESULT ReactToSetVertexPosition (int cv, const CATMathPoint& P) = 0;

/** @} */

protected:

  virtual ~CATIPolySurfaceVertexLine () {}

public:

  const CATIPolySurfaceVertexLine* CastToSurfaceVertexLine () const;
  CATIPolySurfaceVertexLine* CastToSurfaceVertexLine ();

  const CATIPolyMeshCurve* CastToMeshCurve () const;
  CATIPolyMeshCurve* CastToMeshCurve ();

};

inline CATIPolySurfaceVertexLine* CATIPolySurfaceVertexLine::Cast (CATIPolyCurve& C)
{
  return C.CastToSurfaceVertexLine ();
}

inline const CATIPolySurfaceVertexLine* CATIPolySurfaceVertexLine::Cast (const CATIPolyCurve& C)
{
  return C.CastToSurfaceVertexLine ();
}

inline CATIPolySurfaceVertexLine* CATIPolySurfaceVertexLine::Cast (CATIPolyCurve* C)
{
  return C ? Cast (*C) : 0;
}

inline const CATIPolySurfaceVertexLine* CATIPolySurfaceVertexLine::Cast (const CATIPolyCurve* C)
{
  return C ? Cast (*C) : 0;
}

inline CATIPolySurfaceVertexLine* CATIPolySurfaceVertexLine::Cast (CATIPolyObject& O)
{
  return Cast (CATIPolyCurve::Cast (O));
}

inline const CATIPolySurfaceVertexLine* CATIPolySurfaceVertexLine::Cast (const CATIPolyObject& O)
{
  return Cast (CATIPolyCurve::Cast (O));
}

inline CATIPolySurfaceVertexLine* CATIPolySurfaceVertexLine::Cast (CATIPolyObject* O)
{
  return O ? Cast (*O) : 0;
}

inline const CATIPolySurfaceVertexLine* CATIPolySurfaceVertexLine::Cast (const CATIPolyObject* O)
{
  return O ? Cast (*O) : 0;
}

#endif // !CATIPolySurfaceVertexLine_H
