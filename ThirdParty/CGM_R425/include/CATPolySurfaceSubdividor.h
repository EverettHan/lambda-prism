// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceSubdividor.h
//
// Please, read the associated comments before use this class
// **********************************************************
//
//===================================================================
//
// November 2012  Creation: DPS
// August   2020  Modification RBU3 : mode to allow non-manifold input
//                                    and the generation of a non-manifold PolyBody
//===================================================================

#ifndef CATPolySurfaceSubdividor_h
#define CATPolySurfaceSubdividor_h

#include "CATPolyTrianglePartitionDefiner.h"
#include "CATIPolySurfaceVertexIterator.h"
#include "PolyMeshTools.h"         // ExportedBy

#include "CATErrorDef.h"
#include "CATListOfInt.h"
#include "CATListPV.h"
#include "CATMapOfIntIntToInt.h"
#include "CATMapOfIntToInt.h"
#include "CATMapOfIntIntToPtr.h"

#include "CATBoolean.h"
#include "CATSysBoolean.h"

class CATIPolyMesh;
class CATPolySubMesh;
class CATMapOfIntIntToInt;
class CATMapOfPtrToPtr;
class CATPolyBody;
class CATMapOfPtrToInt;


/**
 * Sudivides the initial mesh into SubMeshes in regards with the partition values associated to the mesh triangles
 * 
 * This service works with all types of CATIPolyMesh, and doesn't suppose that
 * the mesh is a single set of connected triangles associated to a parametric surface.
 *
 * The returned SubMeshes only share vertices and internal bars (no triangle) and fill completely the whole original mesh.
 * Each returned SubMesh has only one global PartitionValue but an input partition value may lead to generate several SubMeshes 
 * to seperate the sets of triangles which are not connected to each others.
 * 
 * The only condition to work is that all connected triangles have a consistent orientation in their neighbourhood :
 * if a bar is bounding by 2 different triangles with the same side, the subdivision migth fail if it leads to an inconsistent propagation !
 *
 * For an input with non-mnaifold bars, the option AllowNonManifoldPolyBody() allows this service to generate a non-manifold PolyBody.
 * This mode does not work without the resulting PolyBody as nothing is done to guaranteed that the iterators on SplitEdges and
 * SplitVertex will work. However, the iterator on submeshes should work with this option too.
 * Without this option, non-manifold input lead to a result without splitEdges and splitVertices. Furthermore, the result is not guaranteed
 * to be coherent around the non-manifold bars as they are not used to the propagation.
 * 
 * The result is predictable and guarantees the operation robustness.
 */
class ExportedByPolyMeshTools CATPolySurfaceSubdividor 
{

public:

  /**
  * Constructor with a PolyMesh and an associated TrianglePartitionDefiner
  */  
  CATPolySurfaceSubdividor(CATIPolyMesh & iMesh, CATPolyTrianglePartitionDefiner & iPartitionDefiner);


  /**
  * Destructor
  */
  ~CATPolySurfaceSubdividor();

  /**
  * Allow this operator to generate a non-manifold polyBody.
  *   If not allowed, the subdividor on an non-manifold mesh may FAIL
  * 
  * The non-manifold bars inside a face will be kept unchanged (still leading to a non-manifold mesh)
  * The non-manifold bars shared by several faces will generate an edge on each face around it.
  *
  * CAUTION : iterators on SplitEdges and SplitVertices are not guaranteed to work with this option.
  *    They should not be used after the Run.
  */
  void AllowNonManifoldPolyBody();

  /**
  * SubMeshes computation
  * Sudivides the initial mesh into SubMeshes in regards with the partition values associated to the mesh triangles
  * and describes the result parts as a list of oriented SubMeshes and a set of SplitEdges (set of connex & manifold internal bars)
  *
  * The optional argument ioPartitionBody has to be allocated by the caller and allows the Subdividor
  *                                       to make one CATPolyFace per SubMesh and one CATPolyEdge per SplitEdge (2 in case of closure)
  * The second optional argument oMapPolyBodyFaceToPartition has to be allocated by the caller and allows the Subdividor
  *                                       to associate its partitionValue to each face of the PolyBody.
  *
  * @return
  *      S_OK if the subdivision by SplitEdges is successful
  *      S_FALSE if there is no SplitEdge then no subdivision
  *      E_FAIL in case of pathology like NonManifold bar (whitout the option AllowNonManifoldPolyBody)
  */
  HRESULT Run(CATPolyBody * oPartitionBody=0, CATMapOfPtrToInt * oMapPolyBodyFaceToPartition=0);


  /**
  * Returns the input PolyMesh (no AddRef done during this access)
  * @return [out, IUnknown#Release]
  *   A CATIPolyMesh 
  */ 
  inline CATIPolyMesh & GetInputPolyMesh() const;

  /**
  * Returns the number of SubMeshes after the subdivision
  * @return
  *   An integer number of SubMeshes
  */
  inline int GetNbSubMeshes() const;

  /**
  * Returns the number of SplitEdges after the disconnection
  * @return
  *   An integer number of Split Edges
  */
  inline int GetNbSplitEdges() const;

  /**
  * Returns the Manifold diagnosis of the initial mesh after study.
  *   It only looks for non-manifold bars.
  * @return
  *   A boolean status TRUE or FALSE
  */
  inline CATBoolean IsMeshManifold() const;


public:


  /**
  * Iterator to cycle through all the SubMeshes
  */
  class ExportedByPolyMeshTools SubMeshIterator
  {
  public:

    SubMeshIterator (const CATPolySurfaceSubdividor& iSubdividor);
    ~SubMeshIterator () {}

    void Begin ();
    CATBoolean End () const;
    void operator++ ();

    /**
    * Returns the SubMesh (after AddRef increment)
    * The caller has to release it after use
    * @return [out, IUnknown#Release]
    *   A CATIPolyMesh (may be the initial mesh if there is no subdivision)
    */
    CATIPolyMesh * GetSubMesh() const;

    int GetPartitionValue() const;


  private:    

    const CATListPV     &_subMeshes;
    const CATListOfInt  &_values;
    unsigned int         _subMeshIdx;
    unsigned int         _maxIndex;
  };


public :

  class SplitVertexIterator;

  /**
  * Iterator to cycle through all the SplitEdges
  */
  class ExportedByPolyMeshTools SplitEdgeIterator
  {
  public:

    SplitEdgeIterator (const CATPolySurfaceSubdividor& iSubdividor);
    ~SplitEdgeIterator () {}

    void Begin ();
    CATBoolean End () const;
    void operator++ ();

    int GetNbVertices() const;

    /**
    * Returns the SubMesh on the left side regarding the sense of the SplitEdge mesh vertex line
    * No AddRef has been done here before returning the CATPolySubMesh pointer
    * The caller has to AddRef if necessary
    * @return
    *   A CATPolySubMesh
    */
    CATPolySubMesh * GetLeftSubMesh() const;

    /**
    * Returns the SubMesh on the right side regarding the sense of the SplitEdge mesh vertex line
    * No AddRef has been done here before returning the CATPolySubMesh pointer
    * The caller has to AddRef if necessary
    * @return
    *   A CATPolySubMesh
    */
    CATPolySubMesh * GetRightSubMesh() const;

  private:    

    friend class SplitVertexIterator;

    const CATPolySurfaceSubdividor & _subdividor;
    const CATListOfInt & _splitVertices;
    const CATListOfInt & _splitEdgeSizes;

    unsigned int         _splitEdgeIdx;
    unsigned int         _vtxOffset;
  };

  /**
  * Iterator to cycle through all the vertices in the SplitEdge
  */
  class ExportedByPolyMeshTools SplitVertexIterator : public CATIPolySurfaceVertexIterator
  {
  public:

    SplitVertexIterator (const SplitEdgeIterator& iSplitEdgeIterator);
    ~SplitVertexIterator () {}

    CATIPolyIndexIterator& Begin ();
    CATBoolean End () const;
    CATIPolyIndexIterator& operator++ ();

    /**
    * Returns the current index.
    * @return
    *   An integer index (vertex index in the mesh)
    */
    int Get() const;

    /**
    * Returns the index of the triangles on the left and on the right of the current bar, defined by the previous vertex and the current one.
    * returns S_FALSE for the first vertex of the current SplitEdge, waiting for the second one to define the first bar
    * @return
    *   A HRESULT value
    */
    HRESULT GetTriangles(int &oLeftTriangle, int &oRightTriangle) const;
    
    /**
    * Returns the current index.
    * @return
    *   An integer index.
    */
    int operator*();


  private:

    const SplitEdgeIterator  & _splitEdgeIterator;
    const CATListOfInt       & _splitVertices;
    unsigned int               _vertexIdx;
  };

private:

  // Build the structure of bars to left triangles and the map to get the PartitionValue of each triangle
  // Also checked if the mesh is non-manifold (more than one left triangle for one oriented bar)
  //   And store the information in _IsMeshManifold
  HRESULT ComputeBarsAndTrianglesData(int &oNbTriangles, CATBoolean &oHasMeshSinglePartitionValue, int &oSingleMeshPartitionValue);

  // Compute the subdivision of the original Mesh
  HRESULT SubdivideMesh(int iNbTriangles, CATBoolean iHasSinglePartitionValue);

  // Compute the connex sets of bars as output SplitEdges
  // Only called for manifold meshes (or with the AllowNonManifoldPolyBody option)
  HRESULT ComputeOutputSplitEdges(CATPolyBody * oPartitionBody, CATMapOfPtrToPtr &iMapOfSubMeshToPolyFace);

  // Add an int to a map of (int,int)->CATListOfInt*
  // Initialize a new list if needed, otherwise add it to the existing list.
  // The lists created must be deleted by the caller.
  HRESULT AddIntToMapOfList(CATMapOfIntIntToPtr &ioMap, int iKey1, int iKey2, int iIntToAdd,
    CATBoolean iRemoveDuplicates = FALSE);

  // Add a list of int to a map of (int,int)->CATListOfInt*
  // Initialize a new list if needed, otherwise add it to the existing list.
  // The lists created must be deleted by the caller.
  HRESULT AddListOfIntToMapOfList(CATMapOfIntIntToPtr &ioMap, int iKey1, int iKey2,
    const CATListOfInt &iIntsToAdd, CATBoolean iRemoveDuplicates = FALSE);

  void Clean();


private:

  friend class SubMeshIterator;
  friend class SplitEdgeIterator;
  friend class SplitVertexIterator;


  // Input
  // =====

  CATIPolyMesh                       & _Mesh;
  CATPolyTrianglePartitionDefiner    & _PartitionDefiner;

  CATBoolean                           _NonManifoldPolyBodyAllowed;


  // Working data
  // ============
  CATMapOfIntIntToInt                  _BarsToLeftTriangles;
  CATMapOfIntIntToPtr                  _NonManifoldBarsToLeftTriangles;
  CATMapOfIntToInt                     _TrianglePartitionValues;
  CATBoolean                           _IsMeshManifold;


  // SplitEdge bars
  // ---------------
  CATMapOfIntIntToInt                  _SplitBarToLeftTriangle;
  CATMapOfIntIntToInt                  _SplitBarToRightTriangle;
  CATMapOfIntIntToInt                  _SplitBarToLeftSubMesh;
  CATMapOfIntIntToInt                  _SplitBarToRightSubMesh;

  CATMapOfIntIntToPtr                  _NonManifoldSplitBarToLeftSubMesh;
  CATMapOfIntIntToPtr                  _NonManifoldSplitBarToRightSubMesh;


  // Output
  // ======

  // Mesh partition
  // --------------
  CATListPV                            _ListOfSubMeshes;   // gives the list of SubMeshs on the subdivided original Mesh
  CATListOfInt                         _ListOfValues;      // gives the list of the values associated to the SubMeshes

  // SplitEdge polylines
  // --------------------
  CATListOfInt                         _SplitVertices;     // all the vertices which decribes ordered sets of SplitEdges
  CATListOfInt                         _SplitEdgeSizes;    // gives the number of bars in each SplitEdge, to interpret _SplitVertices as a list of subsets
  CATListOfInt                         _LeftSubMeshes;
  CATListOfInt                         _RightSubMeshes;

};


// inline methods
// --------------
inline CATIPolyMesh & CATPolySurfaceSubdividor::GetInputPolyMesh() const {
  return _Mesh; }

inline int CATPolySurfaceSubdividor::GetNbSubMeshes() const {
  return _ListOfSubMeshes.Size(); }

inline int CATPolySurfaceSubdividor::GetNbSplitEdges() const {
  return _SplitEdgeSizes.Size(); }

inline CATBoolean CATPolySurfaceSubdividor::IsMeshManifold() const {
  return _IsMeshManifold; }

#endif
