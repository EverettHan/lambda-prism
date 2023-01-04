/* -*-c++-*- */
#ifndef CATCGMExtensionsForPart_H_
#define CATCGMExtensionsForPart_H_
// COPYRIGHT DASSAULT SYSTEMES  2001
//=============================================================================
// Dynamic invokation of CGMV5Interoperability framework
// Dec. 01 Modification interface CATGeoTemporary pour :                  HCN
//               - iOriginalFeature passe en CATBaseUnknown
// Apr. 03 GetDualLoadingJustOccuredCode()                                HCN
// May  03 GetDocumentName(...)                                           HCN
// Jun. 03 GetCATBackCGMVersionDef(...)                                   HCN
// Jul. 04 GetDocumentLastStreamVersion (...)                             MNA
// Oct. 06 Ajout CATCGMLoadStatus etc.                                    JMA
//=============================================================================

#include "CATGeometricObjects.h" 
#include "CATBaseUnknown.h" 
#include "CATBoolean.h"
#include "CATListOfCATUnicodeString.h" 
#include "CATThrowForNullPointer.h" 
#include "CATCGMStreamVersion.h"
#include "CATMathInline.h"
#include "CATOGMCoreIContent.h"
#include "CATNotification.h"
#include "CATListOfCATUnicodeString.h"
#include "CATCGAMeasure.h"

class CATMathTransformation;
class CATTransfoManager;
class CATGeometry;
class CATGeoTemporary;
class CATSoftwareConfiguration;
class CATGeoFactory;
 

class CATCGMStreamDifferentialSave;
class CATCGMStreamIncrementalOpen;
class CATStreamArea;

class CATCGMVersionDefinition;

typedef enum {
	CATCGMUnload  = 0,
	CATCGMPartial = 1,
	CATCGMFull    = 2
} CATCGMLoadStatus;




class CATExtCGMGeom;
 
 

class ExportedByCATGeometricObjects CATCGMExtensionsForPart
{
public:
  //=================================================================
  //  CATGeoTemporary
  //=================================================================
  static HRESULT Create(CATSoftwareConfiguration * iConfig,
                        CATBaseUnknown* iOriginalFeature,
                        CATGeometry* iOriginalGeom,
                        const CATMathTransformation &iTransfo,
                        CATGeoTemporary *& ioResult,
						            CATBoolean iForCoverage = FALSE);


  //---------------------------------------------------------------------------
  // ForceFullLoading (For Mechanichal Modeler)
  //     Synchronisation GenericNaming apres chargement du Dual
  //---------------------------------------------------------------------------
  INLINE static void ForceFullLoading(CATGeoFactory* iFactory, CATBoolean & ioComplementaryLoadingOccured ) ;

  //---------------------------------------------------------------------------
  // IsFullLoaded (For Mechanichal Modeler)
  //     Detection du mode de chargement d'une CATGeoFactory
  //---------------------------------------------------------------------------
  static CATBoolean IsFullLoaded(CATGeoFactory* iFactory) ;
  
    /** 
   * GetMainstreamChangeSetStamp : Access current session change set stamps.
   *    helpfull only for quick comparison but mandatory as prerequiste of other services.
   *
   *    @param iOnCGMGEOM
	 *        Geometrical contents.
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
  INLINE static HRESULT GetMainstreamChangeSetStamp( CATExtCGMGeom    * iOnCGMGEOM ,
                                                     CATULONG64       & oStamp ) ;
 

  /** 
   * GetFederators :  Access current change set values (roots of persistency), so necessary relative.
   *
   *    @param iOnCGMGEOM
	 *        Geometrical contents.
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
  INLINE static HRESULT GetFederators( CATExtCGMGeom              *   iOnCGMGEOM ,
                                       CATOGMCoreSet              * & oSet, 
                                       const CATOGMCoreObjective  &   iPurpose,
                                       CATOGMCoreSet              *   iPreviousState = NULL )  ;


 //---------------------------------------------------------------------------
  // GetCGMContainerLoadStatus (For Mechanichal Modeler)
  //---------------------------------------------------------------------------
  static CATCGMLoadStatus GetCGMContainerLoadStatus(CATGeoFactory* iFactory);

  //---------------------------------------------------------------------------
  // SetCGMContainerToLoadStatus (For Mechanichal Modeler)
  //     initialisation du mode de chargement d'une CATGeoFactory
  //---------------------------------------------------------------------------
  static void SetCGMContainerToLoadStatus(CATGeoFactory* iFactory, CATCGMLoadStatus iHowToLoad);

  //---------------------------------------------------------------------------
  // GetDualLoadingJustOccuredCode (For Mechanichal Modeler)
  //     Synchronisation GenericNaming apres chargement du Dual
  //---------------------------------------------------------------------------
  static const char* GetDualLoadingJustOccuredCode() ;

  //---------------------------------------------------------------------------
  // DualLoadingJustOccured (INTERNAL USE)
  //     Synchronisation GenericNaming apres chargement du Dual
  //---------------------------------------------------------------------------
  static void DualLoadingJustOccured(CATGeoFactory* iFactory) ;


  //---------------------------------------------------------------------------
  // FullLoadingJustOccured (INTERNAL USE)
  //     Synchronisation GenericNaming apres chargement du Dual
  //---------------------------------------------------------------------------
  INLINE static void FullLoadingJustOccured(CATGeoFactory* iFactory) ;


  //---------------------------------------------------------------------------
  // GetDocumentName (INTERNAL USE)
  //     Recuperation du nom de fichier document associe a une factory
  //---------------------------------------------------------------------------
  INLINE static void GetDocumentName(CATGeoFactory* iFactory, CATUnicodeString& oFileName);

  //---------------------------------------------------------------------------
  // GetDocumentLastStreamVersion (INTERNAL USE)
  // Recuperation de la Version Part du document
  //---------------------------------------------------------------------------
  INLINE static void GetDocumentLastStreamVersion (CATGeoFactory* iFactory,CATUnicodeString& oVersion);
 
  //---------------------------------------------------------------------------
  // GetCATBackCGMVersionDef (INTERNAL USE)
  //     Recuperation de la version de sauvegarde lors d'une transaction CATBack
  //---------------------------------------------------------------------------
  INLINE static const CATCGMVersionDefinition* GetCATBackCGMVersionDef(CATCGMStreamVersion& ioRequiredTargetStreamVersion);


  //---------------------------------------------------------------------------
  // ParseDocumentNotification (INTERNAL USE)
  //---------------------------------------------------------------------------
  INLINE static CATBaseUnknown * ParseDocumentNotification(CATNotification* iNotification);

  //---------------------------------------------------------------------------
  // IfWePurgeNonPersistent : 
  //---------------------------------------------------------------------------
  static int  IfWePurgeNonPersistent(CATGeoFactory* iFactory, CATBoolean iWithUndoLog ,  CATLISTV(CATUnicodeString) & oLeaksName , CATGMIfWePurgeNonPersistent & oStats );

  static void CATIfWePurgeNonPersistent_LOG( const CATGMIfWePurgeNonPersistent & iStats, const CATLISTV(CATUnicodeString) & iLeaksName, 
                                             const char * iKindOfOperation,  const char * iDataDomain , int CurrentStep  );

  static void CATIfWePurgeNonPersistent(const int    iBeforeOneShotAfter,  const char * iKindOfOperation,  const char * iDataDomain,  void * iObject) ;

  //---------------------------------------------------------------------------
  // MakeSureFullLoad (For Mechanichal Modeler)
  //---------------------------------------------------------------------------
  static void MakeSureFullLoad(CATGeoFactory* iFactory) ;



protected :

  //---------------------------------------------------------------------------------
  // Pour gestion interne 
  //---------------------------------------------------------------------------------
  virtual ~CATCGMExtensionsForPart();


  //---------------------------------------------------------------------------------
  // Pour implementation CATGeoTemporary
  //---------------------------------------------------------------------------------
  virtual HRESULT _Create(CATSoftwareConfiguration * iConfig,
                          CATBaseUnknown* iOriginalFeature,
                          CATGeometry* iOriginalGeom,
                          const CATMathTransformation &iTransfo,
                          CATGeoTemporary *& ioResult,
						              CATBoolean iForCoverage = FALSE) = 0;

   
   //---------------------------------------------------------------------------------
   // CATCGMStreamDifferentialSave
   //---------------------------------------------------------------------------------
   INLINE static CATCGMStreamDifferentialSave *  CreateDifferentialSave(CATGeoFactory* iFactory, CATStreamArea *iStreamArea);
   virtual       CATCGMStreamDifferentialSave * _CreateDifferentialSave(CATGeoFactory* iFactory, CATStreamArea *iStreamArea) = 0 ;
   
   //---------------------------------------------------------------------------------
   // CATCGMStreamIncrementalOpen
   //---------------------------------------------------------------------------------
   INLINE static CATCGMStreamIncrementalOpen *  CreateIncrementalOpen(const char iFilename[]);
   INLINE static CATCGMStreamIncrementalOpen *  CreateIncrementalOpen(CATGeoFactory *iReadFactory);
   virtual       CATCGMStreamIncrementalOpen * _CreateIncrementalOpen(const char iFilename[]) = 0 ;
   virtual       CATCGMStreamIncrementalOpen * _CreateIncrementalOpen(CATGeoFactory *iReadFactory) = 0 ;

  //---------------------------------------------------------------------------
  // DualLoadingJustOccured (INTERNAL USE)
  //     Synchronisation GenericNaming apres chargement du Dual
  //---------------------------------------------------------------------------
  virtual void _DualLoadingJustOccured(CATGeoFactory* iFactory) = 0 ;

  //---------------------------------------------------------------------------
  // FullLoadingJustOccured (INTERNAL USE)
  //     Synchronisation GenericNaming apres chargement du Dual
  //---------------------------------------------------------------------------
  virtual void _FullLoadingJustOccured(CATGeoFactory* iFactory) = 0 ;


  //---------------------------------------------------------------------------
  // ForceFullLoading (For Mechanichal Modeler)
  //     Synchronisation GenericNaming apres chargement du Dual
  //---------------------------------------------------------------------------
  virtual void _ForceFullLoading(CATGeoFactory* iFactory, CATBoolean & ioComplementaryLoadingOccured ) = 0 ;

 

 //---------------------------------------------------------------------------
  // GetMainstreamChangeSetStamp   GetFederators
  //---------------------------------------------------------------------------
 
    /** 
   * GetMainstreamChangeSetStamp : Access current session change set stamps.
   *    helpfull only for quick comparison but mandatory as prerequiste of other services.
   *
   *    @param iOnCGMGEOM
	 *        Geometrical contents.
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
  virtual HRESULT _GetMainStreamChangeSetStamp( CATExtCGMGeom    * iOnCGMGEOM ,
                                                     CATULONG64       & oStamp ) const = 0 ;
 

  /** 
   * GetFederators :  Access current change set values (roots of persistency), so necessary relative.
   *
   *    @param iOnCGMGEOM
	 *        Geometrical contents.
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
  virtual HRESULT _GetFederators( CATExtCGMGeom              *   iOnCGMGEOM ,
                                  CATOGMCoreSet              * & oSet, 
                                  const CATOGMCoreObjective  &    iPurpose,
                                  CATOGMCoreSet              *   iPreviousState = NULL ) const = 0 ;


  //---------------------------------------------------------------------------
  // GetDocumentName (INTERNAL USE)
  //     Recuperation du nom de fichier CATPart associe a une factory
  //---------------------------------------------------------------------------
  virtual void _GetDocumentName(CATGeoFactory* iFactory, CATUnicodeString& oFileName) = 0;

  //---------------------------------------------------------------------------
  // GetDocumentLastStreamVersion (INTERNAL USE)
  // Recuperation de la Version Part du document
  //---------------------------------------------------------------------------
  virtual void _GetDocumentLastStreamVersion (CATGeoFactory* iFactory,CATUnicodeString& oVersion) = 0;
 
  //---------------------------------------------------------------------------
  // GetCATBackCGMVersionDef (INTERNAL USE)
  //     Recuperation de la version de sauvegarde lors d'une transaction CATBack
  //---------------------------------------------------------------------------
  virtual const CATCGMVersionDefinition* _GetCATBackCGMVersionDef(CATCGMStreamVersion& ioRequiredTargetStreamVersion) = 0;

 //---------------------------------------------------------------------------
  // ParseDocumentNotification (INTERNAL USE)
  //---------------------------------------------------------------------------
  virtual CATBaseUnknown * _ParseDocumentNotification(CATNotification* iNotification) = 0;

  //---------------------------------------------------------------------------------
  // Pour gestion interne 
  //---------------------------------------------------------------------------------
  CATCGMExtensionsForPart();
  static CATCGMExtensionsForPart *   FindCGMImplement();




protected :
  static CATCGMExtensionsForPart *_Gateway;
  static int                     _alreadyInitialised;

  friend class CATCGMStreamIncrementalOpen;
  friend class CATCGMStreamDifferentialSave;
};

 
//---------------------------------------------------------------------------------
// CATCGMStreamDifferentialSave
//---------------------------------------------------------------------------------
INLINE CATCGMStreamDifferentialSave * CATCGMExtensionsForPart::CreateDifferentialSave(CATGeoFactory* iFactory, CATStreamArea *iStreamArea)
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  return bridge ? bridge->_CreateDifferentialSave(iFactory,iStreamArea) : 0 ;
}

//---------------------------------------------------------------------------------
// CATCGMStreamIncrementalOpen 
//---------------------------------------------------------------------------------
INLINE CATCGMStreamIncrementalOpen * CATCGMExtensionsForPart::CreateIncrementalOpen(const char iFilename[])
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  return bridge ? bridge->_CreateIncrementalOpen(iFilename) : 0 ;
}

INLINE CATCGMStreamIncrementalOpen * CATCGMExtensionsForPart::CreateIncrementalOpen(CATGeoFactory *iReadFactory) 
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  return bridge ? bridge->_CreateIncrementalOpen(iReadFactory)  : 0 ;
}


//=================================================================
//  CATGeoTemporary
//=================================================================
INLINE HRESULT CATCGMExtensionsForPart::Create(CATSoftwareConfiguration     * iConfig,
                                        CATBaseUnknown                      * iOriginalFeature,
                                        CATGeometry                         * iOriginalGeom,
                                        const CATMathTransformation         & iTransfo,
                                        CATGeoTemporary                   * & ioResult,
                                        CATBoolean                            iForCoverage)
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  return bridge ? bridge->_Create(iConfig, iOriginalFeature, iOriginalGeom, iTransfo ,ioResult, iForCoverage)  : E_FAIL ;
}

//---------------------------------------------------------------------------
// DualLoadingJustOccured (INTERNAL USE)
//     Synchronisation GenericNaming apres chargement du Dual
//---------------------------------------------------------------------------
INLINE void CATCGMExtensionsForPart::DualLoadingJustOccured(CATGeoFactory *iReadFactory) 
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  if ( bridge ) bridge->_DualLoadingJustOccured(iReadFactory);
}

//-----------------------------------------------------------------------------------------------------------
// FullLoadingJustOccured (INTERNAL USE)
//     Synchronisation GenericNaming apres chargement complte (que ce soit partiel ou complet)
//-----------------------------------------------------------------------------------------------------------
INLINE void CATCGMExtensionsForPart::FullLoadingJustOccured(CATGeoFactory *iReadFactory) 
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  if ( bridge ) bridge->_FullLoadingJustOccured(iReadFactory);
}



//---------------------------------------------------------------------------
// ForceFullLoading (For Mechanichal Modeler)
//     Synchronisation GenericNaming apres chargement du Dual
//---------------------------------------------------------------------------
INLINE void CATCGMExtensionsForPart::ForceFullLoading(CATGeoFactory* iFactory, CATBoolean & ioComplementaryLoadingOccured) 
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  if ( bridge ) bridge->_ForceFullLoading(iFactory,ioComplementaryLoadingOccured);
}
 
 
 

//---------------------------------------------------------------------------
// GetMainstreamChangeSetStamp   GetFederators
//---------------------------------------------------------------------------

INLINE   HRESULT CATCGMExtensionsForPart::GetMainstreamChangeSetStamp(CATExtCGMGeom    * iOnCGMGEOM ,  CATULONG64       & oStamp) 
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  if ( bridge )
    return bridge->_GetMainStreamChangeSetStamp(iOnCGMGEOM,oStamp);
  return E_FAIL;
}


INLINE   HRESULT CATCGMExtensionsForPart::GetFederators( CATExtCGMGeom  *   iOnCGMGEOM , CATOGMCoreSet   * & oSet, const CATOGMCoreObjective & iPurpose,  CATOGMCoreSet   *   iPreviousState )   
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  if ( bridge )
    return bridge->_GetFederators(iOnCGMGEOM,oSet,iPurpose,iPreviousState);
  return E_FAIL;
}



//---------------------------------------------------------------------------
// GetDocumentName (INTERNAL USE)
//     Recuperation du nom de fichier CATPart associe a une factory
//---------------------------------------------------------------------------
INLINE void CATCGMExtensionsForPart::GetDocumentName(CATGeoFactory* iFactory, CATUnicodeString& oFileName)
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  if ( bridge )
    bridge->_GetDocumentName(iFactory, oFileName);
}


  //---------------------------------------------------------------------------
  // GetDocumentLastStreamVersion (INTERNAL USE)
  // Recuperation de la Version Part du document
  //---------------------------------------------------------------------------
INLINE void CATCGMExtensionsForPart::GetDocumentLastStreamVersion (CATGeoFactory* iFactory,CATUnicodeString& oVersion)
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  if ( bridge )
    bridge->_GetDocumentLastStreamVersion(iFactory, oVersion);
}

 
//---------------------------------------------------------------------------
// GetCATBackCGMVersionDef (INTERNAL USE)
//     Recuperation de la version de sauvegarde lors d'une transaction CATBack
//---------------------------------------------------------------------------
INLINE const CATCGMVersionDefinition* CATCGMExtensionsForPart::GetCATBackCGMVersionDef(CATCGMStreamVersion& ioRequiredTargetStreamVersion)
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  if ( bridge )
    return bridge->_GetCATBackCGMVersionDef(ioRequiredTargetStreamVersion);

  return NULL;
}

//---------------------------------------------------------------------------
  // ParseDocumentNotification (INTERNAL USE)
//---------------------------------------------------------------------------
INLINE CATBaseUnknown * CATCGMExtensionsForPart::ParseDocumentNotification(CATNotification* iNotification)
{
  CATCGMExtensionsForPart *bridge = _alreadyInitialised ? CATCGMExtensionsForPart::_Gateway : FindCGMImplement();
  if ( bridge )
    return bridge->_ParseDocumentNotification(iNotification);

  return NULL;
}

 

#endif
