// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyVertexEdgeIterator
//
//=============================================================================
// 2018-12-07   NDO: Revisited implementation.  (Usage of CATPolyDartOrbit12 iterator.)
// 2007-07-10   BPG: New
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATPolyMicroTopologyFwd.h"
#include "CATPolyMacroTopologyFwd.h"

/**
 * Iterator through the edges incident to a vertex
 * (once and only once).
 *
 * Example:
 * \code
 *  CATPolyVertexEdgeIterator it;
 *  for (it.Begin (MyVertex); !it.End (); ++it)
 *  {
 *    CATPolyEdge* E = it.GetEdge ();
 *    CATIPolyPoint* P = it.GetPoint ();
 *  }
 * \endcode
 *
 */
class ExportedByPolyMODEL CATPolyVertexEdgeIterator
{

public:

  inline CATPolyVertexEdgeIterator (CATPolyVertex* iVertex = 0);
  inline CATPolyVertexEdgeIterator (const CATPolyVertexEdgeIterator& iRHS);
  inline ~CATPolyVertexEdgeIterator ();

public:

  CATPolyVertexEdgeIterator& Begin (CATPolyVertex* iVertex);
  inline CATPolyVertexEdgeIterator& Begin (CATPolyVertex& iVertex);
  inline bool End () const;
  inline CATPolyVertexEdgeIterator& operator++ ();

public:

  inline CATPolyEdge* GetEdge () const;
  inline CATIPolyPoint* GetPoint () const;

#ifndef _AIX_SOURCE
private:
#else
public:
#endif

  class VertexEdgeIterator
  {
  public:
    virtual ~VertexEdgeIterator () {}
    virtual void Begin (CATPolyVertex& iVertex) = 0;
    virtual bool End () const = 0;
    virtual void operator++ () = 0;
    virtual CATPolyEdge* GetEdge () const = 0;
    virtual CATIPolyPoint* GetPoint () const = 0;

    virtual VertexEdgeIterator* Clone () const = 0;
  };

  VertexEdgeIterator* _Iterator;

  template<class DART> friend class VertexEdgeIteratorImpl;
};

inline CATPolyVertexEdgeIterator::CATPolyVertexEdgeIterator (CATPolyVertex* iVertex) :
  _Iterator (0)
{
  Begin (iVertex);
}

inline CATPolyVertexEdgeIterator::CATPolyVertexEdgeIterator (const CATPolyVertexEdgeIterator& iRHS) :
  _Iterator (0)
{
  if (iRHS._Iterator)
    _Iterator = iRHS._Iterator->Clone ();
}

inline CATPolyVertexEdgeIterator::~CATPolyVertexEdgeIterator ()
{
  delete _Iterator;
  _Iterator = 0;
}

inline CATPolyVertexEdgeIterator& CATPolyVertexEdgeIterator::Begin (CATPolyVertex& iVertex)
{
  return Begin (&iVertex);
}

inline bool CATPolyVertexEdgeIterator::End () const
{
  return _Iterator ? _Iterator->End () : true;
}

inline CATPolyVertexEdgeIterator& CATPolyVertexEdgeIterator::operator++ ()
{
  if (_Iterator)
    ++(*_Iterator);
  return *this;
}

inline CATPolyEdge* CATPolyVertexEdgeIterator::GetEdge () const
{
  return _Iterator ? _Iterator->GetEdge () : 0;
}

inline CATIPolyPoint* CATPolyVertexEdgeIterator::GetPoint () const
{
  return _Iterator ? _Iterator->GetPoint () : 0;
}
