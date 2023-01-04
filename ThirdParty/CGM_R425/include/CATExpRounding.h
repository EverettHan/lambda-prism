//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2010
//==============================================================================================================
// CATExpRounding : Changes / Reset the Rounding control mode. 
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2015/10-xx : RNO : Migration Threadsafe
//  May 2013 - T6L . Delivery in fw CATMathExactPredicate
// 16-Jul-2010 - DNR - Creation.
//==============================================================================================================

#ifndef CATExpRounding_H
#define CATExpRounding_H

#include "CATExpIntervalArithmetic.h"

//#define CheckRounding

class ExportedByCATExpIntervalArithmetic CATExpRounding
{

//==============================================================================================================
// Public Part.
//==============================================================================================================

public :


  /* 
   *constructeur / destructeur
   */
  CATExpRounding();
  virtual ~CATExpRounding();
  /*
  * Reset the rounding mode to its original one.
  **/
  void ResetOriginalMode();

  /*
  * Activate the rounding mode : Nearest, Toward Zero, Minus Infinity and Plus Infinty.
  * The Current rounding is read an saved in order to reset it by ResetOriginalMode.
  **/
  static void SetNearestMode();
  static void SetTowardZeroMode();
  static void SetMinusInfinityMode();
  static void SetPlusInfinityMode();
  /*
  * Reset the rounding mode to its original one.
  **/
  //static void ResetOriginalMode();

#ifdef CheckRounding
  static void CheckRoundingForInterval();
  static void CheckRoundingForRational();
#endif

  enum RoundingMode {
    NearestMode,
    TowardZeroMode,
    MinusInfinityMode,
    PlusInfinityMode,
    UnknownMode
  };
private:

  

  static void _SetNearestMode();
  static void _SetTowardZeroMode();
  static void _SetMinusInfinityMode();
  static void _SetPlusInfinityMode();
  static RoundingMode _GetRoundingMode();


  RoundingMode _OriginalRoundingMode;

} ;
//#ifdef  _WINDOWS_SOURCE
//__declspec( thread)  CATExpRounding::RoundingMode tls_ExpRounding_CurrentRoundingMode= CATExpRounding::_GetRoundingMode();
//#else
//__thread CATExpRounding::RoundingMode tls_ExpRounding_CurrentRoundingMode;
//#endif

  inline void CATExpRounding::SetNearestMode() {
  if (CATExpRounding::_GetRoundingMode() != NearestMode) _SetNearestMode();
};

inline void CATExpRounding::SetTowardZeroMode() {
  if (CATExpRounding::_GetRoundingMode() != TowardZeroMode) _SetTowardZeroMode();
};

inline void CATExpRounding::SetMinusInfinityMode() {
  if (CATExpRounding::_GetRoundingMode() != MinusInfinityMode) _SetMinusInfinityMode();
};

inline void CATExpRounding::SetPlusInfinityMode() {
  if (CATExpRounding::_GetRoundingMode() != PlusInfinityMode) _SetPlusInfinityMode();
};

#endif
