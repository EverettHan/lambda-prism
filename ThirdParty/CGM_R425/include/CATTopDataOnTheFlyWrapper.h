#ifndef CATTopDataInTheFlyWrapper_H
#define CATTopDataInTheFlyWrapper_H

   #define CATTopDataInTheFlyWrapper_UseLocalTopData   "NLD060422: simpler/faster"

//=============================================================================
// Utility class for on the fly topdata creation
//
// - Useful for topological operator use with automatic bridge
//   from old signature with CATSoftwareConfiguration 
//   to   new signature with CATTopData
//
// - handles cases with null software configuration,
//   by creation of an intermediate software configuration with 0 as CGM level
//   (for old operator behaviour)
//   or an open software configuration on demand
//
// - could have been avoided by a new CATTopData constructor creating software configuration if null
//
// Use samples:
//
//   1) for operators requiring a CATTopData pointer
//
//     ClassOperatorTest(CATSoftwareConfiguration* iConfig)
//      : ClassOperatorBase(&CATTopDataOnTheFlyWrapper::GetTopData(CATTopDataOnTheFlyWrapper(iConfig, ...)))
//
//     Caution: in that sample ClassOperatorBase constructor MUST secure data either
//     by copying CATTopData in private data,
//     or using software configuration pointer with mandatory AddRef()

//   2) for operators requiring the address of CATTopData 
//
//     2.a) (basic)
//     CATTopDataOnTheFlyWrapper TopDataWrapper(iConfig);
//     CATTopData*               LocalTopData = &CATTopDataOnTheFlyWrapper::GetTopData(TopDataWrapper);
//     CATXXXOperator*           XXXOperator  = new CATXXXOperator(*LocalTopData, ...);
//
//     2.b) (on the fly)
//     CATXXXOperator*           XXXOperator
//       = new CATXXXOperator(CATTopDataOnTheFlyWrapper::GetTopData(CATTopDataOnTheFlyWrapper TopDataWrapper(iConfig, ...)), ...);
//
//   3) using synthetic macros
//     CATXXXOperator*           XXXOperator
//       = new CATXXXOperator(CATTopDataOnTheFlyWrapperMacroDefaultOpen        (iConfig, iJournal), ...);
//     CATXXXOperator*           XXXOperator
//       = new CATXXXOperator(CATTopDataOnTheFlyWrapperMacroDefaultClosedLevel0(iConfig, iJournal), ...);
//
//=============================================================================
// 26/02/21 NLD Conception/prototype creation for ICM proposal
// 05/04/22 NLD Delivery
// 06/04/22 NLD Constructor added arguments for compatibility with
//              operators creating open configuration
// 06/04/22 NLD _TopData is local instead of allocated
//              GetTopData() method gives back data through address
//              Macro CATTopDataOnTheFlyWrapperMacroDefaultOpen()
//              Macro CATTopDataOnTheFlyWrapperMacroDefaultClosedLevel0()
//=============================================================================
#include "CATGMModelInterfaces.h"
#include "CATSoftwareConfiguration.h"
#include "CATCreateSoftwareConfigurationLicensed.h"
#include "CATTopData.h"
class CATCGMJournalList;

//=============================================================================
// Macros for easy calls
//=============================================================================
// returns the address of a valid CATTopData, with open software configuration if iConfig null
#define CATTopDataOnTheFlyWrapperMacroDefaultOpen(iConfig,iJournal)                          \
        CATTopDataOnTheFlyWrapper::GetTopData(CATTopDataOnTheFlyWrapper(iConfig, iJournal, 1))
// returns the address of a valid CATTopData, with closed software configuration at CGMLevel 0 if iConfig null
#define CATTopDataOnTheFlyWrapperMacroDefaultClosedLevel0(iConfig,iJournal)                  \
        CATTopDataOnTheFlyWrapper::GetTopData(CATTopDataOnTheFlyWrapper(iConfig, iJournal, 0))

//=============================================================================
class ExportedByCATGMModelInterfaces CATTopDataOnTheFlyWrapper
{
 private:
 #ifdef CATTopDataInTheFlyWrapper_UseLocalTopData
   CATTopData  _TopData;
 #else
   CATTopData* _TopData;
 #endif
 public:
                      // TopData is created with iConfig and iJournal
                      // if !iConfig
                      // - by default a software configuration with CGM level 0 is created
                      // - if required with iSOSOpenConfig = 1 an open software configuration
                      //   is created with license iLicense
                      //   (by defaukt no license)
                      //  CAUTION: be conscious, serious and honest with configuration licenses rules
                      // - be aware that topological operators created without software configuration
                      //   internally use an open software configuration
                      //   (unlike geometrical operators)
                      //   so equivalent behaviour is obtained with iSOSOpenConfig = 1
                      CATTopDataOnTheFlyWrapper(      CATSoftwareConfiguration               * iConfig        ,
                                                      CATCGMJournalList                      * iJournal       = NULL,
                                                      int                                      iSOSOpenConfig = 0,
                                                      CATSoftwareConfigurationCreation_License iLicense       = CATSoftwareConfigurationCreation_NotLicensed
                                               );

   virtual           ~CATTopDataOnTheFlyWrapper();

   static       CATTopData& GetTopData         (const CATTopDataOnTheFlyWrapper& iTopDataWrapper);

private:
  // FORBIDDEN copy constructor
  CATTopDataOnTheFlyWrapper                    (const CATTopDataOnTheFlyWrapper& iTopDataWrapper);

  // FORBIDDEN
  // Assignment operator.
  CATTopDataOnTheFlyWrapper& operator =        (const CATTopDataOnTheFlyWrapper& iTopDataWrapper);

};


#endif
