// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyVertexPointIterator
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
 * Iterator through all the points incident to a CATPolyVertex.
 * (Once and only once.)
 *
 * Example:
 * \code
 * CATPolyVertexPointIterator it;
 * for (it.Begin (MyVertex); !it.End (); ++it)
 * {
 *   CATPolyPoint* Point = it.GetPoint();
 * }
 * \endcode
 *
 */
class ExportedByPolyMODEL CATPolyVertexPointIterator
{

public:

  inline CATPolyVertexPointIterator (CATPolyVertex* iVertex = 0);
  inline CATPolyVertexPointIterator (const CATPolyVertexPointIterator& iRHS);
  inline ~CATPolyVertexPointIterator ();

public:

  CATPolyVertexPointIterator& Begin (CATPolyVertex* iVertex);
  inline CATPolyVertexPointIterator& Begin (CATPolyVertex& iVertex);
  inline bool End () const;
  inline CATPolyVertexPointIterator& operator++ ();

public:

  inline CATIPolyPoint* GetPoint () const;
  inline CATIPolyCurve* GetCurve () const;

  inline CATPolyEdge* GetEdge () const;
  inline CATPolyFace* GetFace () const;

#ifndef _AIX_SOURCE
private:
#else
public:
#endif

  class VertexPointIterator
  {
  public:
    virtual ~VertexPointIterator () {}
    virtual void Begin (CATPolyVertex& iVertex) = 0;
    virtual bool End () const = 0;
    virtual void operator++ () = 0;
    virtual CATIPolyPoint* GetPoint () const = 0;
    virtual CATIPolyCurve* GetCurve () const = 0;
    virtual CATPolyEdge* GetEdge () const = 0;
    virtual CATPolyFace* GetFace () const = 0;

    virtual VertexPointIterator* Clone () const = 0;
  };

  VertexPointIterator* _Iterator;

  template<class DART> friend class VertexPointIteratorImpl;
};

inline CATPolyVertexPointIterator::CATPolyVertexPointIterator (CATPolyVertex* iVertex) :
  _Iterator (0)
{
  Begin (iVertex);
}

inline CATPolyVertexPointIterator::CATPolyVertexPointIterator (const CATPolyVertexPointIterator& iRHS) :
  _Iterator (0)
{
  if (iRHS._Iterator)
    _Iterator = iRHS._Iterator->Clone ();
}

inline CATPolyVertexPointIterator::~CATPolyVertexPointIterator ()
{
  delete _Iterator;
  _Iterator = 0;
}

inline CATPolyVertexPointIterator& CATPolyVertexPointIterator::Begin (CATPolyVertex& iVertex)
{
  return Begin (&iVertex);
}

inline bool CATPolyVertexPointIterator::End () const
{
  return _Iterator ? _Iterator->End () : true;
}

inline CATPolyVertexPointIterator& CATPolyVertexPointIterator::operator++ ()
{
  if (_Iterator)
    ++(*_Iterator);
  return *this;
}

inline CATIPolyPoint* CATPolyVertexPointIterator::GetPoint () const
{
  return _Iterator ? _Iterator->GetPoint () : 0;
}

inline CATIPolyCurve* CATPolyVertexPointIterator::GetCurve () const
{
  return _Iterator ? _Iterator->GetCurve () : 0;
}

inline CATPolyEdge* CATPolyVertexPointIterator::GetEdge () const
{
  return _Iterator ? _Iterator->GetEdge () : 0;
}

inline CATPolyFace* CATPolyVertexPointIterator::GetFace () const
{
  return _Iterator ? _Iterator->GetFace () : 0;
}
