// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyUnaryObserver.h
//
//===================================================================
// June 2016 Creation: ndo
// May  2018 Modif JXO: deprecated MapPolyCells
//===================================================================
#ifndef CATPolyBodyUnaryObserver_H
#define CATPolyBodyUnaryObserver_H

#include "PolyBodyTools.h"
#include "CATErrorDef.h"   // For the definition of HRESULT.
#include "CATPolyBodyNaryObserver.h"
#include "CATPolyDeprecated.h"

class CATPolyBody;
class CATPolyCell;
class CATPolyFace;
class CATPolyEdge;
class CATPolyVertex;
class CATMapOfIntToInt;
class CATMathTransformation;
class CATPolyCellPoint;


/**
 * Observer interface for the unary operators taking in input a CATPolyBody operand
 * and producing a CATPolyBody result.
 * This observer maps the cells from the result CATPolyBody to the cells from the input operand.
*/
class ExportedByPolyBodyTools CATPolyBodyUnaryObserver : public CATPolyBodyNaryObserver
{

public:

  virtual ~CATPolyBodyUnaryObserver () {}

public:

/** @name Operand Events
    @{ */

  /**
   * @see CATPolyBodyNaryObserver
   */
  virtual void Begins (CATPolyBodyOperandIterator& it);

  /**
    * Observer call made when an operation begins.
    * @param iOperand
    *   The CATPolyBody operand.
    * @param iPosition
    *   The optional position of the operand.
    * @param iTag
    *   The tag of the operand.
    */
  virtual void Begins (const CATPolyBody& iOperand, const CATMathTransformation* iPosition, const int iTag) {}

  /**
   * Observer call made when an operation begins.
   * It is called when the operand has no tag or when it is not known by the operator.
   */
  virtual void Begins (const CATPolyBody& iPolyBody, const CATMathTransformation* iPosition);

/** @} */

public:

/** @name CATPolyVertex Events
    @{ */

    /**
      * Observer call made at the start of the construction of a new CATPolyVertex.
      * This call is made only if the request has been made (see RequestGeometryEvents ()).
      * Otherwise, only the EndVertex call is made for notification about the construction of a new vertex.
      * @param iCellPoints
      *  An iterator on a set of CATPolyCellPoint from the operand
      */
    virtual void BeginVertex (CATPolyCellPointIterator * iCellPoints);

    /**
     * Observer call made at the start of the construction of a new CATPolyVertex.
     * This call is made only if the request has been made (see RequestGeometryEvents ()).
     * Otherwise, only the EndVertex call is made for notification about the construction of a new vertex.
     * @param iPoint
     *   The cell-point is a reference to the input element and its barycentric coordinates.
     */
    virtual void BeginVertex (const CATPolyCellPoint* iPoint) {}

    /**
     * @see CATPolyBodyNaryObserver
     */
    virtual void EndVertex (CATPolyVertex* vertex, CATPolyBodyOperandCellIterator* iOperandCells);

    /**
     * Observer call made at the end of the construction of a new CATPolyVertex.
     * No calls to the MapPolyCells method will be made when this method is implemented.
     * @param vertex
     *   The new CATPolyVertex.
     * @param iCellOperand
     *   A cell from the input operand associated to the new vertex.
     */
    virtual void EndVertex (CATPolyVertex* vertex, CATPolyCell* iCellOperand);

/** @} */

public:

/** @name CATPolyEdge Events
    @{ */

    /**
     * Call made each time a curve-vertex is added to the underlying edge geometry in sequence from start to end.
     * It provides the references to elements (triangles, bars, cell-vertex) from the input operands with 
     * the barycentric coordinates of the point on these elements. 
     * This call is made only if the request has been made (see RequestGeometryEvents ()).
     * @param cv
     *   The index of the curve-vertex that has just been appended.
     * @param iCellPoints
     *   An iterator on a set of CATPolyCellPoint from the operand.
     *   The cell-points are a reference to the input element and its barycentric coordinates.
     */
    virtual void AppendCurveVertex (const int cv, CATPolyCellPointIterator * iCellPoints);

    /**
     * Call made each time a curve-vertex is added to the underlying edge geometry in sequence from start to end.
     * It provides the references to elements (triangles, bars, cell-vertex) from the input operands with 
     * the barycentric coordinates of the point on these elements. 
     * This call is made only if the request has been made (see RequestGeometryEvents ()).
     * @param cv
     *   The index of the curve-vertex that has just been appended.
     * @param iPoint
     *   The cell-point is a reference to the input element and its barycentric coordinates.
     */
    virtual void AppendCurveVertex (const int cv, const CATPolyCellPoint* iPoint) {}

    /**
     * @see CATPolyBodyNaryObserver
     */
    virtual void EndEdge (CATPolyEdge* edge, CATPolyBodyOperandCellIterator* iOperandCells);

    /**
     * Observer call made at the end of the construction of a new CATPolyEdge.
     * No calls to the MapPolyCells method will be made when this method is implemented.
     * @param edge
     *   The new CATPolyEdge.
     * @param iCellOperand
     *   A cell from the input operand associated to the new edge.
     */
    virtual void EndEdge (CATPolyEdge* edge, CATPolyCell* iCellOperand);

/** @} */

public:

/** @name CATPolyFace Events
    @{ */

  /**
   * Call made each time a surface-vertex is added to the underlying face geometry.
   * It provides the references to elements (triangles, bars, cell-vertex) from the input operands with 
   * the barycentric coordinates of the point on these elements. 
   * This call is made only if the request has been made (see RequestGeometryEvents ()).
   * @param sv
   *   The index of the surface-vertex that was added.
   * @param iCellPoints
   *   An iterator on a set of CATPolyCellPoint from the operand.
   *   The cell-points are a reference to the input element and its barycentric coordinates.
   */
  virtual void AddSurfaceVertex (const int sv, CATPolyCellPointIterator * iCellPoints);

  /**
    * Call made each time a surface-vertex is added to the underlying face geometry.
    * It provides the references to elements (triangles, bars, cell-vertex) from the input operands with 
    * the barycentric coordinates of the point on these elements. 
    * This call is made only if the request has been made (see RequestGeometryEvents ()).
    * @param sv
    *   The index of the surface-vertex that was added.
    * @param iPoint
    *   When the point added to the face refers to a cell from Operand 0, this
    *   argument is the cell-point with reference to the element and its barycentric coordinates.
    *   Otherwise, the argument is null.
    */
  virtual void AddSurfaceVertex (const int sv, const CATPolyCellPoint* iPoint) {}

  /**
    * Call made each time a triangle is added to the underlying face geometry.
    * It provides the reference to a triangle of a face from the input operand.
    * This call is made only if the request has been made (see RequestGeometryEvents ()).
    * @param t
    *   The index of the triangle that was added.
    * @param iFace
    *   The parent face from the input operand.
    *   The argument may be null if the triangle does not refer to any parent face.
    * @param iFaceTriangle
    *   The triangle from the parent face to which the new triangle refers.
    */
  virtual void AddTriangle (const int t, CATPolyFace* iFace, const int iFaceTriangle) {}

  /**
    * @see CATPolyBodyNaryObserver
    */
  virtual void EndFace (CATPolyFace* face, CATPolyBodyOperandCellIterator* iOperandCells);

  /**
    * Observer call made at the end of the construction of a new CATPolyFace.
    * (What about multiplicity? -NDO)
    * @param face
    *   The new CATPolyFace.
    * @param iFaceOperand
    *   A face from the input operand associated to the new face.
    */
  virtual void EndFace (CATPolyFace* face, CATPolyFace* iFaceOperand);

/** @} */

public:

/** @name CATPolyBodyNaryObserver events
  @{ */

  virtual void UneditedSurface (CATPolyFace& iResultFace, 
                                const CATPolyFace& iInputFace, const CATPolyBody& iInputBody, const int iInputTag,
                                int iOrientation, const CATMapOfIntToInt* iVertexMap);

  virtual void UneditedCurves (CATPolyEdge& iResultEdge, 
                               const CATPolyEdge& iInputEdge, const CATPolyBody& iInputBody, const int iInputTag,
                               int iOrientation) ;

  virtual void UneditedPoints (CATPolyVertex& iResultVertex, 
                               const CATPolyVertex& iInputVertex, const CATPolyBody& iInputBody, const int iInputTag);

/** @} */

public:

  CATPolyBodyUnaryObserver* CastAsUnaryObserver ();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

protected:

  POLY_DEPRECATED ("Include CATPolyBody and tag of operand in list of arguments.",
  virtual void UneditedSurface (CATPolyFace& iResultFace, CATPolyFace& iInputFace,
                                const CATMapOfIntToInt* iVertexMap, int iOrientation) {});

  POLY_DEPRECATED ("Include CATPolyBody and tag of operand in list of arguments.",
  virtual void UneditedCurves (CATPolyEdge& iResultEdge, CATPolyEdge& iInputEdge, int iOrientation) {});

  POLY_DEPRECATED ("Include CATPolyBody and tag of operand in list of arguments.",
  virtual void UneditedPoints (CATPolyVertex& iResultVertex, CATPolyVertex& iInputVertex) {});

protected:

  POLY_DEPRECATED("Use BeginVertex/EndVertex, BeginEdge/EndEdge and BeginFace/EndFace instead.", 
  virtual void MapPolyCells (CATPolyCell* iResultCell, CATPolyCell* iCellOperand) {});

#endif

};

#endif
