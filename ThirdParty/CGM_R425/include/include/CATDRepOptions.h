#ifndef CATDRepOptions_h
#define CATDRepOptions_h
// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : L. Marini 
//
// DESCRIPTION  : DRepOptions is used by the CATLiveBody in order to not mixed bodies from different industry/application.
//                It's used to recognize the origin of thr DRep for the GSD LiveFeature, because this feature has is own industry.
//
//=============================================================================
// Creation LAP March 2014
//
//=============================================================================
#include "YI00IMPL.h"
#include "CATCGMNewArray.h"
#include "CATCGMVirtual.h"
#include "CATDeclarativeOriginModeler.h"
#include "CATDeclarativeApplication.h"
#include "CATDeclarativeContext.h"

class CATSoftwareConfiguration;
class CATPGMDRepBehavior;

class ExportedByYI00IMPL CATDRepOptions : public CATCGMVirtual
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATDRepOptions(short                         iCGMLevel,
                 CATDeclarativeOriginModeler   iDeclarativeOriginModeler,
                 CATDeclarativeApplication     iDeclarativeApplication,
                 CATDeclarativeContextIndustry iDecalarativeIndustry);

  CATDRepOptions(const CATDRepOptions &iDRepOptionsToCopy);

  virtual ~CATDRepOptions();

  enum Outdated_Reason { OUTDATED_DREP_OK = 0,
                         OUTDATED_NO_DREPOPTIONS,
                         OUTDATED_NEW_APPLICATION,
                         OUTDATED_NEW_INDUSTRY,
                         OUTDATED_NEW_ORIGINMODELER };

  int CheckResult(const CATPGMDRepBehavior & iDRepBehavior, CATSoftwareConfiguration * iConfig);
  CATBoolean IsOutdated(const CATPGMDRepBehavior & iDRepBehavior, CATSoftwareConfiguration * iConfig, Outdated_Reason & oReason);

  INLINE short GetCGMSoftWareLevel() const;
  INLINE CATDeclarativeContextIndustry GetDeclarativeContextIndustry() const;
  INLINE CATDeclarativeApplication     GetDeclarativeApplication()     const;
  INLINE CATDeclarativeOriginModeler   GetDeclarativeOriginModeler()   const;
  
  static void Dump(CATCGMOutput& os, CATDRepOptions * ipDRepOptions); 
  static CATDRepOptions * UnStreamAndCreate(CATCGMStream& ioStr);
  static void Stream(CATCGMStream& ioStr, CATDRepOptions * ipDRepOptions);

  void Dump(CATCGMOutput& os);         // Do not use, call the static methode Dump
  void Stream(CATCGMStream& ioStr);    // Do not use, call the static methode Stream
  void UnStream(CATCGMStream& ioStr);  // Do not use, call the static methode UnStreamAndCreate

private:

  short                              _CGMLevel;                  // From CATSoftwareConfiguration
  CATDeclarativeOriginModeler        _DeclarativeOriginModeler;
  CATDeclarativeApplication          _DeclarativeApplication;
  CATDeclarativeContextIndustry      _DecalarativeIndustry;

};

INLINE short CATDRepOptions::GetCGMSoftWareLevel() const {
  return _CGMLevel; }

INLINE CATDeclarativeContextIndustry CATDRepOptions::GetDeclarativeContextIndustry() const {
  return _DecalarativeIndustry;}

INLINE CATDeclarativeApplication CATDRepOptions::GetDeclarativeApplication() const {
  return _DeclarativeApplication; }

INLINE CATDeclarativeOriginModeler CATDRepOptions::GetDeclarativeOriginModeler() const {
  return _DeclarativeOriginModeler; }

#endif
