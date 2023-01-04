// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBinaryObserver.h
//
//===================================================================
// November 2015 Creation: ndo
//===================================================================
#ifndef CATPolyBodyBinaryObserver_H
#define CATPolyBodyBinaryObserver_H

#pragma warning( disable : 4275 )

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
class CATPolyCellPointIterator;


/**
 * Observer interface for the binary operators taking in inputs two CATPolyBody operands
 * and producing a CATPolyBody result.
 * This observer maps the cells from the result CATPolyBody to the cells from the input operands.
 */
class ExportedByPolyBodyTools CATPolyBodyBinaryObserver : public CATPolyBodyNaryObserver
{

public:

  virtual ~CATPolyBodyBinaryObserver () {}

public:

/** @name Operand Events
    @{ */

  /**
   * @see CATPolyBodyNaryObserver
   */
  virtual void Begins (CATPolyBodyOperandIterator& iOperands);

  /**
    * Observer call made when a binary operation between two CATPolyBody operands begins.
    * The boolean returned by the method is a request to receive additional notifications  
    * during construction of the vertex, edge or face geometries.
    * @param iPolyBody0
    *   The first CATPolyBody operand.
    * @param iPosition0
    *   The optional position of the first operand.
    * @param iTag0
    *   The tag of the first operand.
    * @param iPolyBody1
    *   The second CATPolyBody operand.
    * @param iPosition1
    *   The optional position of the second operand.
    * @param iTag1
    *   The tag of the second operand.
    */
  virtual void Begins (const CATPolyBody& iPolyBody0, const CATMathTransformation* iPosition0, const int iTag0,
                       const CATPolyBody& iPolyBody1, const CATMathTransformation* iPosition1, const int iTag1) {}

  /**
   * Observer call made when an operation begins.
   * It is called when the operands have no tags or when they are not known by the operator.
   */
  virtual void Begins (const CATPolyBody& iPolyBody0, const CATMathTransformation* iPosition0,
                       const CATPolyBody& iPolyBody1, const CATMathTransformation* iPosition1);

/** @} */

public:

/** @name CATPolyVertex Events
    @{ */

  /**
    * Observer call made at the start of the construction of a new CATPolyVertex.
    * This call is made only if the request has been made (see RequestGeometryEvents ()).
    * Otherwise, only the EndVertex call is made for notification about the construction of a new vertex.
    * @param iCellPoints
    *  An iterator on a set of CATPolyCellPoint from the 2 operands
    */
  virtual void BeginVertex (CATPolyCellPointIterator * iCellPoints);

  /**
    * Observer call made at the start of the construction of a new CATPolyVertex.
    * This call is made only if the request has been made (see RequestGeometryEvents ()).
    * Otherwise, only the EndVertex call is made for notification about the construction of a new vertex.
    * @param iPoint0
    *   When the new vertex refers to a cell from Operand 0, this
    *   argument is the cell-point with reference to the element and its barycentric coordinates.
    *   Otherwise, the argument is null.
    * @param iPoint1
    *   When the new vertex refers to a cell from Operand 1, this
    *   argument is the cell-point with reference to the element and its barycentric coordinates.
    *   Otherwise, the argument is null.
    */
  virtual void BeginVertex (const CATPolyCellPoint* iPoint0, const CATPolyCellPoint* iPoint1) {}

  /**
   * @see CATPolyBodyNaryObserver
   */
  virtual void EndVertex (CATPolyVertex* vertex, CATPolyBodyOperandCellIterator* iOperandCells);

  /**
    * Observer call made at the end of the construction of a new CATPolyVertex.
    * No calls to the MapPolyCells method will be made when this method is implemented.
    * @param vertex
    *   The new CATPolyVertex.
    * @param iCellOperand0
    *   A cell from Operand 0 associated to the new vertex.
    * @param iCellOperand1
    *   A cell from Operand 1 associated to the new vertex.
    */
  virtual void EndVertex (CATPolyVertex* vertex, CATPolyCell* iCellOperand0, CATPolyCell* iCellOperand1);

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
   *   An iterator on a set of CATPolyCellPoint from the 2 operands.
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
    * @param iPoint0
    *   When the point added to the edge refers to a cell from Operand 0, this
    *   argument is the cell-point with reference to the element and its barycentric coordinates.
    *   Otherwise, the argument is null.
    * @param iPoint1
    *   When the point added to the edge refers to a cell from Operand 1, this
    *   argument is the cell-point with reference to the element and its barycentric coordinates.
    *   Otherwise, the argument is null.
    */
  virtual void AppendCurveVertex (const int cv, const CATPolyCellPoint* iPoint0, const CATPolyCellPoint* iPoint1) {}

  /**
   * @see CATPolyBodyNaryObserver
   */
  virtual void EndEdge (CATPolyEdge* edge, CATPolyBodyOperandCellIterator* iOperandCells);

  /**
    * Observer call made at the end of the construction of a new CATPolyEdge.
    * No calls to the MapPolyCells method will be made when this method is implemented.
    * @param edge
    *   The new CATPolyEdge.
    * @param iCellOperand0
    *   A cell from Operand 0 associated to the new edge.
    * @param iCellOperand1
    *   A cell from Operand 1 associated to the new edge.
    */
  virtual void EndEdge (CATPolyEdge* edge, CATPolyCell* iCellOperand0, CATPolyCell* iCellOperand1);

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
   *   An iterator on a set of CATPolyCellPoint from the 2 operands.
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
    * @param iPoint0
    *   When the point added to the face refers to a cell from Operand 0, this
    *   argument is the cell-point with reference to the element and its barycentric coordinates.
    *   Otherwise, the argument is null.
    * @param iPoint1
    *   When the point added to the face refers to a cell from Operand 1, this
    *   argument is the cell-point with reference to the element and its barycentric coordinates.
    *   Otherwise, the argument is null.
    */
  virtual void AddSurfaceVertex (const int sv, const CATPolyCellPoint* iPoint0, const CATPolyCellPoint* iPoint1) {}

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
   * @see CATPolyBodyNaryObserver
   */
  virtual void EndFace (CATPolyFace* face, CATPolyBodyOperandCellIterator* iOperandCells);

  /**
    * Observer call made at the end of the construction of a new CATPolyFace.
    */
  virtual void EndFace (CATPolyFace* face, CATPolyFace* iFaceOperand0, CATPolyFace* iFaceOperand1);

/** @} */

public:

/** @name CATPolyBodyNaryObserver events
    @{ */

  virtual void UneditedSurface (CATPolyFace& iResultFace,
                                const CATPolyFace& iInputFace, const CATPolyBody& iInputBody, const int iInputTag,
                                int iOrientation, const CATMapOfIntToInt* iVertexMap);

  virtual void UneditedCurves (CATPolyEdge& iResultEdge,
                               const CATPolyEdge& iInputEdge, const CATPolyBody& iInputBody, const int iInputTag,
                               int iOrientation);

  virtual void UneditedPoints (CATPolyVertex& iResultVertex,
                               const CATPolyVertex& iInputVertex, const CATPolyBody& iInputBody, const int iInputTag);

/** @} */

public:

  /**
   * Returns the index of the operand in the range 0 to 1
   * The method returns an index out of range if it cannot be determined.
   */
  virtual unsigned int GetIndexOfOperandFromTag (const int iTag) const;

  CATPolyBodyBinaryObserver* CastAsBinaryObserver ();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

protected:

  /**
   * Get the first two poly cell point from the iterator
   * The cell point have to be on each operand (or be null)
   */
  void GetTwoCellPoints(CATPolyCellPointIterator    & iCellPoints   ,
                        CATPolyCellPoint          *   oCellPoints[2]) const;

  /**
   * Get the first two poly cell from the iterator
   * The cell have to be on each operand (or be null)
   */
  void GetTwoOperandCells(CATPolyBodyOperandCellIterator   & iIt     ,
                          CATPolyCell                    *   oCell[2]) const;



  POLY_DEPRECATED ("Include CATPolyBody and tag of operand in list of arguments.",
  virtual void UneditedSurface (CATPolyFace& iResultFace, CATPolyFace& iInputFace,
                                const CATMapOfIntToInt* iVertexMap,
                                unsigned int iOperand01, int iOrientation) {});

  POLY_DEPRECATED ("Include CATPolyBody and tag of operand in list of arguments.",
  virtual void UneditedCurves (CATPolyEdge& iResultEdge, CATPolyEdge& iInputEdge,
                              unsigned int iOperand01, int iOrientation) {});

  POLY_DEPRECATED ("Include CATPolyBody and tag of operand in list of arguments.",
  virtual void UneditedPoints (CATPolyVertex& iResultVertex, CATPolyVertex& iInputVertex, unsigned int iOperand01) {});

protected:

  POLY_DEPRECATED ("Use BeginVertex/EndVertex, BeginEdge/EndEdge and BeginFace/EndFace instead.",
  virtual void MapPolyCells (CATPolyCell* iResultCell, CATPolyCell* iCellOperand0, CATPolyCell* iCellOperand1) {});

#endif

private:
  int _tag[2]; // tag for each operand
};

#endif
