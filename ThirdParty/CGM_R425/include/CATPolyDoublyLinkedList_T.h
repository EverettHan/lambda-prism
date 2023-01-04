//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Generic (macro-based) buckets-based doubly linked list.
//
// To specialize a doubly linked list to a particular value type, declare and
// define a new specialization of CATPolyDoublyLinkedList_T by invoking the
// dedicated macros.
//
// To declare a new specialization named `MyTList' for a value type `T',
// instantiate the `CATPolyDoublyLinkedList_T' template in a dedicated header
// file as follows:
//
//      // MyTList.h
//      #ifndef MyTList_H
//      #define MyTList_H
//
//      #include "CATPolyDoublyLinkedList_T.h"
//      class ExportedByMyDLL Specialize_CATPolyDoublyLinkedList_T(MyTList, T);
//
//      #endif // !MyTList_H
//
// Observe that the macro invocation SHALL be preceded by a `class' or a
// `struct' statement, and terminated by a `;'.
//
// To implement the specialization, instantiate the macro
// `Implement_Specialized_CATPolyDoublyLinkedList_T' in a dedicated implementation file:
//
//      // MyTList.cpp
//      #include "MyTList.h"
//
//      Implement_Specialized_CATPolyDoublyLinkedList_T(MyTList);
//
// For nesting a specialization, declare the specialization as previously:
//
//      // A.h
//      #ifndef A_H
//      #define A_H
// 
//      #include "CATPolyDoublyLinkedList_T.h"
//
//      class A
//      {
//      public:
//        struct Ab
//        {
//          class Specialize_CATPolyDoublyLinkedList_T(MyTList, T);
//        };
//      };
//
//      #endif // !A_H
//
// And prepend the outer class to the typename of the specialization when
// implementing:
//
//      // A.cpp
//      #include "A.h"
//
//      Implement_Specialized_CATPolyDoublyLinkedList_T(A::Ab::MyTList);
//
//=============================================================================
// 2007-01-07   BPG: New
//=============================================================================
#ifndef CATPolyDoublyLinkedList_T_H
#define CATPolyDoublyLinkedList_T_H

#include "CATErrorDef.h"
#include "CATPolyBuckets_T.h"

#define Specialize_CATPolyDoublyLinkedList_T(Typename, ValueTypename)           \
Typename                                                                        \
{                                                                               \
public:                                                                         \
  typedef ValueTypename ValueType;                                              \
                                                                                \
public:                                                                         \
  Typename():                                                                   \
    _Size(0), _Head(0), _Tail(0), _FreeHead(0)                                  \
  {}                                                                            \
                                                                                \
  Typename& operator = (const Typename& iRHS)                                   \
  {                                                                             \
    int nbNodes = iRHS._Nodes.Size ();                                          \
    for (int k = 1; k <= nbNodes; ++k)                                          \
    {                                                                           \
      int n = _Nodes.PushBack (iRHS._Nodes[k]);                                 \
    }                                                                           \
    _Size = iRHS._Size;                                                         \
    _Head = iRHS._Head;                                                         \
    _Tail = iRHS._Tail;                                                         \
    _FreeHead = iRHS._FreeHead;                                                 \
    return *this;                                                               \
  }                                                                             \
                                                                                \
  ~Typename() {}                                                                \
                                                                                \
public:                                                                         \
  /* Return number of referenced values */                                      \
  inline int Size() const { return _Size; }                                     \
  /* Return number of elements for which memory has been allocated. */          \
  /* Capacity() is always greater than or equal to Size() */                    \
  inline int Capacity() const { return _Nodes.Size(); }                         \
                                                                                \
  /* Iterators */                                                               \
public:                                                                         \
  inline int Begin() const { return _Head; }                                    \
  inline int RBegin() const { return _Tail; }                                   \
                                                                                \
  inline int Next(int n) const { return _Nodes[n]._Next; }                      \
  inline int Prev(int n) const { return _Nodes[n]._Prev; }                      \
                                                                                \
  /* Access */                                                                  \
public:                                                                         \
  const ValueTypename &operator[](int i) const;                                 \
  ValueTypename &operator[](int i);                                             \
                                                                                \
  inline const ValueTypename &Front() const { return _Nodes[_Head]._Value; }    \
  inline ValueTypename &Front() { return _Nodes[_Head]._Value; }                \
                                                                                \
  inline const ValueTypename &Back() const { return _Nodes[_Tail]._Value; }     \
  inline ValueTypename &Back() { return _Nodes[_Tail]._Value; }                 \
                                                                                \
  /* Edition */                                                                 \
public:                                                                         \
  /* Append iValue on tail */                                                   \
  int PushBack(const ValueTypename &iValue);                                    \
  /* Remove the element at node n */                                            \
  int Erase(int n);                                                             \
  /* Insert iValue before i (if i is 0, this is equivalent to PushBack */       \
  int Insert(int i, const ValueTypename &iValue);                               \
  /* Move m before n; m shall exist, and for moving m to tail, set n to 0 */    \
  HRESULT Move(int m, int n);                                                   \
  /* Erase all of the elements */                                               \
  HRESULT Clear(CATBoolean iKeepAllocatedMemory = FALSE);                       \
                                                                                \
  /* Internal */                                                                \
public:                                                                         \
  struct Node                                                                   \
  {                                                                             \
    ValueTypename _Value;                                                       \
    int _Next;                                                                  \
    int _Prev;                                                                  \
  };                                                                            \
  class Specialize_CATPolyBuckets_T(NodeBuckets, Node);                         \
                                                                                \
protected:                                                                      \
  /* Attach before n */                                                         \
  void Attach(int a, int n);                                                    \
  void Detach(Node &iNodeToDetach);                                             \
                                                                                \
protected:                                                                      \
  NodeBuckets _Nodes;                                                           \
  int _Size;                                                                    \
  int _Head;                                                                    \
  int _Tail;                                                                    \
  int _FreeHead;                                                                \
}

// ----------------------------------------------------------------------------

#define Implement_Specialized_CATPolyDoublyLinkedList_T(Typename)       \
                                                                        \
Implement_Specialized_CATPolyBuckets_T(Typename::NodeBuckets);          \
                                                                        \
const Typename::ValueType &                                             \
Typename::operator[](int iNode) const                                   \
{                                                                       \
  return _Nodes[iNode]._Value; /* Let buckets fail */                   \
}                                                                       \
                                                                        \
Typename::ValueType &                                                   \
Typename::operator[](int iNode)                                         \
{                                                                       \
  return _Nodes[iNode]._Value; /* Let buckets fail */                   \
}                                                                       \
                                                                        \
int                                                                     \
Typename::PushBack(const Typename::ValueType &iValue)                   \
{                                                                       \
  return Insert(0, iValue);                                             \
}                                                                       \
                                                                        \
int                                                                     \
Typename::Erase(int n)                                                  \
{                                                                       \
  if (0 < n)                                                            \
  {                                                                     \
    Node &NodeToRemove = _Nodes[n];                                     \
                                                                        \
    Detach(NodeToRemove);                                               \
                                                                        \
    NodeToRemove._Prev = 0;                                             \
    /* Push for recycling */                                            \
    NodeToRemove._Next = _FreeHead;                                     \
    _FreeHead = n;                                                      \
                                                                        \
    --_Size;                                                            \
    return _Head;                                                       \
  }                                                                     \
  return 0;                                                             \
}                                                                       \
                                                                        \
void                                                                    \
Typename::Detach(Node &iNodeToDetach)                                   \
{                                                                       \
  if (iNodeToDetach._Prev)                                              \
    _Nodes[iNodeToDetach._Prev]._Next = iNodeToDetach._Next;            \
  else                                                                  \
    _Head = iNodeToDetach._Next;                                        \
                                                                        \
  if (iNodeToDetach._Next)                                              \
    _Nodes[iNodeToDetach._Next]._Prev = iNodeToDetach._Prev;            \
  else                                                                  \
    _Tail = iNodeToDetach._Prev;                                        \
}                                                                       \
                                                                        \
int                                                                     \
Typename::Insert(int i, const Typename::ValueType &iValue)              \
{                                                                       \
  int n = 0;                                                            \
  Node *N = 0;                                                          \
                                                                        \
  if (0 < _FreeHead)                                                    \
  {                                                                     \
    /* Recycle */                                                       \
    n = _FreeHead;                                                      \
    N = &_Nodes[n];                                                     \
                                                                        \
    _FreeHead = N->_Next;                                               \
  }                                                                     \
  else                                                                  \
  {                                                                     \
    n = _Nodes.PushBack(Node());                                        \
    if (0 < n)                                                          \
      N = &_Nodes[n];                                                   \
  }                                                                     \
                                                                        \
  if (0 < n && N)                                                       \
  {                                                                     \
    ++_Size;                                                            \
                                                                        \
    N->_Value = iValue;                                                 \
                                                                        \
    Attach(n, i);                                                       \
  }                                                                     \
                                                                        \
  return n;                                                             \
}                                                                       \
                                                                        \
void                                                                    \
Typename::Attach(int n, int i)                                          \
{                                                                       \
  Node &NodeToAttach = _Nodes[n];                                       \
  NodeToAttach._Next = i;                                               \
  if (i)                                                                \
  {                                                                     \
    NodeToAttach._Prev = _Nodes[i]._Prev;                               \
    _Nodes[i]._Prev = n;                                                \
  }                                                                     \
  else /* Attach as tail */                                             \
  {                                                                     \
    NodeToAttach._Prev = _Tail;                                         \
    _Tail = n;                                                          \
  }                                                                     \
                                                                        \
  if (NodeToAttach._Prev)                                               \
    _Nodes[NodeToAttach._Prev]._Next = n;                               \
  else /* Attach as head */                                             \
    _Head = n;                                                          \
}                                                                       \
                                                                        \
HRESULT                                                                 \
Typename::Move(int m, int n)                                            \
{                                                                       \
  HRESULT Status = E_FAIL;                                              \
  if (0 < m)                                                            \
  {                                                                     \
    Node &NodeToMove = _Nodes[m];                                       \
    Detach(NodeToMove);                                                 \
    Attach(m, n);                                                       \
    Status = S_OK;                                                      \
  }                                                                     \
                                                                        \
  return Status;                                                        \
}                                                                       \
                                                                        \
HRESULT                                                                    \
Typename::Clear(CATBoolean iKeepAllocatedMemory)                        \
{                                                                       \
  _FreeHead = 0;                                                        \
  _Head = 0;                                                            \
  _Tail = 0;                                                            \
  _Size = 0;                                                            \
  return _Nodes.Clear(iKeepAllocatedMemory);                            \
}

#endif // !CATPolyDoublyLinkedList_T_H1
