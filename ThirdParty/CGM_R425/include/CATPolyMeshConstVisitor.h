//=============================================================================
// COPYRIGHT Dassault Systemes 2006
//=============================================================================
//
// CATPolyMeshConstVisitor.h
//
//=============================================================================
// 2006-10-12   BPG     * New
//=============================================================================
#ifndef CATPolyMeshConstVisitor_H
#define CATPolyMeshConstVisitor_H

#include "PolyhedralModel.h"
#include "CATPolySurfaceConstVisitor.h"

// Bogus forward declaration for 
// CATSpaceMap\ProtectedInterfaces\CATSiIn3DMapQueryEdgeVertex.h
class CATPolyMeshEVizUVFace;


class ExportedByPolyhedralModel CATPolyMeshConstVisitor : public CATPolySurfaceConstVisitor
{
};


#endif // !CATPolyMeshConstVisitor_H
