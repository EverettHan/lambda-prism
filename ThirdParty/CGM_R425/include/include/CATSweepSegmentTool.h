//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATSweepSegmentTool:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// Aug. 99     Creation                                       C. Pradal
// Oct. 14     Implement X-scale in CGM-replay                Q48
// Apr. 21     Implement GetCutterDimension()                 SME31
//=============================================================================
#ifndef CATSweepSegmentTool_h
#define CATSweepSegmentTool_h

#include "Connect.h"
#include "CATConnectTool.h"
#include "CATCGMStream.h"
#include "CATString.h"
class CATExtCGMReplay;

class ExportedByConnect CATSweepSegmentTool : public CATConnectTool
{
 public:
  CATSweepSegmentTool();
  ~CATSweepSegmentTool();

  CATLONG32 GetType() const;
  CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

  //CGMReplay
	static CATString _OperatorId;
	const CATString * GetOperatorId();
	CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
	void WriteInput(CATCGMStream  & ioStream);
};

#endif
