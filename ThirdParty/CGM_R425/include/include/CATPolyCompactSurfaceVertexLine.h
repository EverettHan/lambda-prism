//=============================================================================
// COPYRIGHT Dassault Systemes 2006
//=============================================================================
//
// CATPolyCompactSurfaceVertexLine.h
//
//=============================================================================
// 2010-03-15   ZFI: New
// 2014-10-09   JXO: Observers
// 2014-12-03   NDO: Optimization, Surface Observer
// 2015-09-08   NDO: Replace float W layer by double W layer
// November 2015  NDO: Renamed from CATPolyPreAllocatedMesh, 
//                     Constructor with surface observer.
//=============================================================================
#ifndef CATPolyCompactSurfaceVertexLine_H
#define CATPolyCompactSurfaceVertexLine_H

#include "PolyMeshImpl.h"
#include "CATPolySurfaceVertexLineBase.h"
#include "CATPolyCurveObserverList.h"
#include "CATIPolySurfaceObserver.h"

class CATIPolySurface;


/**
 * Implementation of a CATIPolySurfaceVertexLine.
 */
class ExportedByPolyMeshImpl CATPolyCompactSurfaceVertexLine : public CATPolySurfaceVertexLineBase
{

public:

/** @name Life Cycle
    @{ */

  /** 
   * Creates an instance of CATPolyCompactSurfaceVertexLine with 
   * optional vertex W and tangent layers.
   * @param iNbVerticesToAllocate
   *  The number of vertices that will be initially allocated for the SVL.
   * @param iWithVertexWLayer
   *   Optional vertex-w layer.
   * @param iWithVertexTangentLayer
   *   Optional vertex-tangent layer.
   */
  static CATPolyCompactSurfaceVertexLine* New (CATIPolySurface& iSurface, int NbVerticesToAllocate, 
                                               CATBoolean iWithVertexWLayer, CATBoolean iWithVertexTangentLayer);

/** @} */

public:

  CATIPolySurface& GetSurface ();
  const CATIPolySurface& GetSurface () const;

  CATBoolean IsLyingOn (const CATIPolySurface& s) const;

public:

  HRESULT AppendSurfaceVertex (int sv, int& v);
  HRESULT InsertSurfaceVertex (int sv, int vn, int& v);

  int GetSurfaceVertex (int v) const;

  HRESULT FindBar (int sv0, int sv1, int& v0, int& v1) const;

public:

  HRESULT AppendVertex (int &v);

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
  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionLayer *&oLayer);

  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentConstLayer *&oLayer) const;
  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentLayer *&oLayer);

  HRESULT GetVertexWLayer (CATIPolyCurveVertexWConstLayer *&oLayer) const;
  HRESULT GetVertexWLayer (CATIPolyCurveVertexWLayer *&oLayer);

  HRESULT SetSupport (CATIPolySupport* iSupport);
  HRESULT GetSupport (CATIPolySupport*& oSupport) const;

  CATIPolyCurveConstTools* GetConstTools () const;
  CATIPolyCurveTools* GetTools ();

public:

  HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolyCurveObserver* obs = 0);

  HRESULT RemoveLayer (CATIPolyLayer& iLayer);

  HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  bool HasLayer (const CLSID& id) const;

  HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

public:

  HRESULT Close ();
  HRESULT Open ();

public:

  HRESULT RegisterObserver (CATIPolyCurveObserver &iObserver);
  HRESULT UnregisterObserver (CATIPolyCurveObserver &iObserver);

  HRESULT Accept (const CATIPolyCurve& iCurve, CATPolyCurveConstVisitor& iVisitor) const;
  HRESULT Accept (CATIPolyCurve& iCurve, CATPolyCurveVisitor& iVisitor);

public:

/** @name Methods specific to this implementation
    @{ */

  // Return the native surface support.  Do not delete the support that is returned.
  inline CATIPolySupport* GetNativeSupport () const;

public:

  void DisableSurfaceObserver ();
  void EnableSurfaceObserver ();

/** @} */

public:

  // Deprecated.
  HRESULT AppendVertex (const CATMathPoint &P, int &v);

  // Deprecated.
  HRESULT GetVertexPosition (const int v, CATMathPoint &oPoint) const;
  HRESULT SetVertexPosition (const int v, const CATMathPoint &P);

private:

  // No copy constructor and assignment operator allowed.
  CATPolyCompactSurfaceVertexLine (const CATPolyCompactSurfaceVertexLine &iRHS);
  CATPolyCompactSurfaceVertexLine& operator= (const CATPolyCompactSurfaceVertexLine &iRHS);

private:

  /**
   * Observer class of CATIPolySurface events.
   * This observer class is registered with the surface if and only if the surface vertex line
   * is not attached to an edge.
   */
  class SurfaceObserver : public CATIPolySurfaceObserver
  {

  public:

    SurfaceObserver (CATPolyCompactSurfaceVertexLine& iSVL) : _SVL (iSVL) {}
    ~SurfaceObserver () {}

  public:
  
    HRESULT ReactToSetVertexPosition (int sv, const CATMathPoint& iPoint);

  public:

    CATPolyCompactSurfaceVertexLine& _SVL;

  };

protected:

  CATIPolySurface& _Surface;

  int* _SurfaceVertices;
  double* _Ws;        // Replaced by double, September 8, 2015, -NDO
  float* _Tangents;   // Tangents as floats.  Double?

  CATIPolySupport* _Support;
  CATIPolySurfaceObserver* _SurfaceObserver;

  CATPolyCurveObserverList _SVLObservers;  // List of observers of the CATIPolySurfaceVertexLine.

  int _NbVertices;
  int _NbAllocatedVertices;

  /**
   * Definition of various bit flags.
   */
  enum Masks
  {
    /** Bit 0: Bounding box ok. */                      MaskBoundingBoxOK            = 0x0001,
    /** Bit 1: Vertex position layer in float. */       MaskVertexFloat              = 0x0002,
    /** Bit 2: Vertex position layer in double. */      MaskVertexDouble             = 0x0004,
    /** Bit 3: Curve is closed. */                      MaskClosed                   = 0x0008,
    /** Bit 4: Surface observer suspended. */           MaskSurfaceObserverSuspended = 0x0010
  };

  unsigned int _Flags;      // Bit flags.
  unsigned int _Disabled;   // Incremented/decremented each time the surface observer is disabled/enabled.

  friend class CATPolyCompactSVLVertexPositionLayer;
  friend class CATPolyCompactSVLTangentLayer;
  friend class CATPolyCompactSVLWLayer;

  friend class CATPolyCompactSurfaceVertexLineConst;

protected:

  CATPolyCompactSurfaceVertexLine (CATIPolySurface& iSurface);

  virtual ~CATPolyCompactSurfaceVertexLine ();

protected:

  /**
   * Finds the curve vertex that refers to the input surface vertex and returns it.
   * @param iSurfaceVertex
   *   The input surface vertex.
   * @return
   *   The curve vertex referring to the surface vertex.
   */
  int FindSurfaceVertex (int sv) const;

  HRESULT SetPositionLocal (int cv, const CATMathPoint& P);

};

inline CATIPolySupport* CATPolyCompactSurfaceVertexLine::GetNativeSupport () const
{
  return _Support;
}

#endif // !CATPolyCompactSurfaceVertexLine_H
