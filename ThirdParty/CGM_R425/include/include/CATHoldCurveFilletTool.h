//=============================================================================
// Copyright Dassault Systemes 2012-2015, all rights reserved
//=============================================================================
//
// CATHoldCurveFilletTool:
//
//=============================================================================
// Usage notes:
//=============================================================================
// History:
// 23/11/15 : HLN : mkmk-Warning ;
// 21/09/15 : HLN : Add methods SetConicalSection, SetG2Section, GetSectionType, GetConicParameter
// 28/05/12     Creation                                               XMH
// 23/10/14     Implement X-scale in CGM-replay                        Q48
// 22/04/2021   Implement GetCutterDimension()                         SME31
//=============================================================================
#ifndef CATHoldCurveFilletTool_h
#define CATHoldCurveFilletTool_h

#include "Connect.h"
#include "CATConnectTool.h"
#include "CATString.h"

#include "CATCGMStream.h"
class CATSoftwareConfiguration;

class ExportedByConnect CATHoldCurveFilletTool : public CATConnectTool
   {
   CATCGMVirtualDeclareClass(CATHoldCurveFilletTool);
   public:
      //---------------------------------------------------------------
      // Object Management
      //---------------------------------------------------------------
      CATHoldCurveFilletTool(CATSoftwareConfiguration * iConfig);
      ~CATHoldCurveFilletTool();

      //---------------------------------------------------------------
      // Public Methods
      //---------------------------------------------------------------
      CATLONG32 GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

      void SetConicalSection(double iConicParameter);
      void SetG2Section();
      CATLONG32 GetSectionType() const;
      double GetConicParameter() const;

      /*************************************************************/
      /* Methods to stream and unstream the tool for the CGMReplay */
      /*************************************************************/
      static CATString _OperatorId;
      const CATString * GetOperatorId();
      CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
      void WriteInput(CATCGMStream  & ioStream);

      //---------------------------------------------------------------
      // Data
      //---------------------------------------------------------------
   private:
      CATLONG32  _SectionType;
      double     _ConicParameter;
   };
#endif
