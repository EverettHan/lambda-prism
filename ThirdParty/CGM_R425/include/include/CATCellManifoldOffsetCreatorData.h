#ifndef CATCellManifoldOffsetCreatorData_H
#define CATCellManifoldOffsetCreatorData_H

#include "CATDeclarativeManifoldAgent.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATMathTransformation.h"
#include "CATListOfDouble.h"

class CATCellManifoldGroupOperator;
class CATPersistentCellCellFollower;

class ExportedByPersistentCell CATCellManifoldOffsetCreatorData : public CATDeclarativeManifoldAgent
{
public:
  CATCGMDeclareManifoldAgent(CATCellManifoldOffsetCreatorData, CATDeclarativeManifoldAgent);
	
	// Constructor
  CATCellManifoldOffsetCreatorData();
  CATCellManifoldOffsetCreatorData(CATListOfDouble & iOffsetValues);
	
  // Destructor
	virtual ~CATCellManifoldOffsetCreatorData();

  virtual void SetReferenceLiveBody(CATLiveBody *iRefLiveBody);

  virtual HRESULT CreateImageManifolds();
  virtual CATCellManifoldOffsetCreator * GetAsCellManifoldOffsetCreator();
  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  virtual CATDeclarativeManifoldAgent* Clone();
  virtual void SetNullOffsetInstance(int iNullOffsetInstance);

protected:

  short _NbInstances;
  CATListOfDouble _OffsetValues;
  int _NullOffsetInstance; // numero de peau de la peau dont l'offset est null. Permet d'eviter de faire test double.
  CATLiveBody*  _RefLiveBody; 
};

#endif
