/* -*-c++-*- */
#ifndef CATICGMStreamable_h
#define CATICGMStreamable_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES	1999
//=============================================================================
#include "ExportedByCATMathStream.h"
#include "CATGMAdapter.h"
#include "CATCGMStreamVersion.h"
#include "CATListOfCATString.h"
#include "CATBaseUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATMathStream IID IID_CATICGMStreamable ;
#else
extern "C" const IID IID_CATICGMStreamable ;
#endif

class CATMathStream;
class CATExtCGMReplay;

/**
* Interface to manage persistency with CATMathStream/CACGMStream infrastructure
*/
class ExportedByCATMathStream CATICGMStreamable : public CATGMAdapter
{
  CATDeclareInterface;

public:

  /**
   *  GetOperatorString (Default Basic CATExtCGMReplay implementation)
   */
  virtual const char* const GetOperatorString(void *iObject) =0 ;

  /**
   *  For creation of CATCGMOperator, do not forget to    delete [] sharedlib
   */
  virtual void GetSharedlibOfOperator(const char *iOperatorId, char* & ioSharedlib) =0 ;

  /**
  *  For Avalaible Operator Identificators
	 */
  virtual HRESULT GetAvailableOperators(CATListOfCATString &ioOpIds)=0 ;


  /**
   *  Write Operator (Basic CATExtCGMReplay implementation)
   */
	virtual HRESULT WriteOperator(void         * iObject,
                        CATMathStream        & iStr ,
                        CATCGMStreamVersion    iForceVersion = CatCGMStream_UnknownVersion,
												     short iHowMany = 1 ) =0 ;

  /**
	 * Read Operator (Basic CATExtCGMReplay implementation)
	 */
	virtual HRESULT ReadOperator(CATMathStream& iStr, void * &ioObject ) =0 ;
   

  /**
	 * (Basic CATExtCGMReplay implementation)
	 */
	virtual CATExtCGMReplay *GetCGMExtension()=0 ;
 
};


CATDeclareHandler( CATICGMStreamable, CATBaseUnknown ) ;

#endif



