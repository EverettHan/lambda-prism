//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CATVariableSweepCircleTool:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
//     11/2001  Creation                                       F. Caillaud
//     11/2004  Versionning Interne                            EAB
//  23/10/2014  Implement X-scale in CGM-replay                Q48
//  Mars 2016 JSX : Tool with CATsoftwareconfiguration
//  22/04/2021  Implement GetCutterDimension()                 SME31
//=============================================================================

#ifndef CATVariableSweepCircleTool_h
#define CATVariableSweepCircleTool_h

#include "Connect.h"
#include "CATConnectTool.h"
#include "CATCGMStream.h"
#include "CATString.h"

class CATCurve;
class CATLaw;
class CATMathFunctionX;
class CATSoftwareConfiguration;

class ExportedByConnect CATVariableSweepCircleTool : public CATConnectTool
   {
   public:
      //
      CATVariableSweepCircleTool( CATSoftwareConfiguration * iConfig,
                                  CATCurve *iRadiusSpine,
                                  CATLaw *iRadius,
                                  CATLaw *iMapping);

      virtual ~CATVariableSweepCircleTool();

      //
      // Get methods
      //
      CATLONG32 GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

      CATCurve * GetRadiusSpine() const;
      const CATMathFunctionX * GetRadiusFunction() const;
      const CATLaw * GetRadius() const;
      const CATLaw * GetMapping() const;

      //
      // CGMReplay
      //
      const CATString * GetOperatorId();
      CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
      void WriteInput(CATCGMStream &Str);
      static CATString _OperatorId;

//==============================
// DATA
//==============================
   private:

      CATCurve         *_RadiusSpine;
      CATLaw           *_Radius;
      CATLaw           *_Mapping;
      CATMathFunctionX *_Composition;
   };

#endif
