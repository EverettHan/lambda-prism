//=============================================================================
// COPYRIGHT Dassault Systemes 2010
//=============================================================================
//
// CAT3DVectorSetKDTree.h
//
// Allow to build and manage a set of vectors (possibly a vector cloud),
// geometrically arranged in a k-d-tree.
//
//=============================================================================
// 2010-04-12   XXC: New.
// 2012-04-26   JXO: Copied from CAT3DPointSetKDTree
// 2014-01 XXC: Remove the unused and useless point array, add copy
// constructor, add assigment operator, add indexing of nodes in the
// tree.
//=============================================================================

#ifndef CAT3DVectorSetKDTree_H
#define CAT3DVectorSetKDTree_H

#include "PolyMathContainers.h"

#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATMathInline.h"
#include "CATMathBox.h"
#include "CATMathVector.h"


struct CATPolyIndexAndVector {
  int m_i;
  const CATMathVector * m_p;
};


/*
 * Construct a k-d-tree on a vector set. The set of vectors is given by
 * an array of coordinates as [p1.x, p1.y, p1.z, p2.x, p2.y, p2.z,
 * ... , pN.x, pN.y, pN.z] where pi is the i-th vector in the set and N
 * the size of the set.
 * IMPORTANT NOTE: The given array is modified inside the class and
 * should not be modified outside the class, after the build of the
 * tree and while the tree is in use.
 */

class ExportedByPolyMathContainers CAT3DVectorSetKDTree
{
public:

  /** Empty tree. Should be used only in order to get children from an
   *  existing tree. See GetChildren.
   */
  CAT3DVectorSetKDTree();

  /** Copy contructor. Deleting a copy of the root won't delete shared
   *  data. See the root constuctor below.
   */
  CAT3DVectorSetKDTree (const CAT3DVectorSetKDTree & iToCopy);

  /** Root constructor. Build a tree with the given array of vectors
   *  coordinates. The root build with this constructor maintain
   *  temporary data shared by all the nodes. It can be copied but not
   *  deleted before any other node from the same tree.
   *@param ioVectorSet: pointer to the first coordinate of the first
   *vector in the set.
   *@param iSize: number of vectors in the set.
   *@param iNbMaxVectorsInLeaves: the maximum number of vectors that
   *should be present in each leave of the tree.
   */
  CAT3DVectorSetKDTree(const CATMathVector * ioVectorSet, unsigned int iSize, int iNbMaxVectorsInLeaves = 10);

  ~CAT3DVectorSetKDTree();

  CAT3DVectorSetKDTree & operator = (const CAT3DVectorSetKDTree & iTree);

  /** Indicates if the tree is a terminal node, i.e. a leaf. By
   *  default, an empty tree is a leaf.
   *@return TRUE if the tree is a leaf, FALSE otherwise (it then
   *consequently has two children).
   */
  CATBoolean IsLeaf() const;

  /** Get the two children under the tree root. The two children must
   *  be already allocated and should be empty (use the default
   *  constructor).
   *@param oChild1: the first children.
   *@param oChild2: the second children.
   *@return S_OK if the two children has been correctly get, S_FALSE
   *if there is no children (the tree is not empty, but is a leaf),
   *E_FAIL is the tree is empty or something else is wrong.
   */
  HRESULT GetChildren(CAT3DVectorSetKDTree & oChild1, CAT3DVectorSetKDTree & oChild2) const;

  /** Returns the box bounding the vectors contained in the tree node.
   */
  INLINE const CATMathBox & GetBox() const {return _BoundingBox;}

  /** Return the number of vectors contained in this tree node.
   */
  INLINE unsigned int GetSize() const {return _Size;}

  /** Returns the total number of nodes (leaves included) contained in
   *  the tree.
   */
  INLINE unsigned int GetTreeSize () const { return _TreeSize; }
  /** Returns the maximal possible node index. Can be greater than the
   *  number of the tree size in some particular cases and is not
   *  updated for children.
   */
  INLINE unsigned int GetMaxNodeIndex () const { return _MaxLevel; }

  /** Return a pointer to the array of the three coordinates of the
   *  iIndex'th vector in the list of vectors contained in the
   *  tree node. Indices of vectors are from 0 and to (GetSize() - 1).
   */
  INLINE const CATMathVector *GetVector(unsigned int iIndex) const;
  /** Get a CATMathVector representing the iIndex'th vector in the vectors
   *  list contained in the tree node. Indices of vectors are from 0
   *  and to (GetSize() - 1).
   */
  INLINE void GetVector(unsigned int iIndex, CATMathVector & oVector) const;
  /** Get the initial index representing the iIndex'th vector in the vectors
   *  list contained in the tree node. iIndex ranges from 0
   *  and to (GetSize() - 1). Returned index ranges from 0 to number of vectors
   *  in initial array.
   */
  INLINE int GetIndex(unsigned int iIndex) const;
  /** Get the index of the node in the tree. The index is uniquely
   *  defined by its position in the tree relatively to the root in
   *  the same order than a breadth-first traversal, the root having
   *  index 0.
   */
  INLINE int GetIndex () const;

private:
  
  unsigned int BuildKDTree(CATPolyIndexAndVector * ioStructVectorSet, const int iSize, const int iLevel, char PreviousSortDir);

  static int sortAlongX(const void * iVector1, const void * iVector2);
  static int sortAlongY(const void * iVector1, const void * iVector2);
  static int sortAlongZ(const void * iVector1, const void * iVector2);

private:
  const CATPolyIndexAndVector * _StructVectorSet;
  double * _BBoxValues;
  unsigned int _Size, _LeafSizeMax, _Level, _TreeSize, _MaxLevel;
  CATMathBox _BoundingBox;
  CATBoolean _DeleteArray;
};

INLINE const CATMathVector * CAT3DVectorSetKDTree::GetVector(unsigned int iIndex) const
{
  if(!_StructVectorSet || iIndex < 0 || iIndex >= _Size)
    return 0;
  return _StructVectorSet[iIndex].m_p;
}

INLINE void CAT3DVectorSetKDTree::GetVector(unsigned int iIndex, CATMathVector & oVector) const
{
  if(!_StructVectorSet || iIndex < 0 || iIndex >= _Size)
    return;
  if(_StructVectorSet[iIndex].m_p)
    oVector = *(_StructVectorSet[iIndex].m_p);
}

INLINE int CAT3DVectorSetKDTree::GetIndex(unsigned int iIndex) const
{
  if(!_StructVectorSet || iIndex < 0 || iIndex >= _Size)
    return -1;
  return _StructVectorSet[iIndex].m_i;
}

INLINE int CAT3DVectorSetKDTree::GetIndex () const
{
  return _Level;
}

#endif // CAT3DVectorSetKDTree_H
