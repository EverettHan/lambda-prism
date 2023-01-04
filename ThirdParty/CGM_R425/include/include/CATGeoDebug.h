/* -*-c++-*- */
#ifndef CATGeoDebug_H_
#define CATGeoDebug_H_
// COPYRIGHT DASSAULT SYSTEMES  2002
//=============================================================================
//  Dynamic invokation of Build-In But Debug Only Software
//=============================================================================
// Jul. 02 Portage 64 bits                                                HCN
// Sep. 02 CATCGMJournalFollowTag                                         HCN
// Feb. 05 CATCGMFollowTag_AddRefRelease_ByCGM                            HCN
// 15/06/06 NLD _TagHigh passe en public. (on devrait le prefixer par CATCGMFollowTag_)
// 25/11/06 NLD Ajout CATCGMFollowTag_PointingCGMObject
// 30/11/06 NLD Ajout CATCGMFollowTag_PointingNonCGMObject
// 25/10/07 NLD Ajout CATCGMFollowTag_Touch() et _CATCGMFollowTag_Touch()
//              Ajout Touch() et _Touch()
// 26/10/07 NLD Renommage de Touch() en FollowTouch()
//=============================================================================
#include "ExportedByGeometricObjects.h"
#include "CATCGMEventType.h"
#include "CATDataType.h"

#include <stddef.h>

class CATCGMEvents;
class CATICGMUnknown;
class CATCGMObject;
class CATCGMFusion;
class CATCGMOperator;
class CATExtCGMReplay;
class CATCGMStream;
class CATUnicodeString;
class CATError;
class CATGeometry;
class CATCGMJournalItem;
class CATCGMContainer;
class CATCGMOutput;
class CATICGMObject;

#define CATGeoDebug_CATCGMFeatureMonitor


class ExportedByGeometricObjects CATGeoDebug
{
public:

  inline static short IsAvailable();
  
  //---------------------------------------------------------------------------------
  // CATCGMFollowTag
  //---------------------------------------------------------------------------------
  static  const CATULONG32  CATCGMFollowTag_Unset;
  static  const CATULONG32  CATCGMFollowTag_Inactive;
  static  CATULONG32        CATCGMFollowTag_Tag;
  static  CATULONG32  _TagHigh;
  static  int               CATCGMFollowTag_AddRefRelease_ByCGM;
  static  CATICGMObject*    CATCGMFollowTag_PointingCGMObject ;// pointing object for release/reference
  static  void*             CATCGMFollowTag_PointingNonCGMObject ;// pointing object for release/reference
  inline static void CATCGMFollowTag_init();
  inline static void CATCGMFollowTag_AddRef(CATCGMFusion* obj, CATLONG32 ctr, const CATULONG32  increment, short ByCGM);
  inline static void CATCGMFollowTag_Release(CATCGMFusion* obj, CATLONG32 ctr, const CATULONG32  decrement, short ByCGM);
  inline static void CATCGMFollowTag_Touch(CATCGMObject* obj); // a appeler avec implementation

  // FollowTouch() permet a l'application de simuler le referencement/dereferencement d'un objet
  // declenchant les points d'arret catcxtag et les traces s'il s'agit de l'objet
  // suivi en cours (via export CATCGMFollowTag=)
  // et ce sans les risques d'effacement que l'on aurait via AddRef+Release
  inline static void FollowTouch(CATCGMObject* obj); // a appeler depuis application, avec interface

  //---------------------------------------------------------------------------------
  // CATCGMJournalFollowTag
  //---------------------------------------------------------------------------------
  static  CATULONG32        CATCGMJournalFollowTag_Tag;

  inline static void CATCGMJournalFollowTag_init();
  inline static void CATCGMJournalFollowTag_Report(CATCGMJournalItem* pJournalItem, short* pActiveMode = NULL);
  


  //---------------------------------------------------------------------------------
  // CATCGMOperator
  //---------------------------------------------------------------------------------
  static void BeforeAction(CATCGMOperator *iOperator, CATExtCGMReplay * &FactoryOperator,
    CATCGMStream *&stream, size_t &whereDataBegin,
    short  &level,  short & LevelOfRuntime, short &VersionOfStream,
    const short iRecording );
    
  static void AfterAction(CATCGMOperator *iOperator, CATExtCGMReplay * &FactoryOperator,
    CATCGMStream *&stream, size_t &whereDataBegin,
    short  &level,  short & LevelOfRuntime, short &VersionOfStream,
    const short iRecording , CATError *iErr = NULL);


  
  //---------------------------------------------------------------------------------
  // ....
  //---------------------------------------------------------------------------------
  inline static void PrintCallStack(const char* BeginLine,CATCGMOutput& os);


protected :

  //---------------------------------------------------------------------------------
  // Pour gestion interne 
  //---------------------------------------------------------------------------------
  CATGeoDebug();
  virtual ~CATGeoDebug();

  //---------------------------------------------------------------------------
  // CATCGMFollowTag
  //---------------------------------------------------------------------------
  virtual CATULONG32  _CATCGMFollowTag_init() = 0;
  virtual void _CATCGMFollowTag_AddRef(CATCGMObject* obj, CATLONG32 ctr, const CATULONG32  increment, short ByCGM) = 0;
  virtual void _CATCGMFollowTag_Release(CATCGMObject* obj, CATLONG32 ctr, const CATULONG32  decrement, short ByCGM) = 0;
  virtual void _CATCGMFollowTag_Touch(CATCGMObject* obj) = 0;
  virtual void _Touch(CATCGMObject* obj) = 0;
  //---------------------------------------------------------------------------
  // CATCGMJournalFollowTag
  //---------------------------------------------------------------------------
  virtual CATULONG32  _CATCGMJournalFollowTag_init() = 0;
  virtual void _CATCGMJournalFollowTag_Report(CATCGMJournalItem* pJournalItem, short* pActiveMode = NULL) = 0;
  
   
  //---------------------------------------------------------------------------------
  // ....
  //---------------------------------------------------------------------------------
  virtual void _PrintCallStack(const char* BeginLine,CATCGMOutput& os) = 0;


  //---------------------------------------------------------------------------
  // Acces a l'init
  //---------------------------------------------------------------------------
  static CATGeoDebug *GetDebugOnly();
  static CATGeoDebug *_Debug;
  static short         _Once;

  friend class CATCGMContainer;
};

//-----------------------------------------------------------
// IsAvailable
//-----------------------------------------------------------
inline short CATGeoDebug::IsAvailable()
{
  return ( (_Once || GetDebugOnly()) && _Debug ) ? 1 : 0;
}

//---------------------------------------------------------------------------
// CATCGMFollowTag
//---------------------------------------------------------------------------
inline void  CATGeoDebug::CATCGMFollowTag_init()
{
  CATGeoDebug::CATCGMFollowTag_Tag = CATGeoDebug::CATCGMFollowTag_Inactive;
  if ( (_Once || GetDebugOnly()) && _Debug ) CATCGMFollowTag_Tag = _Debug->_CATCGMFollowTag_init();
}
  
    
//---------------------------------------------------------------------------
// CATCGMFollowTag
//---------------------------------------------------------------------------
inline void  CATGeoDebug::CATCGMFollowTag_AddRef(CATCGMFusion* obj, CATLONG32 ctr, const CATULONG32  increment, short ByCGM)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_CATCGMFollowTag_AddRef((CATCGMObject*)obj,ctr,increment,ByCGM);
}

inline void  CATGeoDebug::CATCGMFollowTag_Release(CATCGMFusion* obj, CATLONG32 ctr, const CATULONG32  decrement, short ByCGM)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_CATCGMFollowTag_Release((CATCGMObject*)obj,ctr,decrement,ByCGM);
}

inline void  CATGeoDebug::CATCGMFollowTag_Touch(CATCGMObject* obj)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_CATCGMFollowTag_Touch(obj);
}

inline void  CATGeoDebug::FollowTouch(CATCGMObject* obj)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_Touch(obj);
}

//---------------------------------------------------------------------------
// CATCGMJournalFollowTag
//---------------------------------------------------------------------------
inline void  CATGeoDebug::CATCGMJournalFollowTag_init()
{
  CATGeoDebug::CATCGMJournalFollowTag_Tag = CATGeoDebug::CATCGMFollowTag_Inactive;
  if ( (_Once || GetDebugOnly()) && _Debug ) CATCGMJournalFollowTag_Tag = _Debug->_CATCGMJournalFollowTag_init();
}

inline void CATGeoDebug::CATCGMJournalFollowTag_Report(CATCGMJournalItem* pJournalItem, short* pActiveMode)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_CATCGMJournalFollowTag_Report(pJournalItem, pActiveMode);
}


//---------------------------------------------------------------------------------
// ....
//---------------------------------------------------------------------------------
inline void CATGeoDebug::PrintCallStack(const char* BeginLine,CATCGMOutput& os)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_PrintCallStack(BeginLine,os);
}



#endif
