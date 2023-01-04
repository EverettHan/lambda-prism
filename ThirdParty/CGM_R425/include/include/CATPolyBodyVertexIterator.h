#pragma once

#include "CATPolyBodyCellIterator.h"

#if 0

#ifndef _AIX_SOURCE
using CATPolyBodyVertexIterator = CATPolyBodyCellIteratorImpl<CATPolyVertex>;
#else
typedef CATPolyBodyCellIteratorImpl<CATPolyVertex> CATPolyBodyVertexIterator;
#endif

#else

class CATPolyBodyVertexIterator : public CATPolyBodyCellIteratorImpl<CATPolyVertex>
{
public:
  CATPolyBodyVertexIterator (const CATPolyBody* iBody = 0) : CATPolyBodyCellIteratorImpl<CATPolyVertex> (iBody) {}
  CATPolyBodyVertexIterator (const CATPolyBody& iBody) : CATPolyBodyCellIteratorImpl<CATPolyVertex> (iBody) {}
};

#endif
