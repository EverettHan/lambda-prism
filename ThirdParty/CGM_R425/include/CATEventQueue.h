// COPYRIGHT DASSAULT SYSTEMES 2006-2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATEventQueue.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// September 2006 Creation: NDO
//===================================================================
#ifndef CATEventQueue_h
#define CATEventQueue_h

#include "PolyMathContainers.h"
#include "CATCompareElements.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATPolyBuckets_T.h"


/*
Implementation of an event queue as a balanced binary tree.
Insertion, deletion and lookup of elements in the queue is o(Log N) time where N is
the number of elements in the queue.  
*/
class ExportedByPolyMathContainers CATEventQueue
{

private:

  // For Red-Black Balanced Binary Tree (Implementation).
  struct NodePrivate
  {
    enum color_type { Red, Black } _Color;
    const void* _Element;
    NodePrivate* _Parent;
    NodePrivate* _Left;
    NodePrivate* _Right;

    inline NodePrivate* Min ()
    {
      NodePrivate* n = this;
      for (; n->_Left; n = n->_Left);
      return n;
    }

    inline NodePrivate* Max ()
    {
      NodePrivate* n = this;
      for (; n->_Right; n = n->_Right);
      return n;
    }

    inline NodePrivate* Next ()
    {
      NodePrivate* next = this;
      if (next->_Right)
        next = next->_Right->Min ();
      else
      {
        NodePrivate* p = next->_Parent;
        while (p && next == p->_Right)
        {
          next = p;
          p = next->_Parent;
        }
        next = p;
      }
      return next;
    }

    inline NodePrivate* Prev ()
    {
      NodePrivate* prev = this;
      if (prev->_Left)
        prev = prev->_Left->Max ();
      else
      {
        NodePrivate* p = prev->_Parent;
        while (p && prev == p->_Left)
        {
          prev = p;
          p = prev->_Parent;
        }
        prev = p;
      }
      return prev;
    }

  };

public:

  typedef NodePrivate Node;

  /*
   * Iterator class.
   * Iterate through the elements of the queue.
   * An iterator instance is stable during insertion and deletion of elements in the queue.
   * (Unless the element adressed by the iterator is removed from the queue.)
   */
  class ExportedByPolyMathContainers Iterator
  {
  public:

    inline Iterator () : _Node (0) {}
    inline Iterator (Node* n) : _Node (n) {}

    inline const void* GetElement () const {return _Node->_Element;}
    inline Node* GetNode () const {return _Node;}

    inline CATBoolean End () const {return _Node == 0;}

    inline Iterator& operator++ ()
    {
      if (_Node)
        _Node = _Node->Next ();
      return* this;
    }

    inline Iterator& operator-- ()
    {
      if (_Node)
        _Node = _Node->Prev ();
      return* this;
    }

    inline int operator == (const Iterator& iRHS) const
    {
      return _Node == iRHS._Node;
    }

  protected:
    Node* _Node;
  };

public:

  /*
   * The input argument is a function that is used to compare two elements from the queue.
   * It must be antisymmetric, transitive and equal to 0 if two elements are equal (see CATCompareElements.)
  */
  CATEventQueue (const CATCompareElements& iCompare);  
  ~CATEventQueue ();

  /* 
   * Insertion of an element in the queue.
   * Complexity is o(Log N) where N is the number of elements in the queue.
   * The optional argument is an iterator that will point to the element after its insertion.
   * The method returns S_OK if the element is inserted in the queue.
   * If the element is already in the queue, then the methode returns S_FALSE and sets the
   * optional iterator to the position of the element in the queue.
   * @param iElement
   *   The element to be inserted in the queue.
   * @param oPosition
   *   An optional iterator argument that provides the position of the inserted element in the queue.
   * @return 
   *   S_OK when an element is inserted.
   *   S_FALSE when the element is found in the queue.
   *   E_FAIL when an error occurs.
   */
  HRESULT Insert (const void* iElement, Iterator* oPosition = 0);

  // Insert iElement using an iterator that address an element as a hint to speed up insertion.
  // Update the iterator with the position of the element upon insertion.
  //HRESULT Insert (Iterator& iHint, const void* iElement);

  // Lookup an element in the queue.  If the element is in the queue, it returns TRUE.  
  // In option, an argument gives the position of the element in the queue or 
  // the position where this element can be inserted in the queue.
  inline CATBoolean Locate (const void* iElement, Iterator* oPosition = 0) const;

  // Finds an element in the queue.  Return End if none are found. Complexity is o(log N).
  Iterator Find (const void* iElement) const;

  /*
   * Remove an element from the queue.
   * @param iElement
   *   The element to remove from the queue.
   * @return
   *   S_OK when the element if removed from the queue.
   *   S_FALSE when the element is not found in the queue.
   *   E_FAIL when an error occurs.
   */
  inline HRESULT Remove (const void* iElement);

  /*
   * Remove the element from the queue at the given position.
   * @param iPosition
   *   The position of the element to remove.
   * @return
   *   S_OK when the element if removed from the queue.
   *   S_FALSE when the element is not found in the queue (Iterator at the end for instance.)
   *   E_FAIL when an error occurs.
   */
  HRESULT Remove (const Iterator iPosition);

  // Erase all of the elements.
  HRESULT Clear (CATBoolean iKeepAllocatedMemory = 0);

  // Iterators on elements of the queue.

  inline Iterator First () const {return Iterator (_Root ? _Root->Min () : 0);} // Position of first element in the queue.
  inline Iterator Last () const {return Iterator (_Root ? _Root->Max () : 0);}  // Position of last element in the queue.
  inline Iterator Next (Iterator iPosition) const;     // Position of next element in the queue.
  inline Iterator Prev (Iterator iPosition) const;     // Position of previous element in the queue.

  inline const void* Get (const Iterator iPos) const;  // Returns the element at the current position.

  // Returns the number of elements in the queue.  Complexity is o(1).
  inline int Size (void) const;

protected:

  /*
   * Virtual function that calls the comparaison function provided in the constructor.
   * The comparaison function must be symmetric and return 0 if the two elements are equal.
   * This method can be overridden in a derived class for customization.
   * Returns
   *   +1 if p1 > p2
   *    0 if p1 = p2
   *   -1 if p1 < p2
  */
  inline int Compare (const void* p1, const void* p2) const;

private:

  class Specialize_CATPolyBuckets_T (NodeBuckets, Node);

private:

  const CATCompareElements& _Compare;  // Fonction that is used to compare two elements from the queue.

  NodeBuckets _Nodes;         // Buckets of nodes.
  Node* _Root;                // The root of the balanced binary tree.

  Node* _FirstFreeNode;       // For recycling nodes.
  int _Size;                  // The number of elements in the tree.

  Node _LeafNode;             // Sentinel node playing the role of a leaf.  The color of this node is black.

private:

  friend class Iterator;

  // Return lowest bound node from the tree of iElement. 
  // The lowest bound node is the lowest node in the tree to which iElement can be compared
  // and inserted left or right below this element if it is distinct.
  // This method returns the position of the iElement w.r.t. the node returned: Compare (iElement, Node Returned).
  // The complexity of this step is o(log N)
  Node* LowerBound (const void* iElement, int& cmp) const;

  // Insert iElement in the tree.  Complexity is o(log N).
  // The parameter oElementIsInTree is set to TRUE if the element is already in the tree.
  // The method returns the node associated to the element.
  Node* BinaryInsert (const void* iElement, CATBoolean& oElementIsInTree);

  // Find the minimum element in the right subtree of X.
  // This method assumes that X has a right child.
  Node* RightTreeSuccessor (Node* X);

  // Swaps the roles of two nodes.
  void Swap (Node* x, Node* y);

  HRESULT EraseFixup (Node* X);

private:

  HRESULT LeftRotate (Node* x);
  HRESULT RightRotate (Node* x);

private:

  // Node recycling.
  void PushFreeNode (Node& N);
  Node* PopFreeNode ();

};

inline int CATEventQueue::Compare (const void* p1, const void* p2) const
{
  return _Compare.Compare (p1, p2);
}

inline CATEventQueue::Iterator CATEventQueue::Next (Iterator iPosition) const
{
  Node* n = iPosition.GetNode ();
  return Iterator (n ? n->Next () : 0);
}

inline CATEventQueue::Iterator CATEventQueue::Prev (Iterator iPosition) const
{
  Node* n = iPosition.GetNode ();
  return Iterator (n ? n->Prev () : 0);
}

inline CATBoolean CATEventQueue::Locate (const void* iElement, Iterator* oPosition) const
{
  Iterator I (Find (iElement));
  if (oPosition)
    *oPosition = I;
  return I.End () ? FALSE : TRUE;
}

inline HRESULT CATEventQueue::Remove (const void* iElement)
{
  Iterator I (Find (iElement));
  return Remove (I);
}


inline const void* CATEventQueue::Get (const Iterator iPosition) const
{
  return iPosition.End () ? 0 : iPosition.GetElement ();
}


inline int CATEventQueue::Size () const
{
  return _Size;
}

#endif
