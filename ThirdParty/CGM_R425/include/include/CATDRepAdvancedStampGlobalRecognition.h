#ifndef CATDRepAdvancedStampGlobalRecognition_H
#define CATDRepAdvancedStampGlobalRecognition_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATDRepAdvancedStampRecognitionBase.h"
#include "CATDeclarativeManifoldAgentPriorityDef.h"

class ExportedByPersistentCell CATDRepAdvancedStampGlobalRecognition : public CATDRepAdvancedStampRecognitionBase 
{
public:
  CATCGMDeclareManifoldAgent(CATDRepAdvancedStampGlobalRecognition, CATDRepAdvancedStampRecognitionBase)
	
	// Constructor
  CATDRepAdvancedStampGlobalRecognition();
	
  // Destructor
  virtual ~CATDRepAdvancedStampGlobalRecognition();

  //=======================================================================================
  // Virtual pure methods from parent class : CATDeclarativeManifoldAgent
  //---------------------------------------------------------------------------------------
  virtual int GetPriority();
  virtual CATDeclarativeManifoldAgent* Clone();
  //=======================================================================================

protected:

  virtual void GetInputCellManifoldList(ListPOfCATCellManifold & oInputCellManifoldList);

private:


};

#endif
