//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyVertexFacetNeighborhoodIterator
//
//=============================================================================
// 2007-07-10   BPG: New
//=============================================================================
#ifndef CATPolyVertexFacetNeighborhoodIterator_H
#define CATPolyVertexFacetNeighborhoodIterator_H

#include "PolyMODEL.h"
#include "CATErrorDef.h"
#include "CATListOfInt.h"
#include "CATPolyVertexFaceIterator.h"
#include "CATIPolySurfaceVertexFacetNeighborhood.h"

#include "CATPolyMicroTopologyFwd.h"
#include "CATPolyMacroTopologyFwd.h"


/**
 * Iterator through all the facets from the faces incident to a CATPolyVertex 
 * and referring this vertex.
 *
 * Example:
 * \code
 * void DoSomethingWithFacetsIncidentToPolyVertex (CATPolyFace& F, int sv)
 * {
 *   CATIPolySurfaceVertexCellConstLayer* VertexCellLayer = F.GetVertexCellConstLayer ();
 *
 *   if (VertexCellLayer)
 *   {
 *     CATPolyCell* Cell = 0;
 *     int VertexCell = 0;
 *     if (S_OK == VertexCellLayer.Get (v, Cell, VertexCell) && Cell)
 *     {
 *       CATPolyVertex* Vertex = CATPolyVertex::Cast (Cell);
 *       if (Vertex)
 *       {
 *         for (CATPolyVertexFacetNeighborhoodIterator it (*Vertex); !it.End (); ++it)
 *         {
 *           CATPolyFace *BoundedFace = it.GetFace();
 *           CATListOfInt FacetNeighborhood;
 *           it.GetFacetNeighborhood (FacetNeighborhood);
 *           CATIPolySurface* Surface = BoundedFace.GetSurface ();
 *           DoSomething (Surface, FacetNeighborhood);
 *         }
 *       }
 *     }
 *   }
 * }
 * \endcode
 */
class ExportedByPolyMODEL CATPolyVertexFacetNeighborhoodIterator
{

public:

  inline CATPolyVertexFacetNeighborhoodIterator();
  inline CATPolyVertexFacetNeighborhoodIterator(CATPolyVertex &iVertex);

  inline ~CATPolyVertexFacetNeighborhoodIterator();

public:

  CATPolyVertexFacetNeighborhoodIterator &Begin(CATPolyVertex &iVertex);
  inline bool End () const;
  CATPolyVertexFacetNeighborhoodIterator &operator++();

public:

  inline CATPolyVertex* GetVertex () const;
  inline CATPolyFace* GetFace () const;

  inline int GetFaceVertex() const;

  inline HRESULT GetFacetNeighborhood(CATListOfInt &oNeighbors) const;

private:

  CATPolyVertex *_Vertex;

  CATPolyVertexFaceIterator _VertexFaceIterator;

  int _FaceVertex;
  CATIPolySurfaceVertexFacetNeighborhood *_FacetNeighborhood;

private:

  void UpdateInternalData ();

};

inline CATPolyVertexFacetNeighborhoodIterator::CATPolyVertexFacetNeighborhoodIterator():
  _Vertex(0),
  _FaceVertex(0), _FacetNeighborhood(0)
{
}

inline CATPolyVertexFacetNeighborhoodIterator::CATPolyVertexFacetNeighborhoodIterator(CATPolyVertex &iVertex):
  _Vertex(&iVertex)
{
  Begin(iVertex);
}

inline CATPolyVertexFacetNeighborhoodIterator::~CATPolyVertexFacetNeighborhoodIterator()
{
  _Vertex = 0;
  if (_FacetNeighborhood)
  {
    _FacetNeighborhood->Release();
    _FacetNeighborhood = 0;
  }
}

inline bool CATPolyVertexFacetNeighborhoodIterator::End() const
{
  return _FacetNeighborhood == 0;
}

inline CATPolyVertex* CATPolyVertexFacetNeighborhoodIterator::GetVertex () const
{
  return _Vertex;
}

inline CATPolyFace* CATPolyVertexFacetNeighborhoodIterator::GetFace () const
{
  return _VertexFaceIterator.End() ? 0 : _VertexFaceIterator.GetFace();
}

inline int CATPolyVertexFacetNeighborhoodIterator::GetFaceVertex() const
{
  return _FaceVertex;
}

inline HRESULT CATPolyVertexFacetNeighborhoodIterator::GetFacetNeighborhood(CATListOfInt &oNeighbors) const
{
  return _FacetNeighborhood ? _FacetNeighborhood->GetFacetNeighborsOfVertex (_FaceVertex, oNeighbors) : E_FAIL;
}

#endif // !CATPolyVertexFacetNeighborhoodIterator_H
