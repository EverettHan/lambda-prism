//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Generic (macro-based) red-black tree.
//
// To specialize a red-black tree to a particular key and data types
// combination, declare and define a new specialization of the
// CATPolyRedBlackTree_K_V by invoking the dedicated macros.
//
// To declare a new specialization named `MapKV' for a key type `K' and a data
// type `D', instantiate the `CATPolyRedBlackTree_K_V' template in a dedicated
// header file as follows:
//
//      // MapKD.h
//      #ifndef MapKD_H
//      #define MapKD_H
// 
//      #include "CATPolyRedBlackTree_K_D.h"
//
//      class ExportedByMyDLL Declare_CATPolyRedBlackTree_K_D(MapKD, K, D);
//
//      #endif // !MapKD_H
//
// Observe that the macro invocation SHALL be preceded by a `class' or a
// `struct' statement, and terminated by a `;'.
// 
// To define the specialization, instantiate the macro
// `Define_CATPolyRedBlackTree_K_D' in a dedicated implementation file:
//
//      // MapKD.cpp
//      #include "MapKD.h"
//
//      #define NONE
//      Define_CATPolyRedBlackTree_K_D(NONE, MapKD, KeyTypename, DataTypename)
// 
// The tricky `NONE' parameter specifies that the specialization is not nested
// in a class.
//
// For nesting a specialization, declare the specialization as follows:
//
//      // A.h
//      #ifndef A_H
//      #define A_H
// 
//      #include "CATPolyRedBlackTree_K_D.h"
//
//      class A
//      {
//      public:
//        struct Ab
//        {
//          class Declare_CATPolyRedBlackTree_K_D(MapKD, K, D);
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
//      Define_CATPolyRedBlackTree_K_D(A::Ab::, MapKD, K, D)
//
//=============================================================================
// 2007-01-18   BPG: New
//=============================================================================
#ifndef CATPolyRedBlackTree_K_D_H
#define CATPolyRedBlackTree_K_D_H

#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATPolyBuckets_T.h"

// Red-Black Tree of K to D

#define Specialize_CATPolyRedBlackTree_K_D(Typename, KeyTypename, DataTypename) \
Typename                                                                \
{                                                                       \
public:                                                                 \
  typedef KeyTypename KeyType;                                          \
  typedef DataTypename DataType;                                        \
                                                                        \
public: /* Handle poor compilers */                                     \
  struct Node                                                           \
  {                                                                     \
    enum color_type { Red, Black } _Color;                              \
    KeyType _Key;                                                       \
    DataType _Data;                                                     \
    Node *_Parent;                                                      \
    Node *_Left;                                                        \
    Node *_Right;                                                       \
    /* */                                                               \
    inline Node *Min()                                                  \
    {                                                                   \
      Node *n = this;                                                   \
      for (; n->_Left; n = n->_Left);                                   \
      return n;                                                         \
    }                                                                   \
  };                                                                    \
                                                                        \
public:                                                                 \
  class Iterator                                                        \
  {                                                                     \
  public:                                                               \
    inline Iterator(): _n(0) {}                                         \
    inline Iterator(Node *n): _n(n) {}                                  \
                                                                        \
    inline KeyType &GetKey() const { return _n->_Key; }                 \
    inline DataType &GetData() const { return _n->_Data; }              \
    inline Node *GetNode() const { return _n; }                         \
                                                                        \
    inline CATBoolean End() const { return _n == 0; }                   \
                                                                        \
    inline Iterator& operator++()                                       \
    {                                                                   \
      if (_n)                                                           \
      {                                                                 \
        if (_n->_Right)                                                 \
          _n = _n->_Right->Min();                                       \
        else                                                            \
        {                                                               \
          Node *p = _n->_Parent;                                        \
          while (p && _n == p->_Right)                                  \
          {                                                             \
            _n = p;                                                     \
            p = _n->_Parent;                                            \
          }                                                             \
          _n = p;                                                       \
        }                                                               \
      }                                                                 \
      return *this;                                                     \
   }                                                                    \
                                                                        \
  protected:                                                            \
    Node *_n;                                                           \
  };                                                                    \
                                                                        \
public:                                                                 \
  inline Typename(): _Root(0), _FirstFreeNode(0), _Size(0) {}           \
  inline ~Typename() {}                                                 \
                                                                        \
public:                                                                 \
  inline Iterator Begin() const { return Iterator(_Root ? _Root->Min() : 0); } \
                                                                        \
public:                                                                 \
  /* Erase all of the elements. */                                      \
  HRESULT Clear(CATBoolean iKeepAllocatedMemory = 0);                   \
                                                                        \
  /* Finds an element whose key is iKey. Return end if none found. (Complexity: o(log N)) */ \
  Iterator Find(const KeyType &iKey) const;                             \
                                                                        \
  /* Return number of element. (Complexity: o(1)) */                    \
  inline int Size() const { return _Size; }                             \
                                                                        \
  /* Associate iData to iKey in tree */                                 \
  HRESULT Insert(const KeyType &iKey, const DataType &iData);           \
                                                                        \
  /* Associate iData to iKey using iIterator as hint */                 \
  /* HRESULT Insert(Iterator &iHint, const KeyType &iKey, const DataType &iData, ) */ \
                                                                        \
  /* Erase the element whose key is iKey */                             \
  HRESULT Erase(const KeyType &iKey);                                   \
                                                                        \
private:                                                                \
  friend class Iterator;                                                \
                                                                        \
  /* Return lower bound node of iKey, ie the node whose _Key is the */  \
  /* bigger such that _Key <= iKey (Complexity: o(log N)) */            \
  Node *LowerBound(const KeyType &iKey) const;                          \
                                                                        \
  /* Insert iKey in tree (Complexity: o(log N)) */                      \
  /* Return S_OK for new node, S_FALSE for existing node with same data and E_FAIL otherwise. */ \
  HRESULT BinaryInsert(const KeyType &iKey, const DataType &iData, Node*& X); \
                                                                        \
  /* Rotations */                                                       \
private:                                                                \
  HRESULT LeftRotate(Node *x);                                          \
  HRESULT RightRotate(Node *x);                                         \
                                                                        \
private:                                                                \
  Node *RightTreeSuccessor(Node *X);                                    \
  HRESULT EraseFixup(Node *X);                                          \
                                                                        \
  /* Node recycling */                                                  \
private:                                                                \
  void PushFreeNode(Node &N);                                           \
  Node *PopFreeNode();                                                  \
                                                                        \
public: /* Poor compilers do not support class nesting */               \
  class Specialize_CATPolyBuckets_T(NodeBuckets, Node);                 \
private:                                                                \
  NodeBuckets _Nodes;                                                   \
  Node *_Root;                                                          \
                                                                        \
  Node *_FirstFreeNode;                                                 \
  int _Size;                                                            \
}

// ----------------------------------------------------------------------------

#define Implement_Specialized_CATPolyRedBlackTree_K_D(Typename)         \
Implement_Specialized_CATPolyBuckets_T(Typename::NodeBuckets);          \
                                                                        \
Typename::Iterator                                                      \
Typename::Find(const Typename::KeyType &iKey) const                     \
{                                                                       \
  Node *n = _Root;                                                      \
  while (n)                                                             \
    if (iKey < n->_Key)                                                 \
      n = n->_Left;                                                     \
    else if (n->_Key < iKey)                                            \
      n = n->_Right;                                                    \
    else                                                                \
      break;                                                            \
  return Iterator(n);                                                   \
}                                                                       \
                                                                        \
HRESULT                                                                 \
Typename::Insert(const Typename::KeyType &iKey, const Typename::DataType &iData) \
{                                                                       \
  Node* x = 0;                                                          \
  HRESULT Status = BinaryInsert (iKey, iData, x);                       \
  if (x && Status == S_OK)                                              \
  {                                                                     \
    while (x->_Parent && x->_Parent->_Color == Node::Red &&             \
           x->_Parent->_Parent)                                         \
    {                                                                   \
      Node *y = x->_Parent->_Parent;                                    \
                                                                        \
      if (x->_Parent == y->_Left)                                       \
      {                                                                 \
        y = y->_Right;                                                  \
                                                                        \
        if (y && y->_Color == Node::Red)                                \
        {                                                               \
          x->_Parent->_Color = Node::Black;                             \
          y->_Color = Node::Black;                                      \
          x->_Parent->_Parent->_Color = Node::Red;                      \
          x = x->_Parent->_Parent;                                      \
        }                                                               \
        else                                                            \
        {                                                               \
          if (x == x->_Parent->_Right)                                  \
          {                                                             \
            x = x->_Parent;                                             \
            LeftRotate(x);                                              \
          }                                                             \
          x->_Parent->_Color = Node::Black;                             \
          x->_Parent->_Parent->_Color = Node::Red;                      \
          RightRotate(x->_Parent->_Parent);                             \
          break;                                                        \
        }                                                               \
      }                                                                 \
      else                                                              \
      {                                                                 \
        y = y->_Left;                                                   \
                                                                        \
        if (y && y->_Color == Node::Red)                                \
        {                                                               \
          x->_Parent->_Color = Node::Black;                             \
          y->_Color = Node::Black;                                      \
          x->_Parent->_Parent->_Color = Node::Red;                      \
          x = x->_Parent->_Parent;                                      \
        }                                                               \
        else                                                            \
        {                                                               \
          if (x == x->_Parent->_Left)                                   \
          {                                                             \
            x = x->_Parent;                                             \
            RightRotate(x);                                             \
          }                                                             \
          x->_Parent->_Color = Node::Black;                             \
          x->_Parent->_Parent->_Color = Node::Red;                      \
          LeftRotate(x->_Parent->_Parent);                              \
          break;                                                        \
        }                                                               \
      }                                                                 \
    }                                                                   \
    _Root->_Color = Node::Black;                                        \
  }                                                                     \
  return Status;                                                        \
}                                                                       \
                                                                        \
HRESULT                                                                 \
Typename::BinaryInsert(const Typename::KeyType &iKey, const Typename::DataType &iData, Typename::Node*& oNode) \
{                                                                       \
  Node *B = LowerBound(iKey);                                           \
                                                                        \
  if (B && B->_Key == iKey)                                             \
  {                                                                     \
    oNode = B;                                                          \
    if (B->_Data == iData)                                              \
      return S_FALSE;                                                   \
    else                                                                \
      return E_FAIL; /* Does not update data; fail instead. */          \
  }                                                                     \
  else                                                                  \
  {                                                                     \
    Node *N = PopFreeNode();                                            \
    if (N)                                                              \
    {                                                                   \
      N->_Key = iKey;                                                   \
      N->_Data = iData;                                                 \
      N->_Color = Node::Red;                                            \
      N->_Left = 0;                                                     \
      N->_Right = 0;                                                    \
                                                                        \
      if (!_Root)                                                       \
      {                                                                 \
        N->_Parent = 0;                                                 \
        _Root = N;                                                      \
      }                                                                 \
      else if (B) /* Actually useless */                                \
      {                                                                 \
        N->_Parent = B;                                                 \
        if (B->_Key < iKey)                                             \
          B->_Right = N;                                                \
        else                                                            \
          B->_Left = N;                                                 \
      }                                                                 \
                                                                        \
      oNode = N;                                                        \
      return S_OK;                                                      \
    }                                                                   \
  }                                                                     \
                                                                        \
  return E_FAIL;                                                        \
}                                                                       \
                                                                        \
HRESULT                                                                 \
Typename::Erase(const KeyType &iKey)                                    \
{                                                                       \
  HRESULT Status = S_FALSE;                                             \
                                                                        \
  Iterator I(Find(iKey));                                               \
  Node *Z = I.GetNode();                                                \
  if (Z)                                                                \
  {                                                                     \
    Node *Y = 0;                                                        \
    if (Z->_Left && Z->_Right)                                          \
    {                                                                   \
      Y = RightTreeSuccessor(Z);                                        \
      Z->_Key = Y->_Key;                                                \
      Z->_Data = Y->_Data;                                              \
    }                                                                   \
    else                                                                \
      Y = Z;                                                            \
                                                                        \
    /* Node Y has now at most one non-leaf child. */                    \
    /* This is the node to be removed. */                               \
                                                                        \
    if (Y) /* Useless (mkcs) */                                         \
    {                                                                   \
      Node *X = 0;                                                      \
      if (Y->_Left)                                                     \
        X = Y->_Left;                                                   \
      else                                                              \
        X = Y->_Right;                                                  \
                                                                        \
      if (X)                                                            \
      {                                                                 \
        /* Replace the node by its child. Put X in place of Y */        \
        X->_Parent = Y->_Parent;                                        \
        if (!Y->_Parent)                                                \
          _Root = X;                                                    \
        else if (Y == Y->_Parent->_Left)                                \
          Y->_Parent->_Left = X;                                        \
        else                                                            \
          Y->_Parent->_Right = X;                                       \
      }                                                                 \
      else                                                              \
      {                                                                 \
        /* Phantom leaf that will be deleted afterwards. */             \
        /* (Leaves are represented as null nodes.) */                   \
        X = Y;                                                          \
      }                                                                 \
                                                                        \
      if (X) /* Useless (mkcs). */                                      \
      {                                                                 \
        if (Y->_Color == Node::Black)                                   \
          EraseFixup (X);                                               \
                                                                        \
        /* Remove reference to the leaf node. */                        \
        /* It must be black and not have any child. */                  \
        if (X == Y)                                                     \
        {                                                               \
          if (X->_Parent)                                               \
          {                                                             \
            if (X->_Parent->_Left == X)                                 \
              X->_Parent->_Left = 0;                                    \
            else                                                        \
              X->_Parent->_Right = 0;                                   \
          }                                                             \
          else                                                          \
            _Root = 0;                                                  \
        }                                                               \
                                                                        \
        /* Get rid of Y. */                                             \
        Status = S_OK;                                                  \
        PushFreeNode (*Y);                                              \
      }                                                                 \
    }                                                                   \
  }                                                                     \
                                                                        \
  return Status;                                                        \
}                                                                       \
                                                                        \
Typename::Node *                                                        \
Typename::RightTreeSuccessor(Typename::Node *X)                         \
{                                                                       \
  if (X && X->_Right)                                                   \
  {                                                                     \
    X = X->_Right;                                                      \
    while (X->_Left)                                                    \
      X = X->_Left;                                                     \
    return X;                                                           \
  }                                                                     \
  return 0;                                                             \
}                                                                       \
                                                                        \
HRESULT                                                                 \
Typename::EraseFixup(Node *X)                                           \
{                                                                       \
  while (X != _Root && X->_Color == Node::Black)                        \
    if (X == X->_Parent->_Left)                                         \
    {                                                                   \
      Node *W = X->_Parent->_Right;  /* Sibling of X. */                \
      if (!W) return E_FAIL; /* Cannot fail */                          \
                                                                        \
      if (W->_Color == Node::Red)                                       \
      {                                                                 \
        W->_Color = Node::Black;                                        \
        X->_Parent->_Color = Node::Red;                                 \
        LeftRotate(X->_Parent);                                         \
        W = X->_Parent->_Right;                                         \
      }                                                                 \
                                                                        \
      if ((!W->_Left || W->_Left->_Color == Node::Black) &&             \
          (!W->_Right || W->_Right->_Color == Node::Black))             \
      {                                                                 \
        W->_Color = Node::Red;                                          \
        X = X->_Parent;                                                 \
      }                                                                 \
      else                                                              \
      {                                                                 \
        if (!W->_Right || W->_Right->_Color == Node::Black)             \
        {                                                               \
          W->_Left->_Color = Node::Black;                               \
          W->_Color = Node::Red;                                        \
          RightRotate(W);                                               \
          W = X->_Parent->_Right;                                       \
        }                                                               \
                                                                        \
        W->_Color = X->_Parent->_Color;                                 \
        X->_Parent->_Color = Node::Black;                               \
        W->_Right->_Color = Node::Black;                                \
        LeftRotate(X->_Parent);                                         \
        X = _Root;                                                      \
      }                                                                 \
    }                                                                   \
    else /* X == X->_Parent->_Left */                                   \
    {                                                                   \
      Node *W = X->_Parent->_Left; /* Sibling of X. */                  \
      if (!W) return E_FAIL; /* Cannot fail */                          \
                                                                        \
      if (W->_Color == Node::Red)                                       \
      {                                                                 \
        W->_Color = Node::Black;                                        \
        X->_Parent->_Color = Node::Red;                                 \
        RightRotate(X->_Parent);                                        \
        W = X->_Parent->_Left;                                          \
      }                                                                 \
                                                                        \
      if ((!W->_Left || W->_Left->_Color == Node::Black) &&             \
          (!W->_Right || W->_Right->_Color == Node::Black))             \
      {                                                                 \
        W->_Color = Node::Red;                                          \
        X = X->_Parent;                                                 \
      }                                                                 \
      else                                                              \
      {                                                                 \
        if (!W->_Left || W->_Left->_Color == Node::Black)               \
        {                                                               \
          W->_Right->_Color = Node::Black;                              \
          W->_Color = Node::Red;                                        \
          LeftRotate(W);                                                \
          W = X->_Parent->_Left;                                        \
        }                                                               \
                                                                        \
        W->_Color = X->_Parent->_Color;                                 \
        X->_Parent->_Color = Node::Black;                               \
        W->_Left->_Color = Node::Black;                                 \
        RightRotate(X->_Parent);                                        \
        X = _Root;                                                      \
      }                                                                 \
    }                                                                   \
                                                                        \
  if (!X) return E_FAIL; /* Should not fail */                          \
                                                                        \
  X->_Color = Node::Black;                                              \
  return S_OK;                                                          \
}                                                                       \
                                                                        \
HRESULT                                                                 \
Typename::LeftRotate(Node *x)                                           \
{                                                                       \
  if (!x) return E_FAIL;                                                \
                                                                        \
  Node *y = x->_Right;                                                  \
                                                                        \
  x->_Right = y->_Left;                                                 \
  if (y->_Left)                                                         \
    y->_Left->_Parent = x;                                              \
                                                                        \
  y->_Parent = x->_Parent;                                              \
  if (!x->_Parent)                                                      \
    _Root = y;                                                          \
  else if (x == x->_Parent->_Left)                                      \
    x->_Parent->_Left = y;                                              \
  else                                                                  \
    x->_Parent->_Right = y;                                             \
                                                                        \
  y->_Left = x;                                                         \
  x->_Parent = y;                                                       \
                                                                        \
  return S_OK;                                                          \
}                                                                       \
                                                                        \
HRESULT                                                                 \
Typename::RightRotate(Node *x)                                          \
{                                                                       \
  if (!x) return E_FAIL;                                                \
                                                                        \
  Node *y = x->_Left;                                                   \
                                                                        \
  x->_Left = y->_Right;                                                 \
  if (y->_Right)                                                        \
    y->_Right->_Parent = x;                                             \
                                                                        \
  y->_Parent = x->_Parent;                                              \
  if (!x->_Parent)                                                      \
    _Root = y;                                                          \
  else if (x == x->_Parent->_Right)                                     \
    x->_Parent->_Right = y;                                             \
  else                                                                  \
    x->_Parent->_Left = y;                                              \
                                                                        \
  y->_Right = x;                                                        \
  x->_Parent = y;                                                       \
                                                                        \
  return S_OK;                                                          \
}                                                                       \
                                                                        \
Typename::Node *                                                        \
Typename::LowerBound(const Typename::KeyType &iKey) const               \
{                                                                       \
  Node *N = _Root;                                                      \
  while (N)                                                             \
    if ((iKey < N->_Key) && N->_Left)                                   \
      N = N->_Left;                                                     \
    else if ((N->_Key < iKey) && N->_Right)                             \
      N = N->_Right;                                                    \
    else                                                                \
      break;                                                            \
  return N;                                                             \
}                                                                       \
                                                                        \
void                                                                    \
Typename::PushFreeNode(Typename::Node &N)                               \
{                                                                       \
  if (0 < _Size) /* Cannot fail: assert */                              \
  {                                                                     \
    N._Left = _FirstFreeNode;                                           \
    _FirstFreeNode = & N;                                               \
    --_Size;                                                            \
  }                                                                     \
}                                                                       \
Typename::Node *                                                        \
Typename::PopFreeNode()                                                 \
{                                                                       \
  Typename::Node *N = _FirstFreeNode;                                   \
  if (_FirstFreeNode)                                                   \
    _FirstFreeNode = _FirstFreeNode->_Left;                             \
  else                                                                  \
  {                                                                     \
    unsigned int n = _Nodes.PushBack(Node());                           \
    if (n)                                                              \
      N = & _Nodes[n];                                                  \
  }                                                                     \
  if (N)                                                                \
    ++_Size;                                                            \
  return N;                                                             \
}                                                                       \
                                                                        \
HRESULT Typename::Clear(CATBoolean iKeepAllocatedMemory)                \
{                                                                       \
  _Size = 0;                                                            \
  _Root = 0;                                                            \
  _FirstFreeNode = 0;                                                   \
                                                                        \
  return _Nodes.Clear(iKeepAllocatedMemory);                            \
}

#endif // !CATPolyRedBlackTree_K_D_H
