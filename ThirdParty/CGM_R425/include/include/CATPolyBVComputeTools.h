// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVComputeTools.h
//
//===================================================================
// May 2009  Creation: JS9
//===================================================================
#ifndef CATPolyBVComputeTools_H
#define CATPolyBVComputeTools_H

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathPoint.h"
#include "PolyMathBV.h"

class CATMathTransformation;
class CATMathOBBBase;
class CATPolyAABB;
class CATPolyOBB;
class CATPolyBoundingSphere;
class CATMathBox;


/**
 * Services to compute Bounding Volumes including:
 * <ul>
 *   <li> Bounding Sphere
 *   <li> AABB
 *   <li> OBB
 * </ul>
 */
class ExportedByPolyMathBV CATPolyBVComputeTools
{

public:

  /**
   * Iterator on a set of points.
   */
  class VertexCoordIterator
  {
  public:

    VertexCoordIterator() {}
    virtual ~VertexCoordIterator() {}

    virtual void Begin() = 0;

    virtual CATBoolean End() const = 0;

    virtual void operator++() = 0;

    virtual HRESULT Get(CATMathPoint & point) const = 0;
  };

  /**
   * Implementation of VertexCoordsIterator cycling along an array.
   */
  class VertexCoordsIteratorFromArray : public VertexCoordIterator
  {
  public:
    VertexCoordsIteratorFromArray(const CATMathPoint pointArray[], int nbPoints) : VertexCoordIterator()
    {
      _aPointArray = pointArray;
      _iNbVertices = nbPoints;
    }

    virtual ~VertexCoordsIteratorFromArray() {_aPointArray = NULL;}

    virtual void Begin() {_iCurVertex = 0;}

    virtual CATBoolean End() const {return _iCurVertex >= _iNbVertices;}

    virtual void operator++() {_iCurVertex++;}

    virtual HRESULT Get(CATMathPoint & point) const {point = _aPointArray[_iCurVertex]; return S_OK;}


  private:
    const CATMathPoint * _aPointArray;
    int _iNbVertices;
    int _iCurVertex;
  };


  /**
   * Compute an OBB from a point cloud.
   * @param iCoordsIterator iterator on the point coordinates
   * @param iPos if not NULL addtional position to apply on the points.
   * @param oOBB result of the computation.
   * @param oAABB if not NULL the function also compute the AABB of the point cloud.
   */
  static HRESULT ComputeOBB(VertexCoordIterator & iCoordsIterator, const CATMathTransformation * iPos,
                            CATPolyOBB & oOBB, CATPolyAABB * oAABB = NULL);

  /**
   * Compute an AABB from a point cloud.
   * @param iCoordsIterator iterator on the point coordinates
   * @param iPos if not NULL addtional position to apply on the points.
   * @param oAABB result of the computation.
   */
  static HRESULT ComputeAABB(VertexCoordIterator & iCoordsIterator, const CATMathTransformation * iPos,
                             CATPolyAABB & oAABB);

  /**
   * Compute a Sphere from a point cloud.
   * @param iCoordsIterator iterator on the point coordinates
   * @param iPos if not NULL addtional position to apply on the points.
   * @param oSphere result of the computation.
   */
  static HRESULT ComputeSphere(VertexCoordIterator & iCoordsIterator, const CATMathTransformation * iPos,
                               CATPolyBoundingSphere & oSphere);

  /**
   * Compute an OBB from a point cloud.
   * @param iCoordsIterator iterator on the point coordinates
   * @param iPos if not NULL addtional position to apply on the points.
   * @param oOBB result of the computation.
   * @param oAABB if not NULL the function also compute the AABB of the point cloud.
   */
  static HRESULT ComputeOBB(VertexCoordIterator & iCoordsIterator, const CATMathTransformation * iPos,
                            CATMathOBBBase & oOBB, CATMathBox * oAABB = NULL);

  /**
   * Compute an AABB from a point cloud.
   * @param iCoordsIterator iterator on the point coordinates
   * @param iPos if not NULL addtional position to apply on the points.
   * @param oAABB result of the computation.
   */
  static HRESULT ComputeAABB(VertexCoordIterator & iCoordsIterator, const CATMathTransformation * iPos,
                            CATMathBox & oAABB);

  /**
   * Compute a sphere from a CATMathBox
   */
  static HRESULT ComputeSphereFromBox(const CATMathBox & iBoux, CATPolyBoundingSphere & oSphere, const CATMathTransformation * iPos = NULL);

private:

  /**
   * Not to be used
   */
  CATPolyBVComputeTools() {}
  ~CATPolyBVComputeTools() {}

};

#endif /* CATPolyBVComputeTools */
