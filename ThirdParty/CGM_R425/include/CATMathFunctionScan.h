#ifndef CATMathFunctionScan_H
#define CATMathFunctionScan_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012
//=============================================================================
//
// General scan tools for mathematical functions
//
//=============================================================================
// 14/12/12 NLD Creation par extraction depuis CATMathFunctionX.cpp
//              - CATMathFunctionXGetTolerance
//              - CATMathFunctionScanComponents
//              - CATMathFunctionXReplaceDefaultTolerance
//=============================================================================

#include "YN000FUN.h"

class CATMathFunctionGeneral ;
class CATMathFunctionX ;

#include "CATTolerance.h"

//-----------------------------------------------------------------------------
// Search for a non null CATTolerance object under function, and returns default tolerance if not found
//-----------------------------------------------------------------------------
ExportedByYN000FUN
const CATTolerance& CATMathFunctionXGetTolerance(CATMathFunctionX* iFX);

//-----------------------------------------------------------------------------
// Replaces default CATTolerance objects under function components found by deep scan
// - prototype to be enhanced when needed with new types of components to manage
//   as of 2012 14th December,
//   are managed:
//   - CATMathTrigonometricX
//   are not managed:
//   - CATMathBasisFunctionX
//-----------------------------------------------------------------------------
// VERY RESTRICTED USE
//-----------------------------------------------------------------------------
ExportedByYN000FUN
void CATMathFunctionXReplaceDefaultTolerance(CATMathFunctionX* iFX, const CATTolerance* iTolObject);
//-----------------------------------------------------------------------------
// General scan of a function by its components,
// with call of a treatment function for each component,
// before and after scan of the component
// (treatment may be chosen according to argument iBeforeScan(=1 before scan, 0 after scan))
//-----------------------------------------------------------------------------
// 1) Type of the external function to be called for each component 
typedef void (* CATMathFunctionScan_ComponentManagement)(CATMathFunctionGeneral* iComponent   ,
                                                         int                     iNbComponents,
                                                         int                     iLevel       ,
                                                         void                  * ioData       ,
                                                         int                     iBeforeScan  );


// 2) General scan method.
//    -------------------
//   (iLevel should be set to 1 before 1st level call) 
ExportedByYN000FUN
void CATMathFunctionScanComponents(CATMathFunctionGeneral                 *  iFX                  ,
                                   int                                       iLevel               ,
                                   CATMathFunctionScan_ComponentManagement   ComponentManagement  = NULL,
                                   void                                   *  ioDataForCall        = NULL
                        );


#endif
