// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyFaceLoopVertexEdgeIterator
//
//=============================================================================
// May 2019 - NDO
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATPolyMicroTopologyFwd.h"
#include "CATPolyMacroTopologyFwd.h"
#include "CATPolyFaceLoop.h"


/**
 * Iterator through all the edges around a face loop.
 * This iterator cycles through the vertices and edges around the loop.
 * A face-loop could consist of just a vertex without an edge.
 */
class ExportedByPolyMODEL CATPolyFaceLoopVertexEdgeIterator
{

public:

  inline CATPolyFaceLoopVertexEdgeIterator (const CATPolyFaceLoop* L = 0);
  inline ~CATPolyFaceLoopVertexEdgeIterator ();

public:

  inline CATPolyFaceLoopVertexEdgeIterator& Begin ();
  CATPolyFaceLoopVertexEdgeIterator& Begin (const CATPolyFaceLoop* L);
  inline CATPolyFaceLoopVertexEdgeIterator& Begin (const CATPolyFaceLoop& L);
  inline bool End () const;
  inline CATPolyFaceLoopVertexEdgeIterator& operator++ ();

public:

  /**
   * Returns the current vertex.
   * If there is a current edge, this is the extremity of the edge in the loop direction.
   */
  inline CATPolyVertex* GetVertex () const;

  /**
   * Returns the current edge. It may be null.
   */
  inline CATPolyEdge* GetEdge () const;

  /**
   * Returns the surface-vertex line associated to the current edge on this face.
   */
  inline CATIPolySurfaceVertexLine* GetSurfaceVertexLine () const;

  /**
   * Returns the surface-vertex associated to the current vertex seen from the edge and the face.
   */
  inline CATIPolySurfaceVertex* GetSurfaceVertex () const;

  /**
   * Returns the adjacent face through the manifold edge (may be null.)
   * The edge may be non-manifold but there is only one face adjacent to
   * to the input face via the manifold edge.
   */
  inline CATPolyFace* GetAdjacentFace () const;

#ifndef _AIX_SOURCE
private:
#else
public:
#endif

  class FaceLoopVertexEdgeIterator
  {
  public:
    virtual ~FaceLoopVertexEdgeIterator () {}
    virtual bool End () const = 0;
    virtual void operator++ () = 0;
    virtual CATPolyVertex* GetVertex () const = 0;
    virtual CATPolyEdge* GetEdge () const = 0;
    virtual CATIPolySurfaceVertexLine* GetSurfaceVertexLine () const = 0;
    virtual CATIPolySurfaceVertex* GetSurfaceVertex () const = 0;
    virtual CATPolyFace* GetAdjacentFace () const = 0;

    //virtual FaceLoopVertexEdgeIterator* Clone () const = 0;
  };

  CATPolyFaceLoop _FaceLoop;
  FaceLoopVertexEdgeIterator* _Iterator;

  template<class DART> friend class FaceLoopVertexEdgeIteratorImpl;

};


inline CATPolyFaceLoopVertexEdgeIterator::CATPolyFaceLoopVertexEdgeIterator (const CATPolyFaceLoop* L) :
  _Iterator (0)
{
  Begin (L);
}

inline CATPolyFaceLoopVertexEdgeIterator::~CATPolyFaceLoopVertexEdgeIterator ()
{
  delete _Iterator;
  _Iterator = 0;
}

inline CATPolyFaceLoopVertexEdgeIterator& CATPolyFaceLoopVertexEdgeIterator::Begin ()
{
  return Begin (&_FaceLoop);
}

inline CATPolyFaceLoopVertexEdgeIterator& CATPolyFaceLoopVertexEdgeIterator::Begin (const CATPolyFaceLoop& L)
{
  return Begin (&L);
}

inline bool CATPolyFaceLoopVertexEdgeIterator::End () const
{
  return _Iterator ? _Iterator->End () : true;
}

inline CATPolyFaceLoopVertexEdgeIterator& CATPolyFaceLoopVertexEdgeIterator::operator++ ()
{
  if (_Iterator)
    ++(*_Iterator);
  return *this;
}

inline CATPolyVertex* CATPolyFaceLoopVertexEdgeIterator::GetVertex () const
{
  return _Iterator ? _Iterator->GetVertex () : 0;
}

inline CATPolyEdge* CATPolyFaceLoopVertexEdgeIterator::GetEdge () const
{
  return _Iterator ? _Iterator->GetEdge () : 0;
}

inline CATIPolySurfaceVertexLine* CATPolyFaceLoopVertexEdgeIterator::GetSurfaceVertexLine () const
{
  return _Iterator ? _Iterator->GetSurfaceVertexLine () : 0;
}

inline CATIPolySurfaceVertex* CATPolyFaceLoopVertexEdgeIterator::GetSurfaceVertex () const
{
  return _Iterator ? _Iterator->GetSurfaceVertex () : 0;
}

inline CATPolyFace* CATPolyFaceLoopVertexEdgeIterator::GetAdjacentFace () const
{
  return _Iterator ? _Iterator->GetAdjacentFace () : 0;
}
