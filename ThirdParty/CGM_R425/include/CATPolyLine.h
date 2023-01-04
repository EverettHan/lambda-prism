//=============================================================================
// COPYRIGHT Dassault Systemes 2006
//=============================================================================
//
// CATPolyLine.h
//
//=============================================================================
// 2006-11-15   BPG: New
//=============================================================================
#ifndef CATPolyLine_H
#define CATPolyLine_H

#include "PolyMeshImpl.h"
#include "CATIPolyCurve.h"

#include "CATPolyVector3dDoublyLinkedList.h"

class CATPolyDoubleDoublyLinkedList;
class CATIPolyVertexFloatPositionConstLayer;

#include "CATLISTV_CATMathPoint.h"
typedef CATLISTV(CATMathPoint) CATMathPointList;


/**
 * Implementation of a poly-line.
 * A poly-line is defined by a series of points in space.
 */
class ExportedByPolyMeshImpl CATPolyLine : public CATIPolyCurve
{

public:

  /**
   * Creates an instance of a CATPolyLine.
   * @param iFloatOrDouble
   *   Precision of the vertex position layer: Poly::Precision::eFloat or Poly::Precision::eDouble.
   * @param iWithWLayer
   *   Optional vertex-W layer.
   * @param iWithTangentLayer
   *   Optional vertex-tangent layer.
   */
#ifndef _AIX_SOURCE
  static CATPolyLine* New (Poly::Precision iFloatOrDouble,
    CATBoolean iWithWLayer = FALSE, CATBoolean iWithTangentLayer = FALSE);
#else
  static CATPolyLine* New (PrecisionVertexPosition iFloatOrDouble,
    CATBoolean iWithWLayer = FALSE, CATBoolean iWithTangentLayer = FALSE);
#endif

  /**
   * @deprecated
   */
  static CATPolyLine* New (CATBoolean iWithWLayer, CATBoolean iWithTangentLayer)
    {return New ((PrecisionVertexPosition) Poly::Precision::eDouble, iWithWLayer, iWithTangentLayer);}

  CATBoolean IsEditable () const;

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolyCurve as a const CATPolyLine.
   */
  static const CATPolyLine* Cast (const CATIPolyCurve* C);

  /**
   * Casts a CATIPolyCurve as a CATPolyLine.
   */
  static CATPolyLine* Cast (CATIPolyCurve* C);

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

  HRESULT GetVertexPositionLayer (CATIPolyVertexFloatPositionConstLayer*& oLayer) const;

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

  HRESULT RegisterObserver(CATIPolyCurveObserver &iObserver);
  HRESULT UnregisterObserver(CATIPolyCurveObserver &iObserver);

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

  /**
   * Returns the native surface support.  
   * Do not release the support that is returned.
   */
  inline CATIPolySupport* GetNativeSupport () const;

private:

  // No copy constructor and assignment operator allowed.
  CATPolyLine (const CATPolyLine &iRHS);
  CATPolyLine& operator= (const CATPolyLine &iRHS);

protected:

  /**
   * Definition of various bit flags.
   */
  enum Masks
  {
    /** Bit 0: Closed CATPolyLine. */                   MaskClosed         = 0x0001,
    /** Bit 1: Vertex position layer in float. */       MaskVertexFloat    = 0x0002,
    /** Bit 2: Vertex position layer in double. */      MaskVertexDouble   = 0x0004
  };

protected:

  CATIPolyCurveObserver* _Observer;

  CATPolyVector3dDoublyLinkedList _Positions;
  CATPolyDoubleDoublyLinkedList *_Ws;
  CATPolyVector3dDoublyLinkedList *_Tangents;

  CATIPolySupport* _Support;
    
  unsigned int _Flags;  // Bit flags.

  friend class CATPolyLineTangentLayer;
  friend class CATPolyLineWLayer;

  friend class CATPolyLineConst;

public:  // Should be protected.
//protected:

  // Do not call.
  CATPolyLine ();

  // Do not call this constructor.
  // Use instead CATPolyCreatePolyLine in CATPolyDefaultCurveServices.h
  // @see CATPolyCreatePolyLine
  CATPolyLine (const CATMathPointList &iPoints);

  virtual ~CATPolyLine();

protected:

  // Protected constructor.
  // Use static New methods.
  CATPolyLine (PolyPrecision iFloatOrDouble);

public:

/** @name Deprecated methods.
    @{ */

  // Deprecated.
  HRESULT GetVertexPosition (const int v, CATMathPoint& P) const;

  // Deprecated.
  HRESULT SetVertexPosition (const int v, const CATMathPoint& P);

/** @} */

};


inline CATIPolySupport* CATPolyLine::GetNativeSupport () const
{
  return _Support;
}

#endif // !CATPolyLine_H
