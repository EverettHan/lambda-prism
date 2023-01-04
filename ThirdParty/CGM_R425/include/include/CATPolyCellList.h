// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyCellList.h
//
//=============================================================================
// 2022-06-07 NDO
//=============================================================================
#pragma once

#include "CATLISTP_Clean.h"
#include "CATLISTP_PublicInterface.h"
#include "CATLISTP_Declare.h"

#include "PolyMODEL.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPolyMODEL

class CATPolyVertex;
CATLISTP_DECLARE (CATPolyVertex);
typedef CATLISTP (CATPolyVertex) CATPolyVertexList;

class CATPolyEdge;
CATLISTP_DECLARE (CATPolyEdge);
typedef CATLISTP (CATPolyEdge) CATPolyEdgeList;

class CATPolyFace;
CATLISTP_DECLARE (CATPolyFace);
typedef CATLISTP (CATPolyFace) CATPolyFaceList;

class CATPolyVolume;
CATLISTP_DECLARE (CATPolyVolume);
typedef CATLISTP (CATPolyVolume) CATPolyVolumeList;

//
// Template class
//
template<class CELL>
class CATPolyCellList
{
};

// Specialization CATPolyVertex
template<>
class CATPolyCellList<CATPolyVertex> : public CATPolyVertexList
{
};
