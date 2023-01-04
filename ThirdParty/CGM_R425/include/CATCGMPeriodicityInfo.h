//* -*-c++-*- */
//===========================================================================
// Class CATCGMPeriodicityInfo
//---------------------------------------------------------------------------
// Logical periodicity attribute
// 
//  Default integration made is about
//    1) propagation when transformed
//    2) loss if redefinition occured
//
//  Maintenance on core CGM operations 
//     is made thanks to reproductible scenarios : CGMReplay 
//
//  Integrity is managed from Creator/Assignement 
//     of geometry, not on logical attribute
//
//===========================================================================
#ifndef CATCGMPeriodicityInfo_H
#define CATCGMPeriodicityInfo_H
 
#include "CATMathInline.h"
#include "ExportedByGeometricObjects.h"
#include "CATBoolean.h"
 
#define  CatCGMPeriodicityInfo           short
#define  CatCGMPeriodicity_NotSpecified  0
#define  CatCGMPeriodicity_Numerically   1
 

class CATCGMOutput;
class CATCGMStream;

/**
* Logical periodicity attribute.
*/
class ExportedByGeometricObjects  CATCGMPeriodicityInfo
{
 public :

  /**
  * Unspecified Periodicity Information .
  * 
  */
   INLINE CATCGMPeriodicityInfo();

  /**
  * Set Periodicity Information .
  * @param iInfo
  *    specified or unspecified Info
  * @param iContinuity
  *    iContinuity >= o (if Numerically specified).
  */
  INLINE CATCGMPeriodicityInfo( CatCGMPeriodicityInfo iInfo, const short iContinuity );

  INLINE ~CATCGMPeriodicityInfo();

  /**
  * Get Periodicity Information .
  * @param oInfo
  *    specified or unspecified Info
  * @param oContinuity
  *    oContinuity = -1 (If NotSpecified).
  *    oContinuity >= o (if Numerically specified).
  */
  INLINE void GetInfo( CatCGMPeriodicityInfo & oInfo,  short & oContinuity ) const;


  /**
  * IsSpecified (aka Numerically specified and iContinuity >= 0)
  */
  INLINE CATBoolean IsSpecified() const;
 
  // ...
  INLINE CATCGMPeriodicityInfo(const CATCGMPeriodicityInfo &iCopy);
  INLINE CATCGMPeriodicityInfo& operator=(const CATCGMPeriodicityInfo &iCopy);
 
  // Dump
  void Dump( CATCGMOutput& os );
 
  // Stream
  void Stream(CATCGMStream& Str) const;
  void UnStream( CATCGMStream& Str );
  void UnStreamCompact( CATBoolean IsSpecified, short Continuity );

  // == != 
  INLINE CATBoolean operator == (const CATCGMPeriodicityInfo & iCopy) const;
  INLINE CATBoolean operator != (const CATCGMPeriodicityInfo & iCopy) const;


private :
  CatCGMPeriodicityInfo _Info;
  short                 _Continuity;
};


/**
* inlining.
*/
INLINE CATCGMPeriodicityInfo::CATCGMPeriodicityInfo() 
: _Info(CatCGMPeriodicity_NotSpecified)
, _Continuity(-1)
{}

INLINE CATCGMPeriodicityInfo::CATCGMPeriodicityInfo( CatCGMPeriodicityInfo   iInfo, const short iContinuity )
: _Info(iInfo)
, _Continuity(iContinuity)
{ if (_Info==CatCGMPeriodicity_NotSpecified) _Continuity=-1; if (_Continuity<0) _Continuity=-1; }

INLINE CATCGMPeriodicityInfo::~CATCGMPeriodicityInfo() {}

INLINE void CATCGMPeriodicityInfo::GetInfo( CatCGMPeriodicityInfo & oInfo,  short & oContinuity ) const
{ oInfo = _Info; oContinuity = _Continuity;}

INLINE CATBoolean CATCGMPeriodicityInfo::IsSpecified() const 
{ return ((_Info != CatCGMPeriodicity_NotSpecified) && (_Continuity >= 0)) ? TRUE : FALSE; }

INLINE CATCGMPeriodicityInfo::CATCGMPeriodicityInfo(const CATCGMPeriodicityInfo &iOther) 
{_Info = iOther._Info; _Continuity = iOther._Continuity;}
 
INLINE CATCGMPeriodicityInfo& CATCGMPeriodicityInfo::operator=(const CATCGMPeriodicityInfo &iOther)
{
  if (&iOther == this)  return *this;
  _Info = iOther._Info; _Continuity = iOther._Continuity;
  return *this;
}

INLINE CATBoolean CATCGMPeriodicityInfo::operator==(const CATCGMPeriodicityInfo & iOther) const 
{
  if (this == &iOther) return TRUE; 
  if ( _Info!= iOther._Info ) return FALSE;
  if ( _Continuity != iOther._Continuity ) return FALSE;
  return TRUE;
}

INLINE CATBoolean CATCGMPeriodicityInfo::operator!=(const CATCGMPeriodicityInfo & iOther) const
{
  if (this == &iOther) return FALSE; 
  if ( _Info!= iOther._Info ) return TRUE;
  if ( _Continuity != iOther._Continuity ) return TRUE;
  return FALSE;
}

#endif
