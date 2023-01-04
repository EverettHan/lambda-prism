//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// CATPolyBodyChecker
//
// Check topological consistency of a macro polyhedral body
//
//=============================================================================
// 2007-07-19 BPG: New.
// 2009-04-14 NDO: Revisited.
// 2013-06-18 JXO: CheckBoundingBoxes.
// 2014-06-24 JXO: CheckSurfaceMeshes.
//=============================================================================
#pragma once

#include "PolyBodyTools.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATPolyBody;
class CATPolyFace;
class CATPolyEdge;
class CATPolyVertex;
class CATPolyBodyCheckerObserver;


/**
This class performs several consistency checks of the macro-topology and micro-topology of a CATPolyBody.
It checks if a CATPolyBody is valid or not. 

In some cases (like adapter cases), the discrete entities (surfaces, curves and points) may not satisfy all the properties and adjacency 
relationships required to belong to a CATPolyBody.   A CATPolyBody object may still be built with a valid
macro-topology (as it should always be) but the entities it refers to may fail some of the requirement tests.

Checks can be performed independently.  The check methods return <tt>S_OK</tt> if the CATPolyBody passes the test and 
<tt>S_FALSE</tt> if it fails the test.  A returned error (<tt>E_FAIL</tt> or any other code) means that the test could not
be completely performed or that the data structure has corrupted data.

The errors found during these checks will be logged onto the CATPolyBodyDiagnosis.

@see CATPolyBodyDiagnosis
*/
class ExportedByPolyBodyTools CATPolyBodyChecker
{

public:

  inline CATPolyBodyChecker ();
  ~CATPolyBodyChecker ();

public:

/** @name Main Method
    @{ */

  /**
   * Performs all the various checks on a CATPolyBody object.
   * Errors found during the checks are logged onto the diagnosis.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this test.
   *          The CATPolyBody is valid.
   *     <li> <tt>S_FALSE</tt> The CATPolyBody fails this test. 
   *          Errors are logged onto the diagnosis.  (Invalid CATPolyBody.)
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT FullCheck (CATPolyBody& iBody) const;

/** @} */

public:

/** @name Macro-Topology Checks
    @{ */

  /**
   * Checks the iterator cycling through the edges incident to a CATPolyFace
   * for each face of the CATPolyBody.
   *
   * A CATPolyBody object should always satisfy this check.  A returned code of 
   * <tt>E_FAIL</tt> means that there is something seriously wrong with the 
   * CATPolyBody (corrupt CATPolyBody).
   *
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this validity test.
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT CheckFaceEdgeIterator (CATPolyBody& iPolyBody) const;

  /**
   * Checks the iterator cycling through the edges incident to a CATPolyVertex
   * for each vertex of the CATPolyBody.
   *
   * A CATPolyBody object should always satisfy this check.  A returned code of 
   * <tt>E_FAIL</tt> means that there is something seriously wrong with the 
   * CATPolyBody (corrupt CATPolyBody).
   *
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this validity test.
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT CheckVertexEdgeIterator (CATPolyBody& iPolyBody) const;

  /**
   * Checks the iterators CATPolyEdgeFaceIterator and CATPolyEdgeCurveIterator.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyEdge passes this test.
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyEdge 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT CheckEdgeIterators (CATPolyEdge& iEdge) const;

public:

  /**
   * Checks that the curves of all the CATPolyBody edges pass the incidence test.
   * If the CATPolyBody fails this test, then the errors are logged onto
   * the CATPolyBody diagnosis.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this test.
   *     <li> <tt>S_FALSE</tt> The CATPolyBody fails this test. 
   *          Errors are added to the diagnosis.  (Invalid CATPolyBody.)
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT CheckEdges (CATPolyBody& iBody) const;

/** @} */

public:

/** @name Micro-Topology Checks
    @{ */

  /**
   * Checks the surfaces of the CATPolyBody.
   * Including CheckSurfaceVertexCellLayers, CheckSurfaceOrientations and CheckSurfaceMeshes.
   * If the CATPolyBody fails this test, then the errors are logged onto
   * the CATPolyBody diagnosis.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this test.
   *     <li> <tt>S_FALSE</tt> The CATPolyBody fails this test. 
   *          Errors are logged onto the diagnosis.  (Invalid CATPolyBody.)
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT CheckSurfaces (CATPolyBody& iBody) const;

  /**
   * Checks that each vertex of the surfaces refer to at most one and only one cell.
   * If the CATPolyBody fails this test, then the errors are logged onto
   * the CATPolyBody diagnosis.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this test.
   *     <li> <tt>S_FALSE</tt> The CATPolyBody fails this test. 
   *          Errors are logged onto the diagnosis.  (Invalid CATPolyBody.)
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT CheckSurfaceVertexCellLayers (CATPolyBody& iBody) const;

  /**
   * Checks that the surfaces of all the CATPolyBody faces have
   * consistent facet orientations and are manifold.
   * If the CATPolyBody fails this test, then the errors are logged onto
   * the CATPolyBody diagnosis.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this test.
   *     <li> <tt>S_FALSE</tt> The CATPolyBody fails this test. 
   *          Errors are logged onto the diagnosis.  (Invalid CATPolyBody.)
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT CheckSurfaceOrientations (CATPolyBody& iBody) const;

  /**
   * Checks that all the surface vertex lines refer to surface vertices.
   * If the CATPolyBody fails this test, then the errors are logged onto
   * the CATPolyBody diagnosis.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this test.
   *     <li> <tt>S_FALSE</tt> The CATPolyBody fails this test. 
   *          Errors are logged onto the diagnosis.  (Invalid CATPolyBody.)
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT CheckSurfaceVertexLines (CATPolyBody& iBody) const;

  /**
   * Checks that all the surface meshes are manifold, contiguous, and do
   * not contain degenerate triangles.
   * If the CATPolyBody fails this test, then the errors are logged onto
   * the CATPolyBody diagnosis.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this test.
   *     <li> <tt>S_FALSE</tt> The CATPolyBody fails this test. 
   *          Errors are logged onto the diagnosis.  (Invalid CATPolyBody.)
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT CheckSurfaceMeshes(CATPolyBody& iBody) const;

  /**
   * Checks that all the bounding boxes of faces and edges are really
   * bounding their micro vertices.
   * If the CATPolyBody fails this test, then the errors are logged onto
   * the CATPolyBody diagnosis.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this test.
   *     <li> <tt>S_FALSE</tt> The CATPolyBody fails this test. 
   *          Errors are logged onto the diagnosis.  (Invalid CATPolyBody.)
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT CheckBoundingBoxes (CATPolyBody& iBody) const;

  /**
   * Registers an observer for fine error outputs.
   * And AddRef is done on obs, a Release will be done in destructor
   */
  void RegisterObserver(CATPolyBodyCheckerObserver * obs);
  /** 
   * Unregisters obs. Release will be called.
   */
  void UnregisterObserver(CATPolyBodyCheckerObserver * obs);

/** @} */

public:

  // @deprecated
  HRESULT Check (CATPolyBody &iBody) const;

  // @deprecated
  HRESULT Check (CATPolyEdge& iEdge) const;

  // @deprecated
  inline HRESULT DoCheckMeshOrientationConsistency (CATBoolean iFlag = TRUE);

protected:

  CATBoolean _CheckMeshOrientationConsistencyP;

  CATPolyBodyCheckerObserver * m_obs;

};


inline CATPolyBodyChecker::CATPolyBodyChecker () :
  _CheckMeshOrientationConsistencyP (FALSE), m_obs(0)
{
}

inline HRESULT CATPolyBodyChecker::DoCheckMeshOrientationConsistency (CATBoolean iFlag)
{
  _CheckMeshOrientationConsistencyP = iFlag;
  return S_OK;
}
