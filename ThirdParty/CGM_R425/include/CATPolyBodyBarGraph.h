// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraph.h
//
//===================================================================
// August 2011  Creation NDO
// June   2015  Modif    JXO: FindBars
// April  2018  Modif    JXO: Added skin and wire management
//===================================================================
#ifndef CATPolyBodyBarGraph_H
#define CATPolyBodyBarGraph_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATMapOfIntToPtr.h"
#include "CATPolyBodyBarGraphSurfaceLayers.h"
#include "CATPolyBarGraph.h"

class CATPolyBarGraphNodePositionLayer;
class CATPolyBodyBarGraphNodeCellLayer;
class CATPolyBodyBarGraphBarCellLayer;
class CATPolyBodyBarGraphSurfaceLayers;

class CATPolyBodyBarGraphLayerObserver;
class CATPolyBodyBarGraphTextureLayerObserver;
class CATPolyBodyBarGraphObserver;

class CATMapOfIntToPtr;


/**
 * Graph of nodes and bars for a CATPolyBody.
 *
 * A node is defined by a cell and an index to a vertex (micro-vertex) of the underlying discrete geometry
 * (CATIPolySurface, CATIPolyCurve or CATIPolyPoint).
 * A bar is defined by a pair of nodes.
 *
 * The indices of nodes and bars are strictly greater than 0; they are not necessarily consecutive.
 */
class ExportedByPolyBarGraph CATPolyBodyBarGraph 
{

public:

  /**
   * Construction of an instance of CATPolyBodyBarGraph given a CATPolyBody.
   * The constructor does not extract any bars from the CATPolyBody.
   * (This is done by other operators.)
   * @param iNbFacesEstimated
   *   An estimate of the number of faces there could be in the bar graph.
   * @param iNbFrames
   *   The actual number of frames in the bar graph.
   */
  CATPolyBodyBarGraph (const unsigned int iNbFacesEstimate = 1, const unsigned int iNbFrames = 1);

  ~CATPolyBodyBarGraph ();


public:

  /**
   * Types of the nodes.
   */
  enum NodeType
  {
    /** An unspecified node. */                                                       eUnspecifiedNode = 0x00,
    /** A node that is on a vertex. */                                                eVertexNode =      0x01,
    /** A node that is internal to an edge. */                                        eEdgeNode =        0x02,
    /** A node that is internal to a face. */                                         eFaceNode =        0x04
  };

  /**
   * Types of the bars.
   */
  enum BarType
  {
    /** An unspecified bar. */                                                        eUnspecifiedBar =  0x00,
    /** A bar that is on an edge. */                                                  eEdgeBar =         0x02,
    /** A bar that is internal to a face (or on a boundary but not on an edge. */     eFaceBar =         0x04
  };

public:

/** @name Cell Management
    @{ */

  // Observer class to update cell attributes.
  class CellObserver
  {
  public:

  virtual void ReactToAddCell (const CATPolyBodyBarGraph& iBodyGraph, const unsigned int iCell) {}

  virtual void ReactToAddManifoldCell (const CATPolyBodyBarGraph& iBodyGraph, const unsigned int iCell, const unsigned int iParentCell) {}

  /** 
    * Call made when each time a new manifold face is created by a merge.
    */
  virtual void ReactToMergeFaces (const CATPolyBodyBarGraph& iBodyGraph, unsigned int f, const CATSetOfInt& iOriginalFaces) {}

  };

  inline void SetCellObserver (CellObserver* obs);
  inline CellObserver* GetCellObserver () const;

public:

  /**
   * Adds a new cell to the CATPolyBodyBarGraph.
   * @return 
   *   The cell ID which identifies this cell.
   */
  unsigned int AddCell ();

  /**
   * Adds a new cell to the CATPolyBodyBarGraph sharing attributues with an existing cell.
   * (Construction of manifold cells.)
   * @param c
   *   The index of the current cell.
   * @return 
   *   The cell ID which identifies this cell.
   */
  unsigned int AddManifoldCell (const unsigned int c);

  /**
   * Removes all the cells.
   */
  void FlushCells ();

/** @} */


public:

/** @name Node Management
    @{ */

  /**
   * Adds a vertex node and returns its index.
   * @param v
   *   The index of the vertex.
   * @param oNode
   *   The returned index of the node.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the node is added successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  HRESULT AddVertexNode (const unsigned int v, unsigned int& oNode);

  /**
   * Adds a edge node and returns its index.
   * @param e
   *   The index of the edge.
   * @param oNode
   *   The returned index of the node.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the node is added successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  HRESULT AddEdgeNode (const unsigned int e, unsigned int& oNode);

  /**
   * Adds a face node and returns its index.
   * @param f
   *   The index of the face.
   * @param oNode
   *   The returned index of the node.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the node is added successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  HRESULT AddFaceNode (const unsigned int f, unsigned int& oNode);

  /**
   * Turns a node into a vertex node.
   */ 
  HRESULT UpdateVertexNode (const unsigned int n, unsigned int v);

  /**
   * Turns a node into a edge node.
   */ 
  HRESULT UpdateEdgeNode (const unsigned int n, unsigned int e);

  /**
   * Turns a node into a face node.
   */ 
  HRESULT UpdateFaceNode (const unsigned int n, unsigned int f);

  /**
   * Removes a node from the graph.
   * Add the bars adjacent to the node are also removed.
   * @param iNode
   *   The input index of the node to remove.
   * @return
   *   <li> <tt>S_OK</tt> if the node is removed successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   */
  inline HRESULT RemoveNode (const unsigned int iNode);

  /**
   * Returns the node type.
   * @return
   *   <ul>
   *     <li> eVertexNode
   *     <li> eEdgeNode
   *     <li> eFaceNode
   *   </ul>
   */
  NodeType GetNodeType (const unsigned int iNode) const;

  /**
 * Returns the more restrictive type between the real and the forced one.
 * @return
 *   <ul>
 *     <li> eVertexNode
 *     <li> eEdgeNode
 *     <li> eFaceNode
 *   </ul>
 */
  NodeType GetForcedNodeType(const unsigned int iNode) const;

  /**
   * Returns the cell associated to the node.
   * @param iNode
   *   The index of the node.
   * @return
   *   The index of the cell or 0 if the cell is invalid.
   */
  unsigned int GetNodeCell (const unsigned int iNode) const;

  /**
   * Returns the number of nodes in the graph.
   */
  inline unsigned int GetNbNodes () const;

  /**
   * Returns <tt>TRUE</tt> if the node has adjacent bars and <tt>FALSE</tt> otherwise.
   */
  inline CATBoolean NodeHasAdjacentBar (const unsigned int iNode) const;

/** @} */


public:

/** @name Bar Management
    @{ */

  /**
   * Adds a bar between two existing nodes.
   * @param e
   *   The index of the edge to which the bar belongs.
   * @param iPreviousBar
   *   The index of the previous bar adjacent to the added bar at iNode0 if applicable or 0.
   * @param iNode0
   *   The index of the start node.
   *   This node must be adjacent to the previous bar.
   * @param iVertex1
   *   The index of the end node.
   *   This node must be adjacent to the next bar.
   * @param iNextBar
   *   The index of the next bar adjacent to the added bar at iNode1 if applicable or 0.
   * @param oBar
   *   The index of the added bar.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the bar is added successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  HRESULT AddEdgeBar (const unsigned int e, 
                      const unsigned int iPreviousBar, const unsigned int iNode0, const unsigned int iNode1, const unsigned int iNextBar,
                      unsigned int& oBar);

  /**
   * Adds a bar between two existing nodes.
   * @param f
   *   The index of the face to which the bar belongs.
   * @param iPreviousBar
   *   The index of the previous bar adjacent to the added bar at iNode0 if applicable or 0.
   * @param iNode0
   *   The index of the start node.
   *   This node must be adjacent to the previous bar.
   * @param iVertex1
   *   The index of the end node.
   *   This node must be adjacent to the next bar.
   * @param iNextBar
   *   The index of the next bar adjacent to the added bar at iNode1 if applicable or 0.
   * @param oBar
   *   The index of the added bar.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the bar is added successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  HRESULT AddFaceBar (const unsigned int f, 
                      const unsigned int iPreviousBar, const unsigned int iNode0, const unsigned int iNode1, const unsigned int iNextBar,
                      unsigned int& oBar);

  /**
   * Turns a bar into an edge bar.
   */ 
  HRESULT UpdateEdgeBar (const unsigned int b, unsigned int e);

  /**
   * Turns a bar into a face bar.
   */ 
  HRESULT UpdateFaceBar (const unsigned int b, unsigned int f, CATBoolean doRemoveOldTextures);

  /**
   * Removes the bar.
   * @param iBar
   *   The index of the bar to remove.
   * @return
   *   S_OK if the bar is removed and E_FAIL otherwise.
   */
  HRESULT RemoveBar (const unsigned int iBar);

  /**
   * Removes texture indices associated to the bar.
   * @param iBar
   *   The index of the bar wich texture indices need to be removed.
   * @param adjacentFace0
   *   Adjacent CCW face for node 0 of iBar. Used to find the surfaceLayer which contains texture to remove. If 0 nothing is done. If -1 adjacentFace0 is computed.
   * @param adjacentFace0
   *   Same as adjacentFace0 but for node 1.
   * @return
   *   S_OK if the corresponding texture indices is removed and E_FAIL otherwise.
   */
  HRESULT RemoveBarTextures(const unsigned int iBar, int adjacentFace0 = -1, int adjacentFace1 = -1);

  /**
   * Returns the nodes adjacent to a bar.
   * @param iBar
   *   The index of the bar.
   * @param oNode0
   *   The index of the first node of the bar.
   * @param oNode1
   *   The index of the second node of the bar.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the nodes are returned successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  inline HRESULT GetBar (const unsigned int iBar, unsigned int& iNode0, unsigned int& iNode1) const;

  /**
   * Returns the bar type.
   * @return
   *   <ul>
   *     <li> eEdgeBar
   *     <li> eFaceBar
   *   </ul>
   */
  BarType GetBarType (const unsigned int iBar) const;

  /**
 * Returns the bar or forced bar type.
 * @return
 *   <ul>
 *     <li> eEdgeBar
 *     <li> eFaceBar
 *   </ul>
 */
  BarType GetForcedBarType(const unsigned int iBar) const;

  /**
   * Returns <tt>TRUE</tt> if the bar is an edge-bar.
   */
  CATBoolean IsEdgeBar (const unsigned int b) const;

  /**
   * Returns <tt>TRUE</tt> if the most restrictive type between the real and the forced ons is edge-bar.
   */
  CATBoolean IsForcedEdgeBar(const unsigned int b) const;

  /**
   * Returns the cell associated to the bar.
   * @param iBar
   *   The index of the bar.
   * @return
   *   The index of the cell or 0 if the cell is invalid.
   */
  unsigned int GetBarCell (const unsigned int iBar) const;

  /**
   * Returns the first node from the bar b.
   */
  inline unsigned int Node0 (unsigned int b) const;

  /**
   * Returns the second node from the bar b.
   */
  inline unsigned int Node1 (unsigned int b) const;

  /**
   * Returns the number of bars in the graph.
   */
  inline unsigned int GetNbBars () const;

  /**
   * Returns the number of bars referencing a specific node (valence of the node).
   */
  inline unsigned int GetNbBars (const unsigned int iNode) const;

/** @} */


public:

/** @name Node and Bar Adjacency Attributes
    @{ */

  /**
   * Sets the face adjacent to a bar (left side from the node if facets are oriented CCW.)
   * A bar has at most two adjacent faces which may not necessarily be set.
   * An adjacent face may be set to 0.
   */
  void SetAdjacentFace (const unsigned int iNode, const unsigned int iBar, const unsigned int f, CATBoolean doRemoveOldTextures);

  /**
   * Unsets the face adjacent to a bar (left side from the node if facets are oriented CCW.)
   */
  void UnsetAdjacentFace (const unsigned int iNode, const unsigned int iBar);

  /**
   * Gets the face adjacent to a bar (on the left side from the node if facets are oriented CCW.)
   * If an adjacent face has been set for this pair (node, bar), the method returns <tt>TRUE</tt>
   * Otherwise, the method returns <tt>FALSE</tt> and the returned value for the face is 0.
   */
  CATBoolean GetAdjacentFace (const unsigned int iNode, const unsigned int iBar, unsigned int& f) const;

  /**
   * See CATPolyBodyBarGraph::GetAdjacentFace ().
   */
  inline CATBoolean GetAdjacentFaceCCW (const unsigned int iNode, const unsigned int iBar, unsigned int& f) const;

  /**
   * Gets the face adjacent to a bar (on the right side from the node if facets are oriented CCW.)
   * If an adjacent face has been set for this pair (node, bar), the method returns <tt>TRUE</tt>
   * Otherwise, the method returns <tt>FALSE</tt> and the returned value for the face is 0.
   */
  CATBoolean GetAdjacentFaceCW (const unsigned int iNode, const unsigned int iBar, unsigned int& f) const;

/** @} */

public:

/** @name Boundary Attributes
    @{ */

  /**
   * Returns <tt>TRUE</tt> if the bar is on a boundary.
   * A bar is a boundary-bar if it has only one adjacent face.
   * A boundary bar is not necessarily an edge bar; it can be a face bar.
   */
  CATBoolean IsBoundaryBar (const unsigned int b) const;

  /**
   * Returns <tt>TRUE</tt> if the bar has no adjacent face.
   * A bar without an adjacent face is not a boundary bar; it is a wire bar.
   */
  CATBoolean IsBarWithoutAdjacentFace (const unsigned int b) const;

  /**
   * Returns <tt>TRUE</tt> if the node is on a boundary.
   * A node is a boundary node if it is adjacent to at least one boundary bar.
   */
  CATBoolean IsBoundaryNode (const unsigned int n) const;

  /**
   * Create forced edge bars and forced edge / vertices nodes on bar graph.
   */
  HRESULT ComputeForcedTopology(const CATBoolean DoFreezeBoundary, const double iAngleTol);

/** @} */

public:

/** @name Node and Bar Services
    @{ */

  /** 
   * Merges two nodes.
   * All references to Node iNode1 are replaced by references to Node iNode0
   * The bar(s) between the two nodes is (are) collapsed and the graph is updated.
   * @param iNode0
   *   The first node of the merge.  This node is kept.
   * @param iNode1
   *   The second node of the merge.  This node is deleted.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the nodes are merged successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  HRESULT MergeNodes (const unsigned int iNode0, const unsigned int iNode1);

  /** 
   * Merges two bars.
   *
   * The two bars are merged if either:
   * <ul>
   *   <li> The loop n0, b0, n1, b0, as specified by the order of the argument is degenerate; or,
   *   <li> Both bars b0 and b1 are boundary bars without left and right adjacencies,
   *        for b0 and b1, respectively for a CCW direction (the opposite for a CW direction.)
   * </ul>
   * Otherwise the merge does not proceed.
   *
   * The second bar, iBar1 is removed during the merge.
   * Two observer calls will be made prior to the merge and removal of the bar
   * (PrepareToMergeBars and PrepareToRemoveBar).
   *
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the bars are merged successfully;
   *   <li> <tt>S_FALSE</tt> if the bars cannot be merged (for instance two bars not sharing the same nodes);
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  HRESULT MergeBars (const unsigned int iNode0, const unsigned int iBar0, const unsigned int iNode1, const unsigned int iBar1);

  /** 
   * Splits a bar into two bars.
   * This operation creates a new node and a new bar.
   * Observer calls will be made after the split of the bar.
   * @param iBar
   *   The bar to be split.
   * @param oNode
   *   The new node created to split the bar.
   * @param oBar
   *   The new bar created by the split of the input bar.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the bar is splitted successfully;
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  inline HRESULT SplitBar (const unsigned int iBar, unsigned int& oNode, unsigned int& oBar);

  /**
   * Try to recover a triangle by following the loop starting with
   * the provided node and bar.
   * @param iNode
   *   The first node of the hypothetical triangle
   * @param iBar
   *   The first bar of the hypothetical triangle
   * @param oNodes
   *   If successful, the three nodes of the recovered triangle, the first one being iNode
   * @param oBars
   *   If successful, the three bars of the recovered triangle, the first one being iBar
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a triangle was found;
   *   <li> <tt>E_FAIL</tt> otherwise.
   * </ul>
   */
  HRESULT FetchTriangle(const unsigned int iNode, const unsigned int iBar, unsigned int oNodes[3], unsigned int oBars[3]) const;

/** @} */


public:

/** @name Bar services
    @{ */

  /**
   * Links two bars around a node.
   * The two bars must share a node.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the bars are linked successfully;
   *   <li> <tt>S_FALSE</tt> if the bars are already linked around the node;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  inline HRESULT LinkBars (const unsigned int iBarFrom, const unsigned int iNode, const unsigned int iBarTo);

  /**
   * Unlinks two bars around a node.
   * The two bars must share a node.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the bars are unlinked successfully;
   *   <li> <tt>S_FALSE</tt> if the bars are already unlinked around the node;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  inline HRESULT UnlinkBars (const unsigned int iBarFrom, const unsigned int iNode, const unsigned int iBarTo);

  /**
   * Finds a unique bar between two nodes.
   * Returns the number of bars between the two nodes.
   * @param iNode0
   *   The first node.
   * @param iNode1
   *   The second node.
   * @param b
   *   The unique bar between the two nodes.  If there is more than one bar, then returns 0.
   * @param bPrev
   *   The bar that precedes the unique bar around the first node (iNode0) or 0.
   * @param bNext
   *   The bar that succeeds the unique bar around the first node (iNode0) or 0.
   * @return
   *   The number of bars between the two nodes.
   */
  inline unsigned int FindUniqueBar (const unsigned int iNode0, const unsigned int iNode1,
                                     unsigned int& b, unsigned int& bPrev, unsigned int& bNext, int edgebar) const;

  /**
   * Finds all bars between two nodes.
   * @param iNode0
   *   The first node.
   * @param iNode1
   *   The second node.
   * @param oBars
   *   List of bar indices
   * @return
   *   The number of bars between the two nodes.
   */
  inline unsigned int FindBars (const unsigned int iNode0, const unsigned int iNode1, CATSetOfInt & oBars) const;

/** @} */


public:

/** @name Layer management
    @{ */

  inline CATPolyBarGraph& GetBarGraph ();
  inline const CATPolyBarGraph& GetBarGraph () const;

  inline CATPolyBodyBarGraphNodeCellLayer* GetNodeCellLayer ();
  inline const CATPolyBodyBarGraphNodeCellLayer* GetNodeCellLayer () const;

  inline CATPolyBodyBarGraphBarCellLayer* GetBarCellLayer ();
  inline const CATPolyBodyBarGraphBarCellLayer* GetBarCellLayer () const;

  /**
   * Returns the number of frames.
   */
  inline unsigned int GetNbFrames () const;

  /**
 * Set the number of normal layers.
 */
  inline void SetNormalLayer(CATBoolean hasNormalLayer);

  /**
  * Returns TRUE if there is a normal layer.
  */
  inline CATBoolean HasNormalLayer() const;

  /**
   * Set the number of texture layers.
   */
  inline void SetNbTextureLayers(unsigned int nbLayers);

  /**
  * Returns the number of texture layers.
  */
  inline unsigned int GetNbTextureLayers() const;

  inline void SetNbUnknownLayers(unsigned int nbLayers); //TODO JBS2COMMENT OR  MERGE / REMOVE ??
  inline unsigned int GetNbUnknownLayers() const;

  /**
   * Update layers information.
   */
  inline void AddDataLayer(unsigned int layer, unsigned int dimension, CATBoolean isConstraint);

  /**
   * Returns layer maximum dimension.
   */
  inline unsigned int GetDataLayerDimension(unsigned int layer) const;

  /**
   * Returns TRUE if data layer is a constraint.
   */
  inline unsigned int IsDataLayerConstraint(unsigned int layer) const;

  /**
* Returns the number of layers.
*/
  inline unsigned int GetNbDataLayers() const;

  /**
   * The frame index ranges from 0 to GetNbFrames () - 1.
   */
  CATPolyBarGraphNodePositionLayer* GetNodePositionLayer (const unsigned int iFrame = 0);
  const CATPolyBarGraphNodePositionLayer* GetNodePositionLayer (const unsigned int iFrame = 0) const;

  /**
   * Adds surface layers and asociates them to a face.
   * @param f
   *   The index of the surface.
   * @param iSize
   *   The size of the layers.
   */
  HRESULT AddSurfaceLayers (const unsigned int f, const unsigned int iSize);

  /**
   * Removes the surface layers associated to a face.
   * @param f
   *   The index of the surface.
   */
  HRESULT RemoveSurfaceLayers (const unsigned int f);

  /**
   * Returns the layers associated to a face.
   */
  CATPolyBodyBarGraphSurfaceLayers* GetSurfaceLayers (const unsigned int f);
  const CATPolyBodyBarGraphSurfaceLayers* GetSurfaceLayers (const unsigned int f) const;

  /**
   * Returns <tt>TRUE</tt> if the all input vertex position layers were in float.
   */
  inline CATBoolean HasInputVertexPositionLayersInFloat () const;

  /**
   * Returns <tt>TRUE</tt> if the surfaces have a vertex normal layer.
   */
  inline CATBoolean HasSurfaceVertexNormalLayers () const;

  /**
   * Returns <tt>TRUE</tt> if the surfaces have a vertex texture coordinates layer (1D- or 2D-coordinates.)
   * @param oDim
   *   The output dimension of the layer of texture coordinates.
   */
  inline CATBoolean HasSurfaceVertexTextureCoordLayers (unsigned int& oDim) const;

  /**
  * Returns <tt>TRUE</tt> if the bar graph has a flag set for solid domains.
  */
  inline CATBoolean HasSolidDomains () const;

  /**
  * Returns <tt>TRUE</tt> if the bar graph has a flag set for skin domains.
  */
  inline CATBoolean HasSkinDomains () const;

  /**
  * Returns <tt>TRUE</tt> if the bar graph has a flag set for wire domains.
  */
  inline CATBoolean HasWireDomains () const;

  /**
   * Removes all the surface layers.
   */
  void FlushSurfaceLayers ();

/** @} */


public:

/** @name Event Listener. 
    Event listener are used to update attributes (user-defined layers.)
    @{ */

  /**
   * Registers an observer (event listener) with the instance. 
   * A note about observers:  When several observers are registered, the last observer to be registered
   * is the first to observe an event.  Observers are called in the sequence: Last In, First to Observe.
   * @param iObserver
   *   The observer that is registered with the instance.
   * @return 
   * <ul>
   *   <li> <tt>S_OK</tt> if the observer is successfully registered.
   *   <li> <tt>S_FALSE</tt> otherwise.
   * </ul>
   */
  HRESULT RegisterObserver (CATPolyBodyBarGraphObserver& iObserver) const;

  /** 
   * Unregisters an observer (event listener) with the instance. 
   * @param iObserver
   *   The observer that is unregistered with the instance.
   * @return 
   * <ul>
   *   <li> <tt>S_OK</tt> if the observer is successfully unregistered.
   *   <li> <tt>S_FALSE</tt> otherwise.
   * </ul>
   */
  HRESULT UnregisterObserver (CATPolyBodyBarGraphObserver& iObserver) const;

  /** 
   * Get the collapse restriction from textures around a bar. 
   * @param iNode0
   *   Node 0 index of the bar.
   * @param iNode1
   *   Node 1 index of the bar.
   * @param iBar
   *   Index of bar between node 0 and node 1.
   * @param iIsRestrictedToN0
   *   TRUE if collapse is already restricted to bar start.
   * @param iFrame
   *   Frame index.
   * @return 
   * <ul>
   *   <li> <tt>3</tt> No Restriction.
   *   <li> <tt>2</tt> Restricted to the bar.
   *   <li> <tt>1</tt> Restricted to node 1.
   *   <li> <tt>0</tt> Restricted to node 0.
   *   <li> <tt>-1</tt> Uncollapsable bar.
   * </ul>
   */
  int GetTextureRestriction(unsigned int iNode0, unsigned int iNode1, unsigned int iBar, CATBoolean iIsRestrictedToN0, unsigned int iFrame = 0);

  /**
  * Get boundary node restriction from boundary edges around node (used for NavReps)
  * @param iNode0
  *   Node 0 index of the bar.
  * @param iNode1
  *   Node 1 index of the bar.
  * @return
  * <ul>
  *   <li> <tt>3</tt> No Restriction.
  *   <li> <tt>1</tt> Restricted to node 1.
  *   <li> <tt>0</tt> Restricted to node 0.
  *   <li> <tt>-1</tt> Uncollapsable bar.
  * </ul>
  */
  int GetBoundaryRestriction(unsigned int iNode0, unsigned int iNode1);

  /**
   * Get constraint for decimation when face node computation failed. if onlyEdges is TRUE, sharpness check limited to edges.
   * @param iFrame
       Node 0 index of the bar.
   * @param b
      bar index.
   * @param n0
       Node 0 index of the bar.
   * @param n1
       Node 1 index of the bar.
   * @param sharpAngle
       Angle for sharpness evaluation.
   * @param onlyEdges
       If TRUE sharpness check is limited to edges.
   * @return
   * <ul>
    *   <li> <tt>3</tt> No Restriction.
   *   <li> <tt>2</tt> Restricted to bar.
   *   <li> <tt>1</tt> Restricted to node 1.
   *   <li> <tt>0</tt> Restricted to node 0.
   *   <li> <tt>-1</tt> Uncollapsable bar.
   * </ul>
   */
  int GetSharpBarsRestriction(unsigned int iFrame, unsigned int b, unsigned int n0, unsigned int n1, double sharpAngle, CATBoolean onlyEdges) const;

  /** 
   * A cut bar has at least different textures for one of its nodes on each side of its side. 
   * @param iBar
   *   Bar index.
   * @param iFrame
   *   Frame index.
   * @param iForce
   *   Force check of texture values ignoring cutStatus check.
   * @return 
   * <ul>
   *   <li> <tt>TRUE</tt> The bar is a cut bar.
   *   <li> <tt>FALSE</tt> The bar isn't a cut bar.
   * </ul>
   */
  CATBoolean IsCutBar(unsigned int iBar, unsigned int iFrame = 0, CATBoolean iForce = FALSE) const;

  /**
  * Includes the 1D texture coordinate for the simplification of the bars and placement of the nodes.
  * @param iWeight
  *   The weight given to the texture coordinate.
  */
  void DoProcessTextureCoordinatesConstraints(unsigned int iDoProcessTextureCoordinatesConstraints);

  /** 
   * Set a parameter to enable an additional convexity check for chart border bars to add restrictions on collapse that assure that decimation always keep texture coordinates inside previous charts.
   * @param iTextureCoordinatesInsideCharts
   *   TRUE to enable additional convexity check.
   */
   void SetTextureCoordinatesInsideCharts(CATBoolean iTextureCoordinatesInsideCharts);

  /** 
   * Function to know if bar graph has texture layers supporting multiple UV for each node.
   * @param SL
   *   Also check if the current surface layer has a texture layer.
   * @param iFrame
   *   Frame index.
   * @return 
   * <ul>
   *   <li> <tt>TRUE</tt> The texture layer support multiple UV for one node.
   *   <li> <tt>FALSE</tt> The texture layer does not support multiple UV for one node.
   * </ul>
   */
   CATBoolean PreserveTextureCuts(const CATPolyBodyBarGraphSurfaceLayers *SL = NULL, unsigned int iFrame = 0) const;

  /** 
   * Check if a node has exacty two cut bars including the bar in argument.
   * @param iNode
   *   Node index.
   * @param iBar
   *   Index of the first cut bar.
   * @param Frame
   *   Frame index.
   * @return 
   * <ul>
   *   <li> <tt>TRUE</tt> Check succeded.
   *   <li> <tt>FALSE</tt> Check failed.
   * </ul>
   */
   CATBoolean HasExactlyOneExtraCutBar(unsigned int iNode, unsigned int iBar, unsigned int iFrame = 0) const;

  /** 
   * Check if the node and his two cut bars is convex on their two adjacent charts.
   * @param iNode
   *   Node index.
   * @param iIsCut
   *   TRUE if the node has cut bars, else node is considered as boundary node.
   * @param iFrame
   *   Frame index.
   * @return 
   * <ul>
   *   <li> <tt>TRUE</tt> Check succeded.
   *   <li> <tt>FALSE</tt> Check failed.
   * </ul>
   */
   CATBoolean IsConvexInTextureSpace(unsigned int iNode, CATBoolean iIsCut, unsigned int iFrame = 0) const;

   /**
    * Allow cut creation when the merge node methods are called in texture layer observer.
    * @param enable
    *   TRUE enable cut creation, FALSE to disable.
    */
   void MergeNodeCreateCut(CATBoolean enable) const;

/** @} */
private:
  struct DataLayerInfo
  {
    unsigned int _Dimension = 0;
    CATBoolean _IsConstraint = FALSE;
  };

private:

    const static double LocalLargeEpsilonForAngleTest;

    CATBoolean CheckOrientedConvexity(unsigned int iNode0, unsigned int iNode1, unsigned int iNode2, unsigned int iBar0, unsigned int iBar1, unsigned int iFace0, unsigned int iFace1, unsigned int iFrame = 0) const;

private:

  //
  // Member Data
  //

  // 1. Bar Graph

  CATPolyBarGraph _BarGraph;

  // 2. Cell IDs

  unsigned int _CurrentCell;  // Current cell ID. Cell ID 0 is invalid.

  // 3. Layers of the bar graph.

  // Node layers.
  CATPolyBodyBarGraphNodeCellLayer* _NodeCellLayer;      // Layer of node attributes (cell, vertex and index.)
  CATPolyBarGraphNodePositionLayer* _NodePositionLayer;  // Layer or layers (one for each frame) of node positions.

  // Bar layers.
  CATPolyBodyBarGraphBarCellLayer* _BarCellLayer;        // Layer of bar cells.

  // Surface layers.
  CATMapOfIntToPtr* _MapSurfaceToLayerData;              // Map a face index to additional layers: normals and texture coordinates.

  // Observer of the bar graph (CATPolyBarGraph) for update the layers of this class.
  // It will also forward the observer calls to the registered CATPolyBodyBarGraphObserver observers.
  CATPolyBodyBarGraphLayerObserver* _BarGraphObserver;  
  CATPolyBodyBarGraphTextureLayerObserver* _BarGraphTextureLayerObserver;
  CellObserver* _CellObserver;

  const unsigned int _NbFrames;
  CATBoolean _HasNormalLayer; //TODO JBS2 REMOVE
  unsigned int _NbTextureLayers; //TODO JBS2 REMOVE
  unsigned int _NbUnknownLayers; //TODO JBS2 REMOVE
  std::vector<DataLayerInfo> _DataLayers;
  unsigned int _DoProcessTextureCoordinatesConstraints; // Includes the 1D or 2D texture coordinate for the simplification of the bars and placement of the nodes. \\TODO JBS2 RENAME
  CATBoolean _TextureCoordinatesInsideCharts; // Enable convexity check for texture coordinates interpolation.
  unsigned int _BitField;  // Bits for various attributes.

  /**
   * Types of the nodes.
   */
  enum BitField
  {
    /** Normal Layer. */                                                         eNormalLayer        = 0x01,
    /** Texture 1D Layer. */                                                     eTexture1DLayer     = 0x02,
    /** Texture 2D Layer. */                                                     eTexture2DLayer     = 0x04,
    /** Input vertex position layers in float. */                                eFloatPositionLayer = 0x08,
    /** Dimension 0 (domains): Markers */                                        eDomain0            = 0x10,
    /** Dimension 1 (domains): Wires */                                          eDomain1            = 0x20,
    /** Dimension 2 (domains): Skins */                                          eDomain2            = 0x40,
    /** Dimension 3 (domains): Solids */                                         eDomain3            = 0x80
  };

private:

  friend class CATPolyBodyBarGraphBuilder;
  friend class CATPolyBodyBarGraphBuilderLayerUpdater;
  friend class CATPolyBodyBarGraphSurfaceLayerIterator;

private:

  inline void SetBitForInputVertexPositionLayersInFloat ();
  inline void SetBitForSurfaceVertexNormalLayers ();
  inline void SetBitForSurfaceVertexTexture1DCoordLayers ();
  inline void SetBitForSurfaceVertexTexture2DCoordLayers ();

  inline void SetBitForSolidDomains ();
  inline void SetBitForSkinDomains ();
  inline void SetBitForWireDomains ();

  inline CATPolyBodyBarGraphLayerObserver* GetBarGraphObserver () const {return _BarGraphObserver;}
};


inline void CATPolyBodyBarGraph::SetCellObserver (CellObserver* obs)
{
  _CellObserver = obs;
}

inline CATPolyBodyBarGraph::CellObserver* CATPolyBodyBarGraph::GetCellObserver () const
{
  return _CellObserver;
}

inline CATPolyBarGraph& CATPolyBodyBarGraph::GetBarGraph ()
{
  return _BarGraph;
}

inline const CATPolyBarGraph& CATPolyBodyBarGraph::GetBarGraph () const
{
  return _BarGraph;
}

inline unsigned int CATPolyBodyBarGraph::GetNbFrames () const
{
  return _NbFrames;
}

inline void CATPolyBodyBarGraph::SetNormalLayer(CATBoolean hasNormalLayer)
{
  _HasNormalLayer = hasNormalLayer;
}

inline CATBoolean CATPolyBodyBarGraph::HasNormalLayer() const
{
  return _HasNormalLayer;
}

inline void CATPolyBodyBarGraph::SetNbTextureLayers(unsigned int nbLayers)
{
  _NbTextureLayers = nbLayers;
}

inline unsigned int CATPolyBodyBarGraph::GetNbTextureLayers() const
{
  return _NbTextureLayers;
}

inline void CATPolyBodyBarGraph::SetNbUnknownLayers(unsigned int nbLayers)
{
  _NbUnknownLayers = nbLayers;
}

inline unsigned int CATPolyBodyBarGraph::GetNbUnknownLayers() const
{
  return _NbUnknownLayers;
}

inline void CATPolyBodyBarGraph::AddDataLayer(unsigned int layer, unsigned int dimension, CATBoolean isConstraint)
{
  if (layer >= _DataLayers.size())
    _DataLayers.resize(layer + 1);
  if (dimension > _DataLayers[layer]._Dimension)
  _DataLayers[layer]._Dimension = dimension;
  if (isConstraint)
    _DataLayers[layer]._IsConstraint = TRUE;
}

inline unsigned int CATPolyBodyBarGraph::GetDataLayerDimension(unsigned int layer) const
{
  return _DataLayers[layer]._Dimension;
}

inline unsigned int CATPolyBodyBarGraph::IsDataLayerConstraint(unsigned int layer) const
{
  return _DataLayers[layer]._IsConstraint;
}

inline unsigned int CATPolyBodyBarGraph::GetNbDataLayers() const
{
  return _HasNormalLayer ? 1 + _NbTextureLayers + _NbUnknownLayers : _NbTextureLayers + _NbUnknownLayers;
}

inline CATPolyBodyBarGraphNodeCellLayer* CATPolyBodyBarGraph::GetNodeCellLayer ()
{
  return _NodeCellLayer;
}

inline const CATPolyBodyBarGraphNodeCellLayer* CATPolyBodyBarGraph::GetNodeCellLayer () const
{
  return _NodeCellLayer;
}

inline CATPolyBodyBarGraphBarCellLayer* CATPolyBodyBarGraph::GetBarCellLayer ()
{
  return _BarCellLayer;
}

inline const CATPolyBodyBarGraphBarCellLayer* CATPolyBodyBarGraph::GetBarCellLayer () const
{
  return _BarCellLayer;
}

inline unsigned int CATPolyBodyBarGraph::GetNbNodes () const
{
  return _BarGraph.GetNbNodes ();
}

inline CATBoolean CATPolyBodyBarGraph::NodeHasAdjacentBar (const unsigned int iNode) const
{
  return _BarGraph.NodeHasAdjacentBar (iNode);
}

inline unsigned int CATPolyBodyBarGraph::GetNbBars () const
{
  return _BarGraph.GetNbBars ();
}

inline unsigned int CATPolyBodyBarGraph::GetNbBars (const unsigned int iNode) const
{
  return _BarGraph.GetNbBars (iNode);
}

inline HRESULT CATPolyBodyBarGraph::GetBar (const unsigned int iBar, unsigned int& iNode0, unsigned int& iNode1) const
{
  return _BarGraph.GetBar (iBar, iNode0, iNode1);
}

inline unsigned int CATPolyBodyBarGraph::Node0 (unsigned int b) const
{
  return _BarGraph.Node0 (b);
}

inline unsigned int CATPolyBodyBarGraph::Node1 (unsigned int b) const
{
  return _BarGraph.Node1 (b);
}

inline HRESULT CATPolyBodyBarGraph::RemoveNode (const unsigned int iNode)
{
  return _BarGraph.RemoveNode (iNode);
}

inline unsigned int CATPolyBodyBarGraph::FindUniqueBar (const unsigned int iNode0, const unsigned int iNode1,
                                                        unsigned int& b, unsigned int& bPrev, unsigned int& bNext, int edgebar) const
{
  return _BarGraph.FindUniqueBar (iNode0, iNode1, b, bPrev, bNext, edgebar);
}

inline unsigned int CATPolyBodyBarGraph::FindBars (const unsigned int iNode0, const unsigned int iNode1, CATSetOfInt & oBars) const
{
  return _BarGraph.FindBars (iNode0, iNode1, oBars);
}

inline HRESULT CATPolyBodyBarGraph::LinkBars (const unsigned int iBarFrom, const unsigned int iNode, const unsigned int iBarTo)
{
  return _BarGraph.LinkBars (iBarFrom, iNode, iBarTo);
}

inline HRESULT CATPolyBodyBarGraph::UnlinkBars (const unsigned int iBarFrom, const unsigned int iNode, const unsigned int iBarTo)
{
  return _BarGraph.UnlinkBars (iBarFrom, iNode, iBarTo);
}

inline HRESULT CATPolyBodyBarGraph::SplitBar (const unsigned int iBar, unsigned int& oNode, unsigned int& oBar)
{
  return _BarGraph.SplitBar (iBar, oNode, oBar);
}

inline CATBoolean CATPolyBodyBarGraph::GetAdjacentFaceCCW (const unsigned int iNode, const unsigned int iBar, unsigned int& f) const
{
  return GetAdjacentFace (iNode, iBar, f);
}

inline CATBoolean CATPolyBodyBarGraph::HasInputVertexPositionLayersInFloat () const
{
  return _BitField & eFloatPositionLayer ? TRUE : FALSE;
}

inline CATBoolean CATPolyBodyBarGraph::HasSurfaceVertexNormalLayers () const
{
  return _BitField & eNormalLayer ? TRUE : FALSE;
}

inline CATBoolean CATPolyBodyBarGraph::HasSurfaceVertexTextureCoordLayers (unsigned int& oDim) const
{
  oDim = 0;
  if (_BitField & eTexture1DLayer)
    oDim = 1;
  else if (_BitField & eTexture2DLayer)
    oDim = 2;
  return oDim ? TRUE : FALSE;
}

inline CATBoolean CATPolyBodyBarGraph::HasSolidDomains () const
{
  return _BitField & eDomain3;
}

inline CATBoolean CATPolyBodyBarGraph::HasSkinDomains () const
{
  return _BitField & eDomain2;
}

inline CATBoolean CATPolyBodyBarGraph::HasWireDomains () const
{
  return _BitField & eDomain1;
}

inline void CATPolyBodyBarGraph::SetBitForInputVertexPositionLayersInFloat ()
{
  _BitField |= eFloatPositionLayer;
}

inline void CATPolyBodyBarGraph::SetBitForSurfaceVertexNormalLayers ()
{
  _BitField |= eNormalLayer;
}

inline void CATPolyBodyBarGraph::SetBitForSurfaceVertexTexture1DCoordLayers ()
{
  _BitField |= eTexture1DLayer;
}

inline void CATPolyBodyBarGraph::SetBitForSurfaceVertexTexture2DCoordLayers ()
{
  _BitField |= eTexture2DLayer;
}

inline void CATPolyBodyBarGraph::SetBitForSolidDomains ()
{
  _BitField |= eDomain3;
}
inline void CATPolyBodyBarGraph::SetBitForSkinDomains ()
{
  _BitField |= eDomain2;
}
inline void CATPolyBodyBarGraph::SetBitForWireDomains ()
{
  _BitField |= eDomain1;
}

#endif
