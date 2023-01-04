// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVertexLineSurfaceObserver.h
//
//===================================================================
// 2013-09-26   NDO: Revisited
// 2011-05-24   NDO: Revisited
// 2007-01-31   BPG: New
//===================================================================
#ifndef CATPolySurfaceVertexLineSurfaceObserver_H
#define CATPolySurfaceVertexLineSurfaceObserver_H

#include "PolyMeshImpl.h"
#include "CATIPolySurfaceObserver.h"
#include "CATPolyCurveObserverList.h"
#include "CATBoolean.h"

class CATIPolySurfaceVertexLine;


/**
 * Observer class of CATIPolySurface events for a CATIPolySurfaceVertexLine.
 * The class also contains the observers of a CATIPolySurfaceVertexLine because it needs to
 * notify these observers of CATIPolySurface events.
 */
class ExportedByPolyMeshImpl CATPolySurfaceVertexLineSurfaceObserver : public CATIPolySurfaceObserver
{

public:

  CATPolySurfaceVertexLineSurfaceObserver ();
  void SetLine (CATIPolySurfaceVertexLine& iSVL);

  virtual ~CATPolySurfaceVertexLineSurfaceObserver ();

public:
  inline void Suspend ();
  inline void Resume ();

public:

  HRESULT ReactToSplitBar (int sv0, int sv1, int svn);

  HRESULT PrepareToMergeVertices (int sv0, int sv1);

public:

  CATIPolySurfaceVertexLine* _SVL;

  CATBoolean _Suspended;

};

inline void CATPolySurfaceVertexLineSurfaceObserver::SetLine (CATIPolySurfaceVertexLine& iSVL)
{
  _SVL = &iSVL;
}

inline void CATPolySurfaceVertexLineSurfaceObserver::Suspend ()
{
  _Suspended = TRUE;
}

inline void CATPolySurfaceVertexLineSurfaceObserver::Resume ()
{
  _Suspended = FALSE;
}

#endif // !CATPolySurfaceVertexLineSurfaceObserver_H
