/* -*-c++-*- */
#ifndef CATIGetScale3D_h
#define CATIGetScale3D_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2009
/**
 * @level Private
 * @usage U1
 */
/* 
* -------------------------------------------------------------------------------------- 
*  Access to 3D Scale associated to data modeling 
*     for container, and may be dedicated document integration  
*  to be used only when CATGetTolerance() is not enabled dur to compatibility rules
*      (it means for instance const CATTolerance & CATGetTolerance(CATGeoFactory* iFactory);)
*  For comparison, you may use CATMathFP.h 
*   if ( 0 == CATCompare(iDataScale,iSessionScale) )
* --------------------------------------------------------------------------------------------------- 
*/
#include "YN000MAT.h"
#include "CATBaseUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYN000MAT const IID IID_CATIGetScale3D;
#else
extern "C" const IID IID_CATIGetScale3D ;
#endif

/**
* Access to 3D Scale associated to modeling
*/
class ExportedByYN000MAT CATIGetScale3D : public CATBaseUnknown
{
  CATDeclareInterface;

public:
 
  /** 
  * Access to Scale associated to 3D modeling (to be compared with CATCGMSessionScale)
  *
  *  @param oDataScale    : Scale 
  * 
  *  @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  virtual HRESULT GetDataScale( double & oDataScale ) const  = 0 ;
};


/**
* Access to 3D Scale associated to default Session
*/
extern ExportedByYN000MAT HRESULT CATSessionGetScale3D( double & oDataScale );


CATDeclareHandler( CATIGetScale3D, CATBaseUnknown ) ;


#endif



