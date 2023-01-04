/* -*-c++-*- */
#ifndef CATCGMChainRecordParams_h
#define CATCGMChainRecordParams_h

// COPYRIGHT DASSAULT SYSTEMES 2010

//=============================================================================
//=============================================================================


#include "CATGeometricObjects.h"
#include "CATErrorDef.h"
#include "CATMathInline.h"
#include "CATBoolean.h"

class CATCGMOperator;
//class CATCGMChain;
//class CATCGMStream;

/**
* Interface to manage geometric scenarii
*/
class ExportedByCATGeometricObjects CATCGMChainRecordParams
{
public :

  static   CATBoolean  _IsAuthorized();

  // --------------------------------------------------------------------------
  //  Identification du mode courant d'enregistrement
  //     Inactive  : pas de generation de Record
  //     Debug     : generation de Record sans la phase posterieure au Run()
 
  // --------------------------------------------------------------------------
  enum Mode { Inactive = 0, Debug = +1, RecordAndWriteInRun = +2 };

 
  // --------------------------------------------------------------------------
  //    Pour integration dans le Run() de CATCGMOperator()
  // --------------------------------------------------------------------------
  /**
  * Ask if CATCGMChain is on record mode active
  */
   static INLINE CATCGMChainRecordParams::Mode IsRecording(CATCGMOperator *operateur);

  // static HRESULT WritingRecord(CATCGMChain *chain);
  // static char * GetOdtCaseNameOrFeatureName();

 
  /**
  * query the default directory where playback are registered
  */
  static const char *GetRecordDirectory();
  static void SetRecordDirectory (const char *pDefault);

   static const char *GetRecordName();
  /**
  * Ask to change the Record mode, return the previous mode
  */
  static void SetMode (CATCGMChainRecordParams::Mode iMode);


  /**
  * Get the current Record mode
  */
  static CATCGMChainRecordParams::Mode  GetMode() ;

  

  //---------------------------------------------------------------------------------
  // CATCGMChain
  //---------------------------------------------------------------------------------
  static void Chain(const char *pCGMReplay);
  
 // static char  *FilenameRequired(CATCGMChain *Chain);

  static int GetDepthToRecord();
  static void SetDepthToRecord (int idepth);
   


private:
   static short                          _IsInitialised;
   static char                          *_RecordDirectory;
   static char                          *_Name;
   static char                          *_CurrentFileName;
  // static char                          *_PrefixName;
   static Mode       _IsRecording;
   static short                          _PrefixIsInitialised;
   static int                            _Depth;
  
  /** @nodoc  */
  static void   InitIsRequired();

 // friend class CATCGMChain;


};

//-------------------------------------------------------------------
// Traitement de la vue externe sur la gestion mode Record
//  c'est a dire generation automatique des documents CATCGMReplay
//-------------------------------------------------------------------

INLINE CATCGMChainRecordParams::Mode CATCGMChainRecordParams::IsRecording(CATCGMOperator *operateur)
{
  if (CATCGMChainRecordParams::_IsInitialised == 0) CATCGMChainRecordParams::InitIsRequired();
  return _IsRecording;
}


// pour chargement dynamique
//extern "C" ExportedByCATGeometricObjects void CATCGMChainRecordParamsForceKeepWritingRecord() ;
#endif
