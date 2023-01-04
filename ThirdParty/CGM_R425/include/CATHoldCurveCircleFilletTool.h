//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATHoldCurveCircleFilletTool:
//
//=============================================================================
// Usage notes:
//=============================================================================
// Jul. 01  PKC  Creation
// Oct. 04  EAB  Versionning Interne - EAB - Octobre 2004
// Oct. 14  Q48  Implement X-scale in CGM-replay
// Apr. 21  SME31 Implement GetCutterDimension()
//=============================================================================
#ifndef CATHoldCurveCircleFilletTool_h
#define CATHoldCurveCircleFilletTool_h

#include "Connect.h"
#include "CATConnectTool.h"

#include "CATString.h"
#include "CATCGMStream.h"

class CATCurve;

class ExportedByConnect CATHoldCurveCircleFilletTool : public CATConnectTool
   {
   public:
      CATHoldCurveCircleFilletTool(CATSoftwareConfiguration * iConfig, CATCurve * iCircleSpine);
      ~CATHoldCurveCircleFilletTool();

      CATLONG32 GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

      CATCurve * GetCircleSpine() const;

      /***********************************************************/
      /* AHG :Methods to stream and unstream the tool for the    */
      /* CGMReplay                                               */
      /***********************************************************/
      static CATString _OperatorId;
      const CATString * GetOperatorId();
      CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
      void WriteInput(CATCGMStream  & ioStream);

   private:

      CATCurve * _CircleSpine;
   };

#endif
