#ifndef CATCGMExplicitError_h
#define CATCGMExplicitError_h

// COPYRIGHT DASSAULT SYSTEMES 1999
/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "ExportedByCATMathStream.h"
#include "CATMathInline.h"
/**
 * Debug explicit Error
 */
class ExportedByCATMathStream CATCGMExplicitErrorLoad 
{
public:

  /**
  * nodoc.
  */
  static void SetLoadError(const CATUnicodeString &iError);

  /**
  * nodoc.
  */
  static CATBoolean GetLoadError(CATUnicodeString &oError);

  /**
  * nodoc.
  */
  static void ResetLoadError();


private :
 
  /**
   * Data 
   */
  static CATBoolean        _HasError;
  static CATUnicodeString  _Error;
};
 


#endif

