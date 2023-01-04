// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCompactSurfaceVertexLineConst.h
//
//===================================================================
// May 2016  Creation: NDO
//===================================================================
#ifndef CATPolyCompactSurfaceVertexLineConst_H
#define CATPolyCompactSurfaceVertexLineConst_H

#include "PolyMeshImpl.h"
#include "CATPolySurfaceVertexLineBaseConst.h"

class CATIPolySurface;
class CATPolyCompactSurfaceVertexLine;


/**
 * Implementation of a CATIPolySurfaceVertexLine.
 * An instance of a CATPolyCompactSurfaceVertexLineConst is not editable.
 * 
 * @see CATPolyCompactSurfaceVertexLine
 */
class ExportedByPolyMeshImpl CATPolyCompactSurfaceVertexLineConst : public CATPolySurfaceVertexLineBaseConst
{

public:

/** @name Life Cycle
    @{ */

  /** 
   * Creates an empty instance.
   * @param iSurface
   *   The non-editable surface on which lies this surface vertex line.
   *   This surface must be non-editable.
   * The instance must be filled with the help of the methods Initialize () and Finalize ().
   */
  static CATPolyCompactSurfaceVertexLineConst* New (const CATIPolySurface& iSurface);

  /** 
   * Initializes an instance of an editable surface vertex line (CATPolyCompactSurfaceVertexLine) 
   * that can be filled with the data.  After completion of the surface vertex line, the method
   * Finalize () must be called with the same instance.
   * The call to Finalize completes the construction of the compact surface vertex line which can no longer be edited.
   * @param iNbVerticesToAllocate
   *  The number of vertices that will be initially allocated for the SVL.
   * @param iWithVertexWLayer
   *   Optional vertex-w layer.
   * @param iWithVertexTangentLayer
   *   Optional vertex-tangent layer.
   * @return
   *   A new CATIPolySurfaceVertexLine instance or 0 on memory allocation failure.
   *   This instance is to be filled with the data prior to the call to Finalize ().
   *   Do not release the instance returned.
   */
  CATPolyCompactSurfaceVertexLine* Initialize (CATIPolySurface& iSurface, int iNbVerticesToAllocate, 
                                               CATBoolean iWithVertexWLayer, CATBoolean iWithVertexTangentLayer);

  /** 
   * Completes the construction of a CATPolyCompactSurfaceVertexLineConst.
   * @param iMesh
   *   The editable surface vertex line that was returned by the method Initialize.
   *   The editable SVL becomes invalid and is released after this call.
   */
  HRESULT Finalize (CATPolyCompactSurfaceVertexLine*& iSVL);

/** @} */

public:

  CATIPolySurface& GetSurface ();
  const CATIPolySurface& GetSurface () const;

  CATBoolean IsLyingOn (const CATIPolySurface& s) const;

public:

  int GetSurfaceVertex (int v) const;

  HRESULT FindBar (int sv0, int sv1, int& v0, int& v1) const;

public:

  int GetNbVertices () const;

  int GetStartVertex () const;
  int GetEndVertex () const;

  int GetNextVertex (int v) const;
  int GetPrevVertex (int v) const;

  CATBoolean IsClosed () const;

public:

  HRESULT GetVertexIterator (CATIPolyCurveVertexIterator *&oIterator) const;

public:

  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionConstLayer *&oLayer) const;

  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentConstLayer *&oLayer) const;

  HRESULT GetVertexWLayer (CATIPolyCurveVertexWConstLayer *&oLayer) const;

  HRESULT GetSupport (CATIPolySupport*& oSupport) const;

  CATIPolyCurveConstTools* GetConstTools () const;

public:

  HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolyCurveObserver* obs = 0);

  HRESULT RemoveLayer (CATIPolyLayer& iLayer);

  HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  bool HasLayer (const CLSID& id) const;

  HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

public:

/** @name Visitors
    @{ */

  HRESULT Accept (const CATIPolyCurve& iCurve, CATPolyCurveConstVisitor& iVisitor) const;

/** @} */

public:

/** @name Methods specific to this implementation
    @{ */

  /**
   * Returns the native surface support.  
   * Do not delete the support that is returned.
   */
  inline CATIPolySupport* GetNativeSupport () const;

public:

  void DisableSurfaceObserver ();
  void EnableSurfaceObserver ();

/** @} */

public:

  // Deprecated.
  HRESULT GetVertexPosition (const int v, CATMathPoint &oPoint) const;

protected:

  const CATIPolySurface& _Surface;

  int* _SurfaceVertices;
  double* _Ws;
  float* _Tangents;   // Tangents as floats.  Double?
  CATIPolySupport* _Support;

  int _NbVertices;
  unsigned int _Flags;  // Bit flags: see CATPolyCompactSurfaceVertexLine

  friend class CATPolyCompactSVLConstTangentLayer;
  friend class CATPolyCompactSVLConstWLayer;

protected:

  CATPolyCompactSurfaceVertexLineConst (const CATIPolySurface& iSurface);

  virtual ~CATPolyCompactSurfaceVertexLineConst ();

protected:

  /**
   * Finds the curve vertex that refers to the input surface vertex and returns it.
   * @param iSurfaceVertex
   *   The input surface vertex.
   * @return
   *   The curve vertex referring to the surface vertex.
   */
  int FindSurfaceVertex (int sv) const;

};

inline CATIPolySupport* CATPolyCompactSurfaceVertexLineConst::GetNativeSupport () const
{
  return _Support;
}

#endif // !CATPolyCompactSurfaceVertexLineConst_H
