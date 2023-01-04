/* -*-c++-*- */
#ifndef CATOGMCoreIContent_h
#define CATOGMCoreIContent_h
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
//-------------------------------------------------------------------------------------------------
#include "ExportedByCATOGMCore.h"
#include "CATOGMCore.h"
#include "CATBaseUnknown.h"
#include "CATOGMCoreObjective.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATOGMCore IID IID_CATOGMCoreIContent;
#else
extern "C" const IID IID_CATOGMCoreIContent ;
#endif

class CATOGMCoreIDomain_var;
class CATechSetOfChar;

/**
*  Helper for a local change set analyser 
*     (as for instance, extraction of applied CATGeoFactory contents depending on embedding mainstream technology )
*/
class ExportedByCATOGMCore CATOGMCoreIContent : public CATBaseUnknown
{
  CATDeclareInterface;

public:
 
 
  /** 
   * GetMainstreamChangeSetStamp : Access current session change set stamps.
   *    helpfull only for quick comparison but mandatory as prerequiste of other services.
   *
   *    @param oStamp
	 *        current session change stamp 
   *
   * @return
   *     Failed if prerequisite internal management is not available 
   *        associated minimal original data format is 2012Spring  .
   *        applied and specified dedicated management is implemented 
   *               with minor increment each times 
   *               with major increment each times dedicated times.
   *
  */ 
  virtual HRESULT GetMainstreamChangeSetStamp( CATULONG64 & oStamp ) const  = 0 ;
 


  /** 
   * GetFederators :  Access current change set values (roots of persistency), so necessary relative.
   *
   *    @param oSet
	 *        current change set.
   *    @param iPurpose
   *       Default purpose for default selection of main roots of persistency
   *         Keep original default value of CATOGMCORE_OBJECTIVE_PERSISTENCY 
   *    @param iComparisonSet
   *        As Change Set is necessary relative to a previous state,
   *
   * @return
   *     Failed if previous method (GetMainstreamChangeSetStamp) is not feasible  unavailable
    *     for instance, minimal original data format is 2012Spring  .
  */ 
  virtual HRESULT GetFederators( CATOGMCoreSet             * & oSet, 
                                 const CATOGMCoreObjective &    iPurpose,
                                 CATOGMCoreSet             *   iPreviousState = NULL ) const  = 0 ;
 

  /** 
    * @nodoc
  *    CreateAtom : GetEquivalent Atom
  */ 
  virtual CATOGMCoreAtom * CreateAtom(CATOGMCORE_DOMAINTYPE   iDomain,
                                      const void             *iObject,
                                      CATOGMCORE_INTENTSTATE  iTodo = CATOGMCORE_INTENTSTATE_TO_CREATE ) const  = 0 ;

  /** 
    * @nodoc
    *    DEBUG Purpose Expand : Manage extension of object with purpose defined through  CATOGMCoreObjective 
  */ 
  virtual HRESULT Expand( CATOGMCoreSet & ioSet, CATOGMCoreObjective & ioContext ) const  = 0 ;
  
  /** 
    * @nodoc
    *     DEBUG Purpose :  
  */ 
  virtual HRESULT Report( CATOGMCoreSet              & ioSet, 
                          CATechSetOfChar            & ioDump, 
                          const CATOGMCoreObjective  & iContext  ) const  = 0 ;

  
  /** 
  * Mandatory : Identify Domain associated to Contents
  */ 
  virtual HRESULT GetDomain( CATOGMCoreIDomain_var &oDomain  ) const   = 0 ;

  
};

CATDeclareHandler( CATOGMCoreIContent, CATBaseUnknown ) ;
 
#endif
