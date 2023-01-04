#ifndef CATDRepAdvancedStampCreator_H
#define CATDRepAdvancedStampCreator_H

#include "PersistentCell.h"
#include "CATDeclarativeManifoldAgent.h"
#include "CATCGMNewArray.h"
#include "CATDRepAdvancedStampCreatorBase.h"
#include "CATDeclarativeManifoldAgentPriorityDef.h"
#include "ListPOfCATGMAdvancedStampData.h"

class CATGMAdvancedStampData;


class ExportedByPersistentCell CATDRepAdvancedStampCreator : public CATDRepAdvancedStampCreatorBase 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATDRepAdvancedStampCreator();
	
  // Destructor
  virtual ~CATDRepAdvancedStampCreator();

  //=======================================================================================
  // Virtual pure methods from parent class : CATDeclarativeManifoldAgent
  //---------------------------------------------------------------------------------------
  virtual int GetPriority();
  virtual HRESULT CreateImageManifolds();
  //---------------------------------------------------------------------------------------


  void SetAdvancedStampData(CATGMAdvancedStampData * iAdvancedStampData);

  CATDeclarativeManifoldAgent* Clone();

protected:


private:
  CATGMAdvancedStampLiveData * ComputeAdvancedStampLiveData(CATGMAdvancedStampData * iAdvancedStampData);

private:

  ListPOfCATGMAdvancedStampData  _InputAdvancedStampDataList;

};

#endif
