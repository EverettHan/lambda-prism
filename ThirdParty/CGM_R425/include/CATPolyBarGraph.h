// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarGraph.h
//
//===================================================================
// August 2011  Creation NDO
// June   2015  Modif    JXO: FindBars
//===================================================================
#ifndef CATPolyBarGraph_H
#define CATPolyBarGraph_H

#include "PolyBarGraph.h"
#include "CATPolyRefCounted.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATBucketsOfInt.h"
#include "CATSetOfInt.h"
#include "CATPolyBuckets.h"



class CATPolyBarGraphObserver;
class CATPolyBarGraphNodeFanIterator;
class CATPolyBarGraphNode;
using CATPolyBarGraphNodeVector = CATPolyBuckets<CATPolyBarGraphNode>;


/**
 * Graph of nodes and bars.  
 *
 * In a mathematical graph, the nodes would be referred to as vertices and the bars to as edges of the graph.  
 * However in this data structure, the names of nodes and bars replace those of vertices and edges to distinguish 
 * them from the vertices of meshes and the edges of the polyhedral model.
 *
 * In the bar graph, an adjacency relation is maintained among the bars around a node. Adjacency is kept by sorting
 * the bars around each node. Two bars are adjacent if there is a link between the two bars around the node. 
 * A bar may be adjacent to at most two bars around a node where it is linked to a previous and to a next bar. 
 *
 * A set of incident bars that are linked around a node defines a fan. 
 * A fan is open if its first and last bars are not linked to a previous and next bars respectively. 
 * A fan is closed when it is composed only of adjacent bars. 
 * There may be several open and closed fans around a node.
 *
 * The nodes and the bars have integer indices that start at 1.
 */
class ExportedByPolyBarGraph CATPolyBarGraph : public CATPolyRefCounted
{

public :

  /**
   * Construction of an instance of CATPolyBarGraph given a CATPolyBody.
   * The constructor does not extract any bars from the CATPolyBody.
   * (This is done by the CATPolyBarGraphExtractor or another operator.)
   */
  CATPolyBarGraph ();

  ~CATPolyBarGraph ();

public:

/** @name Node Management
    @{ */

  /**
   * Adds a node (or a vertex to the graph) and returns its index.
   * @param oNode
   *   The returned index of the node.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the node is added successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  HRESULT AddNode (unsigned int& oNode);

  /**
   * Removes a node from the graph.
   * The bars adjacent to the node are also removed.
   * @param iNode
   *   The input index of the node to remove.
   * @return
   *   <li> <tt>S_OK</tt> if the node is removed successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   */
  HRESULT RemoveNode (const unsigned int iNode);

  /**
   * Returns the number of nodes in the graph.
   */
  inline unsigned int GetNbNodes () const;

  /**
   * Returns <tt>TRUE</tt> if the node is valid.
   */
  CATBoolean IsNodeValid (const unsigned int iNode) const;

/** @} */


public:

/** @name Bar Management
    @{ */

  /**
   * Adds a bar between two existing nodes.
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
  HRESULT AddBar (const unsigned int iPreviousBar, const unsigned int iNode0, const unsigned int iNode1, const unsigned int iNextBar,
                  unsigned int& oBar);

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
  HRESULT LinkBars (const unsigned int iBarFrom, const unsigned int iNode, const unsigned int iBarTo);

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
  HRESULT UnlinkBars (const unsigned int iBarFrom, const unsigned int iNode, const unsigned int iBarTo);

  /**
   * Removes the bar.  
   * If there are two bars adjacent to the bar being removed around a node, 
   * then these two bars become adjacent after removal of this bar.  
   * The method returns <tt>S_FALSE</tt> if it is called with a bar that has already 
   * been removed (no calls to observers are made.)
   * @param iBar
   *   The index of the bar to remove.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the bar is removed successfully;
   *   <li> <tt>S_FALSE</tt> if the bar has been removed previously;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  HRESULT RemoveBar (const unsigned int iBar);

  /**
   * Returns the number of bars in the graph.
   */
  inline unsigned int GetNbBars () const;

  /**
   * Returns the number of bars referencing a specific node (valence of the node).
   */
  unsigned int GetNbBars (const unsigned int iNode) const;

  /**
   * Returns the number of bars and fans around a node.
   */
  unsigned int GetNbBars (const unsigned int iNode, unsigned int& oNbFans) const;

  /**
   * Returns the number of bars and tags around the node.
   * This number is greater or equal than GetNbBars (iNode).  
   * This method runs faster tnan GetNbBars (iNode):
   * (O(1) instead of O(nb) where nb is the number of bars around the node.)
   */
  unsigned int GetNbBarsAndTags (const unsigned int iNode) const;

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
  HRESULT GetBar (const unsigned int oBar, unsigned int& oNode0, unsigned int& oNode1) const;

  /**
   * Returns the first node from the bar b.
   */
  inline unsigned int Node0 (unsigned int b) const;

  /**
   * Returns the second node from the bar b.
   */
  inline unsigned int Node1 (unsigned int b) const;

  /**
   * Finds a bar between two nodes.
   * The bar between the two nodes may not be unique.
   * @param iNode0
   *   The first node.
   * @param iNode1
   *   The second node.
   * @return
   *   The bar between the two nodes or 0 if there is none.
   */
  unsigned int FindBar (const unsigned int iNode0, const unsigned int iNode1) const;
  
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
  unsigned int FindBars (const unsigned int iNode0, const unsigned int iNode1, CATSetOfInt & oBars) const;

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
   *   The bar that precedes the unique bar in the fan around iNode0
   *   or 0 if there is none.
   * @param bNext
   *   The bar that succeeds the unique bar in the fan around iNode1 
   *   or 0 if there is none.
   * @return
   *   The number of bars between the two nodes.
   */
  unsigned int FindUniqueBar (const unsigned int iNode0, const unsigned int iNode1,
                              unsigned int& b, unsigned int& bPrev, unsigned int& bNext, int edgebar) const;

  /**
   * Returns <tt>TRUE</tt> if the bar is valid.
   */
  inline CATBoolean IsBarValid (const unsigned int iBar) const;

/** @} */


public:

/** @name Node and Bar Services
    @{ */

  /** 
   * Merges two nodes.
   * All references to Node iNode1 are replaced by references to Node iNode0
   * The bar(s) between the two nodes is (are) collapsed and removed.
   * The second node iNode1 is removed from the graph.
   * Observer calls will be made each time a bar or a node is removed.
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
  HRESULT SplitBar (const unsigned int iBar, unsigned int& oNode, unsigned int& oBar);

  /**
   * Given a fan iterator at the beginning of a fan around a node, reverses the order of its bars.
   * This method is useful to flip the orientation of a bar graph.
   */
  HRESULT ReverseFan (const CATPolyBarGraphNodeFanIterator& iIterator);

  /**
   * Given a bar, returns the previous bar in the fan around the node.
   * If the input bar is not found or if there is no previous bar (open fan),
   * then the method returns 0.
   */
  unsigned int PreviousBarInFan (const unsigned int iNode, const unsigned int iBar) const;

  /**
   * Given a bar, returns the next bar in the fan around the node.
   * If the input bar is not found or if there is no next bar (open fan),
   * then the method returns 0.
   */
  unsigned int NextBarInFan (const unsigned int iNode, const unsigned int iBar) const;

  /**
   * Given a bar and one of its nodes, returns the other node.
   */
  inline unsigned int GetMate (unsigned int iBar, unsigned int iNode) const;

  /**
   * Returns <tt>TRUE</tt> if the node has adjacent bars and <tt>FALSE</tt> otherwise.
   */
  CATBoolean NodeHasAdjacentBar (const unsigned int iNode) const;

/** @} */


public:

/** @name Event Listener. 
    Event listener are used to update attributes (user-defined layers.)
    @{ */

  /**
   * Registers an observer (event listener) with the instance.
   * Observers are called in the following orders:
   * <ul>
   *   <li> Before an event, the observers are called in reverse order of registration;
   *        The last registered observer is called first.
   *   <li> After an event, the observers are called in their order of registration;
   *        The first registered observer is called first.
   * </ul>
   *
   * @param iObserver
   *   The observer that is registered with the instance.
   * @return 
   * <ul>
   *   <li> <tt>S_OK</tt> if the observer is successfully registered.
   *   <li> <tt>S_FALSE</tt> otherwise.
   * </ul>
   */
  HRESULT RegisterObserver (CATPolyBarGraphObserver& iObserver);

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
  HRESULT UnregisterObserver (CATPolyBarGraphObserver& iObserver);

/** @} */


private:

  //
  // Bars.
  //

  // Bar is defined as a pair of nodes.
  // Two integers are associated to each bar:
  //   (1) Index of first node.
  //   (2) Index of second node.
  CATBucketsOfInt _Bars;  

  //
  // Nodes.
  //
  CATPolyBarGraphNodeVector& _Nodes;

  // 
  // Other parameters. Recycling.
  //

  unsigned int _NbNodes; // Number of nodes.
  unsigned int _NbBars;  // Number of bars.

  unsigned int _FirstUndefinedNode; // Recycler of nodes.
  unsigned int _FirstUndefinedBar;  // Recycler of bars.

  CATPolyBarGraphObserver* _FirstObserver;  // Pointer to first observer.
  CATPolyBarGraphObserver* _LastObserver;   // Pointer to last observer.

private:

  unsigned int GetMaxNodeIndex () const;
  void PushUndefinedNode (unsigned int n);
  unsigned int PopUndefinedNode ();
  CATBoolean IsNodeWithinRangeValid (const unsigned int iNode) const;

  inline unsigned int GetMaxBarIndex () const;
  void PushUndefinedBar (unsigned int b);
  unsigned int PopUndefinedBar ();
  inline CATBoolean IsBarWithinRangeValid (const unsigned int iNode) const;

  HRESULT DoAddNode (unsigned int& oNode);
  HRESULT DoRemoveNode (const unsigned int iNode);

  HRESULT DoAddBar (const unsigned int iPreviousBar, const unsigned int iNode0, const unsigned int iNode1, const unsigned int iNextBar,
                    unsigned int& oBar);
  HRESULT DoRemoveBar (const unsigned int iBar);

private:

  // Private services for merging a pair of nodes.

  // Check if a bar is collapsable.
  CATBoolean IsBarCollapsable (const unsigned int b, const unsigned int n0, const unsigned int n1) const;

  // If a bar references n1, replaces this node by n0.
  void UpdateBar (const unsigned int b, const unsigned int n0, const unsigned int n1);

  // Increments k to the start of the next fan in the sequence and return the value.
  unsigned int ProceedToNextFan (const CATPolyBarGraphNode& N, unsigned int k) const;

  // Service for merging two nodes (case of an open fan.)
  HRESULT ScanBackward (const unsigned int iNode0, const unsigned int iNode1,
                        unsigned int i, unsigned int j,
                        unsigned int k[],
                        unsigned int kMin[],                                       
                        unsigned int* oBars, unsigned int& oNbBars);

  HRESULT RemoveCollapsableBars (const CATPolyBarGraphNode& N);

  inline unsigned int& Node0 (unsigned int b);
  inline unsigned int& Node1 (unsigned int b);

  unsigned int NewBar ();

  friend class CATPolyBarGraphNodeIterator;
  friend class CATPolyBarGraphBarIterator;
  friend class CATPolyBarGraphNodeBarIterator;
  friend class CATPolyBarGraphNodeNodeBarIterator;
  friend class CATPolyBarGraphNodeBarLoopIterator;
  friend class CATPolyBarGraphNodeFanIterator;
  friend class CATPolyBarGraphNodeAFanIterator;

};

inline unsigned int CATPolyBarGraph::GetNbNodes () const
{
  return _NbNodes;
}

inline unsigned int CATPolyBarGraph::GetNbBars () const
{
  return _NbBars;
}

inline unsigned int CATPolyBarGraph::Node0 (unsigned int b) const
{
  return (unsigned int) _Bars[2 * b - 1];
}

inline unsigned int CATPolyBarGraph::Node1 (unsigned int b) const
{
  return (unsigned int) _Bars[2 * b];
}

inline unsigned int& CATPolyBarGraph::Node0 (unsigned int b)
{
  return (unsigned int&) _Bars[2 * b - 1];
}

inline unsigned int& CATPolyBarGraph::Node1 (unsigned int b)
{
  return (unsigned int&) _Bars[2 * b];
}

inline unsigned int CATPolyBarGraph::GetMaxBarIndex () const
{
  return _Bars.GetMaxIndex () >> 1;
}

inline CATBoolean CATPolyBarGraph::IsBarValid (const unsigned int iBar) const
{
  return (0 < iBar && iBar <= GetMaxBarIndex ()) ? Node1 (iBar) != 0 : FALSE;
}

inline CATBoolean CATPolyBarGraph::IsBarWithinRangeValid (const unsigned int iBar) const
{
  return Node1 (iBar) != 0;
}

inline unsigned int CATPolyBarGraph::GetMate (const unsigned int b, const unsigned int n) const
{
  unsigned int n0 = Node0 (b);
  unsigned int n1 = Node1 (b);
  return (n == n0) ? n1 : (n == n1) ? n0 : 0;
}

#endif
