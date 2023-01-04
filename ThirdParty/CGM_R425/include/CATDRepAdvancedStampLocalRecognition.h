#ifndef CATDRepAdvancedStampLocalRecognition_H
#define CATDRepAdvancedStampLocalRecognition_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATDRepAdvancedStampRecognitionBase.h"
#include "CATDeclarativeManifoldAgentPriorityDef.h"

class ExportedByPersistentCell CATDRepAdvancedStampLocalRecognition : public CATDRepAdvancedStampRecognitionBase 
{
public:
  CATCGMDeclareManifoldAgent(CATDRepAdvancedStampLocalRecognition, CATDRepAdvancedStampRecognitionBase)
	
	// Constructor
  CATDRepAdvancedStampLocalRecognition();
	
  // Destructor
  virtual ~CATDRepAdvancedStampLocalRecognition();

  //=======================================================================================
  // Virtual pure methods from parent class : CATDeclarativeManifoldAgent
  //---------------------------------------------------------------------------------------
  virtual int GetPriority();
  virtual CATDeclarativeManifoldAgent* Clone();
  //=======================================================================================

  virtual CATDRepAdvancedStampLocalRecognition * GetAsDRepAdvancedStampLocalRecognition();

protected:

  virtual void GetInputCellManifoldList(ListPOfCATCellManifold & oInputCellManifoldList);

private:


};

#endif
