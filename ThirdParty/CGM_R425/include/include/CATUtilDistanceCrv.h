//===================================================================
// COPYRIGHT Dassault Systemes 2015/03/10
//===================================================================
// CATUtilDistanceCrv.cpp
// Header definition of class CATUtilDistanceCrv
//===================================================================
//
// Usage notes:
//
//===================================================================
// Historic :
// 10-03-15 F1Z Creation.
// DD/MM/YY
//===================================================================

#ifndef CATUtilDistanceCrv_H
#define CATUtilDistanceCrv_H

//===================================================================
// System
#include "CATDataType.h"

// Mathematics
#include "CATTolerance.h"

//===================================================================
typedef enum ExtremumType {EXTREMUM_MIN, EXTREMUM_MAX, EXTREMUM_CONST, EXTREMUM_UNDEFINED} ExtremumType;
typedef enum ExtremumAreaType {AREA_MIN, AREA_MAX, AREA_MINMAX, AREA_UNDEFINED} ExtremumAreaType;
//-----------------------------------------------------------------------
ExtremumType GetExtremumType(const CATTolerance & iTol     ,
                                   double         iEigenVal);

#endif
