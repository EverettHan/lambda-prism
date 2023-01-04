// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraphObserver.h
//
//===================================================================
// February 2012  Creation NDO
//===================================================================
#ifndef CATPolyBodyBarGraphObserver_H
#define CATPolyBodyBarGraphObserver_H

#include "PolyBarGraph.h"
#include "CATErrorDef.h"

class CATPolyBodyBarGraph;


/**
* Observer base class for CATPolyBodyBarGraph.
*
* The "PrepareTo" methods are called before the event.
* The "ReactTo" methods are called after the event.
*/
class ExportedByPolyBarGraph CATPolyBodyBarGraphObserver
{

public:

  CATPolyBodyBarGraphObserver () : _Next (0) {}
  virtual ~CATPolyBodyBarGraphObserver () {_Next = 0;}

public:

/** @name Listening to node events.
    @{ */

  virtual HRESULT ReactToAddNode (const CATPolyBodyBarGraph& iBodyGraph, const unsigned int iNode);
  virtual HRESULT PrepareToRemoveNode (const CATPolyBodyBarGraph& iBodyGraph, const unsigned int iNode);

/** @} */

public:

/** @name Listening to bar events.
    @{ */

  virtual HRESULT ReactToAddBar (const CATPolyBodyBarGraph& iBodyGraph, 
                                 const unsigned int iNode0, const unsigned int iNode1, const unsigned int iBar);

  virtual HRESULT PrepareToRemoveBar (const CATPolyBodyBarGraph& iBodyGraph, const unsigned int iBar);

/** @} */

public:

/** @name Listening to merging node and bar events.
    @{ */

  virtual HRESULT PrepareToMergeNodes (const CATPolyBodyBarGraph& iBodyGraph, 
                                       const unsigned int iNode0, const unsigned int iNode1);

  virtual HRESULT ReactToMergeNodes (const CATPolyBodyBarGraph& iBodyGraph, 
                                     const unsigned int iNode0, const unsigned int iNode1);

  virtual HRESULT PrepareToMergeBars (const CATPolyBodyBarGraph& iBodyGraph, 
                                      const unsigned int iNode0, const unsigned int iBar0, 
                                      const unsigned int iNode1, const unsigned int iBar1);

  virtual HRESULT ReactToSplitBar (const CATPolyBodyBarGraph& iBodyGraph, 
                                   const unsigned int iBar, 
                                   const unsigned int oNode, const unsigned int oBar);

/** @} */

public:

  static void PrintNodeAdjacencies(const CATPolyBodyBarGraph& iBodyGraph, const unsigned int n);

private:

  friend class CATPolyBodyBarGraphLayerObserver;

  CATPolyBodyBarGraphObserver* _Next;

private:

  inline CATPolyBodyBarGraphObserver* Next () const {return _Next;}
  inline void SetNext (CATPolyBodyBarGraphObserver* next) {_Next = next;}

};

#endif
