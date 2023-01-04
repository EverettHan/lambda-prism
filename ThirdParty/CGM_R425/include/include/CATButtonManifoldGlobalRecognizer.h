//=======================================================================================
// VB7 February 2017
// Agent which create all ButtonManifold DRep on a body
//=======================================================================================

#ifndef CATButtonManifoldRecognizer_H
#define CATButtonManifoldRecognizer_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATGMLiveShapeButtonData.h"
#include "CATButtonManifoldRecognizerBase.h"

class CATGMLiveShapeButtonRecognizerOpe;
class CATGMLiveShapeButtonData;
class CATGMLiveShapeButtonRecognizerBridge;

class ExportedByPersistentCell CATButtonManifoldGlobalRecognizer : public CATButtonManifoldRecognizerBase
{
public:
  CATCGMDeclareManifoldAgent(CATButtonManifoldGlobalRecognizer, CATButtonManifoldRecognizerBase);
	
	// Constructor
  CATButtonManifoldGlobalRecognizer();
	
  // Destructor
	virtual ~CATButtonManifoldGlobalRecognizer();

  //=======================================================================================
  // Virtual pure methods from parent class : CATDeclarativeManifoldAgent
  //---------------------------------------------------------------------------------------
  virtual int GetPriority();
  virtual CATDeclarativeManifoldAgent* Clone();
  //=======================================================================================

  virtual CATButtonManifoldGlobalRecognizer * GetAsButtonManifoldGlobalRecognizer();

protected:
  //=======================================================================================
  // Virtual pure methods from parent class : CATButtonManifoldRecognizerBase
  //---------------------------------------------------------------------------------------
  virtual void GetInputCellManifoldList(ListPOfCATCellManifold & oInputCellManifoldList);
  //=======================================================================================

};

#endif
