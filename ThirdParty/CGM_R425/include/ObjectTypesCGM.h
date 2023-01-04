//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//  Persistency.Engineering.Change  "DataBase" 
//
// CGM Object Types
//
//----------------------------------------------------------------------------
//  DO NOT INCLUDE THIS HEADER DIRECTLY
//
//  YOU MAY RATHER USE FOLLOWING HEADER FOR ACCESS TO  ACTIVE PERSISTENCY CHANGE
//      GeometricObjectsCGM\ProtectedInterfaces\ObjectTypesCGM.h
//
//    ROOT INTERNAL DEFINITION IS HOLDED BY
//        CATMathStream\ProtectedInterfaces\CATCGMStreamTypeDEFINE.h
//=============================================================================
// Usage notes:
//
// Strictement reserve aux implementations CGM CATxxxCGM
//=============================================================================
// Mar.  97   Creation                                     R. Rorato
// Mar.  04   Ajout de 2 nouveaux types                    MNA
//           CATSharpnessDefCGMType
//           CATLyingOnDefCGMType
// July  04   Ajout CATSubdivMeshCGMType                   RAQ
// Jan   08   Ajout CATSubdivCellSurfaceCGMType            RNO
// May   08   Ajout CATSubdivMeshGeoCGMType                RAQ
//
// April 09  DataBase is managed 
//              Mathematics\ProtectedInterfaces\CATCGMStreamTypeDEFINE.h
//=============================================================================
#ifndef ObjectTypesCGM_H
#define ObjectTypesCGM_H

#include "CATCGMStreamObjectTypesCGM.h"
 

#include "CATCGMBOAObject.h"
#if defined ( CATCGMBOAObject )
#else
#define CATGeoFactoryCGMGeoType       CATRootContainerCGMType
#define CATSubdConfusedLoopGeoType    CATConfusedLoopCGMType
#endif

#endif

