// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraphSurfaceLayerIterator.h
//
//===================================================================
// December 2011  Creation NDO
//===================================================================
#ifndef CATPolyBodyBarGraphSurfaceLayerIterator_H
#define CATPolyBodyBarGraphSurfaceLayerIterator_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATMapOfIntToPtr.h"

class CATPolyBodyBarGraph;
class CATPolyBodyBarGraphSurfaceLayers;


/**
 * Iterator through all the faces and layers of a CATPolyBodyBarGraph.
 */
class ExportedByPolyBarGraph CATPolyBodyBarGraphSurfaceLayerIterator
{

public:

  CATPolyBodyBarGraphSurfaceLayerIterator (const CATPolyBodyBarGraph& iBodyGraph);

  ~CATPolyBodyBarGraphSurfaceLayerIterator () {delete _Iterator; _Iterator = 0;}

public:

  inline CATPolyBodyBarGraphSurfaceLayerIterator& Begin () {if (_Iterator) _Iterator->Begin (); return *this;}
  inline CATBoolean End () const {return _Iterator ? _Iterator->End () : TRUE;}
  inline CATPolyBodyBarGraphSurfaceLayerIterator& operator++ () { if (_Iterator) ++(*_Iterator); return *this;}

public:

  inline unsigned int GetFace () const;
  inline CATPolyBodyBarGraphSurfaceLayers* GetSurfaceLayers () const;

public:

  CATMapOfIntToPtr::Iterator* _Iterator;

};

unsigned int CATPolyBodyBarGraphSurfaceLayerIterator::GetFace () const
{
  return _Iterator->GetKey ();
}

CATPolyBodyBarGraphSurfaceLayers* CATPolyBodyBarGraphSurfaceLayerIterator::GetSurfaceLayers () const
{
  return (CATPolyBodyBarGraphSurfaceLayers*) _Iterator->GetData ();
}

#endif
