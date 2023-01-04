// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyLineConst.h
//
//===================================================================
// June 2016  Creation: NDO
//===================================================================
#ifndef CATPolyLineConst_H
#define CATPolyLineConst_H

#include "PolyMeshImpl.h"
#include "CATPolyCurveBaseConst.h"

#include "CATPolyVector3dDoublyLinkedList.h"

class CATPolyLine;
class CATPolyDoubleDoublyLinkedList;
class CATIPolyVertexFloatPositionConstLayer;

#include "CATLISTV_CATMathPoint.h"
typedef CATLISTV(CATMathPoint) CATMathPointList;


/**
 * Implementation of a poly-line.
 * A poly-line is defined by a series of points in space.
 * An instance of a CATPolyLineConst is not editable.
 *
 * @see CATPolyLine
 */
class ExportedByPolyMeshImpl CATPolyLineConst : public CATPolyCurveBaseConst
{

public:

/** @name Life Cycle
    @{ */

  /** 
   * Creates an empty instance.
   * The instance must be filled with the help of the methods Initialize () and Finalize ().
   */
  static CATPolyLineConst* New ();

  /**
   * Initializes an instance of an editable CATPolyLine that can be filled with the data.
   * @param iFloatOrDouble
   *   Precision of the vertex position layer: Poly::Precision::eFloat or Poly::Precision::eDouble.
   * @param iWithVertexWLayer
   *   Optional vertex-w layer.
   * @param iWithVertexTangentLayer
   *   Optional vertex-tangent layer.
   */
#ifndef _AIX_SOURCE
  CATPolyLine* Initialize (Poly::Precision iFloatOrDouble,
    CATBoolean iWithVertexWLayer = FALSE, CATBoolean iWithVertexTangentLayer = FALSE);
#else
  CATPolyLine* Initialize (PrecisionVertexPosition iFloatOrDouble,
    CATBoolean iWithVertexWLayer = FALSE, CATBoolean iWithVertexTangentLayer = FALSE);
#endif

  /** 
   * Completes the construction of a CATPolyLineConst.
   * @param iPolyLine
   *   The editable poly-line that was returned by the method Initialize.
   *   The editable poly-line becomes invalid and is released after this call.
   */
  HRESULT Finalize (CATPolyLine*& iPolyLine);

/** @} */

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolyCurve as a const CATPolyLine.
   */
  static const CATPolyLineConst* Cast (const CATIPolyCurve* C);

  /**
   * Casts a CATIPolyCurve as a CATPolyLine.
   */
  static CATPolyLineConst* Cast (CATIPolyCurve* C);

/** @} */

public:

/** @name Vertices 
    @{ */

  int GetNbVertices () const;

  HRESULT GetVertexIterator (CATIPolyCurveVertexIterator*& oIterator) const;

  int GetStartVertex () const;
  int GetEndVertex () const;

  int GetNextVertex (int v) const;
  int GetPrevVertex (int v) const;

/** @} */

public:

/** @name Const Layers
    @{ */

  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionConstLayer*& oLayer) const;
  HRESULT GetVertexWLayer (CATIPolyCurveVertexWConstLayer*& oLayer) const;
  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentConstLayer*& oLayer) const;
  HRESULT GetSupport (CATIPolySupport*& oSupport) const;

  HRESULT GetVertexPositionLayer (CATIPolyVertexFloatPositionConstLayer*& oLayer) const;

  CATBoolean IsClosed () const;

/** @} */

public:

  virtual HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolyCurveObserver* obs = 0);

  virtual HRESULT RemoveLayer (CATIPolyLayer& iLayer);

  virtual HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  virtual bool HasLayer (const CLSID& id) const;

  virtual HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  virtual HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

public:

  HRESULT Accept (const CATIPolyCurve& iCurve, CATPolyCurveConstVisitor& iVisitor) const;

  CATIPolyCurveConstTools* GetConstTools () const;

public:

  /**
   * Returns the native surface support.  
   * Do not release the support that is returned.
   */
  inline CATIPolySupport* GetNativeSupport () const;

private:

  // No copy constructor and assignment operator allowed.
  CATPolyLineConst (const CATPolyLineConst &iRHS);
  CATPolyLineConst& operator= (const CATPolyLineConst &iRHS);

protected:

  CATPolyVector3dDoublyLinkedList _Positions;
  CATPolyDoubleDoublyLinkedList* _Ws;
  CATPolyVector3dDoublyLinkedList* _Tangents;

  CATIPolySupport* _Support;
    
  unsigned int _Flags;  // Bit flags.

  friend class CATPolyLineConstTangentConstLayer;
  friend class CATPolyLineConstWConstLayer;

protected:

  // Protected constructor.
  // Use New method.
  CATPolyLineConst ();

  virtual ~CATPolyLineConst ();

public:

  // Deprecated.
  HRESULT GetVertexPosition (const int v, CATMathPoint& P) const;

};


inline CATIPolySupport* CATPolyLineConst::GetNativeSupport () const
{
  return _Support;
}

#endif // !CATPolyLineConst_H
