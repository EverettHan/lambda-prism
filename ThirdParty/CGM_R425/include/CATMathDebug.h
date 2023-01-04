/* -*-c++-*- */
#ifndef CATMathDebug_H_
#define CATMathDebug_H_
// COPYRIGHT DASSAULT SYSTEMES  2002
//=============================================================================
//  Dynamic invokation of Build-In But Debug Only Software
//=============================================================================
// Jul. 02 Portage 64 bits                                                HCN
// Jan. 04 Gestion WINDOWS floating-point control word _controlfp         HCN
// Apr. 05 Migration de xxxFloatingPointControl(...) vers CATMathDebugCGM,
//         GetPerformanceData_IO(...)                                     HCN
// May. 05 Correction mauvaise lecture des variables d'environnement par
//         les methodes CATMathDebug::::xxxGetEnv(...) presents en entete
//         des fichiers cpp (pb du a l'odre de chargement des librairies
//         CATMathematics et CATMathStream et a l'appel recursif
//         sur CATMathDebug::GetDebugOnly()) :
//            - _OnceForGetEnv,
//            - Passage des methodes abstraites _xxxGetEnv(...) implementee
//              dans CATMathDebugCGM en methodes statiques privees       HCN
//=============================================================================

#include "CATMathematics.h"
#include "CATCGMDebugAvailable.h"
#include "CATDataType.h"
#include "CATListPV.h"
#include <stddef.h>
#include "CATMathInline.h"
#include "CGMVersionDebug.h"

class CATError;
class CATCGMOutput;
class CATCGMErrorLog;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATTrace;

struct CATCGAMEMStats;

#define CATCGMFPControlEnv "CATCGMFPControl"

class CATMathStreamImpl;
class CATMathStreamDump;
class CATCGMemoryPOOL;

class ExportedByCATMathematics CATMathDebug
{
public:

  INLINE static short IsAvailable();

  //-----------------------------------------------------------------------------
  // CATGetEnv Encapsulation controlee des variables d'environnement 
  //-----------------------------------------------------------------------------
  INLINE static int         integerGetEnv(const char* iVariable); // 0     is default Value
  INLINE static CATLONG32   longGetEnv(const char* iVariable);    // 0     is default Value
  INLINE static float       floatGetEnv(const char* iVariable);   // 0.0f  is default Value
  INLINE static double      doubleGetEnv(const char* iVariable);  // 0.0d  is default Value

  INLINE static const char* stringGetEnv(const char* iVariable);  // NULL  is default Value

  INLINE static CATMathStreamDump* CreateCATMathStreamDump(CATMathStreamImpl *master);  // NULL  is default Value

  //-----------------------------------------------------------------------------
  // CATTrace Encapsulation controlee 
  //-----------------------------------------------------------------------------
  INLINE static CATTrace* Trace(const char  TraceName[15], 
                                const char  Comment[], 
                                const short isActivated    = 0,
                                const char  Device[]       = "STDERR", 
                                int         LevelMaxAtInit = 1024 ) ;
  
  INLINE static int TraceIsActive(const char TraceName[15]) ;
  
  //-----------------------------------------------------------------------------
  // Debug of objects deleted without execution of destructor code
  //-----------------------------------------------------------------------------
  INLINE static int RecordCreation(void* iCreatedObject);
  INLINE static int RecordDeletion(void* iDeletedObject);
  INLINE static int RecordDump();

  //-----------------------------------------------------------------------------
  // CATCGAMEM
  //-----------------------------------------------------------------------------
  INLINE static void CATCGAMEM_PrintStats(CATCGMOutput& os);
  INLINE static void CATCGAMEM_GetStats(CATULONG32&      NbStats,
                                        CATCGAMEMStats*& TabStats, 
                                        size_t&          TotalUsed,
                                        size_t&          TotalAlloc,
                                        double&          UsedPercentage);

  //-----------------------------------------------------------------------------
  // CATCGMemoryPOOL
  //-----------------------------------------------------------------------------
  INLINE static int musteChangeExit(int RequestedRC);

  //-----------------------------------------------------------------------------
  // Help_CATCX_MEMORY  class ostream;
  //-----------------------------------------------------------------------------
  INLINE static void Help_CATCX_MEMORY(ostream &iout);

  //-----------------------------------------------------------------------------
  // CGMVersionDebug
  //-----------------------------------------------------------------------------
  INLINE static int                    CGMVersionDebugNumber();
  INLINE static const CGMVersionDebug* CGMVersionDebugAccess(const int idx);
  INLINE static short                  CGM_Versionning(const char* pModificationVersionned);

  //-----------------------------------------------------------------------------
  // Retourne le numero d'une variable de versionning en fonction de son nom.
  // Retourne 0 si la variable donnée n'existe pas.
  //-----------------------------------------------------------------------------
  static short Get_CGMVersionNumber(const char* versionString);

  //-----------------------------------------------------------------------------
  // Retourne le nom d'une variable de versionning en fonction de son numero.
  // Retourne NULL si aucune variable ne correpond au numero spécifié.
  // La chaine retournée doit etre effacée par l'utilisateur avec delete [].
  //-----------------------------------------------------------------------------
  static char* Get_CGMVersionString(const short versionNumber);

  //---------------------------------------------------------------------------------------------------------
  // Programmation la level par default d'une variable
  // Rappel du Prealable indispensable   CATDevelopmentStage=TRUE
  // Priviligiez les services suivants :
  //
  //    Activate_CGM_Versionning
  //    Inactivate_CGM_Versionning
  //    RestoreDefault_CGM_Versionning
  //
  //
  // Set_CGM_Versionning : Par defaut inactivation (0x7FFF) sinon modifie le level d'activation de la modif
  //---------------------------------------------------------------------------------------------------------
  INLINE static short Activate_CGM_Versionning(const char* pModificationVersionned);
  INLINE static short Inactivate_CGM_Versionning(const char* pModificationVersionned);
  INLINE static short RestoreDefault_CGM_Versionning(const char* pModificationVersionned);

  INLINE static short Set_CGM_Versionning(const char* pModificationVersionned, const short iNewLevel = 0x7FFF);
  INLINE static short Reset_CGM_Versionning(const char* pModificationVersionned);
  INLINE static void  Reset_All_CGM_Versionning();

  // Gestion INTEL floating-point control word _controlfp
  INLINE static void DumpFloatingPointControl(ostream& iOut);
  INLINE static unsigned int DecodeFloatingPointControlEnv();
  INLINE static unsigned int SetFloatingPointControl();

  // WINDOWS Performance data : Process File Input\Output
  INLINE static void GetPerformanceData_IO(CATULONG32 ioIO_Read,
                                           CATULONG32 ioIO_Read_Bytes,
                                           CATULONG32 ioIO_Write,
                                           CATULONG32 ioIO_Write_Bytes,
                                           CATULONG32 ioIO_Other,
                                           CATULONG32 ioIO_Other_Bytes);

  // Gestion INTEL floating-point control word _controlfp
  static unsigned int _FPControlMask();
  static unsigned int _FPControlValue();

protected :
  //-----------------------------------------------------------------------------
  // Pour gestion interne 
  //-----------------------------------------------------------------------------
  CATMathDebug();
  virtual ~CATMathDebug();

  //-----------------------------------------------------------------------------
  // CATTrace Encapsulation controlee des variables d'environnement 
  //-----------------------------------------------------------------------------
  virtual CATTrace* _Trace(const char  TraceName[15], 
                           const char  Comment[], 
                           const short isActivated    = 0,
                           const char  Device[]       = "STDERR", 
                           int         LevelMaxAtInit = 1024 ) = 0;

  virtual int _TraceIsActive(const char TraceName[15]) = 0;

  //-----------------------------------------------------------------------------
  // Debug of objects deleted without execution of destructor code
  //-----------------------------------------------------------------------------
  int _RecordCreation(void* iCreatedObject);
  int _RecordDeletion(void* iDeletedObject);
  int _RecordDump();
 
  virtual CATMathStreamDump* _CreateCATMathStreamDump(CATMathStreamImpl *master) = 0; 

  //-----------------------------------------------------------------------------
  // CATCGAMEM
  //-----------------------------------------------------------------------------
  virtual void _PrintStats(CATCGMOutput& os) = 0;
  virtual void _GetStats(CATULONG32&      NbStats,
                         CATCGAMEMStats*& TabStats, 
                         size_t&          TotalUsed,
                         size_t&          TotalAlloc,
                         double&          UsedPercentage) = 0;

  //-----------------------------------------------------------------------------
  // CATCGMemoryPOOL
  //-----------------------------------------------------------------------------
  virtual int _musteChangeExit(int RequestedRC) = 0;

  //-----------------------------------------------------------------------------
  // Help_CATCX_MEMORY  class ostream;
  //-----------------------------------------------------------------------------
  virtual void _Help_CATCX_MEMORY(ostream& iout) = 0;

  //-----------------------------------------------------------------------------
  // CGMVersionDebug
  //-----------------------------------------------------------------------------
  virtual int                     _CGMVersionDebugNumber() = 0;
  virtual const CGMVersionDebug * _CGMVersionDebugAccess(const int idx) = 0;
  virtual short                   _CGM_Versionning(const char* pModificationVersionned) = 0;

  //-----------------------------------------------------------------------------
  // Pour modifier en environnement  CATDevelopmentStage=TRUE
  // par programmation la level par default d'une variable
  //-----------------------------------------------------------------------------
  virtual short _Set_CGM_Versionning(const char* pModificationVersionned, const short iNewLevel) = 0;
  virtual short _Reset_CGM_Versionning(const char* pModificationVersionned) = 0;
  virtual void _Reset_All_CGM_Versionning() = 0;

  // Gestion INTEL floating-point control word _controlfp
  virtual void _DumpFloatingPointControl(ostream& iOut) = 0;
  static unsigned int _DecodeFloatingPointControlEnv();
  virtual unsigned int _SetFloatingPointControl() = 0;

  // WINDOWS Performance data : Process File Input\Output
  virtual void _GetPerformanceData_IO(CATULONG32 ioIO_Read,
                                      CATULONG32 ioIO_Read_Bytes,
                                      CATULONG32 ioIO_Write,
                                      CATULONG32 ioIO_Write_Bytes,
                                      CATULONG32 ioIO_Other,
                                      CATULONG32 ioIO_Other_Bytes) = 0;

  //-----------------------------------------------------------------------------
  // Acces a l'init
  //-----------------------------------------------------------------------------
  static CATMathDebug* GetDebugOnly();

  static CATMathDebug* _Debug;


 static void _DecodeFloatingPointControlEnv(const char*          iCATCGMFPControlEnv,
                                                         unsigned int & ValueToSet,
                                                         unsigned int & MaskToSet
                                                         );

  //---------------------------------------------------------------------------------------------------
  //  Small FootPrint To Be Used Restricted with CATCGMDebugAvailable() without dynamic load 
  //--------------------------------------------------------------------------------------------------- 
public :

  INLINE static int         __integerGetEnv(const char* iVariable);
  INLINE static CATLONG32   __longGetEnv(const char* iVariable);
  INLINE static float       __floatGetEnv(const char* iVariable);
  INLINE static double      __doubleGetEnv(const char* iVariable);
  INLINE static const char* __stringGetEnv(const char* iVariable);

protected :


  // Gestion INTEL floating-point control word _controlfp
  static unsigned int __FPControlMask;
  static unsigned int __FPControlValue;

private :

  static int         _integerGetEnv(const char* iVariable);
  static CATLONG32   _longGetEnv(const char* iVariable);
  static float       _floatGetEnv(const char* iVariable);
  static double      _doubleGetEnv(const char* iVariable);
  static const char* _stringGetEnv(const char* iVariable);

  static short         _Once;
  static short         _OnceForGetEnv;
  static const char*   _pFPControlStr;

  CATListPV    _Records;
  
  friend class CATMathODTCGM;
  friend class CATMathDebugCGM;
  friend class CATCGMemoryPOOL;
};

//-----------------------------------------------------------------------------
// Un peu de typedef
//-----------------------------------------------------------------------------
extern "C" { typedef void INIT_CATMathDebug(); }  
extern "C" { typedef void INIT_CATDebugCGM(); }  

//-----------------------------------------------------------------------------
// IsAvailable
//-----------------------------------------------------------------------------
INLINE short CATMathDebug::IsAvailable()
{
  return ( (_Once || GetDebugOnly()) && _Debug ) ? 1 : 0;
}
 

//-----------------------------------------------------------------------------
// CATCGAMEM_PrintStats
//-----------------------------------------------------------------------------
INLINE void CATMathDebug::CATCGAMEM_PrintStats(CATCGMOutput&os)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_PrintStats(os);
}

//-----------------------------------------------------------------------------
// CATCGAMEM_GetStats
//-----------------------------------------------------------------------------
INLINE void CATMathDebug::CATCGAMEM_GetStats(CATULONG32&      NbStats,
                                             CATCGAMEMStats*& TabStats, 
                                             size_t&          TotalUsed,
                                             size_t&          TotalAlloc,
                                             double&          UsedPercentage)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_GetStats(NbStats, TabStats, TotalUsed, TotalAlloc, UsedPercentage);  
}

//-----------------------------------------------------------------------------
// musteChangeExit
//-----------------------------------------------------------------------------
INLINE int CATMathDebug::musteChangeExit(int RequestedRC)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_musteChangeExit(RequestedRC);
  return RequestedRC;
}

//-----------------------------------------------------------------------------
// Help_CATCX_MEMORY
//-----------------------------------------------------------------------------
INLINE void  CATMathDebug::Help_CATCX_MEMORY(ostream &iout)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_Help_CATCX_MEMORY(iout);
}

//-----------------------------------------------------------------------------
// integerGetEnv
//-----------------------------------------------------------------------------
INLINE int CATMathDebug::integerGetEnv(const char* iVariable)
{
  if (  CATCGMDebugAvailable() )  return CATMathDebug::_integerGetEnv(iVariable);
  return 0;
}

//-----------------------------------------------------------------------------
// longGetEnv
//-----------------------------------------------------------------------------
INLINE CATLONG32 CATMathDebug::longGetEnv(const char* iVariable)
{
  if (  CATCGMDebugAvailable() )  return CATMathDebug::_longGetEnv(iVariable);
  return 0;
}

//-----------------------------------------------------------------------------
// floatGetEnv
//-----------------------------------------------------------------------------
INLINE float CATMathDebug::floatGetEnv(const char* iVariable)
{
  if (  CATCGMDebugAvailable() ) return CATMathDebug::_floatGetEnv(iVariable);
  return 0.0f ;
}

//-----------------------------------------------------------------------------
// doubleGetEnv
//-----------------------------------------------------------------------------
INLINE double CATMathDebug::doubleGetEnv(const char* iVariable)
{
 if (  CATCGMDebugAvailable() )  return CATMathDebug::_doubleGetEnv(iVariable);
  return 0.0;
}

//-----------------------------------------------------------------------------
// stringGetEnv
//-----------------------------------------------------------------------------
INLINE const char* CATMathDebug::stringGetEnv(const char* iVariable)
{
  if (  CATCGMDebugAvailable() ) return CATMathDebug::_stringGetEnv(iVariable);
  return NULL;
}



//---------------------------------------------------------------------------------------------------
//  Small FootPrint To Be Used Restricted with CATCGMDebugAvailable() without dynamic load 
//--------------------------------------------------------------------------------------------------- 

INLINE int CATMathDebug::__integerGetEnv(const char* iVariable)
{
  if (  CATCGMDebugAvailable() ) return CATMathDebug::_integerGetEnv(iVariable);
  return 0;
}

INLINE CATLONG32 CATMathDebug::__longGetEnv(const char* iVariable)
{
  if (  CATCGMDebugAvailable() ) return CATMathDebug::_longGetEnv(iVariable);
  return 0;
}

INLINE float CATMathDebug::__floatGetEnv(const char* iVariable)
{
  if (  CATCGMDebugAvailable() ) return CATMathDebug::_floatGetEnv(iVariable);
  return 0.0f ;
}


INLINE double CATMathDebug::__doubleGetEnv(const char* iVariable)
{
  if (  CATCGMDebugAvailable() ) return CATMathDebug::_doubleGetEnv(iVariable);
  return 0.0;
}


INLINE const char* CATMathDebug::__stringGetEnv(const char* iVariable)
{
  if (  CATCGMDebugAvailable() ) return CATMathDebug::_stringGetEnv(iVariable);
  return NULL;
}



//-----------------------------------------------------------------------------
// Trace
//-----------------------------------------------------------------------------
INLINE CATTrace* CATMathDebug::Trace(const char  TraceName[15], 
                                     const char  Comment[], 
                                     const short isActivated,
                                     const char  Device[], 
                                     int         LevelMaxAtInit) 
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_Trace(TraceName, Comment, isActivated, Device, LevelMaxAtInit);
  return NULL;
}

//-----------------------------------------------------------------------------
// TraceIsActive
//-----------------------------------------------------------------------------
INLINE int CATMathDebug::TraceIsActive(const char TraceName[15]) 
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_TraceIsActive(TraceName);
  return 0;
}

//-----------------------------------------------------------------------------
// Record Creation of an object
//-----------------------------------------------------------------------------
INLINE int CATMathDebug::RecordCreation(void* iCreatedObject) 
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_RecordCreation(iCreatedObject);
  return 0;
}

//-----------------------------------------------------------------------------
// Record Deletion of an object (actual execution of destructor code)
//-----------------------------------------------------------------------------
INLINE int CATMathDebug::RecordDeletion(void* iDeletedObject) 
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_RecordDeletion(iDeletedObject);
  return 0;
}

 
//-----------------------------------------------------------------------------
// CreateCATMathStreamDump
//-----------------------------------------------------------------------------
INLINE CATMathStreamDump* CATMathDebug::CreateCATMathStreamDump(CATMathStreamImpl *master) 
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_CreateCATMathStreamDump(master);
  return 0;
}

//-----------------------------------------------------------------------------
// Dump current list of recorded but undeleted objects
//-----------------------------------------------------------------------------
INLINE int CATMathDebug::RecordDump() 
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_RecordDump();
  return 0;
}

//-----------------------------------------------------------------------------
// CGMVersionDebugNumber
//-----------------------------------------------------------------------------
INLINE int CATMathDebug::CGMVersionDebugNumber() 
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_CGMVersionDebugNumber();
  return 0;
}

//-----------------------------------------------------------------------------
// CATMathDebug
//-----------------------------------------------------------------------------
INLINE const CGMVersionDebug* CATMathDebug::CGMVersionDebugAccess(const int idx) 
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_CGMVersionDebugAccess(idx);
  return NULL;
}

//-----------------------------------------------------------------------------
// CGM_Versionning
//-----------------------------------------------------------------------------
INLINE short CATMathDebug::CGM_Versionning(const char* pModificationVersionned)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_CGM_Versionning(pModificationVersionned);
  return 0;
}

//-----------------------------------------------------------------------------
// Activate_CGM_Versionning
//-----------------------------------------------------------------------------
INLINE short CATMathDebug::Activate_CGM_Versionning(const char* pModificationVersionned)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_Set_CGM_Versionning(pModificationVersionned,1);
  return 0;
}

//-----------------------------------------------------------------------------
// Inactivate_CGM_Versionning
//-----------------------------------------------------------------------------
INLINE short CATMathDebug::Inactivate_CGM_Versionning(const char* pModificationVersionned)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_Set_CGM_Versionning(pModificationVersionned,0x7FFF);
  return 0;
}

//-----------------------------------------------------------------------------
// RestoreDefault_CGM_Versionning
//-----------------------------------------------------------------------------
INLINE short CATMathDebug::RestoreDefault_CGM_Versionning(const char* pModificationVersionned)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->Reset_CGM_Versionning(pModificationVersionned);
  return 0;
}

//-----------------------------------------------------------------------------
// Set_CGM_Versionning
//-----------------------------------------------------------------------------
INLINE short  CATMathDebug::Set_CGM_Versionning(const char* pModificationVersionned, const short iNewLevel)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_Set_CGM_Versionning(pModificationVersionned,iNewLevel);
  return 0;
}

//-----------------------------------------------------------------------------
// Reset_CGM_Versionning
//-----------------------------------------------------------------------------
INLINE short  CATMathDebug::Reset_CGM_Versionning(const char* pModificationVersionned)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_Reset_CGM_Versionning(pModificationVersionned);
  return 0;
}

//-----------------------------------------------------------------------------
// Reset_All_CGM_Versionning
//-----------------------------------------------------------------------------
INLINE void CATMathDebug::Reset_All_CGM_Versionning()
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_Reset_All_CGM_Versionning();
}

//-----------------------------------------------------------------------------
// DumpFloatingPointControl
//-----------------------------------------------------------------------------
INLINE void CATMathDebug::DumpFloatingPointControl(ostream& iOut)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_DumpFloatingPointControl(iOut);
}

//-----------------------------------------------------------------------------
// DecodeFloatingPointControlEnv
//-----------------------------------------------------------------------------
INLINE unsigned int CATMathDebug::DecodeFloatingPointControlEnv()
{
  if (  CATCGMDebugAvailable() ) return _DecodeFloatingPointControlEnv();
  return 0;
}

//-----------------------------------------------------------------------------
// SetFloatingPointControl
//-----------------------------------------------------------------------------
INLINE unsigned int CATMathDebug::SetFloatingPointControl()
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_SetFloatingPointControl();
  return 0;
}

//-----------------------------------------------------------------------------
// GetPerformanceData_IO
//-----------------------------------------------------------------------------
INLINE void CATMathDebug::GetPerformanceData_IO(CATULONG32 ioIO_Read,
                                                CATULONG32 ioIO_Read_Bytes,
                                                CATULONG32 ioIO_Write,
                                                CATULONG32 ioIO_Write_Bytes,
                                                CATULONG32 ioIO_Other,
                                                CATULONG32 ioIO_Other_Bytes)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_GetPerformanceData_IO(ioIO_Read,
                                                                            ioIO_Read_Bytes,
                                                                            ioIO_Write,
                                                                            ioIO_Write_Bytes,
                                                                            ioIO_Other,
                                                                            ioIO_Other_Bytes);
}

#endif
