//=============================================================================
// Copyright Dassault Systemes 2001-2014, all rights reserved
//=============================================================================
//
// CATVariableChordalFilletTool:
//
//=============================================================================
// Usage notes:
//=============================================================================
// 23/10/14 : Q48 : Implement X-scale in CGM-replay
// 16/01/14 : HLN : Ajout SetG2Section()
// Feb. 02     Creation                                       D. Johansson
// Apr. 21     Implement GetCutterDimension()                 SME31
//=============================================================================
#ifndef CATVariableChordalFilletTool_h
#define CATVariableChordalFilletTool_h

#include "Connect.h"

#include "CATConnectTool.h"
#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATString.h"
#include "CATCGMStream.h"

class CATCurve;
class CATLaw;
class CATMathFunctionX;
class CATMathInterval;
class CATSoftwareConfiguration;

class ExportedByConnect CATVariableChordalFilletTool : public CATConnectTool
   {
   CATCGMVirtualDeclareClass(CATVariableChordalFilletTool);
   public:

      CATVariableChordalFilletTool(CATSoftwareConfiguration * iConfig,CATCurve * iSpine, CATLaw * iChordLaw, CATLaw * iMappingLaw);
      ~CATVariableChordalFilletTool();

      CATLONG32 GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

      CATCurve * GetSpine() const;
      const CATMathFunctionX * GetChordFunction() const;
      const CATLaw * GetChord() const;
      const CATLaw * GetMapping() const;

      CATBoolean IsToolConstantAtPoint(const double iSpineParam) const;
      CATBoolean IsToolConstantOnDomain(double &ioStartParam, double &ioEndParam) const;

      void SetConicalSection(double iConicParameter);

      void SetG2Section();
      CATLONG32 GetSectionType() const;
      double GetConicParameter() const;

      /***********************************************************/
      /* AHG :Methods to stream and unstream the tool for the    */
      /* CGMReplay                                               */
      /***********************************************************/
      static CATString _OperatorId;
      const CATString * GetOperatorId();
      CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
      void WriteInput(CATCGMStream  & ioStream);

   private:

      CATMathDiagnostic GetSpineParamFromChordParam(const CATMathInterval &SpineDomain, const double iChordParam, double & oW) const; 

      // to know if CATLaw _Chord is a constant function on one specific arc 
      CATBoolean IsChordConstantOnArc(const CATLONG32 iChordArc) const;

//==========================================================
// DATA
//==========================================================
   private:
      CATLONG32  _SectionType;
      double     _ConicParameter;
      CATCurve * _Spine;
      CATLaw   * _Chord;
      CATLaw   * _Mapping;
      CATMathFunctionX * _Composition;
   };

#endif
