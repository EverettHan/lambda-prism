
// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySilhouettePartition.h
// Header definition of CATPolySilhouettePartition
//
//===================================================================
//
// Usage notes: Associates an orientation ( +1, 0, -1) for each triangle of the mesh,
// in regards with its normal Versus a view direction
//
//===================================================================
//
// November 2012 Creation: dps
//===================================================================

#ifndef CATPolySilhouettePartition_H
#define CATPolySilhouettePartition_H

#include "CATPolyTrianglePartitionDefiner.h" // derivation
#include "PolyMeshTools.h"                   // ExportedBy
#include "CATPolyGeoUtil.h"                  // agregation
#include "CATMathDirection.h"                // agregation
#include "CATMathPoint.h"                    // agregation

#include "CATBoolean.h" 
#include "CATSysBoolean.h" 

class CATIPolyMesh;


class ExportedByPolyMeshTools CATPolySilhouettePartition : public CATPolyTrianglePartitionDefiner
{

public:

  CATPolySilhouettePartition(const CATIPolyMesh & iMesh, 
                             double iObserverViewRef[3], CATBoolean iIsViewConical, double iTolDot);

  ~CATPolySilhouettePartition();

  virtual int GetPartitionValue(int iTriangleID);


private:


  // INPUT
  // =====

  const CATIPolyMesh                 & _Mesh;
  CATMathDirection                     _ViewDirToObserver;
  const CATMathPoint                   _ObserverViewPoint;

  const double                         _TolDot;
  CATBoolean                           _ConicalView;


  // Working data
  // ============

  CATPolyGeoUtil                       _PolyGeoUtil;

};

#endif
