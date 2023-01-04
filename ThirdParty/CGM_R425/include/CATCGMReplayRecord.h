/* -*-c++-*- */
#ifndef CATCGMReplayRecord_h
#define CATCGMReplayRecord_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
// Jui   02 HCN Portage 64 bits
// Jan   05 NLD Ajout ForceKeepWritingRecord() et mode IfSelected
// 25/09/08 NLD Ajout CATCGMReplayRecordForceKeepWritingRecord()
// 08/01/09 NLD Ajout _CATCGMReplayRecordCurrent et _CATCGMReplayRecordToKeep
//              Ajout InternalCloseOrDeleteWritingRecord()
//              Passage de CATCGMOperator *operateur a
//              InternalCloseWritingRecord(), InternalDeleteWritingRecord()
//              CloseWritingRecord(), DeleteWritingRecord()
// 13/01/09 TCX Integration filtrage c:cgmdbg avec FirstLevel
// 21/06/21 NLD Smart indent
//              friend CATCGMOperatorRun
//=============================================================================

#include "CATGeometricObjects.h"
#include "CATBooleanDef.h"
#include "CATErrorDef.h"
#include "CATDataType.h"
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATCGMReplayLiveAttrInitMode.h"
#include "CATMathInline.h"

#include "CATechMeta.h"

class CATBaseUnknown;
class CATCGMStream;
class CATCGMOperator;
class CATCGMOperatorRun;
class CATUnicodeString;
class CATGeoDebug;
class CATExtCGMReplay;
class CATRootSharedDataCGM;
class CATExtGeoOperator;
 

/**
* Interface to manage geometric scenarii
*/
class ExportedByCATGeometricObjects CATCGMReplayRecord
{
public :
  // --------------------------------------------------------------------------
  //  Identification du mode courant d'enregistrement
  //     Inactive  : pas de generation de Record
  //     Debug     : generation de Record sans la phase posterieure au Run()
  //     ODT       : generation de Record avec sauvegarde de donnees de references
  //     IfCheckKO : generation de Record en mode debug si CheckInput ou CheckOutput KO
  //     IfSelected: generation de Record si selection par soft via ForceKeepWritingRecord()
//                   (N.B ou activation à la volée via breakpoint CATCGMReplayRecordKeep ())
  // --------------------------------------------------------------------------
  enum Mode { Inactive   =  0,
              Debug      = +1,
              ODT        = +2,
              IfCheckKO  = +3,
              IfSelected = +4
            };

  // --------------------------------------------------------------------------
  //  Identification des types d'operateurs acceptes
  //     AllType          : Tous les operateurs
  //     PureGeometrical  : seulement les operateurs geometriques
  //     OnlyTopological  : seulement les operateurs topologiques
  // --------------------------------------------------------------------------
  enum Category { AllType         =  0,
                  PureGeometrical = +1,
                  OnlyTopological = +2 };

  // --------------------------------------------------------------------------
  //    Pour integration dans le Run() de CATCGMOperator()
  // --------------------------------------------------------------------------
  /**
  * Ask if CATCGMReplay is on record mode active
  */
  static CATCGMReplayRecord::Mode IsRecording(CATCGMOperator * operateur,
                                              CATBoolean     * ioCheckInput=NULL,
                                              CATBoolean     * ioCheckOutput=NULL,
                                              int              iCurrentLevel = 0);

  /**
  * Open a CATCGMReplay for registering Before Run()
  */
  static HRESULT      OpenWritingRecord  (CATExtCGMReplay * iFactoryOperator, CATCGMOperator * operateur,
                                          CATCGMStream* &str, size_t &whereDataBegin, short &level);

  /**
  * Close a CATCGMReplay After Run()
  */
  static HRESULT      CloseWritingRecord (CATCGMOperator * operateur, CATCGMStream* &str, const size_t whereDataBegin, const short level);

  /**
  * Delete the CATCGMReplay data without writing them After Run()
  */
  static HRESULT      DeleteWritingRecord(CATCGMOperator * operateur, CATCGMStream* &str, const size_t whereDataBegin, const short level);

  /**
  * Close the CATCGMReplay data without writing them After Run() if selected, delete it otherwise
  */
  static HRESULT      CloseWritingRecordIfSelected
                                         (CATCGMOperator * operateur, CATCGMStream* &str, const size_t whereDataBegin, const short level);

  static void         ForceKeepWritingRecord(int iForceWritingOfNextRecord = 0);
  // --------------------------------------------------------------------------
  //    Pour l'administration de l'activation du mode Record
  // --------------------------------------------------------------------------
  /**
  * change the default directory where playback are registered
  */
  static void         SetRecordDirectory(const char *directory);

  /**
  * change the default prefixe name for CGMReplay files
  */
  static void         SetPrefixeName(const char *prefixe);

  /**
  * change the forced prefixe name for CGMReplay files
  */
  static void         SetForcedPrefixeName(const char *prefixe);

  /**
  * change the default operator 's filter
  * (to capture selected operators)
  */
  static void         SetKeepName(const char *prefixe);


  /**
  * query the default directory where playback are registered
  */
  static const char * GetRecordDirectory();

  /**
  * Ask to change the Record mode, return the previous mode
  */
  static CATCGMReplayRecord::Mode  Set(CATCGMReplayRecord::Mode);


  /**
  * Get the current Record mode
  */
  static INLINE CATCGMReplayRecord::Mode  GetMode() ;

  /**
  * Get the current FilterName
  */
  static const char  * GetKeepName() ;

  /**
  * Get the current FilterName
  */
  static const char  * GetPrefixeName() ;

  /**
  * Get the current Forces Prefix Name
  */
  static const char  * GetForcedPrefixName() ;

  /**
   * Get available Operators (number an array of Identifiers)
   * @param FwNamesFilter
   *   Filtre des noms de frameworks, au format "|fw1|fw2|..."
   */
  static int          GetAvailableOperators(CATUnicodeString * & TabId, const char *FwNamesFilter = NULL) ;
  // NLD180105 transitoire pour correction de l'identificateur en souplesse
  //#ifndef GetAvalaibleOperators
  //#define GetAvalaibleOperators GetAvailableOperators
  //#endif



  /**
  * Get the filter of Operator
  */
  static CATCGMReplayRecord::Category  GetCategory() ;

  /**
  * Change the filter of Operator
  */
  static void         SetCategory(CATCGMReplayRecord::Category  category);

  /**
   * @return
   *   TRUE if only the first geometrical operator will be considered.
   */
  static CATBoolean   CGMReplayFirstGeo();

  /**
   * @return
   *   TRUE if only the first topological operator will be considered.
   */
  static CATBoolean   CGMReplayFirstTopo();

  /**
   * @param iFirstGeo
   *   TRUE if only the first geometrical operator will be considered.
   */
  static void         SetCGMReplayFirstGeo(CATBoolean iFirstGeo);

  /**
   * @param iFirstTopo
   *   TRUE if only the first topological operator will be considered.
   */
  static void         SetCGMReplayFirstTopo(CATBoolean iFirstTopo);


  /**
  *  Change the default overridding mode in the same document
  */
  static void         SetDifferentName(const short iDifferentNames);

  /**
  *  Get the default overridding mode in the same document
  */
  static const short GetDifferentName();


  /**
  *  Change the config mode
  */
  static void         SetOpenConfig(const short iOpenConfig);

  /**
  *  Get the config mode
  */
  static const short  GetOpenConfig();

  /**
  *  Get the config mode
  */
  static unsigned char GetOpenConfigInChar();

  /**
  *  Convert Config Mode from Short to U Char 
  */
  static unsigned char SoftConfigMode_FromShortToUChar(short iConfigMode);

  /**
   *  Changes the live attributes initialization mode
   */
  static void         SetLiveAttrInitMode(CATCGMReplayLiveAttrInitMode iLiveAttrInitMode);

  /**
   *  Gets the live attributes initialization mode
   */
  static CATCGMReplayLiveAttrInitMode GetLiveAttrInitMode();

  /**
  *  Change the Level Inf limit
  */
  static void         SetInfLevelLimit(const char * iInfLevelLimit);

  /**
  *  Init the Level Inf limit
  */
  static void         InitInfLevelLimit();

    /**
  *  Change the Level Inf limit
  */
  static void         SetSupLevelLimit(const char * iSupLevelLimit);

  /**
  *  Init the Level Sup limit
  */
  static void         InitSupLevelLimit();

  //rlad
  /**
  *  Set the LevelVers
  */
  static void         SetLevelVers(const char * iLevelVers);
  //rlaf

  /**
  *  Change the FreeText
  */
  static void         SetFreeText(const char * iFreeText);

  /**
  *  Get the InfLevelLimit
  */
  static const char * GetInfLevelLimit();

  /**
  *  Get the SupLevelLimit
  */
  static const char * GetSupLevelLimit();

  //rlad
  /**
  *  Get the LevelVers
  */
  static const char * GetLevelVers();
  //rlaf

  /**
  *  Get the FreeText
  */
  static const char * GetFreeText();
  
      //----------------------------------- 
      // OnlyFirstLevel
      //----------------------------------- 

  /**
   * @return
   *   TRUE if only the first level of operator is to be considered when record is made.
   */
  static CATBoolean   RecordOnlyFirstLevel();

  /**
   * @param iRecordOnlyFirstLevel
   *   TRUE if only the first level of operator is to be considered when record is made.
   */
  static void         SetRecordOnlyFirstLevel(CATBoolean iRecordOnlyFirstLevel);
  
      //----------------------------------- 
      // OnlyMultipleRun
      //----------------------------------- 

  /**
   * @return
   *   TRUE if only the first level of operator is to be considered when record is made.
   */
  static CATBoolean   RecordOnlyMultipleRun();

  /**
   * @param iRecordOnlyMultipleRun
   *   TRUE if only the first level of operator is to be considered when record is made.
   */
  static void         SetRecordOnlyMultipleRun(CATBoolean iRecordOnlyMultipleRun);
  
    
      //----------------------------------- 
      // NoZipFile
      //----------------------------------- 

  /**
   * @return
   *   TRUE if only the first level of operator is to be considered when record is made.
   */
  static CATBoolean   IsNoZipFile();

  /**
   * @param iNoZipFile
   *   TRUE if only the first level of operator is to be considered when record is made.
   */
  static void         SetNoZipFile(CATBoolean iNoZipFile);
    
      //----------------------------------------------------- 
      //  GraphicalChangeSet (if possible)
      //----------------------------------------------------- 

  /**
   * @return
   *   TRUE if with graphical change set .
   */
  static CATBoolean   WithGraphicalChangeSet();

  /**
   * @param iGraphicalChangeSet
   *   TRUE if with graphical change set.
   */
  static void         SetGraphicalChangeSet(CATBoolean iGraphicalChangeSet);


      //----------------------------------- 
      // DisableMultipleRecording
      //----------------------------------- 

  /**
   * @return
   *   TRUE if only the first level of operator is to be considered when record is made.
   */
  static CATBoolean   RecordDisableMultipleRecording();

  /**
   * @param iRecordOnlyMultipleRun
   *   TRUE if only the first level of operator is to be considered when record is made.
   */
  static void         SetRecordDisableMultipleRecording(CATBoolean iRecordDisableMultipleRecording);
  
  /**
   * @return
   *   TRUE if only a FastRunContext of operator has been defined.
   */
  static CATBoolean   RecordOnlyIfFastRunContext();

  /**
   * @param iRecordOnlyIfFastRunContext
   *   TRUE if only a FastRunContext of operator has been defined.
   */
  static void         SetRecordOnlyIfFastRunContext(CATBoolean iRecordOnlyIfFastRunContext);

  /**
   * @return
   *   TRUE if enable Hidden Seam Cell Creation and Propagation.
   */
  static CATBoolean   IsEnableHiddenSeamCell();
  
  /**
   * @param iEnableHiddenSeamCell
   *   TRUE if enable Hidden Seam Cell Creation and Propagation when record is made.
   */
  static void         SetEnableHiddenSeamCell(CATBoolean iEnableHiddenSeamCell);

  /**
  * @return
  *   TRUE if Force Journaling enabled through the env. var. CATCGMReplayForceJournaling
  */
  static CATBoolean   IsForceJournaling();

    /**
  * @return
  *   TRUE if Disbale Journaling By default through the env. var. CATCGMDisableJournalingByDefault
  */
  static CATBoolean   IsDisableJournalingByDefault();
  
  

  //---------------------------------------------------------------------------------
  // CATCGMReplay
  //---------------------------------------------------------------------------------
  static void         CATCGMReplay(const char *pCGMReplay);
  
  static char  *FilenameRequired(CATCGMOperator * operateur, const short iJustForTest,
                                        const short iForceCaptureMode, const short iForceCheckMode);
   
  //---------------------------------------------------------------------------------------------
  // Internal Use
  //---------------------------------------------------------------------------------------------
  static void         CleanForExit();

  static int          GetLevelFromString(const char * iString);

  static CATBoolean   IsVersLevelActivated(const char *pLevelLimit);

private:

  /** @nodoc  */
  static char       * FilenameRequired(CATCGMOperator * operateur, const short iJustForTest = 0);


  /** @nodoc  */
  /**
  *  Change the Level Inf limit
  */
  static void         SetLevelLimit(const char * iLevelLimit, char ** ioLevelLimit);

  /** @nodoc  */
  /**
  *  Init the Level limit
  */
  static void         InitLevelLimit(char ** ioLevelLimit);

  /** @nodoc  */
  static short                           _IsInitialised;
  static char                          * _RecordDirectory;
  static char                          * _PrefixName;
  static size_t                          _PrefixName_length;// jsx 2014/11/23 si le prefix devient le nom alors cela n'est pas une prefix, car le nom devient le prefix de l'operarteur fils ... et on a du mal a atteindre la 10° generations !
  static char                          * _KeepName;
  static short                           _LastOnly;
  static short                           _PrefixIsInitialised;
  static CATCGMReplayRecord::Mode        _IsRecording;
  static CATLONG32                       _NumberOfRecordDone;
  static char                          * _CurrentFileName;
  static short                           _CheckInputOutput;
  static CATCGMOperator                * _CATCGMReplayRecordOneShot;
  static CATCGMOperator                * _CATCGMReplayRecordCurrent;
  static CATCGMOperator                * _CATCGMReplayRecordToKeep;
  static CATCGMReplayRecord::Category    _Category;
  static CATBoolean                      _CGMReplayFirstGeo;
  static CATBoolean                      _CGMReplayFirstTopo;
  static short                           _OpenConfig; // 0 : Closed Config, 1 : Open Config without Hist, 2 : Soft Config as caugth from customer scenario      (KY1)
  static CATCGMReplayLiveAttrInitMode    _LiveAttrInitMode;
  static short                           _IsInfOrSupLevelLimitRecord; // 1 : Inf Limit Level | 2 : Sup Limit Level | 0 : no limit level requested 
  static char                          * _InfLevelLimit;
  static char                          * _SupLevelLimit;
   //rlad
  static char                          * _LevelVers;

  // filtrage c:cgmdbg  FirstLevel
  static CATBoolean                      _RecordOnlyFirstLevel;
  static CATBoolean                      _RecordOnlyIfFastRunContext;
  static CATBoolean                      _NoZipFile;
  static CATBoolean                      _GraphicalChangeSet;

  // filtrage c:cgmdbg  OnlyMultipleRun
  static CATBoolean                      _RecordOnlyMultipleRun;
  static CATBoolean                      _RecordDisableMultipleRecording;

  //rlaf
  static char                          * _FreeText;
  static HRESULT InternalCloseOrDeleteWritingRecord(int iClose,
                                                    CATCGMOperator * operateur, CATCGMStream* &str, const size_t whereDataBegin, const short level);
  static HRESULT InternalCloseWritingRecord        (CATCGMOperator * operateur, CATCGMStream* &str, const size_t whereDataBegin, const short level);
  static HRESULT InternalDeleteWritingRecord       (CATCGMOperator * operateur, CATCGMStream* &str, const size_t whereDataBegin, const short level);

  //KY1 (31/07/2009)  
  static CATBoolean                      _IsHiddenSeamCell;

  //TCX (21/04/2010)  
  static CATBoolean                      _IsFwName;

  // (12/12/2011)  
  static char                          * _ForcedPrefixName;

  static CATBoolean                     _ForceJournaling;

  static CATBoolean                     _DisableJournalingByDefault;


  /** @nodoc  */
  static void           InitIsRequired();

  friend class CATCGMOperator;
  friend class CATCGMOperatorRun;
  friend class CATGeoDebugCGM;
  friend class CATGeoDebug;
  friend class CATExtCGMReplay;
  friend class CATRootSharedDataCGM;
  friend class CATExtGeoOperator;
 

public :

  INLINE static const CATechMeta & WithNoZipFile(); 

};


//-------------------------------------------------------------------------------------------------
// Internals value for GM developper
//-------------------------------------------------------------------------------------------------

INLINE const CATechMeta & CATCGMReplayRecord::WithNoZipFile() 
{ static const CATechMeta _Dummy("WithNoZipFile",CATechFormat_NoValue); return _Dummy;}


//-----------------------------------------------------------------------------------------------------------
// GetMode : lecture du mode en cours des CATCGMreplay
//-----------------------------------------------------------------------------------------------------------
INLINE CATCGMReplayRecord::Mode  CATCGMReplayRecord::GetMode()
{
  if (_IsInitialised == 0) InitIsRequired();
  return _IsRecording;
}



// pour chargement dynamique
extern "C" ExportedByCATGeometricObjects void CATCGMReplayRecordForceKeepWritingRecord() ;
#endif
