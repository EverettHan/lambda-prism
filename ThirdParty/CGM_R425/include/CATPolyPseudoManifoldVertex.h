#pragma once

#include "CATPolyVertexOrbit.h"

// CATPolyPseudoManifoldVertex
#ifndef _AIX_SOURCE
using CATPolyPseudoManifoldVertex = CATPolyVertexOrbit;
#else
typedef CATPolyVertexOrbit CATPolyPseudoManifoldVertex;
#endif
