//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CATFilletR1R2Tool:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// Jul. 2001	Creation                  F. Caillaud
// Oct. 2004  Versionning Interne                EAB
// Oct. 2014  Implement X-scale in CGM-replay    Q48
// Mars 2016  clean & Factorize in Mother Class  JSX
// Apr. 2021  Implement GetCutterDimension()     SME31
//=============================================================================

#ifndef CATFilletR1R2Tool_h
#define CATFilletR1R2Tool_h

#include "Connect.h"
#include "CATConnectTool.h"
#include "CATString.h"
class CATSoftwareConfiguration;
class CATCGMStream;

class ExportedByConnect CATFilletR1R2Tool : public CATConnectTool
   {
   public:
      //---------------------------------------------------------------
      // Object Management
      //---------------------------------------------------------------
      CATFilletR1R2Tool(CATSoftwareConfiguration * iConfig, 
                        const double iRadius1, const double iRadius2);

      virtual ~CATFilletR1R2Tool();

      //---------------------------------------------------------------
      // Public Methods
      //---------------------------------------------------------------

      void   SetRadius1(const double iRadius);
      void   SetRadius2(const double iRadius);
      double GetRadius1() const;
      double GetRadius2() const;
      CATLONG32 GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;
      // CGMreplay
      CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
      void   WriteInput(CATCGMStream  & Str);
      static CATString _OperatorId;
      const  CATString * GetOperatorId();

   //---------------------------------------------------------------
   // Data
   //---------------------------------------------------------------

   private:
      double _Radius1;
      double _Radius2;
   };

#endif
