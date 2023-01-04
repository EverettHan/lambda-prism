#pragma once

#include "CATPolyBodyCellIterator.h"

#if 0

#ifndef _AIX_SOURCE
using CATPolyBodyFaceIterator = CATPolyBodyCellIteratorImpl<CATPolyFace>;
#else
typedef CATPolyBodyCellIteratorImpl<CATPolyFace> CATPolyBodyFaceIterator;
#endif

#else

class CATPolyBodyFaceIterator : public CATPolyBodyCellIteratorImpl<CATPolyFace>
{
public:
  CATPolyBodyFaceIterator (const CATPolyBody* iBody = 0) : CATPolyBodyCellIteratorImpl<CATPolyFace> (iBody) {}
  CATPolyBodyFaceIterator (const CATPolyBody& iBody) : CATPolyBodyCellIteratorImpl<CATPolyFace> (iBody) {}
};

#endif

