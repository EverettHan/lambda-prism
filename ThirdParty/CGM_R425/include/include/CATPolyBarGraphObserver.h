// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarGraphObserver.h
//
//===================================================================
// August 2011  Creation NDO
//===================================================================
#ifndef CATPolyBarGraphObserver_H
#define CATPolyBarGraphObserver_H

#include "PolyBarGraph.h"
#include "CATErrorDef.h"

class CATPolyBarGraph;


/**
* Observer base class for CATPolyBarGraph.
*
* The "PrepareTo" methods are called before the event.
* The "ReactTo" methods are called after the event.
*/
class ExportedByPolyBarGraph CATPolyBarGraphObserver
{

public:

  inline CATPolyBarGraphObserver ();
  virtual ~CATPolyBarGraphObserver ();

public:

/** @name Listening to node events.
    @{ */

  virtual HRESULT ReactToAddNode (const CATPolyBarGraph& iGraph, const unsigned int iNode);
  virtual HRESULT PrepareToRemoveNode (const CATPolyBarGraph& iGraph, const unsigned int iNode);

/** @} */

public:

/** @name Listening to bar events.
    @{ */

  virtual HRESULT ReactToAddBar (const CATPolyBarGraph& iGraph, 
                                 const unsigned int iNode0, const unsigned int iNode1, const unsigned int iBar);

  virtual HRESULT PrepareToRemoveBar (const CATPolyBarGraph& iGraph, const unsigned int iBar);

  virtual HRESULT PrepareToLinkBar (const CATPolyBarGraph& iGraph, 
                                    const unsigned int iBarFrom, const unsigned int iNode, const unsigned int iBarTo);

  virtual HRESULT ReactToUnlinkBar (const CATPolyBarGraph& iGraph,
                                    const unsigned int iBarFrom, const unsigned int iNode, const unsigned int iBarTo);

/** @} */

public:

/** @name Listening to merging node and bar events.
    @{ */

  virtual HRESULT PrepareToMergeNodes (const CATPolyBarGraph& iGraph, 
                                       const unsigned int iNode0, const unsigned int iNode1);

  virtual HRESULT ReactToMergeNodes (const CATPolyBarGraph& iGraph, 
                                     const unsigned int iNode0, const unsigned int iNode1);

  virtual HRESULT PrepareToMergeBars (const CATPolyBarGraph& iGraph, 
                                      const unsigned int iNode0, const unsigned int iBar0, 
                                      const unsigned int iNode1, const unsigned int iBar1);

  virtual HRESULT ReactToMergeBars(const CATPolyBarGraph& iGraph,
                                      const unsigned int iNode0, const unsigned int iBar0,
                                      const unsigned int iNode1, const unsigned int iBar1);

  virtual HRESULT ReactToSplitBar (const CATPolyBarGraph& iGraph, 
                                   const unsigned int iBar, 
                                   const unsigned int oNode, const unsigned int oBar);

/** @} */

protected:

  friend class CATPolyBarGraph;

  CATPolyBarGraphObserver* _Prev;
  CATPolyBarGraphObserver* _Next;

protected:

  inline CATPolyBarGraphObserver* Prev () const;
  inline CATPolyBarGraphObserver* Next () const;

  inline void SetPrev (CATPolyBarGraphObserver* prev);
  inline void SetNext (CATPolyBarGraphObserver* next);

};


inline CATPolyBarGraphObserver::CATPolyBarGraphObserver () :
  _Prev (0),
  _Next (0)
{
}

inline CATPolyBarGraphObserver* CATPolyBarGraphObserver::Prev () const
{
  return _Prev;
}

inline CATPolyBarGraphObserver* CATPolyBarGraphObserver::Next () const
{
  return _Next;
}

inline void CATPolyBarGraphObserver::SetPrev (CATPolyBarGraphObserver* prev)
{
  _Prev = prev;
}

inline void CATPolyBarGraphObserver::SetNext (CATPolyBarGraphObserver* next)
{
  _Next = next;
}

#endif
