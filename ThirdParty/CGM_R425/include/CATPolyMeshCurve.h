// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshCurve.h
//
//===================================================================
// May 2015  Creation NDO
//===================================================================
#ifndef CATPolyMeshCurve_H
#define CATPolyMeshCurve_H

#include "PolyMeshImpl.h"
#include "CATIPolyMeshCurve.h"
#include "CATPolyMeshPointDef.h"
#include "CATIPolyMeshObserver.h"

#include "CATPolyMeshPointDoublyLinkedList.h"

class CATIPolyMesh;
class CATIPolySurfaceVertexPositionConstLayer;
class CATPolyVector3dDoublyLinkedList;


/**
 * Implementation of a mesh-curve.
 * A mesh-curve is a CATIPolyCurve that lies on a CATIPolyMesh.  Each segment of the curve lies on 
 * a sub-element of the mesh (bar or triangle).
 */
class ExportedByPolyMeshImpl CATPolyMeshCurve : public CATIPolyMeshCurve
{
public:

  /**
   * Construction of a CATPolyMeshCurve.
   * @param mesh
   *   The mesh on which the curve lies.
   * @param iWithWLayer
   *   Optional vertex-W layer.  Currently, the vertex-w layer is not supported.
   * @param iWithTangentLayer
   *   Optional vertex-tangent layer.
   */
  static CATPolyMeshCurve* New (const CATIPolyMesh& mesh, 
                                CATBoolean iWithWLayer = FALSE, CATBoolean iWithTangentLayer = FALSE);

  CATBoolean IsEditable () const;

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolyCurve as a const CATPolyMeshCurve.
   */
  static const CATPolyMeshCurve* Cast (const CATIPolyCurve* C);

  /**
   * Casts a CATIPolyCurve as a CATPolyMeshCurve.
   */
  static CATPolyMeshCurve* Cast (CATIPolyCurve* C);

/** @} */

public:

  inline const CATIPolyMesh& GetMesh () const;

  CATBoolean IsLyingOn (const CATIPolySurface &s) const;

public:

  HRESULT AppendVertex (int& v);

  HRESULT AppendMeshPoint (const CATPolyMeshPointDef& mp, int& v);

  HRESULT UpdateMeshPoint (int v, const CATPolyMeshPointDef& mp);

  HRESULT GetMeshPoint (int v, CATPolyMeshPointDef& oMP) const;

public:

  int GetNbVertices () const;

  HRESULT GetVertexIterator (CATIPolyCurveVertexIterator *&oIterator) const;

  int GetStartVertex () const;
  int GetEndVertex () const;

  int GetNextVertex (int v) const;
  int GetPrevVertex (int v) const;

public:

  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionConstLayer *&oLayer) const;
  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionLayer *&oLayer);

  HRESULT GetVertexWLayer (CATIPolyCurveVertexWConstLayer *&oLayer) const;
  HRESULT GetVertexWLayer (CATIPolyCurveVertexWLayer *&oLayer);

  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentConstLayer *&oLayer) const;
  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentLayer *&oLayer);

  HRESULT SetSupport (CATIPolySupport* iSupport);
  HRESULT GetSupport (CATIPolySupport*& oSupport) const;

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

  HRESULT RegisterObserver (CATIPolyCurveObserver &iObserver);
  HRESULT UnregisterObserver (CATIPolyCurveObserver &iObserver);

  HRESULT Accept (const CATIPolyCurve& iCurve, CATPolyCurveConstVisitor& iVisitor) const;
  HRESULT Accept (CATIPolyCurve& iCurve, CATPolyCurveVisitor& iVisitor);

  CATIPolyCurveConstTools* GetConstTools () const;
  CATIPolyCurveTools* GetTools ();

private:

  // Copy constructor/operator are forbidden.
  CATPolyMeshCurve (const CATPolyMeshCurve& iRHS);
  CATPolyMeshCurve& operator= (const CATPolyMeshCurve& iRHS);

private:

#if 0
  /**
   * Observer class of CATIPolyMesh events.
   * This observer class is registered with the parent mesh.
   */
  class MeshObserver : public CATIPolyMeshObserver
  {

  public:

    MeshObserver (CATPolyMeshCurve& iMC) : _MC (iMC) {}
    ~MeshObserver () {}

  public:
  
    HRESULT ReactToSetVertexPosition (int sv, const CATMathPoint& iPoint);

    HRESULT ReactToSplitBar (int sv0, int sv1, int svn);

    HRESULT PrepareToMergeVertices (int sv0, int sv1);

  public:

    CATPolyMeshCurve& _MC;

  };

  void DisableMeshObserver ();
  void EnableMeshObserver ();
#endif

protected:

  /**
   * Definition of various bit flags.
   */
  enum Masks
  {
    /** Bit 0: Closed CATPolyMeshCurve. */              MaskClosed         = 0x0001
  };

protected:

  const CATIPolyMesh& _Mesh;
  //MeshObserver* _MeshObserver;
  CATIPolyCurveObserver *_Observer;

  mutable CATIPolySurfaceVertexPositionConstLayer* _MeshPosLayer;
  CATPolyMeshPointDoublyLinkedList _MeshPoints;
  CATPolyVector3dDoublyLinkedList* _Tangents;
    
  unsigned int _Flags;  // Bit flags.

  //friend class CATPolyMeshCurveTangentLayer;
  //friend class CATPolyMeshCurveWLayer;

  friend class CATPolyMeshCurveConst;

private:

  CATPolyMeshCurve (const CATIPolyMesh& mesh);
  virtual ~CATPolyMeshCurve ();

public:

/** @name Deprecated methods.
    @{ */

  // Does not do anything and returns S_FALSE.
  HRESULT AppendVertex (const CATMathPoint& P, int& v);

  // Deprecated.
  HRESULT GetVertexPosition (const int v, CATMathPoint &oPoint) const;

  // Deprecated.
  HRESULT SetVertexPosition (const int v, const CATMathPoint &P);

/** @} */

};

inline const CATIPolyMesh& CATPolyMeshCurve::GetMesh () const
{
  return _Mesh;
}

#endif // !CATPolyMeshCurve_H
