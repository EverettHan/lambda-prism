//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATSweepCircleTool:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// Jan. 01  STY  Creation
// Oct. 14  Q48  Implement X-scale in CGM-replay
// Apr. 21  SME31 Implement GetCutterDimension()
//=============================================================================
#ifndef CATSweepCircleTool_h
#define CATSweepCircleTool_h

#include "Connect.h"
#include "CATConnectTool.h"
#include "CATCGMStream.h"
#include "CATString.h"
class CATExtCGMReplay;

class ExportedByConnect CATSweepCircleTool : public CATConnectTool
{
 public:
  CATSweepCircleTool(const double iRadius);
  ~CATSweepCircleTool();

  double GetRadius() const;
  CATLONG32 GetType() const;
  CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

   //CGMReplay
	static CATString _OperatorId;
	const CATString * GetOperatorId();
	CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
	void WriteInput(CATCGMStream  & ioStream);
  
 private:
  double _radius;
};

#endif
