// COPYRIGHT DASSAULT SYSTEMES 2008

#ifndef DSYSysUsage_H
#define DSYSysUsage_H
/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#define HDSYSYSUSAGE                                  void*

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "DSYSysCommon.h"
#include "DSYString.h"
#include "JS0BASEILB.h"

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/


/** @class DSYSysUsageBase */
class DSYSysUsageBase;

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysUsage
 */
class ExportedByJS0BASEILB DSYSysUsage
{
#ifdef DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED
  DSYSysBanEvilConstructors(DSYSysUsage);
#endif  // DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED

  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructors.
  DSYSysUsage(const CATUnicodeString& irFileName = CATUnicodeString());

  /// Destructor.
  virtual ~DSYSysUsage();

  /// Begin event.
  void BeginEvent(HDSYSYSUSAGE* ophUsage);

  /// Push app identifier.
  int PushAppId(HDSYSYSUSAGE ihUsage, const CATUnicodeString& irAppId);

  /// Add event field to event.
  int PushEvent ( HDSYSYSUSAGE ihUsage
                , const CATUnicodeString& irCategory
                , const CATUnicodeString& irType      = CATUnicodeString()
                , const CATUnicodeString& irAction    = CATUnicodeString()
                , const CATUnicodeString& irLabel     = CATUnicodeString());
  int PushEvent ( HDSYSYSUSAGE ihUsage
                , const CATUnicodeString& irCategory
                , const CATLONG64 iValue
                , const CATUnicodeString& irType      = CATUnicodeString()
                , const CATUnicodeString& irAction    = CATUnicodeString()
                , const CATUnicodeString& irLabel     = CATUnicodeString());

  /// Add error field to event.
  int PushError ( HDSYSYSUSAGE ihUsage
                , const CATUnicodeString& irCode
                , const CATUnicodeString& irType    = CATUnicodeString()
                , const CATUnicodeString& irMessage = CATUnicodeString());

  /// End event.
  void EndEvent(HDSYSYSUSAGE* iophUsage);

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////

protected:
  /// Usage object.
  DSYSysUsageBase* m_pUsage;

private:
  /// Version.
  int m_VersionMajor;
  int m_VersionMinor;
};

#endif // DSYSysUsage_H
