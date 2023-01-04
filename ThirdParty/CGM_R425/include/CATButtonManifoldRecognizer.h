//=======================================================================================
// VB7 February 2017
// Agent which create a new CATButtonManifold DRep.
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

class ExportedByPersistentCell CATButtonManifoldRecognizer : public CATButtonManifoldRecognizerBase
{
public:
  CATCGMDeclareManifoldAgent(CATButtonManifoldRecognizer, CATButtonManifoldRecognizerBase);
	
	// Constructor
  CATButtonManifoldRecognizer();
	
  // Destructor
	virtual ~CATButtonManifoldRecognizer();

  //=======================================================================================
  // Virtual pure methods from parent class : CATDeclarativeManifoldAgent
  //---------------------------------------------------------------------------------------
  virtual int GetPriority();
  virtual CATDeclarativeManifoldAgent* Clone();
  //=======================================================================================

  virtual CATButtonManifoldRecognizer * GetAsButtonManifoldRecognizer();

protected:
  //=======================================================================================
  // Virtual pure methods from parent class : CATButtonManifoldRecognizerBase
  //---------------------------------------------------------------------------------------
  virtual void GetInputCellManifoldList(ListPOfCATCellManifold & oInputCellManifoldList);
  //=======================================================================================

};

#endif
