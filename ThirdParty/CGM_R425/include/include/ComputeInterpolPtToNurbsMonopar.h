 // COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// Internal Functions of the Interpolation Operator for Curves and PCurves.
//
//==========================================================================
//
// Usage notes:
//========================================================================== 
// Sept. 97     Creation                   DHN
//========================================================================== 

#ifndef ComputeInterpolPtToNurbsMonopar_H
#define ComputeInterpolPtToNurbsMonopar_H

class CATMathSetOfPointsND;
class CATKnotVector;

#include "YP00IMPL.h"


//-----------------------------------------------------------------------------
//  Hermitt Interpolation function -> Creates or modifies a NurbsCurve
//  iDimension =2 for posed geometry and 3 for free geometry
//-----------------------------------------------------------------------------
ExportedByYP00IMPL CATMathPoint *ComputeHermitInterpolation (
                                const double *iPoints, const double *iTangents, 
                                const CATLONG32 &iNbOfPoints, const CATKnotVector *iKnotVector, 
                                const CATLONG32 &iDimension);

//-----------------------------------------------------------------------------
//  Set new points and/or new first derivatives to interpolate 
//-----------------------------------------------------------------------------
ExportedByYP00IMPL CATKnotVector *ComputePointsAndTangents(
                                const CATMathSetOfPointsND * iPoints,
                                const CATLONG32 &iDimension,
				const CATLONG32 & nvar0, const CATLONG32 & nvar1,
				const CATLONG32 & nvar2, double *ioPoints,
                                double *ioTangents, CATLONG32 &iNbOfPoints,
                                CATKnotVector *iImposedKnotVector = NULL);
#endif
