#ifndef CATTopCreateBody_H
#define CATTopCreateBody_H
//--------------------------------------------------------------------------------------------------
//
// CATTopCreateBody : Operator which enable the creation with existing domains without activation
//
// Internal use only for CATIA Live Shape :
//
// - Create the operator with the domain list and orientation.
// - Run the operator.
// - Get the Result with GetResult()
//
// Due to partial specifications, correct support may be provided thanks to  :
//    CATTopBodyTools::ChainingSmart(CATBody *iInputBody, CATBody *iOutputBody);
//    CATTopBodyTools::ChainingSmart(const ListPOfCATBody &iInputBodies, CATBody *iOutputBody);
//
//  For instance, have a look on
/*
      CATLiveShapeOperators\CATLiveShapeOperators.m\src\CATLiveShapeBodyServices.cpp

      pBodyCreator = CATPGMCreateTopCreateBody(pGeoFactory, &DomainsTopData, iDomainsList, lLocations);

      if (NULL != pBodyCreator)
      {
         pBodyCreator->Run();
         hResultBody = pBodyCreator->GetResult();

         if ( !! hFirstBody && !! hResultBody )
         {
           CATBody *iInputBody = (CATBody *)hFirstBody;
           CATBody *iOutputBody= (CATBody *)hResultBody;
           CATTopBodyTools::ChainingSmart(iInputBody,hResultBody);
         }
      }

*/
//
//--------------------------------------------------------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
//#include "CATTopData.h"
#include "ListPOfCATDomain.h"
#include "CATListOfInt.h"
#include "ListPOfCATBody.h"
//#include "CATUnicodeString.h"
//#include "CATMathInline.h"

class CATBody;
class CATDomain;
class CATString;
class CATExtTopCreateBody;

//--------------------------------------------------------------------------------------------------

class ExportedByCATTopologicalObjects CATTopCreateBody : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopCreateBody);

public:

  virtual ~CATTopCreateBody ();


  // ---------------------------------------------------------------------------------
  // Force the activation of the result body.
  //
  // This option must be used very carefully !
  // Remember : An activate on a body inactivates every other bodies that
  //            share topology with it. 
  // ---------------------------------------------------------------------------------
  // @nocgmitf
  void ForceActivate(CATBoolean iForce=TRUE);

	//KY1 : 04-02-2011
	/**	@nodoc @nocgmitf*/ 
  static const  CATString  *GetDefaultOperatorId();
    /** @nodoc @nocgmitf */
  virtual const CATString * GetOperatorId();


friend ExportedByCATTopologicalObjects CATTopCreateBody * CATCreateTopCreateBody ( const CATUnicodeString &  iRoleOfOutput,
                                                                                    CATBody                 * iInputBody, 
                                                                                    CATGeoFactory           * iFactory,
                                                                                    CATTopData              * iData,
                                                                                    const CATLISTP(CATDomain) & iDomains,
                                                                                    const CATListOfInt        & iLocations);

  // Official
friend ExportedByCATTopologicalObjects CATTopCreateBody * CATCreateTopCreateBody ( const CATUnicodeString & iRoleOfOutput,
                                                                                  const ListPOfCATBody &iInputBodies,
                                                                                  CATGeoFactory       * iFactory,
                                                                                  CATTopData          * iData,
                                                                                  const CATLISTP(CATDomain) & iDomains);

// Official
friend ExportedByCATTopologicalObjects CATTopCreateBody * CATCreateTopCreateBody (const CATUnicodeString & iRoleOfOutput,
                                                                                  const ListPOfCATBody &iInputBodies,
                                                                                  CATGeoFactory       * iFactory,
                                                                                  CATTopData          * iData,
                                                                                  const CATLISTP(CATDomain) & iDomains,
                                                                                  const CATListOfInt        & iLocations);

friend ExportedByCATTopologicalObjects CATTopCreateBody * CATCreateTopCreateBody ( CATGeoFactory       * iFactory,
																		                                              CATTopData          * iData,
																			                                            const CATLISTP(CATDomain) & iDomains,
                                                                                  const CATListOfInt        & iLocations);

friend ExportedByCATTopologicalObjects CATTopCreateBody * CATCreateTopCreateBody ( CATGeoFactory      * iFactory,
																		                                              CATTopData          * iData,
																			                                            const CATLISTP(CATDomain) & iDomains);

protected :
  /*@nocgmitf*/ 
  CATTopCreateBody(CATGeoFactory * iFactory, CATTopData * iTopData, CATExtTopCreateBody * iImpl);

  /*@nocgmitf*/ 
  virtual int RunOperator();

  /*@nocgmitf*/ 
  CATExtTopCreateBody * GetImpl() const;


  // ---------------------------------------------------
  // CGMReplay Methodes
  // ---------------------------------------------------
  /*@nocgmitf*/ 
  CATExtCGMReplay *  IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /*@nocgmitf*/ 
  virtual void       WriteInput (CATCGMStream & ioStream);


  /*@nocgmitf*/ 
  virtual void       Dump( CATCGMOutput & os );
  /*@nocgmitf*/ 
  virtual void       DumpOutput(CATCGMOutput & os);
  /*@nocgmitf*/ 
  void RequireDefinitionOfInputAndOutputObjects();


  //CATLISTP(CATDomain) _Domains;   // Domain to be added in new body
  //CATListOfInt        _Locations; // Domain location to be added in new body
  //ListPOfCATBody      _InputBodies;
  //CATUnicodeString    _RoleOfOutput;
  //CATBoolean          _ForceActivate;
};

//--------------------------------------------------------------------------------------------------
// Official service for operator creation  
//--------------------------------------------------------------------------------------------------


// Deprecated
ExportedByCATTopologicalObjects CATTopCreateBody * CATCreateTopCreateBody ( const CATUnicodeString &  iRoleOfOutput,
                                                                            CATBody                 * iInputBody, 
                                                                            CATGeoFactory           * iFactory,
                                                                            CATTopData              * iData,
                                                                            const CATLISTP(CATDomain) & iDomains,
                                                                            const CATListOfInt        & iLocations);

// Official
ExportedByCATTopologicalObjects CATTopCreateBody * CATCreateTopCreateBody ( const CATUnicodeString & iRoleOfOutput,
                                                                            const ListPOfCATBody   & iInputBodies,
                                                                            CATGeoFactory          * iFactory,
                                                                            CATTopData             * iData,
                                                                            const CATLISTP(CATDomain) & iDomains);

// Official
ExportedByCATTopologicalObjects CATTopCreateBody * CATCreateTopCreateBody ( const CATUnicodeString & iRoleOfOutput,
                                                                            const ListPOfCATBody &iInputBodies,
                                                                            CATGeoFactory       * iFactory,
                                                                            CATTopData          * iData,
                                                                            const CATLISTP(CATDomain) & iDomains,
                                                                            const CATListOfInt        & iLocations);


// Deprecated
ExportedByCATTopologicalObjects CATTopCreateBody * CATCreateTopCreateBody ( CATGeoFactory       * iFactory,
																		                                        CATTopData          * iData,
																			                                      const CATLISTP(CATDomain) & iDomains,
                                                                            const CATListOfInt        & iLocations);

// Official
ExportedByCATTopologicalObjects CATTopCreateBody * CATCreateTopCreateBody ( CATGeoFactory       * iFactory,
																		                                        CATTopData          * iData,
																			                                      const CATLISTP(CATDomain) & iDomains);


#endif

