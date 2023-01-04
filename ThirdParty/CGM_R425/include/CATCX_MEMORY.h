/* -*-c++-*- */
/**
* @COPYRIGHT DASSAULT SYSTEMES 2009
*/
#ifndef CATCX_MEMORY_H 
#define CATCX_MEMORY_H 
//=============================================================================
// DESCRIPTION : For analysis Knowledge 
/*
   Debug purpose only
*/
//=============================================================================
#include "ExportedByCATMathStream.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "CATDataType.h"
#include "CATUnicodeString.h"
  
class CATMathODTCGM;
class CATechSetOfChar;

const CATULONG32  CATCGMFollowTag_Unset = 0xFFFFFFFF;

/**
* unified documentation on debug needs to avoid numerous static, 
*/
class ExportedByCATMathStream CATCX_MEMORY
{
public :

  /**
  * CGMLog. genuine CGM logging 
  */
  INLINE static  CATBoolean CGMLog(const char iFilterOperatorName[]);

  /**
  * CGMLog. genuine CGM logging 
  */
  static  void              CGMLogLine(const char iFilterOperatorName[], CATechSetOfChar & iContent);

  /**
  * CGMLog. genuine CGM logging 
  */
  static  void              CGMLogLastWrotenCGMReplay(CATUnicodeString & iFileName, const CATBoolean iClose=FALSE);

  /**
  * CATCGMActivateTraces.  NewTopologicalObjects
  *   reporting on reverse topological links build
  */
  INLINE static  CATBoolean CATCGMActivateTraces();

  /**
  * CATCGMActivateStatistics.  NewTopologicalObjects
  *   reporting on reverse topological links build
  */
  INLINE static  CATBoolean CATCGMActivateStatistics();

  /**
  * CATCGMActivateFullTraces.  NewTopologicalObjects
  *   FULL  reporting on reverse topological links build
  */
  INLINE static  CATBoolean CATCGMActivateFullTraces();

  /**
  * CATCGMActivateFollowTag.  NewTopologicalObjects
  *   reporting on reverse topological links deactivation for a given CATBody Tag to follow
  */
  INLINE static  CATULONG32 CATCGMActivateFollowTag();

  /**
  * PCS Data Validation (see Performance Interlocutor Requirement)
  *  Value equals = Bytes overhead on CATGeoFactory * persistency
  *  for compact stream criteria validation 
  *    set/export CATCX_MEMORY=Tare=1048576
  */
  INLINE static  CATLONG32 CGMTare();

  /**
  * Persistency Risky partial recovery attempt  
  */
  INLINE static  CATBoolean RiskyPartialRecovery();


  /**
   * For JMA/JHN  
   *    set/export CATCX_MEMORY=reorder
 */
	enum ReOrderObject 
	{ ReOrderBody=0, ReOrderLoop=1, ReOrderLump=2, ReOrderShell=3 };

	INLINE static  CATBoolean ReOrder(CATCX_MEMORY::ReOrderObject iIndex);

  /**
   * ReOrderRange  
   *    range are given inside [ 0, iNbElems - 1 ] 
 */
  static  void ReOrderRange(const CATULONG32 iNbElems, CATULONG32 * oNewRange );

  /**
   * For FDN  
   *  CheckUpThrow
 */
  INLINE static  CATBoolean CheckUpThrow();

  /**
  * stringGetEnv
  */
 static const char* stringGetEnv(const char* iVariable);  // NULL  is default Value


protected  :
  //------------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------------


private :
  static void  Init();
  static  CATBoolean _CGMLogFiltering(const char iFilterOperatorName[]);

  static CATBoolean      _initialized ;
  static CATBoolean      _CATCGMActivateTraces;
  static CATBoolean      _CATCGMActivateStatistics;
  static CATBoolean      _CATCGMActivateFullTraces;
  static CATULONG32      _CATCGMActivateFollowTag;

  static CATBoolean      _RiskyPartialRecovery;

  static CATBoolean      _CATMathDebugExtend ;
  static CATLONG32       _CATCGMTare ;
  static CATBoolean      _ReOrder[4];
  static CATBoolean      _ReOrderRand;
  static CATLONG32       _ReOrderSeed ;
  static CATLONG32       _ReOrderDicho;
  static CATBoolean      _CheckUpThrow;

  static CATBoolean         _CGMLogActivated;
  static CATUnicodeString   _CGMLog;
  static CATBoolean         _CGMLogFiltered;
  static CATUnicodeString   _CGMLogFilter;
  static CATLONG32          _CGMLogLine;
  static CATBoolean         _CGMLogLastWrotenCGMReplay;
  static CATUnicodeString   _CGMLogCGMReplayFilename;

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCX_MEMORY(const CATCX_MEMORY &iCopy);
  CATCX_MEMORY& operator=(const CATCX_MEMORY &iCopy);
  CATCX_MEMORY();
  ~CATCX_MEMORY();

  friend class CATMathODTCGM;
};

 
INLINE CATBoolean  CATCX_MEMORY::CATCGMActivateTraces()
{ if (! _initialized)  CATCX_MEMORY::Init();  return  _CATCGMActivateTraces; }
 
INLINE CATBoolean  CATCX_MEMORY::CATCGMActivateStatistics()
{ if (! _initialized)  CATCX_MEMORY::Init();  return  _CATCGMActivateStatistics; }
 
INLINE CATBoolean  CATCX_MEMORY::CATCGMActivateFullTraces()
{ if (! _initialized)  CATCX_MEMORY::Init();  return  _CATCGMActivateFullTraces; }

INLINE CATULONG32  CATCX_MEMORY::CATCGMActivateFollowTag()
{ if (! _initialized)  CATCX_MEMORY::Init();  return  _CATCGMActivateFollowTag; }


INLINE CATLONG32  CATCX_MEMORY::CGMTare()
{ if (! _initialized)  CATCX_MEMORY::Init();  return  _CATCGMTare; }
 
INLINE CATBoolean  CATCX_MEMORY::ReOrder(CATCX_MEMORY::ReOrderObject iIndex)
{ if (! _initialized)  CATCX_MEMORY::Init();  return  _ReOrder[(int)iIndex]; }
 
INLINE CATBoolean  CATCX_MEMORY::CheckUpThrow()
{ if (! _initialized)  CATCX_MEMORY::Init();  return  _CheckUpThrow; }

INLINE CATBoolean CATCX_MEMORY::CGMLog(const char iFilterOperatorName[])
{ if (! _initialized)  CATCX_MEMORY::Init(); 
  if (! _CGMLogActivated ) return FALSE;
  return  _CGMLogFiltered ? _CGMLogFiltering(iFilterOperatorName) : TRUE; }
 
 
INLINE CATBoolean  CATCX_MEMORY::RiskyPartialRecovery()
{ if (! _initialized)  CATCX_MEMORY::Init();  return  _RiskyPartialRecovery; }
 

#endif
