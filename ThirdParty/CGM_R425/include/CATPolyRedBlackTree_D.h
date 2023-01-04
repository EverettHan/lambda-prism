//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// Generic (macro-based) red-black tree.
//
// To specialize a red-black tree to a particular data types
// combination, declare and define a new specialization of the
// CATPolyRedBlackTree_D by invoking the dedicated macros.
//
// To declare a new specialization named `MapD' for a data type `D',
// instantiate the `CATPolyRedBlackTree_D' template in a dedicated
// header file as follows:
//
//      // MapD.h
//      #ifndef MapD_H
//      #define MapD_H
// 
//      #include "CATPolyRedBlackTree_D.h"
//
//      class ExportedByMyDLL Declare_CATPolyRedBlackTree_D(MapD, D);
//
//      #endif // !MapD_H
//
// Note that the macro invocation MUST be preceded by a `class' or a
// `struct' statement, and terminated by a `;'.
// 
// To define the specialization, instantiate the macro
// `Define_CATPolyRedBlackTree_D' in a dedicated implementation file:
//
//      // MapD.cpp
//      #include "MapD.h"
//
//      #define NONE
//      Define_CATPolyRedBlackTree_D (NONE, MapD, DataTypeName)
// 
// The `NONE' parameter specifies that the specialization is not nested
// in a class.
//
// For nesting a specialization, declare the specialization as follows:
//
//      // A.h
//      #ifndef A_H
//      #define A_H
// 
//      #include "CATPolyRedBlackTree_D.h"
//
//      class A
//      {
//      public:
//        struct Ab
//        {
//          class Declare_CATPolyRedBlackTree_D(MapD, D);
//        };
//      };
//
//      #endif // !A_H
//
// And define it:
//
//      // A.cpp
//      #include "A.h"
//
//      Define_CATPolyRedBlackTree_D(A::Ab::, MapD, D)
//
//=============================================================================
// 2008-09-19   NDO: Adapted from CATPolyRedBlackTree_K_D_H
//=============================================================================
#ifndef CATPolyRedBlackTree_D_H
#define CATPolyRedBlackTree_D_H

#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATPolyBuckets_T.h"

#include <utility>
#include <cstdint>
#include <algorithm>

template<class DataType>
struct CATPolyRedBlackTree_Node
{
  enum color_type { Red, Black } _Color;
  DataType _Data;
  CATPolyRedBlackTree_Node* _Parent;
  CATPolyRedBlackTree_Node* _Left;
  CATPolyRedBlackTree_Node* _Right;

  CATPolyRedBlackTree_Node* Min()
  {
    CATPolyRedBlackTree_Node* n = this;
    for (; n->_Left; n = n->_Left);
    return n;
  }

  CATPolyRedBlackTree_Node* Max()
  {
    CATPolyRedBlackTree_Node* n = this;
    for (; n->_Right; n = n->_Right);
    return n;
  }
};

template<class DataTypeName, class Less, class Allocator>
class CATPolyRedBlackTree : private Less, Allocator
{
public:
  typedef DataTypeName DataType;
  typedef CATPolyRedBlackTree_Node<DataType> Node;

public:
  class Iterator
  {
  public:
    Iterator(): _n(0) {}
    Iterator (Node *n): _n(n) {}

    DataType& GetData() const {return _n->_Data;}
    DataType& operator*() const {return _n->_Data;}
    DataType* operator->() const {return &_n->_Data;}
    Node* GetNode() const {return _n;}

    CATBoolean End() const {return _n == 0;}

    Iterator& operator++ ()
    {
      if (_n)
      {
        if (_n->_Right)
          _n = _n->_Right->Min();
        else
        {
          Node *p = _n->_Parent;
          while (p && _n == p->_Right)
          {
            _n = p;
            p = _n->_Parent;
          }
          _n = p;
        }
      }
      return *this;
   }

   Iterator& operator-- ()
    {
      if (_n)
      {
        if (_n->_Left)
          _n = _n->_Left->Max();
        else
        {
          Node *p = _n->_Parent;
          while (p && _n == p->_Left)
          {
            _n = p;
            p = _n->_Parent;
          }
          _n = p;
        }
      }
      return *this;
   }

   Iterator operator++ (int)
   {
     Iterator res(*this);
     ++(*this);
     return res;
   }

   Iterator operator-- (int)
   {
     Iterator res(*this);
     --(*this);
     return res;
   }

   bool operator==(Iterator iterator) const {return _n == iterator._n;}
   bool operator!=(Iterator iterator) const {return _n != iterator._n;}

   /* Comparison operators work if the red black tree has less than 2^64 nodes
    * which seems a rather reasonable hypothesis.
    */
   bool operator<(Iterator iterator) const
   {
     if (!_n)
       return false;
     if (!iterator._n)
       return true;

     std::uint64_t m1 = 0;
     std::uint64_t d1 = std::uint64_t(1) << 63;
     Node* n1 = _n;
     while (n1->_Parent)
     {
       d1 >>= 1;
       d1 |= std::uint64_t(1) << 63;
       m1 >>= 1;
       m1 |= std::uint64_t(n1->_Parent->_Right == n1) << 63;
       n1 = n1->_Parent;
     }

     std::uint64_t m2 = 0;
     std::uint64_t d2 = std::uint64_t(1) << 63;
     Node* n2 = iterator._n;
     while (n2->_Parent)
     {
       d2 >>= 1;
       d2 |= std::uint64_t(1) << 63;
       m2 >>= 1;
       m2 |= std::uint64_t(n2->_Parent->_Right == n2) << 63;
       n2 = n2->_Parent;
     }

     m1 &= d2;
     m2 &= d1;
     if (m1 != m2)
       return m1 < m2;
     else
       return d1 > d2;
   }

   bool operator<=(Iterator iterator) const { !(iterator < *this); }
   bool operator>(Iterator iterator) const { return iterator < *this; }
   bool operator>=(Iterator iterator) const { return iterator <= *this; }


  protected:
    Node *_n;
  };

public:
  CATPolyRedBlackTree() : _Size(0) {}
  CATPolyRedBlackTree(Less const &compare)
    : Less(compare), _Size(0) {}
  ~CATPolyRedBlackTree() {}

public:
  using Allocator::_Root;
  Iterator Begin() const { return Iterator(_Root ? _Root->Min() : 0); }
  Iterator End() const { return Iterator(); }
  Iterator Last() const { return Iterator(_Root ? _Root->Max() : 0); }

  Iterator begin() const { return Begin(); }
  Iterator end() const { return End(); }

public:
  /* Finds an element whose key is iData. Return end if none found. (Complexity: o(log N)) */
  Iterator Find (const DataType& iData) const;

  /* Return number of element. (Complexity: o(1)) */
  int Size() const { return _Size; }
  bool IsEmpty () const {return _Size == 0;}

  /* Insert iData in tree */
  HRESULT Insert (const DataType& iData, Iterator *opIterator = 0);

#ifndef _AIX_SOURCE
  template<bool CheckHint = true, bool CheckDuplicate = true>
#else
  template<bool CheckHint, bool CheckDuplicate>
#endif
  HRESULT Insert (Iterator iHint, const DataType& iData, Iterator *opIterator = 0);

  /* Insert iData using iIterator as hint */
  /* HRESULT Insert(Iterator &iHint, const DataType &iData) */

  /* Remove the element whose key is iData */
  HRESULT Remove (const DataType& iData);
  HRESULT Remove(Iterator iterator);

  /* Return lower bound node of iData, ie the node whose _Data is the */
  /* bigger such that _Data <= iData (Complexity: o(log N)) */
  template<class K>
  Iterator LowerBound (const K& iData) const;

  /* Return range ]first, second]such that first->_Data < iData <= second->_Data (Complexity: o(log N)) 
   * If no such first or second exist, first or second will be null iterator.
   */
  template<class K>
  std::pair<Iterator, Iterator> LowerRange(const K& iData) const;

  /* Swap two nodes in tree. DO NO USE UNLESS YOU HAVE A VERY GOOD REASON.
   * Tree node ordering will be invalidated.
   */
  void Swap(Iterator iterator1, Iterator iterator2);

private:
  friend class Iterator;


  /* Insert iData in tree (Complexity: o(log N)) */
  /* Return S_OK for new node, S_FALSE for existing node and E_FAIL otherwise. */
  HRESULT BinaryInsert (const DataType& iData, Node*& X);
  void FinalizeInsert(HRESULT Status, Node *x, Iterator *opIterator);

  template<bool CheckDuplicate>
  HRESULT InsertHint(std::pair<Iterator, Iterator> range, const DataType &iData, Node*& oNode);

  void PushFreeNode(Node& N);
  Node* PopFreeNode();

private:
  /* Rotations */
  HRESULT LeftRotate (Node* x);
  HRESULT RightRotate (Node* x);

private:
  HRESULT EraseFixup(Node* x);

private:
  int _Size;

private:
  CATPolyRedBlackTree(CATPolyRedBlackTree const&);
  CATPolyRedBlackTree& operator=(CATPolyRedBlackTree const&);
};

template<class T>
struct CATPolyRedBlackTree_Less
{
  bool operator()(T const& iT1, T const& iT2) const
  {
    return iT1 < iT2;
  }
};

/* Node recycling */
template<class NodeBuckets>
class CATPolyRedBlackTree_NodeBuckets_Allocator
{
public:
  typedef typename NodeBuckets::ValueType Node;

  CATPolyRedBlackTree_NodeBuckets_Allocator() : _FirstFreeNode(0), _Root(0) {}

  void PushFreeNode(Node& N);
  Node* PopFreeNode();

private:
  NodeBuckets _Nodes;
  Node* _FirstFreeNode;
protected:
  Node* _Root;
};

template<class Data>
class CATPolyRedBlackTree_Default_Allocator
{
public:
  typedef CATPolyRedBlackTree_Node<Data> Node;

  CATPolyRedBlackTree_Default_Allocator() : _Root(0) {}

  ~CATPolyRedBlackTree_Default_Allocator()
  {
    Node* n = _Root;
    while (n)
    {
      if (n->_Left)
      {
        Node* left = n->_Left;
        n->_Left = 0;
        n = left;
        continue;
      }
      if (n->_Right)
      {
        Node* right = n->_Right;
        n->_Right = 0;
        n = right;
        continue;
      }
      Node* parent = n->_Parent;
      delete n;
      n = parent;
    }
  }

  void PushFreeNode(Node& N)
  {
    delete &N;
  }

  Node* PopFreeNode()
  {
    return new Node();
  }

protected:
  Node *_Root;

private:
  CATPolyRedBlackTree_Default_Allocator(CATPolyRedBlackTree_Default_Allocator const&);
  CATPolyRedBlackTree_Default_Allocator& operator=(CATPolyRedBlackTree_Default_Allocator const&);
};

#define Specialize_CATPolyRedBlackTree_D(TypeName, DataTypeName)                                                                                                           \
  Specialize_CATPolyBuckets_T(TypeName##NodeBuckets, CATPolyRedBlackTree_Node<DataTypeName>);                                                                              \
  class TypeName : public CATPolyRedBlackTree<DataTypeName, CATPolyRedBlackTree_Less<DataTypeName>, CATPolyRedBlackTree_NodeBuckets_Allocator<TypeName##NodeBuckets> > {}

#define Implement_Specialized_CATPolyRedBlackTree_D(TypeName) Implement_Specialized_CATPolyBuckets_T(TypeName##NodeBuckets);

// ----------------------------------------------------------------------------

template<class DataTypeName, class Less, class Allocator>
typename CATPolyRedBlackTree<DataTypeName, Less, Allocator>::Iterator CATPolyRedBlackTree<DataTypeName, Less, Allocator>::Find (const DataType &iData) const
{
  Node *n = _Root;
  while (n)
    if ((*this)(iData, n->_Data))
      n = n->_Left;
    else if ((*this)(n->_Data, iData))
      n = n->_Right;
    else
      break;
  return Iterator (n);
}

template<class DataTypeName, class Less, class Allocator>
HRESULT CATPolyRedBlackTree<DataTypeName, Less, Allocator>::Insert (const DataType &iData, Iterator *opIterator)
{
  Node* x = 0;
  HRESULT Status = BinaryInsert (iData, x);
  FinalizeInsert(Status, x, opIterator);
  return Status;
}

template<class DataTypeName, class Less, class Allocator>
template<bool CheckHint, bool CheckDuplicate>
HRESULT CATPolyRedBlackTree<DataTypeName, Less, Allocator>::Insert (Iterator iHint, const DataType &iData, Iterator *opIterator)
{
#ifndef _AIX_SOURCE
  if constexpr (CheckHint)
#else
  if (CheckHint)
#endif
  {
    Node* hNode = iHint.GetNode();
    if (hNode && (*this)(hNode->_Data, iData))
      return Insert(iData, opIterator);
  }

  auto prev = iHint;
  if (!prev.End())
    --prev;
  else
    prev = Last();
  
#ifndef _AIX_SOURCE
  if constexpr (CheckHint)
#else
  if (CheckHint)
#endif
  {
    Node* pNode = prev.GetNode();
    if (pNode && !(*this)(pNode->_Data, iData))
      return Insert(iData, opIterator);    
  }

  Node* x = 0;
  HRESULT Status = InsertHint<CheckDuplicate>(std::pair<Iterator, Iterator>{prev, iHint}, iData, x);
  FinalizeInsert (Status, x, opIterator);
  return Status;
}

template<class DataTypeName, class Less, class Allocator>
HRESULT CATPolyRedBlackTree<DataTypeName, Less, Allocator>::BinaryInsert(const DataType &iData, Node*& oNode)
{
  std::pair<Iterator, Iterator> range = LowerRange(iData);
  return InsertHint<true>(range, iData, oNode);
}

template<class DataTypeName, class Less, class Allocator>
template<bool CheckDuplicate>
HRESULT CATPolyRedBlackTree<DataTypeName, Less, Allocator>::InsertHint(std::pair<Iterator, Iterator> range, const DataType &iData, Node*& oNode)
{
  Node* B = range.second.GetNode();
#ifndef _AIX_SOURCE
  if constexpr (CheckDuplicate)
#else
  if (CheckDuplicate)
#endif
  {
    if (B && !(*this)(iData, B->_Data))
    {
      oNode = B;
      return S_FALSE;
    }
  }

  Node *N = PopFreeNode();
  if (!N)
    return E_FAIL;

  N->_Data = iData;
  N->_Color = Node::Red;
  N->_Left = 0;
  N->_Right = 0;

  if (!_Root)
  {
    N->_Parent = 0;
    _Root = N;
  }
  else if (B && !B->_Left)
  {
    N->_Parent = B;
    B->_Left = N;
  }
  else
  {
    B = range.first.GetNode();
    N->_Parent = B;
    B->_Right = N;        
  }

  oNode = N;
  return S_OK;
}

template<class DataTypeName, class Less, class Allocator>
void CATPolyRedBlackTree<DataTypeName, Less, Allocator>::FinalizeInsert(HRESULT Status, Node *x, Iterator *opIterator)
{
  if(opIterator) *opIterator = Iterator(x);
  if (x && Status == S_OK)
  {
    while (x->_Parent && x->_Parent->_Color == Node::Red &&
           x->_Parent->_Parent)
    {
      Node* y = x->_Parent->_Parent;

      if (x->_Parent == y->_Left)
      {
        y = y->_Right;

        if (y && y->_Color == Node::Red)
        {
          x->_Parent->_Color = Node::Black;
          y->_Color = Node::Black;
          x->_Parent->_Parent->_Color = Node::Red;
          x = x->_Parent->_Parent;
        }
        else
        {
          if (x == x->_Parent->_Right)
          {
            x = x->_Parent;
            LeftRotate(x);
          }
          x->_Parent->_Color = Node::Black;
          x->_Parent->_Parent->_Color = Node::Red;
          RightRotate(x->_Parent->_Parent);
          break;
        }
      }
      else
      {
        y = y->_Left;

        if (y && y->_Color == Node::Red)
        {
          x->_Parent->_Color = Node::Black;
          y->_Color = Node::Black;
          x->_Parent->_Parent->_Color = Node::Red;
          x = x->_Parent->_Parent;
        }
        else
        {
          if (x == x->_Parent->_Left)
          {
            x = x->_Parent;
            RightRotate(x);
          }
          x->_Parent->_Color = Node::Black;
          x->_Parent->_Parent->_Color = Node::Red;
          LeftRotate(x->_Parent->_Parent);
          break;
        }
      }
    }
    _Root->_Color = Node::Black;
  }
}

template<class DataTypeName, class Less, class Allocator>
HRESULT CATPolyRedBlackTree<DataTypeName, Less, Allocator>::Remove (const DataType &iData)
{
  Iterator I (Find(iData));
  return Remove(I);
}

template<class DataTypeName, class Less, class Allocator>
HRESULT CATPolyRedBlackTree<DataTypeName, Less, Allocator>::Remove (Iterator I)
{
  HRESULT Status = S_FALSE;

  Node *Z = I.GetNode();
  if (Z)
  {
    if (Z->_Left && Z->_Right)
    {
      Node* Y = Z->_Right->Min();
      Swap(Iterator(Y), Iterator(Z)); // Swaps the roles of the two nodes for stability of the iterators.  (Removal of Z; not Y!).
    }

    /* Node Z has now at most one non-leaf child. */
    /* This is the node to be removed. */
    Node *X = 0;
    if (Z->_Left)
      X = Z->_Left;
    else
      X = Z->_Right;

    if (X)
    {
      /* Replace the node by its child. Put X in place of Z */
      X->_Parent = Z->_Parent;
      if (!Z->_Parent)
        _Root = X;
      else if (Z == Z->_Parent->_Left)
        Z->_Parent->_Left = X;
      else
        Z->_Parent->_Right = X;
    }
    else
    {
      /* Phantom leaf that will be deleted afterwards. */
      /* (Leaves are represented as null nodes.) */
      X = Z;
    }

    if (X) /* Useless (mkcs). */
    {
      if (Z->_Color == Node::Black)
        EraseFixup (X);

      /* Remove reference to the leaf node. */
      /* It must be black and not have any child. */
      if (X == Z)
      {
        if (X->_Parent)
        {
          if (X->_Parent->_Left == X)
            X->_Parent->_Left = 0;
          else
            X->_Parent->_Right = 0;
        }
        else
          _Root = 0;
      }

      /* Get rid of Z. */
      Status = S_OK;
      PushFreeNode (*Z);
    }
  }

  return Status;
}

template<class DataTypeName, class Less, class Allocator>
HRESULT CATPolyRedBlackTree<DataTypeName, Less, Allocator>::EraseFixup (Node *X)
{
  while (X != _Root && X->_Color == Node::Black)
    if (X == X->_Parent->_Left)
    {
      Node *W = X->_Parent->_Right; /* Sibling of X. */
      if (!W) return E_FAIL; /* Cannot fail */

      if (W->_Color == Node::Red)
      {
        W->_Color = Node::Black;
        X->_Parent->_Color = Node::Red;
        LeftRotate(X->_Parent);
        W = X->_Parent->_Right;
      }

      if ((!W->_Left || W->_Left->_Color == Node::Black) &&
          (!W->_Right || W->_Right->_Color == Node::Black))
      {
        W->_Color = Node::Red;
        X = X->_Parent;
      }
      else
      {
        if (!W->_Right || W->_Right->_Color == Node::Black)
        {
          W->_Left->_Color = Node::Black;
          W->_Color = Node::Red;
          RightRotate(W);
          W = X->_Parent->_Right;
        }

        W->_Color = X->_Parent->_Color;
        X->_Parent->_Color = Node::Black;
        W->_Right->_Color = Node::Black;
        LeftRotate(X->_Parent);
        X = _Root;
      }
    }
    else /* X == X->_Parent->_Left */
    {
      Node *W = X->_Parent->_Left; /* Sibling of X. */
      if (!W) return E_FAIL; /* Cannot fail */

      if (W->_Color == Node::Red)
      {
        W->_Color = Node::Black;
        X->_Parent->_Color = Node::Red;
        RightRotate(X->_Parent);
        W = X->_Parent->_Left;
      }

      if ((!W->_Left || W->_Left->_Color == Node::Black) &&
          (!W->_Right || W->_Right->_Color == Node::Black))
      {
        W->_Color = Node::Red;
        X = X->_Parent;
      }
      else
      {
        if (!W->_Left || W->_Left->_Color == Node::Black)
        {
          W->_Right->_Color = Node::Black;
          W->_Color = Node::Red;
          LeftRotate(W);
          W = X->_Parent->_Left;
        }

        W->_Color = X->_Parent->_Color;
        X->_Parent->_Color = Node::Black;
        W->_Left->_Color = Node::Black;
        RightRotate(X->_Parent);
        X = _Root;
      }
    }

  if (!X) return E_FAIL; /* Should not fail */

  X->_Color = Node::Black;
  return S_OK;
}

template<class DataTypeName, class Less, class Allocator>
HRESULT CATPolyRedBlackTree<DataTypeName, Less, Allocator>::LeftRotate (Node *x)
{
  if (!x) return E_FAIL;

  Node *y = x->_Right;

  x->_Right = y->_Left;
  if (y->_Left)
    y->_Left->_Parent = x;

  y->_Parent = x->_Parent;
  if (!x->_Parent)
    _Root = y;
  else if (x == x->_Parent->_Left)
    x->_Parent->_Left = y;
  else
    x->_Parent->_Right = y;

  y->_Left = x;
  x->_Parent = y;

  return S_OK;
}

template<class DataTypeName, class Less, class Allocator>
HRESULT CATPolyRedBlackTree<DataTypeName, Less, Allocator>::RightRotate (Node *x)
{
  if (!x) return E_FAIL;

  Node *y = x->_Left;

  x->_Left = y->_Right;
  if (y->_Right)
    y->_Right->_Parent = x;

  y->_Parent = x->_Parent;
  if (!x->_Parent)
    _Root = y;
  else if (x == x->_Parent->_Right)
    x->_Parent->_Right = y;
  else
    x->_Parent->_Left = y;

  y->_Right = x;
  x->_Parent = y;

  return S_OK;
}

template<class DataTypeName, class Less, class Allocator>
template<class K>
typename CATPolyRedBlackTree<DataTypeName, Less, Allocator>::Iterator CATPolyRedBlackTree<DataTypeName, Less, Allocator>::LowerBound (const K &iData) const
{
  return LowerRange(iData).second;
}

template<class DataTypeName, class Less, class Allocator>
template<class K>
std::pair<typename CATPolyRedBlackTree<DataTypeName, Less, Allocator>::Iterator, typename CATPolyRedBlackTree<DataTypeName, Less, Allocator>::Iterator>
CATPolyRedBlackTree<DataTypeName, Less, Allocator>::LowerRange(const K& iData) const
{  
  std::pair<Iterator, Iterator> res;
  Node* N = _Root;
  while (N)
  {
    if (!(*this)(N->_Data, iData))
    {
      res.second = Iterator(N);
      N = N->_Left;
    }
    else
    {
      res.first = Iterator(N);
      N = N->_Right;
    }
  }

  return res;
}

template<class DataTypeName, class Less, class Allocator>
void CATPolyRedBlackTree<DataTypeName, Less, Allocator>::Swap(Iterator iterator1, Iterator iterator2)
{
  Node* node1 = iterator1.GetNode();
  Node* node2 = iterator2.GetNode();  
  if (node1 == node2)
    return;

  std::swap(node1->_Color, node2->_Color);
 
  if (node1->_Parent == node2)
  {
    if (node2->_Left == node1)
    {
      node2->_Left = node1->_Left;
      node1->_Left = node2;
      std::swap(node1->_Right, node2->_Right);
    }
    else
    {
      node2->_Right = node1->_Right;
      node1->_Right = node2;
      std::swap(node1->_Left, node2->_Left);
    }

    if (_Root == node2)
    {
      _Root = node1;
      node1->_Parent = 0;
      node2->_Parent = node1;
    }
    else
    {
      if (node2->_Parent->_Left == node2)      
        node2->_Parent->_Left = node1;
      else      
        node2->_Parent->_Right = node1;
      
      node1->_Parent = node2->_Parent;
      node2->_Parent = node1;
    }
  }
  else if (node2->_Parent == node1)
  {
    if (node1->_Left == node2)
    {
      node1->_Left = node2->_Left;
      node2->_Left = node1;
      std::swap(node1->_Right, node2->_Right);
    }
    else
    {
      node1->_Right = node2->_Right;
      node2->_Right = node1;
      std::swap(node1->_Left, node2->_Left);
    }

    if (_Root == node1)
    {
      _Root = node2;
      node2->_Parent = 0;
      node1->_Parent = node2;
    }
    else
    {
      if (node1->_Parent->_Left == node1)
        node1->_Parent->_Left = node2;
      else
        node1->_Parent->_Right = node2;

      node2->_Parent = node1->_Parent;
      node1->_Parent = node2;
    }
  }
  else
  {
    Node** parent1;
    if (!node1->_Parent)
      parent1 = &_Root;
    else
      parent1 = node1->_Parent->_Left == node1 ? &node1->_Parent->_Left : &node1->_Parent->_Right;

    Node** parent2;
    if (!node2->_Parent)
      parent2 = &_Root;
    else
      parent2 = node2->_Parent->_Left == node2 ? &node2->_Parent->_Left : &node2->_Parent->_Right;

    std::swap(node1->_Parent, node2->_Parent);
    std::swap(*parent1, *parent2);
    
    std::swap(node1->_Left, node2->_Left);
    std::swap(node1->_Right, node2->_Right);
  }

  if (node1->_Left)
    node1->_Left->_Parent = node1;
  if (node2->_Left)
    node2->_Left->_Parent = node2;

  if (node1->_Right)
    node1->_Right->_Parent = node1;
  if (node2->_Right)
    node2->_Right->_Parent = node2;
}

template<class DataTypeName, class Less, class Allocator>
void CATPolyRedBlackTree<DataTypeName, Less, Allocator>::PushFreeNode(Node& N)
{
  Allocator::PushFreeNode(N);
  --_Size;
}

template<class DataTypeName, class Less, class Allocator>
typename CATPolyRedBlackTree<DataTypeName, Less, Allocator>::Node* CATPolyRedBlackTree<DataTypeName, Less, Allocator>::PopFreeNode()
{
  Node* N = Allocator::PopFreeNode();
  if (N)
    ++_Size;
  return N;
}

template<class Buckets>
void CATPolyRedBlackTree_NodeBuckets_Allocator<Buckets>::PushFreeNode (Node &N)
{
  N._Left = _FirstFreeNode;
  _FirstFreeNode = & N;
}

template<class Buckets>
typename CATPolyRedBlackTree_NodeBuckets_Allocator<Buckets>::Node* CATPolyRedBlackTree_NodeBuckets_Allocator<Buckets>::PopFreeNode ()
{
  Node *N = _FirstFreeNode;
  if (_FirstFreeNode)
    _FirstFreeNode = _FirstFreeNode->_Left;
  else
  {
    unsigned int n = _Nodes.PushBack(Node());
    if (n)
      N = & _Nodes[n];
  }
  return N;
}

#endif // !CATPolyRedBlackTree_D_H
