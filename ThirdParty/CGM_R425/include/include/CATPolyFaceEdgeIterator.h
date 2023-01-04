// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyFaceEdgeIterator
//
//=============================================================================
// 2009-11-03   NDO: Revisited implementation.
// 2007-07-10   BPG: New
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATPolyMicroTopologyFwd.h"
#include "CATPolyMacroTopologyFwd.h"

// Before removing the following two lines check the frameworks: GeometryVisualization and SMAHvsEngine
#include "CATPolyFace.h"  // Check CATPolyBodyToUVConverter.cpp and SMAHvsVwrDecimateTools.cpp before removing this line.
#include "CATPolyEdge.h"  // Check CATPolyBodyToUVConverter.cpp and SMAHvsVwrDecimateTools.cpp before removing this line.


/**
* Iterates through all the edges of a CATPolyFace.
*
* Example:
* \code
* CATPolyFaceEdgeIterator it;
* for (it.Begin (MyFace); !it.End (); ++it)
* {
*   CATPolyEdge* E = it.GetEdge ();
*   CATPolyCurve* C = it.GetCurve ();
* }
* \endcode
*
*/
class ExportedByPolyMODEL CATPolyFaceEdgeIterator
{

public:

  inline CATPolyFaceEdgeIterator (CATPolyFace* iFace = 0);
  inline ~CATPolyFaceEdgeIterator ();

public:

  CATPolyFaceEdgeIterator& Begin (CATPolyFace* iFace);
  inline CATPolyFaceEdgeIterator& Begin (CATPolyFace& iFace);
  inline bool End () const;
  inline CATPolyFaceEdgeIterator& operator++ ();

public:

  /**
   * Returns the edge.  The iterator cycles though the edges once and only once.
   */
  CATPolyEdge* GetEdge () const;

  /**
   * Returns the underlying geometry associated to the edge on this face.
   */
  CATIPolyCurve* GetCurve () const;

#ifndef _AIX_SOURCE
private:
#else
public:
#endif

  class FaceEdgeIterator
  {
  public:
    virtual ~FaceEdgeIterator () {}
    virtual void Begin (CATPolyFace& iFace) = 0;
    virtual bool End () const = 0;
    virtual void operator++ () = 0;
    virtual CATPolyEdge* GetEdge () const = 0;
    virtual CATIPolyCurve* GetCurve () const = 0;

    //virtual FaceEdgeIterator* Clone () const = 0;
  };

  FaceEdgeIterator* _Iterator;

  template<class DART> friend class FaceEdgeIteratorImpl;
};

inline CATPolyFaceEdgeIterator::CATPolyFaceEdgeIterator (CATPolyFace* iFace) :
  _Iterator (0)
{
  Begin (iFace);
}

inline CATPolyFaceEdgeIterator::~CATPolyFaceEdgeIterator ()
{
  delete _Iterator;
  _Iterator = 0;
}

inline CATPolyFaceEdgeIterator& CATPolyFaceEdgeIterator::Begin (CATPolyFace& iFace)
{
  return Begin (&iFace);
}

inline bool CATPolyFaceEdgeIterator::End () const
{
  return _Iterator ? _Iterator->End () : true;
}

inline CATPolyFaceEdgeIterator& CATPolyFaceEdgeIterator::operator++ ()
{
  if (_Iterator)
    ++(*_Iterator);
  return *this;
}

inline CATPolyEdge* CATPolyFaceEdgeIterator::GetEdge () const
{
  return _Iterator ? _Iterator->GetEdge () : 0;
}

inline CATIPolyCurve* CATPolyFaceEdgeIterator::GetCurve () const
{
  return _Iterator ? _Iterator->GetCurve () : 0;
}
