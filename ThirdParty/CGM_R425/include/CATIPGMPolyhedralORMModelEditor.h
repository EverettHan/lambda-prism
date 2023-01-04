#ifndef CATIPGMPolyhedralORMModelEditor_h_
#define CATIPGMPolyhedralORMModelEditor_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMOperator.h"

#include "CATListOfInt.h"

class CATCGMOrmModel;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATMathPoint;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMPolyhedralORMModelEditor;

/**
*
* Class defining an operator allowing the user to navigate through an OrmModel and edit it.
* <ul>
*     <li> A <tt>CATICGMPolyhedralORMModelEditor</tt> operator is created with the <tt>CATCGMCreatePolyhedralORMModelEditor</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The input OrmModel is modified AFTER the run.
*     <li>    OR a new OrmModel is generated (duplicateMode) and can be retrive using the GetOrmModel method.
*     <li> CAUTION : in duplicate mode each call to Run will then reinitialize the internal data.
*             The next modifications will be done on the input OrmModel and not take into account the modifications before the run.
*     <li> In both mode, the OrmModel is re-created (or created) by the Run method, thus the Run must only be called after ALL the modifications are done.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMPolyhedralORMModelEditor: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPolyhedralORMModelEditor();

  //===========================================================================
  // NODES ATTRIBUTES ACCESS
  //===========================================================================
  //--------------------------------------------------------------------------
  // Method: GetListNodesIdx
  //
  // Description: 
  //  Get the list of idx of the nodes of the model
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT GetListNodesIdx(CATListOfInt &oListNodesIdx) = 0;

  //--------------------------------------------------------------------------
  // Method: GetNodePosition
  //
  // Description: 
  //  Get the position of a node from its id in the OrmModel.
  //
  // Return E_FAIL if the id is not in the OrmModel.
  //--------------------------------------------------------------------------
  virtual HRESULT GetNodePosition(
    int iIdNodeInOrmModel,
    CATMathPoint &oPosition) = 0;

  //--------------------------------------------------------------------------
  // Method: ComputeNodesDensity
  //
  // Description:
  //  Compute the density of the all the nodes of the model,
  //     except for the nodes with a density already set.
  //  You can then use the Set/Get NodeDensity of this class to access the densities.
  //
  //  if iIgnoreFrozenElements is activated (by default it is), the densities of the
  //    frozen elements will be ignored while computing the densities of the nodes.
  //  if iWeightedMean  is activated (activacted by default), the density will
  //     be computed using the mean of the elements' densities weighted by their volumes.
  //
  // CAUTION : only the internal datas are modified before the Run method.
  //--------------------------------------------------------------------------
  virtual HRESULT ComputeNodesDensity(
    CATBoolean iIgnoreFrozenElements = TRUE,
    CATBoolean iWeightedMean = TRUE) = 0;

  //--------------------------------------------------------------------------
  // Method: SetNodeDensity
  //
  // Description: 
  //  Set the density of a node from its id in the OrmModel.
  //
  // CAUTION : only the internal datas are modified before the Run method.
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT SetNodeDensity(int iIdNodeInOrmModel, float iDensity) = 0;

  //--------------------------------------------------------------------------
  // Method: GetNodeDensity
  //
  // Description: 
  //  Get the density of a node from its id in the OrmModel.
  //
  // COMPUTE THE DENSITY if not already set nor computed.
  //   The two booleans are only usefull if the computation is needed.
  //   You can compute all the nodes-density with the ComputeNodesDensity method.
  //
  //  if iIgnoreFrozenElements is activated (by default it is), the densities of the
  //    frozen elements will be ignored.
  //  if iWeightedMean  is activated (activacted by default), the density will
  //     be computed using the mean of the elements' densities weighted by their volumes.
  //
  // Return E_FAIL if the id is not in the OrmModel or if it fails to compute the density.
  //--------------------------------------------------------------------------
  virtual HRESULT GetNodeDensity(int iIdNodeInOrmModel, float &oDensity, CATBoolean iIgnoreFrozenElements = TRUE,
    CATBoolean iWeightedMean = TRUE) = 0;

  //--------------------------------------------------------------------------
  // Method: GetNodeTags
  //
  // Description: 
  //  Get the tags of a node from its id in the OrmModel.
  //    Those tags are tags of CATVertex of the originBody to wich the node is linked
  //    The list is empty if the node is not linked to a CATVertex
  //
  // Return E_FAIL if the id is not in the OrmModel.
  //--------------------------------------------------------------------------
  virtual HRESULT GetNodeTags(int iIdNodeInOrmModel, CATListOfInt &oNodeTags) = 0;

  //--------------------------------------------------------------------------
  // Method: SetNodeTags
  //
  // Description: 
  //  Set the tags of a node from its id in the OrmModel.
  //    Those tags MUST be tags of CATVertex of the OriginBody
  //
  //  CAUTION : remove the current tags of the node
  //  CAUTION 2 : only the internal datas are modified before the Run method.
  //
  // Return E_FAIL if the id is not in the OrmModel.
  //--------------------------------------------------------------------------
  virtual HRESULT SetNodeTags(int iIdNodeInOrmModel, CATListOfInt iNodeTags) = 0;

  //--------------------------------------------------------------------------
  // Method: GetNeighborsOfNode
  //
  // Description: 
  //  Get the idx of all the nodes around a node, from its id in the model.
  //     Aka, all the nodes linked by an edge to this node.
  //
  // Return E_FAIL if the id is not in the OrmModel.
  //--------------------------------------------------------------------------
  virtual HRESULT GetNeighborsOfNode(
    int iIdNodeInOrmModel,
    CATListOfInt &oNeighboors) = 0;

  //--------------------------------------------------------------------------
  // Method: GetElementsAroundNode
  //
  // Description: 
  //  Get the idx of all the elements around a node, from its id in the model.
  //
  // Return E_FAIL if the id is not in the OrmModel.
  //--------------------------------------------------------------------------
  virtual HRESULT GetElementsAroundNode(
    int iIdNodeInOrmModel,
    CATListOfInt &oElementsAround) = 0;

  //===========================================================================
  // ELEMENTS ATTRIBUTES ACCESS
  //===========================================================================
  //--------------------------------------------------------------------------
  // Method: GetListElementsIdx
  //
  // Description: 
  //  Get the list of idx of the elements of the model
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT GetListElementsIdx(CATListOfInt &oListElementsIdx) = 0;

  //--------------------------------------------------------------------------
  // Method: GetElementNodes
  //
  // Description: 
  //  Get the nodes idx of an element from its id in the OrmModel.
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT GetElementNodes(int idElemInOrmModel, CATListOfInt &oNodesIdx) = 0;

  //--------------------------------------------------------------------------
  // Method: SetElementDensity
  //
  // Description: 
  //  Set the density of an element from its id in the OrmModel.
  //
  // CAUTION : only the internal datas are modified before the Run method.
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT SetElementDensity(int idElemInOrmModel, float iDensity) = 0;

  //--------------------------------------------------------------------------
  // Method: GetElementDensity
  //
  // Description: 
  //  Get the density of an element from its id in the OrmModel.
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT GetElementDensity(int idElemInOrmModel, float &oDensity) = 0;

  //--------------------------------------------------------------------------
  // Method: GetElementNeighbors
  //
  // Description: 
  //  Get the elements neighbors of an element from its id in the OrmModel.
  //
  //  They are alway ordered accordingly to the order of the faces or the edges of the element
  //   3D :
  //      tetra : face(0, 2, 1), face(0, 1, 3), face(0, 3, 2) and face(1, 2, 3)
  //      Pyramid : face(0, 1, 2, 3), face(0, 1, 4), face(1, 2, 4), face(2, 3, 4) and face(3, 0, 4)
  //      Penta : face(0,1,2), face(3,4,5), face(0,1,4,3), face(1,2,5,4), face(2,0,3,5)
  //      Cube : face(0,1,2,3), face(4,5,6,7), face(0,1,5,4), face(1,2,6,5), face(2,3,7,6), face(3,0,4,7)
  //       
  //  2D
  //      Triangle : edge(0, 1), edge(1, 2) and edge(2, 0)
  //      Quad : edge(0, 1), edge(1, 2), edge(2, 3) and edge(3, 0)
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT GetElementNeighbors(
    int idElemInOrmModel,
    CATListOfInt &oNeighbordsIdx) = 0;

  //--------------------------------------------------------------------------
  // Method: IsElementFrozen
  //
  // Description: 
  //  Check if an element is Frozen or not.
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT IsElementFrozen(int idElemInOrmModel, CATBoolean &oFrozen) = 0;

  //--------------------------------------------------------------------------
  // Method: SetElementFrozen
  //
  // Description: 
  //  Set an element as Frozen or not.
  //
  // CAUTION : only the internal datas are modified before the Run method.
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT SetElementFrozen(int idElemInOrmModel, CATBoolean iFrozen) = 0;

  //--------------------------------------------------------------------------
  // Method: GetElementFacetsTags
  //
  // Description: 
  //  Get the tags associated with the facets of an element.
  //    If a tag is at 0 in the list, the facet is not linked to any tag.
  //  The facets are ordered as in the OrmModel convention, with an id between 0
  //    and nbFacets - 1
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT GetElementFacetsTags(int iIdElemInOrmModel, CATListOfInt &oFacetsTags) = 0;

  //--------------------------------------------------------------------------
  // Method: GetElementBarsTags
  //
  // Description: 
  //  Get the tags associated with the bars of an element.
  //  Return a list of tags in oBarsTags and the nb of tags per bar in oNbTagsPerBar.
  //    Indeed a bar can be linked to more than one tag.
  //  The bars are ordered as in the OrmModel convention, with an id between 0
  //    and nbBars - 1
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT GetElementBarsTags(int iIdElemInOrmModel, CATListOfInt &oBarsTags, CATListOfInt &oNbTagsPerBar) = 0;

  //--------------------------------------------------------------------------
  // Method: SetElementFacetTag
  //
  // Description: 
  //  Set the tag of a facet of an element.
  //  The facets of an elements are ordered as in the OrmModel convention
  //     and with an id between 0 and nbFacet - 1
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual  HRESULT SetElementFacetTag(int iIdElemInOrmModel, int iIdFacet, int iTag) = 0;

  //--------------------------------------------------------------------------
  // Method: SetElementFacetTag
  //
  // Description: 
  //  Set the tags of a bar of an element.
  //  The bars of an elements are ordered as in the OrmModel convention
  //     and with an id between 0 and nbEdges - 1
  //
  // Return E_FAIL if the id is not in the OrmModel
  //--------------------------------------------------------------------------
  virtual HRESULT SetElementBarTags(int iIdElemInOrmModel, int iIdBar, const CATListOfInt &iTags) = 0;

  //===========================================================================
  // HYBRID ELEMENTS MANAGEMENT
  //===========================================================================
  //--------------------------------------------------------------------------
  // Method: GetIdxOfHybridElements
  //
  // Description:
  //  Return the idx of the hybrid elements of the input model.
  //
  // CAUTION : the list is re-initialized after each Run from the data
  //    of the modified OrmModel.
  //--------------------------------------------------------------------------
  virtual HRESULT GetIdxOfHybridElements(CATListOfInt &oIdxHybridElements) = 0;

  //--------------------------------------------------------------------------
  // Method: ConvertHybridElements
  //
  // Description: 
  //  Convert all the hybrid elements (different than tetrahedral in 3D
  //  or triangle in 2D)
  //
  // CAUTION : Also COMPUTE the NODE DENSITIES.
  // CAUTION 2: only the internal datas are modified before the Run method.
  // CAUTION 3 : it may change the number of nodes, the number of elements, the neighbors
  //    etc...
  //--------------------------------------------------------------------------
  virtual HRESULT ConvertHybridElements() = 0;

  // Method: GetNewElementsAfterConversion
  //
  // Description: 
  //  From the id of an hybrid element, return the idx of the new elements
  //    generated when converting this element.
  //
  // CAUTION : ConvertHybridElements MUST HAVE BEEN CALLED.
  //            AND this method should only be called BEFORE the Run.
  //
  // return S_FALSE if the element is not hybrid, E_FAIL if the conversion was not called.
  //--------------------------------------------------------------------------
  virtual HRESULT GetNewElementsAfterConversion(
    int iIdElem,
    CATListOfInt &oIdxNewElements) = 0;

  // DO NOT CALL, UNDER DEVELOPMENT !
  // Compute the node densities, then go through the elements
  //  and keep all the elements with at least one node above and one node below the isoValue.
  //   + the elements with a node exactly at the isoValue.
  // If iRingsAround != 0, keep the neighbors around those elements, and the neighbors of those elements etc...
  //    The value of iRingsAround give the neighbors depth to keep.
  // MAX 10 RINGS AROUND !
  //
  // CAUTION : if not already done, the computation of the nodes densities will be done
  //   with the options by default (ignoreFrozenElements and WeightedMean).
  virtual HRESULT GetElementsAroundIsoValue(float iIsoValue, int iRingsAround, CATListOfInt &oIdxElements) = 0;

  // DO NOT CALL, UNDER DEVELOPMENT !
  virtual HRESULT GetInternalElements(float iIsoValue, CATBoolean iReverseMode, CATListOfInt &oIdxElements) = 0;

  // DO NOT CALL, UNDER DEVELOPMENT !
  // Keep in the resulting ORM_MODEL only the elements among the list.
  // The other elements are still accessible but will be ignored when building the result.
  // You can call this method multiple times, the idx will all be kept until the Run.
  virtual HRESULT KeepOnlyElements(const CATListOfInt &iListElementsIdx, CATBoolean iAlsoKeepFrozen) = 0;

  // DO NOT CALL, UNDER DEVELOPMENT !
  virtual HRESULT SubdivideListOfTetras(const CATListOfInt &iListElementsIdx) = 0;

  //=============================================================================
  // RESULT
  //=============================================================================
  //--------------------------------------------------------------------------
  // Method: GetResult
  //
  // Description: to be called ONLY after the Run method
  //  In duplicate mode return a pointer to the new OrmModel.
  //     CAUTION : the caller MUST release it.
  //     CAUTION 2 : A new OrmModel is generated at each call to Run.
  //  If not in duplicate mode, the input OrmModel is already modified and this method
  //    return NULL;
  //--------------------------------------------------------------------------
  virtual CATCGMOrmModel *GetOrmModelResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPolyhedralORMModelEditor(); // -> delete can't be called
};

/**
 * Creates a CATIPGMPolyhedralORMModelEditor operator
 * @param iFactory : MANDATORY
 *   The factory of the geometry.
 * @param iOrmModel : MANDATORY
 *   The pointer to the OrmModel
 * @param iDuplicateMode :
 *   If TRUE, the input OrmModel will not be modified and a new one will be generated at each Run.
 *       WARNING : a Run fix the current modifications into a new OrmModel, BUT the next modifications
 *          will be done on the unmodified input OrmModel. The previous Result is forgotten, and a new OrmModel
*           will be created by the next Run, etc...
 *   If FALSE, the input OrmModel is modified by each Run method. DEFAULT MODE.
 * @return [out, IUnknown#Release]
 *   The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 *   Or NULL if the OrmModel or the factory are NULL.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMPolyhedralORMModelEditor *CATPGMCreatePolyhedralORMModelEditor(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATCGMOrmModel *iOrmModel,
  CATBoolean iDuplicateMode = FALSE);

#endif /* CATIPGMPolyhedralORMModelEditor_h_ */
