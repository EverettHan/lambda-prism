#ifndef CATCreateCATSurTo2DCompositionMapping_H 
#define CATCreateCATSurTo2DCompositionMapping_H 

// COPYRIGHT DASSAULT SYSTEMES  1999
 
#include "Connect.h" 
#include "CreateSurTo2DCompositionMapping.h"

class CATGeoFactory;
class CATMathFunctionXY;  
class CATSurTo2DGlobalMapping;
class CATSurTo2DGlobalCompositionMapping;
class CATSoftwareConfiguration;
/**
* Creates an object defining a global mapping by composition of global mapping with 2 bi variable functions .
* <br> This object is used
* by the @href CATTopDevelop operator to define the input and output mappings. You
* have to <tt>delete</tt> this object after use.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iGlobalMapping
* The GlobalMapping To Compose. 
* @param iNewX
* The bi variable function that defines NewX(OldX,OldY). 
* @param iNewY
* The bi variable function that defines NewY(OldX,OldY). 
* @param iOldX
* The bi variable function that defines OldX(NewX,NewY). 
* @param iOldY
* The bi variable function that defines OldY(NewX,NewY). 
* @return
* The pointer to the created operator. To <tt>delete</tt> after use.
*/
ExportedByConnect
CATSurTo2DGlobalCompositionMapping * CATCreateCompositionMapping( CATGeoFactory *iFactory,
                                                                 CATSoftwareConfiguration *iConfig,
                                                                 const CATSurTo2DGlobalMapping * iGlobalMapping,
                                                                 const CATMathFunctionXY * iNewX,
                                                                 const CATMathFunctionXY * iNewY,
                                                                 const CATMathFunctionXY * iOldX,
                                                                 const CATMathFunctionXY * iOldY);


#endif


