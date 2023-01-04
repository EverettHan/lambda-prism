#ifndef CATCGMStreamObjectTypesCGM_h
#define CATCGMStreamObjectTypesCGM_h
// COPYRIGHT DASSAULT SYSTEMES  2009
//----------------------------------------------------------------------------
//  Persistency.Engineering.Change  "DataBase" 
//
// CGM Object Types
//
//----------------------------------------------------------------------------
//  DO NOT INCLUDE THIS HEADER DIRECTLY
//
//  YOU MAY RATHER USE FOLLOWING HEADER FOR ACCESS TO  ACTIVE PERSISTENCY CHANGE
//      GeometricObjectsCGM\ProtectedInterfaces\ObjectTypesCGM.h
//
//    ROOT INTERNAL DEFINITION IS HOLDED BY
//        CATMathStream\ProtectedInterfaces\CATCGMStreamTypeDEFINE.h
//----------------------------------------------------------------------------
//  Storage : Persistency Change Management   
//----------------------------------------------------------------------------
 
#define CATCGMStreamTypeDECLARE(CGMTypeName,CGMTypeValue,CGMTypeIndex,CGMStreamBinder,CGMLinkedObjectsCount, CGMVersion2010Spring, CGMVersionNeverActivated, IsSmallHeader) \
  CAT##CGMTypeName##Type  = CGMTypeValue, \


#include "CATCGMStreamTypeDEFINE_MAX.h"

enum
{ 

#include "CATCGMStreamTypeDEFINE.h"

 CATCGMStreamTERMINATOR_Name = CATCGMStreamTERMINATOR_Value

};

 


#endif
