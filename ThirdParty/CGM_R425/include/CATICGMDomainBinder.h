#ifndef CATICGMDomainBinder_h
#define CATICGMDomainBinder_h

// COPYRIGHT DASSAULT SYSTEMES 1999
/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 
#include "CATBaseUnknown.h"
#include "ExportedByCATGMGeometricInterfaces.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATICGMDomainBinder ;
#else
extern "C" const IID IID_CATICGMDomainBinder ;
#endif
/**
 * Internal class for the attribute definition.
 * <br>Do not use directly.
 */
class ExportedByCATGMGeometricInterfaces CATICGMDomainBinder: public CATBaseUnknown
{
public:
  CATDeclareInterface;

  /**
   * Returns the domain name.
   */
  virtual const char* GetDomainName()=0 ;
    
};

#endif

