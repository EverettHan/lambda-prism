// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyVertexFaceIterator
//
//=============================================================================
// 2009-11-03   NDO: Revisited implementation.
// 2007-07-10   BPG: New
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATPolyMicroTopologyFwd.h"
#include "CATPolyMacroTopologyFwd.h"

/**
 * Iterator through all the faces incident to a CATPolyVertex.
 * (once and only once). 
 *
 * Example:
 * \code
 * CATPolyVertexFaceIterator it;
 * for (it.Begin (MyVertex); !it.End (); ++it)
 * {
 *   CATPolyFace* face = it.GetFace ();   // Incident face.
 *   CATPolyCurve* curve = it.GetCurve ();
 * }
 * \endcode
 *
 * ** The iterator cycles through the faces once and only once. **
 * (For instance: case of non-manifold vertices.)
 *
 */
class ExportedByPolyMODEL CATPolyVertexFaceIterator
{

public:

  inline CATPolyVertexFaceIterator (CATPolyVertex* iVertex = 0);
  inline CATPolyVertexFaceIterator (const CATPolyVertexFaceIterator& iRHS);
  inline ~CATPolyVertexFaceIterator();

public:

  CATPolyVertexFaceIterator& Begin (CATPolyVertex* iVertex);
  inline CATPolyVertexFaceIterator& Begin (CATPolyVertex& iVertex);
  inline bool End () const;
  inline CATPolyVertexFaceIterator& operator++ ();

public:

  /**
   * Returns the face.  The iterator cycles though the faces once and only once.
   */
  inline CATPolyFace* GetFace () const;

  /**
   * Returns the underlying geometry associated to the vertex on this face.
   */
  inline CATIPolyPoint* GetPoint () const;

#ifndef _AIX_SOURCE
private:
#else
public:
#endif

  class VertexFaceIterator
  {
  public:
    virtual ~VertexFaceIterator () {}
    virtual void Begin (CATPolyVertex& iVertex) = 0;
    virtual bool End () const = 0;
    virtual void operator++ () = 0;
    virtual CATPolyFace* GetFace () const = 0;
    virtual CATIPolyPoint* GetPoint () const = 0;

    virtual VertexFaceIterator* Clone () const = 0;
  };

  VertexFaceIterator* _Iterator;

  template<class DART> friend class VertexFaceIteratorImpl;
};


inline CATPolyVertexFaceIterator::CATPolyVertexFaceIterator (CATPolyVertex* iVertex) :
  _Iterator (0)
{
  Begin (iVertex);
}

inline CATPolyVertexFaceIterator::CATPolyVertexFaceIterator (const CATPolyVertexFaceIterator& iRHS) :
  _Iterator (0)
{
  if (iRHS._Iterator)
    _Iterator = iRHS._Iterator->Clone ();
}

inline CATPolyVertexFaceIterator::~CATPolyVertexFaceIterator ()
{
  delete _Iterator;
  _Iterator = 0;
}

inline CATPolyVertexFaceIterator& CATPolyVertexFaceIterator::Begin (CATPolyVertex& iVertex)
{
  return Begin (&iVertex);
}

inline bool CATPolyVertexFaceIterator::End () const
{
  return _Iterator ? _Iterator->End () : true;
}

inline CATPolyVertexFaceIterator& CATPolyVertexFaceIterator::operator++ ()
{
  if (_Iterator)
    ++(*_Iterator);
  return *this;
}

inline CATPolyFace* CATPolyVertexFaceIterator::GetFace () const
{
  return _Iterator ? _Iterator->GetFace () : 0;
}

inline CATIPolyPoint* CATPolyVertexFaceIterator::GetPoint () const
{
  return _Iterator ? _Iterator->GetPoint () : 0;
}
