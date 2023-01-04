// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarsMeshObserver.h
// Header definition of CATPolyBarsMeshObserver
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// February 2008 Creation: ndo
//===================================================================
#ifndef CATPolyBarsMeshObserver_H
#define CATPolyBarsMeshObserver_H

#include "PolyMeshImpl.h"
#include "CATIPolyMeshObserver.h"
#include "CATErrorDef.h"     // HRESULT definition (for compil under UNIX)
#include "CATBoolean.h"

class CATPolyBars;


/**
* Class observing mesh events to update a CATPolyBars object. 
*/
class ExportedByPolyMeshImpl CATPolyBarsMeshObserver : public CATIPolyMeshObserver
{

public:

  CATPolyBarsMeshObserver (CATPolyBars& iBars);
  virtual ~CATPolyBarsMeshObserver ();

public:

  // Listening to vertex events.
  virtual HRESULT PrepareToRemoveVertex (int v);

public:

  // Listening to split bar event.
  virtual HRESULT ReactToSplitBar (int v0, int v1, int n);

  // Listening to merge vertices event.
  virtual HRESULT PrepareToMergeVertices (int v0, int v1);

public:

  inline HRESULT Suspend ();
  inline HRESULT Resume ();

protected:

  CATPolyBars& _Bars;
  CATBoolean _Suspended;

};

inline HRESULT CATPolyBarsMeshObserver::Suspend ()
{
  _Suspended = TRUE;
  return S_OK;
}

inline HRESULT CATPolyBarsMeshObserver::Resume ()
{
  _Suspended = FALSE;
  return S_OK;
}

#endif
