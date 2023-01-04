// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyDeltaMeshConst.h
//
//===================================================================
// Feb 2021 F1Z : Creation
//===================================================================

#pragma once

// Polyhedral Mathematics
#include "Poly/Set.h"

// PolyhedralObjects
#include "PolyMeshImpl.h"
#include "CATPolyDeltaMeshConstDelta.h"

namespace Poly
{
  namespace DeltaMesh
  {
    // This method should be call before any set of vertices kept
    // Return E_FAIL if any kept vertices was already set to the delta keep
    ExportedByPolyMeshImpl HRESULT SetParentVerticesKeptFromRemoved(CATPolyDeltaMeshConst::DeltaKeep & ioDeltaKeep,
                                                                    Poly::Set<int> & iRemovedVertices);

    // This method should be call before any set of triangles kept
    // Return E_FAIL if any kept triangles was already set to the delta keep
    ExportedByPolyMeshImpl HRESULT SetParentTrianglesKeptFromRemoved(CATPolyDeltaMeshConst::DeltaKeep & ioDeltaKeep,
                                                                     Poly::Set<int> & iRemoveTriangles);

    // Return the cost value of the delta and compact stream for the provided delta information
    template<typename DeltaType>
    ExportedByPolyMeshImpl void GetStreamCost(const DeltaType & iDelta,
                                              unsigned int & oDeltaCost,
                                              unsigned int & oCompactCost);

    // Return true if the delta mesh has a lower stream cost then a compact mesh
    template<typename DeltaType>
    ExportedByPolyMeshImpl bool IsDeltaStreamBetterThanCompactMesh(const DeltaType & iDelta,
		                                                               const unsigned int iMinGain=1,
																                                   const double iMinRatio=1.0);
  };
};
