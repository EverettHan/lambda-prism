// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2018
// ................................
//
// VB7
// ----------------------------------------------------------------------------//
//==========================================================
// !!!!!!!!!!!!!!!!!!!!!!DO NOT USE!!!!!!!!!!!!!!!!!!!!!!!!!
//==========================================================
// WORK IN PROGRESS VB7 W09 2018

//This utilities is optimized to be created only once for each input CellManifold Journal.
//It should not be re-created for each GetDRepLabelImages call.

#ifndef CATGMDRepLabelUtilities_H
#define CATGMDRepLabelUtilities_H

#include "ListPOfCATDRepLabel.h"
#include "PersistentCell.h"
#include "ListPOfCATBody.h"
#include "CATBoolean.h"
#include "ListPOfCATManifold.h"
#include "IUnknown.h" // For HRESULT
#include "CATPGMDRepLabelUtilities.h"
#include "CATErrorDef.h"
#include "ListPOfCATManifoldParamId.h"

class CATDRepLabel;
class CATCGMJournalList;
class CATDRepLabelAssoc;
class CATGMDRepLabelServices;
class CATTopData;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATDRepLabelIndexTable;
class CATDRepName;
class CATBody;
class CATLiveBody;
class CATPersistentExtTopOperator;
class CATCGMHashTable;

//#define DREPLABEL_TEST_VB7 //To generate DRepLabelServices CGMReplay in our ODTs

class ExportedByPersistentCell CATGMDRepLabelUtilities : public CATPGMDRepLabelUtilities
{
  //CATCGMVirtualDeclareClass(CATGMDRepLabelUtilities);
public:
  //Constructor CGM
  CATGMDRepLabelUtilities(CATSoftwareConfiguration * iConfig);

  //Destructor
  virtual ~CATGMDRepLabelUtilities();

  virtual HRESULT GetDRepLabelImages(CATDRepLabel * iDRepLabel, CATDRepLabelAssoc *& oDRepLabelAssoc);

  virtual CATManifold * GetManifold(CATBody & iBody, const CATDRepLabel * iDRepLabel);  

  virtual CATManifold * GetManifold(const ListPOfCATBody & iBodyList, const CATDRepLabel * iDRepLabel, CATBody **oFoundBody=NULL);

  // Carefull : oParamIDWithValue must be released after use. 
  virtual HRESULT       CreateParamIDWithValue(CATBody * ipBody, const CATDRepLabel * ipDRepLabel, const CATManifoldParamId * ipParamID, CATManifoldParamId *& oParamIDWithValue);

  virtual HRESULT       GetImageManifolds(CATManifold *iInitialManifold, CATBody * ipCurrentBody, CATCGMJournalList *ipCellManifoldJournal, ListPOfCATManifold &oManifoldImageList) const;

  //======================================================================
  //  Static methods
  //======================================================================    
  //@nocgmitf
  static CATDRepName * GetDRepName(const CATDRepLabel * iDRepLabel);

  //@nocgmitf
  static void CreateDRepNameImages(CATDRepName * iDRepName, CATLiveBody & iLiveBody, ListPOfCATManifold & ioImageManifoldList);

  //@nocgmitf
  static void CreateDRepLabelsOnPersistentOpeInputBodies(CATPersistentExtTopOperator * iOpe);

  //@nocgmitf
  static void RunDRepLabelServicesAfterPersistentOpe(CATPersistentExtTopOperator * iOpe);

  //@nocgmitf
  static CATDRepName * IsPublishedManifold(const CATLiveBody *ipLiveBody, CATManifold *ipManifold, ListPOfCATManifoldParamId * oListPubParamId=NULL);

  //@nocgmitf
  static void          GetPublishedManifoldList(const CATLiveBody *ipLiveBody, CATCGMHashTable &oPublishedManifoldHT, CATBoolean iKnowledgeOnly=TRUE);

  //@nocgmitf
  static HRESULT HasPersistentName(const CATLiveBody *ipLiveBody);

  //@nocgmitf
  static HRESULT PushLabelRequest(CATLiveBody *ioLiveBody, CATDRepName * ipDRepName, const ListPOfCATManifold &iManifoldList, const ListPOfCATManifoldParamId &iListParamId);

  //@nocgmitf
  static HRESULT PushLabelRequest(CATLiveBody *ioLiveBody, const CATDRepLabel * ipDRepLabel, const ListPOfCATManifold &iManifoldList, CATManifoldParamId * ipParamId = NULL);

  //@nocgmitf
  static HRESULT RemoveLabelRequest(CATLiveBody *ioLiveBody, const ListPOfCATManifold &iImageManifoldList, const ListPOfCATManifoldParamId &iParamListToUnpublish);

protected:

  //@nocgmitf
  static const CATDRepLabelIndexTable & GetDRepLabelIndexTable(const CATLiveBody & iLiveBody); // LabelIndexTable CONST

  
  friend ExportedByPersistentCell CATGMDRepLabelUtilities * CATCreateGMDRepLabelUtilities(CATGeoFactory            * iFactory,
                                                                                          CATSoftwareConfiguration * iConfig,
                                                                                          ListPOfCATBody           & iInputBodyList, 
                                                                                          ListPOfCATBody           & iOutputBodyList,
                                                                                          CATCGMJournalList        * iCMJournal);

  
  // friend ExportedByPersistentCell CATGMDRepLabelUtilities * CATCreateGMDRepLabelUtilities(CATSoftwareConfiguration * iConfig);

  //Constructor 1
  CATGMDRepLabelUtilities(CATGeoFactory            * iFactory,
                          CATSoftwareConfiguration * iConfig,
                          ListPOfCATBody           & iInputBodyList, 
                          ListPOfCATBody           & iOutputBodyList,
                          CATCGMJournalList        * iCMJournal);


  /**
	* Copy constructor. 
	**/
	CATGMDRepLabelUtilities(CATGMDRepLabelUtilities const& iOther);
	
	/**
	* Assignment operator.
	**/
	CATGMDRepLabelUtilities& operator=(CATGMDRepLabelUtilities const& iOther); 


private :
  CATGMDRepLabelServices * _DRepLabelOperator;
  CATBoolean               _AlreadyRun;
  CATTopData             * _TopData;

};

// create
ExportedByPersistentCell CATGMDRepLabelUtilities * CATCreateGMDRepLabelUtilities(CATGeoFactory            * iFactory,
                                                                                 CATSoftwareConfiguration * iConfig,
                                                                                 ListPOfCATBody           & iInputBodyList, 
                                                                                 ListPOfCATBody           & iOutputBodyList,
                                                                                 CATCGMJournalList        * iCMJournal);

//To use with GetManifold method
ExportedByPersistentCell CATGMDRepLabelUtilities * CATCreateGMDRepLabelUtilities(CATSoftwareConfiguration * iConfig=NULL);

#endif
