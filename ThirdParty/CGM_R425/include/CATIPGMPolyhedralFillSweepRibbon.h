#ifndef CATIPGMPolyhedralFillSweepRibbon_h_
#define CATIPGMPolyhedralFillSweepRibbon_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPolyTopOperator.h"
#include "ListPOfCATVertex.h"

class CATBody;
class CATCell;
class CATEdge;
class CATGMPolyOperTopExt;
class CATGeoFactory;
class CATTopData;
class CATVertex;
class CATMathDirection;


extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMPolyhedralFillSweepRibbon;

/**
* <b>Role:</b> This operator produces a polyhedral CATBody
* while completing a ribbon shape along a guide wire,
* filling the spaces between successive sweep surfaces associated to guide edges.
* If the guide is an open wire, it's mandatory to associate sweep surfaces on the first and last edges.
* Fill surfaces will be computed between successive sweep surfaces, sharing a guide vertex or separated by guide edges.
* The guide can contain several domains but has to be manifold (no common vertices shared but several wires)
* This operator currently only works for polyhedral CATBody inputs.
**/
class ExportedByCATGMOperatorsInterfaces CATIPGMPolyhedralFillSweepRibbon: public CATIPGMPolyTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPolyhedralFillSweepRibbon();


  //=============================================================================
  // Settings
  //=============================================================================

  /**
  * Adds a Sweep body built from a part of the guide wire body
  * with additional information to distinguish its boundary edges in contact with the guide 
  * and its boundary edges on the opposite side
  * @param iSweepBody
  * The input body to add as part of the final ribbon
  * @param iFreeEdgesOnGuide
  * List of edges bounding the sweep surface, in contact with the guide wire body
  * @param iOppositeFreeEdges
  * List of edges bounding the sweep surface, built from the guide on the opposite side
  * @param iListOfFacesToRemove
  * optional List of faces to remove from iSweepBody
  * This list is mandatory for subset of faces which doesn't follow the input guide (without any edge in contact with the guide)
  * @return
  * The integer value associated to the new Sweep part, equals to the number of recorded Sweep bodies including this one.
  * If the SweepBody is not correctly defined (null body, empty lists of border edges), 
  * or if this method is called after Run(), then it returns 0 without recording the data as inputs
  */
  virtual int AddSweepBody(
    CATBody *iSweepBody,
    const CATLISTP(CATCell) &iFreeEdgesOnGuide,
    const CATLISTP(CATCell) &iOppositeFreeEdges, 
    const CATLISTP(CATCell) * iListOfFacesToRemove = 0) = 0;

  /**
  * Adds a specification of transition as a new sweep between 2 sweep bodies defined by their ID (see AddSweepBody API)
  * This transition specification leads to generate a kind of sweep if the previous and next profiles are similar, 
  * else it will generate a kind of Blend which can be driven by an optional coupling (see optional arguments)
  *
  * @param iPrevSweepBodyID
  * The ID of the previous sweep body according to the guide wire orientation
  * @param iNextSweepBodyID
  * The ID of the next sweep body according to the guide wire orientation
  *
  * @param iPrevCouplingBody
  * optional Body containing vertices lying on the end side of the previous sweep body, 
  * to associate to vertices of the next sweep body on its start side
  * This body can be the previous SweepBody itself, or another one adding vertices on the side edges
  * This body can be exact instead of polyhedral if its dimension is 0
  * @param iNextCouplingBody
  * optional Body containing vertices lying on the start side of the next sweep body, 
  * to associate to vertices of the previous sweep body on its end side
  * This body can be the next SweepBody itself, or another one adding vertices on the side edges
  * This body can be exact instead of polyhedral if its dimension is 0
  *
  * @param iPrevCouplingVertices
  * optional List of vertices belonging to iPrevCouplingBody, lying on the end side of the previous sweep body, 
  * to couple with side vertices of the next sweep body
  * This list has to be ordered from the guide to the opposite free corner
  * A vertex can be repeated in order to be linked with multiple side vertices of the next sweep body
  * This optional list (may be NULL) has to be filled consistently with iNextCouplingVertices (same size)
  * @param iNextCouplingVertices
  * optional List of vertices belonging to iNextCouplingBody, lying on the start side of the next sweep body, 
  * to couple with side vertices of the previous sweep body
  * This list has to be ordered from the guide to the opposite free corner
  * A vertex can be repeated in order to be linked with multiple side vertices of the previous sweep body
  * optional List of faces to remove from iSweepBody
  * This optional list (may be NULL) has to be filled consistently with iPrevCouplingVertices (same size)
  *
  * @return
  * The integer value as ID associated to the new transition, equals to the number of recorded transitions including this one.
  * If the input data are not correctly defined (null ID, lists with different sizes), 
  * or if this method is called after Run(), then it returns 0 without recording this data as inputs
  */
  virtual int AddSweepTransition(
    int iPrevSweepBodyID, 
    int iNextSweepBodyID, 
    CATBody * iPrevCouplingBody=NULL, 
    CATBody * iNextCouplingBody=NULL, 
    const ListPOfCATVertex * iPrevCouplingVertices=NULL, 
    const ListPOfCATVertex * iNextCouplingVertices=NULL) = 0;

  /**
  * @param iDraftDirection
  * The mathematical direction as reference for all the input sweep bodies
  * This knowledge will help the computation to find the best way to connect adjacent sweep bodies to each others
  */
  virtual void SetRefDraftDirection(const CATMathDirection &iDraftDirection) = 0;


  
	//=============================================================================
	// Get additional information after Run
	//=============================================================================

	/**
	* Retrieves the output boundary edges that are on the ribbon’s side corresponding to the input guide wire body.
	* @param oBoundaryEdgesOnGuide
	* The list of edges retrieved from the result boundary, in contact with the guide
	* @param oEdgesOriVsGuide
	* The list of relative orientations of edges versus the input guide wire body orientation
	* @param ioRibbonSideVsOrientedEdges
	* optional pointer to get the side (left or right) of the ribbon surface seen from the border edges according to their associated orientations
	*/
	virtual void GetOutputBoundaryEdgesOnGuide(CATLISTP(CATCell) &oBoundaryEdgesOnGuide, CATListOfInt &oEdgesOriVsGuide, CATSide *ioRibbonSideVsOrientedEdges = 0) = 0;

	
	/**
	* Retrieves the output boundary edges that are on the ribbon’s opposite side relatively to the input guide wire body.
	* @param oOppositeBoundaryEdges
	* The list of edges retrieved from the result boundary, opposite to the guide
	* @param oEdgesOriVsGuide
	* The list of relative orientations of edges versus the input wire body orientation
	* @param ioRibbonSideVsOrientedEdges
	* optional pointer to get the side (left or right) of the ribbon surface seen from the border edges according to their associated orientations
	*/
	virtual void GetOutputOppositeBoundaryEdges(CATLISTP(CATCell) &oOppositeBoundaryEdges, CATListOfInt &oEdgesOriVsGuide, CATSide *ioRibbonSideVsOrientedEdges = 0) = 0;


  /**
	* Retrieves the output faces that have been created to fill spaces between sweep ribbon.
	* @param oFillFaces
	* The list of faces created to fill spaces between input sweep ribbon
	*/
	virtual void GetAllOutputFillFaces(CATLISTP(CATCell) &oFillFaces) = 0;


  /**
  * Get the number of input SweepBodies given through the AddSweepBody API
  * and accepted by the operator, with a not null returned ID [ between 1 and GetNbInputSweepBodies() ]
  * @return
  * The integer number of input SweepBodies with valid associated ID (greater than 0)
  */
  virtual int GetNbInputSweepBodies() = 0;

  /**
  * Get the number of patches which constitute the full partition of the result body,
  * some of them coming from the input Sweep bodies, the other filling the spaces between the first ones
  * @return
  * The integer number of all output patches
  */
  virtual int GetNbOutputPatches() = 0;

  /**
  * Get the list of output patches which come from the input SweepBodies (see AddSweepBody API)
  * @param oSweepPatchesID
  * The list of ID [ between 1 and GetNbOutputPatches() ] associated to each patch coming from input Sweep bodies and modified by the operation
  * @param oInputSweepBodiesID
  * The optional list of ID [ between 1 and GetNbInputSweepBodies() ] associated to each input SweepBody
  * An ID may be repeated if an input SweepBody has several connected parts before or after the operation
  * if enabled (not null), the returned list will be parallel to oSweepPatchesID
  * @return
  * The integer number of elements in the returned list
  */
  virtual int GetOutputSweepPatches(CATListOfInt &oSweepPatchesID, CATListOfInt * oInputSweepBodiesID = 0) = 0;

  /**
  * Get the list of output patches added to fill spaces between the input sweep bodies
  * @param oFillPatchesID
  * The list of ID [ between 1 and GetNbOutputPatches() ] associated to each patch filling a space
  * @return
  * The integer number of elements in the returned list
  */
  virtual int GetOutputFillPatches(CATListOfInt &oFillPatchesID) = 0;

  /**
  * Get 3 lists of cells belonging to an output patch known through its ID [ between 1 and GetNbOutputPatches() ]
  * @param iOutputPatchID
  * input ID [ between 1 and GetNbOutputPatches() ] allowing to identify the output patch
  * @param oFaces
  * The list of all the faces belonging to the ouput patch
  * @param oBoundaryCellsOnGuide
  * The list of highest cells bounding the patch on the guide side
  * If the current patch fills a space between 2 SweepBodies in contact, the list will contain the contact vertex 
  * else the list will contain the successive edges bounding the patch on the guide side
  * @param oOppositeBoundaryEdges
  * The list of edges bounding the patch on the side opposite to the guide
  */
  virtual void GetOutputPatchCells(int iOutputPatchID, CATLISTP(CATCell) &oFaces, CATLISTP(CATCell) &oBoundaryCellsOnGuide, CATLISTP(CATCell) &oOppositeBoundaryEdges) = 0;

  /**
  * Retrieve the input sweep body whose an output patch is coming from
  * @param iOutputPatchID
  * input ID [ between 1 and GetNbOutputPatches() ] allowing to identify the output patch
  * @return
  * return 0 if the ouput patch is a FillPatch,
  * else return a positive integer [ between 1 and GetNbInputSweepBodies() ] if it's a SweepPatch
  */
  virtual int RetrieveInputBodyIDFromPatch(int iOutputPatchID) = 0;

  /**
  * Retrieve the list of output patches along an edge of the guide, or build from a contact vertex between 2 sweep bodies
  * @param iGuideCell
  * input cell belonging to iGuideWireBody
  * @param oOuputPatchesID
  * list of ID [ between 1 and GetNbOutputPatches() ] allowing to identify all the output patches long the guide cell
  * @param iFillPatchOnly
  * enables a filter skipping the ouput patches coming from the input sweep bodies
  */
  virtual int RetrievePatchesFromGuideCell(CATCell * iGuideCell, CATListOfInt & oOuputPatchesID, CATBoolean iFillPatchOnly=FALSE) = 0;


protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPolyhedralFillSweepRibbon(); // -> delete can't be called
};

/**
 * Creates a CATIPGMPolyhedralFillSweepRibbon operator with a guide wire body
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iGuideWireBody
 * The pointer to the 1D body to guide the sweep ribbon to fill
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMPolyhedralFillSweepRibbon *CATPGMCreatePolyhedralFillSweepRibbon(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iGuideWireBody);

#endif /* CATIPGMPolyhedralFillSweepRibbon_h_ */
