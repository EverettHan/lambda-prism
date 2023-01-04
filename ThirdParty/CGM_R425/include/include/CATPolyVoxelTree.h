//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//==============================================================================================================

// CATPolyVoxelTree : Voxel tree structure attached to application elements having an XYZ box and an id
// This is a pure virtual class. The current implementation is defined in CATPolyVoxelTreeImp

// A VoxelTree is a tree (one single root) whose nodes are cuboids (parallelepipeds) named
// "voxels", where each voxel may have children which are defined by a regular spatial subdivision
// of their father. Given 3 integers NSub[3] for the whole tree, each voxel will be parted into NSub[0]
// columns along X axis, NSub[1] along Y and NSub[2] along Z. So each voxel may have at most
// NSub[0]*NSub[1]*NSub[2] direct children, which, in their turn may be further divided.
// Consequently, two voxels having same depth in the tree have same size and are necessarily disjoint
// (their intersection is empty)

// The aim is to attach application elements to voxels, in order to speed up algorithms handling huge
// numbers of elements, where only spatially interfering elements should be processed.

// There are mainly two ways of attaching elements to a VoxelTree, depending whether an element may be
// attached to several voxels or not. If not, the corresponding voxel will be automatically computed
// by AddElement() method, as being the smallest voxel that contains the element. If several voxels
// can be associated to the same element, the application may either choose the voxels involved by
// calling AddElementToVoxel() as many times as required, or let the tree choose the voxels
// automatically, applying the following rule: an element is attached to a voxel if and only if
// it crosses the voxel and there is at least one "brother" voxel (same father) that is not crossed
// (otherwise it applies to be attached to the father itself). However, this rule may only be applied 
// if the tree knows the geometry of the element, so it is available only for some simple shapes such
// as cuboids and triangles.

// Voxels are never created in the tree unless explicitly required by AddElementToVoxel(), or
// implicitly required by AddElement, according to the geometry of the added element and the
// addition mode (one voxel only or not). Unoccupied voxels are never created in memory.

// All added elements can optionally be named by "id"s whose number of bytes may be variable
// or not: if not, memory occupation is less, but their size must then be provided before adding
// elements (at construction or by SetCommonIdLengthInBytes() method).
// The depth of the tree may not be above a given number, 32 by default, which means the smallest
// voxels will never be smaller than NSub[0,1 or 2]**32 times the initial box dimension
// If NSub[0]=NSub[1]=NSub[2]=2, the tree is called an octree because each voxel has at most 8 children
// resulting from simple dichotomy in all dimensions.

//==============================================================================================================
// Creation : CHU , 27 / 02 / 2004
//==============================================================================================================

#ifndef CATPolyVoxelTree_H
#define CATPolyVoxelTree_H

#include "PolyVoxel.h"       // ExportedBy definition
#include "CATErrorDef.h"     // HRESULT definition
#include "CATPolyDumpable.h" // derivation

class CATMathBox;


// The following typedef are used by a method (CreateFrom) designed to build a voxel tree from any foreign
// triangular tessellated model (in float), using iterators on triangles, edges and vertices:
// ioIterData must be null at first call, and iterations must be processed until null is returned
// (then ioIterData is also reset to null)
// TesselVertexIterator returns a triple {x,y,z} whereas TesselSegmentIterator returns an array of 6 values
// {x1,y1,z1,x2,y2,z2} and TesselTriangleIterator returns 9 values {x1,y1,z1,x2,y2,z2,x3,y3,z3}
// iTesselObject is a pointer to an object that defines the tesselated model, it is signed void* to match all types.
// oTrName, oEdgName and oVtxName give a char* representing a name that can remain null if it is not used in this context
// (it is kept for compliancy with other applications). It can be a null pointer, or a pointer to an empty string
// *oNbNormals is the number of normal vectors if oNbNormals is not a null pointer in input
// The number of normals returned will be null if precise normals are not available
// If they are available, they can be retrieved in oNormals[] array (size = 3 * (*oNbNormals))
typedef float * (*TesselTriangleIterator)(void * iTesselObject, void *& ioIterData, char *& oTrName, int & oOrientation);
typedef float * (*TesselSegmentIterator)(void * iTesselObject, void *& ioIterData, char *& oSegName);
typedef float * (*TesselVertexIterator)(void * iTesselObject, void *& ioIterData, char *& oVtxName, int * oNbNormals, float *& oNormals);

class ExportedByPolyVoxel CATPolyVoxelTree : public CATPolyDumpable
{

public :

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Life cycle methods

  // The constructor is protected, use CreatePolyVoxelTree() instead
  // Alternate construction methods from reps, or from tessellation iterators are described
  // in a following section.

  // iNSub[] should contain the 3 numbers of divisions in X, Y and Z. If it is null,
  // {2,2,2} is taken as default and a real octree is created.
  // If iNSub is provided, at least one number (among the three) must be > 1
  // iDepthMajorant defines a maximum value for depth, taking into account the fact that
  // the root alone counts for one level (set iDepthMajorant=2 to get one level of voxels)

  // The argument named "iFitOctreeOverGrid" allows to create a real octree (2*2*2 divisions) 
  // in a box that is bigger than iBox, but where terminal voxels have exactly 
  // the same size and location as they would if the tree were a simple grid (i.e. depth=2, 
  // only one level below the root) with the given iBox and iNSub. The octree voxels, in this case,
  // fit exactly the grid voxels, but the octree is bigger than the grid. If this argument is set, 
  // then iDepthMajorant is ignored, but iNSub and iBox are required. The main benefit is a quicker
  // traversal of the tree (GetOwningVoxelNumber is quicker)

  // iCommonIdLengthInBytes must be set null if id's will not have the same size. In ordinary situations,
  // they are pointers in 32 bits os, hence the default size is 4
  static CATPolyVoxelTree * CreatePolyVoxelTree(CATMathBox * iBox=0, int iCommonIdLengthInBytes=4,
    int * iNSub=0, int iDepthMajorant=32, int iFitOctreeOverGrid=0);
  static void RemovePolyVoxelTree(CATPolyVoxelTree * iTree);

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Introspection methods :

  // The actual definition box may be bigger than the initial box if a box has been added, or if an octree
  // has been fit over a grid
  virtual void GetDefinitionBox(CATMathBox & oBox) const;
  virtual int  GetDepthMajorant() const;

  // Get total size in bytes (definition = memory freed if tree were deleted)
  virtual int GetSizeInMemory(int * oLostBytes=0) const;

  // Read the id size in bytes, if the same size has been assigned to all ids (else 0 is returned)
  virtual int GetCommonIdSizeInBytes() const;

  // Beware that the following method returns {2,2,2} if iFitOctreeOverGrid has been set to 1, whatever
  // the original size of the grid in input (this method should only be used if iFitOctreeOverGrid=0)
  virtual int GetNSub(int iXYZ) const; // iXYZ=0 for X, 1 for Y, 2 for Z

  // Get voxel size (three dimension, or diagonal) for a given depth (1=root=whole box)
  virtual void GetVoxelSizeForDepth(int iDepth, double oSize[3]);
  virtual double GetVoxelDiagonalSizeForDepth(int iDepth);

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // XYZ size modification (without calling this method, the definition box set at construction must absolutely
  // contain all points, boxes and triangles attached to the tree in the future

  // If a non empty tree has to take elements located outside its definition box, then the tree must
  // be updated in order to accept new voxels, without changing the geometry of any existing voxel
  // (hence not changing the elements already attached)
  // The following method must be called to allow this. Existing voxel numbers are not changed (but the root
  // number may change)
  // The new definition box will enclose the initial one plus the one given in input to the following method,
  // but eventually it may be bigger than both of them for internal reasons (if the tree depth is increased)
  // The number of subdivisions is increased only if the tree is a grid (depth=2), and unless explicitly not wanted
  // (iKeepNSub=1). In all other cases (if the tree is not a grid, or is an octree fit over a grid, or if
  // the number of subdivisions should remain constant), then the depth is increased, and the old root becomes
  // an ordinary voxel
  // In all sitiations, the size of the smallest voxels remains unchanged.
  virtual void IncreaseDefinitionBoxWith(CATMathBox & iBox, int iKeepNSub=0);

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Methods designed to attach ids to the tree (and to create the required voxels if they don't exist yet)

  // The following methods (AddElementXX..) are designed to attach an application element to voxel(s) in the tree
  // There are two strategies: an object may either be attached only once, to the smallest voxel that contains the object,
  // or to all deepest voxels it intersects. If the tree is a simple grid (depth = 1), the first strategy should be avoided
  // (any object bigger than a voxel would be attached to the root)

  // Add an element (whose id is *ipId) to the tree, *ipId's length is iIdLength (in bytes) if stated, or the common length for all ids, if not stated
  // The voxel number (1+index) is returned.
  // The second signature can be used to input a point, CATEpsg will be used if no tolerance is supplied
  // If iAddToAllDeepestVoxels=0, the element will be added to one voxel only: the smallest one that entirely contains the element (may be the root)
  // If iAddToAllDeepestVoxels=1, the element will be added to all deepest voxels it intersects (and not to their owning voxels)
  virtual int AddElement(char * ipId, CATMathBox & iElementBox, int iIdLength=0, int iAddToAllDeepestVoxels=1);
  virtual int AddElement(char * ipId, double * iPoint, double iTol=0., int iIdLength=0, int iAddToAllDeepestVoxels=1);

  // Add a triangle (array = x1,y1,z1, x2,y2,z2, x3,y3,z3) to all max depth voxels
  // touched by the triangle (even if they are currently empty)
  // The value returned is the number of the smallest voxel that contains all of them (may be the root)
  // Note that adding a triangle to the smallest voxel that contains the triangle (and only to this one) is not an option
  // because it amounts to handle the triangle as if it were a box, and another method can do this
  virtual int AddTriangleToDeepestVoxels(char * ipId, double * iTriangle, int iIdLength=0);

  // Add a segment (array = x1,y1,z1, x2,y2,z2) to all max depth voxels
  // touched by the segment (even if they are currently empty)
  // The value returned is the number of the smallest voxel that contains all of them (may be the root)
  // Note that adding a segment to the smallest voxel that contains the segment (and only to this one) is not an option
  // because it amounts to handle the segment as if it were a box, and another method can do this
  virtual int AddSegmentToDeepestVoxels(char * ipId, double * iSegment, int iIdLength=0);

  // Directly add an id to a voxel whose number is known 
  // the id's length in bytes must be provided if no common length has been assigned to all ids
  virtual void AddElementId(int iVoxelNumber, char * ipId, int iIdLength=0);

  // Add an element directly to a voxel given by its path (sequence of triples <XNum, YNum,ZNum> from root
  // to target voxel, just 3 numbers for one step below root = default configuration)
  // Returns the voxel number
  virtual int AddElementToVoxel(char * ipId, int * iVoxelPath, int iPathSize=3, int iIdLength=0);

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Methods designed to make the tree grow without attaching ids (create empty voxels)

  // Four methods are supplied, according to the geometry of the object that needs voxels (point, box, segment, triangle)
  // As for AddElement methods, there are two strategies : either create the smallest voxel containing the element (default),
  // or create all deepest voxels intersecting the element. The deepest voxels are created only if the pointer
  // oTouchedVoxelsList is not null. In this case, the array of deepest voxels must be deallocated by the application
  // when it is no longer needed (delete []). Optionally, this array will contain the intermediate voxels between the
  // root and the deepest ones involved (they are excluded by default, see arg. iExcludeNonDeepestVoxelsFromTouchedList)
  // In all cases, the integer value returned by the method is the number of the smallest voxel that contains the element.

  virtual int GetOrAddVoxel(CATMathBox & iBox, int ** oTouchedVoxelsList = 0, int * oTouchedVoxelsListSize = 0,
    int iExcludeNonDeepestVoxelsFromTouchedList = 1);

  virtual int GetOrAddVoxel(double * iPoint, double iTol=0., int ** oTouchedVoxelsList = 0, int * oTouchedVoxelsListSize = 0,
    int iExcludeNonDeepestVoxelsFromTouchedList = 1);

  virtual int GetOrAddVoxelForSegment(double * iSegment, int ** oTouchedVoxelsList = 0, int * oTouchedVoxelsListSize = 0,
    int iExcludeNonDeepestVoxelsFromTouchedList = 1);

  virtual int GetOrAddVoxelForTriangle(double * iTriangle, int ** oTouchedVoxelsList = 0, int * oTouchedVoxelsListSize = 0,
    int iExcludeNonDeepestVoxelsFromTouchedList = 1);

  // This method is designed to add (or get, if already created) one sub-voxel from a given (existing) father
  // iPositionNumber[3] = {number along X, number along Y, number along Z} of child with respect to father
  // Each iPositionNumber[k] must be a number >= 1 and <= the number of subdivisions in direction k (2 for an octree)
  // The returned value is the voxel number of the child. No (additional) id is attached to it
  virtual int GetOrAddChildVoxelToFather(int iFatherVoxelNumber, int iPositionNumber[3]);

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Navigation methods (get voxel from position or in a box, neighbor voxels, go down or up in the tree..)

  // Give smallest voxel (number) among existing ones that contains a given point or box,
  // without adding any voxel.
  // If oTouchedVoxelsList is not null, it contains the list of all intersected max-depth voxels
  // If an allocated array is available, set *ioTouchedVoxelsListMaxSize to its allocated size in input
  virtual int GetOwningVoxelNumber(CATMathBox & iBox, int ** oTouchedVoxelsList=0, int * oTouchedVoxelsListSize=0, int * ioTouchedVoxelsListMaxSize=0);
  virtual int GetOwningVoxelNumber(double * iPoint, double iTol=0., int ** oTouchedVoxelsList=0, int * oTouchedVoxelsListSize=0, int * ioTouchedVoxelsListMaxSize=0);

  // Visit the tree: this method gives the (unordered) list of children of any voxel.
  // oChildrenVoxelNumbers, if not null, should be sized for at most NSub[0]*NSub[1]*NSub[2] children (8 for an octree)
  // iVoxelNumber=0 indicates the root should be taken
  // The parallelepiped associated with iVoxelNumber has diagonal points oMinXYZ[] and oMinXYZ+oVoxelSizeXYZ[]
  // The father voxel number is optionally computed, as well as the number of children 
  // oPosVsFather[3] is the triple position in [1..NSub[0]]*[1..NSub[1]]*[1..NSub[2]] (3 times zero if no father)
  // The value returned by the method is 0 if the tree is ok and not null if it is corrupted
  virtual int GiveChildren(int iVoxelNumber, int * oChildrenVoxelNumbers, double oMinXYZ[3],
    double oVoxelSizeXYZ[3], int * oFatherVoxelNumber=0, int * oPosVsFather=0, int * oIsEmpty=0,
    int * oNbChildren=0, int * oNbNonEmptyChildren=0);

  // Iterate on direct children. oPositionNumbers[k] is between 1 and the number of divisions in direction k
  // oMinXYZ and oSizeXYZ, if not null, should be large enough to get 3 values (box of the child voxel)
  virtual int NextChildNumber(int iFatherVoxelNumber, int iPreviousChildNum, int oPositionNumbers[3],
    double * oMinXYZ=0, double * oSizeXYZ=0, int * oIsEmpty=0);
  
  virtual int GetVTreeSize() const;
  virtual int GetSubTreeSize(int iFromRootNumber) const; // counts given root as one, plus its children

  // Gives the number of the neighbor voxel obtained by a translation iDelta[3] in X,Y and Z
  // starting from iRefVoxel, The translation unit is the size of iRefVoxel (for instance,
  // iDelta={-1,0,0} will return the neighbor voxel immediatly at the left if X axis is to
  // the right. The neighbor voxel returned, if any, has at least iRefVoxelNum size, but may
  // be bigger, unless iSameDepthOnly is set to 1 in input.
  // If there is no such voxel (same depth specification not met, or target voxel out of
  // the reference box), then 0 is returned
  virtual int GetNeighborVoxel(int iRefVoxelNum, int iDelta[3], int iSameDepthOnly=1);

  // Iterate on all non-empty neighbor voxels intersecting a parallelepiped centered on
  // iCenterVoxelNumber whose size is 2*iDelta+1 times the central voxel size in each dimension
  // If all voxels have the same size, the iterator traverses all voxels whose distance with 
  // iCenterVoxelNumber is inferior or equal to iDelta, when the distance is expressed in
  // numbers of voxel rows
  // The 2nd signature matches different ranges (deltas) in each direction X, Y and Z
  virtual int NextNeighbor(int iCenterVoxelNumber, int iDelta, void *& ioIterator, int iSkipCenter=1);
  virtual int NextNeighbor(int iCenterVoxelNumber, int iDelta[3], void *& ioIterator, int iSkipCenter=1);

  // Iterate on all voxels intersecting a given box
  // Set ioIterator=null at first call, and don't interrupt iterations (to prevent memory leaks)
  // The returned value is the current (intersecting) voxel number
  // Beware: If attached elements must be visited, NextElementId should be called in a nested loop
  // with iSkipSmallerVoxels=1 (because NextVoxelIntersectingBox may visit embedded voxels)
  virtual int NextVoxelIntersectingBox(CATMathBox & iBox, void *& ioIterator,
    int iSkipVoxelsOnlyAdjacentToBox=0, int iSkipEmptyVoxels=1);

  // Read the root voxel number (whose extent is that of the definition box)
  // It is the first one (returns 1) unless the box has been increased after adding elements
  virtual int GetRootVoxelNumber() const;

  // Get the voxel that contains iVoxelNumber, and whose depth is one step smaller. If iVoxelNumber is the root voxel 
  // (corresponding to the whole definition box), then zero is returned (zero is not a valid voxel number)
  virtual int GetFatherVoxelNumber(int iVoxelNumber) const;

  // Check if two voxels are embedded, returns 1 if yes, 0 if no
  int IsASubVoxelOf(int iBigVoxelNumber, int iSmallVoxelNumber) const;

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Methods designed to investigate a single voxel (geometry, attached ids, work-area)

  // Gives the max depth downward under a given voxel of the tree, and optionally 
  // gives the number of non-empty voxels (a voxel is said "empty" if it has no "id"s, regardless of
  // how many ids are associated to its children)
  // Set iFromRootNumber=0 or iFromGivenRootIndex=-1 to process the whole tree (starting from _RootVoxelIndex)
  // GiveStatistics() provides all characteristics of the tree (All arrays must have been
  // pre-allocated by caller, first call GetDownwardDepth on root to get max depth, or use
  // the general majoration set at construction, 32 by default)
  virtual int GetDownwardDepth(int * oNbNonEmptyVoxelsInSubTree=0, int iFromGivenRootIndex=-1);
  virtual void GiveStatistics(int * oNbVoxelsPerDepth, int * oNbNonEmptyVoxelsPerDepth=0,
    int * oTotalNbIdsPerDepth=0, int * oMinNbIdsForAVoxelPerDepth=0, int * oMaxNbIdsForAVoxelPerDepth=0,
    int iFromRootNumber=0, int * oMaxDepth=0, int * oTotalNbIds=0, int iRootDepth=0); // don't use iRootDepth (internal use)

  // Get depth (upward) of a voxel (1 is returned for the root)
  virtual int GetDepth(int iVoxelIndex) const;

  // Check if a voxel has any elements attached (only to itself, not to sub-voxels or bigger voxels)
  virtual int IsVoxelEmpty(int iVoxelNumber);

  // The following method should only be called when building the tree is over:
  // Visit all elements belonging to the same voxel or an embedded one or an embedding one
  // (i.e., belonging to a non disjoint voxel in the tree). Returns null when finished
  // ioIterData should be 0 at first call, and then should be passed over iterations (will be =0 after last)
  // Tuning arguments (iSkipBiggerVoxels, iSkipSmallerVoxels) should not be
  // changed between two iterations (otherwise result is unpredictable)
  // No deallocation required if scan is interrupted
  // No counting method is provided (wouldn't be much quicker than iterating calls to NextElementId() while
  // handling a counter)
  // Note: if bigger and smaller voxels are skipped, this method can be used to scan all ids belonging to a voxel
  virtual char * NextElementId(int iRefVoxelNumber, int & ioIterData, int * oIdSizeInBytes=0,
    int iSkipBiggerVoxels=1, int iSkipSmallerVoxels=1, int * oCurrentOwningVoxelNumber=0);

  // Direct access to an id (ReplaceId will copy up to the size of the existing id, it
  // cannot be used to create an id, nor to change its size). GetId returns null if the id does not exist
  virtual char * GetId(int iRefVoxelNumber, int iIndexInVoxel=0, int *oIdSizeInBytes=0);
  virtual void ReplaceId(int iRefVoxelNumber, char * iNewId, int iIndexInVoxel=0);

  // Give the number of ids for a voxel, or the whole tree if iVoxelNumber=0
  virtual int GetNbIds(int iVoxelNumber=0);

  // Handle work area for voxels: the application may use this area in read/write, a reservation
  // flag is handled by the tree (lock / unlock). The size of the work areas is defined in the implementation
  virtual void SetWorkArea(int iVoxelNumber, unsigned char * iVal=0); // set to zero if iVal==null
  virtual void GetWorkArea(int iVoxelNumber, unsigned char * oVal);
  virtual void ResetWorkAreas(unsigned char * iInitVal=0); // set to zero if iVal==null
  virtual void LockWorkArea(); // does not check (IsWorkAreaLocked() should be called before)
  virtual void UnlockWorkArea(); // does not clear areas (call ResetWorkAreas if needed)
  virtual int IsWorkAreaLocked() const;

  // Get the size of a voxel + the coordinates of its center, or its box
  virtual void GetVoxelCenterAndSize(int iVoxelNum, double oSize[3], double oCenter[3], int * oDepth=0) const;
  virtual void GetVoxelBox(int iVoxelNum, CATMathBox & oVoxelBox) const;

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Customizing methods, to be called after construction or never (none of them is actually required)

  // General tuning : must be called before first time AddElement() is called
  // Setting the initial box is compulsory, if it hasn't been done upon construction
  // Maximum depth can be set directly or by setting voxel size, either isotropic
  // (iMinXYZVoxelSize gives a minimum cube) or non isotropic (it is better to provide
  // separate sizes in X, Y and Z if the main object is strongly anisotropic)
  virtual void SetInitialBox(double iMinX, double iMaxX, double iMinY, double iMaxY, double iMinZ, double iMaxZ);
  virtual void SetInitialBox(CATMathBox & iBox);
  virtual void SetCommonIdLengthInBytes(int iCommonIdLengthInBytes);

  // The following three methods must not be called if iFitOctreeOverGrid has been set to 1,
  // or after the first time AddElement() is called
  virtual void SetDepthFromVoxelSize(double iMinXVoxelSize, double iMinYVoxelSize, double iMinZVoxelSize, int * oDepth=0);
  virtual void SetDepthFromVoxelSize(double iMinXYZVoxelSize, int * oDepth=0);
  virtual void SetDepthMajorant(int iDepthMajorant); // iDepthMajorant may not be <1

  // Unlike the precedding customization methods, the next two methods may be called anytime, not only after construction
  // They are designed to customize the way memory is managed
  // The first one is used to optimize the allocation strategy for "id"s, by setting a "reasonable" number of ids per voxel,
  // in order to prevent too many reallocations. The default is 10.
  virtual void SetInitialNbIdsPerVoxel(int iInitialNbIdsPerVoxel);

  // Another tuning method: SetMaxAreaSize defines the biggest contiguous memory block that will be allocated
  // to handle the ids attached to voxels (unit = sizeof(int), default = 4 megabytes)
  virtual void SetMaxAreaSize(int iMaxAreaSize);

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Construction methods from reps or from tessellation iterators.

  // Creation utility from foreign tessellation or point-cloud (iTesselObject) with vertices and/or lines
  // and/or triangles.
  // iTesselObject will be passed to iterators as their working context (see signatures above)
  // All vertices, line segments, and triangles visited by iterators will generate voxels, and
  // attach their id to the corresponding voxels according to iIdMode (see below).
  // If an iterator is missing, then its corresponding objects wil not be attached to the tree.
  // The attachment process can be done in two ways, according to iAttachObjectsToMaxDepthVoxels:
  // if it is =0, objects (vertices, segments and triangles) will only be attached to their
  // smallest containing voxel, after having been "inflated" by iTol value (CATEpsg if null).
  // If iAttachObjectsToMaxDepthVoxels=1, all intersected voxels will be processed
  // If all iterators are supplied (one at least is required), then the voxels subdivision
  // will match triangles, lines and vertex-boxes.
  // The maximum depth of the tree can be majorated by iMajoDepth (32 by default)
  // iNSub will be taken as {2,2,2} (octree) if the pointer is null
  // Supplying the whole model box speeds up the process (avoid a preliminary iteration)
  // "id"s can optionally be associated to voxels, otherwise voxels will be created but considered
  // to be empty (tracking back the vertices or triangles contained will not be possible)
  // iIdMode: 0=no id, 1=iteration number stored (triangles, then edges, then vertices),
  //          2=names given in output by iterator (ended by end-of-string character '\0')
  //          negative value = names given by iterator assuming their size in bytes is the same for all,
  //          equal to -iIdMode
  // Node that repetitions done by vertex iterators will not duplicate voxels, but increase the number
  // of "id"s associated with the voxels involved, if "id"s are managed (iIdMode!=0)
  // If iReceivingTree is set, no new tree will be created, all objects will be added to iReceivingTree,
  // arguments iNSub and iMajoDepth are ignored, and the global box can be updated in option,
  // (using iBox if it is set, or after computing a new box) if iUpdateReceivingTreeBoxIfNeeded=1.
  static CATPolyVoxelTree * CreateFrom(TesselVertexIterator iVIter, TesselTriangleIterator iTrIter,
    TesselSegmentIterator iSegIter, void * iTesselObject, int iAttachObjectsToMaxDepthVoxels=0,
    int * iNSub=0, int iMajoDepth=32, double iTol=0., CATMathBox * iBox=0, int iIdMode=0,
    CATPolyVoxelTree * iReceivingTree = 0, int iUpdateReceivingTreeBoxIfNeeded = 1);

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Stream, unstream, and comparison methods, to be used by test-objects only

  // The "streamed" format is just a (very) verbose formatted dump, in ascii, with no session-dependant data,
  // where id's are dumped by their dump method (initialized by SetDumpMethod) and separated by //
  // It is not designed for archiving.
  // An "unstream" from such format generates a tree with the same voxels, but the id's attached
  // are allocated char* that will only contain the character string dumped by each id
  // WriteTreeToFile returns 0 if ok.
  // ReadTreeFromString assumes the tree has been dumped in iTreeContents, ending right before
  // the first occurrence of iEndOfTree if specified, or with the given size in bytes if it is not null,
  // or until /0 character is met if both arguments are null.
  // Keeping the voxel numbers is an option available only if all father voxels are described before their
  // children. This rule is broken on a tree dumped after having its reference box enlarged: using this
  // option in this context will cause the method to fail (result = null pointer)
  // These three methods require CATDevelopmentStage=TRUE (for the use of CATCGMOutput)
  virtual int WriteTreeToFile(char * iFilePathName);
  static CATPolyVoxelTree * ReadTreeFromFile(char * iFilePathName, int iKeepVoxelNumbers=0, int iIgnoreIds=0);
  static CATPolyVoxelTree * ReadTreeFromString(char * iTreeContents, int iKeepVoxelNumbers=0, int iIgnoreIds=0, char * iEndOfTree = 0, int iTreeSizeInBytes = 0);

  // Conpare two voxel trees: each voxel of this must have a matching voxel with same path to root
  // in iOtherTree, and if iCompareIds is not null, the lists of ids must be identical (in same order if
  // iCompareIds=2, in whichever order if it is =1). Two ids are said identical if the comparison method
  // returns 1. If there is no comparison method provided, the Dump method will be used instead, and
  // the strings generated by each id should be identical
  // This method returns 0 if the trees are identical, and the number of an unpaired voxel in this
  // if they are not
  virtual int CompareWithTree(CATPolyVoxelTree * iOtherTree, int iCompareIds = 2, 
    int (*iCompareId)(char* iId1, int iId1SizeInBytes, char* iId2, int iId2SizeInBytes, void* iCompareContext) = 0,
    void * iCompareContext = 0);

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Utility and debug methods 

  // Static methods : Utilities dedicated to compress or uncompress application "id"s,
  // assuming application's ids are sequences of non negative numbers, where each number can be majorated
  // All lengths in iFieldLengths[] array are in bytes (use GetNbBytesToCode() to compute them)
  // All values in iFieldValues[] must be non negative
  static int GetNbBytesToCode(int iNbValues); // means all values are in [0, iNbValues-1]
  static void Encode(int iNbFields, int * iFieldLengths, int * iFieldValues, char * oSequence); // oSequence allocated by caller
  static void Decode(int iNbFields, int * iFieldLengths, char * iSequence, int * oFieldValues); // oFieldValues allocated by caller

  // Dump
  static char _Name[10];
  static int  _IdModeForDebug;
  virtual char * GetShortName() const;
  virtual HRESULT Dump( CATCGMOutput & s) const;
  virtual void DumpVTreeStatistics( CATCGMOutput & s);
  virtual int * GetLastIVNumHandledInIdRef(); // dump utility
  virtual int AppendStringAndGiveOffsetInIdRef(char * iNewId, int iNewIdSize); // dump utility

  // Debug: Set a dump method dedicated to elements attached to voxels, whose signature is
  // void Dump(CATCGMOutput & s, char * ipElementId, int iElementSize, int iVoxelNumber, void * iElementContext);
  // where ipElementId and iElementSize are the argument passed to AddElement (size in bytes)
  // and iElementContext (optional) is a pointer that will be passed to the dump method at each call
  // iVoxelNumber is the owning voxel number and may not be used in the dump.
  virtual void SetDumpElementMethod(void(*iDump)(CATCGMOutput&,char*,int,int,void*), void * iElementContext=0);
  virtual int HasDumpElementMethod() const; // returns 1 if answer is yes, 0 if no

  // Check integrity of all data
  // returns 0 if ok
  virtual int Check(int iCheckLinksTreeMemoryArea=0);

  // Get creation number for debug (1 = first created tree, 2 = next one, and so on..)
  inline int GetTreeCreationRankForDebug() const;

  // Internal structures used by CreateFrom
  struct IdCount {
    int _IdMode; // >0 : "GPxx.Vyy or GPxx.Lyy or GPxx.Tyy", <0 : "Vyy" or "Lyy" or "Tyy"
    int _NVisitedGPs;
    int _NbVisitedVertices, _NbVisitedSegments, _NbVisitedTriangles;
    IdCount(int iIdMode);
  };

protected:

  // constructor and destructor only called by implementation (pure virtual class)
  CATPolyVoxelTree();
  virtual ~CATPolyVoxelTree();

  int _TreeCreationRankForDebug;

private:

  // Debug utilities used by CreateFrom()
  static void DumpIdInCreateFromMethod(CATCGMOutput& s, char * ipElementId, int iElementSize, int iVNum, void* iIdMode);
  static void DumpIdInCreateFromRepMethod(CATCGMOutput& s, char * ipElementId, int iElementSize, int iVNum, void* iIdCount);

  // Recursive utility for CompareWithTree
  // Note that children are not compared if an id comparison has failed on one of their ancestors,
  // but are counted as different in this case (in ioNbUnmatchedInThis)
  int CompareWithSubtree(int iFromRootNumber, CATPolyVoxelTree * iOtherTree, int iFromOtherRoot,
    int * ioMatchingVoxelNumber, int & ioNbUnmatchedInThis, int iCompareIds, 
    int (*iCompareId)(char* iId1, int iId1SizeInBytes, char* iId2, int iId2SizeInBytes, void* iCompareContext),
    void * iCompareContext);
  virtual void DumpIdInString(char * ipElementId, int iElementSize, int iVoxelNumber, char *& oDump);

  static int CompareTwoIds(CATPolyVoxelTree * iTree1, int iVNum1, char * iId1, int iId1Size, 
    CATPolyVoxelTree * iTree2, int iVNum2, char * iId2, int iId2Size,
    int (*iCompareId)(char* iId1, int iId1SizeInBytes, char* iId2, int iId2SizeInBytes, void* iCompareContext),
    void * iCompareContext);

};

inline int CATPolyVoxelTree::GetTreeCreationRankForDebug() const {
  return _TreeCreationRankForDebug; }

#endif
