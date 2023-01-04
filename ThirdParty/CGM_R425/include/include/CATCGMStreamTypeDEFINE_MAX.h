#ifndef CATCGMStreamTypeDEFINE_MAX_h
#define CATCGMStreamTypeDEFINE_MAX_h
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
//        CATMathStream\ProtectedInterfaces\CATCGMStreamTypeDEFINE_MAX.h
//----------------------------------------------------------------------------
//  Storage : Persistency Change Management   
//
//  #define CATCGMStreamTypeDECLARE(CGMTypeName,CGMTypeValue,CGMTypeIndex,...)  
//
//-------------------------------------------------------- 
//    V E R Y     I M P O R T A N T 
//
//     NECESSARY TO UPDATE AFTER EACH CHANGE
//
//  CATMathStream\ProtectedInterfaces\CATCGMStreamTypeDEFINE_MAX.h
//
//----------------------------------------------------------

#define CATCGMStreamTERMINATOR_Name   CATCGMStreamTERMINATORCGMType
#define CATCGMStreamTERMINATOR_Value  902
#define CATCGMStreamTERMINATOR_Index  158
 
#include "ExportedByCATMathStream.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "CATThrowForNullPointer.h"
 
  
extern ExportedByCATMathStream void CATCGMTypeByteIndexToShortValue_INIT(short Value[CATCGMStreamTERMINATOR_Index+1]);
extern ExportedByCATMathStream void CATCGMTypeShortValueToByteIndex_INIT(unsigned char Index[CATCGMStreamTERMINATOR_Value+1]);
extern ExportedByCATMathStream void CATCGMTypeShortValueToLinkObjCount_INIT(short LinkObjCount[CATCGMStreamTERMINATOR_Value+1]);
extern ExportedByCATMathStream void CATCGMTypeShortValueToStaticIsSmallHeader_INIT(short IsSmallHeader[CATCGMStreamTERMINATOR_Value+1]);

 
INLINE unsigned char CATCGMTypeShortValueToByteIndex(short ShortValue)
{
  static unsigned char Index[CATCGMStreamTERMINATOR_Value+1];
  static CATBoolean IndexValuated = FALSE;
  if ( ! IndexValuated )
  {
    IndexValuated = TRUE;
    CATCGMTypeShortValueToByteIndex_INIT(Index);
  }

  unsigned char ByteIndex = ((ShortValue>0) && (ShortValue<CATCGMStreamTERMINATOR_Value)) ? Index[ShortValue] : 0;
  if ( !ByteIndex ) CATThrowForNullPointerReturnValue(ByteIndex);
  return ByteIndex;
}


INLINE short CATCGMTypeByteIndexToShortValue(unsigned char ByteValue)
{
  static short Value[CATCGMStreamTERMINATOR_Index+1];
  static CATBoolean ValueValuated = FALSE;
  if ( ! ValueValuated )
  {
    ValueValuated = TRUE;
    CATCGMTypeByteIndexToShortValue_INIT(Value);
  }

  short ShortValue = ((ByteValue>0) && (ByteValue<=CATCGMStreamTERMINATOR_Index)) ? Value[ByteValue] : 0;
  if ( !ShortValue ) CATThrowForNullPointerReturnValue(ShortValue);
  return ShortValue;
}

INLINE short CATCGMTypeShortValueToLinkObjCount(short ShortValue) 
{
  static short LinkObjCount[CATCGMStreamTERMINATOR_Value+1];
  static CATBoolean CountValuated = FALSE;
  if ( ! CountValuated )
  {
    CountValuated = TRUE;
    CATCGMTypeShortValueToLinkObjCount_INIT(LinkObjCount);
  }

  //short ShortCount = ((ShortValue>0) && (ShortValue<=CATCGMStreamTERMINATOR_Value)) ? LinkObjCount[ShortValue] : 0;
   
  short ShortCount = LinkObjCount[ShortValue];
  return ShortCount;
}

INLINE short CATCGMTypeShortValueIsSmallHeader(short ShortValue)
{
  static short _IsSmallHeader[CATCGMStreamTERMINATOR_Value+1];
  static CATBoolean _IsSmallHeaderValuated = FALSE;
  if ( ! _IsSmallHeaderValuated )
  {
    _IsSmallHeaderValuated = TRUE;
    CATCGMTypeShortValueToStaticIsSmallHeader_INIT(_IsSmallHeader);
  }

  short IsSmallHeader = ((ShortValue>0) && (ShortValue<=CATCGMStreamTERMINATOR_Value))
                      ? _IsSmallHeader[ShortValue] : -1;

  return IsSmallHeader;
}
 

#endif
