/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 1999 : 
// detection of the context : Replay ODT
//    --> integration of a special treatment
//
//==========================================================================
#ifndef CATCGMIsUnderODT_H
#define CATCGMIsUnderODT_H

#include "CATMathematics.h"
#include "CATBooleanDef.h"
#include "CATCGMVirtual.h"
#include "CATUnicodeString.h"


class CATCGMemoryPOOL;
class CATMathODT;
class CATMathODTCGM;
class CATCXControl;
class CATCGAMeasure;
class CATCGMemoryPOOL_Session;

const int CATCGMIsUnderODT_IntegerNotSet             = -16;

const int CATCGMIsUnderODT_Olk_RegressionStatus      =  87;
const int CATCGMIsUnderODT_Activate_RegressionStatus =  88;
const int CATCGMIsUnderODT_Olk_CorrectionStatus      =  89;

class ExportedByCATMathematics CATCGMIsUnderODT 
{
public :
   //-------------------------------------------------------------------------------------
   // In ODT mode, returns a file beginning  "ADL_ODT_OUT/ODT_LOG_NAME."
   //       that can have a suffix to generate special outputs
   //  const char *MyPrefix = CATCGMIsUnderODT::GetOutput();
   //-------------------------------------------------------------------------------------
   static const char *GetOutput(); 

    //-------------------------------------------------------------------------------------
   // In ODT mode, refential  
   //    "ADL_ODT_IN/OutputRef/ODT_LOG_NAME."
   //    "ADL_ODT_OUT/ODT_LOG_NAME."
   //-------------------------------------------------------------------------------------

   static CATBoolean GetFileReferential(const CATUnicodeString & iSuffixName,
                                        CATUnicodeString       & oReferenceName);

   static CATBoolean GetFileComputed(const CATUnicodeString & iSuffixName,
                                     CATUnicodeString       & oReferenceName);

   //-------------------------------------------------------------------------------------
   // For detection of ODT context
   // Permets de pallier les probleme de contexte de sortie d'ODT
   //-------------------------------------------------------------------------------------
   static CATBoolean IsUnderODT(size_t       iMaxNameLength      = 0,
                                CATBoolean   iWithScenarioName   = FALSE, 
                                char        *iopName             = NULL,
                                size_t      *iopFilledNameLength = NULL); 

   //-------------------------------------------------------------------------------------
   // For the  Performance mode, the odt name has the prefix "PerfOnly_"
   //-------------------------------------------------------------------------------------
   static CATBoolean IsPerfOnly(); 
   
   //-------------------------------------------------------------------------------------
   // For the OLK Defects detection mode
   //-------------------------------------------------------------------------------------
   static int IsUnderOLK(); 
   // static void SetUnderOLK(CATBoolean iMode=TRUE); 

   //-------------------------------------------------------------------------------------
   // For XScale Defects detection mode
   // IsUnderXScale ==  0  no detection ou désactivé selon le contexte Perfo ou autre
   // IsUnderXScale == +1  catcxtol for detection (export CGMCATToleranceErrorDetect=1)
   // IsUnderXScale == +2  catcxtol + catcgmthrow (export CGMCATToleranceErrorThrow=1)
   // IsUnderXScale == +3  same as +2 with deactivation of CGMCATToleranceNoErrorDuringUnStream  
   // IsUnderXScale == +4  same as +3 with a CD instead of a CATCGMThrow (statistic pupose) 
   // IsUnderXScale == +5  same as +4 including purify replay 
   //-------------------------------------------------------------------------------------
   static int  IsUnderXScale(); 
   
   //-------------------------------------------------------------------------------------
   // For the Activate Defects detection mode
   //-------------------------------------------------------------------------------------
   static int IsUnderActivate(); 
 
   //-------------------------------------------------------------------------------------
   // DEDICATED TO INTERNAL USE  
   //-------------------------------------------------------------------------------------
   static void CleanAtExitIfNecessary();

    //-------------------------------------------------------------------------------------
   // In ODT mode, returns the Framework Name
   //-------------------------------------------------------------------------------------
   static const char *GetFwName(); 

    //-------------------------------------------------------------------------------------
   // In ODT mode, returns the Framework Name
   //-------------------------------------------------------------------------------------
   static const char *GetODTName(); 

    //-------------------------------------------------------------------------------------
   // In ODT mode, returns the CGM LOG directory
   //-------------------------------------------------------------------------------------
   static const char *GetWorkspaceLOG(); 
   static const char *GetWorkspaceLOGSave(); 

    //-------------------------------------------------------------------------------------
   // In ODT mode, dedicated synthesis
   //-------------------------------------------------------------------------------------
   static const char *GetCATMathODTLOG(); 

   //-------------------------------------------------------------------------------------
   // For detection of CGM  ODT context (more validation analysis)
   //  It is another mean to detect Batch condition for Debug Tools
   //-------------------------------------------------------------------------------------
   static CATBoolean IsUnder_CATCX_MEMORY_MAIN_FUNCTION(); 

    //-------------------------------------------------------------------------------------
   // TOOLS  : Slash presentation uniforme WINDOWS UNIX
   //-------------------------------------------------------------------------------------
   static	const char DirectorySeparator;

private:
  
  static void _InitWorkspaceLOG();

  static void InitIfNecessary();

  static void InitOLKIfNecessary();
  static void InitXScaleIfNecessary();
  static void InitActivateIfNecessary();

  static void _LocalInitIfNecessary();

  static int         _FirstTime;

  static char       *_OutputName;

  static char       *_InputName;
  static size_t      _LgrInputName;

  static char       *_OdtName;
  static size_t      _LgrOdtName;

  static CATBoolean  _IsPerfOnly;
  static CATBoolean  _IsUnderODT;

  static int         _IsUnderOLK;
  static int         _IsUnderXScale;
  static int         _IsUnderActivate;

#define  CATCGMIsUnderODT_MAXPATHNAME 512

  static CATBoolean  __FwWorkspaceLOGInitialised;

  static CATBoolean  _WithFwWorkspaceLOG;
  static char        _FwWorkspaceLOG[CATCGMIsUnderODT_MAXPATHNAME];

  static CATBoolean  _WithFwWorkspaceLOGSave;
  static char        _FwWorkspaceLOGSave[CATCGMIsUnderODT_MAXPATHNAME];

  static short       _CATMathODTLOG_Init;
  static char        _CATMathODTLOG[CATCGMIsUnderODT_MAXPATHNAME];
 


  friend class CATCGMemoryPOOL;
  friend class CATCGMemoryPOOL_Session;

  friend class CATMathODT;
  friend class CATMathODTCGM;
  friend class CATCXControl;
  friend class CATCGAMeasure;
};
#endif

