#ifndef CATFilletReconfigFillFunction_H
#define CATFilletReconfigFillFunction_H
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
// COPYRIGHT DASSAULT SYSTEMES 1999
//=================================================================================================
//
// Function definition for overiding default fillet reconfig shape
//
//=================================================================================================

#include "CATIACGMLevel.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
class CATBody;
class CATGeoFactory;
class CATShell;
class CATEdge;
class CATFace;
class CATTopData;
class CATTopFillingTool;
class CATTopFillingReport;
class CATTopFillingInput;

//=================================================================================================
typedef CATLONG32 
    (*CATFilletReconfigFillFunction) 
        (
          CATGeoFactory*         iCreationFactory,
          CATTopData*            iTopData,
          CATTopFillingTool*     iFillingTool, 
          CATBody*               iCreationBody,     
          CATShell*              iCreationShell,
          CATTopFillingInput*    iContour,
          CATTopFillingReport* & oReport     
        )  ;    
//=================================================================================================
// Actual Entry point to be used as a CATFilletReconfigFillFunction
//=================================================================================================
#define CATFreeFormFillFunction CATC1SingleFaceFilling;
//=================================================================================================
//=================================================================================================
// To be used to dynamically load a CATFilletReconfigFillFunction
//=================================================================================================
ExportedByCATGMOperatorsInterfaces CATFilletReconfigFillFunction CATGetFreeFormFillFunction();
//=================================================================================================
#endif
