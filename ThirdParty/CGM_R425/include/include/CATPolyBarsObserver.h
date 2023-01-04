// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarsObserver.h
// Header definition of CATPolyBarsObserver
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// November 2007 Creation: ndo
//===================================================================
#ifndef CATPolyBarsObserver_H
#define CATPolyBarsObserver_H

#include "PolyMeshImpl.h"
#include "CATPolyRefCounted.h"
#include "CATErrorDef.h"     // HRESULT definition (for compil under UNIX)

class CATPolyBars;


/**
* Observer base class for CATPolyBars objects. 
*/
class ExportedByPolyMeshImpl CATPolyBarsObserver : public CATPolyRefCounted
{

public :

  CATPolyBarsObserver ();
  virtual ~CATPolyBarsObserver ();

public:

  // Listening to bar events.

  // Call made after a bar is added.
  virtual HRESULT ReactToAddBar (const int vertex0, const int vertex1, const int bar);

  // Call made before a bar is removed.
  virtual HRESULT PrepareToRemoveBar (const int bar);

public:

  // Call made before two vertices are merged.
  virtual HRESULT PrepareToMergeVertices (const int v0, const int v1);

protected:

  friend class CATPolyBars;

  CATPolyBarsObserver* _Prev;
  CATPolyBarsObserver* _Next;

protected:

  inline CATPolyBarsObserver* Prev () const;
  inline CATPolyBarsObserver* Next () const;

  inline void SetPrev (CATPolyBarsObserver* prev);
  inline void SetNext (CATPolyBarsObserver* next);

};


inline CATPolyBarsObserver* CATPolyBarsObserver::Prev () const
{
  return _Prev;
}

inline CATPolyBarsObserver* CATPolyBarsObserver::Next () const
{
  return _Next;
}

inline void CATPolyBarsObserver::SetPrev (CATPolyBarsObserver* prev)
{
  _Prev = prev;
}

inline void CATPolyBarsObserver::SetNext (CATPolyBarsObserver* next)
{
  _Next = next;
}

#endif
