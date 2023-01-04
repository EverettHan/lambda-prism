#ifndef CATEdge_H
#define CATEdge_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATGMModelInterfaces.h"
#include "CATGeoDef.h"
#include "CATCell.h"
#include "ListVOfLong.h"

class CATBody;

class CATDomain;
class CATShell;
class CATLoop;

class CATBoundaryIterator;
class CATBoundedCellsIterator;

class CATFace;
class CATVertex;

class CATEdgeCurve;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATCrvParam;
class CATMathVector;
class CATSurLimits;

#include "CATTopData.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATEdge ;
#else
extern "C" const IID IID_CATEdge ;
#endif

/**
 * Interface representing a topological edge. 
 * <br> An edge is a topological cell which geometry is an edge-curve. It 
 * is bounded by vertices. 
 * <br> Edges can be used in the following ways:
 * <ul>
 * <li> to bound a face (edge must be put in one of the face loops)
 * <li> to bound a volume (edge must be put in one of the volume wires)
 * <li> as a piece of a wire in 3D space (edge must be put in a wire, and that
 *      wire must be directly referred by a body).
 * </ul>
 * <br> In order to be valid, the vertices of the edge must be different.
 * An edge is oriented with regards to the
 * underlying edge-curve:
 * <dl><dt><tt>CATOrientationNegative</tt><dd> The start
 * vertex is the one with the larger parameter, and the end vertex is the
 * one with the smaller parameter.
 *     <dt><tt>CATOrientationPositive</tt><dd> The start
 * vertex is the one with the smaller parameter, and the end vertex is the
 * one with the larger parameter.
 *     <dt><tt>CATOrientationUnknown</tt><dd> The cell orientation is not
 * defined.</dl>
 * <br>A CATEdge is created with the @href CATBody#CreateCell or @href CATBody#CreateEdge methods and
 * deleted with the @href CATICGMContainer#Remove method.
 */ 
class ExportedByCATGMModelInterfaces CATEdge : public CATCell
{

  CATDeclareInterface;

  public :
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Sets the geometric edge-curve of <tt>this</tt> CATEdge. 
 * @param iCurve
 * The pointer to the geometry of <tt>this</tt> edge.
 * @param iOrientation
 * The relative orientation of <tt>this</tt> and its geometry.
 */
  virtual void SetCurve( CATEdgeCurve * iCurve, CATOrientation iOrientation=CATOrientationPositive)=0;

/**
 * Returns the geometric edge-curve of <tt>this</tt> CATEdge.
 * @param ioOrientation
 * A pointer to the relative orientation with regards to the edge-curve.
 * If <tt>NULL</tt>, the orientation is not filled out.
 * @return
 * The pointer to the geometry of <tt>this</tt> CATEdge.
 */
  virtual CATEdgeCurve * GetCurve(CATOrientation * ioOrientation=NULL)=0;

/**
 * Returns the geometry of <tt>this</tt> CATEdge with respect to an underlying CATFace.
 * @param iBoundedFace
 * The pointer to a face bounded by <tt>this</tt>.
 * @param iSide
 * The matter side of <tt>this</tt> while bounding <tt>iBoundedFace</tt>.
 * @param ioOrientation
 * The orientation of <tt>this</tt> edge with regards to its geometry (a CATPCurve).
 * If <tt>NULL</tt>, this is not filled out.
 * @param ioStartParam
 * The start limitation of the CATPCurve, always with regards to its own 
 * orientation: <tt>ioStartParam < ioEndParam</tt>.
 * If <tt>NULL</tt>, this is not filled out.
 * @param ioEndParam
 * The end limitation of the CATPCurve.
 * If <tt>NULL</tt>, this is not filled out.
 * @return
 * The pointer to the geometry as a CATPCurve.
 */
  virtual CATPCurve * GetGeometryOnFace(CATFace *iBoundedFace, CATSide iSide,
					CATOrientation * ioOrientation=NULL,
					CATCrvParam    * ioStartParam = NULL,
					CATCrvParam    * ioEndParam   = NULL)=0;
  

/**
 * Sets the geometry of <tt>this</tt> CATEdge with respect to an underying face.
 * @param iBoundedFace
 * The pointer to a face bounded by <tt>this</tt>.
 * @param iSide
 * The matter side of <tt>this</tt> while bounding <tt>iBoundedFace</tt>.
 * @param iPCurve
 * The pointer to the geometry of <tt>this</tt> on <tt>iBoundedFace</tt>.
 * @param iStartVertexGeometry
 * The pointer to the geometry of the start vertex bounding <tt>this</tt>
 * If <tt>NULL</tt>, this is not taken into account.
 * @param iEndVertexGeometry
 * The pointer to the geometry of the end vertex bounding <tt>this</tt>
 * If <tt>NULL</tt>, this is not taken into account.
 */
  virtual void SetGeometryOnFace(CATFace  *iBoundedFace,  CATSide  iSide,
		    CATPCurve           * iPCurve,
		    CATPointOnEdgeCurve * iStartVertexGeometry=NULL,
		    CATPointOnEdgeCurve * iEndVertexGeometry  =NULL) = 0;

/**
 * Returns the matter side of <tt>this</tt> CATEdge with respect to a CATFace. 
 * @param iBoundedFace
 * The pointer to a face bounded by <tt>this</tt>.
 * @return
 * The matter side of <tt>this</tt> while bounding <tt>iBoundedFace</tt>.
 */
  virtual CATSide GetSideOnFace( CATFace *iBoundedFace ) = 0;

/**
 * Sets the matter side of <tt>this</tt> CATEdge with respect to a CATFace.
 * @param iBoundedFace
 * The pointer to a face bounded by <tt>this</tt>.
 * @param iSide
 * The matter side of <tt>this</tt> while bounding <tt>iBoundedFace</tt>.
 */
  virtual void SetSideOnFace( CATFace *iBoundedFace, CATSide iSide ) = 0;

/**
 * Retrieves the CATEdge which is right after <tt>this</tt> in its loop.
 * @param iSideVsFace
 * The matter side of <tt>this</tt> while bounding <tt>iBoundedFace</tt>.
 * @param iBoundedFace
 * The pointer to a face bounded by <tt>this</tt>.
 * @param oNextEdge
 * The next edge in the loop.
 * If the edge loop is  closed, this method skips over the 
 * loop closure. If the
 * loop is open, the method, applied to the end edge, returns a <tt>NULL</tt> pointer.
 * @param oSide
 * The matter side of <tt>oNextEdge</tt> while bounding <tt>iBoundedFace</tt>.
 */
  virtual void GetNextInLoop( CATSide iSideVsFace, CATFace * iBoundedFace,  CATEdge ** oNextEdge, CATSide * oSide ) = 0;

/**
 * Retrieves the CATEdge which is right before <tt>this</tt> CATEdge in its loop.
 * @param iSideVsFace
 * The matter side of <tt>this</tt> while bounding <tt>iBoundedFace</tt>.
 * @param iBoundedFace
 * The pointer to a face bounded by <tt>this</tt>.
 * @param oPrevEdge
 * The previous edge in the loop.
 * If the edge loop is  closed, this method skips over the 
 * loop closure. If the
 * loop is open, the method, applied to the end edge, returns a <tt>NULL</tt> pointer.
 * @param oSide
 * The matter side of <tt>oPrevEdge</tt> while bounding <tt>iBoundedFace</tt>.
 */
  virtual void GetPreviousInLoop( CATSide iSideVsFace, CATFace * iBoundedFace, CATEdge ** oPrevEdge, CATSide * oSide ) = 0;

/**
 * Returns the start and end vertices of <tt>this</tt> CATEdge.
 * <br>Sample: To only retrieve the start vertex:
 * <pre>CATVertex * Start;
 * PointerToAnEdge->GetVertices(&Start,NULL);</pre>
 * @param oStartVertex
 * The start vertex. If <tt>NULL</tt>, this argument is not filled out.
 * @param oEndVertex
 * The end vertex. If <tt>NULL</tt>, this argument is not filled out.
 */
  virtual void GetVertices( CATVertex **oStartVertex, CATVertex **oEndVertex )=0;


/**
 * Retrieves the start and end points on edge curve of <tt>this</tt> CATEdge.
 * <br>Theses match the start and end vertices.
 * <br>Sample: To only retrieve the CATPointOnEdgeCurve corresponding to the end vertex:
 * <pre>CATPointOnEdgeCurve * End;
 * PointerToAnEdge->GetVerticesPointsOnEdgeCurve(NULL,&End);</pre>
 * @param oStartPoec
 * The CATPointOnEdgeCurve corresponding to the start vertex.
 * If <tt>NULL</tt>, this argument is not filled out.
 * @param oEndPoec
 * The CATPointOnEdgeCurve corresponding to the end vertex.
 * If <tt>NULL</tt>, this argument is not filled out.
	*/
  virtual void GetVerticesPointsOnEdgeCurve(CATPointOnEdgeCurve  ** oStartPoec, CATPointOnEdgeCurve  ** oEndPoec )=0;

/**
 * Retrieves the start and end point curve parameters of <tt>this</tt> CATEdge. 
 * <br>They match the
 * start and end vertices (e.g. if the underlying edge-curve is reversed, the
 * start parameter is larger than the end parameter).
 * <br>Sample: To only retrieve the CATCrvParam corresponding to the end vertex:
 * <pre>CATCrvParam End;
 * PointerToAnEdge->GetVerticesParamsOnEdgeCurve(NULL,&End);</pre>
 * @param oStartParam
 * The CATCrvParam corresponding to the start vertex.
 * If <tt>NULL</tt>, this argument is not filled out.
 * @param oEndParam
 * The CATCrvParam corresponding to the end vertex.
 * If <tt>NULL</tt>, this argument is not filled out.
 */
  virtual void GetVerticesParamsOnEdgeCurve(CATCrvParam * oStartParam, CATCrvParam * oEndParam )=0;


/**
 * Computes the tangent vector to <tt>this</tt> CATEdge at a given parameter.
 * @param iParamOnEdgeCurve
 * The parameter where to compute the tangent.
 * @param ioTangentVector
 * The computed vector.
 * @param iTgtNormalization
 * The mode of normalization.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> TRUE </tt></dt><dd>if <tt>ioTangentVector</tt> must be  normalized.
 *     <dt><tt> FALSE </tt></dt><dd> otherwise.</dl> 
 * @return
 * The diagnosis of the evaluation.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> TRUE </tt></dt><dd>if vector is non-zero
 *     <dt><tt> FALSE </tt></dt><dd> otherwise.</dl>
 */
  virtual CATBoolean EvalTangent( const CATCrvParam & iParamOnEdgeCurve, 
				  CATMathVector     & ioTangentVector,  CATBoolean  iTgtNormalization=TRUE)=0;


/**
 * @nodoc
 * @deprecated V5R11 GetLocalSharpness
 * Computes sharpness angle of <tt>this</tt> CATEdge at a given parameter 
 * on the edge curve. 
 * @param iParamOnEdgeCurve
 * The parameter where to compute the tangent.
 * @param iFace1
 * The pointer to the one face bounded by <tt>this</tt>.
 * @param iFace2
 * The pointer to another face bounded by <tt>this</tt>.
 * @param ioSharpness
 * The sharpness related to 2 faces <tt>iFace1</tt> and <tt>iFace2</tt>
 * bounded by the edge. 
 * @param oOrientation 
 * If no reference shell has been provided, and if the 2 faces have
 * reversed orientations along the edge, then the first face will be used
 * as a reference for the outer side. In this case, <tt>oOrientation</tt> 
 * indicates that second face has to be reversed or not.
 * @param iShellOwningTheTwoFaces
 * The pointer to a shell that owns the two faces. If <tt>NULL</tt>, the faces are supposed
 * to belong to only one shell.
 * @exception
 * If the edge bounds one of the faces twice (closed faces case).
 * An other method with matter side specification will be available soon.
 */    
  virtual CATAngle EvalSharpness( const CATCrvParam & iParamOnEdgeCurve, 
			 CATFace           * iFace1, CATFace           * iFace2,
			 CATTopSharpness&    ioSharpness,	 CATOrientation    * oOrientation=NULL,
			 CATShell*           iShellOwningTheTwoFaces=NULL)=0;


/**
 * @nodoc
 * @deprecated V5R11 GetGlobalSharpness
 * Retrieves the global sharpness of <tt>this</tt> CATEdge.
 * @param iFace1
 * The pointer to the one face bounded by <tt>this</tt>.
 * @param iFace2
 * The pointer to another face bounded by <tt>this</tt>.
 * @param ioSharpness
 * The sharpness related to 2 faces <tt>iFace1</tt> and <tt>iFace2</tt>
 * bounded by the edge. 
 * @param oOrientation 
 * If no reference shell has been provided, and if the 2 faces have
 * reversed orientations along the edge, then the first face will be used
 * as a reference for the outer side. In this case, <tt>oOrientation</tt> 
 * indicates that second face has to be reversed or not.
 * @param iShellOwningTheTwoFaces
 * The pointer to a shell that owns the two faces. If <tt>NULL</tt>, the faces are supposed
 * to belong to only one shell.
 * @param oDefinedSharpness
 * The way the sharpness has been filled out (stored or computed).
 * <br><b>Legal values</b>:
 * <dl><dt><tt> TRUE </tt></dt><dd>if <tt>SetSharpness</tt> has been previously applied.
 *     <dt><tt> FALSE </tt></dt><dd> geometric evaluation of sharpness.</dl> 
 * If <tt>NULL</tt>, this argument is not filled out.
 * @exception
 * If the sharpness is not constant along the edge.
 */     
  virtual void     EvalGlobalSharpness(CATFace *iFace1, CATFace *iFace2,
			 CATTopSharpness  & ioSharpness,
       CATOrientation   * oOrientation=NULL,
			 CATShell         * iShellOwningTheTwoFaces=NULL,
       CATBoolean       * oDefinedSharpness = NULL)=0;
       
/**
 * @nodoc
 * @deprecated V5R11 SetGlobalSharpness
 * Defines the global sharpness of <tt>this</tt> CATEdge on the edge curve.
 * @param iFace1
 * The pointer to the one face bounded by <tt>this</tt>.
 * @param iFace2
 * The pointer to another face bounded by <tt>this</tt>.
 * @param iSharpness
 * The tangential continuity.
 * @param iConcavity
 * The curvature.
 * @param iShellOwningTheTwoFaces
 * The pointer to a shell that owns the two faces. If <tt>NULL</tt>, the faces are supposed
 * to belong to only one shell. 
 */     
  virtual void     SetSharpness(CATFace *iFace1, CATFace *iFace2,
      const CATGeoContinuity   iSharpness,
      const CATGeoConvexity    iConcavity = CATUnknownConvexity,
      CATShell *iShellOwningTheTwoFaces=NULL)  = 0;


/**
 * Computes the sharpness angle of <tt>this</tt> CATEdge at a given parameter 
 * on the edge curve.
 * @param iTopData
 * The object defining the CATSoftwareConfiguration.  
 * @param iParamOnEdgeCurve
 * The parameter where to compute the tangent.
 * @param iFace1
 * The pointer to the one face bounded by <tt>this</tt>.
 * @param iFace2
 * The pointer to another face bounded by <tt>this</tt>.
 * @param ioSharpness
 * The sharpness related to 2 faces <tt>iFace1</tt> and <tt>iFace2</tt>
 * bounded by the edge. 
 * @param oOrientation 
 * If no reference shell has been provided, and if the 2 faces have
 * reversed orientations along the edge, then the first face will be used
 * as a reference for the outer side. In this case, <tt>oOrientation</tt> 
 * indicates that second face has to be reversed or not.
 * @param iShellOwningTheTwoFaces
 * The pointer to a shell that owns the two faces.
 * If <tt>NULL</tt>, the faces are supposed to belong to only one shell.
 * @param iMinSharpAngle
 * Minimum (resp. maximum) angle value in rad for which the edge
 * is declared Sharp (resp. Smooth).
 * @exception
 * If the edge bounds one of the faces twice (closed faces case).
 * An other method with matter side specification will be available soon.
 */    
  virtual CATAngle GetLocalSharpness(CATTopData &iTopData,
       const CATCrvParam & iParamOnEdgeCurve, 
			 CATFace           * iFace1,
       CATFace           * iFace2,
			 CATTopSharpness&    oSharpness,
       CATOrientation    * oOrientation = NULL,
			 CATShell*           iShellOwningTheTwoFaces = NULL,
       CATAngle			       iMinSharpAngle = CATTopSharpAngle) = 0;


/**
 * Retrieves the global sharpness of <tt>this</tt> CATEdge.
 * @param iTopData
 * The object defining the CATSoftwareConfiguration. 
 * @param iFace1
 * The pointer to the one face bounded by <tt>this</tt>.
 * @param iFace2
 * The pointer to another face bounded by <tt>this</tt>.
 * @param ioSharpness
 * The sharpness related to 2 faces <tt>iFace1</tt> and <tt>iFace2</tt>
 * bounded by the edge. 
 * @param oOrientation 
 * If no reference shell has been provided, and if the 2 faces have
 * reversed orientations along the edge, then the first face will be used
 * as a reference for the outer side. In this case, <tt>oOrientation</tt> 
 * indicates that second face has to be reversed or not.
 * @param iShellOwningTheTwoFaces
 * The pointer to a shell that owns the two faces.
 * If <tt>NULL</tt>, the faces are supposed to belong to only one shell.
 * @param iComputeConvexity
 * Whether the convexity is computed for Sharp edges.
 * If FALSE, <tt>iShellOwningTheTwoFaces</tt> can be set to NULL.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> TRUE </tt></dt><dd>the convexity is computed if the edge is Sharp.
 *     <dt><tt> FALSE </tt></dt><dd>the convexity is not computed.</dl>
 * @param iForceGeometricEvaluation
 * If TRUE, a geometric evaluation is performed even if a value
 * stored (with <tt>SetGlobalSharpness</tt>) if it exists.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> TRUE </tt></dt><dd>
 *     <dt><tt> FALSE </tt></dt><dd></dl>   
 * @param oStoredSharpness
 * The way the sharpness has been filled out (stored or computed).
 * <br><b>Legal values</b>:
 * <dl><dt><tt> TRUE </tt></dt><dd>if <tt>SetLocalSharpness</tt> has been previously applied.
 *     <dt><tt> FALSE </tt></dt><dd> geometric evaluation of sharpness.</dl> 
 * If <tt>NULL</tt>, this argument is not filled out.
 * @param iMinSharpAngle
 * Minimum (resp. maximum) angle value in rad for which the edge
 * is declared Sharp (resp. Smooth).
 * @exception
 * If no geometry evaluation could be properly performed.
 */     
  virtual void GetGlobalSharpness(CATTopData &iTopData,
       CATFace          * iFace1,
       CATFace          * iFace2,
			 CATTopSharpness  & oSharpness,
       CATOrientation   * oOrientation = NULL,
			 CATShell         * iShellOwningTheTwoFaces = NULL,
       CATBoolean         iComputeConvexity = TRUE,
       CATBoolean         iForceGeometricEvaluation = FALSE,
       CATBoolean       * oStoredSharpness = NULL,
       CATAngle			      iMinSharpAngle = CATTopSharpAngle) = 0;
       
/**
 * Defines the global sharpness of <tt>this</tt> CATEdge on the edge curve.
 * @param iTopData
 * The object defining the CATSoftwareConfiguration. 
 * @param iFace1
 * The pointer to the one face bounded by <tt>this</tt>.
 * @param iFace2
 * The pointer to another face bounded by <tt>this</tt>.
 * @param iSharpness
 * The tangential continuity.
 * @param iConcavity
 * The curvature.
 * @param iShellOwningTheTwoFaces
 * The pointer to a shell that owns the two faces.
 * If <tt>NULL</tt>, the faces are supposed to belong to only one shell.
 * @param iMinSharpAngle
 * Minimum (resp. maximum) angle value in rad for which the edge
 * is declared Sharp (resp. Smooth).
 * @param iCheckBeforeSet
 * If TRUE, <tt>GetGlobalSharpness</tt> is called and its result compared with <tt>iMinSharpAngle</tt>.
 * The sharpness is stored only if no incoherence was detected.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> TRUE </tt></dt><dd>
 *     <dt><tt> FALSE </tt></dt><dd></dl>
 * @param iForceGeometricEvaluation
 * If TRUE, a geometric evaluation is performed during <tt>GetGlobalSharpness</tt> even if a value
 * stored (with <tt>SetGlobalSharpness</tt>) exists.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> TRUE </tt></dt><dd>
 *     <dt><tt> FALSE </tt></dt><dd></dl>   
 * @return
 * Whether the sharpness has been stored or not.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> TRUE </tt></dt><dd>
 *     <dt><tt> FALSE </tt></dt><dd></dl>
 */     
  virtual CATBoolean SetGlobalSharpness(CATTopData &iTopData,
      CATFace                * iFace1,
      CATFace                * iFace2,
      const CATGeoContinuity   iSharpness,
      const CATGeoConvexity    iConcavity = CATUnknownConvexity,
      CATShell               * iShellOwningTheTwoFaces = NULL,
      CATAngle			           iMinSharpAngle = CATTopSharpAngle,
      CATBoolean               iCheckBeforeSet = TRUE,
      CATBoolean               iForceGeometricEvaluation = FALSE) = 0;

/**
  * @nodoc
  * @deprecated V5R15 @href CATDynMassProperties3D#GetLength
  * Computes the length (between start and end vertex) of <tt>this</tt> CATEdge.
  * @return
  * The computed length.
  */
  virtual double   CalcLength() = 0;

/**
 * Returns the 2D bounding box of <tt>this</tt> CATEdge on the surface of the bounded face. 
 * @param iBoundedFace
 * The pointer to a face bounded by <tt>this</tt>.
 * @return
 * The computed bounding box.
 */
  virtual const CATSurLimits * Get2DBoundingBox(CATFace* iBoundedFace)=0;

/**
 * Flags the edge junction status (No effect before V5R8)
 * @param iTopData
 * The object defining the CATSoftwareConfiguration. 
 * @param iFlag
 * <dl><dt><tt>CatTopUndefined</tt></dt><dd>
 *     <dt><tt>CatTopJunction</tt></dt><dd>
 *     <dt><tt>CatTopFunctional</tt></dt><dd>
 */
  virtual void SetJunctionStatus(CATTopData &iTopData, CATTopJunctionEdgeStatus iFlag = CatTopJunction)=0;

/**
 * Reads the edge junction status. 
 * @return
 * The junction status of <tt>this</tt> CATEdge.
 */
  virtual CATTopJunctionEdgeStatus GetJunctionStatus()=0;
  
  

  

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  

/**
 * @nodoc
 * Do not use.
 */
  virtual void SetGeometryOnSupport( CATPCurve           * iPCurve , 
				     CATOrientation        orientation,
				     CATPointOnEdgeCurve * iStart,  CATPointOnEdgeCurve * iEnd) = 0;


  /** @nodoc */ 
  virtual  HRESULT GetBorderedFaces(CATBody *iBody, 
                                    CATLISTP(CATCell) & oFaces,
                                    CATListOfLong     & oNbOfFacesByDomain ) = 0;
  
};

CATDeclareHandler(CATEdge,CATCell);

#endif // CATEdge_H
