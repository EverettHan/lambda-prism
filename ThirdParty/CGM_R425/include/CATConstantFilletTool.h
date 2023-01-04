//=============================================================================
// Copyright Dassault Systemes 1998-2010, all rights reserved
//=============================================================================
//
// CATConstantFilletTool:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// Jan. 98      Creation (S. Royer)
// 17/09/09 HLN Ajout SetG2Section()
// 05/03/10 HLN class CATCGMStream remplace #include "CATCGMStream.h"
// 20/10/14 Q48 Implement X-scale in CGM-replay
// 22/04/2021 SME31 Implement GetCutterDimension()
//=============================================================================
#ifndef CATConstantFilletTool_h
#define CATConstantFilletTool_h

#include "Connect.h"
#include "CATConnectTool.h"
#include "CATString.h"

class CATCGMStream;
class CATSoftwareConfiguration;

class ExportedByConnect CATConstantFilletTool : public CATConnectTool
   {
   CATCGMVirtualDeclareClass(CATConstantFilletTool);
   public:
      //---------------------------------------------------------------
      // Object Management
      //---------------------------------------------------------------
      CATConstantFilletTool(CATSoftwareConfiguration * iConfig, const double iRadius);
/*DONOTUSE*/  CATConstantFilletTool(const double iRadius);
      ~CATConstantFilletTool();

      CATLONG32   GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

      void   SetRadius(const double iradius);
      double GetRadius() const;

      void SetConicalSection(double iConicParameter);
      void SetG2Section();
      CATLONG32 GetSectionType() const;

      double GetConicParameter() const;

      // AHG : adaptation CGMreplay
      // Methodes de stream et de unstream ( cf architecture CATCGMOperator )
      /** @nodoc @nocgmitf */
      CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

      /** @nodoc @nocgmitf */
      void WriteInput(CATCGMStream  & Str);
      static CATString _OperatorId;
      /** @nodoc @nocgmitf */
      const CATString * GetOperatorId();

   private:
      //---------------------------------------------------------------
      // Private Data
      //---------------------------------------------------------------
      double     _radius;
      CATLONG32  _SectionType;
      double     _ConicParameter;
   };

#endif
