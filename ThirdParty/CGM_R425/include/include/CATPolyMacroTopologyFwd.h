#pragma once

class CATPolyBody;
class CATPolyCell;
class CATPolyVertex;
class CATPolyEdge;
class CATPolyFace;
class CATPolyVolume;

class CATPolyCellOrbit;
class CATPolyVertexOrbit;
class CATPolyEdgeOrbit;
class CATPolyFaceOrbit;
class CATPolyVolumeOrbit;

#ifndef _AIX_SOURCE
using CATPolyPseudoManifoldVertex = CATPolyVertexOrbit;
using CATPolyManifoldEdge = CATPolyEdgeOrbit;
using CATPolyFaceLoop = CATPolyFaceOrbit;
using CATPolyVolumeShell = CATPolyVolumeOrbit;
#else
typedef CATPolyVertexOrbit CATPolyPseudoManifoldVertex;
typedef CATPolyEdgeOrbit CATPolyManifoldEdge;
typedef CATPolyFaceOrbit CATPolyFaceLoop;
typedef CATPolyVolumeOrbit CATPolyVolumeShell;
#endif
