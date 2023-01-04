/* -*-c++-*- */
#ifndef CATIToleranceConvertor_h
#define CATIToleranceConvertor_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
/* 
* -------------------------------------------------------------------------------------- 
*   Tolerance convertor behavior of container
* -------------------------------------------------------------------------------------- 
*/
#include "ExportedByCATMathStream.h"
#include "CATBaseUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATMathStream IID IID_CATIToleranceConvertor;
#else
extern "C" const IID IID_CATIToleranceConvertor ;
#endif

/**
  * Definition of tolerance convertor value
  * <tt> Possible values:</tt>
  * <dl>
  * @param <tt>ScaleS   </tt>    <dd>Convertor to small size    ( resolution at 1.e-5 mm , model size at 1 meter      ) 
  * @param <tt>ScaleN   </tt>    <dd>Convertor to standard size ( resolution at 1.e-3 mm , model size at 1 kilometer  ) 
  * @param <tt>ScaleL   </tt>    <dd>Convertor to large size    ( resolution at 0.1   mm , model size at 10 kilometer )   
  * </dl>
  */
#include "CATCGMScaleCategoryDef.h"

/**
* Interface to manage a Redo pattern
*/
class ExportedByCATMathStream CATIToleranceConvertor : public CATBaseUnknown
{
  CATDeclareInterface;

public:
 
  /** 
  * Implement tolerance conversion for container
  *
  *  @param iSizeToConvert    : Size to convert
  * 
  *  @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  virtual HRESULT ConvertTolerance ( const CATCGMScaleCategory  iTargetScale )  = 0 ;


};


CATDeclareHandler( CATIToleranceConvertor, CATBaseUnknown ) ;

#endif



