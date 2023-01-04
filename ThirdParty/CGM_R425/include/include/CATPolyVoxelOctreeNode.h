// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyVoxelOctreeNode.h
//
//===================================================================
//
// Usage notes: Class representing a general node of a voxel based
// octree (class CATPolyVoxelOctree).
//
//===================================================================
// 2009/04/20 - XXC: Creation
//===================================================================

#ifndef CATPolyVoxelOctreeNode_H
#define CATPolyVoxelOctreeNode_H

#include "PolyPartitions.h"
#include "CATMathBox.h"

class ExportedByPolyPartitions CATPolyVoxelOctreeNode
{
public:
  inline CATPolyVoxelOctreeNode();
  inline virtual ~CATPolyVoxelOctreeNode();

  /** If the node is a leaf, retrieves the elements contained in
   *  it. The array and size are null if the node is not a leaf or if
   *  the leaf does not contain any element.
   *@param oElements: an array of the indexes identifying the elements
   *contained in the leaf. MUST NOT BE FREED AFTER USE.
   *@param oNbElements: the number of elements (the size of the array
   *oElements).
   */
  virtual HRESULT GetElements(int * & oElements, int & oNbElements) const = 0;

  /** If the node is an inner node, retrieves an array of its
   *  children. The array is null if the node is a leaf.
   *@param oChildren: an array of nodes. The maximum number of
   *children is 8. All children are contained in the first
   *compartments of the array, i.e. if the node contains x < 8
   *children, then the x first elements of the array are the children
   *while the 8-x other elements are null pointers.
   */
  virtual HRESULT GetChildren(CATPolyVoxelOctreeNode ** & oChildren) const = 0;
  /** Tests if the node is a leaf or not.
   *@return TRUE if the node is a leaf, FALSE if it is an inner node.
   */
  virtual CATBoolean IsALeaf() const = 0;

  /** Get the bounding box of the set represented by the node.
   */
  inline virtual void GetBoundingBox(CATMathBox & oBox) const;

private:
  friend class CATPolyVoxelOctree;
  friend class CATPolyVoxelOctreeInNode;
  virtual CATPolyVoxelOctreeNode * FreeEmptyNodes() = 0;
protected:
  CATMathBox _PartitionBox;
};

inline  CATPolyVoxelOctreeNode::CATPolyVoxelOctreeNode()
{}

inline CATPolyVoxelOctreeNode::~CATPolyVoxelOctreeNode()
{}

inline void CATPolyVoxelOctreeNode::GetBoundingBox(CATMathBox & oBox) const
{
  oBox = _PartitionBox;
}

#endif // CATPolyVoxelOctreeNode_H
