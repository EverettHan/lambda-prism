#ifndef CATIPGMTopShellFlattener_h_
#define CATIPGMTopShellFlattener_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"

#include "CATCGMJournal.h"

#include "CATListOfDouble.h"

#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATBody.h"

#include "CATShellUnfoldMethod.h"

class CATBody;
class CATEdge;
class CATFace;
class CATVertex;
class CATGeoFactory;
class CATLISTP_CATBody_;
class CATLISTP_CATEdge_;
class CATLISTP_CATFace_;
class CATMathPlane;
class CATShell;
class CATPlane;
class CATLISTP(CATFace);
class CATLISTP(CATEdge);
class CATMathTransformation2D;
class CATLaw;

//enum CATShellUnfoldMethod;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopShellFlattener;

//-----------------------------------------------------------------------
//
// Operator for flattening ruled/torus surfaces with zero radius bend support
//
class ExportedByCATGMOperatorsInterfaces CATIPGMTopShellFlattener: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopShellFlattener();

	//
	// Changes the method of development action
	// 
	virtual void SetUnfoldMethod(CATShellUnfoldMethod iMethod) = 0;

	//
	// Set edges to tear
	// WARNING : Call to SetZeroRadiusBendFaces  and SetZeroRadiusBendEdges is mandatory before calling this method
	//
	// NOTE: Once SetEdgesToTear is called, the edges-to-tear (iEdgesToTear) provided at the time of...
	//       operator construction are no more respected.
	//
	// iEdgesToTear:    Edges to tear in case of ambiguity
	//                  If this is not sufficient to remove all ambiguities, and
	//                  later, one doesn't remove all ambiguities using SetEdgesToTear again, the
	//                  remaining ambiguities are removed by automatically choosing additional
	//                  edges to tear. This automatic selection depends on order of faces in the 
	//                  "list of faces"/"shell" if provided to the constructor, else on the shell
	//                  of Body provided to the constructor
	//
	// oNbAmbiguities:   Number of ambiguities, still unresolved with iEdgesToTear
	//
	// oCandidateEdgesToTear: Edges which can be selected further to reduce ambiguity
	//
	// oInvalidInputEdges:   * Edges out of iEdgesToTear, which cannot be used for tearing.
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
	// Returns  TRUE     if iEdgesToTear + GetEdgesMustToTear together can be taken as edges-to-tear. This ...
	//                   doesn't mean that all the ambiguities are removed. oNbAmbiguities can still be non-zero.
	//          FALSE    if iEdgesToTear + GetEdgesMustToTear together cannot be taken as edges-to-tear, as this will...
	//                   result in a non-connex output. Note that if iEdgesToTear is empty, that means this shell is...
	//                   impossible to Unfold. One reason can be the presence of GetEdgesMustToTear, which can cause...
	//                   a non-connex result.  
	//
	virtual CATBoolean SetEdgesToTear(
    const CATLISTP(CATEdge) &iEdgesToTear,
	CATLONG32 &oNbAmbiguities,
    CATLISTP(CATEdge) &oCandidateEdgesToTear,
    CATLISTP(CATEdge) &oInvalidInputEdges,
    CATLISTP(CATEdge) *ioMandatoryCandidates = NULL,
    CATLISTP(CATEdge) *ioOptionalCandidates = NULL) = 0;

	//
	// Set parameters to define an initial axis system
	// iVertxOrign: Vertex on initial shell to be taken as origin
	// iEdgeX:      An edge bounded by iVertxOrign, this defines X-axis (N.B. Currently, this should ONLY be one of the border edges or edges-to-tear)
	// iFace:       A face bounded by iEdgeX, this governs Y-axis. Necessary to give if iEdgeX is not a border edge
	//
	// Returns non-zero on failure, e.g.
	// if the provided cells are not related
	// or if the iEdgeX is not a border edge & a NULL iFace is provided
	//
  virtual int SetInitialLocation(
    CATVertex *ipVertxOrign,
    CATEdge *ipEdgeX,
    CATFace *ipFace = NULL) = 0;

	//
	// --- Requested by GSD, ONLY USEFUL FOR R16. Use it to define the initial axis system ---
	// Takes a plane, tangential to a face, subject to the following condition:
	// o	Origin of the plane should be near enough (within 0.1 mm) to the shell so that it 
	//    can be laid down on a face. 
	// o	Also, this lay down should not occur on an Edge-to-tear (which is a candidate for 
	//    future versions of FreeForm operator), because it will make positioning unstable as 
	//    there are going to be two images of the Edge-to-tear (one per bounded face) in the
	//    flattened skin. In such case, one should specify the support face to avoid a throw.
	//
  virtual int SetInitialLocation(
    const CATMathPlane &ipIniPlane,
    CATFace *ipSuppFace = NULL) = 0;

	//
	// Set parameters to define location of unfolded shell
	// iFixedWire:will keep the same location, tangent and normal to shell at its beginning vertex
	// iFixedWire is a Body containing only one Wire
  // It must be possible to laid down iFixedWire on shell (compatible with CATIPGMLayDownOperator).
	// First Edge of iFixedWire should not lie on a Sharp Edge.
	//
	virtual void SetInitialLocation(CATBody * ipFixedWire) = 0;

	//
	// Set target axis system; to be called only after InitialLocation has been set, throws otherwise.
	// iTargetPlane: Plane defining a target axis system  
	//
	virtual void SetTargetLocation(const CATMathPlane * ipTargetPlane) = 0;

	//
	// Set one Tool on a list of face (First use is the strectch coef )
	// Need to be call for each tool
	// 
  virtual void SetToolData(
    const CATLISTP(CATFace) *iplistOfCATFace,
    double *pTool) = 0;

	//
	// Set options for output journal
	//
	virtual void SetJournalOptions(
	  const CATBoolean			iDifferentiateTearedEdges = FALSE, 
	  const CATCGMJournal::Type	iItemType				  = CATCGMJournal::Creation) = 0;

	//
	// For each wire to constraint (wtc), there should be corresponding image wire (wi).
	// Each wi should have same number of edges as in wtc. Further, for each wire pair,
	// one shall specify the desired angle at both the wire extremities. This is the 
	// angle which wire at respective extremity makes with the next edge on the skin. 
	// Thus, for n numbder of wtc, there should be 2*n number of angles. Closed wires
	// are not handled yet.
	//
	virtual void SetWireImages(
    const CATLISTP(CATBody) &iWiresToConstraint,
    const CATLISTP(CATBody) &iWiresImages,
	const CATListOfDouble	&	iAnglesAtWireEnd,
	const CATLaw				**	iLaws =	NULL) = 0;

	//
	// Set the zero radius bend edges
	// iListOfBendEdges – List of edges for which there is zero bend radius
	// iListOfArcLengths – List of arc lengths corresponding to the zero bend edges
	// iListOfStretchFactors – List of stretch factors for these zero bends
	//
	virtual void SetZeroRadiusBendEdges(
      const CATLISTP(CATEdge) &iListOfBendEdges,
	  const CATListOfDouble	& iListOfArcLengths, 
      const CATListOfDouble	& iListOfBendEdgeStretchFactors) = 0;

	//
	// Set the bend faces
	// iListOfBendFaces – List of faces which are bend faces. Stretch factors are applied to such faces
	// iListOfStretchFactors – List of stretch factors. Can be same for all faces.
	//
	virtual void SetBendFaces(
      const CATLISTP(CATFace) &iListOfBendFaces,
     const CATListOfDouble	& iListOfBendFaceStretchFactors) = 0;

	//
	// Change the lying on tolerance for transfert
	//
	virtual void SetTransfertTolerance(double iTol) = 0;

	//
  //WARNING : Call to RunTransfer is mandatory After calling Run method
  //Operate wire or vertex transfert from fold to unfold, or reverse. Input elements are layed by the operator. Output elements are not.
	// Returns the result of the transformation	
	// CATBody* GetResult();	use TopOperator's
	// Operate wire or vertex transfert from fold to unfold, or reverse. Input elements are layed by the operator. Output elements are not.
	//
	// iBody : Body containing elements to transfert. It can be multi-domain from R18
	// oBody : Resulting body (created by the operator)
	// iReport : Journal
	// iReverse : FALSE by default, TRUE if the input elements are to lay on the previously unfolded body
	//
  virtual void RunTransfer(
    CATBody *ipBody,
    CATBody *&opBody,
    CATCGMJournalList *ipReport,
    CATBoolean iReverse = FALSE) = 0;

  //
  //WARNING : Call to RunTransfer is mandatory After calling Run method
  //Operate wire or vertex transfert from fold to unfold, or reverse. Input elements are layed by the operator. Output elements are not.
	// Operate wire or vertex transfer from fold to unfold, or reverse. Input elements are layed by the operator. Output elements are not.
	// Returns non-zero if iCellInInputBody is not in input body
	// iBodiesToTransfer : Bodies to transfer.
	// ioBodiesTransferred : Resulting bodies (created by the operator)
	// iReport : Journal
	// iReverse : FALSE by default, TRUE if the input elements are to lay on the previously unfolded body
	// Returns 0 if successful. Returns the non-zero index of the body in iBodiesToTransfer which fails to transfer, in such case...
	// the caller needs to manage the first index-1 transferred bodies, available in ioBodiesTransferred.
	//
	virtual int RunTransfer(
    const CATLISTP(CATBody) &iBodiesToTransfer,
    CATLISTP(CATBody) &ioBodiesTransferred,
    CATCGMJournalList *ipReport,
    CATBoolean iReverse = FALSE) = 0;

	//
	// Runs the operator
	// IMPORTANT INSTRUCTIONS: Run doesn't guarantee the computation of Result.
	// Hence, it is very important to call GetResult method before calling any other post-Run methods like
	// GetCellImage, RunTransfer except functions for pre-visualization of distortion
	//
	virtual int Run() = 0;

	//
	// To switch on/off a specific treatment of edges-to-tear. Specially for GSD, when CGM edges are treated in a group.
	// For example, when the edges-to-tear are internal as always and G1 continuous, then they can be taken as one
	// group to tear. 
	//
	// NOTE: By default, clustering is on for Ruled Unfold, while it is off for FrF Shell Unfold.
	//
	// iMakeCluster = 0 or 1 to switch OFF or ON the clustering
	//
	virtual void TreatEdgesToTearAsCluster(int iMakeCluster) = 0;

	//
	// Returns the edges which are to be compulsorily torn
	// 
  virtual CATLISTP(CATEdge) GetEdgesMustToTear() = 0;

	//
	// Get 2D transformation
	// return resulting face if transformation is found
	//
  virtual CATFace *GetTransformation2D(
    CATFace *ipFace,
    CATMathTransformation2D &oTransformation2D) = 0;

	//
	// Provides the output image of a cell in the input body or vice-versa
	// Requested by ship-building team, to avoid use of journal. 
	// iCell: The Cell whose image is needed, if iReverse is FALSE, iCell should be in the 3D body
	// oCellsInOtherImage: The image Cells in the flattened body, if iReverse is FALSE, these will be in flattened body
	// iReverse : FALSE by default, TRUE if the iCell is in flattened body and oCellsInOtherImage are needed in 3D body
	// Returns non-zero if iCell is not in 3D body if iReverse is FALSE, or if iCell is not in flattened body if iReverse is TRUE
	//
  virtual int GetCellImage(
    CATCell *ipCell,
    CATLISTP(CATCell) &oCellsInOtherImage,
    CATBoolean iReverse = FALSE) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopShellFlattener(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopShellFlattener *CATPGMCreateTopShellFlattener(
																						  CATGeoFactory	 * ipFactory,
																						  CATTopData	 * ipTopData,
																						  const CATBody	 * ipOriginalBody,
																						  const CATShell * ipShellToFlatten = NULL,
																						  const CATEdge	 * ipConstrainedEdge = NULL,
																						  const CATFace  * ipFirstFace = NULL);

#endif /* CATIPGMTopShellFlattener_h_ */
