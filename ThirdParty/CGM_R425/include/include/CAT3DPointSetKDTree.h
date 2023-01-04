//=============================================================================
// COPYRIGHT Dassault Systemes 2010
//=============================================================================
//
// CAT3DPointSetKDTree.h
//
// Allow to build and manage a set of points (possibly a point cloud),
// geometrically arranged in a k-d-tree.
//
//=============================================================================
// 2010-04-12   XXC: New.
// 2012-04-26   JXO: Index management.
// 2014-01      XXC: Remove the unused and useless point array, add copy constructor.
//=============================================================================

#ifndef CAT3DPointSetKDTree_H
#define CAT3DPointSetKDTree_H

#include "PolyMathContainers.h"

#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATMathInline.h"
#include "CATMathBox.h"
#include "CATMathPoint.h"


struct CATPolyIndexAndPoint {
  int m_i;
  const CATMathPoint * m_p;
};


/*
 * Construct a k-d-tree on a point set. The set of points is given by
 * an array of coordinates as [p1.x, p1.y, p1.z, p2.x, p2.y, p2.z,
 * ... , pN.x, pN.y, pN.z] where pi is the i-th point in the set and N
 * the size of the set.
 * IMPORTANT NOTE: The given array is modified inside the class and
 * should not be modified outside the class, after the build of the
 * tree and while the tree is in use.
 */

class ExportedByPolyMathContainers CAT3DPointSetKDTree
{
public:

  /** Empty tree. Should be used only in order to get children from an
   *  existing tree. See GetChildren.
   */
  CAT3DPointSetKDTree ();

  /** Copy contructor. Deleting a copy of the root won't delete shared
   *  data. See the root constuctor below.
   */
  CAT3DPointSetKDTree (const CAT3DPointSetKDTree & iToCopy);

  /** Root constructor. Build a tree with the given array of points
   *  coordinates. The root build with this constructor maintain
   *  temporary data shared by all the nodes. It can be copied but not
   *  deleted before any other node from the same tree.
   *@param ioPointSet: pointer to the first coordinate of the first
   *point in the set.
   *@param iSize: number of point in the set.
   *@param iNbMaxPointsInLeaves: the maximum number of points that
   *should be present in each leave of the tree.
   */
  CAT3DPointSetKDTree (const CATMathPoint * ioPointSet, unsigned int iSize, int iNbMaxPointsInLeaves = 10);

  ~CAT3DPointSetKDTree ();

  CAT3DPointSetKDTree & operator = (const CAT3DPointSetKDTree & iTree);

  /** Indicates if the tree is a terminal node, i.e. a leaf. By
   *  default, an empty tree is a leaf.
   *@return TRUE if the tree is a leaf, FALSE otherwise (it then
   *consequently has two children).
   */
  CATBoolean IsLeaf () const;

  /** Get the two children under the tree root. The two children must
   *  be already allocated and should be empty (use the default
   *  constructor).
   *@param oChild1: the first children.
   *@param oChild2: the second children.
   *@return S_OK if the two children has been correctly get, S_FALSE
   *if there is no children (the tree is not empty, but is a leaf),
   *E_FAIL is the tree is empty or something else is wrong.
   */
  HRESULT GetChildren (CAT3DPointSetKDTree & oChild1, CAT3DPointSetKDTree & oChild2) const;

  /** Returns the box bounding the points contained in the tree node.
   */
  INLINE const CATMathBox & GetBox () const {return _BoundingBox;}

  /** Return the number of points contained in this tree node.
   */
  INLINE unsigned int GetSize () const {return _Size;}

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
   *  iIndex'th point in the list of points contained in the
   *  tree node. Indices of points are from 0 and to (GetSize() - 1).
   */
  INLINE const CATMathPoint * GetPoint (unsigned int iIndex) const;
  /** Get a CATMathPoint representing the iIndex'th point in the point
   *  list contained in the tree node. Indices of points are from 0
   *  and to (GetSize() - 1).
   */
  INLINE void GetPoint (unsigned int iIndex, CATMathPoint & oPoint) const;
  /** Get the initial index representing the iIndex'th point in the point
   *  list contained in the tree node. iIndex ranges from 0
   *  and to (GetSize() - 1). Returned index ranges from 0 to number of point
   *  in initial array.
   */
  INLINE int GetIndex (unsigned int iIndex) const;
  /** Get the index of the node in the tree. The index is uniquely
   *  defined by its position in the tree relatively to the root in
   *  the same order than a breadth-first traversal, the root having
   *  index 0.
   */
  INLINE int GetIndex () const;

private:
  
  unsigned int BuildKDTree (CATPolyIndexAndPoint * ioStructPointSet, const int iSize, const int iLevel, char PreviousSortDir);

  static int sortAlongX(const void * iPoint1, const void * iPoint2);
  static int sortAlongY(const void * iPoint1, const void * iPoint2);
  static int sortAlongZ(const void * iPoint1, const void * iPoint2);

private:
  const CATPolyIndexAndPoint * _StructPointSet;
  double * _BBoxValues;
  unsigned int _Size, _LeafSizeMax, _Level, _TreeSize, _MaxLevel;
  CATMathBox _BoundingBox;
  CATBoolean _DeleteArray;
};

INLINE const CATMathPoint * CAT3DPointSetKDTree::GetPoint (unsigned int iIndex) const
{
  if(!_StructPointSet || iIndex < 0 || iIndex >= _Size)
    return 0;
  return _StructPointSet[iIndex].m_p;
}

INLINE void CAT3DPointSetKDTree::GetPoint(unsigned int iIndex, CATMathPoint & oPoint) const
{
  if(!_StructPointSet || iIndex < 0 || iIndex >= _Size)
    return;
  if(_StructPointSet[iIndex].m_p)
    oPoint = *(_StructPointSet[iIndex].m_p);
}

INLINE int CAT3DPointSetKDTree::GetIndex (unsigned int iIndex) const
{
  if(!_StructPointSet || iIndex < 0 || iIndex >= _Size)
    return -1;
  return _StructPointSet[iIndex].m_i;
}

INLINE int CAT3DPointSetKDTree::GetIndex () const
{
  return _Level;
}

#endif // CAT3DPointSetKDTree_H
