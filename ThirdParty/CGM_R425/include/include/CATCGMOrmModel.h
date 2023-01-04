#ifndef CATCGMOrmModel_h
#define CATCGMOrmModel_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2015
//-----------------------------------------------------------------------------
// Class allowing to build a CGM Model working form from sim data
// 
// RBU3 : 03 2021 : debug of stream (the number of nodes was put in the version number in old old streams)
// RBU3 : 04 2021 : New surfacic mode
//-----------------------------------------------------------------------------

#include "ExportedByGeometricObjects.h"
#include "CATCGMVirtual.h"
#include "CATListOfInt.h"
#include "CATBoolean.h"
#include "CATLISTV_CATMathPoint.h"

class CATMathTransformation;
class CATMathPoint;
class CATMathStream;

class ExportedByGeometricObjects CATCGMOrmModel : public CATCGMVirtual
{
public:

  // Type of Element that we want to store in Model
  enum CGMOrmModelElementType { Tetrahedron, Pyramid, Penta, Cube, Beam, Quad, Triangle };

  // -----------
  // Ctor & Dtor
  // -----------

  //--------------------------------------------------------------------------
  //
  // Method: Create
  //
  // Description: 
  //   Creation of instance of Orm Model.
  // 
  // Arguments:
  //   inDim    dimension of the model. Only 3 (volumic) and 2 (surfacic) are implemented.
  //    
  // Returns:
  //     Pointer to an instance of Orm Model, or NULL if the dimension is different from 2 or 3
  //   
  //--------------------------------------------------------------------------
  static CATCGMOrmModel * Create(short inDim = 3);

  //--------------------------------------------------------------------------
  //
  // Method: Remove
  //
  // Description: 
  //   Removal of one instance of an Orm Model
  //   
  // Arguments:
  //   iModel    Pointer to an instance of Orm Model.
  //   
  //--------------------------------------------------------------------------
  static void Remove(CATCGMOrmModel * ipModel);

  //--------------------------------------------------------------------------
  //
  // Method: AddRef
  //
  // Description: 
  //   Add a reference to this OrmModel.
  //   Use then the Remove method (static) to remove an instance of a model.
  //   
  //--------------------------------------------------------------------------
  void AddRef();

  // -----------
  // Services
  // -----------

  //--------------------------------------------------------------------------
  //
  // Method: GetModelDimension
  //
  // Description: 
  //   return the dimension of this OrmModel.
  //      3 for volumic models, 2 for surfacic ones.
  //--------------------------------------------------------------------------
  virtual int GetModelDimension() = 0;

  //--------------------------------------------------------------------------
  //
  // Method: AddNodes
  //
  // Description: 
  //   Add nodes to Orm Model
  //   
  // Arguments:
  //   inCount       Number of nodes 
  //   inStartIndex   Start Node index - all index need to be consecutive between each call
  //   ipfCoord       Node Coordinates float[inCount*3]
  //   (optional) ipDensities    Node density. If NULL, all nodes will have their density set at 0.
  //   
  // Return E_FAIL if the model is locked.
  //--------------------------------------------------------------------------
  virtual HRESULT AddNodes(int inCount, int inStartIndex, float *ipfCoord, float *ipDensities = NULL) = 0;

  //--------------------------------------------------------------------------
  //
  // Method: AddElements
  //
  // Description: 
  //   Add Elements to Orm Model
  //   
  // Arguments:
  //   inCount   Number of elements 
  //   iElementType Type of Elements ( tetrahedron, cube, pyramide , ... ) at first only tetrahedron supported.
  //   ipnIDs    Element id int[inCount]
  //   ipnIndexNodes  List of Node index - element composition int[nb node per element * inCount]
  //   ipfDensity Element density float[inCount], can be null. If NULL, all elements will have their density set to 0.
  //
  // Returns:
  //   E_FAIL if the dimension of the elements is not the same than the one of the model,
  //      or if the model is locked.
  //--------------------------------------------------------------------------
  virtual HRESULT AddElements(int inCount, CGMOrmModelElementType ieElementType, int *ipnIDs, int *ipnIndexNodes, float *ipfDensity) = 0;


  //--------------------------------------------------------------------------
  //
  // Method: SetElementsFrozen
  //
  // Description: 
  //   Set Frozen Element to Orm Model
  //   
  // Arguments:
  //   ilnFrozenIDs   List of elements id 
  //
  // Return E_FAIL if the model is locked.
  //--------------------------------------------------------------------------
  virtual HRESULT SetElementsFrozen(CATListOfInt & ilnFrozenIDs) = 0;

  //--------------------------------------------------------------------------
  //
  // Method: IsFrozenElement
  //
  // Description: 
  //   return TRUE if the element is Frozen
  //
  // Arguments:
  //   inIDElt   ID of the element.
  //--------------------------------------------------------------------------
  virtual CATBoolean IsFrozenElement(int inIDElt) = 0;


  //--------------------------------------------------------------------------
  //
  // Method: Transform
  //
  // Description: 
  //   apply a transformation to all Nodes Coordinates 
  //   
  // Arguments:
  //   iTransfo   transformation to apply
  //--------------------------------------------------------------------------
  virtual void Transform(CATMathTransformation & iTransfo) = 0;

  //--------------------------------------------------------------------------
  // Method: IsOnlyTetrahedral
  //
  // Description:
  //   Only usefull for volumic models (dimension = 3), return always FALSE if the model is surfacic (dimension = 2).
  //   Check if this volumic model contains only tetrahedra.
  //   If not and if this model is volumic, its non-tet elements will be converted into tetras in some processes.
  //
  // DEPRECATED ! Please use IsHybrid.
  //--------------------------------------------------------------------------
  //virtual CATBoolean IsOnlyTetrahedral() = 0;

  //--------------------------------------------------------------------------
  // Method: IsHybrid
  //
  // Description:
  //  return TRUE if the model has at least one hybrid element
  //  An hybrid element is an element different than a tetrahedra in 3D
  //    or different than a triangle in 2D.
  //--------------------------------------------------------------------------
  virtual CATBoolean IsHybrid() = 0;

  //--------------------------------------------------------------------------
  // Method: GetNbElements
  //
  // Description: 
  //   return the number of elements  
  //--------------------------------------------------------------------------
  virtual const int GetNbElements() = 0;

  //--------------------------------------------------------------------------
  // Method: GetNbNodes
  //
  // Description: 
  //   return the number of nodes
  //--------------------------------------------------------------------------
  virtual const int GetNbNodes() = 0;

  //--------------------------------------------------------------------------
  // Method: GetElementPosInList
  //
  // Description: 
  //    From the id of an element, return its position in the OrmModel list of elements.
  //    The position in the list is often used by the methods of the model.
  //
  // returns:
  //    0 if the element is not in the list, the position in the list otherwise.
  //--------------------------------------------------------------------------
  virtual int GetElementPosInList(int inIdElem) = 0;

  //--------------------------------------------------------------------------
  // Method: GetIdElementWithNodes
  //
  // Description: 
  //   return the list of node of an element, from its position in the model
  // Arguments:
  //   inPos   position of the element in the list of element, between 1 and NbElement
  //   ioListOfIdNode   list of nodes of this element
  //--------------------------------------------------------------------------
  virtual int GetIdElementWithNodes(int inPos, CATListOfInt& ioListOfIdNode) = 0;

  //--------------------------------------------------------------------------
  // Method: GetIdElementWithDensity
  //
  // Description: 
  //   return the density of an element, from its position in the model
  // Arguments:
  //   inPos   position of the element in the list of element, between 1 and NbElement
  //   ioDensity   the density of this element
  // return
  //   0 if the pos is outside the bound of the list of nodes of the model.
  //   The id of the node otherwise
  //--------------------------------------------------------------------------
  virtual int GetIdElementWithDensity(int inPos, float& ioDensity) = 0;

  //--------------------------------------------------------------------------
  // Method: GetIdElement
  //
  // Description: 
  //   return the ID of an element from its position in the list of the model.
  // Arguments:
  //   inPos   position of the element in the list of element, between 1 and NbElement
  // return
  //   0 if the pos is outside the bound of the list of elements of the model.
  //   The id of the element otherwise
  //--------------------------------------------------------------------------
  virtual int GetElementId(int inPos) = 0;

  //--------------------------------------------------------------------------
  // Method: GetNodeId
  //
  // Description: 
  //   return the ID of a node from its position in the list of the model.
  // Arguments:
  //   inPos   position of the node in the list of node, between 1 and NbNode
  // return
  //   0 if the pos is outside the bound of the list of nodes of the model.
  //   The id of the node otherwise
  //--------------------------------------------------------------------------
  virtual int GetNodeId(int inPos) = 0;

  // Return the pos of a node in the model list, from its id
  //   Return 0 if the the node is not in the list
  //--------------------------------------------------------------------------
  // Method: GetNodePosInList
  //
  // Description: 
  //   return the position of a node in the list of the model form its id.
  // Arguments:
  //   inId   id of the node in the model.
  // Returns:
  //   0 if the node is not in the list, its position in the list otherwise (between 1 and NbNode)
  //--------------------------------------------------------------------------
  virtual int GetNodePosInList(int inId) = 0;

  //--------------------------------------------------------------------------
  // Method: GetElementNodeCoordinates
  //
  // Description: 
  //   return the positions of the nodes of an element
  //     from its position in the list of element.
  //
  // Arguments:
  //   inPos   position of the element in the list of element, between 1 and NbNode
  //--------------------------------------------------------------------------
  virtual HRESULT GetElementNodeCoordinates(int inPos, CATLISTV(CATMathPoint)  &oLPoints) = 0;

  //--------------------------------------------------------------------------
  // Method: GetElementCOG
  //
  // Description: 
  //   Compute the center of gravity of an element
  //
  // Arguments :
  //   inPos   the position of the element in the list of elements of the model
  //   oG     center of gravity of the element.
  //--------------------------------------------------------------------------
  virtual HRESULT GetElementCOG(int inPos, CATMathPoint &oG) = 0;

  //--------------------------------------------------------------------------
  // Method: GetNodeCoordinates
  //
  // Description: 
  //   fill iMathPoint with the coordinate of a node, from the position of the node
  //   in the list of nodes.
  // Arguments:
  //   inPos   position of the node in the list of nodes, between 1 and NbNode
  //--------------------------------------------------------------------------
  virtual HRESULT GetNodeCoordinates(int inPosNode, CATMathPoint &iMathPoint) = 0;

  //--------------------------------------------------------------------------
  // Method: GetNodeCoordinatesFromyId
  //
  // Description: 
  //   fill iMathPoint with the coordinate of a node, from the position of the node
  //   in the list of nodes.
  // Arguments:
  //   inIdNode   id of the node
  //--------------------------------------------------------------------------
  virtual HRESULT GetNodeCoordinatesFromId(int inIdNode, CATMathPoint &iMathPoint) = 0;

  //--------------------------------------------------------------------------
  // Method: GetNodeDensity
  //
  // Description: 
  //   return the density of a node from its position in the list of nodes.
  // Arguments:
  //   inPos          position of the node in the list of nodes, between 1 and NbNode
  //   ioDensity      Where the density of the node will be stored
  //                    or -1 if the density of this node was not set during the creation of this model
  //   oSetInCreation Optional argument. Set at FALSE if the density of this node was not set during
  //                    the creation of this model. TRUE otherwise.
  //
  //--------------------------------------------------------------------------
  virtual HRESULT GetNodeDensity(int inPosNode, float& ioDensity, CATBoolean *oSetInCreation=NULL) = 0;

  //--------------------------------------------------------------------------
  // Method: GetNodeDensityFromId
  //
  // Description: 
  //   return the density of a node from its id
  // Arguments:
  //   inIdNode   id of the node
  //   ioDensity      Where the density of the node will be stored
  //                    or -1 if the density of this node was not set during the creation of this model
  //   oSetInCreation Optional argument. Set at FALSE if the density of this node was not set during
  //                    the creation of this model. TRUE otherwise.
  //
  //--------------------------------------------------------------------------
  virtual HRESULT GetNodeDensityFromId(int inIdNode, float& ioDensity, CATBoolean *oSetInCreation = NULL) = 0;

  // #########################################################################
  // Origin Body setters
  // #########################################################################
  //--------------------------------------------------------------------------
  // Method: SetOriginBody
  //
  // Description: 
  //   Link this model to a list of CATBody
  //
  // Arguments:
  //   inBodyTag   list of body tags
  //
  // Return E_FAIL if the model is locked.
  //--------------------------------------------------------------------------
  virtual HRESULT SetOriginBody(CATListOfInt &inBodyTag) = 0;

  //--------------------------------------------------------------------------
  // Method: SetElementsOriginCell
  //
  // Description: 
  //   Link a list of element to a CATCell.
  //   This CATCell should be of High dimension according to the dim of the model.
  //        Dimension 3 : a CATVolume, Dimension 2 : a CATFace.
  //
  // Arguments:
  //   inCellTag     tag of the CATCell
  //   ilnElemId     list of element idx
  //
  // Return E_FAIL if the model is locked.
  //--------------------------------------------------------------------------
  virtual HRESULT SetElementsOriginCell(int inCellTag, CATListOfInt &ilnElemId) = 0;

  //--------------------------------------------------------------------------
  // Method: SetNodesOriginCell
  //
  // Description: 
  //   Link a list of nodes to a CATCell.
  //
  // TO BE REMOVED, now use the method SetNodesOriginVertex to link node to CATVertex only.
  //
  // Arguments:
  //   inCellTag     tag of the CATCell
  //   ilnNodeId     list of node idx
  //
  // Return E_FAIL if the model is locked.
  //--------------------------------------------------------------------------
  virtual HRESULT SetNodesOriginCell(int inCellTag, CATListOfInt &ilnNodeId) = 0;

  //--------------------------------------------------------------------------
  // Method: DoesOldCodeIsCalled
  //
  // Description: 
  //   Return TRUE if a call to SetNodesOriginCell has been made.
  //
  // TO BE REMOVED when the new links between OrmModel and Tags will be fully implented
  //    And the old code will stop to be call.
  //
  // Arguments:
  //   inCellTag     tag of the CATCell
  //   ilnNodeId     list of node idx
  //
  // Return E_FAIL if the model is locked.
  //--------------------------------------------------------------------------
  virtual CATBoolean IsOldCodeCalled() = 0;

  //--------------------------------------------------------------------------
  // Method: SetElementFacetsOriginFace
  //
  // Description: 
  //   Link a list of facets (from known elements) to a CATFace.
  //   ONLY USEFULL for 3D models. For 2D models, only one facet per element,
  //      directly link the element to a CATFace.
  //
  // Arguments:
  //   inFaceTag     tag of the CATFace
  //   ilnElemId     list of element idx
  //   iFacetID      list parallel to ilnElemId, containing facets ID, according 
  //                   to the convention of each type of element
  //
  // Return E_FAIL if the model is locked.
  //--------------------------------------------------------------------------
  virtual HRESULT SetElementFacetsOriginFace(int inFaceTag, CATListOfInt &ilnElemId, CATListOfInt &iFacetId) = 0;

  //--------------------------------------------------------------------------
  // Method: SetElementBarsOriginEdge
  //
  // Description: 
  //   Link a list of bars (from known elements) to a CATEdge.
  //
  // Arguments:
  //   inEdgeTag     tag of the CATEdge
  //   ilnElemId     list of element idx
  //   iBarID        list parallel to ilnElemId, containing bars ID, according
  //                   to the convention of each type of element
  //
  // Return E_FAIL if the model is locked.
  //--------------------------------------------------------------------------
  virtual HRESULT SetElementBarsOriginEdge(int inEdgeTag, CATListOfInt &ilnElemId, CATListOfInt &iBarId) = 0;

  //--------------------------------------------------------------------------
  // Method: SetNodesOriginVertex
  //
  // Description: 
  //   Link a list of nodes to a CATVertex.
  //
  // Arguments:
  //   inVertexTag tag of the CATVertex
  //   ilnNodeId list of node idx
  //
  // Return E_FAIL if the model is locked.
  //--------------------------------------------------------------------------
  virtual HRESULT SetNodesOriginVertex(int inVertexTag, CATListOfInt &ilnNodeId) = 0;


  //--------------------------------------------------------------------------
  // Method: GetListOriginBodies
  //
  // Description: 
  //   return the list of CATBody tags linked to this model.
  //--------------------------------------------------------------------------
  virtual CATListOfInt GetOriginBodies() = 0;

  //--------------------------------------------------------------------------
  // Method: GetListCellTagsForElements
  //
  // Description: 
  //   return the list of CATCell tags linked to the elements of this model.
  //--------------------------------------------------------------------------
  virtual CATListOfInt GetListCellTagsForElements() = 0;

  //--------------------------------------------------------------------------
  // Method: GetListCellTagsForNodes
  //
  // Description: 
  //   return the list of CATCell tags linked to the nodes of this model.
  //--------------------------------------------------------------------------
  virtual CATListOfInt GetListCellTagsForNodes() = 0;

  //--------------------------------------------------------------------------
  // Method: GetListFaceTagsForFacets
  //
  // Description: 
  //   return the list of CATFace tags linked to the facets of this model's elements.
  //--------------------------------------------------------------------------
  virtual CATListOfInt GetListFaceTagsForFacets() = 0;

  //--------------------------------------------------------------------------
  // Method: GetListCellTagsForNodes
  //
  // Description: 
  //   return the list of CATEdge tags linked to the bars of this model's elements.
  //--------------------------------------------------------------------------
  virtual CATListOfInt GetListEdgeTagsForBars() = 0;

  //--------------------------------------------------------------------------
  // Method: GetElementsLinkedToCellTag
  //
  // Description: 
  //   From the tag of a CATCell (linked to this model),
  //    get the list of idx of the elements linked to this cell.
  //   WARNING : return a list of idx. Most of the method of the OrmModel use the position in the model list.
  //     Use GetElemPosInList to get its position in the list.
  //
  // Arguments:
  //   inCellTag   tag of the CATVolume
  //   ioElemId      list of element idx linked to this volume
  //
  // Return:
  //   E_FAIL if the cell is not linked to this model
  //   S_OK otherwise
  //--------------------------------------------------------------------------
  virtual HRESULT GetElementsLinkedToCellTag(int inCellTag, CATListOfInt &ioElemId) = 0;

  //--------------------------------------------------------------------------
  // Method: GetNodesLinkedToCellTag
  //
  // Description: 
  //   From the tag of a CATCell (linked to this model),
  //    get the list of idx of the nodes linked to this cell.
  //
  // Arguments:
  //   inCelltag     tag of the CATCell
  //   ioNodeId      list of node idx linked to this cell
  //
  // Return:
  //   E_FAIL if the cell is not linked to this model
  //   S_OK otherwise
  //--------------------------------------------------------------------------
  virtual HRESULT GetNodesLinkedToCellTag(int inCellTag, CATListOfInt &ioNodeId) = 0;

  //--------------------------------------------------------------------------
  // Method: GetFacetsLinkedToFaceTag
  //
  // Description: 
  //   From the tag of a CATFace (linked to this model),
  //    get two parallel lists describing the facets linked to this face.
  //       Facet i is the facet number ioFacetId[i] in the element ioElemId[i]
  //
  // Arguments:
  //   inFaceTag     tag of the CATFace
  //   ioElemId      list of element idx
  //   ioFacetId     list parallel to ioElemId, containing facets ID, according to the convention of each type of element
  //
  // Return:
  //   E_FAIL if the face is not linked to this model
  //   S_OK otherwise
  //--------------------------------------------------------------------------
  virtual HRESULT GetFacetsLinkedToFaceTag(int inFaceTag, CATListOfInt &oElemId, CATListOfInt &ioFacetId) = 0;

  //--------------------------------------------------------------------------
  // Method: GetBarsLinkedToEdgeTag
  //
  // Description: 
  //   From the tag of a CATEdge (linked to this model),
  //    get two parallel lists describing the bars linked to this face.
  //       Bar i is the bar number ioBarId[i] in the element ioElemId[i]
  //
  // Arguments:
  //   inFaceTag     tag of the CATFace
  //   ioElemId      list of element idx
  //   ioFacetId     list parallel to ioElemId, containing facets ID, according to the convention of each type of element
  //
  // Return:
  //   E_FAIL if the face is not linked to this model
  //   S_OK otherwise
  //--------------------------------------------------------------------------
  virtual HRESULT GetBarsLinkedToEdgeTag(int inCellTag, CATListOfInt &oElemId, CATListOfInt &ioBarId) = 0;

  //--------------------------------------------------------------------------
  //                  EDITION METHOD
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // Method: ClearAllData
  //
  // Description: 
  //   Clear all the data of this OrmModel except for its dimension.
  //
  // Return E_FAIL if the model is locked.
  //--------------------------------------------------------------------------
  virtual HRESULT ClearAllData() = 0;

  //--------------------------------------------------------------------------
  // Method: Lock
  //
  // Description: 
  //   Lock the OrmModel : it cannot be edited while locked.
  //   The key is necessary to then unlock it.
  //
  // Return E_FAIL if already locked
  //--------------------------------------------------------------------------
  virtual HRESULT Lock(int &oKey) = 0;

  //--------------------------------------------------------------------------
  // Method: Unlock
  //
  // Description: 
  //   Unlock the OrmModel, allowing its modification
  //
  // Return E_FAIL if the key is wrong
  //--------------------------------------------------------------------------
  virtual HRESULT Unlock(int iKey) = 0;

  //--------------------------------------------------------------------------
  // Method: Islocked
  //
  // Description: 
  //   return TRUE if this model is locked
  //--------------------------------------------------------------------------
  virtual CATBoolean Islocked() = 0;

  // #########################################################################
  // Stream infrastructure 
  // #########################################################################
  //--------------------------------------------------------------------------
  // Method: Stream
  //
  // Description: 
  //   Stream the Model into a CATMathStream
  //--------------------------------------------------------------------------
  virtual void Stream(CATMathStream& Str) const = 0;

  //--------------------------------------------------------------------------
  // Method: UnStream
  //
  // Description: 
  //   Unstream a Model from a CATMathStream.
  //   If the caller does not know the dimension of the ormModel before the unstream,
  //     he can initialize it as volumic (by default), the dimension will be unstreamed and overwrited in all cases.  
  //
  // Arguments :
  //   Str  the stream
  //--------------------------------------------------------------------------
  virtual void UnStream(CATMathStream&Str) = 0;

protected:

  // ------------------------
  // Internal Use Ctor & Dtor
  // ------------------------
  CATCGMOrmModel();
  virtual ~CATCGMOrmModel();

private:
  // ---------------
  // Forbidden Ctors
  // ---------------
  CATCGMOrmModel(const CATCGMOrmModel& iCGMOrmModel);
  CATCGMOrmModel& operator = (const CATCGMOrmModel& iCGMOrmModel);

private:
  int _Counter;
};

#endif
