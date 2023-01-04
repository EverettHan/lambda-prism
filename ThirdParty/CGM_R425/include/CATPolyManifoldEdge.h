#pragma once

#include "CATPolyEdgeOrbit.h"

// CATPolyManifoldEdge
#ifndef _AIX_SOURCE
using CATPolyManifoldEdge = CATPolyEdgeOrbit;
#else
typedef CATPolyEdgeOrbit CATPolyManifoldEdge;
#endif
