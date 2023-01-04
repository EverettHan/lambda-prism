//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATChamferTool:
//
//=============================================================================
// Usage notes:
//=============================================================================
// Mar. 98     Creation                                   S. Royer
// Sep. 98     Modification : Angle                       P-A Lourme
// Oct. 04     Versionning Interne                        EAB
// Oct. 14     Implement X-scale in CGM-replay            Q48
// Apr. 21     Implement GetCutterDimension()             SME31
//=============================================================================
#ifndef CATChamferTool_h
#define CATChamferTool_h

#include "Connect.h"
#include "CATConnectTool.h"
#include "CATCGMStream.h"
#include "CATString.h"

class CATCurve;
class CATSoftwareConfiguration;

class ExportedByConnect CATChamferTool : public CATConnectTool
   {
   CATCGMVirtualDeclareClass(CATChamferTool);
   public:
      CATChamferTool();
      CATChamferTool(CATSoftwareConfiguration * iConfig, const double idist1, const double idist2, CATCurve * iSpine);
      CATChamferTool(CATSoftwareConfiguration * iConfig, const double iValue1, const double iValue2, const CATLONG32 iCATChamferToolType);

      ~CATChamferTool();

      CATLONG32 GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;
      // new chamfer 
      double GetFirstValue() const;
      double GetSecondValue() const;

      void SetConfig(CATSoftwareConfiguration * iConfig);
      void SetType(const CATLONG32 iType);
      void SetFirstValue(const double iFirstValue);
      void SetSecondValue(const double iSecondValue);

      void SetBadShapeStaus(const CATBoolean iStatus);
      CATBoolean GetBadShapeStatus() const;

      void SetApproxChamferMode();
      CATBoolean GetStatusOfApproxChamferMode() const;

      void SetOriginalChamferValues(double iD1, double iD2);
      void GetOriginalChamferValues(double &ioD1, double &ioD2);

      // Methodes de stream et de unstream ( cf architecture CATCGMOperator )
      /** @nodoc @nocgmitf */
      CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

      /** @nodoc @nocgmitf */
      void WriteInput(CATCGMStream  & Str);
      static CATString _OperatorId; 
      /** @nodoc @nocgmitf */
      const CATString * GetOperatorId(); 
//================================================
// DATA
//================================================
   private:
      CATLONG32   _ChamferToolType;
      double      _dist1, _dist2;
      double      _Value1,_Value2;
      CATBoolean _BadShapeStatus;
      CATBoolean _ApproxChamferMode;
      CATCurve * _Spine;
      double _originalD1, _originalD2;
   };

#endif
