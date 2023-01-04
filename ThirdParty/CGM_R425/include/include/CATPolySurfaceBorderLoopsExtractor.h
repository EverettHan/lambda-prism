// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceBorderLoopsExtractor.h
//
// Please, read the associated comments before use this class
// **********************************************************
//
//===================================================================
//
// June 2012  Creation: DPS
//===================================================================

#ifndef CATPolySurfaceBorderLoopsExtractor_h
#define CATPolySurfaceBorderLoopsExtractor_h

#include "CATIPolySurfaceVertexIterator.h" // derivation for LoopVertexIterator
#include "PolyMeshTools.h"                 // ExportedBy

#include "CATErrorDef.h"
#include "CATListOfInt.h"
#include "CATListPV.h"
#include "CATSetOfInt.h"

#include "CATBoolean.h"
#include "CATSysBoolean.h"

class CATIPolyMesh;
class CATIPolyMeshTriangleVertexIterator;
class CATMapOfIntIntToInt;
class CATMapOfIntToInt;
class CATMapOfIntToPtr;


/**
 * Extracts all the mesh border loops = closed set of bars on the PolySurface boundaries.
 * 
 * This service works with all types of CATIPolyMesh, and doesn't suppose that
 * the mesh is a connex set of triangles associated to a parametric surface.
 * 
 * Each returned loop is a closed & ordered set of border vertices which associates one and only one next element to each border bar.
 * In case of Non Manifold border vertices (more than 2 incident border bars), the next element is chosen 
 * in respect with the triangle orientation (always on the left).
 * Then, a loop might be NonManifold, containing several times the same border vertex.
 * Keep in mind the ordered set of vertices describes in fact a set of ordered border bars !
 * 
 * The only condition to work is that all connected triangles have a consistent orientation in their neighbourhood :
 * if a bar is bounding 2 different triangles with the same side, the loops extraction fails !
 * 
 * Thanks to the "always on the left" specification, the result is predictable and guarantees the operation robustness.
 */
class ExportedByPolyMeshTools CATPolySurfaceBorderLoopsExtractor 
{

public:


  CATPolySurfaceBorderLoopsExtractor (const CATIPolyMesh & iMesh, CATIPolyMeshTriangleVertexIterator * iTriangleVertexIterator=NULL);

  ~CATPolySurfaceBorderLoopsExtractor ();


  /**
  * Border loops computation
  */
  HRESULT Run();

  /**
  * Returns the number of loops
  * @return
  *   An integer number of loops
  */
  inline int GetNbLoops();

  /**
  * Returns the number of bars/vertices in all the PolySurface boundaries
  * @return
  *   An integer number of vertices
  */
  inline int GetNbVerticesOnLoops();


public:

  class LoopVertexIterator;

  /**
  * Iterator to cycle through all the loops
  */
  class ExportedByPolyMeshTools LoopIterator
  {
  public:
    LoopIterator (const CATPolySurfaceBorderLoopsExtractor& iExtractor);
    ~LoopIterator () {}

    void Begin ();
    CATBoolean End () const;
    void operator++ ();

    /**
    * Returns the number of bars/vertices in the current loop
    * @return
    *   An integer number of vertices
    */
    int GetNbVertices() const;

    /**
    * Returns the Manifold status of the current loop
    * @return
    *   A boolean value :
    *   TRUE if the loop contains each vertex once and only once
    *   FALSE if the loop contains at least one vertex twice or more
    */
    CATBoolean IsLoopManifold() const;

  private:    

    friend class LoopVertexIterator;

    const CATListOfInt & _loopVertices;
    const CATListOfInt & _loopsSizes;
    const CATSetOfInt  & _loopsConnectionVtx;
    const CATListPV    & _loopsNMVtx; 

    unsigned int         _loopIdx;
    unsigned int         _vtxOffset;
  };


  /**
  * Iterator to cycle through all the vertices in the loop
  */
  class ExportedByPolyMeshTools LoopVertexIterator : public CATIPolySurfaceVertexIterator
  {
  public:
    LoopVertexIterator (const LoopIterator& iLoopIterator);
    ~LoopVertexIterator () {}

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
    * Returns the Manifold status of the current vertex in the context of the current loop
    * @return
    *   A boolean value :
    *   TRUE if the loop contains the vertex once and only once
    *   FALSE if the loop contains the vertex twice or more
    */
    CATBoolean IsVtxManifoldInLoop() const;

    /**
    * Returns the NonManifold Connection status of the current vertex regarding all the loops
    * @return
    *   A boolean value :
    *   TRUE if the vertex is connected to at least one other loop
    *   else FALSE
    */
    CATBoolean IsVtxConnectedToAnotherLoop() const;


    /**
    * Returns the current index.
    * @return
    *   An integer index.
    */
    int operator*();


  private:

    const LoopIterator & _loopIterator;
    const CATListOfInt & _loopVertices;
    unsigned int         _vertexIdx;
  };


private:

  HRESULT Run(CATIPolyMeshTriangleVertexIterator& iTriangleVertexIterator);

  // Build the map to get the third vertex from a border bar in its single adjacent triangle
  // -> each bar is recorded with V1 < V2
  // -> a null vertex index means the bar is not lying on the mesh boundary
  // -> a negative vertex index means the bar is negative versus its single triangle orientation
  HRESULT BuildBorderBarToV3Map(CATIPolyMeshTriangleVertexIterator & iTriangleVertexIterator, 
                                CATMapOfIntIntToInt &oBorderBarToV3Map) const;

  // Build the map to get the next border vertex from a border vertex
  // -> a null next vertex index means the border vertex is locally NonManifold (more than 2 incident free bars)
  // -> all border vertices (both manifold & non manifold) are recorded in the table
  // -> the oNonManifBdVtxList option leads to fill the list of non manifold vertices indexes
  HRESULT BuildNextBorderVtxMap(const CATMapOfIntIntToInt &iBorderBarToV3Map, 
                                CATMapOfIntToInt &oNextBorderVtxMap, CATBoolean &oManifoldDiag, CATListOfInt * oNonManifBdVtxList=0) const;

  // Build/Fill the map to get the next single border bar from a border bar
  // -> all border bars are recorded in the table with their single next border bar
  HRESULT BuildNextBorderBarMap(const CATMapOfIntIntToInt &iBorderBarToV3Map, const CATMapOfIntToInt &iNextBorderVtxMap, 
                                CATMapOfIntIntToInt &oNextBorderBarMap) const;
  HRESULT BuildNextBorderBarMap(CATIPolyMeshTriangleVertexIterator & iTriangleVertexIterator, const CATListOfInt & iNonManifoldBdVertices,
                                const CATMapOfIntToInt &iNextBorderVtxMap, CATMapOfIntIntToInt &oNextBorderBarMap) const;
  HRESULT FillNextBorderBarMap(const CATMapOfIntToInt &iNextBorderVtxMap, const CATMapOfIntToPtr &iNonManifBdVtxSectors,
                               CATMapOfIntIntToInt &oNextBorderBarMap) const;
  
  // Build the incident sectors around Non Manifold vertices thanks to the triangles iterator
  HRESULT BuildNonManifBdVtxSectors(CATIPolyMeshTriangleVertexIterator & iTriangleVertexIterator, const CATListOfInt & iNonManifoldBdVertices,
                                    CATMapOfIntToPtr &oNonManifBdVtxSectors) const;

  void Clean();


private:

  friend class LoopIterator;

  // Input
  const CATIPolyMesh                 & _Mesh;
  CATIPolyMeshTriangleVertexIterator * _TriangleVertexIterator;

  // Output
  CATListOfInt                         _LoopVertices; // all the border vertices which decribes ordered sets of free bars
  CATListOfInt                         _LoopSizes;    // gives the number of free bars in each loop, to interpret _LoopVertices as a list of subsets
  CATSetOfInt                          _LoopsConnectionVtx; // gives the NonManifold mesh border vertices which connect several loops to each other
  CATListPV                            _LoopNMVtx;    // gives the list of NonManifold vertices in each loop
};

// inline methods
// --------------
inline int CATPolySurfaceBorderLoopsExtractor::GetNbLoops() {
  return _LoopSizes.Size(); }

inline int CATPolySurfaceBorderLoopsExtractor::GetNbVerticesOnLoops() {
  return _LoopVertices.Size(); }


#endif


