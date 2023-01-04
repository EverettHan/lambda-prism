/* -*-C++-*- */
#ifndef CATCGMValidObjectV5_H
#define CATCGMValidObjectV5_H

// COPYRIGHT DASSAULT SYSTEMES 2002
//================================================================================
// Provide an alternative optimised Implement  
//   following an intense deployment inside low-levels API inside core CGM V5
//   for PCS reasons (same service, but reduced cost)
//---------------------------------------------------------------------------
// 06/07/21 NLD Ajout CATCGMValidObjectV5CGMDiag()
//              Ajout CATCGMValidObjectV5Diag()
//---------------------------------------------------------------------------
#include "ExportedByCATCGMFusion.h"
#include "CATCGMValidObject.h"
 
class CATCGMObject;

// Invalidity diagnostic and exception throw if invalidity
ExportedByCATCGMFusion
CATGeoFactory* CATCGMValidObjectV5      (CATICGMUnknown           *  iObject                   ,
                                        CATGeometricType             iType                     = CATUnknownGeometryType,
                                         // if iUnknownOther not NULL, will be checked for validity and same container appartenance
                                         CATICGMUnknown           *  iUnknownOther             = NULL                  ,
                                         CATBoolean                  iAskCheckInsideMemoryPool = FALSE                 );

// Invalidity diagnostic and exception throw if invalidity
ExportedByCATCGMFusion
void           CATCGMValidObjectV5CGM   (CATCGMObject             *  iObject                   ,
                                         CATGeometricType            iType                     = CATUnknownGeometryType);

// (same logics as CATCGMValidObjectV5)    Validity diagnostic with no exception thrown
ExportedByCATCGMFusion
void           CATCGMValidObjectV5Diag  (CATICGMUnknown           *  iUnknown                  ,
                                         CATCGMObject_Invalidity   & oInvalidity               ,
                                         CATGeoFactory            ** oOwnImplicitFactory       = NULL,
                                         CATGeometricType            iType                     = CATUnknownGeometryType,
                                         // if iUnknownOther not NULL, will be checked for validity and same container appartenance
                                         CATICGMUnknown           *  iUnknownOther             = NULL,
                                         // value given back if non null pointer received
                                         CATCGMObject_Invalidity  *  oInvalidityOther          = NULL,
                                         CATBoolean                  iAskCheckInsideMemoryPool = FALSE                );


// (same logics as CATCGMValidObjectV5CGM) Validity diagnostic with no exception thrown
ExportedByCATCGMFusion
void           CATCGMValidObjectV5CGMDiag(CATCGMObject             *  iObject                  ,
                                          CATICGMUnknown           *& oInterface               ,
                                          CATCGMObject_Invalidity   & oInvalidity              ,
                                          CATGeometricType            iType                    = CATUnknownGeometryType);

#endif
