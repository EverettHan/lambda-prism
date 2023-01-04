//=============================================================================
// Copyright Dassault Systemes 2001-2010, all rights reserved
//=============================================================================
//
// CATChordalFilletTool:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// 23/10/14 : Q48 : Implement X-scale in CGM-replay
// 24/11/09 : HLN : Ajout SetG2Section(), 05/03/10 Promotion
// Octobre 2004 Versionning Interne - EAB
// Nov. 2001	Creation  D. Johansson
// 22/04/2021 : SME31 : Implement GetCutterDimension()
//=============================================================================
#ifndef CATChordalFilletTool_h
#define CATChordalFilletTool_h

#include "Connect.h"
#include "CATConnectTool.h"
#include "CATString.h"

class CATCGMStream;
class CATSoftwareConfiguration;

class ExportedByConnect CATChordalFilletTool : public CATConnectTool  
   {
   CATCGMVirtualDeclareClass(CATChordalFilletTool);
   public:
      //---------------------------------------------------------------
      // Object Management
      //---------------------------------------------------------------
      CATChordalFilletTool(CATSoftwareConfiguration * iConfig,const double iChord) ;
/* DO NOT USE */ CATChordalFilletTool(const double iChord) ;
      ~CATChordalFilletTool() ;

      //---------------------------------------------------------------
      // Public Methods
      //---------------------------------------------------------------

      CATLONG32	GetType() const ;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

      void   SetChord(const double iChord) ;
      double GetChord() const ;

      void SetConicalSection(double iConicParameter);
      void SetG2Section();
      CATLONG32 GetSectionType() const;
      double GetConicParameter() const;

      // AHG : adaptation CGMreplay
      // Methodes de stream et de unstream ( cf architecture CATCGMOperator )
      CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

      void WriteInput(CATCGMStream  & Str) ;
      static CATString   _OperatorId ;
      const  CATString * GetOperatorId() ;

   private:
      //---------------------------------------------------------------
      // Private Data
      //---------------------------------------------------------------
      double _Chord ;
      CATLONG32  _SectionType;
      double     _ConicParameter;
   };

#endif
