#pragma once

#include "CATPolyBodyCellIterator.h"

#if 0

#ifndef _AIX_SOURCE
using CATPolyBodyEdgeIterator = CATPolyBodyCellIteratorImpl<CATPolyEdge>;
#else
typedef CATPolyBodyCellIteratorImpl<CATPolyEdge> CATPolyBodyEdgeIterator;
#endif

#else

class CATPolyBodyEdgeIterator : public CATPolyBodyCellIteratorImpl<CATPolyEdge>
{
public:
  CATPolyBodyEdgeIterator (const CATPolyBody* iBody = 0) : CATPolyBodyCellIteratorImpl<CATPolyEdge> (iBody) {}
  CATPolyBodyEdgeIterator (const CATPolyBody& iBody) : CATPolyBodyCellIteratorImpl<CATPolyEdge> (iBody) {}
};

#endif
