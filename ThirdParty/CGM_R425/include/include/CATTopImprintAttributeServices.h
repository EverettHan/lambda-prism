#ifndef CATTopImprintAttributeServices_H
#define	CATTopImprintAttributeServices_H
// COPYRIGHT DASSAULT SYSTEMES  2009
//===========================================================================  
//  Class  CATTopImprintAttributeServices  
//---------------------------------------------------------------------------  
//
//  Class offers services on Imprint Attributes.
//
//  
//===========================================================================  

#include "ExportedByGeometricObjects.h"
#include "CATBoolean.h"

class CATGeoFactory;


/** @nodoc @nocgmitf */
/**
* Class offers services on Imprint Attributes.
*
*
*/

/** @nodoc @nocgmitf */
class ExportedByGeometricObjects CATTopImprintAttributeServices
{
public:
   /** @nodoc @nocgmitf */
   /** 
   * Test whether the factory is activated to manage Imprint Cells Propagation.
   *
   * <br><b>Role</b>: Test whether the factory is activated to manage Imprint Cells Propagation.
   *
   * @param iFactory [in]
   *   The factory under scope
   *
   * @return
   * <dl>
   * <dt><tt>TRUE</tt>     <dd>if succeeded
   * <dt><tt>FALSE</tt>    <dd>if failed
   * </dl>
   *
   */
   static CATBoolean IsActive(CATGeoFactory *iFactory);

   /** @nodoc @nocgmitf */
   /** 
   * Activated the factory to manage Imprint Cells Propagation
   *
   * <br><b>Role</b>: Enables the factory propagate Imprint Cells Propagation
   *
   * @param iFactory [in]
   *   The factory under scope
   *
   */
   static void SetActive(CATGeoFactory *iFactory);

   /** @nodoc @nocgmitf */
   static CATBoolean IsOldImprintAttribute(const char *piImprintAttrName);

   /** @nodoc @nocgmitf */
   static CATBoolean HasOldImprintAttribute(CATGeoFactory *iFactory);

   /** @nodoc @nocgmitf */
   static CATBoolean ForceImprintActivation();

private:
   ~CATTopImprintAttributeServices();
   CATTopImprintAttributeServices();
   CATTopImprintAttributeServices(const CATTopImprintAttributeServices &iCopy);
   CATTopImprintAttributeServices& operator=(const CATTopImprintAttributeServices &iCopy);
};
#endif
