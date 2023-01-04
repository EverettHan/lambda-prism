#ifndef CGMSPABeforeRunCallback_h
#define CGMSPABeforeRunCallback_h

#include "ExportedByCATTopologicalObjects.h"

#ifdef CATIAR419
class CATTopOperator;
/**
* This class provides a callback for CGM Component to
* check if operators are authorized by Spatial licensing
* from within CATExtTopOperator::BeforeRun
**/
class ExportedByCATTopologicalObjects CGMSPABeforeRunCallback
{
public:
	virtual ~CGMSPABeforeRunCallback(){}
	virtual void BeforeRun(CATTopOperator& iOper, int depth, int depthForChain) = 0;

	static CGMSPABeforeRunCallback* Get();
	static void Set(CGMSPABeforeRunCallback* iCallback);
};
#endif
#endif

