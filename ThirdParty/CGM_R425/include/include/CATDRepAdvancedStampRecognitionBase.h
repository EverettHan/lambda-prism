#ifndef CATDRepAdvancedStampRecognitionBase_H
#define CATDRepAdvancedStampRecognitionBase_H

#include "PersistentCell.h"
#include "CATDeclarativeManifoldAgent.h"
#include "CATCGMNewArray.h"
#include "CATDRepAdvancedStampCreatorBase.h"

class CATGMLocalAdvancedStampRecognizerBridge;

class ExportedByPersistentCell CATDRepAdvancedStampRecognitionBase : public CATDRepAdvancedStampCreatorBase 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATDRepAdvancedStampRecognitionBase();
	
  // Destructor
  virtual ~CATDRepAdvancedStampRecognitionBase();

  //=======================================================================================
  // Virtual pure methods from parent class : CATDeclarativeManifoldAgent
  //---------------------------------------------------------------------------------------
  virtual HRESULT CreateImageManifolds();
  //---------------------------------------------------------------------------------------

protected:

  virtual void GetInputCellManifoldList(ListPOfCATCellManifold & oInputCellManifoldList)=0;

private:
  
  HRESULT ComputeAdvancedStampRecognition(ListPOfCATCellManifold & iInputCellManifoldList);
  HRESULT CallAdvancedStampRecognizer(CATCellManifold * iCM, ListPOfCATCellManifold & oOutputCellManifold);

private:
  CATGMLocalAdvancedStampRecognizerBridge * _AdvancedStampRecognizerOpe;

};

#endif
