// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyEdgeCurveIterator
//
//=============================================================================
// 2009-11-03   NDO: Revisited implementation.
// 2007-01-03   BPG: New
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATPolyMicroTopologyFwd.h"
#include "CATPolyMacroTopologyFwd.h"


/**
 * Iterator through all the curves incident to a CATPolyEdge.
 * (Once and only once.)
 *
 * Example:
 * \code
 * CATPolyEdgeCurveIterator it;
 * for (it.Begin (MyEdge); !it.End (); ++it)
 * {
 *   CATPolyFace* face = it.GetFace ();   // Incident face.
 *   CATPolyCurve* curve = it.GetCurve ();  // Incident curve.
 * }
 * \endcode
 *
 */
class ExportedByPolyMODEL CATPolyEdgeCurveIterator
{

public:

  inline CATPolyEdgeCurveIterator (CATPolyEdge* iEdge = 0);
  inline CATPolyEdgeCurveIterator (const CATPolyEdgeCurveIterator& iRHS);
  inline ~CATPolyEdgeCurveIterator ();

public:

  CATPolyEdgeCurveIterator& Begin (CATPolyEdge* iEdge);
  inline CATPolyEdgeCurveIterator& Begin (CATPolyEdge& iEdge);
  inline bool End () const;
  inline CATPolyEdgeCurveIterator& operator++ ();

public:

  /**
   * Returns the incident face. (May be null.)
   */
  inline CATPolyFace* GetFace () const;

  /**
   * Returns the incident curve.
   */
  inline CATIPolyCurve* GetCurve () const;

#ifndef _AIX_SOURCE
private:
#else
public:
#endif

  class EdgeCurveIterator
  {
  public:
    virtual ~EdgeCurveIterator () {}
    virtual void Begin (CATPolyEdge& iEdge) = 0;
    virtual bool End () const = 0;
    virtual void operator++ () = 0;
    virtual CATPolyFace* GetFace () const = 0;
    virtual CATIPolyCurve* GetCurve () const = 0;

    virtual EdgeCurveIterator* Clone () const = 0;
  };

  EdgeCurveIterator* _Iterator;

  template<class DART> friend class EdgeCurveIteratorImpl;
};


inline CATPolyEdgeCurveIterator::CATPolyEdgeCurveIterator (CATPolyEdge* iEdge) :
  _Iterator (0)
{
  Begin (iEdge);
}

inline CATPolyEdgeCurveIterator::CATPolyEdgeCurveIterator (const CATPolyEdgeCurveIterator& iRHS) :
  _Iterator (0)
{
  if (iRHS._Iterator)
    _Iterator = iRHS._Iterator->Clone ();
}

inline CATPolyEdgeCurveIterator::~CATPolyEdgeCurveIterator ()
{
  delete _Iterator;
  _Iterator = 0;
}

inline CATPolyEdgeCurveIterator& CATPolyEdgeCurveIterator::Begin (CATPolyEdge& iEdge)
{
  return Begin (&iEdge);
}

inline bool CATPolyEdgeCurveIterator::End () const
{
  return _Iterator ? _Iterator->End () : true;
}

inline CATPolyEdgeCurveIterator& CATPolyEdgeCurveIterator::operator++ ()
{
  if (_Iterator)
    ++(*_Iterator);
  return *this;
}

inline CATPolyFace* CATPolyEdgeCurveIterator::GetFace () const
{
  return _Iterator ? _Iterator->GetFace () : 0;
}

inline CATIPolyCurve* CATPolyEdgeCurveIterator::GetCurve () const
{
  return _Iterator ? _Iterator->GetCurve () : 0;
}
