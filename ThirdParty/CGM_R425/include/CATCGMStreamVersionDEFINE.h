#ifndef CATCGMStreamVersionDEFINE_h
#define CATCGMStreamVersionDEFINE_h
// COPYRIGHT DASSAULT SYSTEMES  2009
#include "CATCGMVersionLevel.h"
//----------------------------------------------------------------------------
//  Persistency.Engineering.Change  "DataBase" 
//
//   Change are documented (on initial status (if not created) to current content)
//
//   Methodology for Change Management  
//
//----------------------------------------------------------------------------
//  DO NOT INCLUDE THIS HEADER DIRECTLY
//     YOU MAY RATHER USE FOLLOWING HEADER FOR ACCESS TO  ACTIVE PERSISTENCY CHANGE
//      Mathematics\ProtectedInterfaces\CATCGMStreamVersionUnderEvaluation.h
//----------------------------------------------------------------------------
//  Storage : Persistency Change Management   
//       
//  Provide as variable of type CATCGMStreamVersion 
//     numerous variations of persistency associated to a particular topic.
//       
//  Provide as variable of type CATCGMStreamVersion 
//      StreamTopic                : Name of Topic , to be compared with current CATCGMStreamVersion_##StreamTopic
//      TargetCATCGMStreamVersion  : Target version provided from CATCGMStreamVersionLimited.h 
//                                        (rather than CATMathStreamVersionDef)
//      CurrentActivation          : Default status of activation 
//                                       1 : default is activated 
//                                       0 : Inactivated , NEEDED VARIABLES ARE ABOUT : 
//                                            set CATCGMStreamVersionUnderEvaluation=CXR20
//                                            set CATDevelopmentStage=TRUE
//----------------------------------------------------------------------------
//  For new variable : TWO points of delivery for declaration, definition : 
//
//      1/ Mathematics\ProtectedInterfaces\CATCGMStreamVersionDEFINE.h
//           ONE DATABASE for complete definition of variable
//      2/ Mathematics\ProtectedInterfaces\CATCGMStreamVersionUnderEvaluation.h
//           for cosmetic usage of variable  
//
//  N.B : Definition are automatically defined thanks to
//           Mathematics\CATMathStream.m\src\CATCGMStreamVersionDEFINE.cpp
//----------------------------------------------------------------------------

 
/*
 *
 * Origin : Auto-adaptative Header for small Object
 * Persistency Validity : automatic ( 4 bytes per small objects )
 *
 * Change Documentation 
 *    Previous Status    : Adaptative V5R6 V5R19 format
 *    content Proposal   : Optimised Scalable data size
*/
//  IsSmallHeader()  

 /*
 *
 * Origin               : Performance && Statistics on referential
 * Persistency Validity : ODT CATCGMStreamCoverage
 *                         and CATCGMStream.tst\CATCGMStreamCoverage.m\src\CATCGMStreamCoverage_Integer.cpp
 * 
 * Change Documentation 
 *    Previous Status    : Full value fixed size
 *    content Proposal   : Scalable stream size with small header (bit field) for number of bytes
*/
//  IsScalableInteger()  


 /*
 *
 * Origin               : Performance && Statistics on referential
 * Persistency Validity : ODT CATCGMStreamCoverage
 *
 * Change Documentation 
 *    Previous Status    : Full value fixed size
 *    content Proposal   : Scalable but Relative Tag Value
*/
//  IsRelativeTagValue()  



 /*
 *
 * Origin               : Functionnal
 * Persistency Validity : Scale Management (Management in Header)
*/
CATCGMStreamVersionDECLARE(FactoryHeaderAtBegin,CatCGMStream_2009Fall,0)



//--------------------------------------------------------------------------------------------------------
//
//    Not validated  CatCGMStream_2009Fall
//
//--------------------------------------------------------------------------------------------------------
CATCGMStreamVersionDECLARE(DifferedDeletion,CatCGMStream_2009Fall,0)




#endif
