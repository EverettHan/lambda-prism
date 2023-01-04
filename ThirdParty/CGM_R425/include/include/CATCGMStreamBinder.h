#ifndef CATCGMStreamBinder_h
#define CATCGMStreamBinder_h

// COPYRIGHT DASSAULT SYSTEMES 1999
/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 
#include "CATBaseUnknown.h"
#include "ExportedByCATMathStream.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATMathStream IID IID_CATCGMStreamBinder ;
#else
extern "C" const IID IID_CATCGMStreamBinder ;
#endif
/**
 * Internal class for the attribute definition.
 * <br>Do not use directly.
 */
class ExportedByCATMathStream CATCGMStreamBinder: public CATBaseUnknown
{
public:
  CATDeclareInterface;

  /**
   * Returns the domain name.
   */
  virtual void MakeSureInitDone(short iTypeCode) =0 ;
    
};

extern ExportedByCATMathStream void CATCGMStreamBind(short iTypeCode);  

/**
 * Perfo migration / protocole change (Cf MPROC) without QueryInterface
*/
extern  "C"  {  typedef  CATCGMStreamBinder*  CATCGMStreamBinder_Creator();  }     

#endif

