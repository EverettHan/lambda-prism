/* -*-C++-*- */
#ifndef CATCGMValidObject_H
#define CATCGMValidObject_H

// #define CATCGMValidObject_TemporaryShuntNewMethod "pour voir impact et appelants"

// COPYRIGHT DASSAULT SYSTEMES 2002
//================================================================================
// Detect invalid pointer of V5 geometrical object
//    1) Null address 
//    2) invalid address 
//    3) not a V5 implementation
//    4) unexpected type
//    5) object out of a container (removed object)
//    6) incompatible container 
// If invalidity is detected, an error is thrown ...
//---------------------------------------------------------------------------
// ??/??/?? TCX
// 01/04/10 NLD Ajout enum CATCGMObject_Validity
//              Ajout signature sans levee d'exception, rendant un diagnostic
//              pour performances
// 02/07/21 NLD Renommage de iSameContainer en iUnknownOther
// 05/07/21 NLD Ajout CATCGMValidObjectThrow() (qui était interne)
//---------------------------------------------------------------------------
#include "ExportedByGeometricObjects.h"
#include "CATGeometryType.h"
#include "CATBoolean.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

class CATICGMUnknown;
class CATGeoFactory;
class CATICGMObject;

typedef enum {CATCGMObject_IsValid = 0,
              CATCGMObject_NullAddress,
              CATCGMObject_NotInPool,
              CATCGMObject_InvalidAddress,
              CATCGMObject_NoV5Implementation,
              CATCGMObject_UnexpectedType,
              CATCGMObject_RemovedObject,
              CATCGMObject_IncompatibleContainer,
              CATCGMObject_InternalNullPointer
             }CATCGMObject_Invalidity;

#ifndef CATCGMValidObject_TemporaryShuntNewMethod
// quick call not raising exception
ExportedByGeometricObjects
void           CATCGMValidObject(CATICGMUnknown          *  iUnknown                  ,
                                 // output
                                 CATCGMObject_Invalidity  & oInvalidity               ,
                                 CATGeoFactory          **  oOwnImplicitFactory       = NULL,// <-- returns factory address if not null pointer in input
                                 // Extra optional input data
                                 CATGeometricType           iType                     = CATUnknownGeometryType,
                                 // if iUnknownOther not NULL, will be checked for validity and same container appartenance
                                 CATICGMUnknown          *  iUnknownOther             = NULL,
                                 CATBoolean                 iAskCheckInsideMemoryPool = FALSE
                                );
#endif

// standard call with exception raise
ExportedByGeometricObjects
CATGeoFactory* CATCGMValidObject(CATICGMUnknown          *  iObject                   ,
                                 CATGeometricType           iType                     = CATUnknownGeometryType,
                                 // if iUnknownOther not NULL, will be checked for validity and same container appartenance
                                 CATICGMUnknown          *  iUnknownOther             = NULL,
                                 CATBoolean                 iAskCheckInsideMemoryPool = FALSE);


//---------------------------------------------------------------------------
//  For CATCGMValidObjectV5
//---------------------------------------------------------------------------
// 1) dedicated throw methods
extern ExportedByGeometricObjects  void CATCGMValidObject_InvalidAddress       (CATICGMUnknown * iUnknown);
extern ExportedByGeometricObjects  void CATCGMValidObject_NotV5Modelisation    (CATICGMUnknown * iUnknown);
extern ExportedByGeometricObjects  void CATCGMValidObject_UnexpectedType       (CATICGMUnknown * iUnknown, CATGeometricType iType);
extern ExportedByGeometricObjects  void CATCGMValidObject_RemovedObject        (CATICGMObject  * iObject , int iDebugODT=0);
extern ExportedByGeometricObjects  void CATCGMValidObject_IncompatibleContainer(CATICGMUnknown * iUnknown, CATICGMUnknown * iUnknownOther);

// 2) general throw method; Restricted use, be CAREFUL
//    N.B for this throw method the argument ownImplicitFactory is optional
extern ExportedByGeometricObjects 
CATGeoFactory* CATCGMValidObjectThrow(CATICGMUnknown          *  iUnknown                 ,
                                      CATCGMObject_Invalidity    iInvalidity              ,
                                      CATGeometricType           iType                    = CATUnknownGeometryType,
                                      CATICGMUnknown          *  iUnknownOther            = NULL,
                                      CATCGMObject_Invalidity    iInvalidityOther         = CATCGMObject_IsValid,
                                      CATGeoFactory           *  ownImplicitFactory       = NULL);


#endif
