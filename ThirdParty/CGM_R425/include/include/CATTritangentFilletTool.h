//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================
//
// CATTritangentFilletTool:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// ??/11/06 CWM Creation
// 20/10/14 Q48 Implement X-scale in CGM-replay
// 22/04/2021 SME31 Implement GetCutterDimension()
//=============================================================================
#ifndef CATTritangentFilletTool_h
#define CATTritangentFilletTool_h

#include "Connect.h"

#include "CATConnectTool.h"
#include "CATCGMStream.h"
#include "CATString.h"

class CATSoftwareConfiguration;

class ExportedByConnect CATTritangentFilletTool : public CATConnectTool
   {
   CATCGMVirtualDeclareClass(CATTritangentFilletTool);
   public:

      CATTritangentFilletTool(CATSoftwareConfiguration * iConfig);
      ~CATTritangentFilletTool();

      CATLONG32   GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;
      // cwm: pour le tritangent special AutoFillet 
      // traces d'une sphere qui roule sur 2 surfaces a section circulaire
      void  SetDoubleCircleProfile();
      CATBoolean IsDoubleCircleProfileSet() const;


      // AHG : adaptation CGMreplay
      // Methodes de stream et de unstream ( cf architecture CATCGMOperator )
      void WriteInput(CATCGMStream  & Str);
      static CATString _OperatorId;
      const CATString * GetOperatorId();
//=========================================================
//DATA
//=========================================================
   private:
      CATBoolean _DoubleCircleProfile;
   };

#endif
