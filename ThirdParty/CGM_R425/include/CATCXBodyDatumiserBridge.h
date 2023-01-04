/* -*-c++-*- */
#ifndef CATCXBodyDatumiserBridge_H
#define CATCXBodyDatumiserBridge_H
// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
//  Dedicated to CATCXBodyDatumiser needs onto Boolean and Healing operators
//=============================================================================
#include "CATIACGMLevel.h"

#include "ExportedByCATTopologicalObjects.h"
#ifdef CATIACGMR216CAA
#include "CATBodyDatumiserCheckStatus.h"
#endif

#include "CATListOfCATICGMObjects.h"

class CATGeoFactory;
class CATBody;
class CATMathTransformation;
class CATSoftwareConfiguration;
class CATCGMJournalList;
class CATError;
class CATCGMHashTable;


//
class ExportedByCATTopologicalObjects CATCXBodyDatumiserBridge
{
public:
	virtual ~CATCXBodyDatumiserBridge();

#ifdef CATIACGMR216CAA
	static CATBodyDatumiserCheckStatus CheckBeforePreliminaryClipping  (CATGeoFactory* iFactory , 
	                                                                    CATBody * iBodyToClip,
	                                                                    CATMathTransformation * iMathTransfo) ;  
#endif
  static CATBody  *  MakePreliminaryClipping (CATGeoFactory* iFactory , 
	                                            CATBody * iBodyToClip,
	                                            CATMathTransformation * iMathTransfo, 
                                              CATSoftwareConfiguration  *iConfig , 
                                              CATCGMJournalList * ioJournal,
                                              CATLISTP(CATICGMObject) & ioOutputMapping ,
                                              int & ioStatus, 
                                              CATLISTP(CATICGMObject) & ioFittedObjects ) ; 

  static CATBody  *  MakeSecondaryHealing    (CATBody * iOriginalBody
                                             ,CATBody * iBodyToHeal
	                                           ,CATSoftwareConfiguration  *iConfig  
                                             ,CATCGMJournalList * ioJournal  
                                             ,CATLISTP(CATICGMObject) & ioOutputMapping ) ;  

  static CATError *  RunDataChecker          (CATGeoFactory* iFactory , 
                                              CATBody * iOriginalBody, 
                                              CATBody * iBodyToCheck,
                                              CATSoftwareConfiguration  *iConfig ,
                                              CATLISTP(CATICGMObject) & ioFittedObjects );
protected:
	CATCXBodyDatumiserBridge();
	
#ifdef CATIACGMR216CAA
  virtual CATBodyDatumiserCheckStatus _CheckBeforePreliminaryClipping (CATGeoFactory            * iFactory , 
                                                                       CATBody                  * iBodyToClip,  
                                                                       CATMathTransformation    * iMathTransfo)= 0;
#endif

  virtual CATBody *  _MakePreliminaryClipping (CATGeoFactory* iFactory  
	                                            ,CATBody * iBodyToClip
	                                            ,CATMathTransformation * iMathTransfo 
                                              ,CATSoftwareConfiguration  *iConfig  
                                              ,CATCGMJournalList * ioJournal
                                              ,CATLISTP(CATICGMObject) & ioOutputMapping)= 0;

  virtual CATBody *  _MakePreliminaryReframe  (CATGeoFactory* iFactory  
	                                            ,CATBody * iBodyToReframe
                                              ,CATMathTransformation * iMathTransfo 
	                                            ,CATSoftwareConfiguration  *iConfig  
                                              ,CATCGMJournalList * ioJournal
                                              ,CATLISTP(CATICGMObject) & ioOutputMapping)= 0;

   virtual CATBody *  _MakePreliminaryRegularization  (CATGeoFactory* iFactory  
	                                                    ,CATBody * iBodyToRegul
                                                      ,CATSoftwareConfiguration  *iConfig
                                                      ,CATCGMJournalList * ioJournal 
                                                      ,CATLISTP(CATICGMObject) & ioOutputMapping)= 0;

  virtual CATBody *  _MakePreliminaryFitting  (CATGeoFactory* iFactory  
                                              ,CATBody * iBodyToFit
                                              ,CATSoftwareConfiguration  * iConfig
                                              ,CATCGMJournalList * ioJournal
                                              ,CATLISTP(CATICGMObject) & ioOutputMapping
                                              ,CATLISTP(CATICGMObject) & ioFittedObjects  )= 0;

  virtual CATBody *  _MakeSecondaryHealing    (CATBody * iOriginalBody
                                              ,CATBody * iBodyToHeal
	                                            ,CATSoftwareConfiguration  *iConfig
                                              ,CATCGMJournalList * ioJournal 
                                              ,CATLISTP(CATICGMObject) & ioOutputMapping)= 0;


  virtual CATError * _RunDataChecker          (CATGeoFactory* iFactory , 
                                               CATBody * iOriginalBody, 
                                               CATBody * iBodyToCheck,
                                               CATSoftwareConfiguration  *iConfig,
                                               CATLISTP(CATICGMObject) & ioFittedObjects )= 0;
private:
  static CATCXBodyDatumiserBridge * GetBodyDatumiserBridgeImpl();
	
};
//----------------------------------------------------------------------------------------------------------------

#endif
