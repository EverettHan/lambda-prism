//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATPolyVoxelHybridTree
//
//=============================================================================
// 2009-08-26   MPX: New
//=============================================================================
#ifndef CATPolyVoxelHybridTree_H
#define CATPolyVoxelHybridTree_H

#include "PolyVoxelHybrid.h"

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathLimits.h"
#include "CATMathInline.h"
#include "CATListOfInt.h"
#include "CATPolyVoxelTree.h"
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATPolyRayTriangleIntersector.h"




class CATMathBox;
class CATPolyMapVoxelToStradlersSet;

//////////////////////////////////////////////////////////////////////////////////
// class CATPolyVoxelHybridTree
//
// This class internally uses CATPolyVoxelTree, but extends the functionality.
//
// Salient Features:
//
// 1. Allows creation of a blank voxel tree of appropriate size, depth and voxel 
//    aspect ratios based on the number of elements to be added and the cumulative 
//    bounding box of all elements to be added.
//    [ CreateBlankVoxelTree() ]
//
// 2. Adds every element to the smallest voxel completely containing the element.
//    [ AddElement() ]
//
// 3. Because of the above point, it may happen that a rather tiny element might
//    get added to a rather large voxel, when an element straddles across two or 
//    more voxels. This might introduce inefficiencies in spatial search. In order
//    to mitigate this issue, the voxel stradlers of every voxel are grouped
//    spatially and these groups are treated as additional children of the 
//    containing voxel. However grouping of voxel stradlers is done only if they 
//    are large enough in number to justify special treatment.
//    [ these are internal specifics that the user need not bother about ]
//
// 4. Provides functionality to create a custom filtered iterator of elements.
//    The filtering and sorting is done based on the user given "VoxelFilter"
//    Elements rejected by the user given "VoxelFilter" will not be traversed
//    by the filtered iterator. Also the elements returned will be "loosely"
//    sorted based on the priority indicated by the user given "VoxelFilter".
//    [ GetFilteredIterator() ]
//
// 5. A predefined filtered iterator has been provided that can be used to
//    all elements that might possibly intersect a given segment, sorted
//    "loosely" based on its distance from the start of segment.
//    [ GetSegmentFilteredIterator() ]
//
// 6. The same predefined filtered iterator can be used with ray, which is a 
//    special case of a segment. class CATPolyVoxelHybridTree::Ray is derived
//    from class CATPolyVoxelHybridTree::Segment.
// 
// 7. Note that every element is an integer, whose interpretation is left to the
//    derived class.
//
//////////////////////////////////////////////////////////////////////////////////

class ExportedByPolyVoxelHybrid CATPolyVoxelHybridTree
{

public:

  class ExportedByPolyVoxelHybrid Segment
  {
  public:
    INLINE Segment(
            const CATMathPoint& iSegmentStart,
            const CATMathDirection& iSegmentDir,
            double iSegmentLen);

    CATBoolean IsIntersectingWithAnotherSegment(
            const Segment& iAnotherSegment, 
            double iLenTol,
            double& oParamOnS1,
            double& oParamOnS2) const;

    CATBoolean IsIntersectingWithTriangle(
            const CATMathPoint& iP1, 
            const CATMathPoint& iP2, 
            const CATMathPoint& iP3,
            double iLenTol,
            CATPolyRayTriangleIntersector::Result& oRayTriangleIntersectionResult,
            CATBoolean& oIntersectsAtStart) const;

  public:
    CATMathPoint _Start;
    CATMathDirection _Dir;
    double _Len;
  };

  class ExportedByPolyVoxelHybrid Ray : public Segment
  {
  public:
    INLINE Ray(
            const CATMathPoint& iRayStart,
            const CATMathDirection& iRayDir);
  };

  class ExportedByPolyVoxelHybrid VoxelFilter
  {
  protected:

    // This function should be implemented in the derived class
    // oPriority value should be filled to indicate the priority of this voxel 
    //      Lesser the oPriority value, higher is the priority given.
    // Should return FALSE, if this voxel box is out of region of interest

    virtual CATBoolean IsVoxelRelevant(const CATMathBox& iVoxelBox, double& oPriority) = 0;

  public:
    virtual ~VoxelFilter();

    INLINE CATBoolean IsVoxelOfInterest(const CATMathBox& iVoxelBox, double& oPriority);
    INLINE VoxelFilter();
    INLINE CATULONG32 ForDebug__NbCallsToFilter() const;
  
  private:
    CATULONG32 _ForDebug__NbCallsToFilter;
  };

  class ExportedByPolyVoxelHybrid FilteredIterator
  {
  public:
    virtual ~FilteredIterator();

    virtual void Begin() = 0;
    virtual CATBoolean End() const = 0;
    virtual int Get() const = 0;
    virtual void operator++ () = 0;

  public:
    virtual CATULONG32 ForDebug__NbCallsToFilter() const = 0;
  };




public:

  virtual ~CATPolyVoxelHybridTree();

  // Creates a new filtered iterator. The iterator returns elements
  // only from voxels that intersect the given segment, sorted based
  // which voxel hits the segment first along the start to end of segment.
  // Make sure to delete the FilteredIterator after use.

  CATPolyVoxelHybridTree::FilteredIterator* GetSegmentFilteredIterator(
                          const Segment& iSegment,
                          double iLenTol);

  // Creates user defined filtered iterator. The iterator returns elements
  // only from voxels as per chosen and prioritized by user-given VoxelFilter.
  // Make sure to delete the FilteredIterator after use.

  CATPolyVoxelHybridTree::FilteredIterator* GetFilteredIterator(
                          VoxelFilter* iFilter,
                          CATBoolean iShouldReturnedIteratorOwnFilter);


  // For internal use 
  void GetChildVoxels(int iVoxel, CATListOfInt& oChildVoxels);
  void GetElementsInVoxel(int iVoxel, CATListOfInt& oElements);
  int GetNbChildrenVoxels(int iVoxel);
  INLINE void GetVoxelBox(int iVoxel, CATMathBox& oVoxelBox);
  INLINE int GetRootVoxelNumber();
  INLINE double GetModelSize();
  INLINE CATBoolean IsVoxelEmpty(int iVoxel);
  INLINE CATPolyVoxelTree& GetVoxelTree();
  INLINE CATPolyMapVoxelToStradlersSet* GetMapOfVoxelToStradlersSet();


protected:

  virtual HRESULT GetElementBox(int iElementIdx, CATMathBox& oElementBox) const = 0;

protected:

  // For use by derived class

  static CATPolyVoxelTree* CreateBlankVoxelTree(int iNbElements, const CATMathBox& iCumulativeBox, double& oModelSize);
  CATPolyVoxelHybridTree(CATPolyVoxelTree& iVoxelTree, double iModelSize);
  
  HRESULT AddElement(int iElementIdx);

  // To be called only after all elements have been added
  void ClassifyVoxelStradlers();


protected:

  CATPolyVoxelTree& _VoxelTree;
  CATPolyMapVoxelToStradlersSet* _MapOfVoxelToStradlersSet;
  double _ModelSize;

public:
  // For internal use only (ODT/debug purpose)
  static unsigned short __Mode;
};






INLINE 
CATPolyVoxelHybridTree::Segment::Segment(
            const CATMathPoint& iSegmentStart,
            const CATMathDirection& iSegmentDir,
            double iSegmentLen)
:
_Start(iSegmentStart),
_Dir(iSegmentDir),
_Len(iSegmentLen)
{
}

INLINE 
CATPolyVoxelHybridTree::Ray::Ray(
            const CATMathPoint& iRayStart,
            const CATMathDirection& iRayDir)
:
Segment(iRayStart, iRayDir, CATMathInfinite)
{
}

INLINE CATBoolean 
CATPolyVoxelHybridTree::VoxelFilter::IsVoxelOfInterest(const CATMathBox& iVoxelBox, double& oPriority)
{
  ++ _ForDebug__NbCallsToFilter;
  return IsVoxelRelevant(iVoxelBox, oPriority);
}

INLINE 
CATPolyVoxelHybridTree::VoxelFilter::VoxelFilter()
:
_ForDebug__NbCallsToFilter(0)
{
}

INLINE CATULONG32 
CATPolyVoxelHybridTree::VoxelFilter::ForDebug__NbCallsToFilter() const
{
  return _ForDebug__NbCallsToFilter;
}

INLINE double 
CATPolyVoxelHybridTree::GetModelSize() 
{ 
  return _ModelSize; 
}

INLINE int 
CATPolyVoxelHybridTree::GetRootVoxelNumber()
{
  return _VoxelTree.GetRootVoxelNumber();
}

INLINE CATPolyVoxelTree& 
CATPolyVoxelHybridTree::GetVoxelTree()
{
  return _VoxelTree;
}

INLINE void 
CATPolyVoxelHybridTree::GetVoxelBox(int iVoxel, CATMathBox& oVoxelBox)
{
  return _VoxelTree.GetVoxelBox(iVoxel, oVoxelBox);
}

INLINE CATBoolean 
CATPolyVoxelHybridTree::IsVoxelEmpty(int iVoxel)
{
  return (0 != _VoxelTree.IsVoxelEmpty(iVoxel));
}

INLINE CATPolyMapVoxelToStradlersSet* 
CATPolyVoxelHybridTree::GetMapOfVoxelToStradlersSet()
{
  return _MapOfVoxelToStradlersSet;
}

#endif // !CATPolyVoxelHybridTree_H

