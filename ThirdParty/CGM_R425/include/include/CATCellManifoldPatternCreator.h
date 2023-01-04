#ifndef CATCellManifoldPatternCreator_H
#define CATCellManifoldPatternCreator_H

#include "CATDeclarativeManifoldAgent.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATMathTransformation.h"

class CATCellManifoldGroupOperator;
class CATPersistentCellCellFollower;

class ExportedByPersistentCell CATCellManifoldPatternCreator : public CATDeclarativeManifoldAgent
{
public:

  CATCGMNewClassArrayDeclare;     

	// Constructor
  CATCellManifoldPatternCreator();
  CATCellManifoldPatternCreator(short iNbInstances, CATMathTransformation &iUnitaryTransfo);
	
  // Destructor
	virtual ~CATCellManifoldPatternCreator();

  virtual HRESULT CreateImageManifolds() = 0;
  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  virtual CATDeclarativeManifoldAgent* Clone() = 0;

private:

 // void SetReferenceLiveBody(CATLiveBody *iRefLiveBody);
  //short _NbInstances;
  //CATMathTransformation _UnitaryTransfo;
};

#endif
