// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshCurveConst.h
//
//===================================================================
// June 2016  Creation NDO
//===================================================================
#ifndef CATPolyMeshCurveConst_H
#define CATPolyMeshCurveConst_H

#include "PolyMeshImpl.h"
#include "CATIPolyMeshCurve.h"
#include "CATPolyMeshPointDef.h"

#include "CATPolyMeshPointDoublyLinkedList.h"

class CATIPolyMesh;
class CATIPolySurfaceVertexPositionConstLayer;
class CATPolyVector3dDoublyLinkedList;
class CATPolyMeshCurve;


/**
 * Implementation of a mesh-curve.
 * A mesh-curve is a CATIPolyCurve that lies on a CATIPolyMesh.  Each segment of the curve lies on 
 * a sub-element of the mesh (bar or triangle).
 * An instance of a CATPolyMeshCurveConst is not editable.
 *
 * @see CATPolyMeshCurve
 */
class ExportedByPolyMeshImpl CATPolyMeshCurveConst : public CATIPolyMeshCurve
{

public:

/** @name Life Cycle
    @{ */

  /** 
   * Creates an empty instance.
   * @param mesh
   *   The non-editable mesh on which the curve lies.
   *   This mesh must be non-editable.
   * The instance must be filled with the help of the methods Initialize () and Finalize ().
   */
  static CATPolyMeshCurveConst* New (const CATIPolyMesh& mesh);

  /**
   * Creates an instance of a CATPolyMeshCurve.
   * @param mesh
   *   The mesh on which the editable mesh-curve lies.
   * @param iWithWLayer
   *   Optional vertex-W layer.  Currently, the vertex-w layer is not supported.
   * @param iWithTangentLayer
   *   Optional vertex-tangent layer.
   */
  CATPolyMeshCurve* Initialize (const CATIPolyMesh& mesh,
                                CATBoolean iWithWLayer = FALSE, CATBoolean iWithTangentLayer = FALSE);

  /** 
   * Completes the construction of a CATPolyMeshCurveConst.
   * @param iMeshCurve
   *   The editable mesh-curve that was returned by the method Initialize.
   *   The editable mesh-curve becomes invalid and is released after this call.
   */
  HRESULT Finalize (CATPolyMeshCurve* iMeshCurve);

  CATBoolean IsEditable () const;

/** @} */

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolyCurve as a const CATPolyMeshCurveConst.
   */
  static const CATPolyMeshCurveConst* Cast (const CATIPolyCurve* C);

  /**
   * Casts a CATIPolyCurve as a CATPolyMeshCurveConst.
   */
  static CATPolyMeshCurveConst* Cast (CATIPolyCurve* C);

/** @} */

public:

  inline const CATIPolyMesh& GetMesh () const;

  CATBoolean IsLyingOn (const CATIPolySurface &s) const;

public:

  HRESULT GetMeshPoint (int v, CATPolyMeshPointDef& oMP) const;

  int GetNbVertices () const;

  HRESULT GetVertexIterator (CATIPolyCurveVertexIterator *&oIterator) const;

  int GetStartVertex () const;
  int GetEndVertex () const;

  int GetNextVertex (int v) const;
  int GetPrevVertex (int v) const;

public:

  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionConstLayer *&oLayer) const;
  HRESULT GetVertexWLayer (CATIPolyCurveVertexWConstLayer *&oLayer) const;
  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentConstLayer *&oLayer) const;

  HRESULT GetSupport (CATIPolySupport*& oSupport) const;

public:

  HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolyCurveObserver* obs = 0);

  HRESULT RemoveLayer (CATIPolyLayer& iLayer);

  HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  bool HasLayer (const CLSID& id) const;

  HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

public:

  CATBoolean IsClosed () const;

public:

  HRESULT Accept (const CATIPolyCurve& iCurve, CATPolyCurveConstVisitor& iVisitor) const;

  CATIPolyCurveConstTools* GetConstTools () const;

public:

/** @name Methods not doing anything and returning S_FALSE.
    @{ */

  HRESULT AppendVertex (int& v);
  HRESULT AppendVertex (const CATMathPoint& P, int& v);  // Deprecated.

  HRESULT GetVertexPositionLayer (CATIPolyCurveVertexPositionLayer *&oLayer);
  HRESULT GetVertexWLayer (CATIPolyCurveVertexWLayer *&oLayer);
  HRESULT GetVertexTangentLayer (CATIPolyCurveVertexTangentLayer *&oLayer);
  HRESULT SetSupport (CATIPolySupport* iSupport);

  HRESULT SplitBar (const int v0, const int v1, int &n);
  HRESULT MergeVertices (const int v0, const int v1);

  HRESULT SetVertexPosition (const int v, const CATMathPoint &P);  // Deprecated.

  HRESULT Close ();
  HRESULT Open ();

  HRESULT RegisterObserver (CATIPolyCurveObserver &iObserver);
  HRESULT UnregisterObserver (CATIPolyCurveObserver &iObserver);

  HRESULT Accept (CATIPolyCurve& iCurve, CATPolyCurveVisitor& iV);

  CATIPolyCurveTools* GetTools ();

/** @} */

private:

  // Copy constructor/operator are forbidden.
  CATPolyMeshCurveConst (const CATPolyMeshCurveConst& iRHS);
  CATPolyMeshCurveConst& operator= (const CATPolyMeshCurveConst& iRHS);

protected:

  const CATIPolyMesh& _Mesh;

  mutable CATIPolySurfaceVertexPositionConstLayer* _MeshPosLayer;
  CATPolyMeshPointDoublyLinkedList _MeshPoints;
  CATPolyVector3dDoublyLinkedList* _Tangents;
    
  unsigned int _Flags;  // Bit flags.

  //friend class CATPolyMeshCurveConstTangentConstLayer;
  //friend class CATPolyMeshCurveConstWConstLayer;

private:

  CATPolyMeshCurveConst (const CATIPolyMesh& mesh);
  virtual ~CATPolyMeshCurveConst ();

public:

  // Deprecated.
  HRESULT GetVertexPosition (const int v, CATMathPoint &oPoint) const;

};

inline const CATIPolyMesh& CATPolyMeshCurveConst::GetMesh () const
{
  return _Mesh;
}

#endif // !CATPolyMeshCurveConst_H
