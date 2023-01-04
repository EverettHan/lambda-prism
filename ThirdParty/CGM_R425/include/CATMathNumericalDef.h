// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathNumericalDef:
//  Constants for numerical algorithms.
//
//=============================================================================
//
// Usage notes:
//  Those constants are related to the ones defined in CATMathDef.h.
//
//=============================================================================
// Oct. 97   Creation                                               S. Royer
//=============================================================================
#ifndef CATMathNumericalDef_h
#define CATMathNumericalDef_h

#include "YN000FUN.h"
#include "CATDataType.h"

//-----------------------------------------------------------------------------
// Derivative approximation constants.
//-----------------------------------------------------------------------------
// Cubic root of CATEpsilon for first derivative evaluation.
// CATMathh1 = pow(CATEpsilon, 1./3.) = 1.e-5
extern ExportedByYN000FUN const double CATMathh1;

// Precision on the approximate first derivate computed with CATMathh1.
// CATMathDerivPrecision = pow(CATEpsg, 2./3.) = 1.e-8
extern ExportedByYN000FUN const double CATMathDerivPrecision;

// Quartic root of CATEpsilon for second derivative evaluation.
// CATMathh2 = pow(CATEpsilon, 1./4.) = 1.e-4
extern ExportedByYN000FUN const double CATMathh2;

// "Hexic" root of CATEpsilon for third derivative evaluation.
// CATMathh3 = 2. * pow(CATEpsilon, 1./6.) = 2.e-3
extern ExportedByYN000FUN const double CATMathh3;

//-----------------------------------------------------------------------------
// Iteration limits constants.
//-----------------------------------------------------------------------------
// Maximum iteration number for a Newton loop.
// CATMaxNewtonIteration = 50
extern ExportedByYN000FUN const CATLONG32 CATMaxNewtonIteration;

// Maximum iteration number for an interval algorithm.
// CATMaxIntervalIteration = 10
extern ExportedByYN000FUN const CATLONG32 CATMaxIntervalIteration;

// Maximum interval reducing ratio for an interval algorithm.
// CATMaxIntervalReduction = 1.e-3
extern ExportedByYN000FUN const double CATMaxIntervalReduction;

// Minimum interval ratio size in interval algorithm before calling MaxDepth solver
// CATMinWidth = 0.005
extern ExportedByYN000FUN const double CATMinWidth;

#endif
