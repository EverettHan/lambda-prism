// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyIsClosed.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// 2008-12-22   NDO: New
//===================================================================
#ifndef CATPolyBodyIsClosed_H
#define CATPolyBodyIsClosed_H

#include "PolyBodyTools.h"
#include "CATErrorDef.h"  // Definition of HRESULT.
#include "CATIAV5Level.h"
#include "CATechExt.h"
class CATPolyBody;


#ifdef CATIAR418
class CATPolyBodyIsClosedObserver;
#endif //CATIAR418

/**
 * This operator checks if a CATPolyBody object is closed (and orientable) or not.
 * A CATPolyBody is closed if none of its facets has an open border.
 * The closure test for each facet border consists of summing up the orientation of the border in all the adjacent 
 * facets. Adacent facets need to share the same vertices along their common border.  
 * This verification is purely combinatorial.
 */
class ExportedByPolyBodyTools CATPolyBodyIsClosed
{

public:

  CATPolyBodyIsClosed () ;
  ~CATPolyBodyIsClosed () ;

public: 

  // @param
  //   The polybody that is to be checked for watertightness.
  // @param oNbOpenBars
  //   An optional argument to count the number of bars that fail the closure test.
  // @return
  //   S_FALSE if the CATPolyBody is open.
  //   S_OK if the CATPolyBody is closed.
  //   E_FAIL on failure.
  HRESULT IsBodyClosed (const CATPolyBody& iPolyBody, int* opNbOpenBars = 0) const;
#ifdef CATIAR418
  // For Internal use
public:
  inline void SetObserver (CATPolyBodyIsClosedObserver* iObserver);
  inline CATPolyBodyIsClosedObserver* GetObserver () const;

protected:
  CATPolyBodyIsClosedObserver* _Observer;
  CATechExt *_Extension;
#endif //CATIAR418

};

#ifdef CATIAR418
inline void CATPolyBodyIsClosed::SetObserver (CATPolyBodyIsClosedObserver* iObserver)
{
  _Observer = iObserver;
}

inline CATPolyBodyIsClosedObserver* CATPolyBodyIsClosed::GetObserver () const
{
  return _Observer;
}
#endif //CATIAR418

#endif
