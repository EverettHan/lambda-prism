// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyFaceLoopEdgeIterator
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
 * This iterator cycles through the edges around the loop once and only once.
 */
class ExportedByPolyMODEL CATPolyFaceLoopEdgeIterator
{

public:

  inline CATPolyFaceLoopEdgeIterator (const CATPolyFaceLoop* L = 0);
  inline ~CATPolyFaceLoopEdgeIterator ();

public:

  inline CATPolyFaceLoopEdgeIterator& Begin ();
  CATPolyFaceLoopEdgeIterator& Begin (const CATPolyFaceLoop* L);
  inline CATPolyFaceLoopEdgeIterator& Begin (const CATPolyFaceLoop& L);
  inline bool End () const;
  inline CATPolyFaceLoopEdgeIterator& operator++ ();

public:

  /**
   * Returns the current edge.
   */
  inline CATPolyEdge* operator* () const;

  /**
   * Returns the current edge.
   */
  inline CATPolyEdge* GetEdge () const;

  /**
   * Returns the surface-vertex line associated to the current edge on this face.
   */
  inline CATIPolySurfaceVertexLine* GetSurfaceVertexLine () const;

  /**
   * Returns a vertex from the edge in the sequence of the edges around the loop.
   * @param k
   *   0 or 1
   */
  inline CATPolyVertex* GetVertex (unsigned int k) const;

  /**
   * Returns a vertex from the edge in the sequence of the edges around the loop.
   */
  inline CATPolyVertex* GetVertex () const { return GetVertex (0); }

  /**
   * Returns the surface-vertex associated to the matching vertex seen from the edge and the face.
   * See GetVertex (unsigned int k) above.
   * @param k
   *   0 or 1
   */
  inline CATIPolySurfaceVertex* GetSurfaceVertex (unsigned int k) const;

  /**
   * Returns the surface-vertex associated to the current vertex seen from the edge and the face.
   */
  inline CATIPolySurfaceVertex* GetSurfaceVertex () const { return GetSurfaceVertex (0); }

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

  class FaceLoopEdgeIterator
  {
  public:
    virtual ~FaceLoopEdgeIterator () {}
    virtual bool End () const = 0;
    virtual void operator++ () = 0;
    virtual CATPolyEdge* GetEdge () const = 0;
    virtual CATIPolySurfaceVertexLine* GetSurfaceVertexLine () const = 0;
    virtual CATPolyVertex* GetVertex (unsigned int i) const = 0;
    virtual CATIPolySurfaceVertex* GetSurfaceVertex (unsigned int i) const = 0;
    virtual CATPolyFace* GetAdjacentFace () const = 0;

    //virtual FaceLoopEdgeIterator* Clone () const = 0;
  };

  CATPolyFaceLoop _FaceLoop;
  FaceLoopEdgeIterator* _Iterator;

  template<class DART> friend class FaceLoopEdgeIteratorImpl;
};


inline CATPolyFaceLoopEdgeIterator::CATPolyFaceLoopEdgeIterator (const CATPolyFaceLoop* L) :
  _Iterator (0)
{
  Begin (L);
}

inline CATPolyFaceLoopEdgeIterator::~CATPolyFaceLoopEdgeIterator ()
{
  delete _Iterator;
  _Iterator = 0;
}

inline CATPolyFaceLoopEdgeIterator& CATPolyFaceLoopEdgeIterator::Begin ()
{
  return Begin (&_FaceLoop);
}

inline CATPolyFaceLoopEdgeIterator& CATPolyFaceLoopEdgeIterator::Begin (const CATPolyFaceLoop& L)
{
  return Begin (&L);
}

inline bool CATPolyFaceLoopEdgeIterator::End () const
{
  return _Iterator ? _Iterator->End () : true;
}

inline CATPolyFaceLoopEdgeIterator& CATPolyFaceLoopEdgeIterator::operator++ ()
{
  if (_Iterator)
    ++(*_Iterator);
  return *this;
}

inline CATPolyEdge* CATPolyFaceLoopEdgeIterator::operator* () const
{
  return _Iterator ? _Iterator->GetEdge () : 0;
}

inline CATPolyEdge* CATPolyFaceLoopEdgeIterator::GetEdge () const
{
  return _Iterator ? _Iterator->GetEdge () : 0;
}

inline CATIPolySurfaceVertexLine* CATPolyFaceLoopEdgeIterator::GetSurfaceVertexLine () const
{
  return _Iterator ? _Iterator->GetSurfaceVertexLine () : 0;
}

inline CATPolyVertex* CATPolyFaceLoopEdgeIterator::GetVertex (unsigned int i) const
{
  return _Iterator ? _Iterator->GetVertex (i) : 0;
}

inline CATIPolySurfaceVertex* CATPolyFaceLoopEdgeIterator::GetSurfaceVertex (unsigned int i) const
{
  return _Iterator ? _Iterator->GetSurfaceVertex (i) : 0;
}

inline CATPolyFace* CATPolyFaceLoopEdgeIterator::GetAdjacentFace () const
{
  return _Iterator ? _Iterator->GetAdjacentFace () : 0;
}
