//=======================================================================================
// VB7 February 2017
// parent class of CATButtonManifoldRecognizer and CATButtonManifoldGlobalRecognizer
//=======================================================================================

#ifndef CATButtonManifoldRecognizerBase_H
#define CATButtonManifoldRecognizerBase_H

#include "CATDeclarativeManifoldUpgradeAgent.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATGMLiveShapeButtonData.h"

class CATGMLiveShapeButtonRecognizerOpe;
class CATGMLiveShapeButtonData;
class CATGMLiveShapeButtonRecognizerBridge;

class ExportedByPersistentCell CATButtonManifoldRecognizerBase : public CATDeclarativeManifoldUpgradeAgent
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATButtonManifoldRecognizerBase();
	
  // Destructor
	virtual ~CATButtonManifoldRecognizerBase();

  //=======================================================================================
  // Virtual pure methods from parent class : CATDeclarativeManifoldAgent
  //---------------------------------------------------------------------------------------
  virtual HRESULT CreateImageManifolds();
  virtual int GetPriority() = 0;
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  virtual CATDeclarativeManifoldAgent* Clone()=0;
  //=======================================================================================

protected:

  virtual void GetInputCellManifoldList(ListPOfCATCellManifold & oInputCellManifoldList) = 0;

private:

  void RecognizeButton(CATCellManifold * iCM);
  void CreateButtonManifolds();
  CATBoolean Locate(ListPOfCATGMLiveShapeButtonData & iButtonDataList,  CATGMLiveShapeButtonData * iButtonData);
  void CreateButtonRecognizer();

private:

  ListPOfCATGMLiveShapeButtonData _ResultButtonDataList;

  CATGMLiveShapeButtonRecognizerBridge * _ButtonRecognizerBridge;

};

#endif
