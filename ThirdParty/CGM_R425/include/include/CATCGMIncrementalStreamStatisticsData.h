/* -*-c++-*- */
#ifndef CATCGMIncrementalStreamStatisticsData_H
#define CATCGMIncrementalStreamStatisticsData_H

#include "ExportedByCATCGMFusion.h"  
#include "CATCGMHashTable.h"

class ExportedByCATCGMFusion CATCGMIncrementalStreamStatisticsData
{

public:

	CATCGMIncrementalStreamStatisticsData();
	~CATCGMIncrementalStreamStatisticsData();

	void ResetAll();

	int NbObjectsInContainer;
	int NbSavedObjectsInStdSave;
	int NbSavedObjectsInIncSave;

	// NbNew : Creation
	// NbRemoved : Removed from Container
	// NbDeleted : Deleted and has been saved previously
	int NbNew;
	int NbRemoved;
	int NbDeleted;

	int NbUndoLogObjects;

	// NbObjectsInModifiedList ~= NbGeometricModified + NbSharpnessChange + NbLyingOnChange
	int NbObjectsInModifiedList; 
	int NbGeometricModified;
	int NbSharpnessChange;
	int NbLyingOnChange;
	int NbModifiedLinked;

	int NbWithAttribute;
	int NbPermanentSave;
	int NbNoFrozenTopo;

	int NbLimitCompactMapping;

	int NbEstimatedObjToSave;

  CATCGMHashTable * ObjectTypesHT;
};

#endif

