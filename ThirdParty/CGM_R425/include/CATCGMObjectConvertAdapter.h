/* -*-c++-*- */
#ifndef CATCGMObjectConvertAdapter_h
#define CATCGMObjectConvertAdapter_h


#include "ExportedByCATCGMFusion.h"
#include "CATListOfCATICGMObjects.h"
#include "CATCGMStreamVersionLimited.h"

class ExportedByCATCGMFusion CATCGMObjectConvertAdapter
{
public:

	CATCGMObjectConvertAdapter();
	virtual ~CATCGMObjectConvertAdapter();

	virtual void SetTargetVersion(CATCGMStreamVersion & iTargetVersion) = 0;
	virtual void AddObjectsToConvert(CATLISTP(CATICGMObject) & iObjectsToConvert) = 0;
	virtual void GetObjectsToConvert(CATLISTP(CATICGMObject) & oObjectsToConvert) = 0;
	virtual void Convert() = 0;

	virtual CATICGMObject*  GetConvertedResult(CATICGMObject* & iObjectToConvert) = 0;
	virtual void UpdateIncompatibilityInfo(CATLISTP(CATICGMObject) & iNewIncompatibleObjects) = 0;
};

#endif

