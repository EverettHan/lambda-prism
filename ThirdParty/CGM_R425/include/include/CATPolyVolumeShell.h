#pragma once

#include "CATPolyVolumeOrbit.h"

// CATPolyVolumeShell
#ifndef _AIX_SOURCE
using CATPolyVolumeShell = CATPolyVolumeOrbit;
#else
typedef CATPolyVolumeOrbit CATPolyVolumeShell;
#endif
