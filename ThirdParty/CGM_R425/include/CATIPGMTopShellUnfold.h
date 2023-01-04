#ifndef CATIPGMTopShellUnfold_h_
#define CATIPGMTopShellUnfold_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCGMJournal.h"
#include "CATShellUnfoldMethod.h"
#include "CATCollec.h"

class CATBody;
class CATCrvLimits;
class CATFace;
class CATFrFNurbsBipar;
class CATGeoFactory;
class CATMathPoint;
class CATMathTransformation;
class CATPCurve;
class CATPlane;
class CATPoint;
class CATShell;
class CATSurface;
class CATVertex;
class CATEdge;
class CATMathPlane;
class CATCell;
class CATLISTP(CATFace);
class CATLISTP(CATCell);
class CATMathTransformation2D;
class CATLISTP(CATEdge);
class CATLaw;
class CATPolyMeshMappingFunction;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopShellUnfold;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopShellUnfold: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopShellUnfold();

  // Changes the method of development action
  // ACCESS: For Ruled Shell Unfold only
  virtual void SetUnfoldMethod(CATShellUnfoldMethod iMethod) = 0;

  //DEPRECATED
  //use SetTargetLocation instead
  virtual void SetUnfoldLocation(
    CATPlane *iPlaneForUnfolding,
    CATPoint *iOrigin = NULL) = 0;

  //Set edges to tear
  // ACCESS: For Ruled Shell Unfold only
  //
  //NOTE: Once SetEdgesToTear is called, the edges-to-tear (iEdgesToTear) provided at the time of...
  //      operator construction are no more respected.
  //
  //iEdgesToTear:     Edges to tear in case of ambiguity
  //                  If this is not sufficient to remove all ambiguities, and
  //                  later, one doesn't remove all ambiguities using SetEdgesToTear again, the
  //                  remaining ambiguities are removed by automatically choosing additional
  //                  edges to tear. This automatic selection depends on order of faces in the 
  //                  "list of faces"/"shell" if provided to the constructor, else on the shell
  //                  of Body provided to the constructor
  //
  //oNbAmbiguities:   Number of ambiguities, still unresolved with iEdgesToTear
  //
  //oCandidateEdgesToTear: Edges which can be selected further to reduce ambiguity
  //
  //oInvalidInputEdges:    * Edges out of iEdgesToTear, which cannot be used for tearing.
  //                         Example: Common edge in a shell of two faces, since it will create
  //                         disconnected result  
  //                       * It can be same as iEdgesToTear if iEdgesToTear cannot be, together,
  //                         taken for tearing.
  //                         Example: All internal edges in a closed shell
  //
  // ioMandatoryCandidates: * Edges out of oCandidateEdgesToTear, which are incident on sharp internal 
  //				                  corners in the skin. Sharp corners are found using GetSharpCornerInfo.
  //                        * Not filled if ioMandatoryCandidates or ioOptionalCandidates is NULL. Both 
  //                          should be given together. Operator insists this for efficiency.
  //
  // ioOptionalCandidates:  * Edges out of oCandidateEdgesToTear sans ioMandatoryCandidates. That is
  //                          oCandidateEdgesToTear = ioMandatoryCandidates+ioOptionalCandidates
  //                        * Not filled if ioMandatoryCandidates or ioOptionalCandidates is NULL. Both 
  //                          should be given together. Operator insists this for efficiency.
  //
  //
  //Returns   TRUE     if iEdgesToTear + GetEdgesMustToTear together can be taken as edges-to-tear. This ...
  //                   doesn't mean that all the ambiguities are removed. oNbAmbiguities can still be non-zero.
  //          FALSE    if iEdgesToTear + GetEdgesMustToTear together cannot be taken as edges-to-tear, as this will...
  //                   result in a non-connex output. Note that if iEdgesToTear is empty, that means this shell is...
  //                   impossible to Unfold. One reason can be the presence of GetEdgesMustToTear, which can cause...
  //                   a non-connex result.  
  virtual CATBoolean SetEdgesToTear(
    const CATLISTP(CATEdge) &iEdgesToTear,
    CATLONG32 &oNbAmbiguities,
    CATLISTP(CATEdge) &oCandidateEdgesToTear,
    CATLISTP(CATEdge) &oInvalidInputEdges,
    CATLISTP(CATEdge) *ioMandatoryCandidates = 0,
    CATLISTP(CATEdge) *ioOptionalCandidates = 0) = 0;

  // Returns the edges which are to be compulsorily torn
  // ACCESS: For Ruled Shell Unfold only
  virtual CATLISTP(CATEdge) GetEdgesMustToTear() = 0;

  //To switch on/off a specific treatment of edges-to-tear. Specially for GSD, when CGM edges are treated in a group.
  // For example, when the edges-to-tear are internal as always and G1 continuous, then they can be taken as one
  // group to tear. 
  // ACCESS: For both Shell Unfold modes
  //
  // NOTE: By default, clustering is on for Ruled Unfold, while it is off for FrF Shell Unfold.
  //
  // iMakeCluster = 0 or 1 to switch OFF or ON the clustering
  virtual void TreatEdgesToTearAsCluster(int iMakeCluster) = 0;

  //Set parameters to define an initial axis system
  // iVertxOrign: Vertex on initial shell to be taken as origin
  // iEdgeX:      An edge bounded by iVertxOrign, this defines X-axis (N.B. Currently, this should ONLY be one of the border edges or edges-to-tear)
  // iFace:       A face bounded by iEdgeX, this governs Y-axis. Necessary to give if iEdgeX is not a border edge
  //
  //Returns non-zero on failure, e.g.
  // if the provided cells are not related
  // or if the iEdgeX is not a border edge & a NULL iFace is provided
  virtual int SetInitialLocation(
    CATVertex *iVertxOrign,
    CATEdge *iEdgeX,
    CATFace *iFace = 0) = 0;

  //Set parameters to define location of unfolded shell
  // iFixedWire:will keep the same location, tangent and normal to shell at its beginning vertex
  // iFixedWire is a Body containing only one Wire
  // It must be possible to laid down iFixedWire on shell (compatible with CATIPGMLayDownOperator).
  // First Edge of iFixedWire should not lie on a Sharp Edge.
  virtual void SetInitialLocation(CATBody *iFixedWire) = 0;

  //Set target axis system; to be called only after InitialLocation has been set, throws otherwise.
  // iTargetPlane: Plane defining a target axis system  
  virtual void SetTargetLocation(const CATMathPlane *iTargetPlane) = 0;

  //Set one Tool on a list of face (First use is the strectch coef )
  // Need to be call for each tool
  // ACCESS: For Ruled Shell Unfold only
  virtual void SetToolData(const CATLISTP(CATFace) *ListOfCATFace, double *Tool) = 0;

  // Set options for output journal
  virtual void SetJournalOptions(
    const CATBoolean iDifferentiateTearedEdges = FALSE,
    const CATCGMJournal::Type iItemType = CATCGMJournal::Creation) = 0;

  //Runs the operator
  // IMPORTANT INSTRUCTIONS: In case of FrFShellUnfold, Run doesn't guarantee the computation of Result.
  // Hence, it is very important to call GetResult method before calling any other post-Run methods like
  // GetCellImage, RunTransfer except functions for pre-visualization of distortion
  virtual int Run() = 0;

  // Returns the result of the transformation	
  //CATBody* GetResult();	use TopOperator's
  //Operate wire or vertex transfert from fold to unfold, or reverse. Input elements are layed by the operator. Output elements are not.
  //ACCESS: In case of FrF Shell Unfold, only after calling GetResult. See IMPORTANT INSTRUCTIONS for Run()
  //        No such restriction in case of Ruled Shell Unfold, can be called after Run()
  //
  // iBody : Body containing elements to transfert. It can be multi-domain from R18
  // oBody : Resulting body (created by the operator)
  // iReport : Journal
  // iReverse : FALSE by default, TRUE if the input elements are to lay on the previously unfolded body
  //
  // NOTE: The resulting curves are cleaned in case of FrF shell unfold. Hence, there may be some deviation warnings appended to ...
  //       the operator after calling RunTransfer. It is advisable to check for appended warnings after calling RunTransfer
  virtual void RunTransfer(
    CATBody *iBody,
    CATBody *&oBody,
    CATCGMJournalList *iReport,
    CATBoolean iReverse = FALSE) = 0;

  // Change the lying on tolerance for transfert
  virtual void SetTransfertTolerance(double iTol) = 0;

  // Get 2D transformation
  // return resulting face if transformation is found
  virtual CATFace *GetTransformation2D(
    CATFace *iFace,
    CATMathTransformation2D &oTransformation2D) = 0;

  //=========================================================================================
  // New Methods
  //=========================================================================================  
  // --- Requested by GSD, ONLY USEFUL FOR R16. Use it to define the initial axis system ---
  // Takes a plane, tangential to a face, subject to the following condition:
  // o	Origin of the plane should be near enough (within 0.1 mm) to the shell so that it 
  //    can be laid down on a face. 
  // o	Also, this lay down should not occur on an Edge-to-tear (which is a candidate for 
  //    future versions of FreeForm operator), because it will make positioning unstable as 
  //    there are going to be two images of the Edge-to-tear (one per bounded face) in the
  //    flattened skin. In such case, one should specify the support face to avoid a throw.
  virtual int SetInitialLocation(
    const CATMathPlane &iIniPlane,
    CATFace *iSuppFace = NULL) = 0;

  //------------------------------------------------------------------------------------------
  // Methods for pre-visualization of distortion, only useful for Free Form Shell Unfold
  //------------------------------------------------------------------------------------------
  //Provides important tesselation statistics
  // Note that oNbNodes tells the number of vertices used in triangulization. It is quite possible that 
  // that the maximum node index is more than oNbNodes. For example, if there are 4 nodes (oNbNodes=4)
  // in the mesh, there indices can be {1, 3, 4, 5}
  //
  //ACCESS: For FrF Shell Unfold only
  //
  //Returns non-zero if called before Run
  virtual int GetPreviewStats(int &oNbTriangles, int &oNbNodes) = 0;

  //Provides flattening data:
  // ioUV            : Parametric values for nodes scaled to unit square. Size = 2 * NbNodes. Not filled if NULL
  // ioXYZAfter      : 3d flattened coordinates. Size = 3 * NbNodes. Not filled if NULL
  // ioXYZBefore     : 3d un-flattened (of input skin) coordinates. Size = 3 * NbNodes. Not filled if NULL
  // ioNormalAfter[3]: 3D Normal of the plane of flattened skin. Not filled if NULL
  // ioNormalsBefore : 3D Normals of the input skin at nodes. Size = 3 * NbNodes. Not filled if NULL
  // ioTriangles     : Indices of bounding nodes of each triangle. Size = 3 * NbTriangles. Not filled if NULL
  //
  //Returns non-zero if called before Run
  //ACCESS: For FrF Shell Unfold only
  //
  //For performance sake, it is highly recommended to allocate the memory for the required arrays ONLY ONCE...
  // after gathering the size information from GetPreviewStats. Also, usually this function will be called 
  // several times after calls to ApplyCorrection. In such cases, it is not neccessary to retrieve ioXYZBefore,
  // ioNormalsBefore and ioTriangles again and again, as they don't change after Run has been called. Thus, it is
  // recommended to pass NULL for these three values after fetching them through first call to this method.
  virtual int GetPreviewData(
    double *ioUV,
    double *ioXYZAfter,
    double *ioXYZBefore,
    double   ioNormalAfter[3],
    double *ioNormalsBefore,
    int *ioTriangles) = 0;

  //Triggers Distortion computation
  //ACCESS: For FrF Shell Unfold only
  //
  //To define distortion value, let P2d = length/area/angle parameter of Flattened Output element
  // and let P3d = corresponding length/area/angle parameter of 3d Input element
  //       -------------------------------------
  // then, |   Distortion = (P2d - P3d)/P3d    |
  //       -------------------------------------  
  // A positive distortion means streching of Flattened element, while negative means shrinking.
  //
  //Returns non-zero if called before Run or after GetResult or invalid iType
  virtual int ComputeDistortion(
    const int &iType,
    double &oMinDistortion,
    double &oMaxDistortion,
    double &oMedianDistortion) = 0;

  //Provides distortion value at a node of tesselation
  //ACCESS: For FrF Shell Unfold only
  //
  // 0 <= iNodeIndex < oNbNodes
  //
  //Returns non-zero if called before ComputeDistortion or invalid iNodeIndex is used
  virtual int GetDistortionAtNode(const int &iNodeIndex, double &oDistortion) = 0;

  //To play with the distortion if the requested type is not angle
  //ACCESS: For FrF Shell Unfold only
  //
  //iRatio: in [0,1], to scale distortion to desired value. This ratio indicates the
  //        fraction of points with positive/stretching distortion.
  //
  //Examples:
  //iRatio = 0   corresponds to only shrinking (i.e. the distortion at 0% of the computation
  //             points is positive, i.e. the distortion is negative at all the points). 
  //             This means the flattened body is smaller than the input body.
  //iRatio = 1   corresponds to only stretching (i.e. the distortion at 100% of the 
  //             computation points is positive). This means the flattened body is larger
  //             than the input body. 
  //iRatio = 0.5 corresponds to even distortion (i.e. there are as many (50%) points with 
  //            stretching distortion as there are with shrinking distortion)  
  //An intermediate value, say 0.85, means 85% points have stretching distortion, which
  //implies 15% of the points have shrinking distortion
  //
  //
  //Returns non-zero if called before ComputeDistortion or after GetResult or  invalid iRatio or ...
  //if requested distortion type is Angle type in ComputeDistortion
  virtual int ApplyCorrection(
    const double &iRatio,
    double &oMinDistortion,
    double &oMaxDistortion,
    double &oMedianDistortion) = 0;

  //Provides distortion value at a point by giving its parametric values
  //ACCESS: For FrF Shell Unfold only
  //
  //Returns non-zero if called before ComputeDistortion or if point(iU, iV) is out of mesh
  virtual int GetDistortionForUV(
    const double &iU,
    const double &iV,
    double &oDistortion) = 0;

  //------------------------------------------------------------------------------------------
  // New Result retrieval methods
  //------------------------------------------------------------------------------------------
  //Provides the output image of a cell in the input body or vice-versa
  //Requested by ship-building team, to avoid use of journal. 
  //ACCESS: In case of FrF Shell Unfold, only after calling GetResult. See IMPORTANT INSTRUCTIONS for Run()
  //        No such restriction in case of Ruled Shell Unfold, can be called after Run()
  //
  //iCell: The Cell whose image is needed, if iReverse is FALSE, iCell should be in the 3D body
  //oCellsInOtherImage: The image Cells in the flattened body, if iReverse is FALSE, these will be in flattened body
  //iReverse : FALSE by default, TRUE if the iCell is in flattened body and oCellsInOtherImage are needed in 3D body
  //
  //Returns non-zero if iCell is not in 3D body if iReverse is FALSE, or if iCell is not in flattened body if iReverse is TRUE
  virtual int GetCellImage(
    CATCell *iCell,
    CATLISTP(CATCell) &oCellsInOtherImage,
    CATBoolean iReverse = FALSE) = 0;

  //Operate wire or vertex transfer from fold to unfold, or reverse. Input elements are layed by the operator. Output elements are not.
  //ACCESS: In case of FrF Shell Unfold, only after calling GetResult. See IMPORTANT INSTRUCTIONS for Run()
  //        No such restriction in case of Ruled Shell Unfold, can be called after Run()
  //
  //Returns non-zero if iCellInInputBody is not in input body
  // iBodiesToTransfer : Bodies to transfer.
  // ioBodiesTransferred : Resulting bodies (created by the operator)
  // iReport : Journal
  // iReverse : FALSE by default, TRUE if the input elements are to lay on the previously unfolded body
  //
  //Returns 0 if successful. Returns the non-zero index of the body in iBodiesToTransfer which fails to transfer, in such case...
  //the caller needs to manage the first index-1 transferred bodies, available in ioBodiesTransferred.
  //
  // NOTE: The resulting curves are cleaned in case of FrF shell unfold. Hence, there may be some deviation warnings appended to ...
  //       the operator after calling RunTransfer. It is advisable to check for appended warnings after calling RunTransfer
  virtual int RunTransfer(
    const CATLISTP(CATBody) &iBodiesToTransfer,
    CATLISTP(CATBody) &ioBodiesTransferred,
    CATCGMJournalList *iReport,
    CATBoolean iReverse = FALSE) = 0;

  //Info about sharp internal corners, which are not allowed by FrF Unfold
  //ACCESS: For FrF Shell Unfold only
  //
  //...
  virtual void GetSharpCornerInfo(CATLISTP(CATCell) &oSharpCorners) = 0;

  //------------------------------------------------------------------------------------------
  // Fixation/Image of the bondary : FrF Only : 
  //------------------------------------------------------------------------------------------
  //To constrain edges from distorting
  //ACCESS: For FrF Shell Unfold only
  //
  virtual void SetCellsToFix(
    const CATLISTP(CATCell) &iCellsToFix,
    const CATListOfDouble *iAnglesAtWireEnd = NULL) = 0;

  //For each wire to constraint (wtc), there should be corresponding image wire (wi).
  // Each wi should have same number of edges as in wtc. Further, for each wire pair,
  // one shall specify the desired angle at both the wire extremities. This is the 
  // angle which wire at respective extremity makes with the next edge on the skin. 
  // Thus, for n numbder of wtc, there should be 2*n number of angles. Closed wires
  // are not handled yet.
  virtual void SetWireImages(
    const CATLISTP(CATBody) &iWiresToConstraint,
    const CATLISTP(CATBody) &iWiresImages,
    const CATListOfDouble &iAnglesAtWireEnd,
    const CATLaw **iLaws = NULL) = 0;

  //------------------------------------------------------------------------------------------
  //nodoc 
  // deprecated
  virtual void SetLevel(int iLevel) = 0;

  //------------------------------------------------------------------------------------------
  // Quality : FrF Only : 
  //------------------------------------------------------------------------------------------
  //To request forcing bijection (less gaps or smaller slides) among the 
  // constituent curves of an edge. This will try to have better representation
  // at the edges and in thus, make the computations SLOW.
  //ACCESS: For FrF Shell Unfold only
  virtual void SetAccurateEdgeMerging() = 0;

  //------------------------------------------------------------------------------------------
  // FrF Only : SetRigidifiedFlatArea 
  //------------------------------------------------------------------------------------------
  // Rigidified flat areas of the shell :
  //  iMinMaxRadiusLimit[0] : Min Radius : On curved areas the local radius is smaller.
  //  iMinMaxRadiusLimit[1] : Max Radius : Flat areas are above this radius 
  // SolvingRatio : ratio for using curvature data in the deformation
  //               0: The shape is not modified ( same result)
  virtual void SetRigidifiedFlatArea(
    double iMinMaxRadiusLimit[2],
    double SolvingRatio) = 0;

  //------------------------------------------------------------------------------------------
  // FrF Only : SetAutoScalingOnFlateArea
  //------------------------------------------------------------------------------------------
  // AutoScaling to keep Flat area unchanged
  virtual void SetAutoScalingOnFlateArea(CATLONG32 AutoScalingOn) = 0;

  //------------------------------------------------------------------------------------------
  // sticker
  //------------------------------------------------------------------------------------------
  // Force the computation of the mappingFunction
  virtual void SetForceMappingFunctionComputation() = 0;

  //
  virtual void GetMappingFunction(CATPolyMeshMappingFunction *&MappingFunction) = 0;

  // Force the of Advanved mesh
  virtual void SetAdvancedMesh(double *) = 0;

  /**
  * SetUVBoxLowerCorner 
  * To define the lower corner of the resulting UVBox.
  * @param iLowerCornerUV
  * the coordinates uv of the lower corner
  */
  virtual void SetUVBoxLowerCorner(const double iLowerCornerUV[2])=0;

  /**
  * SetUVBoxMaxLength
  * To define the length of the largest UV directions. 
  * Do not change anisotropy (lengthU/lengthV) of the result.
  * @param iLenght
  * the Max(Umax-Umin, Vmax-Vmin) will be equal to the given value of iLenght.
  */
  virtual void SetUVBoxMaxLength(const double iLenght)=0;

  /**
  * @SetTexturingContext
  * To define the uv coordinates in the range [0,1].
  * Do not change anisotropy (lengthU/lengthV) of the result.
  * CAREFUL : this method calls SetResultLowerCorner( (0,0) and SetTheLargestUVDirectionsLength( 1. ).
  *           So do not call @SetResultLowerCorner or @SetTheLargestUVDirectionsLength after SetTexturingContext
  */
  virtual void SetTexturingContext()=0;

  /**
   * Sets a flag that indicates to put an attribute in the resulting unfolded
   * shell to track its corresponding input shell via its tag. By default the
   * attribute will not be added to the unfolded shell.
   * @param iDoCreate
   *   If <tt>TRUE</tt> will create and add the attribute; otherwise not.
   */
  virtual void CreateUnfoldedShellTrackingAttribute(CATBoolean iDoCreate) = 0;

#if !defined(_AIX_SOURCE) && !defined(_LINUX_SOURCE) && defined(CATIAR423)
  //------------------------------------------------------------------------------------------
  // FrF Only : ReduceDistortions
  //------------------------------------------------------------------------------------------
  /**
   * Sets a flag that enables improvement in length or area distortions in unfold output with respect to input shell
   * @param iMode
   *   If <tt>1</tt> it will reduce boundary length distortion: Should be used for singly curved input surfaces. Output is body with Nurbs surfaces
   *   If <tt>2</tt> it will reduce area distortion: Should be used for singly curved input surfaces. Output is body with Nurbs surfaces
   *   If <tt>3</tt> it will reduce boundary length distortion: Can be used for singly as well as doubly curved input surfaces. Output is body with plane surface
   *   For any other value, there will not be any effect and previous setting (if any) will be used
   */
  virtual void ReduceDistortions(short iMode) = 0;
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopShellUnfold(); // -> delete can't be called
};

// Global Create functions, use them to create the operator
//DEPRECATED
// iFactory:        Input factory
// iTopData:        Top Data
// iBody:           Input Body
// iFacesToUnfold:  Faces to unfold, all should belong to a single shell
//                  If NULL, and if iBody has only one shell, all the faces of this shell
//                  are unfolded. Must not be NULL if iBody has more than one shell.
// iEdgesToTear:    Edges to tear in case of ambiguity
//                  If this is NULL or not sufficient to remove all ambiguities, and
//                  later, one doesn't remove all ambiguities using SetEdgesToTear, the
//                  remaining ambiguities are removed by automatically choosing additional
//                  edges to tear. This automatic selection depends on order of faces in 
//                  iFacesToUnfold (or if iFacesToUnfold is NULL, on order of faces in the
//                  shell of iBody)
//            NOTE: Once SetEdgesToTear is called on the created operator, iEdgesToTear
//                  provided here are no more respected. It is RECOMMENDED to keep default
//                  iEdgesToTear = 0 and explore SetEdgesToTear instead.
// iMethod:         Surface development method,
//                  effective in case of a non-developable surface
//DEPRECATED
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopShellUnfold *CATPGMCreateTopShellUnfold(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATLISTP(CATFace) *iFacesToUnfold,
  CATLISTP(CATEdge) *iEdgesToTear = 0,
  CATShellUnfoldMethod iMethod = CATShellUnfoldRotation);

// Global Create functions, use them to create the operator
//DEPRECATED
// iFactory:        Input factory
// iTopData:        Top Data
// iBody:           Input Body
// iShellToUnfold:  Shell to unfold, all the faces of which will be unfolded
//                  If NULL, and if iBody has only one shell, all the faces of this shell
//                  are unfolded. Must not be NULL if iBody has more than one shell.
// iEdgesToTear:    Edges to tear in case of ambiguity
//                  If this is NULL or not sufficient to remove all ambiguities, and
//                  later, one doesn't remove all ambiguities using SetEdgesToTear, the
//                  remaining ambiguities are removed by automatically choosing additional
//                  edges to tear. This automatic selection depends on order of faces in
//                  the shell of iBody, iShellToUnfold.
//            NOTE: Once SetEdgesToTear is called on the created operator, iEdgesToTear
//                  provided here are no more respected. It is RECOMMENDED to keep default
//                  iEdgesToTear = 0 and explore SetEdgesToTear instead.
// iMethod:         Surface development method,
//                  effective in case of a non-developable surface
//DEPRECATED
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopShellUnfold *CATPGMCreateTopShellUnfold(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATShell *iShellToUnfold,
  CATLISTP(CATEdge) *iEdgesToTear = 0,
  CATShellUnfoldMethod iMethod = CATShellUnfoldRotation);

#endif /* CATIPGMTopShellUnfold_h_ */
