#pragma once

#include "CATPolyBodyCellIterator.h"

#if 0

#ifndef _AIX_SOURCE
using CATPolyBodyVolumeIterator = CATPolyBodyCellIteratorImpl<CATPolyVolume>;
#else
typedef CATPolyBodyCellIteratorImpl<CATPolyVolume> CATPolyBodyVolumeIterator;
#endif

#else

class CATPolyBodyVolumeIterator : public CATPolyBodyCellIteratorImpl<CATPolyVolume>
{
public:
  CATPolyBodyVolumeIterator (const CATPolyBody* iBody = 0) : CATPolyBodyCellIteratorImpl<CATPolyVolume> (iBody) {}
  CATPolyBodyVolumeIterator (const CATPolyBody& iBody) : CATPolyBodyCellIteratorImpl<CATPolyVolume> (iBody) {}
};

#endif
