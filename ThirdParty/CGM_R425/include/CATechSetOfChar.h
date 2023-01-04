#ifndef CATechSetOfChar_h
#define CATechSetOfChar_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//  Helper's as buffer of value between File operations
//-------------------------------------------------------------------------------------------------

#include "CATMathematics.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "CATBoolean.h"


#include "CATErrorDef.h"
#include "CATError.h"


/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

//---------------------------------------------------------------------------------
//  Small wrapper to a piecewise debug Text aggregator
//    Once made one times ; it should be sufficient for next times ... 
// The only purpose is to ease use of the simple need   Fill x Times and Wrtite once ...
//    (with a minimal cost about software writing (user)  and PCS status)
// Simple chain is sufficient  (keep it as simple as needed for implementation)
//---------------------------------------------------------------------------------
class CATechBufferOfChar;

class ExportedByCATMathematics CATechSetOfChar
{
public:

  CATechSetOfChar() ;
  ~CATechSetOfChar() ;

  // First step numerous Fill piecewise of text
  char * Fill( const char TextArea[], const size_t iTextAreaSize = 0, const CATBoolean iWithNULL = FALSE);

  // First step numerous Fill piecewise of text
  char * Fill( const CATechSetOfChar  & iToRead, const CATBoolean iWithNULL = FALSE  );

  // Second step Write all content Buffer inside a FileDescriptor 
  unsigned int  Write( unsigned int Fdumpset );

  // Second step Write all content Buffer inside a CATUnicodeString 
  unsigned int  Write( CATUnicodeString  & oDump  );

  // Second step Write all content Buffer inside a CATUnicodeString 
  unsigned int  Write( ostream &ilogstat );

  // Last step content
  void Empty();

  // compare
  int HasSameContents( const CATechSetOfChar  & iToCompare  ) const;

  // GetContinuousBuffer
  char * GetContinuousBuffer(  size_t & oBufferSize );

  // IsEmpty
  int IsEmpty() const;

  /** 
  * HResultHandling : Helpers for debugging a returned FAILED HRESULT.
  *  while under dedicated Phoenix management
  *       Good Practise :  use CATechHandle::HResultHandling(rc,,) before return or CATThrow;
  *       Bad Practice  :  CATThrowForNullPointerReturnValue(E_FAIL);
  *
  *  @param iHResult  : Value of synthetic HRESULT. 
  *                        
  *
  *  @param iSeverity : Severity of anomalie. 
  *                        CATErrorTypeCritical    : 
  *                        CATErrorTypeFatal       : 
  *                        CATErrorTypeWarning     : 
  *                        CATErrorTypeInformation : 
  *
  *  @param iMessage  : Error Message. 
  *                        Helpers about messaging
  *
  * @return
  *      same as given input argument<br>
  */
  static HRESULT  HResultHandling(HRESULT iHResult, CATErrorType iSeverity = CATErrorTypeCritical, CATError *iMessage = NULL) ;
 

private :
  CATechBufferOfChar   *   _FirstBuffer;
  CATechBufferOfChar   *   _LastBuffer;

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATechSetOfChar(const CATechSetOfChar &iCopy);
  CATechSetOfChar& operator=(const CATechSetOfChar &iCopy);

};

#endif
