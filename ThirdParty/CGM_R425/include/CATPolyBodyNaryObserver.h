// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyNaryObserver.h
//
//===================================================================
// February 2017 Creation: xxc
//===================================================================
#ifndef CATPolyBodyNaryObserver_H
#define CATPolyBodyNaryObserver_H

#include "PolyBodyTools.h" // Exported by.
#include "CATErrorDef.h"   // For the definition of HRESULT.

class CATPolyBody;
class CATPolyCell;
class CATPolyFace;
class CATPolyEdge;
class CATPolyVolume;
class CATPolyVertex;
class CATMapOfIntToInt;
class CATMathTransformation;
class CATPolyBodyOperandIterator;
class CATPolyBodyOperandCellIterator;
class CATPolyBodyUnaryObserver;
class CATPolyBodyBinaryObserver;
class CATPolyCellPointIterator;


/**
 * Observer interface for the n-ary operators taking n CATPolyBody operands as inputs
 * and producing a CATPolyBody result.
 * This observer maps the cells from the result CATPolyBody to the cells from the input operands.
 *
 * Binary observers are a n-ary observers taking two operands as inputs. 
 * Unary observers are n-ary observers taking one operand as input.
 *
 * @see CATPolyBodyJoin
 * @see CATPolyBodyBoolean
 * @see CATPolyBodySplitter
 * @see CATPolyBodyCombine
 * @see CATPolyBodyIntersect
 * @see CATPolyBodyCutter
 *
 */
class ExportedByPolyBodyTools CATPolyBodyNaryObserver
{

public:

  virtual ~CATPolyBodyNaryObserver () {}

  /**
   * This observer call is made for propagation of events during the construction of the
   * vertex, edge or face geometries.
   * By default, no events are generated during the construction of the geometry.
   * @return
   * <ul>
   *   <li> <tt>false</tt>: By default, no additional notifications are made during construction of the
   *                        vertex, edge or face geometries.
   *   <li> <tt>true</tt>: Additional notifications are made during construction of the vertex, edge or
   *                       face geometries.
   * </ul>
   */
  virtual bool RequestGeometryEvents () { return false; }

  /**
   * Returns the index of the operand in the range 0 to N-1, where N is the number
   * of operands from a tag. 
   * The method returns an index out of range if it cannot be determined.
   */
  virtual unsigned int GetIndexOfOperandFromTag (const int iTag) const { return (unsigned int) -1; }

public:

/** @name Operand and Result Events
    @{ */

  /**
   * Observer call made when an n-ary operation with n operands begins.
   * @param iOperands
   *   Iterator on the operands in the order of use.
   */
  virtual void Begins (CATPolyBodyOperandIterator& iOperands) {}

  /**
   * Call made with the result CATPolyBody obtained by processing the CATPolyBody operands
   * according to the n-ary operation.
   * @param iPolyBody
   *   The result CATPolyBody.
   *   The reference count must be incremented when keeping a reference.
   * @param iPosition
   *   If different from null, the position of the CATPolyBody result.
   */
  virtual void Result (CATPolyBody& iPolyBody, const CATMathTransformation* iPosition) {}

  /**
   * Observer call made when an n-ary operation with n operands ends.
   * The argument is the HRESULT returned by the Run () method.
   */
  virtual void Ends (HRESULT hrRun) {}

/** @} */

public:

/** @name CATPolyVertex Events
    @{ */

  /**
    * Observer call made at the start of the construction of a new CATPolyVertex.
    * This call is made only if the request has been made (see RequestGeometryEvents ()).
    * Otherwise, only the EndVertex call is made for notification about the construction of a new vertex.
    * @param iCellPoints
    *  An iterator on a set of CATPolyCellPoint from the N operands
    */
  virtual void BeginVertex (CATPolyCellPointIterator * iCellPoints) {}

  /**
   * Observer call made at the end of the construction of a new CATPolyVertex.
   * @param vertex
   *   The new CATPolyVertex.
   * @param iOperandCells
   *   An iterator on a set of operand cells associated to the new vertex.
   *   The cell-points are a reference to the input element and its barycentric coordinates.
   */
  virtual void EndVertex (CATPolyVertex* vertex, CATPolyBodyOperandCellIterator* iOperandCells) {}

/** @} */

public:

/** @name CATPolyEdge Events
    @{ */

  /**
   * Observer call made at the start of the construction of a new CATPolyEdge.
   */
  virtual void BeginEdge () {}

  /**
   * Call made each time a curve-vertex is added to the underlying edge geometry in sequence from start to end.
   * It provides the references to elements (triangles, bars, cell-vertex) from the input operands with 
   * the barycentric coordinates of the point on these elements. 
   * This call is made only if the request has been made (see RequestGeometryEvents ()).
   * @param cv
   *   The index of the curve-vertex that has just been appended.
   * @param iCellPoints
   *   An iterator on a set of CATPolyCellPoint from the N operands.
   *   The cell-points are a reference to the input element and its barycentric coordinates.
   */
  virtual void AppendCurveVertex (const int cv, CATPolyCellPointIterator * iCellPoints) {}

  /**
   * Observer call made at the end of the construction of a new CATPolyEdge.
   * @param edge
   *   The new CATPolyEdge.
   * @param iOperandCells
   *   An iterator on a set of operand cells associated to the new edge.
   */
  virtual void EndEdge (CATPolyEdge* edge, CATPolyBodyOperandCellIterator* iOperandCells) {}

/** @} */

public:

/** @name CATPolyFace Events
    @{ */

  /**
   * Observer call made at the start of the construction of a new CATPolyFace.
   */
  virtual void BeginFace () {}

  /**
   * Call made each time a surface-vertex is added to the underlying face geometry.
   * It provides the references to elements (triangles, bars, cell-vertex) from the input operands with 
   * the barycentric coordinates of the point on these elements. 
   * This call is made only if the request has been made (see RequestGeometryEvents ()).
   * @param sv
   *   The index of the surface-vertex that was added.
   * @param iCellPoints
   *   An iterator on a set of CATPolyCellPoint from the N operands.
   *   The cell-points are a reference to the input element and its barycentric coordinates.
   */
  virtual void AddSurfaceVertex (const int sv, CATPolyCellPointIterator * iCellPoints) {}

  /**
    * Call made each time a triangle is added to the underlying face geometry.
    * It provides the reference to a triangle of a face from an input operand.
    * This call is made only if the request has been made (see RequestGeometryEvents ()).
    * @param t
    *   The index of the triangle that was added.
    * @param iFace
    *   The parent face from an input operand.
    *   The argument may be null if the triangle does not refer to any parent face.
    * @param iFaceTriangle
    *   The triangle from the parent face to which the new triangle refers.
    */
  virtual void AddTriangle (const int t, CATPolyFace* iFace, const int iFaceTriangle) {}

  /**
   * Observer call made at the end of the construction of a new CATPolyFace.
   * @param face
   *   The new CATPolyFace.
   * @param iOperandCells
   *   An iterator on a set of operand cells associated to the new face.
   */
  virtual void EndFace (CATPolyFace* face, CATPolyBodyOperandCellIterator* iOperandCells) {}

/** @} */

  /** @} */

public:

  /** @name CATPolyVolume Events
      @{ */

  /**
    * Observer call made at the start of the construction of a new CATPolyVolume.
    */
  virtual void BeginVolume() {}

  /**
   * Observer call made at the end of the construction of a new CATPolyVolume.
   * @param volume
   *   The new CATPolyVolume.
   * @param iOperandCells
   *   An iterator on a set of operand cells associated to the new volume.
   */
  virtual void EndVolume(CATPolyVolume * volume, CATPolyBodyOperandCellIterator * iOperandCells) {}

  /** @} */

public:

/** @name Unedited Cell Events
    @{ */

    /**
    * Signals that a result face was constructed by the sharing or the copy
    * of a surface from a face from an input operand.  
    * The surface from the result face matches the geometry of the input face.
    * @param iResultFace
    *   A reference to the new face from the result.
    * @param iInputFace
    *   The reference to the face from an input operand that has not been edited.
    * @param iInputTag
    *   The tag identifying the input operand.
    * @param iOrientation
    *   The relative orientation of the two surfaces: -1 or +1.
    * @param iVertexMap
    *   A pointer to a map from the input to the result
    *   surface-vertices. If the map is the identity, the pointer may
    *   be null. Lifecycle is managed internaly by the observer.
    */
  virtual void UneditedSurface (CATPolyFace& iResultFace,
                                const CATPolyFace& iInputFace, const CATPolyBody& iInputBody, const int iInputTag,
                                int iOrientation, const CATMapOfIntToInt* iVertexMap) {}

  /**
  * Signals that a result edge was constructed by the sharing or the copy
  * of the curves from an edge of an input operand.
  * The curves from the result edge match the geometry of the input edge.
  * @param iResultEdge
  *   A reference to the new edge from the result.
  * @param iInputEdge
  *   The reference to the edge from an input operand that has not been edited.
  * @param iInputTag
  *   The tag identifying the input operand.
  * @param iOrientation
  *   The relative orientation of the curves from the result edge
  *   w.r.t. the curves of the input edge: -1 or +1.
  */
  virtual void UneditedCurves (CATPolyEdge& iResultEdge,
                               const CATPolyEdge& iInputEdge, const CATPolyBody& iInputBody, const int iInputTag,
                               int iOrientation) {}

  /**
  * Signals that a result vertex was constructed by the sharing or the copy
  * of the points from a vertex of an input operand.  
  * The points from the result vertex match the geometry of the input vertex.
  * @param iResultVertex
  *   A reference to the new vertex from the result.
  * @param iInputVertex
  *   The reference to the vertex from an input operand that has not been edited.
  * @param iInputTag
  *   The tag identifying the input operand.
  */
  virtual void UneditedPoints (CATPolyVertex& iResultVertex,
                               const CATPolyVertex& iInputVertex, const CATPolyBody& iInputBody, const int iInputTag) {}

/** @} */

public:
  /** @name Method to help for code factorisation. Not virtual
    @{ */
  inline void End(CATPolyVertex * iVertex, CATPolyBodyOperandCellIterator * iOperandCells) { return EndVertex(iVertex, iOperandCells); };
  inline void End(CATPolyEdge   * iEdge  , CATPolyBodyOperandCellIterator * iOperandCells) { return EndEdge  (iEdge  , iOperandCells); };
  inline void End(CATPolyFace   * iFace  , CATPolyBodyOperandCellIterator * iOperandCells) { return EndFace  (iFace  , iOperandCells); };
  inline void End(CATPolyVolume * iVol   , CATPolyBodyOperandCellIterator * iOperandCells) { return EndVolume(iVol   , iOperandCells); };
/** @} */

public:

  virtual CATPolyBodyUnaryObserver* CastAsUnaryObserver () { return 0; }

  virtual CATPolyBodyBinaryObserver* CastAsBinaryObserver () { return 0; }

};

#endif
