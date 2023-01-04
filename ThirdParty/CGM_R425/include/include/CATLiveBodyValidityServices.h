#ifndef CATLiveBodyValidityServices_H
#define CATLiveBodyValidityServices_H
//-----------------------------------------------------------------------------
// VB7 : Creation                                                   November 17
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2017
//
// USAGE :
//-------
//
// For Natural Shape
//    Allow CGM to define Validity of CATLiveBody
//    Allow Natural Shape to read this validity
//
//-----------------------------------------------------------------------------

#include "CATBoolean.h"
#include "ListPOfCATBody.h"
#include "ExportedByCATTopologicalObjects.h"

/** @nodoc  */
enum CATLiveBodyValidity
{
  CATLiveBodyValidity_Unknown=0,
  CATLiveBodyValidity_NotValid_BestResult,
  CATLiveBodyValidity_NotValid_PatternOut,
  CATLiveBodyValidity_NotValid_PreviewDispatch
};

/** @nodoc  */
class ExportedByCATTopologicalObjects CATLiveBodyValidityServices
{
public:

  //For Natural Shape
  static CATBoolean PassedForValidation(const ListPOfCATBody & iBodyList);

  static CATBoolean PassedForValidation(CATBody * iBody);

  //Internal use only
  // @nocgmitf
  static void SetNotValid(CATBody * iBody, CATLiveBodyValidity iValidity);

  // @nocgmitf
  static CATLiveBodyValidity GetValidity(CATBody * iBody);

};

#endif
