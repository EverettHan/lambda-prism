#ifndef CATMathLimits_h
#define CATMathLimits_h

// COPYRIGHT DASSAULT SYSTEMES  2005

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "YN000MAT.h"

/**
 * Defines the maximum relative precision. 
 * CATEpsilon = 1.e-15
 */
extern ExportedByYN000MAT const double CATEpsilon;

/**
 * Defines the calculation result precision. 
 * CATEps = 1.e-12
 */
extern ExportedByYN000MAT const double CATEpsg;

/**
 * Defines the infinite. 
 * CATMathInfinite = 1.e12
 */
extern ExportedByYN000MAT const double CATMathInfinite;

/**
 * Defines the maximum value of a double. 
 * CATdoubleMax = DBL_MAX or CATdoubleMax = 1.7976931348623157E+308
 */
extern ExportedByYN000MAT const double CATdoubleMax;

/**
 * Defines the maximum absolute precision. 
 */
#define CAT_ABSOLUTE_EPSILON 1.e-38

/**
 * Defines CATEpsilon squared. 
 * 1.e-30
 */
extern ExportedByYN000MAT const double CATSquareEpsilon;

/**
 * Defines CATEpsg squared. 
 * 1.e-24
 */
extern ExportedByYN000MAT const double CATSquareEpsg;

/**
 * Defines the square root of CATEpsilon. 
 * sqrt(1.e-15)
 */
extern ExportedByYN000MAT const double CATSqrtEpsilon;

/**
 * Defines the square root of CATEpsg. 
 * 1.e-6
 */
extern ExportedByYN000MAT const double CATSqrtEpsg;

#endif
