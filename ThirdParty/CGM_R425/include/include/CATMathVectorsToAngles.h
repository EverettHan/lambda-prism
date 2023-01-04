#ifndef CATMathVectorsToAngles_h
#define CATMathVectorsToAngles_h

// COPYRIGHT DASSAULT SYSTEMES  1997

#include "YN000M2D.h"
#include "CATDataType.h"

class CATMathVector2D;
/**
 * Function to calulate the angular sector from a start vector (V1) to an end
 * vector (V3), crossing a middle vector(V2).
 */ 
CATLONG32 ExportedByYN000M2D CATMathVectorsToAngles(const CATMathVector2D & iV1,
												const CATMathVector2D & iV2,
												const CATMathVector2D & iV3,
												double & oStartAngle,
												double & oEndAngle,
												short & oOrientation);
#endif
