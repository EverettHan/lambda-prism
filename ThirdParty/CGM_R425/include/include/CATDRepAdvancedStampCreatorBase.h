#ifndef CATDRepAdvancedStampCreatorBase_H
#define CATDRepAdvancedStampCreatorBase_H

#include "PersistentCell.h"
#include "CATDeclarativeManifoldAgent.h"
#include "CATCGMNewArray.h"

class CATGMLocalAdvancedStampRecognizerBridge;
class CATGMAdvancedStampData;
class CATGMAdvancedStampLiveData;

class ExportedByPersistentCell CATDRepAdvancedStampCreatorBase : public CATDeclarativeManifoldAgent 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATDRepAdvancedStampCreatorBase();
	
  // Destructor
  virtual ~CATDRepAdvancedStampCreatorBase();

  //=======================================================================================
  // Virtual pure methods from parent class : CATDeclarativeManifoldAgent
  //---------------------------------------------------------------------------------------
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  //---------------------------------------------------------------------------------------

protected:

  CATLiveBody * GetCurrentLiveBody();
  HRESULT CreateDRepAdvancedStamp(CATGMAdvancedStampLiveData * iAdvancedStampLiveData);

private:
  

};

#endif
