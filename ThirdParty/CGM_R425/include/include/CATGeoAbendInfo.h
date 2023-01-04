#ifndef CATGeoAbendInfo_h
#define CATGeoAbendInfo_h
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
// class CATGeoAbendInfo
//   Une seule instance par
//=============================================================================
// 22/06/21 NLD Ajout CATCGMOperatorRun
//              Smart indent. Detabulation
//=============================================================================
#include "CATAbendInfo.h"
#include "CATMathematics.h"
#include "CATHashDico.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "CATDataType.h"
#include "CATMathInline.h"

#ifndef CAT_ABEND_GEOM_INFO
#define CAT_ABEND_GEOM_INFO                       130
#endif


#define CATGeoAbendInfo_TheOnlyOne_NbDoubles   (((sizeof(CATAbendInfo) + 7) >> 3) + 4)
#define CATGeoAbendInfo_BufferDump_NbBytes      16384
#define CATGeoAbendInfo_BufferDumpLine_NbBytes    512
#define CATGeoAbendInfo_Buffer_MAXLINE             31

class   CATMakePoint;
struct sCATMakePointStep;
class   CATTopOperator;
class   CATCGMOperator;
class   CATCGMOperatorRun;
class   CATMathODTCGM;
class   CATSoftwareConfiguration;

//=============================================================================
//=============================================================================

//-----------------------------------------------------------------------------
// Gestion des echecs d'allocations a CGM
//-----------------------------------------------------------------------------
typedef struct sCATGeoAbend_NoMoreMemory
{
   short     _Detected;
   short     _Forget;
   size_t    _MinimalBytes;
   CATLONG32 _UnclosedGeoFactory;
   CATLONG64 _FlagFactories;
}
CATGeoAbend_NoMoreMemory;


//-----------------------------------------------------------------------------
// Gestion des levees d'erreurs a CGM
//-----------------------------------------------------------------------------
typedef struct sCATGeoAbend_CGMError
{
   int _NumberOfThrow;
   int _NumberOfCreation;
   int _NbReleased;
}
CATGeoAbend_CGMError;


//-----------------------------------------------------------------------------
// Gestion des levees d'erreurs a CGM
//-----------------------------------------------------------------------------
typedef struct sCATGeoAbend_Interrupt
{
   int _NumberOfProgressBar;
   int _NumberOfThrow;
}
CATGeoAbend_Interrupt;


//-----------------------------------------------------------------------------
// Gestion des levees d'erreurs a CGM
//-----------------------------------------------------------------------------
typedef struct sCATGeoAbend_CATGeoFactory
{
   CATULONG64 _NumberOfFactory;
   CATULONG64 _NumberOfCreation;
   CATULONG64 _LoadBytes;
   CATULONG64 _SaveBytes;
}
CATGeoAbend_CATGeoFactory;

//-----------------------------------------------------------------------------
// Gestion des levees d'erreurs a CGMAttribute
//-----------------------------------------------------------------------------
typedef struct sCATGeoAbend_CGMAttribute
{
   CATBoolean       _CDUnstream;
   CATUnicodeString _CurrentUnstream;
   CATHashDico   *  _ThrowUnstream;
}
CATGeoAbend_CGMAttribute;

//-----------------------------------------------------------------------------
// Gestion des niveaux de configuration
//-----------------------------------------------------------------------------
typedef struct sCATGeoAbend_SoftLevel
{
   short       _CGMBSF;
   CATBoolean  _CGMForcedUpgrade;
   CATULONG64  _NbGeoOperators_Run;
   CATULONG64  _NbTopOperators_Create;
   short       _OriginalCGMBSF;
   short       _ForceBSFLevelAllReadConfigs;
}
CATGeoAbend_SoftLevel;

#if ! defined ( ForwardExportedByCATMathStream )
#ifdef _STATIC_SOURCE
#define ForwardExportedByCATMathStream
#elif defined(__CATMathStream)
#define ForwardExportedByCATMathStream DSYExport
#else
#define ForwardExportedByCATMathStream DSYImport
#endif
#include "DSYExport.h"
#endif

class CATSoftwareConfiguration;

ForwardExportedByCATMathStream  void  CATCGMForceBSFLevelAllConfigs  (      short                     iForAllCGMLevel);
ForwardExportedByCATMathStream  short ForceBSFCGMLevel               (      short                     iLevel);
ForwardExportedByCATMathStream  void CATCGMFirstSoftwareConfiguration();
ForwardExportedByCATMathStream  short GetCGMLevel                    (      CATSoftwareConfiguration* iConfig,
                                                                      const char                    * iModifId);
ForwardExportedByCATMathStream  short CATCGMQueryBSFLevelAllConfigs  ();

class CATechSetOfChar;

//=============================================================================
class ExportedByCATMathematics CATGeoAbendInfo : public CATAbendInfo
{
public:

  // Fonctionnalite desiree dediee pour Fw System
         virtual char                    * Dump                         ();
                 void                      DumpForCATCGAMeasure         (CATechSetOfChar  &ioDump);

  // Pour amorcage des statistiques utiles
         static  void                      GenerateTheOnlyOneIfNecessary();
         virtual ~CATGeoAbendInfo();

  // coverage
         static  CATGeoAbendInfo         * HasSomethingToDump           ();

  // Gestion des echecs d'allocations a CGM
         static  CATGeoAbend_NoMoreMemory  _NoMoreMemory;

  // Gestion des levees d'erreurs a CGM
         static  CATGeoAbend_CGMError      _CGMError;

  // Gestion des levees d'erreurs a CGM
         static  CATGeoAbend_Interrupt     _CGMInterrupt;
  
  // Gestion des levees d'erreurs a CGM
         static  CATGeoAbend_CATGeoFactory _CATGeoFactory;
 
  // Gestion des levees d'erreurs a CGMAttribute
         static  CATGeoAbend_CGMAttribute  _CGMAttribute;

  // Direct access (CGMBSF CGMForcedUpgrade NbGeoOperators_Run NbTopOperators_Create )
  INLINE static  short                     Get_CGMBSF                   ();
  INLINE static  CATBoolean                Get_CGMForcedUpgrade         ();
  INLINE static  CATULONG64                Get_NbGeoOperators_Run       ();
  INLINE static  CATULONG64                Get_NbTopOperators_Create    ();

protected :

  
    // Gestion des niveaux de configuration
         static  CATGeoAbend_SoftLevel     _SoftLevel;


  
         static char                       _BufferDump    [CATGeoAbendInfo_BufferDump_NbBytes];
         static char                       _LineBufferDump[CATGeoAbendInfo_BufferDumpLine_NbBytes];

  // Constructeur-Destructeur (cycle de vie reserve)
                                           CATGeoAbendInfo              ();
         static CATGeoAbendInfo          * _TheOnlyOne;

  // Robustesse en cas d'echec d'allocation memoire (preresevation de l'espace memoire)
                void                     * operator new                 (size_t);
                void                       operator delete              (void *);
         static double                    _InstanceArea[CATGeoAbendInfo_TheOnlyOne_NbDoubles];

  // CATCGMExitProcess CATMakePoint
  friend class   CATCGMExitProcess;
  friend class   CATMakePoint;
  friend struct sCATMakePointStep;

  friend class   CATTopOperator;
  friend class   CATCGMOperator;
  friend class   CATCGMOperatorRun;
  friend class   CATMathODTCGM;
  friend class   CATSoftwareConfiguration;

  friend ForwardExportedByCATMathStream  void  CATCGMForceBSFLevelAllConfigs   (      short                     iForAllCGMLevel);
  friend ForwardExportedByCATMathStream  short ForceBSFCGMLevel                (      short                     iLevel         );
  friend ForwardExportedByCATMathStream  void  CATCGMFirstSoftwareConfiguration();
  friend ForwardExportedByCATMathStream  short GetCGMLevel                     (      CATSoftwareConfiguration* iConfig        ,
                                                                                const char                    * iModifId       );
  friend ForwardExportedByCATMathStream  short CATCGMQueryBSFLevelAllConfigs();
};

extern "C" { typedef void CATGMLevelUpgrading(int iValue); }

// Direct access (CGMBSF CGMForcedUpgrade NbGeoOperators_Run NbTopOperators_Create )
INLINE short        CATGeoAbendInfo::Get_CGMBSF()                { return _SoftLevel._CGMBSF;                }
INLINE CATBoolean   CATGeoAbendInfo::Get_CGMForcedUpgrade()      { return _SoftLevel._CGMForcedUpgrade;      }
INLINE CATULONG64   CATGeoAbendInfo::Get_NbGeoOperators_Run()    { return _SoftLevel._NbGeoOperators_Run;    }
INLINE CATULONG64   CATGeoAbendInfo::Get_NbTopOperators_Create() { return _SoftLevel._NbTopOperators_Create; }


#endif
