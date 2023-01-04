/* -*-c++-*- */
#ifndef CATOGMCoreIDomain_h
#define CATOGMCoreIDomain_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2009
/**
 * @level Private
 * @usage U1
 */

//-------------------------------------------------------------------------------------------------
// Be Carefull about limited scope of this interface
//   high performance computation could not rely on central main memory management 
//
// Short term local transaction (change set acquisition)   
//    for extended N1 Operators on statefull modelisation
// Not to used by applied integration 
//    Dedicated to core kernel GM Component based modeler
//
// Cf  Oxxx Geomerical Modeler 
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Core Persistent Structure Management
//-------------------------------------------------------------------------------------------------
#include "ExportedByCATOGMCore.h"
#include "CATOGMCore.h"
#include "CATBaseUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATOGMCore IID IID_CATOGMCoreIDomain;
#else
extern "C" const IID IID_CATOGMCoreIDomain ;
#endif

/**
*  Domain manager relative to  CATOGMCORE_DOMAINTYPE 
*  Helper to convert generic multiples domains (runtimeview objects)
*     into a common persistent centric protocols
*  N.B : binded Atoms are provided from specific services of domaines
*/
class ExportedByCATOGMCore CATOGMCoreIDomain : public CATBaseUnknown
{
  CATDeclareInterface;

public:
 
  /** 
  * Mandatory : GetCoreHead of object of Domain
  */ 
  virtual HRESULT GetCoreHead( const void *iBind, CATOGMCoreHead &oHead ) const  = 0 ;

 
};

CATDeclareHandler( CATOGMCoreIDomain, CATBaseUnknown ) ;

#endif

