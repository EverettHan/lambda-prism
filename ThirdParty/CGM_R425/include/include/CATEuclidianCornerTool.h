//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATEuclidianCornerTool:
//
//=============================================================================
// Usage notes:
//=============================================================================
// Jan. 1999     Creation                                       T. Phung
// Oct. 2004     Versionning Interne                            EAB
// Oct. 2014     Implement X-scale in CGM-replay                Q48
//  Mars 2016 JSX : Tool with CATsoftwareconfiguration 
// Apr. 2021     Implement GetCutterDimension()                 SME31
//=============================================================================
#ifndef CATEuclidianCornerTool_h
#define CATEuclidianCornerTool_h

#include "Connect.h"

#include "CATConnectTool.h"
#include "CATCGMStream.h"
#include "CATString.h"

class CATCurve;
class CATLaw;
class CATMathFunctionX;
class CATSoftwareConfiguration;

class ExportedByConnect CATEuclidianCornerTool : public CATConnectTool
{
 public:
   CATEuclidianCornerTool(CATSoftwareConfiguration * iConfig, CATLONG32 iSide, const double iRadius);
  ~CATEuclidianCornerTool();

  CATLONG32 GetType() const;
  CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

  CATLONG32 GetSide() const;
  void SetSide(CATLONG32 iSide);
  double GetRadius() const;


  // CGM-replay mechanism
  // --------------------

  CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

  void WriteInput(CATCGMStream  & Str);
  static CATString _OperatorId;
  const CATString * GetOperatorId();
  
  //=========================
  // DATA
  //=========================
 private:
  double _Radius;
  CATLONG32   _Side;
};

#endif
