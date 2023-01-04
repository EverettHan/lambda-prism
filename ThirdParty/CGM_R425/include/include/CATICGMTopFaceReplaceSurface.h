#ifndef CATICGMTopFaceReplaceSurface_h_
#define CATICGMTopFaceReplaceSurface_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATTopDefine.h"

class CATBody;
class CATEdge;
class CATEdgeCurve;
class CATFace;
class CATGMLiveShapeRunOptions;
class CATMathPoint;
class CATMathTransformation;
class CATSurface;
class CATVertex;
class CATSurLimits;
class CATCrvLimits;
class CATTopData;
class CATListPtrCATFace;
class CATListPtrCATEdge;
class CATCurve;


extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopFaceReplaceSurface;

/**
* Class defining the operator which replaces the surfaces of faces in a body with the given surfaces.
*<br>
* The <tt>CATICGMTopFaceReplaceSurface</tt> operator follows the global frame of the topological operators 
* and satisfies the smart mechanism: the input bodies are not modified. A new resulting body 
* is created, possibly sharing data with the input body.
*<ul>
* <li>A <tt>CATICGMTopFaceReplaceSurface</tt> operator is created with the <tt>CATCreateFaceReplaceSurfaceOperator</tt> global function:
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
*<li>Options can be set with the <tt>SetXxx</tt> methods, before
* calling the operator's <tt>Run</tt> method. In particular, an optimized mode
* allows you to do some local operations in union mode.
*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometry factory. 
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopFaceReplaceSurface: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopFaceReplaceSurface();

  /**
 * Specifies the face in the input body whose surface should be replaced in the result body.
 * @param iOldFace
 * The pointer of an existing face in the input body.
 * @param iNewSurf
 * The pointer to the replacing surface for iOldFace.
 * If iNewSurf is a canonical surface, it may be replaced by an equivalent
 * surface (for closure management purpose).
 * @param iWorkingDomain
 * The limits of iNewSurf that are useful for the operation
 * These limits have to correctly match with its use in the result body, but
 * the operator may perform an extrapolation on the surface if necessary.
 * @param iOrientation
 * The orientation of the face in the new Body with respect to the new surface. 
 */
  virtual void ReplaceWith(
    CATFace *iOldFace,
    CATSurface *iNewSurf,
    CATSurLimits &iWorkingDomain,
    CATOrientation iOrientation) = 0;

  /**
 * Specifies the edge in the input body whose edge curve should be replaced in the result body.
 * @param iOldEdge
 * The pointer of an existing edge in the input body.
 * @param iNewEdgeCurve
 * The pointer to the replacing <tt>CATEdgeCurve</tt> for iOldEdge. This new curve will
 * include only one PCurve on surfaces associated to the faces boundary.
 * iOldEdge
 * @param iWorkingDomain
 * The limits of iNewEdgeCurve that are useful for the operation.
 * These limits have to correctly match with its use in the result body, but
 * the operator may perform an extrapolation on the curve if necessary
 * @param iOrientation
 * The orientation of the edge in the new Body with respect to the new edge curve. 
 */
  virtual void ReplaceWith(
    CATEdge *iOldEdge,
    CATEdgeCurve *iNewEdgeCurve,
    CATCrvLimits &iWorkingDomain,
    CATOrientation iOrientation) = 0;

  /**
 * Specifies the edge in the input body whose edge curve should be replaced in the result body.
 * This method works for isotopological configurations (when there is a bijection between the cells
 * of input and result body). It will have no effect otherwise.
 * @param iOldEdge
 * The pointer of an existing edge in the input body. This edge must border a face with a new
 * surface specfied by the ReplaceWith method. An error is thrown if not.
 * @param iCurve
 * The pointer to the <tt>CATCurve</tt> to laydown in order to compute the new EdgeCurve
 * for iOldEdge. 
 * @param iWorkingDomain
 * The limits of iCurve that are useful for the operation.
 * These limits have to correctly match with its use in the result body, but
 * the operator may perform an extrapolation on the curve if necessary 
 * This method is not compatible with the TransformWith, SetSameSurfacesParametrization
 * and ReplaceWith(iNewEdgeCurve) methods.
 */
  virtual void SetLaydownEdge(
    CATEdge *iOldEdge,
    CATCurve *iNewCurve,
    CATCrvLimits &iWorkingDomain) = 0;

  /**
 * Specifies a new target point for a given vertex in the input body.
 * This method is optionnal, but is required for some special cases where all adjacent
 * new EdgeCurves are tangent, and so the new point location can't be computed without
 * external information.
 * @param iOldVertex
 * The pointer of an existing vertex in the input body.
 * @param iNewTargetPoint
 * The location of the new vertex in the result body. This MathPoint should
 * be close enough (less than Tolerance) to all replacing surfaces of the 
 * faces bordering iOldVertex.
 */
  virtual void ReplaceWith(CATVertex *iOldVertex, CATMathPoint &iTargetPoint) = 0;

  /**
 * Method to call in order to specify the tansformation to apply to a list of faces
 * in the input body. 
 * An error is thrown if the same <tt>CATFace</tt> is given with several Transformations.
 * An error is thrown if the following other methods are called with this one :
 *  - All ReplaceWith methods 
 *  - SetCanonicalTangentEdge
 *  - SetSameSurfacesParametrization
 * @param iListFaces
 * The list of faces to be tranformed.
 * @param iTransfo
 * The 3D trandformation to apply to theses faces.
 */
  virtual void TransformWith(
    CATLISTP(CATFace) &iListFaces,
    CATMathTransformation &iTransfo) = 0;

  /**
 * Method to call in order to specify the tansformation to apply to a list of edges in the input body.  
 * @param iListEdges
 * The list of edges to be tranformed.
 * @param iTransfo
 * The 3D trandformation to apply to theses edges.
 */
  virtual void TransformWith(
    CATLISTP(CATEdge) &iListEdges,
    CATMathTransformation &iTransfo) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopFaceReplaceSurface(); // -> delete can't be called
};

/**
 * Creates a <tt>CATICGMTopFaceReplaceSurface</tt> operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iBody
 * The pointer to the body where the surface’s replacement will be performed.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.

 */
ExportedByCATGMOperatorsInterfaces CATICGMTopFaceReplaceSurface *CATCGMCreateFaceReplaceSurfaceOperator(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody);

#endif /* CATICGMTopFaceReplaceSurface_h_ */
