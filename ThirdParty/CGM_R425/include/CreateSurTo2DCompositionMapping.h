#ifndef CreateCATSurTo2DCompositionMapping_H 
#define CreateCATSurTo2DCompositionMapping_H 

// COPYRIGHT DASSAULT SYSTEMES  1999
 
#include "Connect.h" 

class CATGeoFactory;
class CATMathFunctionXY;  
class CATIPGMSurTo2DGlobalMapping;
class CATSurTo2DGlobalMapping;
class CATSurTo2DGlobalCompositionMapping;
/**
* @deprecated V5R13 CATCreateCompositionMapping
*/
ExportedByConnect
CATSurTo2DGlobalCompositionMapping * CreateCompositionMapping( CATGeoFactory *iFactory,
															  const CATSurTo2DGlobalMapping * iGlobalMapping,
															  const CATMathFunctionXY * iNewX,
															  const CATMathFunctionXY * iNewY,
															  const CATMathFunctionXY * iOldX,
															  const CATMathFunctionXY * iOldY);

/**
* @deprecated V5R13 CATCreateCompositionMapping
*/
ExportedByConnect
CATSurTo2DGlobalCompositionMapping * CreateCompositionMapping( CATGeoFactory *iFactory,
															  CATIPGMSurTo2DGlobalMapping * iGlobalMapping,
															  const CATMathFunctionXY * iNewX,
															  const CATMathFunctionXY * iNewY,
															  const CATMathFunctionXY * iOldX,
															  const CATMathFunctionXY * iOldY);

/** @nodoc*/
ExportedByConnect
void RemoveMapping(CATSurTo2DGlobalCompositionMapping *&iMappingToRemove); 

#endif


