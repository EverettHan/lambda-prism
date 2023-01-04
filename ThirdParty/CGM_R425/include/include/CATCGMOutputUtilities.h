/* -*-c++-*- */
#ifndef CATCGMOutputUtilities_H
#define CATCGMOutputUtilities_H

#include "ExportedByCATMathStream.h"
#include "CATBoolean.h"
#include "CATError.h"
#include "CATCGMOutput.h"
#include "CATErrorMacros.h"

class ExportedByCATMathStream CATCGMOutputUtilities 
{
  public:
	  
  static void Dump(CATCGMOutput& os, const char* iDescription, const int iValue, const int iDefault, const CATBoolean iOnlyIfNotEqualToDefault=FALSE);
  static void Dump(CATCGMOutput& os, const char* iDescription, const double iValue, const double iDefault, const CATBoolean iOnlyIfNotEqualToDefault=FALSE);
};

/**
* Macros to deactivate temporarily a given CATCGMOutput.
*
* Example:
*
*   DeactivateCGMOutputFromHere(cgmout)
*   {
*     ...
*   } DeactivateCGMOutputUntilHere(cgmout);
*/

#define DeactivateCGMOutputFromHere(CGMOUTPUT)                          \
{                                                                       \
  CATError * __StockErr##CGMOUTPUT = 0;                                 \
  ostream * __SavedOstream##CGMOUTPUT = (ostream *)CGMOUTPUT;           \
                                                                        \
  CGMOUTPUT.ChangeOstream(0);                                           \
                                                                        \
  CATTry                                                                \
  {

#define DeactivateCGMOutputUntilHere(CGMOUTPUT)                         \
  }                                                                     \
  CATCatch(CATError, curerr)                                            \
  {                                                                     \
    __StockErr##CGMOUTPUT = curerr;                                     \
  }                                                                     \
  CATEndTry;                                                            \
                                                                        \
  CGMOUTPUT.ChangeOstream(__SavedOstream##CGMOUTPUT);                   \
                                                                        \
  if (__StockErr##CGMOUTPUT)                                            \
    CATThrow(__StockErr##CGMOUTPUT);                                    \
}


#endif
