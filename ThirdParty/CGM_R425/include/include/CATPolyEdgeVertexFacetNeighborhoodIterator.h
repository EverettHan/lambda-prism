//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyEdgeVertexFacetNeighborhoodIterator
//
// Iterate over the micro facet neighboring of an edge-vertex, crossing
// macro-topology. Usage:
//
// void
// DoSomethingOnEachNeighboringFacetCrossMacroTopology(CATIPolySurface &iSurface, int v)
// {
//   CATIPolySurfaceVertexCellLayer *VertexCellLayer = iSurface.GetVertexCellLayer();  // Obsolete.
//
//   if (VertexCellLayer)
//   {
//     CATPolyCell *Cell = 0;
//     int EdgeVertex = 0;
//
//     if (S_OK == VertexCellLayer.Get(v, Cell, EdgeVertex) && Cell)
//     {
//       CATPolyEdge *Edge = Cell.CastInEdge();
//       if (Edge)
//         for (CATPolyEdgeVertexFacetNeighborhoodIterator it(*Edge, EdgeVertex); !it.End(); ++it)
//         {
//           CATPolyFace *BoundedFace = it.GetFace();
//           CATListOfInt FacetNeighborhood;
//           it.GetFacetNeighborhood(FacetNeighborhood);
//
//           CATIPolySurface *Surface = BoundedFace.GetSurface();
//
//           DoSomething(*Surface, FacetNeighborhood);
//         }
//     }
//   }
// }
//
//=============================================================================
// 2007-07-10   BPG: New
//=============================================================================
#ifndef CATPolyEdgeVertexFacetNeighborhoodIterator_H
#define CATPolyEdgeVertexFacetNeighborhoodIterator_H

#include "PolyMODEL.h"

#include "CATErrorDef.h"
#include "CATListOfInt.h"

#include "CATPolyEdgeFaceIterator.h"
#include "CATIPolySurfaceVertexFacetNeighborhood.h"

#include "CATPolyMicroTopologyFwd.h"
#include "CATPolyMacroTopologyFwd.h"

class ExportedByPolyMODEL CATPolyEdgeVertexFacetNeighborhoodIterator
{
public:
  inline CATPolyEdgeVertexFacetNeighborhoodIterator();
  inline CATPolyEdgeVertexFacetNeighborhoodIterator(CATPolyEdge &iEdge, int iEdgeVertex);

  inline ~CATPolyEdgeVertexFacetNeighborhoodIterator();

public:
  CATPolyEdgeVertexFacetNeighborhoodIterator &Begin(CATPolyEdge &iEdge, int iEdgeVertex);
  inline CATBoolean End() const;

  CATPolyEdgeVertexFacetNeighborhoodIterator &operator++();

public:
  inline const CATPolyEdge *GetEdge() const;
  inline CATPolyEdge *GetEdge();

public:
  inline const CATPolyFace *GetFace() const;
  inline CATPolyFace *GetFace();

  inline int GetFaceVertex() const;

  inline HRESULT GetFacetNeighborhood(CATListOfInt &oNeighbors) const;


protected:
  void UpdateInternalData();

protected:
  CATPolyEdge *_Edge;
  int _EdgeVertex;

  CATPolyEdgeFaceIterator _EdgeFaceIterator;

  int _FaceVertex;
  CATIPolySurfaceVertexFacetNeighborhood *_FacetNeighborhood;
};

// ----------------------------------------------------------------------------

//
inline
CATPolyEdgeVertexFacetNeighborhoodIterator::CATPolyEdgeVertexFacetNeighborhoodIterator():
  _Edge(0), _EdgeVertex(0),
  _FaceVertex(0), _FacetNeighborhood(0)
{}

inline
CATPolyEdgeVertexFacetNeighborhoodIterator::CATPolyEdgeVertexFacetNeighborhoodIterator(CATPolyEdge &iEdge, int iEdgeVertex):
  _Edge(&iEdge), _EdgeVertex(iEdgeVertex),
  _FaceVertex(0), _FacetNeighborhood(0)
{
  Begin(iEdge, iEdgeVertex);
}

inline
CATPolyEdgeVertexFacetNeighborhoodIterator::~CATPolyEdgeVertexFacetNeighborhoodIterator()
{
  _Edge = 0;
  if (_FacetNeighborhood)
  {
    _FacetNeighborhood->Release();
    _FacetNeighborhood = 0;
  }
}

//
inline CATBoolean
CATPolyEdgeVertexFacetNeighborhoodIterator::End() const
{
  return _FacetNeighborhood == 0;
}

//
inline const CATPolyEdge *
CATPolyEdgeVertexFacetNeighborhoodIterator::GetEdge() const
{
  return _Edge;
}
inline CATPolyEdge *
CATPolyEdgeVertexFacetNeighborhoodIterator::GetEdge()
{
  return _Edge;
}

inline const CATPolyFace *
CATPolyEdgeVertexFacetNeighborhoodIterator::GetFace() const
{
  return _EdgeFaceIterator.End() ? 0 : _EdgeFaceIterator.GetFace();
}
inline CATPolyFace *
CATPolyEdgeVertexFacetNeighborhoodIterator::GetFace()
{
  return _EdgeFaceIterator.End() ? 0 : _EdgeFaceIterator.GetFace();
}

inline int
CATPolyEdgeVertexFacetNeighborhoodIterator::GetFaceVertex() const
{
  return _FaceVertex;
}

inline HRESULT
CATPolyEdgeVertexFacetNeighborhoodIterator::GetFacetNeighborhood(CATListOfInt &oNeighbors) const
{
  return _FacetNeighborhood ? _FacetNeighborhood->GetFacetNeighborsOfVertex (_FaceVertex, oNeighbors) : E_FAIL;
}

#endif // !CATPolyEdgeVertexFacetNeighborhoodIterator_H
