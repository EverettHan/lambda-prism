//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATVariableCircleFilletTool:
//
//=============================================================================
// Usage notes:
//=============================================================================
// May. 00     Creation                                       P. Catel
// Oct. 14     Implement X-scale in CGM-replay                J. Dickens
// Apr. 21     Implement GetCutterDimension()                 SME31
//=============================================================================
#ifndef CATVariableCircleFilletTool_h
#define CATVariableCircleFilletTool_h

#include "Connect.h"
#include "CATConnectTool.h"

#include "CATString.h"
#include "CATCGMStream.h"

class CATCurve;
class CATLaw;
class CATMathFunctionX;
class CATSoftwareConfiguration;

class ExportedByConnect CATVariableCircleFilletTool : public CATConnectTool
   {
   public:

      CATVariableCircleFilletTool(CATSoftwareConfiguration * iConfig,
         CATCurve * iCircleSpine, 
         CATCurve * iRadiusSpine,
         CATLaw * iRadiusLaw,
         CATLaw * iMappingLaw);

      ~CATVariableCircleFilletTool();

      CATLONG32 GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

      CATCurve * GetCircleSpine() const;
      CATCurve * GetRadiusSpine() const;

      const CATMathFunctionX * GetRadiusFunction() const;
      const CATLaw * GetRadius() const;
      const CATLaw * GetMapping() const;

      void SetConicalSection(double iConicParameter);
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

      CATLONG32  _SectionType;
      double     _ConicParameter;
      CATCurve * _CircleSpine;
      CATCurve * _RadiusSpine;
      CATLaw *   _Radius;
      CATLaw *   _Mapping;
      CATMathFunctionX * _Composition;

   };

#endif
