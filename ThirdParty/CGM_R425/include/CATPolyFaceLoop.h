#pragma once

#include "CATPolyFaceOrbit.h"

// CATPolyFaceLoop
#ifndef _AIX_SOURCE
using CATPolyFaceLoop = CATPolyFaceOrbit;
#else
typedef CATPolyFaceOrbit CATPolyFaceLoop;
#endif
