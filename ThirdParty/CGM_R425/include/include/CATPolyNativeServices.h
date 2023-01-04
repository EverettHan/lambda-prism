// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyNativeServices.h
//
//===================================================================
// January 2019  Creation: NDO
//===================================================================
#pragma once

#include "PolyMeshTools.h"
#include "CATErrorDef.h"

class CATIPolyObject;
class CATIPolyPoint;
class CATIPolyCurve;
class CATIPolySurface;
class CATIPolyMesh;
class CATIPolySurfaceVertexLine;
class CATPolyBody;
class CATPolyVertex;
class CATPolyEdge;
class CATPolyFace;
class CATPolyMeshImpl;
class CATPolyLineConst;
class CATPolyCompactMeshConst;
class CATPolyCompactSurfaceVertexLineConst;
class CATMathPoint;
class CATMapOfIntToInt;
class CATMapOfPtrToPtr;


/** @file 
 * Native services applies to polyhedral objects implemented in the 
 * framework PolyhedralObjects (and only in this framework.)
 */


namespace Poly
{
  /** @name Polyhedral Objects Native Services: Cell Creation
   *
   * CATPolyNativeServices.h
   * @{ */

   /*
    * Given a position, creates a native CATPolyPoint and makes a CATPolyVertex from it.
    * @param B
    *   The input CATPolyBody.
    * @param P
    *   The position for construction of the native CATPolyPoint.
    * @return
    *   A CATPolyVertex from the CATPolyBody.
    */
  ExportedByPolyMeshTools CATPolyVertex* MakeVertex (CATPolyBody& B, const CATMathPoint& P);

  /*
   * Given a curve-vertex, creates a native CATPolyCurveVertex and makes a CATPolyVertex from it.
   * @param B
   *   The input CATPolyBody.
   * @param C
   *   The input CATIPolyCurve.
   * @param cv
   *   The index of the curve-vertex on C.
   * @return
   *   A CATPolyVertex from the CATPolyBody.
   */
  ExportedByPolyMeshTools CATPolyVertex* MakeVertex (CATPolyBody& B, CATIPolyCurve& C, int cv);

  /*
   * Given a surface-vertex, creates a native CATPolySurfaceVertex and makes a CATPolyVertex from it.
   * @param B
   *   The input CATPolyBody.
   * @param F
   *   The input CATPolyFace owner of the CATIPolySurface.
   * @param sv
   *   The index of the surface-vertex on S.
   * @return
   *   A CATPolyVertex from the CATPolyBody.
   */
  ExportedByPolyMeshTools CATPolyVertex* MakeFaceVertex (CATPolyBody& B, CATPolyFace& F, int sv);

  /** @} */
};


namespace Poly
{
  /** @name Polyhedral Objects Native Services: Geometry Creation, Edition
  *
  * CATPolyNativeServices.h
  * @{ */

  /**
   * Splits a curve at a given vertex and constructs two new curves.
   * @param C
   *    The input curve.  It is not modified.
   * @param cv
   *    The curve vertex where the split occurs.
   * @param NC0
   *    A new curve representing the first part of the input curve.
   * @param NC1
   *    A new curve representing the second part of the input curve.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> on a successful split.
   *     <li> <tt>S_FALSE</tt> if the split cannot occur.
   *     <li> <tt>E_FAIL</tt> if an error occurs.
   *   </ul>
   */
  ExportedByPolyMeshTools HRESULT SplitCurve (CATIPolyCurve& C, int cv, CATIPolyCurve*& NC0, CATIPolyCurve*& NC1);

  /**
   * Creates a CATPolyMeshImpl copy of an input mesh.
   * @param iMesh
   *    The input mesh.
   * @param oMesh
   *    The output mesh which is a fully editable copy of the input mesh.
   *    The output mesh must be released.
   * @param iFlipOrientation
   *    An optional argument to create a copy with the opposite orientation.
   * @param ioV2VMap
   *    An optional argument which maps the vertices from the input to the output meshes.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> on a successful fully editable mesh creation.
   *     <li> <tt>E_FAIL</tt> if an error occurs.
   *   </ul>
   */
  ExportedByPolyMeshTools HRESULT CreateCopy (const CATIPolyMesh& iMesh, CATPolyMeshImpl*& oMesh,
                                              bool iFlipOrientation = false, CATMapOfIntToInt* ioV2VMap = 0);

  /**
   * Creates a CATPolyCompactMeshConst copy of an input mesh.
   * @param iMesh
   *    The input mesh.
   * @param oMesh
   *    The output mesh which is a non-editable copy of the input mesh.
   *    The output mesh must be released.
   * @param iFlipOrientation
   *    An optional argument to create a copy with the opposite orientation.
   * @param ioV2VMap
   *    An optional argument which maps the vertices from the input to the output meshes.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> on a successful compact mesh creation.
   *     <li> <tt>E_FAIL</tt> if an error occurs.
   *   </ul>
   */
  ExportedByPolyMeshTools HRESULT CreateCopy (const CATIPolyMesh& iMesh, CATPolyCompactMeshConst*& oMesh,
                                              bool iFlipOrientation = false, CATMapOfIntToInt* ioV2VMap = 0);


  /**
  * Creates a CATPolyLineConst copy of an input curve.
  * @param iCurve
  *    The input mesh.
  * @param oCurve
  *    The output curve which is a non-editable copy of the input curve.
  *    The output curve must be released.
  * @return
  *   <ul>
  *     <li> <tt>S_OK</tt> on a successful curve creation.
  *     <li> <tt>E_FAIL</tt> if an error occurs.
  *   </ul>
  */
  ExportedByPolyMeshTools HRESULT CreateCopy (const CATIPolyCurve& iCurve, CATPolyLineConst*& oCurve);

  /**
   * Creates a CATPolyCompactSurfaceVertexLineConst copy of an input surface-vertex line.
   * @param iSVL
   *   The input surface-vertex line.
   * @param iS
   *   The input parent surface of the new surface-vertex line. 
   * @param iV2VMap
   *   A mapping of the vertices from the parent surface of iSVL to the vertices from the iS surface. 
   *   If null the mapping is the identity.
   * @param oSVL
   *    The output surface-vertex line which is a non-editable copy of the input surface-vertex line.
   *    The output must be released.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> on a successful compact surface-vertex line creation.
   *     <li> <tt>E_FAIL</tt> if an error occurs.
   *   </ul>
   */
  ExportedByPolyMeshTools HRESULT CreateCopy (const CATIPolySurfaceVertexLine& iSVL, CATIPolySurface& iS, const CATMapOfIntToInt* iV2VMap,
                                              CATPolyCompactSurfaceVertexLineConst*& oSVL);

  /**
   * Updates the position of a point.
   * @param P0
   *    The reference point.
   * @param P1
   *     The point to be updated.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> on a successful update.
   *     <li> <tt>S_FALSE</tt> if the update cannot be done.
   *   </ul>
   */
  ExportedByPolyMeshTools HRESULT ReconcilePosition (const CATIPolyPoint& P0, CATIPolyPoint& P1);

  /**
   * Updates the position of a curve-vertex.
   * @param P0
   *    The reference point.
   * @param C
   *     The curve to be updated.
   * @param cv
   *     The curve-vertex from the curve to be updated.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> on a successful update.
   *     <li> <tt>S_FALSE</tt> if the update cannot be done.
   *   </ul>
   */
  ExportedByPolyMeshTools HRESULT ReconcilePosition (const CATIPolyPoint& P0, CATIPolyCurve& C, int cv);

  /**
   * Updates the position of a geometry associated to a vertex.
   * @param V0
   *    The vertex with the reference geometry.
   * @param V1
   *    The vertex whose geometry should be updated.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> on a successful update.
   *     <li> <tt>S_FALSE</tt> if the update cannot be done.
   *   </ul>
  */
  ExportedByPolyMeshTools HRESULT ReconcilePosition (const CATPolyVertex& V0, CATPolyVertex& V1);

  /**
   * Matches the indices from a curve to the indices of a reference curve from a CATPolyEdge.
   * This method does not change the geometry of the curve.   It just changes the indices of the 
   * curve-vertices.  This method helps preparing a curve before adding it to a CATPolyBody 
   * as with a FaceAddEdge () method.
   */
  ExportedByPolyMeshTools HRESULT MatchCurve (const CATPolyEdge& E, CATIPolyCurve& C);

  /** @} */

};


namespace Poly
{
  /** @name Polyhedral Objects Services: Queries
   *
   * CATPolyNativeServices.h
   * @{ */

  /**
   * Returns true if the polyhedral point is native.
   * A native CATIPolyPoint has an implementation in the PolyhedralObjects framework.
   */
  ExportedByPolyMeshTools bool IsNative (const CATIPolyPoint& P);

  /**
   * Returns true if the polyhedral curve is native.
   * A native CATIPolyCurve has an implementation in the PolyhedralObjects framework.
   */
  ExportedByPolyMeshTools bool IsNative (const CATIPolyCurve& C);

  /**
   * Returns true if the polyhedral surface is native.
   * A native CATIPolySurface has an implementation in the PolyhedralObjects framework.
   */
  ExportedByPolyMeshTools bool IsNative (const CATIPolySurface& S);

  /**
   * Returns true if the polyhedral object is native.
   * A native CATIPolyObject has an implementation in the PolyhedralObjects framework.
   */
  ExportedByPolyMeshTools bool IsNative (const CATIPolyObject& iObject);

  /**
   * Returns true if the native CATIPolyPoint is fully editable.
   * A CATIPolyObject is fully editable if:
   *   * Elements can be added or removed from the object.
   *   * It can be edited by any of its methods.
   *   * Its position layer can be edited.
   */
  ExportedByPolyMeshTools bool IsFullyEditable (const CATIPolyPoint& P);

  /**
   * Returns true if the native CATIPolyCurve is fully editable.
   */
  ExportedByPolyMeshTools bool IsFullyEditable (const CATIPolyCurve& C);

  /**
   * Returns true if the native CATIPolySurface is fully editable.
   */
  ExportedByPolyMeshTools bool IsFullyEditable (const CATIPolySurface& S);

  /**
   * Returns true if the native CATIPolyObject is fully editable.
   */
  ExportedByPolyMeshTools bool IsFullyEditable (const CATIPolyObject& iObject);

  /**
   * Returns true if the native CATIPolyPoint is not editable.
   */
  ExportedByPolyMeshTools bool IsNotEditable (const CATIPolyPoint& P);

  /**
   * Returns true if the native CATIPolyCurve is not editable.
   */
  ExportedByPolyMeshTools bool IsNotEditable (const CATIPolyCurve& C);

  /**
   * Returns true if the native CATIPolySurface is not editable.
   */
  ExportedByPolyMeshTools bool IsNotEditable (const CATIPolySurface& S);

  /**
   * Returns true if the native CATIPolyObject is not editable.
   * A CATIPolyObject is not editable if:
   *   * No element can be added or removed from the object.
   *   * It cannot be edited by any of its methods.
   *   * Its position layer cannot be edited.
   * However, layers can be added or removed to the CATIPolyObject.
   */
  ExportedByPolyMeshTools bool IsNotEditable (const CATIPolyObject& iObject);

  /** @} */

};


namespace Poly
{
  /** @name Polyhedral Objects Native Services: Editable/Non-Editable CATPolyBody
  *
  * CATPolyNativeServices.h
  * @{ */

  /**
   * Creates a copy of the input CATPolyBody with editable geometry constructed from the input geometry.
   */
  ExportedByPolyMeshTools CATPolyBody* NewEditableBody (const CATPolyBody& iPolyBody);

  /**
   * Substitutes the non-editable geometry in a native CATPolyBody with editable geometry.
   * @param ioPolyBody
   *   A native CATPolyBody to update.
   * @param ioSubstitutedGeometry
   *   An optional map from non-editable CATIPolyObject objects from the CATPolyBody to the new and editable geometry.
   *   This is a map from non-editable CATIPolyObject to editable CATIPolyObject created during the substitution.
   */
  ExportedByPolyMeshTools HRESULT SubstituteWithEditableGeometry (CATPolyBody& ioPolyBody, CATMapOfPtrToPtr* ioSubstitutedGeometry = 0);

  /**
   * Substitutes the editable geometry in a native CATPolyBody with non-editable geometry.
   * @param ioPolyBody
   *   A native CATPolyBody to update.
   * @param ioSubstitutedGeometry
   *   A map from the non-editable CATIPolyObject objects from the CATPolyBody to the editable geometry.
   *   This is the map from non-editable CATIPolyObject to editable CATIPolyObject created during the substitution:
   *   See SubstituteWithEditableGeometry ().
   */
  ExportedByPolyMeshTools HRESULT SubstituteWithNonEditableGeometry (CATPolyBody& ioPolyBody, CATMapOfPtrToPtr* ioSubstitutedGeometry = 0);

  /** @} */

};
